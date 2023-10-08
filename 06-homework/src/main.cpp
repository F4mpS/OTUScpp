#include "matrix.h"    

#include <cstddef>
#include <iostream>

int main()
{
	Matrix<int, 0> m;

	for (std::size_t a = 0; a < 10; a++)
		m[a][a] = a;

	for (std::size_t a = 0; a < 10; a++)
		m[a][9 - a] = a;

	for (std::size_t a = 1; a < 9; a++)
	{
		for (std::size_t b = 1; b < 9; b++)
			std::cout << m[a][b] << " ";
		std::cout << std::endl;
	}
	std::cout << std::endl;

	std::cout << m.Size() << std::endl << std::endl;

	for (auto it = m.begin(); it != m.end(); ++it) 
	{
		std::cout << '[' << std::get<0>(*it) << ']' << '[' << std::get<1>(*it) << "] = " << std::get<2>(*it) << std::endl;
	}
}