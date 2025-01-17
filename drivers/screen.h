#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0f

#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

#ifndef SUBTRATA_SCREEN_H
#define SUBTRATA_SCREEN_H

void clear_screen();
void kprint(char *message);
void kprint_at(char *message, int col, int row);
void kprint_backspace();
void screen_banner();

#endif //SUBTRATA_SCREEN_H
