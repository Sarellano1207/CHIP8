#include <cstdint>
#include <string>

class Chip8 {
    void loadROM(const std::string& path);
    uint8_t display[64 * 32]; // Screen for our CHIP8

private: 
    uint8_t memory[4096]{}; // RAM
    uint8_t V[16]{}; // 16 8 bit registers
    uint8_t index{}; // Index register
    uint8_t pc{}; // Program counter
    uint16_t stack[16]; // Program stack
    uint8_t sp; // Stack pointer
    uint8_t delayTimer;
    uint8_t soundTimer;
    uint16_t opcode; 
    bool keypad[16];
public:

};