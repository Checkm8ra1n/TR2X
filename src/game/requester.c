#include "game/requester.h"

#include "game/text.h"
#include "global/funcs.h"
#include "global/vars.h"

#include <libtrx/utils.h>

static void Requester_ClearTextStrings(REQUEST_INFO *req);

static void Requester_ClearTextStrings(REQUEST_INFO *const req)
{
    Text_Remove(req->heading_text1);
    req->heading_text1 = NULL;

    Text_Remove(req->heading_text2);
    req->heading_text2 = NULL;

    Text_Remove(req->background_text);
    req->background_text = NULL;

    Text_Remove(req->moreup_text);
    req->moreup_text = NULL;

    Text_Remove(req->moredown_text);
    req->moredown_text = NULL;

    for (int32_t i = 0; i < MAX_REQUESTER_ITEMS; i++) {
        Text_Remove(req->item_texts1[i]);
        req->item_texts1[i] = NULL;
        Text_Remove(req->item_texts2[i]);
        req->item_texts2[i] = NULL;
    }
}

void __cdecl Requester_Init(REQUEST_INFO *const req)
{
    req->background_flags = 1;
    req->moreup_flags = 1;
    req->moredown_flags = 1;
    req->items_count = 0;

    req->heading_text1 = NULL;
    req->heading_text2 = NULL;
    req->heading_flags1 = 0;
    req->heading_flags2 = 0;
    req->background_text = NULL;
    req->moreup_text = NULL;
    req->moredown_text = NULL;

    for (int32_t i = 0; i < MAX_REQUESTER_ITEMS; i++) {
        req->item_texts1[i] = NULL;
        req->item_texts2[i] = NULL;
        req->item_flags1[i] = 0;
        req->item_flags2[i] = 0;
    }

    req->pitem_flags1 = g_RequesterFlags1;
    req->pitem_flags2 = g_RequesterFlags2;

    req->render_width = GetRenderWidth();
    req->render_height = GetRenderHeight();
}

void __cdecl Requester_Shutdown(REQUEST_INFO *const req)
{
    Requester_ClearTextStrings(req);
    req->ready = 0;
}

void __cdecl Requester_RemoveAllItems(REQUEST_INFO *const req)
{
    req->items_count = 0;
    req->line_offset = 0;
    req->selected = 0;
}

void __cdecl Requester_Item_CenterAlign(
    REQUEST_INFO *const req, TEXTSTRING *const text)
{
    if (text == NULL) {
        return;
    }
    text->bgnd_off.x = 0;
    text->pos.x = req->x_pos;
}

void __cdecl Requester_Item_LeftAlign(
    REQUEST_INFO *const req, TEXTSTRING *const text)
{
    if (text == NULL) {
        return;
    }
    const uint32_t scale_h = Text_GetScaleH(text->scale.h);
    const int32_t x = ((scale_h * req->pix_width) >> 16) / 2
        - Text_GetWidth(text) / 2 - ((8 * scale_h) >> 16);
    text->pos.x = req->x_pos - x;
    text->bgnd_off.x = x;
}

void __cdecl Requester_Item_RightAlign(
    REQUEST_INFO *const req, TEXTSTRING *const text)
{
    const uint32_t scale_h = Text_GetScaleH(text->scale.h);
    if (text == NULL) {
        return;
    }
    const int32_t x = ((scale_h * req->pix_width) >> 16) / 2
        - Text_GetWidth(text) / 2 - ((8 * scale_h) >> 16);
    text->pos.x = x + req->x_pos;
    text->bgnd_off.x = -x;
}

void __cdecl Requester_SetHeading(
    REQUEST_INFO *const req, const char *const text1, const uint32_t flags1,
    const char *const text2, const uint32_t flags2)
{
    Text_Remove(req->heading_text1);
    req->heading_text1 = NULL;

    Text_Remove(req->heading_text2);
    req->heading_text2 = NULL;

    if (text1 != NULL) {
        strcpy(req->heading_string1, text1);
        req->heading_flags1 = flags1 | REQ_USE;
    } else {
        strcpy(req->heading_string1, "u");
        req->heading_flags1 = 0;
    }

    if (text2 != NULL) {
        strcpy(req->heading_string2, text2);
        req->heading_flags2 = flags2 | REQ_USE;
    } else {
        strcpy(req->heading_string2, "u");
        req->heading_flags2 = 0;
    }
}

void __cdecl Requester_ChangeItem(
    REQUEST_INFO *const req, const int32_t item, const char *const text1,
    const uint32_t flags1, const char *const text2, const uint32_t flags2)
{
    Text_Remove(req->item_texts1[item]);
    req->item_texts1[item] = NULL;

    Text_Remove(req->item_texts2[item]);
    req->item_texts2[item] = NULL;

    if (text1 != NULL) {
        strcpy(&req->pitem_strings1[item * req->item_string_len], text1);
        req->pitem_flags1[item] = flags1 | REQ_USE;
    } else {
        req->pitem_flags1[item] = 0;
    }

    if (text2 != NULL) {
        strcpy(&req->pitem_strings2[item * req->item_string_len], text2);
        req->pitem_flags2[item] = flags2 | REQ_USE;
    } else {
        req->pitem_flags2[item] = 0;
    }
}

void __cdecl Requester_AddItem(
    REQUEST_INFO *const req, const char *const text1, const uint32_t flags1,
    const char *const text2, const uint32_t flags2)
{
    req->pitem_flags1 = g_RequesterFlags1;
    req->pitem_flags2 = g_RequesterFlags2;

    if (text1 != NULL) {
        strcpy(
            &req->pitem_strings1[req->items_count * req->item_string_len],
            text1);
        req->pitem_flags1[req->items_count] = flags1 | REQ_USE;
    } else {
        g_RequesterFlags1[req->items_count] = 0;
    }

    if (text2 != NULL) {
        strcpy(
            &req->pitem_strings2[req->items_count * req->item_string_len],
            text2);
        req->pitem_flags2[req->items_count] = flags2 | REQ_USE;
    } else {
        req->pitem_flags2[req->items_count] = 0;
    }

    req->items_count++;
}

void __cdecl Requester_SetSize(
    REQUEST_INFO *const req, const int32_t max_lines, const int32_t y_pos)
{
    int32_t visible_lines = GetRenderHeight() / 2 / 18;
    CLAMPG(visible_lines, max_lines);
    req->y_pos = y_pos;
    req->visible_count = visible_lines;
}
