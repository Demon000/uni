bits 32

global start        

extern exit
extern printf

import exit msvcrt.dll
import printf msvcrt.dll

; Sa se construiasca sirul D prin concatenarea elementelor de pe pozitiile multiplu de 3 din sirul S1 cu elementele sirului S2 in ordine inversa.
; S1: '+', '4', '2', 'a', '8', '4', 'X', '5'
; S2: 'a', '4', '5'
; D: '+', 'a', 'X', '5', '4', 'a'

segment data use32 class=data
    s1 db '+', '4', '2', 'a', '8', '4',  'X', '5'
    len_s1 equ $ - s1

    s2 db 'a', '4', '5'
    len_s2 equ $ - s2

    len_d equ ((len_s1 - 1) / 3) + 1 + len_s2
    d times len_d db 0

segment code use32 class=code
    start:
        mov eax, len_d
        mov eax, 0

        mov esi, 0
        start_first_loop:
            mov bl, [s1 + esi]
            mov [d + eax], bl
            add esi, 3
            inc eax
        cmp esi, len_s1
        jl start_first_loop

        mov esi, len_s2
        start_second_loop:
            mov bl, [s2 + esi - 1]
            mov [d + eax], bl
            inc eax
            dec esi
        cmp esi, 0
        jne start_second_loop
        
        push    dword 0
        call    [exit]
