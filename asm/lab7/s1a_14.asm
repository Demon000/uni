bits 32

global start        

extern exit
extern printf
extern scanf
import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll

segment data use32 class=data
    input_a_message db "a (hex) = ", 0
    input_b_message db "b (hex) = ", 0
    input_number_format db "%x", 0
    print_apb_message db "a + b = %d", 0
    a dd 0
    b dd 0
    apb dd 0

segment code use32 class=code
    start:
        ; Sa se citeasca de la tastatura doua numere a si b (in baza 16) si sa se calculeze a+b. Sa se afiseze rezultatul adunarii in baza 10.
        push dword input_a_message
        call [printf]
        add esp, 4 * 1

        push dword a
        push dword input_number_format
        call [scanf]
        add esp, 4 * 2
        mov eax, [a]

        push dword input_b_message
        call [printf]
        add esp, 4 * 1

        push dword b
        push dword input_number_format
        call [scanf]
        add esp, 4 * 2

        mov eax, [a]
        mov ebx, [b]
        add eax, ebx
        mov [apb], eax

        push dword [apb]
        push dword print_apb_message
        call [printf]
        add esp, 4 * 2

        push    dword 0
        call    [exit]
