/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 19:47:56 by pabmart2          #+#    #+#             */
/*   Updated: 2026/05/12 21:02:38 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MUTANTSTACK_HPP
#define MUTANTSTACK_HPP

#include <deque>
#include <stack>

template <typename T, typename Container = std::deque<T> >
class MutantStack : public std::stack{
	public:
		MutantStack();
		MutantStack(MutantStack &src);
		MutantStack &operator=(MutantStack &src);
		~MutantStack();

		//TODO: Implementar MutantStack<T>::iterator, begin() y end()
};
#include "MutantStack.tpp"

#endif