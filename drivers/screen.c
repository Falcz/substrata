#include "screen.h"
#include "ports.h"

void clear_screen() {
  int screen_size = MAX_COLS * MAX_ROWS;
  char *screen = (char*) VIDEO_ADDRESS;

  for (int i = 0; i < screen_size; i++) {
    screen[i * 2] = ' ';
    screen[i * 2 + 1] = WHITE_ON_BLACK;
  }

  set_cursor_offset(0);
}

void kprint(char *message) {
  int offset = get_cursor_offset();
  char *screen = (char*) VIDEO_ADDRESS;

  int position = 0;

  while (message[position] != 0) {
    screen[offset + position * 2] = message[position];
    screen[offset + position * 2 + 1] = WHITE_ON_BLACK;
    position++;
  }

  set_cursor_offset(offset + position * 2);
}

void kprint_at(char *message, int col, int row) {
  // TODO
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

