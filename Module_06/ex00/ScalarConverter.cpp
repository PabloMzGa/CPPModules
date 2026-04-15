/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 18:29:02 by pabmart2          #+#    #+#             */
/*   Updated: 2026/04/15 20:14:13 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>

////////////////////////////////// CANONICAL ///////////////////////////////////

ScalarConverter::ScalarConverter()
{
}

ScalarConverter::ScalarConverter(const ScalarConverter &other)
{
	(void)other;
}

ScalarConverter &ScalarConverter::operator=(const ScalarConverter &other)
{
	(void)other;
	return (*this);
}

ScalarConverter::~ScalarConverter()
{
}

/////////////////////////////////// HELPERS ////////////////////////////////////

/**
 * @enum PseudoType
 * @brief Types of pseudo-literals recognized by the converter.
 *
 * This enum represents special floating-point literals that do not
 * represent regular numeric values but instead denote Not-a-Number
 * or infinity variants. These are handled specially when printing
 * conversion results.
 */
enum PseudoType
{
	PSEUDO_NONE,  /**< Not a pseudo-literal */
	PSEUDO_NAN,   /**< "nan" (double) */
	PSEUDO_NANF,  /**< "nanf" (float) */
	PSEUDO_PINF,  /**< "+inf" or "inf" (double) */
	PSEUDO_PINFF, /**< "+inff" or "inff" (float) */
	PSEUDO_NINF,  /**< "-inf" (double) */
	PSEUDO_NINFF  /**< "-inff" (float) */
};

/**
 * @brief Print conversion results for pseudo-literal floating-point values.
 *
 * This helper prints the canonical output for special floating-point
 * pseudo-literals (NaN and infinities) for the ScalarConverter output.
 * The function writes to std::cout the representations for char and int
 * (always "impossible"), and the appropriate float/double literal
 * variants (for example, "nanf" and "nan").
 *
 * @param p The PseudoType enum value identifying the pseudo-literal.
 *
 * @note The function returns immediately when p == PSEUDO_NONE.
 */
static void printPseudoLog(PseudoType p)
{
	std::string f, d;
	switch (p)
	{
	case PSEUDO_NAN:
	case PSEUDO_NANF:
		f = "nanf";
		d = "nan";
		break;
	case PSEUDO_PINF:
	case PSEUDO_PINFF:
		f = "+inff";
		d = "+inf";
		break;
	case PSEUDO_NINF:
	case PSEUDO_NINFF:
		f = "-inff";
		d = "-inf";
		break;
	default:
		return;
	}
	std::cout << "char: impossible" << std::endl;
	std::cout << "int: impossible" << std::endl;
	std::cout << "float: " << f << std::endl;
	std::cout << "double: " << d << std::endl;
}

/**
 * @brief Detect pseudo-floating point literals in the input string.
 *
 * The function performs a case-insensitive comparison of the input against
 * the recognized pseudo-literals: "nan", "nanf", "inf", "+inf", "inff",
 * "+inff", "-inf" and "-inff". When a match is found it calls
 * printPseudoLog with the corresponding enum and returns true.
 *
 * @param s Input string to examine.
 * @return true if the input is a pseudo-literal (and printPseudoLog was
 * called), false otherwise.
 */
