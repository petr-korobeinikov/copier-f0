#include "keymap.h"
#include "test.h"

static void test_short_back_exits(void) {
    assert(keymap_exits(KeymapKeyBack, KeymapEventShort));
}

static void test_other_back_events_stay(void) {
    assert(!keymap_exits(KeymapKeyBack, KeymapEventPress));
    assert(!keymap_exits(KeymapKeyBack, KeymapEventLong));
    assert(!keymap_exits(KeymapKeyBack, KeymapEventRepeat));
    assert(!keymap_exits(KeymapKeyBack, KeymapEventRelease));
}

static void test_other_keys_stay(void) {
    for(KeymapKey key = KeymapKeyUp; key < KeymapKeyBack; key++) {
        assert(!keymap_exits(key, KeymapEventShort));
    }
}

int main(void) {
    test_run(test_short_back_exits);
    test_run(test_other_back_events_stay);
    test_run(test_other_keys_stay);
    return 0;
}
