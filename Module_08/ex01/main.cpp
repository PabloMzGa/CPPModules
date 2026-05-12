#include "Span.hpp"

#include <iostream>
#include <list>
#include <vector>

int main()
{
	try
	{
		// Test 1: direct insertion with addNumber.
		// Values: 42, 7, 100 -> sorted: 7, 42, 100
		// Shortest span: min(42 - 7 = 35, 100 - 42 = 58) = 35
		// Longest span: 100 - 7 = 93
		std::cout << "=== Test 1: addNumber ===" << std::endl;
		{
			Span span(5);

			span.addNumber(42);
			span.addNumber(7);
			span.addNumber(100);

			std::cout << "shortest span: " << span.shortestSpan() << std::endl;
			std::cout << "longest span: " << span.longestSpan() << std::endl;
		}

		// Test 2: addNumbers with vector iterators.
		// Values: 0, 2, 4, ..., 5998 (3000 numbers)
		// Shortest span: 2 because every consecutive value differs by 2
		// Longest span: 5998 - 0 = 5998
		std::cout << std::endl << "=== Test 2: vector iterators ===" << std::endl;
		{
			Span span(3000);
			std::vector<int> vectorNumbers;

			vectorNumbers.reserve(3000);
			for (int i = 0; i < 3000; ++i)
				vectorNumbers.push_back(i * 2);

			span.addNumbers(vectorNumbers.begin(), vectorNumbers.end());

			std::cout << "loaded " << vectorNumbers.size() << " numbers" << std::endl;
			std::cout << "shortest span: " << span.shortestSpan() << std::endl;
			std::cout << "longest span: " << span.longestSpan() << std::endl;
		}

		// Test 3: addNumbers with list iterators.
		// Values: 5000, 5004, 5008, ..., 9796 (1200 numbers)
		// Shortest span: 4 because every consecutive value differs by 4
		// Longest span: 9796 - 5000 = 4796
		std::cout << std::endl << "=== Test 3: list iterators ===" << std::endl;
		{
			Span span(1200);
			std::list<int> listNumbers;

			for (int i = 0; i < 1200; ++i)
				listNumbers.push_back(5000 + i * 4);

			span.addNumbers(listNumbers.begin(), listNumbers.end());

			std::cout << "loaded " << listNumbers.size() << " numbers" << std::endl;
			std::cout << "shortest span: " << span.shortestSpan() << std::endl;
			std::cout << "longest span: " << span.longestSpan() << std::endl;
		}

		// Test 4: addNumbers with raw array pointers.
		// Values: 20000, 20005, 20010, ..., 42495 (4500 numbers)
		// Shortest span: 5 because every consecutive value differs by 5
		// Longest span: 42495 - 20000 = 22495
		std::cout << std::endl << "=== Test 4: array iterators ===" << std::endl;
		{
			Span span(4500);
			int arrayNumbers[4500];

			for (int i = 0; i < 4500; ++i)
				arrayNumbers[i] = 20000 + i * 5;

			span.addNumbers(arrayNumbers, arrayNumbers + 4500);

			std::cout << "loaded 4500 numbers" << std::endl;
			std::cout << "shortest span: " << span.shortestSpan() << std::endl;
			std::cout << "longest span: " << span.longestSpan() << std::endl;
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return (1);
	}
	return (0);
}