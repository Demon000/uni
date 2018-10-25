bits 32

global start

extern exit
import exit msvcrt.dll

segment data use32 class=data
    a DB 1
    b DB 1
    c DB 1
    d DB 1

segment code use32 class=code
start:
    ; (a + d - c) - (b + b)
    mov AL, [a] ; AL = a
    mov AH, [d] ; AH = b
    add AL, AH  ; AL = a + b
    mov AH, [c] ; AH = c
    sub AL, AH  ; AL = a + b - c

    mov BL, [b] ; BL = b
    mov BH, [b] ; BH = b
    sub BL, BH  ; BL = b + b

    sub AL, BL  ; AL = (a + b - c) - (b + b)

    push    dword 0
    call    [exit]
