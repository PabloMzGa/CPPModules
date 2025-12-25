/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 13:48:11 by pablo             #+#    #+#             */
/*   Updated: 2025/12/25 14:14:13 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CURE_HPP
#define CURE_HPP

#include "AMateria.hpp"

class Cure : public AMateria
{
  public:
	Cure();
	Cure(const Cure &other);
	~Cure();

	virtual AMateria *clone() const;
	virtual void use(ICharacter &target);

  private:
	Cure &operator=(const Cure &src);
};

#endif
