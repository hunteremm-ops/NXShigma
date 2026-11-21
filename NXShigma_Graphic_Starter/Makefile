.SUFFIXES:

ifeq ($(strip $(DEVKITPRO)),)
$(error DEVKITPRO is not set)
endif

TOPDIR ?= $(CURDIR)

include $(DEVKITPRO)/libnx/switch_rules

TARGET := NXShigma
BUILD := build
SOURCES := source
DATA :=
INCLUDES :=

ARCH := -march=armv8-a+crc+crypto -mtune=cortex-a57 -mtp=soft -fPIE

CFLAGS := -g -Wall -O2 -ffunction-sections $(ARCH)
CFLAGS += -D__SWITCH__ $(INCLUDE) $(shell sdl2-config --cflags)

CXXFLAGS := $(CFLAGS) -fno-rtti -fno-exceptions
ASFLAGS := -g $(ARCH)

LDFLAGS := -specs=$(DEVKITPRO)/libnx/switch.specs -g $(ARCH)

LIBDIRS := $(PORTLIBS) $(LIBNX)
LIBS := $(shell sdl2-config --libs) -lSDL2_image -lSDL2_ttf -lnx
