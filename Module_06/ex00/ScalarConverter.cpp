/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 18:29:02 by pabmart2          #+#    #+#             */
/*   Updated: 2026/03/25 19:59:57 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <cctype>
#include <cstdlib>
#include <iostream>

enum		PseudoType
{
	PSEUDO_NONE,
	PSEUDO_NAN,
	PSEUDO_NANF,
	PSEUDO_PINF,
	PSEUDO_PINFF,
	PSEUDO_NINF,
	PSEUDO_NINFF
};

static void	printPseudoLog(PseudoType p)
{
	std::string f, d;
	switch (p)
	{
	case PSEUDO_NAN:
	case PSEUDO_NANF:
		f = "nanf";
		d = "nan";
		break ;
	case PSEUDO_PINF:
	case PSEUDO_PINFF:
		f = "+inff";
		d = "+inf";
		break ;
	case PSEUDO_NINF:
	case PSEUDO_NINFF:
		f = "-inff";
		d = "-inf";
		break ;
	default:
		return ;
	}
	std::cout << "char: impossible\n";
	std::cout << "int: impossible\n";
	std::cout << "float: " << f << '\n';
	std::cout << "double: " << d << '\n';
}

static bool	detectPseudo(const std::string &s)
{
	std::string t;
	t.resize(s.size());
	for (std::size_t i = 0; i < s.size(); ++i)
		t[i] = static_cast<char>(std::tolower(static_cast<unsigned char>(s[i])));
	if (t == "nan")
	{
		printPseudoLog(PSEUDO_NAN);
		return (true);
	}
	if (t == "nanf")
	{
		printPseudoLog(PSEUDO_NANF);
		return (true);
	}
	if (t == "inf" || t == "+inf")
	{
		printPseudoLog(PSEUDO_PINF);
		return (true);
	}
	if (t == "inff" || t == "+inff")
	{
		printPseudoLog(PSEUDO_PINFF);
		return (true);
	}
	if (t == "-inf")
	{
		printPseudoLog(PSEUDO_NINF);
		return (true);
	}
	if (t == "-inff")
	{
		printPseudoLog(PSEUDO_NINFF);
		return (true);
	}
	return (false);
}

void ScalarConverter::convert(std::string literal)
{
	const char		*str;
	char			char_cast;
	int				int_cast;
	float			float_cast;
	double			double_cast;
	PseudoType		p;
	unsigned char	uc;

	str = literal.c_str();
	if (detectPseudo(literal))
		return ;
	if (literal.length() == 1)
	{
		char_cast = *str;
		uc = static_cast<unsigned char>(*str);
		if (std::isprint(uc) && !std::isdigit(uc))
		{
			int_cast = static_cast<int>(char_cast);
			float_cast = static_cast<float>(char_cast);
			double_cast = static_cast<double>(char_cast);
		}
		else
		{
			int_cast = std::atoi(str);
			char_cast = static_cast<char>(int_cast);
			float_cast = static_cast<float>(int_cast);
			double_cast = static_cast<double>(int_cast);
		}
	}
	else
	{

	}
}
