/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 20:22:03 by pabmart2          #+#    #+#             */
/*   Updated: 2025/12/11 20:53:28 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <ctime>
#include <string>

void	randomChump(std::string name);


int	main(void)
{
	std::string random_names[] = {"Braingore McDead", "Rotgut Ramirez",
		"Fleshmuncher Jones", "Bonecruncher Silva", "Decay Drake",
		"Maggot Mike", "Skullface Garcia", "Wormwood Wilson", "Corpse Carl",
		"Ghoulie Gonzalez", "Putrid Pete", "Zombie Zack", "Rancid Rita",
		"Decay Dean", "Moldy Max", "Graveyard Greg", "Stench Steve",
		"Undead Ursula", "Rotten Roger", "Braindead Betty"};
	srand(time(NULL));
	randomChump(random_names[rand() % 20]);
}
