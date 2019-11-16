#include "../drivers/screen.h"
#include "util.h"

void main() {
  clear_screen();

  for (int i = 0; i <= MAX_ROWS; i++) {
    kprint("--------------------------------------------------------------------------------");
  }
  kprint("a");
}
