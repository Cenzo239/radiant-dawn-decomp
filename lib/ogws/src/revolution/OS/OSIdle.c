#include <revolution/OS.h>

/* FE10 links OSSetIdleFunction (Dolphin SDK OSIdle.c; reconstructed from the code). */

static OSThread IdleThread;

OSThread* OSSetIdleFunction(OSThreadFunc idleFunction, void* param,
                            void* stack, u32 stackSize) {
    if (idleFunction != NULL) {
        if (IdleThread.state == 0) {
            OSCreateThread(&IdleThread, idleFunction, param, stack, stackSize,
                           31, 1);
            OSResumeThread(&IdleThread);
            return &IdleThread;
        }
    } else if (IdleThread.state != 0) {
        OSCancelThread(&IdleThread);
    }

    return NULL;
}
