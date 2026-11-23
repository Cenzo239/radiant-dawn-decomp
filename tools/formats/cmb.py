"""Reader / disassembler for FE10 event scripts (Scripts/*.cmb).

See docs/formats/maps_events.md, section "Event scripts (.cmb)".

Container (uncompressed; NOTE: header/table integers are LITTLE-endian,
while immediate operands inside the bytecode are big-endian):

  0x00 char[4]  "cmb\\0"
  0x04 char[20] script file name ("C0101.cmb"), NUL padded
  0x18 u32      build date as BCD-ish hex, e.g. 0x20061024 = 2006-10-24
  0x1C u32      runtime: next-script link (0 in file)
  0x20 u16      runtime: base index of this script's static vars (0 in file)
  0x22 u16      number of script-static variables to reserve
  0x24 u32      offset of string table (always 0x2C); bytecode string
                operands are offsets relative to this
  0x28 u32      offset of function table: u32 offsets of function headers,
                terminated by 0

Function / event header (pointed to by the table):
  +0x00 u32 name offset (absolute, 0 = anonymous)   name is registered in the
            global symbol table, so other scripts can call it by name
  +0x04 u32 code offset (absolute)
  +0x08 u32 runtime: owning script
  +0x0C u8  trigger kind (0 = plain function, else event trigger, see KINDS)
  +0x0D s8  argument count
  +0x0E s8  trigger parameter count n
  +0x0F u8  unused (uninitialised garbage in the files)
  +0x10 u16 function index (position in the function table)
  +0x12 u16 frame size in 4-byte slots (args + locals)
  +0x14 u16 params[n]  trigger parameters (ints or string-table offsets)
  ...       code (4-byte aligned), runs until the next header

Interpreter: fn_801D0EC0 (opcode switch), native call fn_801D20D4,
script call fn_801D0D58, loader fn_800C3840 / relocation fn_800C358C,
builtin registration fn_800C3C3C(name, fn, argc).
"""
import os
import struct
import sys

