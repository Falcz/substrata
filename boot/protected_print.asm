[bits 32]
VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f

print_string_pm:
  pusha
  mov edx, VIDEO_MEMORY
  print_string_next_char_pm:
    mov al, [ebx]
    mov ah, WHITE_ON_BLACK
    mov [edx], ax
    add ebx, 1
    add edx, 2
    cmp al, 0
    jnz print_string_next_char_pm
  popa
  ret
