bits 32

global start        

extern exit
extern fopen
extern fprintf
extern scanf

import exit msvcrt.dll
import fopen msvcrt.dll
import fprintf msvcrt.dll
import scanf msvcrt.dll

segment data use32 class=data
    filename db "asc.txt", 0
    mode db "w", 0
    descriptor dd 0

    input_format db "%d", 0
    number dd 0

    output_format db "%d ", 0

segment code use32 class=code
    start:
        ; Se da un nume de fisier (definit in segmentul de date). Sa se creeze un fisier cu numele dat, apoi sa se citeasca de la tastatura numere si sa se scrie din valorile citite in fisier numerele divizibile cu 7, pana cand se citeste de la tastatura valoarea 0.
        push dword mode
        push dword filename
        call [fopen]
        add esp, 4 * 2

        mov [descriptor], eax

    start_input_number_loop:
        push dword number
        push dword input_format
        call [scanf]
        add esp, 4 * 2

        cmp dword [number], 0
        je end_input_number_loop
        
        mov eax, [number]
        cdq
        mov ecx, 7
        div ecx
        cmp edx, 0
        jne fi_write_number_to_file

    if_write_number_to_file:
        push dword [number]
        push dword output_format
        push dword [descriptor]
        call [fprintf]
        add esp, 4 * 3
    fi_write_number_to_file:

        jmp start_input_number_loop
    end_input_number_loop:

        push    dword 0
        call    [exit]
