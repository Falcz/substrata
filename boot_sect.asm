; Set Teletype Mode
mov ah, 0x0e
  
; Write 'ok'
mov al, 'o'
int 0x10
mov al, 'k'
int 0x10

; Infinite loop
jmp $

; Padding
times 510-($-$$) db 0

; Set boot sector flag
dw 0xaa55
