/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 13:49:18 by pablo             #+#    #+#             */
/*   Updated: 2025/12/24 19:24:08 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <string>

class A_Animal
{
	public:
		A_Animal();
		A_Animal(const A_Animal &copy);
		A_Animal &operator=(const A_Animal &src);
		virtual ~A_Animal();

		virtual void makeSound() const = 0;

		std::string getType() const;
		void setType(const std::string &type);

	protected:
		std::string type;

};

#endif
