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

    return fileSize;
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
                    std::printf("0x%04X  0x%04X    CLS\n", addr, opcode);
                    break;
                case 0xEE:
                    std::printf("0x%04X  0x%04X    RET\n", addr, opcode);
                    break;
                default:    
                    std::printf("0x%04X  0x%04X    ???\n", addr, opcode);
                    break;
            }
            break;
        
        case 1:
            std::printf("0x%04X  0x%04X    JP       0x%03X\n", addr, opcode, nnn);
            break;
        case 2:
            std::printf("0x%04X  0x%04X    CALL     0x%03X\n", addr, opcode, nnn);
            break;
        case 3:
            std::printf("0x%04X  0x%04X    SE       V%X, 0x%02X\n", addr, opcode, x, kk);
            break;
        case 4:
            std::printf("0x%04X  0x%04X    SNE      V%X, 0x%02X\n", addr, opcode, x, kk);
            break;
        case 5:
            switch(n){
                case 0x0:
                    std::printf("0x%04X  0x%04X    SE       V%X, V%X\n", addr, opcode, x, y);
                    break;
                default:
                    std::printf("0x%04X  0x%04X    ???\n", addr, opcode);
                    break;
            }
            break;
        case 6:
            std::printf("0x%04X  0x%04X    LD       V%X, 0x%02X\n", addr, opcode, x, kk);
            break;
        case 7: 
            std::printf("0x%04X  0x%04X    ADD      V%X, 0x%02X\n", addr, opcode, x, kk);
            break;
        case 8:
            switch(n) {
                case 0x0:
                    std::printf("0x%04X  0x%04X    LD       V%X, V%X\n", addr, opcode, x, y);
                    break;
                case 0x1:
                    std::printf("0x%04X  0x%04X    OR       V%X, V%X\n", addr, opcode, x, y);
                    break;
                case 0x2:
                    std::printf("0x%04X  0x%04X    AND      V%X, V%X\n", addr, opcode, x, y);
                    break;
                case 0x3:
                    std::printf("0x%04X  0x%04X    XOR      V%X, V%X\n", addr, opcode, x, y);
                    break;
                case 0x4:
                    std::printf("0x%04X  0x%04X    ADD      V%X, V%X\n", addr, opcode, x, y);
                    break;
                case 0x5:
                    std::printf("0x%04X  0x%04X    SUB      V%X, V%X\n", addr, opcode, x, y);
                    break;
                case 0x6:
                    std::printf("0x%04X  0x%04X    SHR >>   V%X, V%X\n", addr, opcode, x, y);
                    break;
                case 0x7:
                    std::printf("0x%04X  0x%04X    SUBN     V%X, V%X\n", addr, opcode, x, y);
                    break;
                case 0xE:
                    std::printf("0x%04X  0x%04X    SHL <<   V%X, V%X\n", addr, opcode, x, y);
                    break;
                default:
                    std::printf("0x%04X  0x%04X    ???\n", addr, opcode);
                
            }
            break;

        case 9:
            switch(n) {
                case 0x0:
                    std::printf("0x%04X  0x%04X    SNE      V%X, V%X\n", addr, opcode, x, y);
                    break;
                default:
                    std::printf("0x%04X  0x%04X    ???\n", addr, opcode);
                }
            break;
        case 0x0A:
            std::printf("0x%04X  0x%04X    LD       I, 0x%03X\n", addr, opcode, nnn);
            break;
        case 0x0B:
            std::printf("0x%04X  0x%04X    JP       V0, 0x%03X\n", addr, opcode, nnn);
            break;
        case 0x0C:
            std::printf("0x%04X  0x%04X    RND      V%X, 0x%03X\n", addr, opcode, x, nnn);
            break;
        case 0x0D:
            std::printf("0x%04X  0x%04X    DRW      V%X, V%X, 0x%02X\n", addr, opcode, x, y, n);
            break;
        case 0x0E:
            switch (kk) {
                case 0x9E:
                    std::printf("0x%04X  0x%04X    SKP      V%X\n", addr, opcode, x);
                    break;
                case 0xA1:
                    std::printf("0x%04X  0x%04X    SKNP     V%X\n", addr, opcode, x);
                    break;
                default:
                std::printf("0x%04X  0x%04X    ???\n", addr, opcode);
            }
            break;
        case 0x0F:
            switch (kk) {
                case 0x07:
                    std::printf("0x%04X  0x%04X    LD       V%X, DT\n", addr, opcode, x);
                    break;
                case 0x0A:
                    std::printf("0x%04X  0x%04X    LD       V%X, K\n", addr, opcode, x);
                    break;
                case 0x15:
                    std::printf("0x%04X  0x%04X    LD       DT, V%X\n", addr, opcode, x);
                    break;
                case 0x18:
                    std::printf("0x%04X  0x%04X    LD       ST, V%X\n", addr, opcode, x);
                    break;
                case 0x1E:
                    std::printf("0x%04X  0x%04X    ADD      I, V%X\n", addr, opcode, x);
                    break;
                case 0x29:
                    std::printf("0x%04X  0x%04X    LD       F, V%X\n", addr, opcode, x);
                    break;
                case 0x33:
                    std::printf("0x%04X  0x%04X    LD       B, V%X\n", addr, opcode, x);
                    break;
                case 0x55:
                    std::printf("0x%04X  0x%04X    LD       [I], V%X\n", addr, opcode, x);
                    break;
                case 0x65:
                    std::printf("0x%04X  0x%04X    LD       V%X, [I]\n", addr, opcode, x);
                    break;   
                default:
                    std::printf("0x%04X  0x%04X    ???\n", addr, opcode);


            }
            break;
        default:
            std::printf("0x%04X  0x%04X    ???\n", addr, opcode);
    }
}

