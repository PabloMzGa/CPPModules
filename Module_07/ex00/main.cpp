#include <iostream>
#include <string>
#include "whatever.hpp"

int main(void)
{
	int a = 2;
	int b = 3;

	std::cout << "--- int ---" << std::endl;
	std::cout << "Antes: a = " << a << ", b = " << b << std::endl;
	::swap(a, b);
	std::cout << "Despues de swap(a, b): a = " << a << ", b = " << b << std::endl;
	std::cout << "min(a, b) = " << ::min(a, b) << std::endl;
	std::cout << "max(a, b) = " << ::max(a, b) << std::endl;

	float x = 4.2f;
	float y = 1.5f;

	std::cout << "\n--- float ---" << std::endl;
	std::cout << "Antes: x = " << x << ", y = " << y << std::endl;
	::swap(x, y);
	std::cout << "Despues de swap(x, y): x = " << x << ", y = " << y << std::endl;
	std::cout << "x = " << x << ", y = " << y << std::endl;
	std::cout << "min(x, y) = " << ::min(x, y) << std::endl;
	std::cout << "max(x, y) = " << ::max(x, y) << std::endl;

	std::string s1 = "hola";
	std::string s2 = "adios";

	std::cout << "\n--- std::string ---" << std::endl;
	std::cout << "Antes: s1 = " << s1 << ", s2 = " << s2 << std::endl;
	::swap(s1, s2);
	std::cout << "Despues de swap(s1, s2): s1 = " << s1 << ", s2 = " << s2 << std::endl;
	std::cout << "s1 = " << s1 << ", s2 = " << s2 << std::endl;
	std::cout << "min(s1, s2) = " << ::min(s1, s2) << std::endl;
	std::cout << "max(s1, s2) = " << ::max(s1, s2) << std::endl;

	return (0);
}
