# Compiler and Tools
CC = m68k-elf-gcc
AS = m68k-elf-as
LD = m68k-elf-ld
OBJCOPY = m68k-elf-objcopy
CFLAGS =  -O2 -Wall -std=c99 -ffreestanding  -Iinclude
LDFLAGS = -T bios.ld -e start

# Directories
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include

# Files
SRCS = $(wildcard $(SRC_DIR)/*.c)
ASMS = $(wildcard $(SRC_DIR)/*.s)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS)) \
       $(patsubst $(SRC_DIR)/%.s, $(BUILD_DIR)/%.o, $(ASMS))
TARGET = $(BUILD_DIR)/bios.bin

# Rules
all: $(TARGET)

$(TARGET): $(OBJS)
	@echo "Linking..."
	$(LD)  $(LDFLAGS) -o $(BUILD_DIR)/bios.elf $^
	@echo "Creating binary..."
	$(OBJCOPY) -O binary $(BUILD_DIR)/bios.elf $(TARGET)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.s
	@mkdir -p $(BUILD_DIR)
	@echo "Assembling $<..."
	$(AS) -o $@ $<

clean:
	@echo "Cleaning up..."
	rm -rf $(BUILD_DIR)

# Optional debugging
disasm: $(TARGET)
	@echo "Disassembling..."
	m68k-elf-objdump -D $(BUILD_DIR)/bios.elf > $(BUILD_DIR)/bios.disasm

.PHONY: all clean disasm
