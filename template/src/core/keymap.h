#pragma once

#include <stdbool.h>

typedef enum {
    KeymapKeyUp,
    KeymapKeyDown,
    KeymapKeyLeft,
    KeymapKeyRight,
    KeymapKeyOk,
    KeymapKeyBack,
    KeymapKeyMAX,
} KeymapKey;

typedef enum {
    KeymapEventPress,
    KeymapEventShort,
    KeymapEventLong,
    KeymapEventRepeat,
    KeymapEventRelease,
    KeymapEventMAX,
} KeymapEvent;

bool keymap_exits(KeymapKey key, KeymapEvent event);
