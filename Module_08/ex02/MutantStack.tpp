/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.tpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 20:15:39 by pabmart2          #+#    #+#             */
/*   Updated: 2026/05/12 21:01:31 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/////////////////////////////////// ORTHODOX ///////////////////////////////////

template <typename T, typename Container> MutantStack<T,
	Container>::MutantStack() : _container()
{
}

template <typename T, typename Container> MutantStack<T,
	Container>::MutantStack(MutantStack &src) : std::stack<T, Container>(src)
{
}

template <typename T, typename Container> MutantStack<T,
	Container> &MutantStack<T, Container>::operator=(MutantStack &src)
{
	if (this != src)
	{
		std::stack<T, Container>::operator=(other);
	}
	return (*this);
}

template <typename T, typename Container> MutantStack<T, Container>::~MutantStack()
{
}