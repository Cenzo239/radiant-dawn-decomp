// FE10's HBM (Jul 9 2007) sound engine: plays the Home Menu MIDI sequences with
// the SDK's SEQ/SYN/MIX libraries on its own thread (0x80347FBC-0x80348A28).
// No reference source exists; reconstructed from the disassembly, names are placeholders.
#include <revolution/AI.h>
#include <revolution/ARC.h>
#include <revolution/AX.h>
#include <revolution/OS.h>

extern "C" {
double log10(double x);
typedef struct SEQSEQUENCE {
    u32 data[0x3D50 / 4];
} SEQSEQUENCE;

void SEQInit(void);
void SEQRunAudioFrame(void);
void SEQAddSequence(SEQSEQUENCE* sequence, u8* midiStream, void* wt, u32 aramBase, u32 zeroBase,
                    u32 priorityVoiceAlloc, u32 priorityNoteOn, u32 priorityNoteRelease);
void SEQRemoveSequence(SEQSEQUENCE* sequence);
void SEQSetState(SEQSEQUENCE* sequence, u32 state);
u32 SEQGetState(SEQSEQUENCE* sequence);
void SEQSetVolume(SEQSEQUENCE* sequence, s32 dB);
void SYNInit(void);
void SYNRunAudioFrame(void);
void MIXInit(void);
void MIXUpdateSettings(void);
BOOL AICheckInit(void);
}

void HBMSoundCreate(void* arcBuf, void* mem, u32 size);
void HBMSoundUpdate();
void HBMSoundPlay(int id);
void HBMSoundStopAll();
void HBMSoundSetVolume(f32 gain);

struct HBMSePlayer {
    SEQSEQUENCE seq;   // at 0x0
    u8 used;           // at 0x3D50
    HBMSePlayer* next; // at 0x3D54
    HBMSePlayer* prev; // at 0x3D58
    int id;            // at 0x3D5C
};

struct HBMSeList {
    HBMSePlayer* head; // at 0x0
    HBMSePlayer* tail; // at 0x4
};

struct HBMSoundWork {
    HBMSePlayer players[4];    // at 0x0
    HBMSePlayer sePlayers[3];  // at 0xF580
    HBMSeList list;            // at 0x1ADA0
    HBMSeList seList;          // at 0x1ADA8
    u32 unk1ADB0;              // at 0x1ADB0
    AXOutCallback oldCallback; // at 0x1ADB4
    ARCHandle arc;             // at 0x1ADB8
    OSThread thread;           // at 0x1ADD8
    OSMessageQueue queue;      // at 0x1B0F0
    OSMessage msgs[4];         // at 0x1B110
    u8 stack[0x2000];          // at 0x1B120
    void* wt;                  // at 0x1D120
    void* pcm;                 // at 0x1D124
};

static const char* sSeFileNames[] = {
    "midi\\00_home_button.mid",
    "midi\\01_return_app.mid",
    "midi\\02_goto_menu.mid",
    "midi\\03_reset_app.mid",
    "midi\\04_focus.mid",
    "midi\\05_select.mid",
    "midi\\06_cancel.mid",
    "midi\\07_open_controller.mid",
    "midi\\08_close_controller.mid",
    "midi\\09_volume_plus.mid",
    "midi\\10_volume_minus.mid",
    "midi\\11_volume_plus_limit.mid",
    "midi\\12_volume_minus_limit.mid",
    "midi\\13_nothing_done.mid",
    "midi\\14_vibe_on.mid",
    "midi\\15_vibe_off.mid",
    "midi\\16_start_connect_window.mid",
    "midi\\17_connected1.mid",
    "midi\\18_connected2.mid",
    "midi\\19_connected3.mid",
    "midi\\20_connected4.mid",
    "midi\\21_end_connect_window.mid",
    "midi\\22_manual_open.mid",
    "midi\\23_manual_focus.mid",
    "midi\\24_manual_select.mid",
    "midi\\25_manual_scroll.mid",
    "midi\\26_manual_cancel.mid",
    "midi\\27_manual_return_app.mid",
};

static HBMSoundWork* spWork;

static inline HBMSeList* GetList(int id) {
    switch (id) {
    case 4:
    case 23:
    case 25:
        return &spWork->seList;
    default:
        return &spWork->list;
    }
}

static inline void FreePlayer(HBMSePlayer* p) {
    HBMSeList* list = GetList(p->id);

    SEQSetState(&p->seq, 0);
    SEQRemoveSequence(&p->seq);
    p->used = FALSE;

    if (p->prev == NULL) {
        list->head = p->next;
    } else {
        p->prev->next = p->next;
    }

    if (p->next == NULL) {
        list->tail = p->prev;
    } else {
        p->next->prev = p->prev;
    }

    p->next = NULL;
    p->prev = NULL;
}

static HBMSePlayer* AllocPlayer(int id) {
    HBMSePlayer* players;
    int num;
    switch (id) {
    case 4:
    case 23:
    case 25:
        players = spWork->sePlayers;
        num = 3;
        break;
    default:
        players = spWork->players;
        num = 4;
        break;
    }

    HBMSePlayer* p = NULL;

    for (int i = 0; i < num; i++) {
        if (!players[i].used) {
            p = &players[i];
            p->used = TRUE;
            break;
        }
    }

    if (p == NULL) {
        p = GetList(id)->head;
        FreePlayer(p);
        p->used = TRUE;
    }

    return p;
}