# ---------------------------------------------------------------- builtins
# Native functions registered via fn_800C3C3C(name, fn, argc) in main.dol
# (656 entries): "Name:argc:fnaddr-0x80000000".
_BUILTIN_TABLE = """
CreateNoticeFrame:4:036398 CreateNoticeLFrame:7:038D38 DeleteNoticeFrame:0:039030
DialogResult:0:06BFE0 DialogSetDefault:1:06BFEC ArenaDump:0:07914C GetRnd:1:089C88
AchieveSet:2:08DA3C PlayerDeadCheck:0:08DD14 EnemyDeadCheck:0:08DD28
EnemyUnitCheckByPID:1:08DD3C EnemyMonkCheck:0:08DDB0 EnemySelfDefenceCheck:0:08DE5C
EnemyTigerCheck:0:08DED4 PlayerEscapeCheck:0:08DF4C PlayerEscapeCount:0:08E07C
ShooterBulletCheck:0:08E1B0 GetDiedPlayerCount:0:08E258 UnitGet:2:08E3B4 UnitSet:3:08E768
ForceGetFirst:1:08E844 ForceGetCount:1:08E880 UnitGetByPID:1:08E8AC UnitGetParent:1:08E8E0
UnitGetChild:1:08E930 ForceUnitGetByPID:2:08E980 UnitGetByPos:2:08E9E8 UnitGetHero:0:08EA1C
UnitGetDie:0:08EA64 UnitGetNext:1:08EAAC UnitGetForce:1:08EAF8 UnitGetStatus:1:08EB40
UnitClrStatus:2:08EB84 UnitSetStatus:2:08EBE8 UnitTstStatus:2:08EC44 UnitBreakup:1:08EC8C
UnitPairup:2:08ED74 InstantUnitClassChange:1:08EE50 UnitClassChange:1:08EF10 UnitGetX:1:08F07C
UnitGetY:1:08F0C4 UnitGetDispX:1:08F10C UnitGetDispY:1:08F164 UnitGetMaxHP:1:08F1BC
UnitGetHP:1:08F21C UnitSetHP:2:08F264 UnitSetEXP:2:08F2C4 UnitQueryPID:2:08F324
UnitQueryJID:2:08F398 UnitForcedSally:1:08F410 UnitDontMoveSally:1:08F494
UnitNeverSally:1:08F518 MindGetMe:0:08F59C MindGetTarget:0:08F5BC MindSetMind:1:08F5E0
MindGetMind:0:08F61C UnitGetRace:1:08F62C UnitCanParty:1:08F6B4 PIDisAlive:1:08F6F8
BMSetTurn:1:08F73C BMGetTurn:0:08F74C BMSetPhase:1:08F75C BMGetPhase:0:08F76C
BMSetTanto:4:08F77C BMGetTanto:1:08F7C4 BMSetMoney:1:08F7D8 BMGetMoney:0:08F814
BMSetScore:1:08F820 BMGetScore:0:08F874 BMSetWinTerm:2:08F880 BMSetLoseTerm:2:08F8B8
BMGetValue:1:08F8F0 BMSetValue:2:08F904 BMSetChapter:1:08F91C BMGetChapter:0:08F958
BMAddForgeLevel:1:08F968 EventGetX:0:08F9C0 EventGetY:0:08F9CC UnitTransferToForce:2:08F9DC
UnitSetLeader:2:08FAAC UnitSetBelong:2:08FB28 UnitGetBelongCount:1:08FBBC UnitSetOrigin:2:08FC7C
UnitSetCpAttackSeq:2:08FCC4 UnitSetCpMoveSeq:2:08FD3C UnitSetCpTwiceMoveSeq:2:08FDB4
UnitSetCpHealSeq:2:08FE2C UnitSetCpMTypeID:2:08FEA4 UnitSetCpForceNoMoveFlag:2:08FF1C
UnitSetCpFlag:2:08FF9C UnitTstCpFlag:2:090000 UnitClrCpFlag:2:090060 UnitSearchItem:2:0900C4
UnitAddItem:2:090138 UnitDelItem:2:090198 UnitDelAllItems:1:09020C UnitReplaceItem:3:0902A8
UnitGetWeaponCount:1:090318 UnitGetItemCount:1:090378 UnitQueryEquip:2:0903FC
UnitCanUseIt:2:090458 UnitSetEquip:2:0904B4 UnitGetEquipWepI:1:09054C UnitGetEquipAccI:1:0905AC
UnitSetWeaponAway:1:09060C UnitSetAccAway:1:0906D8 UnitItemSetDrop:2:090764
UnitItemSetSealSteal:2:09081C UnitItemGetValuation:2:090890 UnitItemSetBless:2:0908F8
UnitItemClrAllSubItems:1:0909C0 UnitItemSetEndurance:3:090B1C
UnitItemSendtoCurrentWarehouseAll:1:090BBC UnitItemSendtoCurrentWarehouse:2:090CC0
AddToCurrentWarehouseWhatever:1:090DFC UnitItemSendtoWarehouseAll:2:090EDC
UnitItemSendtoWarehouse:3:090FEC AddToWarehouseWhatever:2:09111C DelItemsFromForce:2:091208
DelItemsFromCurrentWarehouse:1:0912CC UnitGetTeam:1:0913A4 UnitSetTeam:2:0913E8
UnitGetTeamCommander:1:09144C UnitGetTeamCount:1:091538 UnitAddSkill:2:091610
UnitAddSkillWhatever:2:09167C UnitTstSkill:2:091854 UnitClrSkill:2:0918C8
UnitReorderSkill:1:0919B0 ItemGetIndex:1:091A14 MapGetTerrain:2:091A48 MapGetSight:2:091A84
UnitGetMoveCost:2:091AA8 GCST:0:091B40 GetBattleType:0:091B48 SysGetRound:0:091B58
SysGetEventFlag:0:091B80 GameGetRound:0:091B88 PersonGetYellLevel:2:091BAC
PersonSetYellLevel:3:091C5C CpClrNoMoveFlag:1:091DC4 GetLanguage:0:091E10 global:1:092E38
regist:1:092F74 get:1:093084 set:1:09317C clr:1:093254 TalkEventDirect:1:093328
TalkEvent:1:093388 TalkResume:0:0933E8 TalkLeave:1:09340C TalkExist:0:093458
MessSetIntArg:2:0934A0 MessSetStringArg:2:0934C4 MessSetPersonNameArg:2:0934E8
InstantFocus:2:09352C Focus:2:09358C FocusWait:0:09368C FocusHardWait:0:093764
UnitFocus:1:0937E0 DefaultEscapeTalk:0:0938C4 DefaultDieTalk:0:09394C UnitEscape:1:093AB0
AllUnitEscape:0:093B20 UnitResetStatus:1:093C98 UnitResetStatusWholeForce:1:093D50 _gi:2:09408C
_gs:2:09419C MindGetMoney:1:0942A0 DDFlagCheck:1:0942F0 DDFlagOn:1:0942F4 DDFlagOff:1:094318
DDExtraFlagAmlitaOn:0:09433C RectBuild:1:094364 RectLeave:1:0943F0 RectKill:1:094478
RectKillAll:0:0944D4 RectGet:2:0944FC RectSet:3:094584 RectSetCurve:6:094648
RectAdjustBoundary:2:09475C RectSetPos:3:0947DC RectMove:6:094BE4 RectMoveOffset:5:094C80
RectFadeIn:2:094C88 RectFadeOut:2:094D08 RectFadeOutDelete:2:094D88 RectSetDepth:2:094E08
RectGetDepth:1:094EA0 GMapSetCurrentGID:1:094F18 GMapBuild:1:094F80 GMapKill:1:094FF4
GMapPos:2:095064 GMapMove:6:095294 GMapMoveOffset:6:095350 GMapFin:1:0953C4 GMapFout:1:09546C
GMapPointOn:5:095514 GMapPointOff:1:09563C GMapPointOffAll:0:0956E8 IsGMapPointEnable:1:095784
GMapRegionOn:2:09581C GMapRegionOff:1:0958D8 GMapRegionOffAll:0:095984
IsGMapRegionEnable:1:095A20 GMapFlagMarkOn:5:095AB8 GMapFlagMarkOff:1:095B8C
GMapFlagMarkOffAll:0:095C38 IsGMapFlagMarkEnable:1:095CD4 GMapCurveEntry:1:095D6C
GMapCurveDraw:1:095E04 GMapCurveDrawInstant:1:095EB0 GMapCurveReset:1:095F5C
GMapCurveDispOnOff:2:096008 GMapCurveDarkOnOff:2:0960CC GMapCurveDrawWait:0:096218
GMapHazeOn:1:096308 GMapHazeOff:1:0963B4 GMapBGMPlay:0:096460 GMapBGMStop:0:096528
DialogDirect:1:096598 Dialog:1:09661C DialogTutorial:1:0966A0 td:1:096724 tde:0:0967F4
Dialog2Items:2:096808 Dialog3Items:3:0968A8 Dialog3ItemsWithSt:6:096980 Dialog4Items:4:096AA0
DialogGetRes:0:096BB0 FacePreLoad:1:096BB4 FaceCreate:6:096C28 FaceDelete:2:096D8C
FaceDeleteImm:1:096DD0 FaceDeleteImmAll:0:096DF4 FaceSetBright:3:096E18 FaceMove:5:096F70
IsFaceEnable:1:097114 TimeiShow:7:097140 TimeiShowHold:5:0971E4 TimeiShowHoldOff:2:097278
TimeiShowHoldOffAll:1:0972A0 TutShowKari:5:0972C4 Fade:2:097358 isFading:0:09738C
GetFadeType:0:097390 Flash:5:0973B4 FlashWait:0:097480 isFlash:0:0974D8 WipeOut:1:0974DC
WipeIn:1:09750C WipeEnd:0:09753C WipeWait:0:09759C isWipe:0:0975F4 ProcKill:1:0975F8
ProcExists:1:097654 PadSetMask:1:097754 PadResetMask:1:097790 NetuzoInit:0:0977CC
NetuzoSet:3:0978F0 NetuzoSetD:4:09792C NetuzoSkill:1:097964 NetuzoDisableFlatter:0:097998
NetuzoBG:1:0979B0 NetuzoDisableBGM:0:0979E0 NetuzoWeather:1:0979F8 NetuzoWeapon:2:097A2C
NetuzoBattle:3:097A88 AddTT:6:097CD8 ClrTT:3:097D68 GetTT:3:097DF8 GetTTCount:1:097E48
InitializeTT:0:097E5C SetFragile:3:097E88 SetShooter:4:097EEC SetPit:2:097F54 SetRock:4:097F98
SetClimb:2:097FE0 SetLava:5:098024 SetBomber:3:0980A0 JyokyoMapCapture:0:09812C
JyokyoMapShow:0:09817C JyokyoMapPlayerOn:0:0981A4 JyokyoMapEnemyOn:0:0981C8
JyokyoMapHide:0:0981EC JyokyoMapDelete:0:098210 BGMPlay:2:098234 BGMPlayAlways:2:0982C0
BGMPlayVol:3:098340 BGMSetVol:3:0983EC BGMStop:1:0984A4 BGMFadeIn:3:098528 BGMFadeOut:2:0985C8
BGMMute:2:098658 BGMCont:2:0986E8 BGMQuietOn:1:0987D0 BGMQuietOff:1:098818 BGMSilentOn:1:098860
BGMSilentOff:1:0988A8 BGMResume:1:0988F0 SFXPlay:1:098AB8 SFXPlay3D:4:098B2C SFXStop:1:098C54
IsSFXPlay:1:098CB4 ENVQuietOn:1:098D08 ENVQuietOff:1:098D50 ENVSilentOn:1:098D98
ENVSilentOff:1:098DFC ENVNoisyOn:1:098E44 ENVNoisyOff:1:098E8C ENVPlay:2:098ED4
ENVPlay3D:5:098F60 ENVSetVol:3:0990A4 ENVStop:2:09916C VOICEPlay:1:0991FC VOICEStop:1:09925C
VOICEAllStop:0:0992BC IsVOICEPlay:1:0992FC MapEnvPause:1:099350 MapEnvResume:1:099398
GetRank:0:0993E0 Easy:0:09940C Normal:0:099444 Hard:0:099478 Maniac:0:0994B0 MStoF:1:0994E8
MoviePlay:1:09957C ChapterMoviePlay:1:0996D8 UnitsPush:0:099774 UnitsPush_Uninitialize:0:099808
UnitsPop:0:099898 UnitsPopWithoutMap:0:09991C AllPush:0:09999C AllPop:0:099A90
UnitDispReload:0:099B24 UnitsInitialize:0:099B50 Check:0:099B90 CheckAttackable:1:099BA0
Join:2:099BE4 DispPreLoadWholeForce:1:099C5C DispLoadWholeForce:1:099CAC
DispFreeWholeForce:1:099CFC SelectSally:0:099D4C SelectSallyEx:1:099D80 SelectAuxiliary:1:099DC8
SelectAuxiliaryRank:1:099E48 SaveMenu:0:099EEC DivideForce:0:099F20 _intr:0:099F54
intplGetValue:5:099FB4 CompleteSubChapter:1:09A030 SallyGetSurplus:0:09A110
SallySetByPos:2:09A120 SallySetByGroup:1:09A15C SallySetByGroupRank:1:09A18C
SallyAddByPos:2:09A1E8 SallyAddByGroup:1:09A224 SallyAddByGroupRank:1:09A254 report:1:09A2B0
WaitPressAnyKey:0:09A35C MSEC2FRAME:1:09A39C FRAME2MSEC:1:09A3D8 BeginFinale:0:09A414
EndFinale:0:09A45C IsE3Version:0:09A4A4 IsPrivateViewVersion:0:09A4AC IsShowVersion:0:09A4B4
IsFinalVersion:0:09A4BC IsJPVersion:0:09A4C4 IsNOAVersion:0:09A4CC IsNOEVersion:0:09A4D4
IsInheritFE8Data:0:09A4DC SetAvailableGrandOpening:0:09A524 IsExtraTutoIn:0:09A554
CreateVMCThread:1:09A5F0 CreateVMCThread1:2:09A67C CreateVMCThread2:3:09A720
CreateVMCThread3:4:09A7DC CreateVMCThread4:5:09A890 KillVMCThread:1:09A954 GetButton:1:09A9EC
GetRepeat:1:09AA1C GetPress:1:09AA4C GetRelease:1:09AA7C Warning:1:09AAAC SetConfig:2:09AAB4
GetConfig:1:09AB0C GetNumDiedPlayers:0:09AB50 GetNumDiedEnemies:0:09AB60
GetNumDiedThirds:0:09AB70 GetNumDiedBrothers:0:09AB80 GetTime:0:09AB90 GetFrame:0:09ABDC
RepairAllWeaponsWholeForce:1:09ABE0 TstConversationFlag:1:09AC94
FE8UnitCheckExistsByPID:1:09ACC8 AddKizna:3:09AD3C SetPreSallyFlag:1:09ADD8
DebugDisplayCtrl:2:09AE4C Epilogue:0:09C5C4 StaffRoll:0:09C5F8 FinEffect:0:09C62C
WarRecord:0:09C674 UnitRanking:0:09C6A8 ScriptMovieStart:0:09CA68 ScriptMovieReference:1:09CAF4
ScriptMoviePlay:1:09CC50 ScriptMoviePreLoad:1:09CD1C ScriptMovieWait:0:09CD9C
ScriptMovieEnd:0:09CDF8 SetTalkTick:1:09CE68 Comeback:0:09E080 DisableSkip:0:09E2A0
EnableSkip:0:09E2B4 SuspendEvent:0:09E704 ResumeEvent:0:09E7CC TutorialCall:1:0A2388
QueryLesson:1:0A2430 _seqini:0:0A24F8 _bmsini:0:0A25A0 GameBind:0:0A25CC GameUnbind:0:0A2684
_pa:1:0A286C BeginMapHoldCursor:0:0A29C4 EndMapHoldCursor:0:0A29F4 TutShow:1:0A2A20 _tt:1:0A2A48
_tr:0:0A2AA8 TutMapLoad:1:0A2ACC TutMapFree:0:0A2B08 ArcLoad:1:0A2B50 ArcFree:1:0A2B74
CmbMessLoad:2:0A2B98 CmbMessUnload:1:0A2C44 taikitk:0:0A2CDC turntk:0:0A2D0C turnatk:0:0A2D3C
TutorialUnlock:1:0A2D6C TutorialLock:1:0A2E04 TutorialLearn:1:0A2E9C TutorialForget:1:0A2F34
TutorialSallyCreate:0:0A2FCC TutorialSallyDelete:0:0A3000 TutorialBaseCreate:0:0A3024
TutorialBaseDelete:0:0A3058 TutorialInitialize:0:0A3274 Config_Tutorial:0:0A32B4
Config_TutSet_ctrlInfo:1:0A3344 Config_TutSet_unitInfo:1:0A33A0 Config_TutSet_terInfo:1:0A33F0
Config_TutSet_otheridoshowing:1:0A3448 Config_TutSet_XinfoPage:1:0A34A0
Config_TutGet_sfx_vol:0:0A34D8 Config_TutSet_sfx_vol:1:0A3504 GetTutorial:0:0A3550
SetTutorial:1:0A3584 Tut3SArrowUAnim:3:0A41AC Tut3SArrowDAnim:3:0A4224 Tut3SArrowABAnim:3:0A4298
Tut3SArrowBCAnim:3:0A4318 Tut3SArrowCAAnim:3:0A439C CmLoadScript:1:0C3840 CmFreeScript:0:0C3974
CmSleepScript:1:0C3A48 CmWakeupScripts:0:0C3B1C FadeIsBlackHolding:0:0C7FA0
FadeIsWhiteHolding:0:0C7FC4 SetWhiteBackdrop:0:0C916C RemoveBackdrop:0:0C919C
RectPreLoad:1:0D433C SetEventBattle:1:0D7DB0 UnitMoveDelete:1:0D7F14 IsUnitMove:1:0D7F98
UnitFocusOff:0:0D805C UnitFocusOn:0:0D8124 UnitWalkPush:1:0D81EC UnitWalkHold:1:0D82D0
UnitWalkReverse:1:0D83B4 UnitWalkAnim:1:0D8498 UnitWalkTime:1:0D85C8 UnitWalkSpeed:1:0D86C8
UnitWalkGround:1:0D87C8 UnitWalkManual:1:0D88AC UnitRotateAnim:1:0D8990 UnitFadeIn:0:0D8A68
UnitFadeOut:0:0D8B34 UnitFadeOff:0:0D8C00 SetEventCameraPrec:1:0D8CC8 GetMapHeightBase:2:0D8D8C
GetMapHeight:2:0D8E00 UnitWalkDir:1:0D8E74 UnitWaitAnim:1:0D8F88 SetGrid:1:0D90B8
SetCircle:1:0D918C SetUnitIcon:1:0D9258 SetUnitGauge:1:0D9324 SetUnitMask:1:0D93F0
SetUnitAlways:1:0D94BC _dispos:2:0D9588 _idispos:2:0D9610 DisposGetRankGroup:1:0D9638
DisposAuxiliary:1:0D967C DisposGetGroupCenter:3:0D9764 IsDispos:0:0D97C0 DisposGetCount:0:0D9800
DisposGetUnit:1:0D9834 UnitMoveDir:2:0D987C UnitMovePos:3:0D9AC8 UnitMoveRoute:2:0D9CE8
UnitSetPos:3:0D9EB8 UnitRotate:3:0D9FA8 UnitPosRotate:4:0DA1FC UnitAngleRotate:3:0DA430
UnitSetScale:2:0DA61C UnitSetColor:5:0DA74C UnitSetAnim:2:0DA898 UnitSetAID:2:0DA9F4
UnitSetOffset:4:0DAB6C UnitAnimPreLoad:2:0DACF8 UnitAnimEx:5:0DADA0 UnitAnim:2:0DAF74
UnitHide:1:0DAF84 UnitShow:1:0DB0B0 UnitDead:1:0DB138 UnitRunAway:1:0DB214 UnitWarpOut:1:0DB2FC
UnitTackle:3:0DB3E4 UnitPush:3:0DB56C InstantUnitTransform:2:0DB6E4 UnitTransform:2:0DB7B0
UnitGetDir:1:0DB98C UnitGetStrike:1:0DBA10 UnitGetFumble:1:0DBAB4 UnitReplace:2:0DBB58
UnitSetScaleAll:1:0DBD48 MapLoad:1:0DBE1C MapFree:0:0DBE58 DisposLoad:1:0DBE98
DisposFree:1:0DBEBC MapReload:0:0DBEE0 SetOutLink:1:0DBF74 SetSight:1:0DC0A8 SetFog:6:0DC114
SetWeather:1:0DC1B0 GetWeather:0:0DC204 SetAmbient:4:0DC20C SetDiffuse:4:0DC2CC
SetWeatherAlpha:3:0DC38C SetLisner:3:0DC424 SetMapCamera:3:0DC5A8 InstantSetMapCamera:3:0DC680
CopyMapCamera:0:0DC770 PastMapCamera:0:0DC824 InstantPastMapCamera:0:0DC9D4
SetMapCameraWeight:1:0DCAD4 CreateEventCamera:0:0DCB34 SetEventCameraAt:4:0DCB5C
SetEventCameraEye:4:0DCC38 SetEventCameraRot:4:0DCD14 SetEventCameraUnit:2:0DCDF0
SetEventCameraCurve:2:0DCEAC StartEventCamera:1:0DCEEC ClearEventCamera:0:0DCF10
DeleteEventCamera:0:0DCF34 IsEventCamera:0:0DCF58 FileCameraPlay:4:0DD0F0 IsFileCamera:0:0DD1B8
SetCameraDisp:1:0DD20C BuildInstAnim:3:0DD214 BuildInstShow:2:0DD3E4 BuildInstHide:2:0DD4A0
BuildInstReject:3:0DD560 BuildInstRejectByName:2:0DD680 InstantDoorOpen:2:0DD7C4
InstantDoorClose:2:0DD940 DoorOpen:2:0DDAB8 DoorClose:2:0DDC7C TBoxOpen:2:0DDDAC
InstantRoofOpen:2:0DDE60 InstantRoofClose:2:0DDF54 RoofOpen:2:0DE044 RoofClose:2:0DE1B8
BuildInstTorch:4:0DE324 BuildInstExtinction:3:0DE3C0 BuildInstGetX:2:0DE45C
BuildInstGetY:2:0DE4C8 SetMapLamp:1:0DE534 VisitIn:3:0DE5FC VisitOut:3:0DE604
SetRoofEnable:3:0DE6D8 BuildDestruction:2:0DE794 SetTerrName:3:0DE854 SetTerrData:3:0DE8EC
ShowMapCursor:2:0DE9A8 HideMapCursor:0:0DE9FC EffectPlay:1:0DEAE8 EffectPlay2D:1:0DEB88
EffectPos:3:0DEC18 EffectXYZ:4:0DED44 EffectRotate:4:0DEE80 EffectUnit:4:0DF0B8
EffectCamera:2:0DF2C8 EffectLoop:2:0DF368 EffectCycle:2:0DF438 EffectScale:2:0DF4DC
EffectSpeed:2:0DF56C EffectDepth:2:0DF5DC EffectPriority:2:0DF64C EffectDelete:1:0DF6C8
EffectFadeOut:2:0DF738 EffectPreLoad:1:0DF7D4 IsEffect:1:0DF80C EventQuake:3:0DF894
EventQuakeStop:0:0DF940 SetPullCursor:1:0DF964 SetCamSuspend:1:0DF984 SetCamHold:1:0DF9A4
SetOnBtFocus:1:0DF9C4 UnitSetFixed:2:0DF9E4 UnitLooksChange:2:0DFA60 UnitSetHand:2:0DFB28
HidePrim2D:1:0DFC78 GetFukiPosX:0:0DFCC4 GetFukiPosY:0:0DFD00 ShowPoint:5:0E0284
HidePoint:2:0E0394 MapHide:1:0E0468 MapShow:1:0E052C UnitRescue:2:0E0604 UnitDropOff:2:0E07B0
UnitChildSend:2:0E0A40 PostEffectStart:4:0E0C14 PostEffectColor:4:0E0CDC PostEffectStop:2:0E0D78
GetFragileHP:2:0E0E10 GetFragileMaxHP:2:0E0E60 SetTimeScale:1:0E0EB0 ShowHealWindow:2:0E0F9C
MapUpdate:0:113370 DumpUnit:0:12D588 EventArrowAppend:5:180FC4 EventArrowStart:2:181104
EventArrowFadeOut:1:181168 EventArrowDelete:0:181190 EventArrowFocus:2:1811B4
EventArrowColor:5:1811F4 EventArrowWait:0:1812B8 TerInfoFadeIn:0:1AD434 TerInfoFadeOut:0:1AD46C
TerInfoShow:0:1AD4A4 TerInfoHide:0:1AD4DC TutorialResume:0:1B3A30 TFXTstSignal:0:1D0AE0
_pldone:0:23F87C IsConversationRoom:0:27D6C4 strcmp:2:291188
"""

