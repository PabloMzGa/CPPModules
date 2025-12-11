/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 20:58:35 by pabmart2          #+#    #+#             */
/*   Updated: 2025/12/11 21:02:33 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp";


Zombie* zombieHorde( int N, std::string name )
{
	Zombie *horde;

	horde = new Zombie[N](name);
}
