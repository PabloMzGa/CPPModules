/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 18:23:42 by pablo             #+#    #+#             */
/*   Updated: 2025/12/16 18:51:19 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Harl.hpp>
#include <iostream>

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
	typedef void (Harl::*ComplaintFunc)();
}
