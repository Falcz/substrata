#include "keyboard.h"
#include "../drivers/ports.h"
#include "../drivers/screen.h"
#include "../cpu/isr.h"
#include "../kernel/kernel.h"
#include "../libc/string.h"

#define SC_MAX 57
#define BACKSPACE 14
#define ENTER 28
#define SHIFT_ON 42
#define SHIFT_OFF 170

static const char sc_ascii[] = { '?', '?', '1', '2', '3', '4', '5', '6',
                          '7', '8', '9', '0', '-', '=', '?', '?', 'q', 'w', 'e', 'r', 't', 'y',
                          'u', 'i', 'o', 'p', '[', ']', '?', '?', 'a', 's', 'd', 'f', 'g',
                          'h', 'j', 'k', 'l', ';', '\'', '`', '?', '\\', 'z', 'x', 'c', 'v',
                          'b', 'n', 'm', ',', '.', '/', '?', '?', '?', ' '};
static const char sc_shifted_ascii[] = { '?', '?', '!', '@', '#', '$', '%', '^',
                                  '&', '*', '(', ')', '_', '+', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y',
                                  'U', 'I', 'O', 'P', '{', '}', '?', '?', 'A', 'S', 'D', 'F', 'G',
                                  'H', 'J', 'K', 'L', ':', '\"', '~', '?', '|', 'Z', 'X', 'C', 'V',
                                  'B', 'N', 'M', '<', '>', '?', '?', '?', '?', ' '};

static _Bool shifted = 0;
static char buffer[256];

static void clear_buffer() {
    buffer[0] = '\0';
}

static void keyboard_callback(registers_t regs) {
    u8 input = port_byte_in(0x60);

    switch (input) {
        case ENTER:
            kprint("\n");
            handle_user_input(buffer);
            clear_buffer();
            break;
        case BACKSPACE:
            kprint_backspace();
            backspace(buffer);
            break;
        case SHIFT_ON:
            shifted = 1;
            break;
        case SHIFT_OFF:
            shifted = 0;
            break;
        default:
            if (input > SC_MAX) return;

            const char *ascii_set = shifted ? sc_shifted_ascii : sc_ascii;
            char input_char = ascii_set[(int) input];
            char str[2] = {input_char, '\0'};
            append(buffer, input_char);
            kprint(str);
    }
}

void init_keyboard() {
    clear_buffer();
    register_interrupt_handler(IRQ1, &keyboard_callback);
}