static bool detectPseudo(const std::string &s)
{
	std::string t;
	t.resize(s.size());
	for (std::size_t i = 0; i < s.size(); ++i)
		t[i] =
		    static_cast<char>(std::tolower(static_cast<unsigned char>(s[i])));
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

/**
 * @enum InputType
 * @brief Detected type of the input literal.
 *
 * INPUT_CHAR:    Single printable non-digit character.
 * INPUT_INT:     Integer literal (e.g. "42").
 * INPUT_FLOAT:   Float literal with trailing 'f' (e.g. "42.0f").
 * INPUT_DOUBLE:  Double literal with a decimal point but no trailing 'f' (e.g.
 *     "42.0"). INPUT_INVALID: Input does not match any valid form.
 */
enum InputType
{
	INPUT_CHAR,
	INPUT_INT,
	INPUT_FLOAT,
	INPUT_DOUBLE,
	INPUT_INVALID
};

/**
 * @brief Detects the input type and validates the literal format.
 *
 * The function recognizes the following forms:
 * - Single printable non-digit character -> INPUT_CHAR
 * - Optional leading '+' or '-' sign
 * - Digits with an optional single '.' decimal point
 * - Optional trailing 'f' or 'F' (must be the last character and requires a
 * decimal point)
 *
 * @param s Input string to analyze
 * @return InputType The detected input type or INPUT_INVALID on format error
 */
static InputType detectInputType(const std::string &s)
{
	size_t i = 0;
	bool hasPoint = false;
	bool hasF = false;

	if (s.empty())
		return INPUT_INVALID;

	if (s.size() == 1)
	{
		unsigned char uc = static_cast<unsigned char>(s[0]);
		if (std::isprint(uc) && !std::isdigit(uc))
			return INPUT_CHAR;
	}
	if (s[0] == '+' || s[0] == '-')
		i = 1;
	if (i >= s.size())
		return INPUT_INVALID;

	for (; i < s.size(); ++i)
	{
		if (s[i] == '.')
		{
			if (hasPoint || hasF)
				return INPUT_INVALID;
			hasPoint = true;
		}
		else if (s[i] == 'f' || s[i] == 'F')
		{
			if (hasF || i != s.size() - 1)
				return INPUT_INVALID;
			hasF = true;
		}
		else if (!std::isdigit(static_cast<unsigned char>(s[i])))
			return INPUT_INVALID;
	}
	if (hasF)
	{
		if (!hasPoint)
			return INPUT_INVALID;
		return INPUT_FLOAT;
	}
	if (hasPoint)
		return INPUT_DOUBLE;

	return INPUT_INT;
}

/**
 * @brief Helper to print conversion results for all target types.
 *
 * Prints the char (or "Non displayable"), the int, the float (with one
 * decimal and trailing 'f') and the double (with one decimal).
 *
 * @param c Character representation
 * @param i Integer representation
 * @param f Float representation
 * @param d Double representation
 */
static void printResult(char c, int i, float f, double d)
{

	if (std::isprint(static_cast<unsigned char>(c)))
		std::cout << "char: " << c << std::endl;
	else
		std::cout << "char: Non displayable" << std::endl;
	std::cout << "int: " << i << std::endl;
	std::cout << std::fixed << std::setprecision(1);
	std::cout << "float: " << f << "f" << std::endl;
	std::cout << "double: " << d << std::endl;
}

/////////////////////////////////// MEMBERS ////////////////////////////////////

/**
 * @brief Convert a string literal to char, int, float and double and print.
 *
 * The function detects special pseudo-literals (nan, +inf, -inf, with 'f')
 * and delegates their handling to detectPseudo(). Otherwise it determines
 * the input type (char, int, float, double) via detectInputType() and
 * performs the corresponding conversions. Results are printed using
 * printResult(). If a conversion from stringstream fails, no output is
 * produced for that branch.
 *
 * @param literal The input literal string to convert.
 */
void ScalarConverter::convert(std::string literal)
{
	if (detectPseudo(literal))
		return;

	InputType type = detectInputType(literal);
	if (type == INPUT_INVALID)
	{
		std::cerr << "Error: invalid literal" << std::endl;
		return;
	}

	if (type == INPUT_CHAR)
	{
		char c = literal[0];
		int i = static_cast<int>(c);
		float f = static_cast<float>(c);
		double d = static_cast<double>(c);
		printResult(c, i, f, d);
	}
	else if (type == INPUT_INT)
	{
		std::stringstream ss(literal);
		int i;
		if (ss >> i)
		{
			char c = static_cast<char>(i);
			float f = static_cast<float>(i);
			double d = static_cast<double>(i);
			printResult(c, i, f, d);
		}
		else
			std::cerr << "Error: invalid literal" << std::endl;
	}
	else if (type == INPUT_FLOAT)
	{
		std::stringstream ss(literal);
		float f;
		if (ss >> f)
		{
			double d = static_cast<double>(f);
			int i = static_cast<int>(f);
			char c = static_cast<char>(i);
			printResult(c, i, f, d);
		}
		else
			std::cerr << "Error: invalid literal" << std::endl;
	}
	else if (type == INPUT_DOUBLE)
	{
		std::stringstream ss(literal);
		double d;
		if (ss >> d)
		{
			float f = static_cast<float>(d);
			int i = static_cast<int>(d);
			char c = static_cast<char>(i);
			printResult(c, i, f, d);
		}
		else
			std::cerr << "Error: invalid literal" << std::endl;
	}
}


