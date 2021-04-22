/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 17:30:07 by abaur             #+#    #+#             */
/*   Updated: 2021/04/22 18:12:21 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR
#define VECTOR_ITERATOR

namespace ft
{
	template <typename T, typename Container>
	struct vector_iterator
	{
	public:
		vector_iterator(void);
		vector_iterator(const vector_iterator& other);
		vector_iterator(Container* target, typename Container::size_type index);
		vector_iterator&	operator=(const vector_iterator& other);
		bool	operator==(const vector_iterator& other) const;
		bool	operator!=(const vector_iterator& other) const;
		bool	operator<=(const vector_iterator& other) const;
		bool	operator>=(const vector_iterator& other) const;
		bool	operator< (const vector_iterator& other) const;
		bool	operator> (const vector_iterator& other) const;

		T&	operator*() const;
		T*	operator->() const;
		T&	operator[](typename Container::size_type index) const;

		vector_iterator<T, Container>&	operator++();
		vector_iterator<T, Container>&	operator--();
		vector_iterator<T, Container> 	operator++(int);
		vector_iterator<T, Container> 	operator--(int);

		vector_iterator<T, Container> 	operator+ (const vector_iterator& other) const;
		vector_iterator<T, Container> 	operator- (const vector_iterator& other) const;
		vector_iterator<T, Container>&	operator+=(const vector_iterator& other);
		vector_iterator<T, Container>&	operator-=(const vector_iterator& other);

	private:
		Container*	target;
		typename Container::size_type	index;
	};
}


#endif
