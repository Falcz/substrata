#include "../drivers/screen.h"
#include "util.h"

void main() {
  clear_screen();

  int i = 0;
  while (1) {
    char c[20];
    int_to_ascii(i, c);
    kprint(c);
    i++;
    }
}
