/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 16:43:44 by pablo             #+#    #+#             */
/*   Updated: 2025/12/25 17:00:25 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MATERIASOURCE_HPP
#define MATERIASOURCE_HPP

#include "IMateriaSource.hpp"
#include "AMateria.hpp"

class MateriaSource :  public IMateriaSource
{
  public:
	MateriaSource();
	MateriaSource(const MateriaSource &copy);
	MateriaSource &operator=(const MateriaSource &src);
	virtual ~MateriaSource();

	virtual void learnMateria(AMateria *);
	virtual AMateria *createMateria(std::string const &type);

  private:
	AMateria *sources[4];

};

#endif
