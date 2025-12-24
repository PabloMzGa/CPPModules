/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 13:49:18 by pablo             #+#    #+#             */
/*   Updated: 2025/12/24 18:04:11 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <string>

class Animal
{
	public:
		Animal();
		Animal(const Animal &copy);
		Animal &operator=(const Animal &src);
		virtual ~Animal();

		virtual void makeSound() const;

		std::string getType() const;
		void setType(const std::string &type);

	protected:
		std::string type;

};

#endif
