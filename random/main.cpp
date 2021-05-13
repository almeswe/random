#include <iostream>
#include "random.h"

#define uint  unsigned int
#define ulong unsigned long long

#define FOR_I_TO_SIZE(size)			 for (size_t i = 1; i <= size; i++)
#define COUT_DATA_ENDL(data)		 std::cout << data << std::endl;
#define COUT_SEQ_OF_DATA(size, data) FOR_I_TO_SIZE(size) COUT_DATA_ENDL(data)

void gen64_test(size_t size = 25)
{
	COUT_SEQ_OF_DATA(size, random64())
}
void gen64_range_test(ulong from, ulong to, size_t size = 25)
{
	COUT_SEQ_OF_DATA(size, randrange64(from, to))
}

void gen32_range_test(uint from, uint to, size_t size = 25)
{
	COUT_SEQ_OF_DATA(size, randrange32(from, to))
}
void gen32_test(size_t size = 25)
{
	COUT_SEQ_OF_DATA(size, random32())
}

int main(int argc, char** argv)
{
	gen64_test(15);
	return 0;
}