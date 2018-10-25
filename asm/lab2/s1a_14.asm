bits 32

global start

extern exit
import exit msvcrt.dll

segment data use32 class=data
    ;

segment code use32 class=code
start:
    ; -2 * 5
    mov AH, -2 ; AH = -2
    mov AL, 5  ; AL = 5
    mul AH    ; AX = -2 * 5

    push    dword 0
    call    [exit]
