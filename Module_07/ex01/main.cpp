#include <iostream>
#include <string>
#include "iter.hpp"

template <typename T>
void printElement(const T &element)
{
	std::cout << element << std::endl;
}

template <typename T>
void incrementElement(T &element)
{
	++element;
}

void appendMarker(std::string &element)
{
	element += "!";
}

int main(void)
{
	int ints[] = {1, 2, 3, 4};
	float floats[] = {1.5f, 2.5f, 3.5f};
	std::string strings[] = {"hola", "42", "cpp"};

	std::cout << "--- int array before ---" << std::endl;
	iter(ints, 4, printElement<int>);
	iter(ints, 4, incrementElement<int>);
	std::cout << "--- int array after increment ---" << std::endl;
	iter(ints, 4, printElement<int>);

	std::cout << "\n--- float array before ---" << std::endl;
	iter(floats, 3, printElement<float>);
	iter(floats, 3, incrementElement<float>);
	std::cout << "--- float array after increment ---" << std::endl;
	iter(floats, 3, printElement<float>);

	std::cout << "\n--- string array before ---" << std::endl;
	iter(strings, 3, printElement<std::string>);
	iter(strings, 3, appendMarker);
	std::cout << "--- string array after appendMarker ---" << std::endl;
	iter(strings, 3, printElement<std::string>);

	return (0);
}
