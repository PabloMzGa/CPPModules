/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 18:31:21 by pabmart2          #+#    #+#             */
/*   Updated: 2026/05/12 19:05:37 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
# define SPAN_HPP

# include <cstddef>
# include <vector>
# include <stdexcept>


class Span
{
  public:
	Span();
	Span(Span &src);
	Span(std::size_t size);
	Span &operator=(Span &src);
	~Span();

	void addNumber(int number);
	template <typename It> void addNumbers(It begin, It end)
	{
		std::size_t distance = std::distance(begin, end);

		if (_vector.size() + distance > _size)
			throw std::runtime_error("No space enough in Span");

		_vector.insert(_vector.end(), begin, end);
	}
	unsigned int shortestSpan();
	unsigned int longestSpan();

  private:
	std::size_t _size;
	std::vector<int> _vector;
};

#endif