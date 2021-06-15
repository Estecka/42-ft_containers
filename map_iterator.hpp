/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 16:30:54 by abaur             #+#    #+#             */
/*   Updated: 2021/06/15 17:05:54 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

#include "pair.hpp"

#include <iterator>

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
}


#endif
