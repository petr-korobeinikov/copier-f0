#include "keymap_input.h"

static const KeymapKey keymap_input_keys[InputKeyMAX] = {
    [InputKeyUp] = KeymapKeyUp,
    [InputKeyDown] = KeymapKeyDown,
    [InputKeyRight] = KeymapKeyRight,
    [InputKeyLeft] = KeymapKeyLeft,
    [InputKeyOk] = KeymapKeyOk,
    [InputKeyBack] = KeymapKeyBack,
};

static const KeymapEvent keymap_input_events[InputTypeMAX] = {
    [InputTypePress] = KeymapEventPress,
    [InputTypeRelease] = KeymapEventRelease,
    [InputTypeShort] = KeymapEventShort,
    [InputTypeLong] = KeymapEventLong,
    [InputTypeRepeat] = KeymapEventRepeat,
};

bool keymap_input_exits(const InputEvent* event) {
    return keymap_exits(keymap_input_keys[event->key], keymap_input_events[event->type]);
}
