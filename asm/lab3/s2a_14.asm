bits 32

global start        

extern exit
import exit msvcrt.dll

segment data use32 class=data
    a DB 1
    b DW 1
    c DD 2
    x DQ 2

segment code use32 class=code
    start:
        ; x + (2 - a * b) / (a * 3) - a + c

        ; ecx = 2
        mov ecx, 2
        
        ; ax = a
        mov al, [a]
        cbw

        ; bx = b
        mov bx, [b]

        ; dx:ax = a * b
        imul bx

        ; eax = a * b
        push dx
        push ax
        pop eax

        ; ecx = 2 - a * b
        sub ecx, eax

        ; ax = a
        mov al, [a]
        cbw

        ; dx:ax = a * 3
        mov bx, 3
        imul bx
    
        ; ebx = a * 3
        push dx
        push ax
        pop ebx

        ; edx:eax = 2 - a * b
        mov eax, ecx
        cdq

        ; eax = (2 - a * b) / (a * 3)
        idiv ebx

        ; ecx:ebx = x
        mov ebx, dword[x]
        mov ecx, dword[x + 4]

        ; ecx:ebx = x + (2 - a * b) / (a * 3)
        add ebx, eax
        adc ecx, edx

        ; dx:ax = a
        mov al, [a]
        cbw
        cwd

        ; eax = a
        push dx
        push ax
        pop eax
        cdq

        ; ecx:ebx = x + (2 - a * b) / (a * 3) - a
        add ebx, eax
        adc ecx, edx

        ; eax = c
        mov eax, [c]
        cdq
        ; ecx:ebx = x + (2 - a * b) / (a * 3) - a + c
        add ebx, eax
        adc ecx, edx

        push    dword 0
        call    [exit]
