/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RNP.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 18:39:56 by pablo             #+#    #+#             */
/*   Updated: 2026/05/19 20:33:20 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RNP.hpp"
#include <cctype>
#include <cstdlib>
#include <stdexcept>
#include <sstream>

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// ORTHODOX ///////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Default constructor.
 *
 * Initializes an empty RPN evaluator.
 */
RNP::RNP() {}

/**
 * @brief Copy constructor.
 *
 * @param src Source object to copy from.
 */
RNP::RNP(const RNP &src) : _stack(src._stack) {}

/**
 * @brief Copy assignment operator.
 *
 * @param src Source object to assign from.
 * @return Reference to the current object.
 */
RNP &RNP::operator=(const RNP &src)
{
	if (this != &src)
		this->_stack = src._stack;
	return *this;
}

/**
 * @brief Destructor.
 *
 * Releases the resources owned by the evaluator.
 */
RNP::~RNP() {}

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// HELPERS ////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Checks whether a character is a supported arithmetic operator.
 *
 * @param c Character to validate.
 * @return true if the character is one of +, -, *, /.
 * @return false otherwise.
 */
bool RNP::is_valid_operator(char c)
{
	switch (c)
	{
	case '+':
		return true;
	case '-':
		return true;
	case '*':
		return true;
	case '/':
		return true;
	default:
		return false;
	}
}


/**
 * @brief Applies an operator to the two top-most stack values.
 *
 * @param op Operator to apply.
 * @throws std::runtime_error If there are not enough operands, if the
 *         operator is invalid, or if a division by zero is attempted.
 */
void RNP::use_operator(char op)
{
	if (_stack.size() < 2)
		throw std::runtime_error("Not enough operands");
	int rhs = _stack.top();
	_stack.pop();
	int lhs = _stack.top();
	_stack.pop();
	int res;
	switch (op)
	{
	case '+':
		res = lhs + rhs;
		break;
	case '-':
		res = lhs - rhs;
		break;
	case '*':
		res = lhs * rhs;
		break;
	case '/':
		if (rhs == 0)
			throw std::runtime_error("Division by zero");
		res = lhs / rhs;
		break;
	default:
		throw std::runtime_error("Invalid operator");
	}
	_stack.push(res);
}

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// PUBLIC MEMBERS ////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Evaluates an expression in Reverse Polish Notation.
 *
 * The stack is reset before each evaluation so repeated calls are independent.
 *
 * @param input Expression to evaluate.
 * @return Result of the expression.
 * @throws std::runtime_error If a token is invalid or the expression is
 *         malformed.
 */
int RNP::calculate(const std::string &input)
{
	// reset stack for repeated calls
	if (!_stack.empty())
	{
		_stack = std::stack<int>();
	}
	std::istringstream ss(input);
	std::string token;

	while (ss >> token)
	{
		if (token.size() == 1 && is_valid_operator(token[0]))
		{
			use_operator(token[0]);
		}
		else
		{
			int v;
			std::istringstream conv(token);
			if (!(conv >> v) || !(conv >> std::ws).eof())
				throw std::runtime_error(std::string("Invalid token: ") +
				                         token);
			_stack.push(v);
		}
	}

	if (_stack.size() != 1)
		throw std::runtime_error("Invalid RPN expression");
	return _stack.top();
}
