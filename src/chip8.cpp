#include "chip8.h"

Chip8::Chip8() {
    for (unsigned int i = 0; i < FONTSET_SIZE; i++) {
        memory[FONTSET_START_ADDRESS + i] = fonts[i];
    }
    pc = ROM_START_ADDRESS;
}

int Chip8::loadROM(const std::string& path) {
    // Open the file in the given path
    std::ifstream inFile(path, std::ios::binary | std::ios::ate);
    
    // Check if there was an error with the file
    if (!inFile) {
        std::cerr << "Error: file not found or can't open file!" << std::endl;
        return -1;
    }

    //If the file is open, check the size and either pass/fail it    
    std::streampos fileSize = inFile.tellg();
    std::cout << "File size: " << fileSize << " bytes." << std::endl;
    unsigned int valid_size = MEMORY_SIZE - ROM_START_ADDRESS;
    if (fileSize > valid_size) {
        std::cerr << "ROM File is too big!" << std::endl;
        return -1;
    }
    else
        std::cout << "File size is acceptable!" << std::endl;
    inFile.seekg(0, std::ios::beg);

    //Load ROM file into memory 
    inFile.read(reinterpret_cast<char*>(memory + ROM_START_ADDRESS), fileSize);

    return 1;
}

void Chip8::debug_dump(unsigned int start_pos, unsigned int length) const{
    if (start_pos >= MEMORY_SIZE) return;
    if (length > MEMORY_SIZE - start_pos) length = MEMORY_SIZE - start_pos;

    for (unsigned int i = 0; i < length; ++i) {
        if (i % 16 == 0) std::printf("0x%04X: ", start_pos + i);
        std::printf("%02x", memory[start_pos + i]);
        if (i % 2 == 1)  std::printf(" ");
        if (i % 16 == 15 || i == length - 1) std::printf("\n");
    }
}

uint16_t Chip8::fetch() {
    uint16_t opcode = (memory[pc] << 8) | memory[pc + 1];
    pc += 2;
    return opcode;
}

// Remove at some point, it is only here for testing purposes
uint16_t Chip8::get_pc() {
    return pc;
}

void Chip8::disassemble(uint16_t opcode, uint16_t addr) {
    uint8_t family = (opcode & 0xF000) >> 12;
    uint8_t  x      = (opcode & 0x0F00) >> 8;   // register index
    uint8_t  y      = (opcode & 0x00F0) >> 4;   // register index
    uint8_t  n      =  opcode & 0x000F;         // low nibble
    uint8_t  kk     =  opcode & 0x00FF;         // low byte
    uint16_t nnn    =  opcode & 0x0FFF;         // 12-bit address

    switch (family) {
        case 0:
            switch (kk) {
                case 0xE0: 
                    std::printf("Ox%04X  %04X    CLS\n", addr, opcode);
                    break;
                case 0xEE:
                    std::printf("Ox%04X  %04X    RET\n", addr, opcode);
                    break;
                default:    
                    std::printf("???\n");
                    break;
            }
        
        case 1:
            std::printf("Ox%04X  %04X    JP   %03X\n", addr, opcode, nnn);
            break;
        case 2:
            std::printf("Ox%04X  %04X    CALL   %03X\n", addr, opcode, nnn);
            break;
        case 3:
            std::printf("Ox%04X  %04X    SE   %04X\n", addr, opcode, nnn);
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            std::printf("Ox%04X  %04X    LD   V%x, Ox%04X\n", addr, opcode, x, kk);
            break;
        case 7: 
            break;
        case 8:
            break;
        case 9:
            break;
        case 0x0A:
            break;
        case 0x0B:
            break;
        case 0x0C:
            break;
        case 0x0D:
            break;
        case 0x0E:
            break;
        case 0x0F:
            break;
    }
}