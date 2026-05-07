/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 20:25:09 by pabmart2          #+#    #+#             */
/*   Updated: 2026/05/07 19:45:24 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <algorithm>

template <typename A, typename B>
struct is_same { static const bool value = false; };

template <typename A>
struct is_same<A, A> { static const bool value = true; }; // ✔️ LEGAL

/*
template <typename Container>
//"typename Container::value_type* = 0" forces the compiler to only use the template
// in case it has a type defined inside called "value_type", typical for containers
bool easyfind(Container &container, int value, typename Container::value_type* = 0)
{
	std::find(t.)
}
*/

#endif