void Chip8::disassemble_range(uint16_t start, uint16_t end) {
    for (uint16_t addr = start; addr < end; addr += 2) {
        uint16_t opcode = (memory[addr] << 8) | memory[addr + 1];
        disassemble(opcode, addr);
    }   
}

void Chip8::execute(uint16_t opcode) {
    uint8_t family  = (opcode & 0xF000) >> 12;
    uint8_t  x      = (opcode & 0x0F00) >> 8;   // register index
    uint8_t  y      = (opcode & 0x00F0) >> 4;   // register index
    uint8_t  n      =  opcode & 0x000F;         // low nibble
    uint8_t  kk     =  opcode & 0x00FF;         // low byte
    uint16_t nnn    =  opcode & 0x0FFF;         // 12-bit address

    switch (family) {
        case 0:
            switch (kk) {
                case 0xE0:
                    for (unsigned int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++)
                        display[i] = 0;
                    break;
                case 0xEE:
                    pc = stack[sp];
                    sp--;
                    break;
                default:    
                    break;
            }
            break;
        
        case 1:
            pc = nnn;
            break;
        case 2:
            sp += 1;
            stack[sp] = pc;
            pc = nnn;
            break;
        case 3:
            if (V[x] == kk)
                pc += 2;
            break;
        case 4:
            if (V[x] != kk)
                pc += 2;
            break;
        case 5:
            switch(n){
                case 0x0:
                    if (V[x] == V[y])
                        pc += 2;
                    break;
                default:
                    break;
            }
            break;
        case 6:
            V[x] = kk;
            break;
        case 7: 
            V[x] += kk;
            break;
        case 8:
            switch(n) {
                case 0x0:
                    V[x] = V[y];
                    break;
                case 0x1:
                    V[x] |= V[y];
                    break;
                case 0x2:
                    V[x] &= V[y];
                    break;
                case 0x3:
                    V[x] ^= V[y];
                    break;
                case 0x4:
                    V[x] += V[y];
                    V[0xF] = 1;
                    break;
                case 0x5:
                    V[x] -= V[y];
                    V[0xF] = 0;
                    break;
                case 0x6:
                    break;
                case 0x7:
                    break;
                case 0xE:
                    break;
                default:
                    break;
            }
            break;

        case 9:
            switch(n) {
                case 0x0:
                    break;
                default:
                    break;
                }
            break;
        case 0x0A:
            index = nnn;
            break;
        case 0x0B:
            break;
        case 0x0C:
            break;
        case 0xD: {                              
            uint8_t start_x = V[x] % SCREEN_WIDTH;
            uint8_t start_y = V[y] % SCREEN_HEIGHT;
            V[0xF] = 0;

            for (int row = 0; row < n; row++) {
                uint8_t sprite_byte = memory[index + row];
                unsigned int py = start_y + row;
                if (py >= SCREEN_HEIGHT) break;          // clip bottom

                for (int col = 0; col < 8; col++) {
                    unsigned int px = start_x + col;
                    if (px >= SCREEN_WIDTH) break;       // clip right

                    uint8_t sprite_pixel = sprite_byte & (0x80 >> col);
                    if (sprite_pixel) {
                        int idx = py * SCREEN_WIDTH + px;
                        if (display[idx] == 1)
                            V[0xF] = 1;   // collision
                        display[idx] ^= 1;                   // XOR toggle
                    }
                }
            }
    break;
}
        case 0x0E:
            switch (kk) {
                case 0x9E:
                    break;
                case 0xA1:
                    break;
                default:    
                    break;
            }
            break;
        case 0x0F:
            switch (kk) {
                case 0x07:
                    break;
                case 0x0A:
                    break;
                case 0x15:
                    break;
                case 0x18:
                    break;
                case 0x1E:
                    break;
                case 0x29:
                    break;
                case 0x33:
                    break;
                case 0x55:
                    break;
                case 0x65:
                    break;   
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

void Chip8::cycle() {
    uint16_t opcode = fetch();
    execute(opcode);
}