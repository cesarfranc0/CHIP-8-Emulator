#ifndef CHIP8REGISTERS_H
#define CHIP8REGISTERS_H

#include "config.h"

struct chip8_registers
{
    unsigned char V[CHIP8_TOTAL_DATA_REGISTERS];
    unsigned short I; // register to store memory addresses
    unsigned char delay_timer;
    unsigned char sound_timer;
    unsigned short program_counter; // register that uses a pointer to point to a specified instruction set
    unsigned char stack_pointer;
};

#endif