---
description: How the core is tested on the Mac with no device, and what only the device can check.
---

# Host tests

```shell
mise run test
```

From `.mise/tasks/`:

- `test` builds the suites under `test/` with the system `cc` and runs them on the Mac,
  one `ok` line per test.
  The template ships no suite: the first comes with the first code in `src/core/`.

`mise run test` alone also needs the system `cc`, unpinned.
It compiles with the SDK's warning flags as errors,
plus the address and undefined-behavior sanitizers the device cannot run,
and needs no device.
A failed assertion stops the task non-zero, naming its file and line,
after the `ok` lines of the tests before it.

## Writing a test

The core, `src/core/`, includes no Flipper header, so it builds on the Mac.
A suite `test/<path>_test.c` is built with `src/core/<path>.c`, at any depth,
and with every `*_fake.c` under `test/`:

- each test is a `static void test_…(void)` function on `assert`;
- `main` runs each through `test_run` from `test/test.h`, which prints `ok <name>`;
- code that reaches the platform through an interface gets a fake of it,
  `<interface>_fake.c` under `test/` with its header beside it, which every suite links.

A `.c` file under `test/` builds into no package, and lint checks it.

## What only the device checks

The platform layer, `src/platform/`, and the view, `src/ui/`, run only on the device:
the buttons, the screen, and whatever else the app reaches through the firmware.
