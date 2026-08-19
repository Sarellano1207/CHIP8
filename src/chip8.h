#ifndef CHIP8_H
#define CHIP8_H

#include <cstdint>
#include <string>
#include <iostream>
#include <fstream>

constexpr unsigned int FONTSET_START_ADDRESS = 0x50;
constexpr unsigned int FONTSET_SIZE = 80;
constexpr unsigned int MEMORY_SIZE = 4096;
constexpr unsigned int SCREEN_WIDTH = 64;
constexpr unsigned int SCREEN_HEIGHT = 32;
constexpr unsigned int ROM_START_ADDRESS = 0x200;

class Chip8 {
private: 
    uint8_t memory[MEMORY_SIZE]{}; // RAM
    uint8_t V[16]{}; // 16 8 bit registers
    uint16_t index{}; // Index register
    uint16_t pc{}; // Program counter
    uint16_t stack[16]{}; // Program stack
    uint8_t sp{}; // Stack pointer
    uint8_t delayTimer{};
    uint8_t soundTimer{};
    bool keypad[16]{};

    uint8_t fonts[FONTSET_SIZE] = {
        0xF0, 0x90, 0x90, 0x90, 0xF0,   // 0
        0x20, 0x60, 0x20, 0x20, 0x70,   // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0,   // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0,   // 3
        0x90, 0x90, 0xF0, 0x10, 0x10,   // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0,   // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0,   // 6
        0xF0, 0x10, 0x20, 0x40, 0x40,   // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0,   // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0,   // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90,   // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0,   // B
        0xF0, 0x80, 0x80, 0x80, 0xF0,   // C
        0xE0, 0x90, 0x90, 0x90, 0xE0,   // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0,   // E
        0xF0, 0x80, 0xF0, 0x80, 0x80    // F
    };

    private:
        void execute(uint16_t opcode);

public:
    uint8_t display[SCREEN_WIDTH * SCREEN_HEIGHT]{1}; // Screen for our CHIP8

    Chip8();

    int loadROM(const std::string& path);

    void debug_dump(unsigned int start_pos, unsigned int length) const;

    uint16_t fetch();

    uint16_t get_pc();

    void disassemble(uint16_t opcode, uint16_t addr);

    void disassemble_range(uint16_t start, uint16_t end);

    void cycle();

};

#endif