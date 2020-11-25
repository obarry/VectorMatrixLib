#include <iostream>
#include "Matrix3f.h"

int main()
{
	std::cout << "Test Matrix3f" << std::endl;
	Matrix3f m(7);
	m.set(1, 1, 9);
	std::cout << m << std::endl;
	std::cout << "Multiply with matrice:" << std::endl;
	Matrix3f n(4);
	std::cout << n << std::endl;
	std::cout << "Resulting in:" << std::endl;
	Matrix3f p = m.times(n);
	std::cout << p << std::endl;
}