; File: prt_dec.asm
; Author: Sam Everett
; Project 3
; Last Updated: 03/28/2017
; CMSC 313
; Email: eversam1@umbc.edu
	;; This file contains the subroutine (globalized) to be used in the
	;; mytest3 file.  It's main functionality is to print an input of
	;; numbers as a string.  The input comes from the stack.

%define STDIN 0
%define STDOUT 1
%define SYSCALL_READ  3
%define SYSCALL_WRITE 4
%define BUFLEN 256


        SECTION .data                   ; initialized data section

        SECTION .bss                    ; uninitialized data section
newstr: resb BUFLEN                     ; converted string


        SECTION .text                   ; Code section.

	global prt_dec
prt_dec:	

        
L1_init:
	push	edi
        mov     edi, newstr             ; point to start of new string
	push	eax
	mov	eax, [esp+12]
	push	ecx
	mov	ecx, 10
	push	ebx
	mov	ebx, 0
	push	edx
	
L1_top:

	mov	edx, 0
	div	ecx
	
L1_cont:
	inc	ebx
	add	edx, 48
	push 	edx
	cmp	eax,0
        ja     L1_top                  ; loop to top if more chars

createStringLoop:
	mov	ecx, 0
	cmp	ebx, 0
	je	loopFinish
	dec	ebx
	pop	ecx
	mov	[edi], ecx
	inc	edi
	jmp	createStringLoop
	

loopFinish:

        mov     eax, SYSCALL_WRITE      ; write out string
        mov     ebx, STDOUT
	mov     ecx, newstr
        mov     edx, edi
	sub	edx, ecx
        int     080h

        ; final exit
        ;
exit:
	pop	edx
	pop	ebx
	pop	ecx
	pop	eax
	pop	edi
	ret
	