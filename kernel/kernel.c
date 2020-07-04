#include "../drivers/ports.h"
#include "../drivers/screen.h"
#include "../libc/string.h"
#include "../cpu/isr.h"

void kernel_main() {
  clear_screen();

  // Setup interrupts
  isr_install();
  irq_install();

  screen_banner();

  kprint("Type 'exit' to shutdown or shout into the void:\n\n");
}

void handle_user_input(char input[]) {
    if (strcmp(input, "exit") == 0) {
        kprint("Shutting down...");

        // TODO: This is specific to QEMU, replace it with an ACPI Shutdown
        port_word_out(0x604, 0x2000);
    } else if (strcmp(input, "help") == 0) {
        kprint("I'm afraid you can't be helped.\n\n");
    } else {
        kprint("Unrecognised command.\n\n");
    }
}
