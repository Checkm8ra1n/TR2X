#include "game/output.h"

#include "global/funcs.h"
#include "global/vars.h"

void __cdecl Output_InsertPolygons(const int16_t *obj_ptr, int32_t clip)
{
    g_FltWinLeft = g_PhdWinMinX;
    g_FltWinTop = g_PhdWinMinY;
    g_FltWinRight = (g_PhdWinMaxX + g_PhdWinMinX + 1);
    g_FltWinBottom = (g_PhdWinMaxY + g_PhdWinMinY + 1);
    g_FltWinCenterX = (g_PhdWinMinX + g_PhdWinCenterX);
    g_FltWinCenterY = (g_PhdWinMinY + g_PhdWinCenterY);
    obj_ptr = Output_CalcObjectVertices(obj_ptr + 4);
    if (obj_ptr) {
        obj_ptr = Output_CalcVerticeLight(obj_ptr);
        obj_ptr = g_Output_DrawObjectGT4(obj_ptr + 1, *obj_ptr, ST_AVG_Z);
        obj_ptr = g_Output_DrawObjectGT3(obj_ptr + 1, *obj_ptr, ST_AVG_Z);
        obj_ptr = g_Output_DrawObjectG4(obj_ptr + 1, *obj_ptr, ST_AVG_Z);
        g_Output_DrawObjectG3(obj_ptr + 1, *obj_ptr, ST_AVG_Z);
    }
}
