TARGET := NXShigma
BUILD := build
SOURCES := source
DATA :=
INCLUDES :=
ROMFS := romfs

ARCH := -march=armv8-a+crc+crypto -mtune=cortex-a57 -mtp=soft -fPIE

CFLAGS := -g -Wall -O2 -ffunction-sections $(ARCH)
CFLAGS += $(shell $(DEVKITPRO)/portlibs/switch/bin/sdl2-config --cflags)

CXXFLAGS := $(CFLAGS) -fno-rtti -fno-exceptions

LDFLAGS := -specs=$(DEVKITPRO)/libnx/switch.specs -g $(ARCH)

LIBS := -lSDL2_image -lSDL2_ttf $(shell $(DEVKITPRO)/portlibs/switch/bin/sdl2-config --libs) -lnx

include $(DEVKITPRO)/libnx/switch_rules
