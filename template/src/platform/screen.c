#include "screen.h"

#include <gui/gui.h>

#include "../ui/view.h"

struct Screen {
    Gui* gui;
    ViewPort* view_port;
};

static void screen_draw_callback(Canvas* canvas, void* context) {
    UNUSED(context);
    view_draw(canvas);
}

/* Runs on the GUI thread, and event_loop.h binds its functions to the loop's own thread. */
static void screen_input_callback(InputEvent* event, void* context) {
    FuriMessageQueue* input_queue = context;
    furi_message_queue_put(input_queue, event, 0);
}

Screen* screen_alloc(FuriMessageQueue* input_queue) {
    Screen* screen = malloc(sizeof(Screen));
    screen->view_port = view_port_alloc();
    view_port_draw_callback_set(screen->view_port, screen_draw_callback, NULL);
    view_port_input_callback_set(screen->view_port, screen_input_callback, input_queue);
    screen->gui = furi_record_open(RECORD_GUI);
    gui_add_view_port(screen->gui, screen->view_port, GuiLayerFullscreen);
    return screen;
}

void screen_free(Screen* screen) {
    gui_remove_view_port(screen->gui, screen->view_port);
    furi_record_close(RECORD_GUI);
    view_port_free(screen->view_port);
    free(screen);
}
