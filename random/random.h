#pragma once

#include <intrin.h>

#define DWORD unsigned int
#define QWORD unsigned long long

#define GET_LOWR_BITS(x) (DWORD)(x & 0xffffffff)
#define GET_HIGH_BITS(x) (DWORD)(x >> 32)

#define TO_RANGE(rand, from, to) rand % (to - from + 1) + from

extern "C" DWORD __random32(DWORD);
extern "C" QWORD __random64(DWORD, DWORD);

unsigned long long __seed = __rdtsc();

DWORD random32(DWORD from = GET_LOWR_BITS(__seed))
{
	DWORD rnum32 = 0;
	__asm
	{
		push from
		call __random32
		add  esp, 4

		mov rnum32, eax
	}
	__seed = rnum32;
	return rnum32;
}
QWORD random64(QWORD from = __seed)
{
	QWORD rnum64 = 0;
	DWORD lowr_part = GET_LOWR_BITS(from);
	DWORD high_part = GET_HIGH_BITS(from);
	__asm
	{
		push high_part
		push lowr_part
		call __random64
		add  esp, 8

		; it does not work
		; mov dword ptr[rnum64], edx
		; shl qword ptr[rnum64], 32
		; or  dword ptr[rnum64], eax

		mov lowr_part, eax
		mov high_part, edx
	}
	rnum64 = (rnum64 = high_part) << 32 | lowr_part;
	__seed = rnum64;
	return rnum64;
}
DWORD randrange32(DWORD from, DWORD to)
{
	return (DWORD)(TO_RANGE(random32(), from, to));
}
QWORD randrange64(QWORD from, QWORD to)
{
	return (QWORD)(TO_RANGE(random64(), from, to));
}