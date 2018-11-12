bits 32

global start        

extern exit
extern printf

import exit msvcrt.dll
import printf msvcrt.dll

; Dandu-se un sir de cuvinte, sa se calculeze cel mai lung subsir de cuvinte ordonate crescator din acest sir. 

segment data use32 class=data
    words dw 'ab', 'bc', 'cd', '1', '2', '3', '4', '5', 'aa', 'bb', 'cc', 'dd'
    words_length equ ($ - words) / 2

    current_address dd words
    longest_address dd words

    current_length dw 1
    longest_length dw 1


segment code use32 class=code
    start:
        mov esi, words + 2
        mov edi, words
        mov ecx, 0

    start_compare_loop:
        cmp ecx, words_length
        je end_compare_loop
        add ecx, 1
        
        cmpsw

        jge fi_end_sequence
    
    ;if_end_sequence:
        mov ax, [current_length]
        mov bx, [longest_length]
        cmp ax, bx

        jle fi_replace_longest_sequence

    ;if_replace_longest_sequence:
        mov eax, [current_address]
        mov [longest_address], eax

        mov ax, [current_length]
        mov [longest_length], ax
    fi_replace_longest_sequence:

        mov [current_address], edi
        mov word[current_length], 0
    fi_end_sequence:

        add word[current_length], 1
        jmp start_compare_loop
    end_compare_loop:
        
        push    dword 0
        call    [exit]
