/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 18:29:28 by abaur             #+#    #+#             */
/*   Updated: 2021/06/24 19:15:16 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "list.hpp"

namespace ft
{
	template <typename T, typename C = ft::list<T> >
	class queue 
	{
	public:
		// ## Member types
		typedef T	value_type;
		typedef C	container_type;
		typedef typename C::size_type	size_type;

		explicit queue(const container_type& src = container_type()) : _base(src) {}
		~queue() {}

		bool     	empty() const { return _base.empty(); } 
		size_type	size()  const { return _base.size();  }

		value_type&      	front()       { return _base.front(); }
		const value_type&	front() const { return _base.front(); }
		value_type&      	back()        { return _base.back(); }
		const value_type&	back()  const { return _base.back(); }
		void	push(const value_type& val) { return _base.push_back(val); }
		void	pop() { return _base.pop_front(); }

		friend	bool operator==(const queue&, const queue&);
		friend	bool operator!=(const queue&, const queue&);
		friend	bool operator< (const queue&, const queue&);
		friend	bool operator> (const queue&, const queue&);
		friend	bool operator<=(const queue&, const queue&);
		friend	bool operator>=(const queue&, const queue&);

	private:
		container_type	_base;
	};
}

template <typename T, typename C>
bool	operator==(const ft::queue<T,C>& a, const ft::queue<T,C>& b) {
	return a._base == b._base;
}
template <typename T, typename C>
bool	operator!=(const ft::queue<T,C>& a, const ft::queue<T,C>& b) {
	return a._base != b._base;
}
template <typename T, typename C>
bool	operator< (const ft::queue<T,C>& a, const ft::queue<T,C>& b) {
	return a._base <  b._base;
}
template <typename T, typename C>
bool	operator> (const ft::queue<T,C>& a, const ft::queue<T,C>& b) {
	return a._base >  b._base;
}
template <typename T, typename C>
bool	operator<=(const ft::queue<T,C>& a, const ft::queue<T,C>& b) {
	return a._base <= b._base;
}
template <typename T, typename C>
bool	operator>=(const ft::queue<T,C>& a, const ft::queue<T,C>& b) {
	return a._base >= b._base;
}

#endif