BUILTINS = {}  # name -> (argc, native function address)
for _tok in _BUILTIN_TABLE.split():
    _n, _a, _f = _tok.rsplit(":", 2)
    BUILTINS[_n] = (int(_a), 0x80000000 | int(_f, 16))

# ---------------------------------------------------------------- triggers
# kind -> (name, param types: 'i' int, 's' string-table offset)
# Confidence: names derived from the condition functions in 8009C000/800A0000
# and from the parameter contents; see the doc for details.
KINDS = {
    0: ("function", ""),
    1: ("flag_set", "s"),               # fires when flag is set (gf_complete)
    2: ("flag_set2", "s"),              # same test as 1, other hook (unseen)
    3: ("turn", "iii"),                 # turn_min, turn_max (0=any), phase (-1=any)
    4: ("area", "iiiiis"),              # x0,y0,x1,y1, army(-1 any), flag/cond
    5: ("location", "iiis"),            # x, y, command/type, flag/cond (visit, chest, door)
    6: ("turn_end", "iii"),             # same params as turn, other hook
    7: ("after_action", ""),            # state check run after actions (win checks)
    8: ("talk", "ssis"),                # pid_a, pid_b, ?, flag/cond
    9: ("battle_talk", "ssis"),         # pid_a, pid_b, ?, flag/cond (boss quotes)
    10: ("unit_retreat", "s"),          # pid (startup.cmb: player units)
    11: ("unit_defeat", "s"),           # pid (chapter scripts)
    12: ("clear_bonus", "s"),           # sets the BEXP bonus rules (Achieve_*)
    13: ("kind13", ""),
    14: ("base_conversation", "ss"),    # title, flag/function
    15: ("unit_action", ""),            # per acting unit (MindGetMe), tutorials
    17: ("kind17", "ssss"),
    18: ("kind18", "sssss"),
    19: ("kind19", "ssss"),
    20: ("epilogue", "ss"),             # pid, condition function (CFINAL)
}

