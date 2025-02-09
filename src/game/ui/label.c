#include "game/ui/label.h"

#include "game/text.h"

#include <libtrx/memory.h>

typedef struct {
    UI_WIDGET_VTABLE vtable;
    TEXTSTRING *text;
    int32_t width;
    int32_t height;
    bool has_frame;
} UI_LABEL;

static int32_t UI_Label_GetWidth(const UI_LABEL *self);
static int32_t UI_Label_GetHeight(const UI_LABEL *self);
static void UI_Label_SetPosition(UI_LABEL *self, int32_t x, int32_t y);
static void UI_Label_Free(UI_LABEL *self);

static int32_t UI_Label_GetWidth(const UI_LABEL *const self)
{
    if (self->width < 0) {
        return Text_GetWidth(self->text) * PHD_ONE / Text_GetScaleH(PHD_ONE);
    }
    return self->width;
}

static int32_t UI_Label_GetHeight(const UI_LABEL *const self)
{
    return self->height;
}

static void UI_Label_SetPosition(
    UI_LABEL *const self, const int32_t x, const int32_t y)
{
    Text_SetPos(self->text, x, y);
}

static void UI_Label_Free(UI_LABEL *const self)
{
    Text_Remove(self->text);
    Memory_Free(self);
}

UI_WIDGET *UI_Label_Create(
    const char *const text, const int32_t width, const int32_t height)
{
    UI_LABEL *self = Memory_Alloc(sizeof(UI_LABEL));
    self->vtable = (UI_WIDGET_VTABLE) {
        .control = NULL,
        .get_width = (UI_WIDGET_GET_WIDTH)UI_Label_GetWidth,
        .get_height = (UI_WIDGET_GET_HEIGHT)UI_Label_GetHeight,
        .set_position = (UI_WIDGET_SET_POSITION)UI_Label_SetPosition,
        .free = (UI_WIDGET_FREE)UI_Label_Free,
    };

    self->text = Text_Create(0, 0, 0, text);
    self->text->pos.z = 16;
    self->width = width;
    self->height = height;
    self->has_frame = false;
    return (UI_WIDGET *)self;
}

void UI_Label_ChangeText(UI_WIDGET *const widget, const char *const text)
{
    UI_LABEL *const self = (UI_LABEL *)widget;
    Text_ChangeText(self->text, text);
}

void UI_Label_AddFrame(UI_WIDGET *const widget)
{
    UI_LABEL *const self = (UI_LABEL *)widget;
    if (!self->has_frame) {
        self->text->pos.z = 0;
        Text_AddBackground(self->text, 0, 0, 0, 0, 0, INV_COLOR_BLACK, NULL, 0);
        Text_AddOutline(self->text, true, INV_COLOR_BLUE, NULL, 0);
        self->has_frame = true;
    }
}

void UI_Label_RemoveFrame(UI_WIDGET *const widget)
{
    UI_LABEL *const self = (UI_LABEL *)widget;
    if (self->has_frame) {
        Text_RemoveBackground(self->text);
        Text_RemoveOutline(self->text);
        self->text->pos.z = 16;
        self->has_frame = false;
    }
}

void UI_Label_Flash(
    UI_WIDGET *const widget, const bool enable, const int32_t rate)
{
    UI_LABEL *const self = (UI_LABEL *)widget;
    Text_Flash(self->text, enable, rate);
}
