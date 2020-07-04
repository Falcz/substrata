#include "string.h"

void append(char s[], char c) {
    int length = strlen(s);
    s[length] = c;
    s[length + 1] = '\0';
}

void backspace(char s[]) {
    int length = strlen(s);
    s[length - 1] = '\0';
}

void int_to_ascii(int n, char str[]) {
    int pos = 1;
    str[0] = '\0';
    while (n > 0) {
        int low = n % 10;
        n /= 10;
        str[pos] = '0' + low;
        pos++;
    }

    for (int i = 0; i < pos / 2; i++) {
        int temp = str[i];
        str[i] = str[pos - i - 1];
        str[pos - i - 1] = temp;
    }
}

int strcmp(char a[], char b[]) {
    int i;
    for (i = 0; a[i] == b[i]; i++) {
        if (a[i] == '\0')
            return 0;
    }
    return a[i] - b[i];
}

int strlen(char s[]) {
    int length = 0;

    while (s[length] != '\0')
        length++;

    return length;
}
