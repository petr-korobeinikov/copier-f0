#pragma once

#include <furi.h>

typedef struct Screen Screen;

Screen* screen_alloc(FuriMessageQueue* input_queue);

void screen_free(Screen* screen);
