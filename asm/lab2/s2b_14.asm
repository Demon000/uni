bits 32

global start

extern exit
import exit msvcrt.dll

segment data use32 class=data
    a DW 1
    b DW 1
    c DW 1
    d DW 1

segment code use32 class=code
start:
    ; (c + d) + (a - b) + a
    mov AX, [c] ; AX = c
    mov BX, [d] ; BX = d
    add AX, BX  ; AX = c + d

    mov BX, [a] ; BX = a
    mov CX, [b] ; CX = b
    sub BX, CX  ; BX = a - b

    add AX, BX  ; AX = (c + d) + (a - b)

    mov BX, [a] ; BX = a
    add AX, BX  ; AX = (c + d) + (a - b) + a

    push    dword 0
    call    [exit]
