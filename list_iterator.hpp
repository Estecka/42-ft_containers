/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_iterator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 14:56:38 by abaur             #+#    #+#             */
/*   Updated: 2021/05/02 17:03:48 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_ITERATOR
#define LIST_ITERATOR

#include <iterator>

namespace ft
{
	template <typename T, typename Container>
	struct list_iterator
	{
	public:
		typedef T 	value_type;
		typedef T*	pointer;
		typedef T&	reference;
		typedef typename Container::size_type	size_type;
		typedef typename Container::size_type	difference_type;
		typedef std::random_access_iterator_tag	iterator_category;

		list_iterator(void);
		list_iterator(const list_iterator& other);
		list_iterator(Container* target, size_type index);
		list_iterator&	operator=(const list_iterator& other);
		bool	operator==(const list_iterator& other) const;
		bool	operator!=(const list_iterator& other) const;
		bool	operator<=(const list_iterator& other) const;
		bool	operator>=(const list_iterator& other) const;
		bool	operator< (const list_iterator& other) const;
		bool	operator> (const list_iterator& other) const;

		T&	operator*() const;
		T*	operator->() const;
		T&	operator[](size_type offset) const;

		list_iterator<T, Container>&	operator++();
		list_iterator<T, Container>&	operator--();
		list_iterator<T, Container> 	operator++(int);
		list_iterator<T, Container> 	operator--(int);

		list_iterator<T, Container> 	operator+ (int offset) const;
		list_iterator<T, Container> 	operator- (int offset) const;
		list_iterator<T, Container>&	operator-=(int offset);
		list_iterator<T, Container>&	operator+=(int offset);
		size_type	operator+ (const list_iterator& other) const;
		size_type	operator- (const list_iterator& other) const;
	};
}

#endif
