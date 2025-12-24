/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 14:08:31 by pablo             #+#    #+#             */
/*   Updated: 2025/12/24 18:44:23 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_HPP
#define DOG_HPP

#include "Animal.hpp"
#include "Brain.hpp"

class Dog : public Animal
{
  public:
	Dog();
	Dog(const Dog &copy);
	Dog &operator=(const Dog &src);
	~Dog();

	void makeSound() const;

	const std::string &getIdea(int index) const;
	void setIdea(int index, const std::string &idea);
	Brain *brain;
};

#endif
