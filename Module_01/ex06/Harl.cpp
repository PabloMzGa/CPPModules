/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 18:23:42 by pablo             #+#    #+#             */
/*   Updated: 2025/12/19 12:44:52 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"
#include <iostream>
#include <iterator>

void Harl::debug()
{
	std::cout << "DEBUG: I love having extra bacon for my "
	             "7XL-double-cheese-triple-pickle-special"
	             "ketchup burger. I really do!"
	          << std::endl;
}

void Harl::info()
{
	std::cout << "INFO: I cannot believe adding extra bacon costs more money. "
	             "You didn’t put"
	             "enough bacon in my burger! If you did, I wouldn’t be asking "
	             "for more!"
	          << std::endl;
}

void Harl::warning()
{
	std::cout << "WARNING: I think I deserve to have some extra bacon for "
	             "free. I’ve been coming for"
	             " years, whereas you started working here just last month."
	          << std::endl;
}

void Harl::error()
{
	std::cout
	    << "ERROR: This is unacceptable! I want to speak to the manager now."
	    << std::endl;
}

void Harl::complain(std::string level)
{
	typedef void (Harl::*t_complaint_func)();

	struct s_complain_lvl{
		std::string level_s;
		t_complaint_func complain_func;
	};

	s_complain_lvl complains[] = {
		{"DEBUG", &Harl::debug},
		{"INFO", &Harl::info},
		{"WARNING", &Harl::warning},
		{"ERROR", &Harl::error}
	};

	int size = sizeof(complains) / sizeof(s_complain_lvl);

	for (int i = 0; i < size; ++i) {
		if (complains[i].level_s == level) {
			(this->*complains[i].complain_func)();
			break;
		}
	}
}
