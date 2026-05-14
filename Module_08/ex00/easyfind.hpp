/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 20:25:09 by pabmart2          #+#    #+#             */
/*   Updated: 2026/05/13 19:43:31 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EASYFIND_HPP
# define EASYFIND_HPP

# include <algorithm>

namespace easyfind_detail
{
template <typename A, typename B> struct is_same
{
	static const bool value = false;
};

template <typename A> struct is_same<A, A>
{
	static const bool value = true;
};

}

/**
 * typename Container::value_type* = 0" forces the compiler to only use the
 * template in case it has a type defined inside called "value_type",
 * typical for containers
 */
template <typename Container> typename Container::iterator easyfind(Container &container,
	int value, typename Container::value_type * = 0)
{
	char	must_be_int[easyfind_detail::is_same<typename Container::value_type,
			int>::value ? 1 : -1];

	// If container isn't a <int> container, the compiler will select the
	// template which returns false. That way, must_be_int will have size -1
	// and an compilation error will ouccur
	(void)must_be_int;
	return (std::find(container.begin(), container.end(), value));
}

#endif