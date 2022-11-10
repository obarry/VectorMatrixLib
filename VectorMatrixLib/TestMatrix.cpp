#include <iostream>
#include "Matrix3f.h"
#include "Vector3f.h"

using namespace vectormatrix;

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
	float f = 0.5f;
	std::cout << "Multiplying by float : " << f << std::endl;
	p.times(f);
	std::cout << p << std::endl;

	std::cout << "Test Vector3f" << std::endl;
	Vector3f v1(5);
	Vector3f v2(2, 3, 4);
	std::cout << "Vector v1: " << v1 << std::endl;
	std::cout << "Vector v2: " << v2 << std::endl;
	std::cout << "dot product: v1.v2 = " << v1 * v2 << std::endl;
	v2*=2;
	std::cout << "v2.timesEquals(2): " << v2 << std::endl;
	Vector3f v3 = v1*11;
	std::cout << "v3 = v1.times(11): " << v3 << std::endl;
	std::cout << "v1 length: " << v1.length() << std::endl;
	std::cout << "v2 length: " << v2.length() << std::endl;
	std::cout << "v3 length: " << v3.length() << std::endl;
	v2.normalize();
	std::cout << "Normalized v2: " << v2 << std::endl;
	std::cout << "Normalized v2 length: " << v2.length() << std::endl;
}