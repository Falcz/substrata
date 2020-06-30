#include "keyboard.h"
#include "../drivers/ports.h"
#include "../drivers/screen.h"
#include "../cpu/isr.h"
#include "../kernel/util.h"

#define SC_MAX 57
const char sc_ascii[] = { '?', '?', '1', '2', '3', '4', '5', '6',
                          '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y',
                          'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G',
                          'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V',
                          'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '};

static void keyboard_callback(registers_t regs) {
    u8 input = port_byte_in(0x60);
    char input_char = sc_ascii[(int)input];

    if (input > SC_MAX) return;

    kprint("Keyboard input: ");
    char str[2] = {input_char, '\0'};
    kprint(str);
    kprint("\n");
}

void init_keyboard() {
    register_interrupt_handler(IRQ1, &keyboard_callback);
}
