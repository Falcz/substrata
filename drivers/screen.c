#include "screen.h"
#include "ports.h"
#include "../kernel/util.h"

int get_cursor_offset();
void set_cursor_offset(int offset);

void set_char(char character, int offset) {
    char *screen = (char*) VIDEO_ADDRESS;
    screen[offset] = character;
    screen[offset + 1] = WHITE_ON_BLACK;
}

void clear_screen() {
  int screen_size = MAX_COLS * MAX_ROWS;

  for (int i = 0; i < screen_size; i++) {
    set_char(' ', i * 2);
  }

  set_cursor_offset(0);
}

int increment_offset(int offset) {
  char *screen = (char*) VIDEO_ADDRESS;
  int new_offset = offset + 2;
  if (new_offset >= MAX_COLS * MAX_ROWS  * 2) {
    int bottom = MAX_COLS * (MAX_ROWS - 1) * 2;
    memory_copy(screen + MAX_COLS * 2, screen, MAX_COLS * (MAX_ROWS - 1) * 2);

    for (int i = 0; i < MAX_COLS; i++) {
        set_char(' ', bottom + i * 2);
    }
    return bottom;
  }
  return new_offset;
}

void kprint(char *message) {
  int offset = get_cursor_offset();

  int position = 0;

  while (message[position] != 0) {
      if (message[position] == '\n') {
          int current_row = (offset / (MAX_COLS * 2)) + 1;
          offset = ((MAX_COLS * current_row) - 1) * 2;
      } else {
          set_char(message[position], offset);
      }
      offset = increment_offset(offset);
    position++;
  }

  set_cursor_offset(offset);
}

void backspace() {
    int offset = get_cursor_offset() - 2;
    set_cursor_offset(offset);
    set_char(' ', offset);
}

void kprint_at(char *message, int col, int row) {
  if (col >= MAX_COLS) {
    kprint("Maximum column position exceeded.");
    return;
  }
  if (row >= MAX_ROWS) {
    kprint("Maximum row position exceeded.");
    return;
  }
  int offset = col * 2 + row * 2 * MAX_COLS;
  set_cursor_offset(offset);

  kprint(message);
}

int get_cursor_offset() {
  port_byte_out(REG_SCREEN_CTRL, 14);
  int offset = port_byte_in(REG_SCREEN_DATA) << 8;
  port_byte_out(REG_SCREEN_CTRL, 15);
  offset += port_byte_in(REG_SCREEN_DATA);
  return offset * 2;
}

void set_cursor_offset(int offset) {
  offset /= 2;
  port_byte_out(REG_SCREEN_CTRL, 14);
  port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
  port_byte_out(REG_SCREEN_CTRL, 15);
  port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
}