# ---------------------------------------------------------------- opcodes
# opcode -> (mnemonic, operand format)
#   b: s8   B: u8   h: s16   H: u16   I: u32   S1/S2/S4: string offset
#   F: function index (u8, or 15-bit if high bit set)   N: name16 + argc8
OPS = {0x00: ("nop", "")}
for _base, _kind in ((0x01, "L"), (0x0D, "G")):
    for _i, _m in enumerate(("ld", "ldidx", "ldptr", "lea", "leaidx", "leaptr")):
        OPS[_base + 2 * _i] = ("%s%s" % (_m, _kind), "B")
        OPS[_base + 2 * _i + 1] = ("%s%s" % (_m, _kind), "H")
OPS.update({
    0x19: ("push", "b"), 0x1A: ("push", "H"), 0x1B: ("push", "I"),
    0x1C: ("pushs", "S1"), 0x1D: ("pushs", "S2"), 0x1E: ("pushs", "S4"),
    0x1F: ("deref", ""), 0x20: ("pop", ""), 0x21: ("assign", ""),
    0x22: ("add", ""), 0x23: ("sub", ""), 0x24: ("mul", ""), 0x25: ("div", ""),
    0x26: ("mod", ""), 0x27: ("neg", ""), 0x28: ("bnot", ""), 0x29: ("lnot", ""),
    0x2A: ("or", ""), 0x2B: ("and", ""), 0x2C: ("xor", ""), 0x2D: ("shl", ""),
    0x2E: ("shr", ""), 0x2F: ("eq", ""), 0x30: ("ne", ""), 0x31: ("lt", ""),
    0x32: ("le", ""), 0x33: ("gt", ""), 0x34: ("ge", ""), 0x35: ("streq", ""),
    0x36: ("strne", ""), 0x37: ("call", "F"), 0x38: ("callname", "N"),
    0x39: ("retv", ""), 0x3A: ("jmp", "h"), 0x3B: ("jnz", "h"),
    0x3C: ("orjmp", "h"), 0x3D: ("jz", "h"), 0x3E: ("andjmp", "h"),
    0x3F: ("yield", ""), 0x40: ("nop4", "I"), 0x41: ("popn", "b"),
    0x42: ("inc", ""), 0x43: ("dec", ""), 0x44: ("dup", ""),
    0x45: ("ret0", ""), 0x46: ("ret1", ""), 0x47: ("store", ""),
})
BINOPS = {"add": "+", "sub": "-", "mul": "*", "div": "/", "mod": "%",
          "or": "|", "and": "&", "xor": "^", "shl": "<<", "shr": ">>",
          "eq": "==", "ne": "!=", "lt": "<", "le": "<=", "gt": ">", "ge": ">=",
          "streq": "==", "strne": "!="}


