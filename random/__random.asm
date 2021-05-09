.586
.model flat, C
.stack 100h

.code

pshtap macro src, bit						; pushes specified bit to the ebx register through carry flag
	bt  src, bit
	adc ebx, 0
endm
		
xortap macro src, bit						; xors pushed tap with tap in ebx
	pshtap src, bit
	and ebx, 1
endm
											; ---ARGS---
											; DWORD - seed
__random32 proc

	push ebp
	mov  ebp, esp

	mov eax, [ebp + 8]						; seed

	cmp eax, 0								; dead case when this algorithm returns 0 all time, we must avoid calculations
	je	exit32
											; this realization (32 bit size) uses this taps for the best period (2^n-1): 
											; 32, 22, 2, 1 (https://www.xilinx.com/support/documentation/application_notes/xapp052.pdf)

	mov ecx, 32								
	LFSR32:									; in every iteration it generated next pseudorandom number from the sequence

		xor	   ebx, ebx						; in this realization ebx - buffer for all calculations with CF(carry flag)
		pshtap eax, 31
		xortap eax, 21
		xortap eax, 1
		xortap eax, 0
		shl    eax, 1						; shift bits to the left side for escaping 0 bit of eax, that will be used by the new xored bit
		or     eax, ebx						; set new xored bit as 0 bit of eax 

	loop LFSR32

	exit32:
		pop ebp
		ret									; return is: preusdorandom 32bit number from sequence in eax

__random32 endp

											; ---ARGS---
											; DWORD - lowr_seed
											; DWORD - high_seed
__random64 proc

	push ebp
	mov  ebp, esp

	mov eax, [ebp+8]						; lower 32 pack of bits
	mov edx, [ebp+12]						; higher 32 pack

	mov ebx, edx
	or  ebx, eax
	cmp ebx, 0								; the same idea like in 32bit variant, but here i check two registers (because i get number from rdtsc divided between edx & eax)
	je  exit64

	mov ecx, 64
	LFSR64:

		xor    ebx, ebx						; for 64bit realization i use: 64, 63, 61, 60 taps (https://www.xilinx.com/support/documentation/application_notes/xapp052.pdf)
		pshtap edx, 31
		xortap edx, 30
		xortap edx, 28
		xortap edx, 27
		shl    eax, 1						; then i shift lower part of number 
		rcl    edx, 1						; and here i shift with CF high bits 
		or     eax, ebx						; then i set the xored taps as 0 in register with lower bits

	loop LFSR64

	exit64:
		pop ebp
		ret									; return is: preusdorandom 64bit number from sequence in :
											;															-edx high  32bits of number
											;															-eax lower 32bits

__random64 endp

end