# Terminal Text Editor

**Learning how an editor works, one terminal experiment at a time.**

A C++20 project for Linux, following the concepts in [Build Your Own Text Editor](https://viewsourcecode.org/snaptoken/kilo/) and documenting deliberate C++ adaptations.

`C++20` · `Linux` · `termios` · `GNU Make`

[Try the current step](#try-the-current-step) · [Progress](docs/progress.md) · [Roadmap](ROADMAP.md) · [Terminal behavior](docs/terminal-behavior.md)

---

## Current checkpoint

**Kilo chapter 2, step 8 — [Display keypresses](https://viewsourcecode.org/snaptoken/kilo/02.enteringRawMode.html#display-keypresses).**

The program saves the original terminal settings, disables echo and canonical mode, and reads input one byte at a time. It displays each byte's numeric value and, when printable, the character itself.

| Implemented now | Still ahead |
| :--- | :--- |
| Immediate byte-by-byte input | Full raw mode and escape-sequence decoding |
| Numeric keypress display | Screen drawing and cursor navigation |
| Checked terminal restoration on supported exit paths | Opening, editing, and saving text |
| C++20 build with warnings enabled | Unicode editing and Arabic presentation |

**Text editing is not implemented yet.** The goal at this stage is understanding the terminal boundary.

## Try the current step

Requirements: Linux, a C++20-capable `g++`, GNU Make, and an interactive terminal.

```bash
git clone https://github.com/Mohamed-Saeed-Hussein/text-editor.git
cd text-editor
make
./build/text-editor
```

The Makefile creates `build/text-editor`. The program starts with:

```text
ICANON: disabled
ECHO: disabled
```

Press `a`, then `Ctrl-A`. Expected output:

```text
97 ('a')
1
```

Press **`q`** to exit immediately without Enter. The `q` itself is not printed. At the shell prompt, `echo $?` reports `0` after a successful run; handled setup, input, or restoration failures report `1`.

## Terminal behavior

This is an incremental experiment, not full raw mode. Reads block with `VMIN = 1` and `VTIME = 0`; Ctrl-D is an ordinary byte, not an EOF shortcut.

A shared cleanup block restores the saved settings on normal exit and handled errors. Signal termination, crashes, and future control flow that bypasses this block are outside that guarantee.

If interrupted and shell typing becomes invisible, type `stty sane` at the shell prompt and press Enter. If suspended with Ctrl-Z, use `fg`, then `q`. Read the [full behavior and recovery notes](docs/terminal-behavior.md) before experimenting.

## Design notes

- **Explicit control flow:** a local snapshot and checked cleanup replace Kilo's global snapshot and `atexit` callback.
- **Immediate settings changes:** `TCSANOW` retains queued input. Type only `q` when quitting; trailing input can reach the shell.
- **Byte classification:** conversion to `unsigned char` keeps character classification valid.
- **Small learning steps:** the next step is reviewing Ctrl-C/Ctrl-Z signal behavior. It has not been implemented.

## Documentation map

| Document | Purpose |
| :--- | :--- |
| [Current progress](docs/progress.md) | Verified work, evidence, and the next small step |
| [Roadmap](ROADMAP.md) | Long-term scope and acceptance criteria |
| [Decisions](docs/decisions.md) | Design history and options |
| [Terminal behavior](docs/terminal-behavior.md) | Cleanup limits, input details, and recovery |

Arabic support is planned in separate stages: UTF-8 preservation, Unicode-aware editing/history, and shaping/bidirectional presentation. None is claimed complete by the current byte-input experiment.
