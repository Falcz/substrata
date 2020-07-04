#include "timer.h"
#include "../drivers/ports.h"
#include "../drivers/screen.h"
#include "../cpu/isr.h"

u32 tick = 0;

static void timer_callback(registers_t regs) {
    tick++;
}

void init_timer(u32 frequency) {
    register_interrupt_handler(IRQ0, &timer_callback);

    // The Programmable Timer Interface has a frequency of 1.1931816666MHz
    u32 divisor = 1193180/frequency;

    // Set the timer to repeating mode
    port_byte_out(0x43, 0x36);

    port_byte_out(0x40, low_8(divisor));
    port_byte_out(0x40, high_8(divisor));
}
