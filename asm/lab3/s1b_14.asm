bits 32

global start        

extern exit
import exit msvcrt.dll

segment data use32 class=data
    a DB 1
    b DW 1
    c DD 5

segment code use32 class=code
    start:
        ; c - b - (a + a) - b

        ; ebx = c
        mov ebx, [c]

        ; ax = b
        mov ax, [b]

        ; eax = b
        cwd
        push dx
        push ax
        pop eax

        ; ebx = c - b
        sub ebx, eax

        ; al = a
        mov al, [a]

        ; ax = a
        cbw

        ; eax = a + a
        cwd
        push dx
        push ax
        pop eax

        ; eax = a + a
        add eax,eax

        ; ebx = c - b - (a + a)
        sub ebx, eax

        ; ax = b
        mov ax, [b]

        ; eax = b
        cwd
        push dx
        push ax
        pop eax

        ; ebx = c - b - (a + a) - b
        sub ebx, eax

        push    dword 0
        call    [exit]
