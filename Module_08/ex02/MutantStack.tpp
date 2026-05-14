/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.tpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 20:15:39 by pabmart2          #+#    #+#             */
/*   Updated: 2026/05/14 19:10:08 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/////////////////////////////////// ORTHODOX ///////////////////////////////////

template <typename T, typename Container>
MutantStack<T, Container>::MutantStack() : std::stack<T, Container>()
{
}

template <typename T, typename Container>
MutantStack<T, Container>::MutantStack(const MutantStack &src)
	: std::stack<T, Container>(src)
{
}

template <typename T, typename Container>
MutantStack<T, Container> &MutantStack<T, Container>::operator=(const MutantStack &src)
{
	if (this != &src)
	{
		std::stack<T, Container>::operator=(src);
	}
	return (*this);
}

template <typename T, typename Container>
MutantStack<T, Container>::~MutantStack()
{
}