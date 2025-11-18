/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:18:06 by pablo             #+#    #+#             */
/*   Updated: 2025/11/18 19:38:16 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cctype>
#include <cstring>
#include <iostream>

int main(int argc, char *argv[])
{
	size_t len;

	if (argc == 1)
	{
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
		return (0);
	}
	for (int i = 1; i < argc; i++)
	{
		len = std::strlen(argv[i]);
		for (size_t j = 0; j < len; j++)
		{
			argv[i][j] = std::toupper(argv[i][j]);
		}
		std::cout << argv[i];
	}
	std::cout << std::endl;
}
