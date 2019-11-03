[org 0x7c00]

mov bx, hello
call print_string

mov dx, 0xbf38
call print_hex

mov dx, 0x0000
call print_hex

mov dx, 0x9999
call print_hex

mov dx, 0xAAAA
call print_hex

mov dx, 0xFFFF
call print_hex

jmp $

%include "print.asm"

hello:
  db "Testing String Print",0

times 510-($-$$) db 0
dw 0xaa55
