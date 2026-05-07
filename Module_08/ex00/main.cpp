/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 19:35:50 by pabmart2          #+#    #+#             */
/*   Updated: 2026/05/07 19:46:12 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "easyfind.hpp"

int main ()
{
	std::cout << "Ret: " << is_same<int, bool>::value << std::endl;
		std::cout << "Ret: " << is_same<int, int>::value << std::endl;
}