bits 32

global start

extern exit
import exit msvcrt.dll

segment data use32 class=data
    a DB 1
    b DB 1
    c DB 1
    d DB 1

    e DW 1
    f DW 1
    g DW 1
    h DW 2

segment code use32 class=code
start:
    ; a * d * e / (f - 5) 

    mov AL, [a] ; AL = a
    mov AH, [d] ; AH = b
    mul AH      ; AX = a * b

    mov BX, [e] ; BX = e
    mul BX      ; DX.AX = a * b * e

    mov BX, [f] ; BX = f
    sub BX, 5   ; BX = f - 5

    div BX      ; AX = a * b * e / (f - 5)

    push    dword 0
    call    [exit]
