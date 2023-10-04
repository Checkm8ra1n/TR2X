#include "inject_exec.h"

#include "game/camera.h"
#include "game/math.h"
#include "game/matrix.h"
#include "game/shell.h"
#include "game/sound.h"
#include "inject_util.h"

static void Inject_Camera(void);
static void Inject_Math(void);
static void Inject_Matrix(void);
static void Inject_Shell(void);
static void Inject_Sound(void);

static void Inject_Camera(void)
{
    INJECT(1, 0x004105A0, Camera_Initialise);
    INJECT(1, 0x00410650, Camera_Move);
    INJECT(1, 0x004109D0, Camera_Clip);
    INJECT(1, 0x00410AB0, Camera_Shift);
    INJECT(1, 0x00410C10, Camera_GoodPosition);
    INJECT(1, 0x00410C60, Camera_SmartShift);
    INJECT(1, 0x004113F0, Camera_Chase);
    INJECT(1, 0x004114E0, Camera_ShiftClamp);
    INJECT(1, 0x00411680, Camera_Combat);
    INJECT(1, 0x00411810, Camera_Look);
    INJECT(1, 0x00411A00, Camera_Fixed);
    INJECT(1, 0x00411AA0, Camera_Update);
    INJECT(1, 0x004126A0, Camera_LoadCutsceneFrame);
    INJECT(1, 0x00412290, Camera_UpdateCutscene);
}

static void Inject_Matrix(void)
{
    INJECT(1, 0x00401000, Matrix_GenerateW2V);
    INJECT(1, 0x004011D0, Matrix_LookAt);
    INJECT(1, 0x004012D0, Matrix_RotX);
    INJECT(1, 0x00401380, Matrix_RotY);
    INJECT(1, 0x00401430, Matrix_RotZ);
    INJECT(1, 0x004014E0, Matrix_RotYXZ);
    INJECT(1, 0x004016C0, Matrix_RotYXZpack);
    INJECT(1, 0x004018B0, Matrix_TranslateRel);
}

static void Inject_Math(void)
{
    INJECT(1, 0x00457C10, Math_Atan);
    INJECT(1, 0x00457C58, Math_Cos);
    INJECT(1, 0x00457C5E, Math_Sin);
    INJECT(1, 0x00457C93, Math_Sqrt);
}

static void Inject_Shell(void)
{
    INJECT(1, 0x0044E890, Shell_ExitSystem);
}

static void Inject_Sound(void)
{
    INJECT(1, 0x00455380, Sound_SetMasterVolume);
}

void Inject_Exec(void)
{
    Inject_Camera();
    Inject_Math();
    Inject_Matrix();
    Inject_Shell();
    Inject_Sound();
}
