# Compiler definitions
CROSS := riscv32-unknown-elf-
CC := $(CROSS)gcc
LD := $(CROSS)ld
DUMP := $(CROSS)objdump

# Dir definitions
BUILD_DIR := build

# Source and object file names
CSRCS := $(shell find src -name '*.c')
ASRCS := $(shell find src -name '*.S')
OBJS := $(CSRCS:%.c=$(BUILD_DIR)/%.o) $(ASRCS:%.S=$(BUILD_DIR)/%.o)

# Compiler flags
CFLAGS := \
	-fdata-sections -ffunction-sections \
	-Wall -Wextra -Wpedantic -Werror \
	-O3 -march=rv32g -mabi=ilp32 -mno-div \
	-DRISCV_ENV $(EXTRA_FLAGS) \
	-fopt-info-optimized=comp_report.txt \
	-I src
# Linker flags
LDFLAGS := -nostartfiles -T linker.lds -Wl,--gc-sections

$(BUILD_DIR)/main.elf : $(OBJS)
	@echo "LD $@"
	@$(CC) $(LDFLAGS) $^ -o $@ /dev/null

$(BUILD_DIR)/%.o: %.c
	@echo "CC $<"
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.S
	@echo "CASM $<"
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

dump: $(BUILD_DIR)/main.elf
	@echo "DUMP $<"
	@$(DUMP) -D $< > main.dump

clean:
	@rm -rf $(BUILD_DIR)
	@rm -rf main.dump
	@rm -rf comp_report.txt
