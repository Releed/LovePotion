#include "common/runtime.h"
#include "modules/audio/audio.h"

#include "audiodriver.h"

using namespace love;

void Audio::_Initialize()
{
    s32 priority = 0;
    svcGetThreadPriority(&priority, CUR_THREAD_HANDLE);
    Result ret = threadCreate(&this->poolThread, AudioThreadRunner, this->pool, NULL, AUDIO_THREAD_STACK_SIZE, priority - 1, 0);

    if (R_SUCCEEDED(ret))
        threadStart(&this->poolThread);
}

void Audio::_Exit()
{
    threadWaitForExit(&this->poolThread);
    threadClose(&this->poolThread);
}

void Audio::SetVolume(float volume)
{
    AudrenDriver::LockFunction([volume](AudioDriver * driver) {
        for (int i = 0; i < 2; i++)
            audrvMixSetVolume(driver, i, volume);
    });
}
