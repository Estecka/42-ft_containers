/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 16:09:02 by abaur             #+#    #+#             */
/*   Updated: 2021/06/14 22:22:38 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include "pair.hpp"
#include "map_iterator.hpp"
#include "reverse_iterator.hpp"

#include <memory>
#include <stdlib.h>

namespace ft
{

	template<typename K, typename V, typename C, typename A>
	class	map;
	template<typename K, typename V, typename C, typename A>
	void	swap(map<K,V,C,A>& a, map<K,V,C,A>& b);


	template <
		typename K,
		typename V,
		typename Compare, // = less<K>
		typename Alloc    // = allocator<pair<const K, V>>
		>
	class map 
	{
	public:
		typedef K	key_type;
		typedef V	mapped_type;
		typedef pair<K,V>	value_type;
		typedef value_type	pair_type;
		typedef Compare	key_compare;
		typedef void	value_compare; // !

		typedef Alloc	allocator_type;
		typedef typename allocator_type::reference      	reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer      	pointer;
		typedef typename allocator_type::const_pointer	const_pointer;

		typedef ft::map_iterator<      K,       V, Compare>	iterator;
		typedef ft::map_iterator<const K, const V, Compare>	const_iterator;
		typedef ft::reverse_iterator<iterator>      	      reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		typedef __gnu_cxx::ptrdiff_t	difference_type;
		typedef size_t   	size_type;

	private:
		struct node {
			node*	parent;
			node*	left, right;

			node();
			node(const node& other);
			node(node* parent, node* left=NULL, node* right=NULL);
			~node();
			node&	operator=(const node& other);

			node*	next() const;
			node*	previous() const;
		};

	public:
	// ## Constructors
		explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
		map(const map& other);
		template <typename IT>
		map(IT first, IT last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
		~map();
		map&	operator=(const map& other);

	// ## Iterators
		iterator	begin();
		iterator	end();
		const_iterator	begin() const;
		const_iterator	end() const;
		reverse_iterator	rbegin();
		reverse_iterator	rend();
		const_reverse_iterator	rbegin() const;
		const_reverse_iterator	rend() const;

	// ## Capacity
		bool	empty() const;
		size_type	size() const;
		size_type	max_size() const;
		mapped_type&	operator[](const key_type& key);

	// ## modifiers
		pair<iterator, bool>	insert(const pair_type& pair);
		iterator	insert(iterator position, const pair_type& pair);
		template <typename IT>
		void	insert(IT begin, IT end);
		void	erase(iterator position);
		size_type	erase(const key_type& key);
		void	erase(iterator begin, iterator end);
		void	swap(map& other);
		friend void	ft::swap(map& a, map& b);
		void	clear();

	// ## Observers
		key_compare	key_comp() const;
		value_compare	value_comp() const;

	// ## Operations
		iterator      	find(const key_type& key);
		const_iterator	find(const key_type& key) const;
		size_type	count(const key_type& key) const;
		iterator      	lower_bound(const key_type& key);
		const_iterator	lower_bound(const key_type& key) const;
		iterator      	upper_bound(const key_type& key);
		const_iterator	upper_bound(const key_type& key) const;
		pair<iterator, iterator>            	equal_range(const key_type& key);
		pair<const_iterator, const_iterator>	equal_range(const key_type& key) const;
		

	private:
		allocator_type	_allocator;
		key_compare   	_comparator;
		node*	_root;
		size_type	_size;
	};

// ## Nodes
	template <typename K, typename V, typename C, typename A>
	map<K,V,C,A>::node::node() {
		new(this) node(NULL,NULL,NULL);
	}
	template <typename K, typename V, typename C, typename A>
	map<K,V,C,A>::node::node(const node& other) {
		new(this) node(other.parent, other.left, other.right);
	}
	template <typename K, typename V, typename C, typename A>
	map<K,V,C,A>::node::node(node* parent, node* left, node* right) : parent(parent), left(left), right(right){
	}
	template <typename K, typename V, typename C, typename A>
	map<K,V,C,A>::node::~node() {
	}
	template <typename K, typename V, typename C, typename A>
	typename map<K,V,C,A>::node&	map<K,V,C,A>::node::operator=(const node& other) {
		this->parent = other.parent;
		this->left   = other.left;
		this->right  = other.right;
	}
	template <typename K, typename V, typename C, typename A>
	typename map<K,V,C,A>::node*	map<K,V,C,A>::node::next() const {
		if (this->right)
			return this->right;
	
		node* current = this;
		node* parent  = this->parent;
		while (true) {
			if (!parent)
				return NULL;
			if (current == parent->left)
				return parent;
			current = parent;
			parent = current->parent;
		}
	}
	template <typename K, typename V, typename C, typename A>
	typename map<K,V,C,A>::node*	map<K,V,C,A>::node::previous() const {
		if (this->left)
			return this->left;
	
		node* current = this;
		node* parent  = this->parent;
		while (true) {
			if (!parent)
				return NULL;
			if (current == parent->right)
				return parent;
			current = parent;
			parent = current->parent;
		}
	}
}

#endif
