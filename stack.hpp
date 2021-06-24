/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 18:29:28 by abaur             #+#    #+#             */
/*   Updated: 2021/06/24 19:15:00 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{
	template <typename T, typename C = ft::vector<T> >
	class stack 
	{
	public:
		// ## Member types
		typedef T	value_type;
		typedef C	container_type;
		typedef typename C::size_type	size_type;

		explicit stack(const container_type& src = container_type()) : _base(src) {}
		~stack() {}

		bool     	empty() const { return _base.empty(); } 
		size_type	size()  const { return _base.size();  }
		value_type&      	top()       { return _base.back(); }
		const value_type&	top() const { return _base.back(); }
		void	push(const value_type& val) { return _base.push_back(val); }
		void	pop() { return _base.pop_back(); }

		friend	bool operator==(const stack&, const stack&);
		friend	bool operator!=(const stack&, const stack&);
		friend	bool operator< (const stack&, const stack&);
		friend	bool operator> (const stack&, const stack&);
		friend	bool operator<=(const stack&, const stack&);
		friend	bool operator>=(const stack&, const stack&);

	private:
		container_type	_base;
	};
}

template <typename T, typename C>
bool	operator==(const ft::stack<T,C>& a, const ft::stack<T,C>& b) {
	return a._base == b._base;
}
template <typename T, typename C>
bool	operator!=(const ft::stack<T,C>& a, const ft::stack<T,C>& b) {
	return a._base != b._base;
}
template <typename T, typename C>
bool	operator< (const ft::stack<T,C>& a, const ft::stack<T,C>& b) {
	return a._base <  b._base;
}
template <typename T, typename C>
bool	operator> (const ft::stack<T,C>& a, const ft::stack<T,C>& b) {
	return a._base >  b._base;
}
template <typename T, typename C>
bool	operator<=(const ft::stack<T,C>& a, const ft::stack<T,C>& b) {
	return a._base <= b._base;
}
template <typename T, typename C>
bool	operator>=(const ft::stack<T,C>& a, const ft::stack<T,C>& b) {
	return a._base >= b._base;
}

#endif
