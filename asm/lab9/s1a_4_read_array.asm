bits 32

global read_array

extern scanf
extern printf
import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    index_numbers dd 0
    no_numbers dd 0
    number dd 0

    array_ptr dd 0

    no_mesage db "How many numbers do you want to enter?",0xa,0xd,0
    number_format db "%d", 0

segment code use32 class=code
read_array:
    mov eax, [esp + 4]
    mov dword [array_ptr], eax
    push dword no_mesage
    call [printf]
    add esp, 4 * 1

    push dword no_numbers
    push dword number_format
    call [scanf]
    add esp, 4 * 2

.start_read_array_loop:
    push dword number
    push dword number_format
    call [scanf]
    add esp, 4 * 2

    mov eax, [index_numbers]
    mov ecx, [number]
    mov ebx, [array_ptr]
    mov [ebx + eax * 4], ecx

    inc dword [index_numbers]
    mov eax, [index_numbers]
    cmp eax, [no_numbers]
    jne .start_read_array_loop
.end_read_array_loop:
    ret
