/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 21:11:43 by pabmart2          #+#    #+#             */
/*   Updated: 2026/05/04 20:56:04 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <cstddef>
#include <stdexcept>

template <typename T> class Array
{
  public:
	Array();
	Array(const Array &copy);
	Array(unsigned int size);
	Array &operator=(const Array &src);
	T& operator[](unsigned int index);
	const T& operator[](unsigned int index) const;
	~Array();

	size_t size() const;

	private:
		T *_elements;
		size_t _size;
};
#include "Array.tpp"

#endif
