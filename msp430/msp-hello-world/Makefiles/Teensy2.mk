#
# embedXcode
# ----------------------------------
# Embedded Computing on Xcode
#
# Copyright © Rei VILO, 2010-2014
# http://embedxcode.weebly.com
# All rights reserved
#
#
# Last update: Mar 01, 2014 release 136



# Teensy 2.0 specifics
# ----------------------------------
#
BUILD_CORE       := avr

UPLOADER            = teensy_flash
TEENSY_FLASH_PATH   = $(APPLICATION_PATH)/hardware/tools/avr/bin
TEENSY_POST_COMPILE = $(TEENSY_FLASH_PATH)/teensy_post_compile
TEENSY_REBOOT       = $(TEENSY_FLASH_PATH)/teensy_reboot

APP_TOOLS_PATH   := $(APPLICATION_PATH)/hardware/tools/avr/bin
CORE_LIB_PATH    := $(APPLICATION_PATH)/hardware/teensy/cores/teensy
APP_LIB_PATH     := $(APPLICATION_PATH)/libraries

BUILD_CORE_LIB_PATH  = $(APPLICATION_PATH)/hardware/teensy/cores/teensy3/avr
BUILD_CORE_LIBS_LIST = $(subst .h,,$(subst $(BUILD_CORE_LIB_PATH)/,,$(wildcard $(BUILD_CORE_LIB_PATH)/*.h))) # */
BUILD_CORE_C_SRCS    = $(wildcard $(BUILD_CORE_LIB_PATH)/*.c) # */

ifneq ($(strip $(NO_CORE_MAIN_FUNCTION)),)
    BUILD_CORE_CPP_SRCS = $(filter-out %program.cpp %main.cpp,$(wildcard $(BUILD_CORE_LIB_PATH)/*.cpp)) # */
else
    BUILD_CORE_CPP_SRCS = $(filter-out %program.cpp, $(wildcard $(BUILD_CORE_LIB_PATH)/*.cpp)) # */
endif

BUILD_CORE_OBJ_FILES  = $(BUILD_CORE_C_SRCS:.c=.o) $(BUILD_CORE_CPP_SRCS:.cpp=.o)
BUILD_CORE_OBJS       = $(patsubst $(BUILD_CORE_LIB_PATH)/%,$(OBJDIR)/%,$(BUILD_CORE_OBJ_FILES))

# Sketchbook/Libraries path
# wildcard required for ~ management
# ?ibraries required for libraries and Libraries
#
ifeq ($(USER_PATH)/Library/Arduino/preferences.txt,)
    $(error Error: run Teensy once and define the sketchbook path)
endif

ifeq ($(wildcard $(SKETCHBOOK_DIR)),)
    SKETCHBOOK_DIR = $(shell grep sketchbook.path $(wildcard ~/Library/Arduino/preferences.txt) | cut -d = -f 2)
endif

ifeq ($(wildcard $(SKETCHBOOK_DIR)),)
    $(error Error: sketchbook path not found)
endif

USER_LIB_PATH  = $(wildcard $(SKETCHBOOK_DIR)/?ibraries)


# Rules for making a c++ file from the main sketch (.pde)
#
PDEHEADER      = \\\#include \"WProgram.h\"  


# Tool-chain names
#
CC      = $(APP_TOOLS_PATH)/avr-gcc
CXX     = $(APP_TOOLS_PATH)/avr-g++
AR      = $(APP_TOOLS_PATH)/avr-ar
OBJDUMP = $(APP_TOOLS_PATH)/avr-objdump
OBJCOPY = $(APP_TOOLS_PATH)/avr-objcopy
SIZE    = $(APP_TOOLS_PATH)/avr-size
NM      = $(APP_TOOLS_PATH)/avr-nm


#LDSCRIPT = $(call PARSE_BOARD,$(BOARD_TAG),build.linkscript)
#VARIANT  = $(call PARSE_BOARD,$(BOARD_TAG),build.variant)
#VARIANT_PATH = $(APPLICATION_PATH)/hardware/lm4f/variants/$(VARIANT)

MCU_FLAG_NAME   = mmcu
MCU             = atmega32u4
F_CPU           = 16000000

#EXTRA_LDFLAGS   = -T$(CORE_LIB_PATH)/$(LDSCRIPT) -mthumb

# CXX = flags for C++ only
# CPP = flags for both C and C++
#
EXTRA_CPPFLAGS  = $(addprefix -D, $(PLATFORM_TAG)) -D__AVR_ATmega32U4__ -nostdlib -MMD
EXTRA_CXXFLAGS  = -fno-rtti -felide-constructors -std=c++0x


#EXTRA_CPPFLAGS += $(call PARSE_BOARD,$(BOARD_TAG),build.option3) # -D__MK20DX128__

OBJCOPYFLAGS  = -R .eeprom -Oihex 
TARGET_HEXBIN = $(TARGET_HEX)
TARGET_EEP    = $(OBJDIR)/$(TARGET).eep