def _cstr(buf, off):
    end = buf.index(b"\0", off)
    return buf[off:end].decode("shift_jis", "replace")


class Function:
    def __init__(self, script, index, hdr):
        d = script.raw
        self.header = hdr
        self.index = index
        name_off, self.code = struct.unpack_from("<II", d, hdr)
        self.name = _cstr(d, name_off) if name_off else None
        self.kind = d[hdr + 0x0C]
        self.argc = struct.unpack_from("b", d, hdr + 0x0D)[0]
        nparam = struct.unpack_from("b", d, hdr + 0x0E)[0]
        self.declared_index, self.frame = struct.unpack_from("<HH", d, hdr + 0x10)
        self.params_raw = list(struct.unpack_from("<%dH" % nparam, d, hdr + 0x14))
        self.end = None  # filled by Script

    @property
    def label(self):
        return self.name or "func_%d" % self.index

    def params(self, script):
        fmt = KINDS.get(self.kind, ("", ""))[1]
        out = []
        for i, v in enumerate(self.params_raw):
            t = fmt[i] if i < len(fmt) else "i"
            if t == "s" and v < script.strtab_size:
                out.append(script.string(v))
            else:
                out.append(struct.unpack("h", struct.pack("H", v))[0])
        return out

    def to_dict(self, script):
        kname = KINDS.get(self.kind, ("kind%d" % self.kind, ""))[0]
        return {"index": self.index, "name": self.name, "header": self.header,
                "code": self.code, "end": self.end, "kind": self.kind,
                "kind_name": kname, "argc": self.argc, "frame": self.frame,
                "params": self.params(script)}


