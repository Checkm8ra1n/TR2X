#pragma once

#include <stdint.h>

void __cdecl Output_InsertPolygons(const int16_t *obj_ptr, int32_t clip);
void __cdecl Output_InsertRoom(const int16_t *obj_ptr, int32_t is_outside);
void __cdecl Output_InsertSkybox(const int16_t *obj_ptr);
const int16_t *__cdecl Output_CalcObjectVertices(const int16_t *obj_ptr);
const int16_t *__cdecl Output_CalcSkyboxLight(const int16_t *obj_ptr);
const int16_t *__cdecl Output_CalcVerticeLight(const int16_t *obj_ptr);
const int16_t *__cdecl Output_CalcRoomVertices(
    const int16_t *obj_ptr, int32_t far_clip);
void __cdecl Output_RotateLight(int16_t pitch, int16_t yaw);
void __cdecl Output_InitPolyList(void);
void __cdecl Output_SortPolyList(void);
void __cdecl Output_QuickSort(int32_t left, int32_t right);
void __cdecl Output_PrintPolyList(uint8_t *surface_ptr);
void __cdecl Output_SetNearZ(int32_t near_z);
void __cdecl Output_SetFarZ(int32_t far_z);
