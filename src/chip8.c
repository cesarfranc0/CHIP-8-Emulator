#include "chip8.h"
#include <memory.h>
#include <assert.h>

const char chip8_defualt_character_set[] = {
    0xf0, 0x90, 0x90, 0x90, 0xf0, // creates a drawing of 0
    0x20, 0x60, 0x20, 0x20, 0x70, // creates a drawing of 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80, // F
};
void chip8_init(struct chip8 *chip8)
{
    memset(chip8, 0, sizeof(struct chip8));
    memcpy(&chip8->memory.memory, chip8_defualt_character_set, sizeof(chip8_defualt_character_set));
}

void chip8_load(struct chip8 *chip8, const char *buffer, size_t size)
{
    assert(size + CHIP8_LOAD_ADDRESS < CHIP8_MEMORY_SIZE);
    memcpy(&chip8->memory.memory[CHIP8_LOAD_ADDRESS], buffer, size);
    chip8->registers.program_counter = CHIP8_LOAD_ADDRESS; // indicates to the chip8 that it is ready to begin the program
}

static void chip8_exec_extended(struct chip8 *chip8, unsigned short opcode)
{
    unsigned short nnn = opcode & 0x0fff;
    unsigned char x = (opcode >> 8) & 0x000f;
    unsigned char kk = opcode & 0x00ff;
    switch (opcode & 0xf000)
    {
    case 0x1000: // jump to address nnn
        chip8->registers.program_counter = nnn;
        break;

    case 0x2000: // calls the address as well as subroutine at nnn
        chip8_stack_push(chip8, chip8->registers.program_counter);
        chip8->registers.program_counter = nnn;
        break;

    case 0x3000: // skip next instruction if V[x] == kk
        if (chip8->registers.V[x] == kk)
        {
            chip8->registers.program_counter += 2;
        }
        break;

    default:
        break;
    }
}

void chip8_exec(struct chip8 *chip8, unsigned short opcode)
{
    switch (opcode)
    {
    case 0x00E0: // clears the display
        chip8_screen_clear(&chip8->screen);
        break;

    case 0x00EE: // returns from the subroutine
        chip8->registers.program_counter = chip8_stack_pop(&chip8);
        break;

    default:
        chip8_exec_extended(chip8, opcode);
    }
}
