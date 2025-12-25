/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 19:34:05 by pablo             #+#    #+#             */
/*   Updated: 2025/12/25 14:38:17 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AMATERIA_HPP
#define AMATERIA_HPP

#include <string>

class ICharacter;

class AMateria
{
  public:
	AMateria();
	AMateria(std::string const &type);
	AMateria(const AMateria &other);
	virtual ~AMateria();

	std::string const &getType() const; // Returns the materia type
	virtual AMateria *clone() const = 0;
	virtual void use(ICharacter &target) = 0;

  private:
	std::string _type;
	AMateria &operator=(const AMateria &other);
};

#endif
