# This file contains a make script for the PkTime application
#
# Author: Josh McIntyre
#

# This block defines makefile variables
UI_FILES=src/ui/*.c
CORE_FILES=src/core/*.c
CRYPTO_FILES=src/crypto/*.c
INCLUDE_CORE=src/core
INCLUDE_CRYPTO=src/crypto

BUILD_DIR=bin
BUILD_BIN=pktime

CC=gcc
FLAGS=-Werror -I$(INCLUDE_CORE) -I$(INCLUDE_CRYPTO)

# This rule builds the utility
build: $(SRC_FILES)
	mkdir -p $(BUILD_DIR)
	$(CC) $(FLAGS) -o $(BUILD_DIR)/$(BUILD_BIN) $(CORE_FILES) $(UI_FILES) $(CRYPTO_FILES)

# This rule cleans the build directory
clean: $(BUILD_DIR)
	rm $(BUILD_DIR)/* 
	rmdir $(BUILD_DIR)
