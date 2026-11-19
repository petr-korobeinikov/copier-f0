#include "app.h"

#include <furi.h>

#include "keymap_input.h"
#include "screen.h"

struct App {
    FuriEventLoop* event_loop;
    FuriMessageQueue* input_queue;
    Screen* screen;
};

static void app_input_callback(FuriEventLoopObject* object, void* context) {
    App* app = context;
    InputEvent event;
    furi_check(furi_message_queue_get(object, &event, 0) == FuriStatusOk);

    if(keymap_input_exits(&event)) {
        furi_event_loop_stop(app->event_loop);
    }
}

App* app_alloc(void) {
    App* app = malloc(sizeof(App));
    app->event_loop = furi_event_loop_alloc();
    app->input_queue = furi_message_queue_alloc(8, sizeof(InputEvent));
    furi_event_loop_subscribe_message_queue(
        app->event_loop, app->input_queue, FuriEventLoopEventIn, app_input_callback, app);
    app->screen = screen_alloc(app->input_queue);
    return app;
}

void app_free(App* app) {
    screen_free(app->screen);
    furi_event_loop_unsubscribe(app->event_loop, app->input_queue);
    furi_message_queue_free(app->input_queue);
    furi_event_loop_free(app->event_loop);
    free(app);
}

void app_run(App* app) {
    furi_event_loop_run(app->event_loop);
}
