/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 16:30:54 by abaur             #+#    #+#             */
/*   Updated: 2021/06/15 17:43:21 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

#include "pair.hpp"

#include <iterator>
#include <stdexcept>

namespace ft
{
	template <typename K, typename V, typename Container>
	struct map_iterator 
	{
	private:
		typedef typename Container::node	node;

	public:
		typedef ft::pair<K,V>	pair_type;
		typedef ft::pair<K,V>	value_type;
		typedef ft::pair<K,V>*	pointer;
		typedef ft::pair<K,V>&	reference;
		typedef typename Container::size_type	size_type;
		typedef typename Container::size_type	difference_type;
		typedef std::bidirectional_iterator_tag	iterator_category;

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

	
		template <typename K, typename V, class C>
		map_iterator<K,V,C>::map_iterator()
		: target(), position() {
		}
		template <typename K, typename V, class C>
		map_iterator<K,V,C>::map_iterator(const map_iterator& other)
		:target(other.target), position(other.position) {
		}
		template <typename K, typename V, class C>
		map_iterator<K,V,C>::map_iterator(C& target, node* position)
		: target(&target), position(position) {
		}

		template <typename K, typename V, class C>
		map_iterator<K,V,C>&	map_iterator<K,V,C>::operator=(const map_iterator& other){
			this->target   = other.target;
			this->position = other.position;
		}
		template <typename K, typename V, class C>
		bool	map_iterator<K,V,C>::operator==(const map_iterator& other) const {
			return (this->target == other.target) && (this->position == other.position);
		}
		template <typename K, typename V, class C>
		bool	map_iterator<K,V,C>::operator!=(const map_iterator& other) const {
			return (this->target != other.target) || (this->position != other.position);
		}

		template <typename K, typename V, class C>
		typename map_iterator<K,V,C>::value_type&	map_iterator<K,V,C>::operator*() const {
			return *(position->value);
		}
		template <typename K, typename V, class C>
		typename map_iterator<K,V,C>::value_type*	map_iterator<K,V,C>::operator->() const {
			return &**this;
		}

		template <typename K, typename V, class C>
		map_iterator<K,V,C>&	map_iterator<K,V,C>::operator++(){
			if (this->position) {
				this->position = position->next();
				return *this;
			}
			else
				throw std::length_error("Past-the-end map iterator.");
		}
		template <typename K, typename V, class C>
		map_iterator<K,V,C>&	map_iterator<K,V,C>::operator--(){
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
		template <typename K, typename V, class C>
		map_iterator<K,V,C> 	map_iterator<K,V,C>::operator++(int){
			map_iterator	oldthis(this);
			++this;
			return oldthis;
		}
		template <typename K, typename V, class C>
		map_iterator<K,V,C> 	map_iterator<K,V,C>::operator--(int){
			map_iterator	oldthis(this);
			--this;
			return oldthis;
		}
}


#endif
