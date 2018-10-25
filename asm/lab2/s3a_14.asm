bits 32

global start

extern exit
import exit msvcrt.dll

segment data use32 class=data
    a DB 1
    b DB 1
    c DB 1
    d DW 1
    r DW 0

segment code use32 class=code
start:
    ; (d - b * c + b * 2) / a
    mov AX, [d] ; AX = d
    mov [r], AX ;  r = d
    
    mov AH, [b] ; AH = b
    mov AL, [c] ; AL = c
    mul AH      ; AX = b * c
    sub [r], AX ;  r = d - b * c

    mov AH, [b] ; AH = b
    mov AL, 2   ; AL = 2
    mul AH      ; AX = b * 2
    add [r], AX ;  r = d - b * c + b * 2

    mov AX, [r] ; AX = d - b * c + b * 2
    mov BL, [a] ; BL = a
    div BL      ; AL = (d - b * c + b * 2) / a

    push    dword 0
    call    [exit]
