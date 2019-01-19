bits 32

global _add_char_to_number

;
; Se citeste de la tastatura un sir de mai multe numere in baza 2.
; Sa se afiseze aceste numere in baza 16.
;

segment code use32 class=code
	_add_char_to_number:
		push ebp
		mov ebp, esp

		mov eax, [ebp + 8]
		mov ebx, 2
		mul ebx

		mov bl, [ebp + 12]

		cmp bl, '1'
		jne .fi_char_is_1
	.if_char_is_1:
		inc eax
		jmp .the_end
	.fi_char_is_1:

		cmp bl, '0'
		jne .fi_char_is_0
	.if_char_is_0:
		jmp .the_end 
	.fi_char_is_0:

		mov eax, -1

	.the_end:
		pop ebp
		ret
