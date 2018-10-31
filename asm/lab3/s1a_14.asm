bits 32

global start        

extern exit
import exit msvcrt.dll

segment data use32 class=data
    a DB 1
    b DW 1
    c DD 2
    d DQ 2

segment code use32 class=code
    start:
        ; (a + d) - (c - b) + c

        mov eax,0
        mov edx,0
        mov al, [a]
        
        ; edx:eax = a + d
        add eax, dword [d]
        adc edx, dword [d + 4]        

        ; ebx = c
        mov ebx, [c]

        ; ecx = b
        mov ecx, 0
        mov cx, [b]

        ; ebx = c - b
        sub ebx, ecx

        ; edx:eax = (a + d) - (c - b)
        sub eax, ebx
        sbb edx, 0

        ; edx:eax = (a + d) - (c - b) + c
        add eax, [c]
        adc edx, 0

        push    dword 0
        call    [exit]
