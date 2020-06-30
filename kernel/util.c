void memory_copy(char *source, char *dest, int nbytes) {
  for (int i = 0; i < nbytes; i++) {
    dest[i] = source[i];
  }
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
