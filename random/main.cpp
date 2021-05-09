#include <iostream>
#include "random.h"

#define uint  unsigned int
#define ulong unsigned long long

#define for_i_to_size(size)				  for (size_t i = 1; i <= size; i++)
#define cout_data_endl(data)			  std::cout << data << std::endl;
#define cout_sequence_of_data(size, data) for_i_to_size(size) cout_data_endl(data)

void gen64_test(size_t size = 25)
{
	cout_sequence_of_data(size, random64())
}
void gen64_range_test(ulong from, ulong to, size_t size = 25)
{
	cout_sequence_of_data(size, randrange64(from, to))
}

void gen32_range_test(uint from, uint to, size_t size = 25)
{
	cout_sequence_of_data(size, randrange32(from, to))
}
void gen32_test(size_t size = 25)
{
	cout_sequence_of_data(size, random32())
}

int main(int argc, char** argv)
{
	gen64_range_test(0, 10, 123);
	return 0;
}