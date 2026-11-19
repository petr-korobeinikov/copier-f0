#include "keymap.h"

bool keymap_exits(KeymapKey key, KeymapEvent event) {
    return key == KeymapKeyBack && event == KeymapEventShort;
}
