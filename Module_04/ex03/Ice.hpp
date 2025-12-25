/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 13:36:00 by pablo             #+#    #+#             */
/*   Updated: 2025/12/25 14:14:11 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ICE_HPP
#define ICE_HPP

#include "AMateria.hpp"

class Ice : public AMateria
{
  public:
	Ice();
	Ice(const Ice &copy);
	~Ice();

	virtual AMateria *clone() const;
	virtual void use(ICharacter &target);

  private:
	Ice &operator=(const Ice &src);
};

#endif
