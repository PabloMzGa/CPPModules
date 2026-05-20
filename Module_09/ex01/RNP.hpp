/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RNP.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 18:36:45 by pablo             #+#    #+#             */
/*   Updated: 2026/05/20 18:43:39 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RNP_HPP
#define RNP_HPP

#include <string>

class RNP
{
public:
	RNP();
	RNP(const RNP &src);
	RNP &operator=(const RNP &src);
	~RNP();
	int calculate(const std::string &input);
};

#endif
