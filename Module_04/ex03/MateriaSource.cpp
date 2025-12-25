/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 16:46:25 by pablo             #+#    #+#             */
/*   Updated: 2025/12/25 17:12:19 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MateriaSource.hpp"

MateriaSource::MateriaSource()
{
	for (int i = 0; i < 4; i++)
		sources[i] = NULL;
}

MateriaSource::MateriaSource(const MateriaSource &copy)
{
	for (int i = 0; i < 4; i++)
	{
		if (copy.sources[i])
			sources[i] = copy.sources[i]->clone();
		else
			sources[i] = NULL;
	}
}

MateriaSource &MateriaSource::operator=(const MateriaSource &src)
{
	if (this != &src)
	{
		for (int i = 0; i < 4; i++)
		{
			delete sources[i];
			sources[i] = NULL;
		}
		for (int i = 0; i < 4; i++)
		{
			if (src.sources[i])
				sources[i] = src.sources[i]->clone();
			else
				sources[i] = NULL;
		}
	}
	return *this;
}

MateriaSource::~MateriaSource()
{
	for (int i = 0; i < 4; i++)
	{
		delete sources[i];
	}
}

void MateriaSource::learnMateria(AMateria *m)
{
	for (int i = 0; i < 4; i++)
	{
		if (sources[i] == NULL)
		{
			sources[i] = m;
			return;
		}
	}
	delete m;
}

AMateria *MateriaSource::createMateria(std::string const &type)
{
	for (int i = 0; i < 4; i++)
	{
		if (sources[i] && sources[i]->getType() == type)
			return sources[i]->clone();
	}
	return NULL;
}
