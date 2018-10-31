bits 32

global start        

extern exit
import exit msvcrt.dll

segment data use32 class=data
    a dw 0111011101010111b
    b dd 0

segment code use32 class=code
; Se da un cuvant A. Sa se obtina dublucuvantul B astfel:
;    bitii 28-31 ai lui B sunt 1;
;    bitii 24-25 si 26-27 ai lui B sunt bitii 8-9 ai lui A
;    bitii 20-23 ai lui B sunt bitii 0-3 inversati ca valoare ai lui A ;
;    bitii 16-19 ai lui B sunt biti de 0
;    bitii 0-15 ai lui B sunt identici cu bitii 16-31 ai lui B.

    start:
        mov ebx, 0

        mov eax, 0
        mov ax, [a]

        or ebx, 11110000000000000000000000000000b

        and eax, 00000000000000000000001100000000b

        mov cl, 16
        rol eax, cl
        or ebx, eax
        
        mov cl, 2
        rol eax, cl
        or ebx, eax

        mov eax, 0
        mov ax, [a]

        and eax, 00000000000000000000000000001111b
        not eax
        mov cl, 20
        rol eax, cl
        or ebx, eax
        
        mov ecx, ebx
        mov cl, 16
        ror ecx, cl
        and ecx, 00000000000000001111111111111111b
        or ebx, ecx
        
        mov [b], ebx

        push    dword 0
        call    [exit]
