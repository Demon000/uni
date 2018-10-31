bits 32

global start        

extern exit
import exit msvcrt.dll

segment data use32 class=data
    a DB 1
    b DW 1
    c DD 2
    x DQ 2

    r DQ 0

segment code use32 class=code
    start:
        ; x + (2 - a * b) / (a * 3) - a + c

        ; ecx = 2
        mov ecx, 2
        
        ; ax = a
        mov ax, 0
        mov al, [a]

        ; bx = b
        mov bx, [b]

        ; dx:ax = a * b
        mul bx

        ; eax = a * b
        push dx
        push ax
        pop eax

        ; ecx = 2 - a * b
        sub ecx, eax

        ; ax = a
        mov ax, 0
        mov al, [a]

        ; dx:ax = a * 3
        mov bx, 3
        mul bx
    
        ; ebx = a * 3
        push dx
        push ax
        pop ebx

        ; edx:eax = 2 - a * b
        mov edx, 0
        mov eax, ecx

        ; eax = (2 - a * b) / (a * 3)
        div ebx

        ; ecx:ebx = x
        mov ebx, dword[x]
        mov ecx, dword[x + 4]

        ; ecx:ebx = x + (2 - a * b) / (a * 3)
        add ebx, eax
        adc ecx, 0

        ; eax = a
        mov eax, 0
        mov al, [a]

        ; ecx:ebx = x + (2 - a * b) / (a * 3) - a
        add ebx, eax
        adc ecx, 0

        ; eax = c
        mov eax, [c]

        ; ecx:ebx = x + (2 - a * b) / (a * 3) - a + c
        add ebx, eax
        adc ecx, 0

        push    dword 0
        call    [exit]
