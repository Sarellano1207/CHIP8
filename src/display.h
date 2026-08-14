#ifndef DISPLAY_H
#define DISPLAY_H

#include "raylib.h"
#include <cstdint>

class Display {
private:

public:
    Display(int width, int height, int scale, uint8_t display[]);
};

#endif