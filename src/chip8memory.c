#include "chip8memory.h"
#include <assert.h>

static void chip8_is_memory_in_bounds(int index)
// checks to see if the memory can fit. If it can't, it throws an error and terminates the program
{
    assert(index >= 0 && index < CHIP8_MEMORY_SIZE);
}

void chip8_memory_set(struct chip8_memory *memory, int index, unsigned char value)
{
    chip8_is_memory_in_bounds(index);
    memory->memory[index] = value;
}

unsigned char chip8_memory_get(struct chip8_memory *memory, int index)
{
    chip8_is_memory_in_bounds(index);
    return memory->memory[index];
}