/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 16:30:54 by abaur             #+#    #+#             */
/*   Updated: 2021/06/27 18:24:23 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

#include "pair.hpp"
#include "map.hpp"

#include <iterator>
#include <stdexcept>

namespace ft
{
	template <typename K, typename V, typename C, typename A>
	class map;

	template <typename T, typename Container>
	struct map_iterator 
	{
	private:
		typedef typename Container::node	node;

	public:
		typedef T	value_type;
		typedef T*	pointer;
		typedef T&	reference;
		typedef typename Container::size_type	size_type;
		typedef typename Container::size_type	difference_type;
		typedef std::bidirectional_iterator_tag	iterator_category;

		friend class ft::map<typename Container::key_type, typename Container::mapped_type, typename Container::key_compare, typename Container::allocator_type>;

	public:
		map_iterator();
		map_iterator(const map_iterator& other);
		map_iterator(Container& target, node* position);
		map_iterator&	operator=(const map_iterator& other);

		bool	operator==(const map_iterator& other) const;
		bool	operator!=(const map_iterator& other) const;

		value_type&	operator*() const;
		value_type*	operator->() const;

		map_iterator&	operator++();
		map_iterator&	operator--();
		map_iterator 	operator++(int);
		map_iterator 	operator--(int);

	private:
		Container*	target;
		node*     	position;
	};

/******************************************************************************/
/* # Implementation                                                           */
/******************************************************************************/

	template <typename T, class C>
	map_iterator<T,C>::map_iterator()
	: target(), position() {
	}
	template <typename T, class C>
	map_iterator<T,C>::map_iterator(const map_iterator& other)
	:target(other.target), position(other.position) {
	}
	template <typename T, class C>
	map_iterator<T,C>::map_iterator(C& target, node* position)
	: target(&target), position(position) {
	}

	template <typename T, class C>
	map_iterator<T,C>&	map_iterator<T,C>::operator=(const map_iterator& other){
		this->target   = other.target;
		this->position = other.position;
		return *this;
	}
	template <typename T, class C>
	bool	map_iterator<T,C>::operator==(const map_iterator& other) const {
		return (this->target == other.target) && (this->position == other.position);
	}
	template <typename T, class C>
	bool	map_iterator<T,C>::operator!=(const map_iterator& other) const {
		return (this->target != other.target) || (this->position != other.position);
	}

	template <typename T, class C>
	typename map_iterator<T,C>::value_type&	map_iterator<T,C>::operator*() const {
		return (position->value);
	}
	template <typename T, class C>
	typename map_iterator<T,C>::value_type*	map_iterator<T,C>::operator->() const {
		return &**this;
	}

	template <typename T, class C>
	map_iterator<T,C>&	map_iterator<T,C>::operator++(){
		if (this->position) {
			this->position = position->next();
			return *this;
		}
		else
			throw std::length_error("Past-the-end map iterator.");
	}
	template <typename T, class C>
	map_iterator<T,C>&	map_iterator<T,C>::operator--(){
		if (!this->position)
			this->position = target->last();
		else {
			node* prev = position->previous();
			if (prev)
				this->position = prev;
			else
				throw std::length_error("Past-the-beginning map iterator.");
		}
		return *this;
	}
	template <typename T, class C>
	map_iterator<T,C> 	map_iterator<T,C>::operator++(int){
		map_iterator	oldthis(*this);
		++*this;
		return oldthis;
	}
	template <typename T, class C>
	map_iterator<T,C> 	map_iterator<T,C>::operator--(int){
		map_iterator	oldthis(*this);
		--*this;
		return oldthis;
	}
}


#endif
