# Terminal Text Editor

A terminal text editor project that I am building in C++ to learn
how text editors work, using the Kilo tutorial as a reference.

## Current status

Current learning point: [Kilo chapter 2, step 7 — Turn off canonical mode](https://viewsourcecode.org/snaptoken/kilo/02.enteringRawMode.html#turn-off-canonical-mode).

The program saves the terminal settings, disables echo and canonical mode, and
reads one byte at a time until `q` or end-of-file. One explicit cleanup block restores the
original settings on normal exit and handled setup/input errors. It also accepts
an already noncanonical terminal and restores that original configuration.
Text editing is not implemented yet.

## Requirements

- Linux
- g++ with C++20 support
- GNU Make

## Build

Run this command from the project root, where the Makefile is located:

```bash
make
```

This builds the program and creates the executable at `build/text-editor`.

## Run

```bash
./build/text-editor
```

Run in a terminal. Expected output after echo and canonical mode are disabled:

```text
ICANON: disabled
ECHO: disabled
```

The program waits for one byte without a timer (`VMIN = 1`, `VTIME = 0`).
Press `q` to quit immediately without Enter. The typed `q` stays invisible.
Ctrl-D is now an ordinary input byte, not an EOF shortcut; use `q` to exit.
This is an incremental terminal experiment, not full raw mode.

After the program exits, check its exit status:

```bash
echo $?
```

An exit status of `0` indicates successful completion.
Setup, input, or explicitly checked restoration failures print an error and
exit with status `1`. Redirected non-terminal input fails the settings check.

## Interrupted tests and recovery

After a settings-change attempt, every normal return path must reach the
cleanup block. Future early returns, thrown exceptions, or calls to exit() can
bypass it. It also does not run when a default signal action terminates the process (for
example Ctrl-C/SIGINT or SIGTERM), or on SIGKILL or a crash. Signal handling
is outside this small experiment. If restoration itself fails, an error is
reported; restoration cannot be guaranteed for an unavailable terminal.

If interrupted and typing is invisible, return to the shell prompt, type
`stty sane` even if you cannot see it, and press Enter. This restores usable
terminal defaults, not necessarily your exact earlier custom settings.
If the program was suspended with Ctrl-Z, use `fg` to resume it, then type
`q` to reach cleanup and restore the original settings. If the display
is still unusable, type `reset` and Enter or open a new terminal.

Manual check: run `./build/text-editor`, type `q`, confirm that it is invisible
and the program exits without Enter. At the shell prompt, run
`echo $?`: typing should be visible again (if echo was originally enabled),
and the status should be `0`.

## Deliberate adaptations

Use C++20, a local saved snapshot, and one explicit cleanup block instead of
Kilo's global snapshot and `atexit` callback. Restoration retries interrupted
calls; other failures produce an error and status 1. There is no destructor
fallback. After attempting to change settings, record errors in exitStatus and
leave the loop with break so cleanup runs before returning. Keep syscall checks
now, with system-error details, rather than postponing them.

`VMIN = 1`, `VTIME = 0` makes this step's blocking read independent of inherited
settings. This is not Kilo's later timeout experiment. `TCSANOW` is retained:
settings change immediately and unread input is not discarded, unlike Kilo's
`TCSAFLUSH`. Type only `q` when quitting; any queued trailing input may reach
the shell. The two initial status lines are temporary observation aids.

## Learning reference

[Build Your Own Text Editor](https://viewsourcecode.org/snaptoken/kilo/).
Follow its concept order and small step diffs, adapting to C++ as explained.
Next: chapter 2, step 8, displaying keypress values; not implemented yet.
