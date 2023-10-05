#include "specific/s_music.h"

#include "global/funcs.h"
#include "global/vars.h"
#include "lib/winmm.h"

bool __cdecl S_Music_PlaySynced(int32_t track_id)
{
    g_CD_TrackID = track_id;

    track_id = Music_GetRealTrack(track_id);

    MCI_SET_PARMS set_params;
    set_params.dwTimeFormat = MCI_FORMAT_TMSF;
    if (mciSendCommand(
            g_MciDeviceID, MCI_SET, MCI_SET_TIME_FORMAT, (DWORD_PTR)&set_params)
        != 0) {
        return false;
    }

    MCI_PLAY_PARMS play_params;
    play_params.dwFrom = track_id;
    play_params.dwTo = track_id + 1;
    if (mciSendCommand(
            g_MciDeviceID, MCI_PLAY, MCI_NOTIFY_FAILURE | MCI_NOTIFY_ABORTED,
            (DWORD_PTR)&play_params)
        != 0) {
        return false;
    }

    return true;
}

uint32_t __cdecl S_Music_GetFrames(void)
{
    MCI_STATUS_PARMS status_params;
    status_params.dwItem = MCI_STATUS_POSITION;
    if (mciSendCommand(
            g_MciDeviceID, MCI_STATUS, MCI_STATUS_ITEM,
            (DWORD_PTR)&status_params)
        != 0) {
        return 0;
    }

    uint32_t pos = status_params.dwReturn;
    int32_t min = MCI_TMSF_MINUTE(pos);
    int32_t sec = MCI_TMSF_SECOND(pos);
    int32_t frame = MCI_TMSF_FRAME(pos);
    return (min * 60 + sec) * 75 + frame;
}

void __cdecl S_Music_SetVolume(int32_t volume)
{
    int32_t aux_dev_count = auxGetNumDevs();
    if (aux_dev_count == 0) {
        return;
    }

    volume *= 0x100;

    int32_t device_id = -1;
    bool is_volume_set = false;
    for (int32_t i = 0; i < aux_dev_count; ++i) {
        AUXCAPS caps;
        auxGetDevCaps(i, &caps, sizeof(AUXCAPS));

        switch (caps.wTechnology) {
        case AUXCAPS_CDAUDIO:
            auxSetVolume(i, MAKELONG(volume, volume));
            is_volume_set = true;
            break;

        case AUXCAPS_AUXIN:
            device_id = i;
            break;
        }
    }

    if (!is_volume_set && device_id != -1) {
        auxSetVolume(device_id, MAKELONG(volume, volume));
    }
}
