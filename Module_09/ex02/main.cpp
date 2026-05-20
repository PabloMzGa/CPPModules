#include "PmergeMe.hpp"
#include <iostream>
#include <sstream>

static std::string join_args(int argc, char **argv)
{
	std::ostringstream oss;
	for (int i = 1; i < argc; ++i)
	{
		if (i > 1)
			oss << ' ';
		oss << argv[i];
	}
	return oss.str();
}

int main(int argc, char **argv)
{
	try
	{
		if (argc < 2)
			throw std::runtime_error("Usage: ./PmergeMe <positive integers>");
		PmergeMe sorter(join_args(argc, argv));
		sorter.sort();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
	return 0;
}
