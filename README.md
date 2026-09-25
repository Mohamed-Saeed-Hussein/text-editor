# Terminal Text Editor

A terminal text editor project that I am building in C++ to learn
how text editors work, using the Kilo tutorial as a reference.

## Current status

This project is at the initial build setup stage.
The program currently prints a test message.
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

Expected output:

```text
Try Make
```

Immediately after running the program, check its exit status:

```bash
echo $?
```

An exit status of `0` indicates successful completion.

## Learning reference

https://viewsourcecode.org/snaptoken/kilo/