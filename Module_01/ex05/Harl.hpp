/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 18:21:59 by pablo             #+#    #+#             */
/*   Updated: 2025/12/16 18:25:22 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HARL.HPP
#define HARL.HPP

#include <string>

class Harl
{
  private:
	void debug(void);
	void info(void);
	void warning(void);
	void error(void);

  public:
	void complain(std::string level);
};

#endif
