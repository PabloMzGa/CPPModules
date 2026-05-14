/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 19:47:56 by pabmart2          #+#    #+#             */
/*   Updated: 2026/05/14 19:09:53 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MUTANTSTACK_HPP
#define MUTANTSTACK_HPP

#include <deque>
#include <stack>

template <typename T, typename Container = std::deque<T> >
class MutantStack : public std::stack<T, Container>{
	public:
		MutantStack();
		MutantStack(const MutantStack &src);
		MutantStack &operator=(const MutantStack &src);
		~MutantStack();

		using iterator = typename Container::iterator;
		using const_iterator = typename Container::const_iterator;

		iterator begin(){return this->c.begin();}
		iterator end(){return this->c.end();}
		const_iterator begin() const{return this->c.begin();}
		const_iterator end() const{return this->c.end();}
};
#include "MutantStack.tpp"

#endif