# Nintendo Switch homebrew build file.
# Requires devkitA64, libnx, switch-sdl2, switch-sdl2_image, switch-sdl2_ttf.
TARGET      := NXShigma
BUILD       := build
SOURCES     := source
DATA        := assets
INCLUDES    :=

ROMFS       := romfs
ROMFS_DIRS  := assets

ARCH        := -march=armv8-a+crc+crypto -mtune=cortex-a57 -mtp=soft -fPIE
CFLAGS      := -g -Wall -O2 -ffunction-sections $(ARCH) $(INCLUDES) \
               $(shell sdl2-config --cflags)
CXXFLAGS    := $(CFLAGS) -fno-rtti -fno-exceptions
LDFLAGS     := -specs=$(DEVKITPRO)/libnx/switch.specs -g $(ARCH) \
               -Wl,-Map,$(notdir $*.map)
LIBS        := -lSDL2_image -lSDL2_ttf $(shell sdl2-config --libs) -lnx

# Include project assets in the app's read-only filesystem.
include $(DEVKITPRO)/libnx/switch_rules
