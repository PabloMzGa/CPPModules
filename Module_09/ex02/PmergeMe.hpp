/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 18:25:21 by pablo             #+#    #+#             */
/*   Updated: 2026/05/26 20:02:55 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <cctype>
# include <ctime>
# include <deque>
# include <limits>
# include <sstream>
# include <stdexcept>
# include <string>
# include <vector>
#include <memory>

class PmergeMe
{
  public:
	PmergeMe();
	PmergeMe(const PmergeMe &src);
	PmergeMe(const std::string &input);
	PmergeMe &operator=(const PmergeMe &src);
	~PmergeMe();
	void sort();

  private:
	static unsigned int parse_positive_int(const std::string &token);
	template <typename Container> static bool is_sorted(const Container &src);
	template <typename Container> static void load_values(const std::string &input,
		Container &container);
	/*
	template <typename Container>
	static void merge(Container left, Container right, Container &src);
	template <typename Container> static void merge_sort(Container &src);
	*/

	std::vector<unsigned int> _vector;
	std::deque<unsigned int> _deque;

	double _vector_time_ms;
	double _deque_time_ms;
};

template < template <typename, typename> class Container, typename T >
void ford_johnson(Container<T, std::allocator<T> >&c)
{

}

template <typename Container> void PmergeMe::load_values(const std::string &input,
	Container &container)
{
	unsigned int	value;

	std::stringstream ss(input);
	std::string token;
	while (ss >> token)
	{
		value = parse_positive_int(token);
		container.push_back(value);
	}
	if (container.empty())
		throw std::runtime_error("Error: no numbers provided");
}

template <typename Container> bool PmergeMe::is_sorted(const Container &src)
{
	if (src.size() <= 1)
		return (true);
	typename Container::const_iterator it = src.begin();
	typename Container::const_iterator prev = it;
	++it;
	for (; it != src.end(); ++it, ++prev)
	{
		if (*prev > *it)
			return (false);
	}
	return (true);
}

/*
template <typename Container>
void PmergeMe::merge(Container left, Container right, Container &src)
{
	typename Container::iterator l_it = left.begin();
	typename Container::iterator r_it = right.begin();
	typename Container::iterator src_it = src.begin();
	while (src_it != src.end())
	{
		if (l_it != left.end() && r_it != right.end())
			*src_it = *l_it < *r_it ? *l_it++ : *r_it++;
			else if (l_it != left.end())
			*src_it = *l_it++;
			else if (r_it != right.end())
			*src_it = *r_it++;
		else
		throw std::runtime_error("Error merging, both splitted containers "
		"reached the end too early!");
		++src_it;
	}
}

template <typename Container> void PmergeMe::merge_sort(Container &src)
{
	std::size_t length = src.size();
	if (length <= 1 || is_sorted(src))
	return ;
	Container left(src.begin(), src.begin() + length / 2);
	Container right(src.begin() + length / 2, src.end());
	merge_sort(left);
	merge_sort(right);
	merge(left, right, src);
}
*/
#endif
