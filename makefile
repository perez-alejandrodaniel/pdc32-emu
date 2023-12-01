CXX := g++
CXXFLAGS := -std=c++11 -Wall -O2
SDL2FLAGS=$(shell pkg-config sdl2 --cflags --libs)

TEST_SOURCE := "prg/uart_test.pdc"
TEST_SOURCE_BASE := "prg/jump_call_test.pdc"
BUILD_DIR := build

all: $(BUILD_DIR)/emu.exe $(BUILD_DIR)/asm.exe

$(BUILD_DIR)/emu.exe: emu.cpp vga.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@ ${SDL2FLAGS}

$(BUILD_DIR)/asm.exe: asm.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

compile_flags.txt: makefile
	echo '$(CXXFLAGS)' | tr ' ' '\n' > $@

test: $(BUILD_DIR)/asm.exe $(BUILD_DIR)/emu.exe
	cat $(TEST_SOURCE) | ./$(BUILD_DIR)/asm.exe > $(BUILD_DIR)/test.bin
	cat $(TEST_SOURCE_BASE) | ./$(BUILD_DIR)/asm.exe > $(BUILD_DIR)/program.bin
	./$(BUILD_DIR)/emu.exe $(BUILD_DIR)/test.bin

clean:
	rm -rf $(BUILD_DIR)/*
