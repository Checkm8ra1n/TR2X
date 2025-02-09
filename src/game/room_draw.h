#pragma once

#include "global/types.h"

void __cdecl Room_GetBounds(void);
void __cdecl Room_SetBounds(
    const int16_t *obj_ptr, int32_t room_num, const ROOM_INFO *parent);
void __cdecl Room_Clip(const ROOM_INFO *r);
void __cdecl Room_DrawAllRooms(int16_t current_room);
void __cdecl Room_DrawSingleRoomGeometry(int16_t room_num);
void __cdecl Room_DrawSingleRoomObjects(int16_t room_num);
