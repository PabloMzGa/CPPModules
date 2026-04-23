/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 20:04:42 by pabmart2          #+#    #+#             */
/*   Updated: 2026/04/23 21:07:02 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITER_HPP
# define ITER_HPP

# include <aio.h>

template <typename T, typename Func> void iter(T *array, const size_t size,
	Func func)
{
	for (size_t i = 0; i < size; i++)
		func(array[i]);
}

#endif