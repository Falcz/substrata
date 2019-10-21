print_string:
  pusha
  mov ah, 0x0e
  print_string_next_char:
    mov al, [bx]
    add bx, 0x01
    cmp al, 0
    int 0x10
    jnz print_string_next_char
  popa
  ret

print_hex:
  pusha
  mov bx, HEX_OUT
  add bx, 0x01

  mov ah, dh
  call print_hex_handle_char

  mov ah, dh
  call print_hex_nibble
  call print_hex_handle_char

  mov ah, dl
  call print_hex_nibble
  call print_hex_handle_char

  mov ah, dl
  call print_hex_handle_char

  mov bx, HEX_OUT
  call print_string
  popa
  ret

; Helpers
print_hex_nibble:
  shr ax, 4
  mov ah, al
  ret

print_hex_handle_char:
  add bx, 0x01
  mov cl, '0'

  shr ah, 4
  mov al, ah
  call print_hex_set_char
  add cl, al

  mov [bx], cl
  ret

print_hex_set_char:
  cmp al, 0x0A
  jge print_hex_letter
  ret
  print_hex_letter:
    add al, 0x07
    ret

HEX_OUT:
  db '0x0000',0
