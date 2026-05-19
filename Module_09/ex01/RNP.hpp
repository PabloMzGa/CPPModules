/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RNP.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 18:36:45 by pablo             #+#    #+#             */
/*   Updated: 2026/05/19 20:11:45 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RNP_HPP
#define RNP_HPP

#include <stack>
#include <string>

class RNP
{
public:
	RNP();
	RNP(const RNP &src);
	RNP &operator=(const RNP &src);
	~RNP();
	int calculate(const std::string &input);

  private:
	std::stack<int> _stack;
	bool is_valid_operator(char c);
	void use_operator(char op);
};

#endif
