#include "../drivers/screen.h"
#include "util.h"
#include "../cpu/isr.h"
#include "../cpu/timer.h"
#include "../drivers/keyboard.h"

void main() {
  clear_screen();

  // Setup interrupts
  isr_install();

  // Enable interrupts and setup timer
  asm volatile("sti");
  // init_timer(50);
  init_keyboard();
}
