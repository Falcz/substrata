disk_load:
  pusha
  push dx

  mov ah, 0x02                  ; BIOS read sector function
  mov al, dh                    ; Number of sectors to read
  mov ch, 0x00                  ; track number
  mov dh, 0x00                  ; head number
  mov cl, 0x02                  ; sector number

  int 0x13                      ; BIOS interrupt

  jc disk_error

  pop dx
  cmp dh, al
  jne disk_error

  popa
  ret

disk_error:
  mov bx, DISK_ERROR_MSG
  call print_string
  jmp $

DISK_ERROR_MSG db "Disk read error",0