class Script:
    def __init__(self, raw: bytes):
        if raw[:4] != b"cmb\0":
            raise ValueError("not a cmb script")
        self.raw = raw
        self.filename = _cstr(raw, 4)
        (self.date, _, _, self.static_count, self.strtab,
         self.functab) = struct.unpack_from("<IIHHII", raw, 0x18)
        self.strtab_size = self.functab - self.strtab
        self.functions = []
        i = 0
        while True:
            hdr = struct.unpack_from("<I", raw, self.functab + 4 * i)[0]
            if hdr == 0:
                break
            self.functions.append(Function(self, i, hdr))
            i += 1
        bounds = sorted([f.header for f in self.functions] + [self.functab])
        for f in self.functions:
            f.end = min(b for b in bounds if b > f.code) if any(b > f.code for b in bounds) else len(raw)

    def string(self, off):
        if not 0 <= off < self.strtab_size:
            return "<bad string 0x%x>" % off
        return _cstr(self.raw, self.strtab + off)

    def strings(self):
        """All NUL-terminated strings of the string table: [(offset, text)]."""
        out, o = [], 0
        while o < self.strtab_size:
            e = self.raw.index(b"\0", self.strtab + o) - self.strtab
            if e > o:
                out.append((o, self.string(o)))
            o = e + 1
        return out

    # ------------------------------------------------------------ decoding
    def decode(self, func):
        """Instructions of a function: [(addr, op, mnemonic, operand, size)].

        Code runs up to the next header; the last 1-4 bytes before it are
        uninitialised padding, so decoding stops at the first return that
        no later jump target lies beyond."""
        ins = list(self._decode_raw(func))
        reach = 0   # furthest forward jump target seen so far
        for i, (pc, op, mn, arg, size) in enumerate(ins):
            if mn in ("jmp", "jnz", "jz", "orjmp", "andjmp"):
                reach = max(reach, arg)
            if op in (0x39, 0x45, 0x46) and reach <= pc:
                return ins[:i + 1]
        return ins

    def _decode_raw(self, func):
        d = self.raw
        pc = func.code
        while pc < func.end:
            op = d[pc]
            mn, fmt = OPS.get(op, ("db", ""))
            if pc + {"": 1, "b": 2, "B": 2, "H": 3, "h": 3, "I": 5, "S1": 2, "S2": 3,
                     "S4": 5, "F": 2, "N": 4}[fmt] > len(d):
                mn, fmt = "db", ""
            p = pc + 1
            arg = None
            if fmt == "b":
                arg = struct.unpack_from("b", d, p)[0]; p += 1
            elif fmt == "B":
                arg = d[p]; p += 1
            elif fmt in ("H", "h"):
                arg = struct.unpack_from(">" + fmt, d, p)[0]; p += 2
            elif fmt == "I":
                arg = struct.unpack_from(">I", d, p)[0]; p += 4
            elif fmt == "S1":
                arg = ("str", struct.unpack_from("b", d, p)[0]); p += 1
            elif fmt == "S2":
                arg = ("str", struct.unpack_from(">H", d, p)[0]); p += 2
            elif fmt == "S4":
                arg = ("str", struct.unpack_from(">I", d, p)[0]); p += 4
            elif fmt == "F":
                v = struct.unpack_from("b", d, p)[0]; p += 1
                if v < 0:
                    v = (v & 0x7F) << 8 | d[p]; p += 1
                arg = v
            elif fmt == "N":
                no, argc = struct.unpack_from(">HB", d, p); p += 3
                arg = (self.string(no), argc)
            if fmt == "h":
                arg = pc + 1 + arg      # jump target (relative to operand)
            yield pc, op, mn, arg, p - pc
            pc = p

    def fmt_operand(self, mn, arg):
        if arg is None:
            return ""
        if isinstance(arg, tuple) and arg[0] == "str":
            return '"%s"' % self.string(arg[1]).replace('"', '\\"')
        if mn == "callname":
            return "%s/%d" % arg
        if mn == "call":
            return self.functions[arg].label if arg < len(self.functions) else "func_%d" % arg
        if mn in ("jmp", "jnz", "jz", "orjmp", "andjmp"):
            return "loc_%04x" % arg
        if isinstance(arg, int) and mn == "push" and abs(arg) > 9:
            return "%d (0x%x)" % (arg, arg)
        return str(arg)

    def disasm(self, func):
        lines = []
        targets = {a for _, _, m, a, _ in self.decode(func)
                   if m in ("jmp", "jnz", "jz", "orjmp", "andjmp")}
        for pc, op, mn, arg, size in self.decode(func):
            if pc in targets:
                lines.append("loc_%04x:" % pc)
            hexb = self.raw[pc:pc + size].hex(" ")
            lines.append("  %04x: %-17s %-9s %s" % (pc, hexb, mn, self.fmt_operand(mn, arg)))
        return lines

    # ------------------------------------------------------------ pseudo-C
    def pseudo(self, func):
        """Best-effort statement recovery from the stack code."""
        ins = list(self.decode(func))
        targets = {}
        for pc, op, mn, a, _ in ins:
            if mn in ("jmp", "jnz", "jz", "orjmp", "andjmp"):
                targets.setdefault(a, []).append((pc, mn))
        out, st, pend, ntmp = [], [], {}, [0]
        # The symbolic stack is kept across labels and jumps (switch
        # statements keep the selector on the stack: dup/push/eq/jnz chains).

        def var(mn, n):
            return ("a%d" % n if n < func.argc else "v%d" % n) if mn.endswith("L") \
                else "G%d" % n

        def flush():
            while st:
                out.append("    push %s;" % st.pop(0))

        for pc, op, mn, a, _ in ins:
            if pc in targets:
                for (cpc, cm) in pend.pop(pc, []):
                    if len(st) >= 2:
                        r = st.pop(); l = st.pop()
                        st.append("(%s %s %s)" % (l, "||" if cm == "orjmp" else "&&", r))
                if any(m not in ("orjmp", "andjmp") for _, m in targets[pc]):
                    out.append("  loc_%04x:" % pc)
            try:
                if mn in ("ldL", "ldG"):
                    st.append(var(mn, a))
                elif mn in ("ldidxL", "ldidxG"):
                    st.append("%s[%s]" % (var(mn, a), st.pop()))
                elif mn in ("ldptrL", "ldptrG"):
                    st.append("%s->[%s]" % (var(mn, a), st.pop()))
                elif mn in ("leaL", "leaG"):
                    st.append("&" + var(mn, a))
                elif mn in ("leaidxL", "leaidxG"):
                    st.append("&%s[%s]" % (var(mn, a), st.pop()))
                elif mn in ("leaptrL", "leaptrG"):
                    st.append("&%s->[%s]" % (var(mn, a), st.pop()))
                elif mn == "push":
                    st.append(str(a) if abs(a) < 10 else "0x%x" % a if a > 0 else str(a))
                elif mn == "pushs":
                    st.append(self.fmt_operand(mn, a))
                elif mn == "deref":
                    st.append("*" + st[-1])
                elif mn == "dup":
                    if not st[-1].replace("_", "").isalnum():
                        tmp = "t%d" % ntmp[0]
                        ntmp[0] += 1
                        out.append("    %s = %s;" % (tmp, st.pop()))
                        st.append(tmp)
                    st.append(st[-1])
                elif mn in BINOPS:
                    r = st.pop(); l = st.pop()
                    st.append("(%s %s %s)" % (l, BINOPS[mn], r))
                elif mn in ("neg", "bnot", "lnot"):
                    st.append({"neg": "-", "bnot": "~", "lnot": "!"}[mn] + st.pop())
                elif mn in ("call", "callname"):
                    if mn == "call":
                        name = self.fmt_operand(mn, a)
                        argc = self.functions[a].argc if a < len(self.functions) else 0
                    else:
                        name, argc = a
                    args = st[len(st) - argc:] if argc else []
                    del st[len(st) - argc:]
                    st.append("%s(%s)" % (name, ", ".join(args)))
                elif mn == "pop":
                    e = st.pop()
                    if not e.replace("_", "").isalnum():   # drop bare temps
                        out.append("    %s;" % e)
                elif mn == "popn":
                    # values pushed and dropped unused; in practice the
                    # arguments of compiled-out debug printf calls
                    if a > len(st):
                        raise IndexError
                    args = st[len(st) - a:]
                    del st[len(st) - a:]
                    out.append("    discard(%s);" % ", ".join(args))
                elif mn in ("store", "assign"):
                    v = st.pop(); ad = st.pop()
                    lhs = ad[1:] if ad.startswith("&") else "*" + ad
                    if mn == "store":
                        out.append("    %s = %s;" % (lhs, v))
                    else:
                        st.append("(%s = %s)" % (lhs, v))
                elif mn in ("inc", "dec"):
                    ad = st.pop()
                    lhs = ad[1:] if ad.startswith("&") else "*" + ad
                    out.append("    %s%s;" % (lhs, "++" if mn == "inc" else "--"))
                elif mn in ("jz", "jnz"):
                    c = st.pop()
                    out.append("    if (%s%s) goto loc_%04x;" % ("!" if mn == "jz" else "", c, a))
                elif mn == "jmp":
                    out.append("    goto loc_%04x;" % a)
                elif mn in ("orjmp", "andjmp"):
                    pend.setdefault(a, []).append((pc, mn))
                elif mn == "retv":
                    out.append("    return %s;" % st.pop())
                elif mn in ("ret0", "ret1"):
                    out.append("    return %s;" % mn[-1])
                elif mn == "yield":
                    out.append("    yield;")
                elif mn in ("nop", "nop4"):
                    pass
                else:
                    out.append("    /* %s %s */" % (mn, a))
            except IndexError:
                out.append("    /* stack underflow at %04x (%s) */" % (pc, mn))
        flush()
        return out

    def to_dict(self):
        return {"filename": self.filename, "date": "%08x" % self.date,
                "static_vars": self.static_count,
                "functions": [f.to_dict(self) for f in self.functions]}


