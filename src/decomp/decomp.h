#pragma once

#include "global/types.h"

#include <stdint.h>
#include <windows.h>

int32_t __cdecl GameInit(void);
int32_t __stdcall WinMain(
    HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine,
    int32_t nShowCmd);
const char *__cdecl DecodeErrorMessage(int32_t error_code);
int32_t __cdecl RenderErrorBox(int32_t error_code);
void __cdecl ScreenshotPCX(void);
size_t __cdecl CompPCX(
    uint8_t *bitmap, int32_t width, int32_t height, RGB888 *palette,
    uint8_t **pcx_data);
size_t __cdecl EncodeLinePCX(const uint8_t *src, int32_t width, uint8_t *dst);
size_t __cdecl EncodePutPCX(uint8_t value, uint8_t num, uint8_t *buffer);
void __cdecl Screenshot(LPDDS screen);