static void AxCallback(void) {
    if (spWork != NULL) {
        OSSendMessage(&spWork->queue, (OSMessage)1, 0);

        if (spWork->oldCallback != NULL) {
            spWork->oldCallback();
        }
    }
}

static inline void UpdateList(HBMSePlayer* p) {
    HBMSePlayer* next;

    for (; p != NULL; p = next) {
        next = p->next;
        if (p->used && SEQGetState(&p->seq) == 0) {
            FreePlayer(p);
        }
    }
}

static inline void UpdateList(HBMSeList* list) {
    HBMSePlayer* p;
    HBMSePlayer* next;
    for (p = list->head; p != NULL; p = next) {
        next = p->next;
        if (p->used && SEQGetState(&p->seq) == 0) {
            FreePlayer(p);
        }
    }
}

static void* SoundThread(void* /* arg */) {
    OSMessage msg = NULL;

    while (TRUE) {
        OSReceiveMessage(&spWork->queue, &msg, OS_MSG_BLOCKING);

        if ((u32)msg == 1) {
            SEQRunAudioFrame();
            SYNRunAudioFrame();
            MIXUpdateSettings();

            if (spWork != NULL) {
                UpdateList(&spWork->list);
                UpdateList(&spWork->seList);

            }
        } else if ((u32)msg == 8) {
            break;
        }
    }

    return NULL;
}

void HBMSoundPlay(int id) {
    ARCFileInfo info;
    void* data;
    HBMSePlayer* p;
    HBMSeList* list;

    if (ARCOpen(&spWork->arc, sSeFileNames[id], &info)) {
        data = ARCGetStartAddrInMem(&info);
    } else {
        data = NULL;
    }

    if (data != NULL) {
        p = AllocPlayer(id);
        SEQAddSequence(&p->seq, (u8*)data, spWork->wt, (u32)spWork->pcm, 0, 16, 15, 1);
        SEQSetState(&p->seq, 1);
        p->id = id;

        list = GetList(id);
        if (list->tail == NULL) {
            list->head = p;
            list->tail = p;
            p->next = NULL;
            p->prev = NULL;
        } else {
            list->tail->next = p;
            p->prev = list->tail;
            p->next = NULL;
            list->tail = p;
        }
    }
}

static const char sWtName[] = "wt\\HomeButtonSe.wt";
static const char sPcmName[] = "wt\\HomeButtonSe.pcm";

void HBMSoundCreate(void* arcBuf, void* mem, u32 size) {
    HBMSoundWork* work = (HBMSoundWork*)mem;
    ARCFileInfo wtInfo;
    ARCFileInfo pcmInfo;
    if (size < sizeof(HBMSoundWork)) {
        return;
    }

    if (!AICheckInit()) {
        AIInit(NULL);
        AXInit();
    }

    MIXInit();
    SYNInit();
    SEQInit();

    for (int i = 0; i < 4; i++) {
        work->players[i].used = FALSE;
        work->players[i].next = NULL;
        work->players[i].prev = NULL;
    }

    for (int i = 0; i < 3; i++) {
        work->sePlayers[i].used = FALSE;
        work->sePlayers[i].next = NULL;
        work->sePlayers[i].prev = NULL;
    }

    work->wt = NULL;
    work->pcm = NULL;
    work->list.head = NULL;
    work->list.tail = NULL;
    work->seList.head = NULL;
    work->seList.tail = NULL;

    if (!ARCInitHandle(arcBuf, &work->arc)) {
        return;
    }

    if (!ARCOpen(&work->arc, sWtName, &wtInfo)) {
        return;
    }
    work->wt = ARCGetStartAddrInMem(&wtInfo);

    if (!ARCOpen(&work->arc, sPcmName, &pcmInfo)) {
        return;
    }
    work->pcm = ARCGetStartAddrInMem(&pcmInfo);

    OSInitMessageQueue(&work->queue, work->msgs, 4);

    if (!OSCreateThread(&work->thread, SoundThread, NULL, (void*)((u32)work->stack + 0x2000), sizeof(work->stack), 4, 0)) {
        return;
    }

    spWork = work;
    OSResumeThread(&work->thread);
    work->oldCallback = AXRegisterCallback(AxCallback);
}

void HBMSoundUpdate() {}

void HBMSoundStopAll() {

    if (spWork == NULL) {
        return;
    }

    for (int i = 0; i < 4; i++) {
        HBMSePlayer* p = &spWork->players[i];
        if (p->used) {
            FreePlayer(p);
        }
    }

    for (int i = 0; i < 3; i++) {
        HBMSePlayer* p = &spWork->sePlayers[i];
        if (p->used) {
            FreePlayer(p);
        }
    }
}

void HBMSoundSetVolume(f32 gain) {

    if (spWork == NULL) {
        return;
    }

    int vol = 10.0f * (20.0f * (f32)log10(gain));

    if (vol > 60) {
        vol = 60;
    }
    if (vol < -904) {
        vol = -904;
    }

    for (int i = 0; i < 4; i++) {
        HBMSePlayer* p = &spWork->players[i];
        if (p->used) {
            SEQSetVolume(&p->seq, vol);
        }
    }

    for (int i = 0; i < 3; i++) {
        HBMSePlayer* p = &spWork->sePlayers[i];
        if (p->used) {
            SEQSetVolume(&p->seq, vol);
        }
    }
}
