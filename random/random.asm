.586
.model flat
.stack 100h

.data

.code

                        ; int from
                        ; int to
__randrange proc

	push ebp            ; save old base pointer
	mov  ebp, esp       ; use current stack pointer as new base

	call __random_rdtsc ; get random number in eax
	mov  ebx, [ebp+8]   ; to
	mov  ecx, [ebp+12]  ; from

	sub  ebx, ecx       ; implementing normalizaton formula : rand % (to - from + 1) + from
	add  ebx, 1
		
	xor  edx, edx
	div  ebx
	mov  eax, edx
	add  eax, ecx
	
	pop  ebp
	ret

__randrange endp

__random_rdtsc proc

	rdtsc               ; get CPU cycles from the last restart (edx -> first 32bit, eax -> second 32bit)
	mov  ecx, 32        ; count of loop iterations for LFSR algorithm processing

	cmp  eax, 0h        ; situation when xor returns 0 all time -> skip it
	je	 exit

	LFSR:
		xor  ebx, ebx   ; clear the ebx register
		bt   eax, 31    ; get value of the 32th bit of eax
		rcl  ebx, 1     ; append it to the cleared ebx register
		bt   eax, 27    ; test 28th bit of eax
		adc  ebx, 0	    ; ebx + 0 + CF (carry flag received from 28th bit) 
		and  ebx, 1     ; implementing xor through add+and
		shl  eax, 1     ; shift to left by 1
		or   eax, ebx   ; set ebx (xored value) as eax's first bit
	loop LFSR

	exit:
		ret             ; eax - pseudo random number

__random_rdtsc  endp

main proc

	push 10
	push 21
	call __randrange
	ret

main endp

end main