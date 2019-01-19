bits 32

global start        

extern read_array

extern exit
extern printf
extern scanf
import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll

segment data use32 public class=data
    no_numbers dd 0
    index_numbers dd 0
    index_bit db 0

    array resd 100

    hex_message db '0x%x',0
    between_message db ' 0b',0
    bin_message db '%d',0
    end_message db 0xa,0xd,0
    
segment code use32 class=code
    ; Se da un sir de numere. Sa se afiseze valorile in baza 16 si in baza 2.
    start:
        push dword array
        call read_array
        add esp, 4 * 1
        mov [no_numbers], eax

    .start_print_array_loop:
        mov eax, [index_numbers]
        push dword [array + eax * 4]
        push dword hex_message
        call [printf]
        add esp, 4 * 2

        push dword between_message
        call [printf]
        add esp, 4 * 1
        
        mov byte [index_bit], 31
    .start_print_bits_loop:
        mov eax, ebx
        mov cl, 31
        sub cl, [index_bit]
        shl eax, cl
        mov cl, 31
        shr eax, cl

        push dword eax
        push dword bin_message
        call [printf]
        add esp, 4 * 2

        sub byte [index_bit], 1
        cmp byte [index_bit], -1
        jne .start_print_bits_loop
    .end_print_bits_loop:
        push dword end_message
        call [printf]
        add esp, 4 * 1

        inc dword [index_numbers]
        mov eax, [index_numbers]
        cmp eax, [no_numbers]
        jne .start_print_array_loop
    .end_print_array_loop:

        push    dword 0
        call    [exit]
