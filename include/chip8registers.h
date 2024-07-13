#ifndef CHIP8REGISTERS_H
#define CHIP8REGISTERS_H

#include "config.h"

struct chip8_registers
{
    unsigned char V[CHIP8_TOTAL_DATA_REGISTERS]; // general purpose data registers
    unsigned short I;                            // register to store memory addresses
    unsigned char delay_timer;
    unsigned char sound_timer;
    unsigned short program_counter; // register that uses a pointer to a currently executing address in the program's memory which is then incremented to proceed to the next instruction
    unsigned char stack_pointer;    // points to the top of the stack which returns addresses when subroutines are called
};

#endif