#include "Array.hpp"
#include <iostream>

int main()
{
	try
	{
		// 1) default constructor
		Array<int> a;
		std::cout << "[default constructor] a.size()=" << a.size()
		          << " (expected 0)\n";

		// 2) size constructor
		Array<int> b(5);
		std::cout << "[size constructor] b.size()=" << b.size()
		          << " (expected 5)\n";

		// elements value-initialized
		std::cout << "b initial elements:";
		for (size_t i = 0; i < b.size(); ++i)
			std::cout << ' ' << b[i];
		std::cout << "\n";

		// modify elements
		for (size_t i = 0; i < b.size(); ++i)
			b[i] = static_cast<int>(i) + 1;
		std::cout << "b after assignment:";
		for (size_t i = 0; i < b.size(); ++i)
			std::cout << ' ' << b[i];
		std::cout << "\n";

		// 3) copy constructor (deep copy)
		Array<int> c(b);
		std::cout << "[copy ctor] c copy of b:";
		for (size_t i = 0; i < c.size(); ++i)
			std::cout << ' ' << c[i];
		std::cout << "\n";

		// changing b should not affect c
		b[0] = 100;
		std::cout << "after changing b[0]=100 -> b[0]=" << b[0]
		          << " c[0]=" << c[0] << "\n";

		// 4) operator= (deep copy)
		Array<int> e;
		e = b;
		std::cout << "[assign] e copy of b:";
		for (size_t i = 0; i < e.size(); ++i)
			std::cout << ' ' << e[i];
		std::cout << "\n";

		// 5) const access
		const Array<int> d = c;
		std::cout << "[const access] d[1]=" << d[1]
		          << " (using operator[] const)\n";

		// 6) out_of_range exception check
		try
		{
			std::cout << "Attempting out-of-range access b[10]...\n";
			std::cout << b[10] << "\n"; // should throw
			std::cerr << "ERROR: no exception thrown for out-of-range access\n";
		}
		catch (const std::out_of_range &ex)
		{
			std::cout << "Caught expected exception: " << ex.what() << "\n";
		}

		std::cout << "All tests completed successfully." << std::endl;
	}
	catch (const std::exception &ex)
	{
		std::cerr << "Unexpected exception: " << ex.what() << std::endl;
		return 1;
	}

	return 0;
}