def open_file(path):
    with open(path, "rb") as f:
        raw = f.read()
    if raw[:1] == b"\x10":
        sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
        from lz10 import decompress
        raw = decompress(raw)
    return Script(raw)


def listing(s, mode="pseudo"):
    out = ["// %s  date %08x  static vars %d  functions %d" %
           (s.filename, s.date, s.static_count, len(s.functions))]
    for f in s.functions:
        kname = KINDS.get(f.kind, ("kind%d" % f.kind, ""))[0]
        args = ", ".join("a%d" % i for i in range(f.argc))
        head = "%s(%s)" % (f.label, args)
        if f.kind:
            head = "event[%s %s] %s" % (kname, ", ".join(
                '"%s"' % p if isinstance(p, str) else str(p) for p in f.params(s)), head)
        out.append("")
        out.append("// #%d  header 0x%x  code 0x%x-0x%x  frame %d" %
                   (f.index, f.header, f.code, f.end, f.frame))
        out.append(head + " {")
        out.extend(s.disasm(f) if mode == "asm" else s.pseudo(f))
        out.append("}")
    return "\n".join(out)


def main(argv):
    import argparse
    import json
    ap = argparse.ArgumentParser(description="FE10 .cmb event script disassembler")
    ap.add_argument("file")
    ap.add_argument("--asm", action="store_true", help="raw instruction listing")
    ap.add_argument("--strings", action="store_true", help="dump string table")
    ap.add_argument("--json", action="store_true", help="header + function table as JSON")
    a = ap.parse_args(argv)
    s = open_file(a.file)
    if a.json:
        print(json.dumps(s.to_dict(), ensure_ascii=False, indent=1))
    elif a.strings:
        for o, t in s.strings():
            print("%04x  %s" % (o, t))
    else:
        print(listing(s, "asm" if a.asm else "pseudo"))


if __name__ == "__main__":
    main(sys.argv[1:])
