# NXShigma Graphic Starter

This is a **starter source project**, not a compiled `.nro` and not a console exploit.

## What's included
- `source/main.c`: SDL2-based menu source
- `assets/nxshigma.png`: NXShigma background image (if included in this ZIP)
- `Makefile`: starter build configuration

## Important requirements
This project requires a correctly installed Nintendo Switch homebrew toolchain:
- devkitA64 and libnx
- switch-sdl2
- switch-sdl2_image
- switch-sdl2_ttf

The app expects a TrueType font at `romfs:/font.ttf` or `romfs:/assets/font.ttf`.
Add a legally redistributable `.ttf` font to `assets` and name it `font.ttf`.
If no font is present, the background and colored menu bars still render, but menu text is not drawn.

## Build status
This ZIP contains source files only. It does not contain a compiled `.nro`, a jailbreak payload,
or instructions to bypass console security. Copying it to a microSD card will not make it launch.
A compatible homebrew environment is required.

## Controls
- D-pad Up/Down: move selection
- B: exit
- Keyboard Up/Down and Escape are supported for testing on a computer build.
