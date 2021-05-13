#pragma once

#include <intrin.h>

#define DWORD __int32
#define QWORD __int64
#define UDWORD unsigned DWORD
#define UQWORD unsigned QWORD

#define GET_LOWR_BITS(x) (DWORD)(x & 0xffffffff)
#define GET_HIGH_BITS(x) (DWORD)(x >> 32)

#define TO_RANGE(rand, from, to) rand % (to - from + 1) + from

extern "C" DWORD __random32(DWORD);
extern "C" QWORD __random64(DWORD, DWORD);

UQWORD seed = __rdtsc();

UDWORD random32(DWORD from = GET_LOWR_BITS(seed))
{
	return (UDWORD)(seed = __random32(from));
}
UQWORD random64(QWORD from = seed)
{
	return (UQWORD)(seed = __random64(GET_HIGH_BITS(from), GET_LOWR_BITS(from)));
}
UDWORD randrange32(DWORD from, DWORD to)
{
	return (UDWORD)(TO_RANGE(random32(), from, to));
}
UQWORD randrange64(QWORD from, QWORD to)
{
	return (UQWORD)(TO_RANGE(random64(), from, to));
}