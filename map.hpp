/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 16:09:02 by abaur             #+#    #+#             */
/*   Updated: 2021/06/18 16:13:14 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include "less.hpp"
#include "map_iterator.hpp"
#include "pair.hpp"
#include "reverse_iterator.hpp"
#include "reconstruct.hpp"

#include <memory>
#include <new>
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
		typename Compare = ft::less<K>,
		typename Alloc = std::allocator< pair<const K,V> >
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

		typedef ft::map_iterator<      pair_type,       map>	iterator;
		typedef ft::map_iterator<const pair_type, const map>	const_iterator;
		typedef ft::reverse_iterator<iterator>      	      reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		typedef __gnu_cxx::ptrdiff_t	difference_type;
		typedef size_t   	size_type;

		friend struct ft::map_iterator<      pair_type,       map>;
		friend struct ft::map_iterator<const pair_type, const map>;

	private:
		struct node {
			pair_type	value;
			node*	parent;
			node*	left;
			node*	right;

			node();
			node(const node& other);
			node(const pair_type& value, node* parent=NULL, node* left=NULL, node* right=NULL);
			node(const key_type& key, const mapped_type& value, node* parent=NULL, node* left=NULL, node* right=NULL);
			~node();
			node&	operator=(const node& other);

			node*	next();
			node*	previous();
			node&	leftmost();
			node&	rightmost();
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

	// ## Modifiers
		ft::pair<iterator, bool>	insert(const pair_type& pair);
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
		key_compare   	_kcomp;
		node*	_root;
		size_type	_size;

		node*	first() const;
		node*	last() const;

		// Recursively frees the node and its children.
		void	clear(node&);
		// Inserts an element somewhere below the given node.
		pair<iterator, bool>	insert(const pair_type& item, node& root);

		// Restructures the tree into a simple chained list.
		void	linearize();
	};

/******************************************************************************/
/* # Nodes                                                                    */
/******************************************************************************/

// ## Nodes
	template <typename K, typename V, typename C, typename A>
	map<K,V,C,A>::node::node() 
	: value(), parent(NULL), left(NULL), right(NULL) {
	}
	template <typename K, typename V, typename C, typename A>
	map<K,V,C,A>::node::node(const node& other) {
		new(this) node(other.value, other.parent, other.left, other.right);
	}
	template <typename K, typename V, typename C, typename A>
	map<K,V,C,A>::node::node(const key_type& key, const mapped_type& value, node* parent, node* left, node* right) 
	: value(key, value), parent(parent), left(left), right(right){
	}
	template <typename K, typename V, typename C, typename A>
	map<K,V,C,A>::node::node(const pair_type& value, node* parent, node* left, node* right) 
	: value(value), parent(parent), left(left), right(right){
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
	typename map<K,V,C,A>::node*	map<K,V,C,A>::node::next() {
		if (this->right)
			return &this->right->leftmost();
	
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
	typename map<K,V,C,A>::node*	map<K,V,C,A>::node::previous() {
		if (this->left)
			return &this->left->rightmost();
	
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
	template <typename K, typename V, typename C, typename A>
	typename map<K,V,C,A>::node&	map<K,V,C,A>::node::leftmost() {
		for (node* ilt=this; true; ilt=ilt->left)
			if (ilt->left == NULL)
				return *ilt;
	}
	template <typename K, typename V, typename C, typename A>
	typename map<K,V,C,A>::node&	map<K,V,C,A>::node::rightmost() {
		for (node* ilt=this; true; ilt=ilt->right)
			if (ilt->right == NULL)
				return *ilt;
	}
	template <typename K, typename V, typename C, typename A>
	typename map<K,V,C,A>::node*	map<K,V,C,A>::first() const {
		if (this->_root)
			return &_root->leftmost();
		else
			return NULL;
	}
	template <typename K, typename V, typename C, typename A>
	typename map<K,V,C,A>::node*	map<K,V,C,A>::last() const {
		if (this->_root)
			return &_root->rightmost();
		else
			return NULL;
	}

/******************************************************************************/
/* # Map                                                                      */
/******************************************************************************/

// ## Constructors
	template <typename K, typename V, typename C, typename A>
	map<K,V,C,A>::map(const key_compare& comp, const allocator_type& alloc) {
		this->_allocator = alloc;
		this->_kcomp = comp;
		this->_root  = NULL;
		this->_size  = 0;
	}
	template <typename K, typename V, typename C, typename A>
	map<K,V,C,A>::map(const map& other) {
		new(this) map(other.begin(), other.end(), other._kcomp, other._allocator);
	}
	template <typename K, typename V, typename C, typename A>
	template <typename IT>
	map<K,V,C,A>::map(IT begin, IT end, const key_compare& comp, const allocator_type& alloc) {
		this->_allocator = alloc;
		this->_kcomp = comp;
		this->_root  = NULL;
		this->_size  = 0;
		this->insert(begin, end);
	}
	template <typename K, typename V, typename C, typename A>
	map<K,V,C,A>::~map() {
		this->clear();
	}
	template <typename K, typename V, typename C, typename A>
	map<K,V,C,A>&	map<K,V,C,A>::operator=(const map& other) {
		reconstruct(*this, other);
		return *this;
	}

// ## Iterators
	template <typename K, typename V, typename C, typename A>
	typename map<K,V,C,A>::iterator	map<K,V,C,A>::begin() { return iterator(*this, this->first()); }
	template <typename K, typename V, typename C, typename A>
	typename map<K,V,C,A>::iterator	map<K,V,C,A>::end()   { return iterator(*this, NULL);          }
	template <typename K, typename V, typename C, typename A>
	typename map<K,V,C,A>::const_iterator	map<K,V,C,A>::begin() const { return const_iterator(*this, this->first()); }
	template <typename K, typename V, typename C, typename A>
	typename map<K,V,C,A>::const_iterator	map<K,V,C,A>::end()   const { return const_iterator(*this, NULL);          }
	template <typename K, typename V, typename C, typename A>
	typename map<K,V,C,A>::reverse_iterator	map<K,V,C,A>::rbegin() { return reverse_iterator(this->end());   }
	template <typename K, typename V, typename C, typename A>
	typename map<K,V,C,A>::reverse_iterator	map<K,V,C,A>::rend()   { return reverse_iterator(this->begin()); }
	template <typename K, typename V, typename C, typename A>
	typename map<K,V,C,A>::const_reverse_iterator	map<K,V,C,A>::rbegin() const { return reverse_iterator(this->end());   }
	template <typename K, typename V, typename C, typename A>
	typename map<K,V,C,A>::const_reverse_iterator	map<K,V,C,A>::rend()   const { return reverse_iterator(this->begin()); }

// ## Capacity
	template <typename K, typename V, typename C, typename A>
	bool	map<K,V,C,A>::empty() const {
		return this->_size > 0;
	}
	template <typename K, typename V, typename C, typename A>
	typename map<K,V,C,A>::size_type	map<K,V,C,A>::size() const {
		return this->_size;
	}

// ## Modifiers
	template <typename K, typename V, typename C, typename A>
	template <typename IT>
	void	map<K,V,C,A>::insert(IT begin, IT end) {
		for (IT it=begin; it!=end; it++)
			this->insert(*it);
	}
	template <typename K, typename V, typename C, typename A>
	ft::pair<typename map<K,V,C,A>::iterator, bool>	map<K,V,C,A>::insert(const pair_type& item) {
		if (!this->_root) {
			this->_root = new node(item);
			this->_size++;
			return ft::pair<iterator, bool>(iterator(*this, _root), true);
		}
		else
			return this->insert(item, *_root);
	}
	template <typename K, typename V, typename C, typename A>
	ft::pair<typename map<K,V,C,A>::iterator, bool>	map<K,V,C,A>::insert(const pair_type& item, node& root) {
		if (item.first == root.value.first)
			return ft::pair<iterator, bool>(iterator(*this, &root), false);

		node*& direction = (this->_kcomp(item.first, root.value.first)) ? 
		                  root.left :
		                  root.right;
		if (!direction) {
			direction = new node(item, &root);
			this->_size++;
			return ft::pair<iterator, bool>(iterator(*this, direction), true);
		}
		else
			return this->insert(item, *direction);
	}
	template <typename K, typename V, typename C, typename A>
	void	map<K,V,C,A>::clear() {
		if (this->_root)
			this->clear(*_root);
	}
	template <typename K, typename V, typename C, typename A>
	void	map<K,V,C,A>::clear(node& root) {
		if (root.left)
			this->clear(*root.left);
		if (root.right)
			this->clear(*root.right);
		delete &root;
	}

// ## Miscellaneous
	template <typename K, typename V, typename C, typename A>
	void	map<K,V,C,A>::linearize() {
		if (this->_size < 2)
			return;

		node*	it;
		node*	parent;
		node*	left;
		node*	prev;

		for (it=this->last(); it->parent()!=NULL; it=it->parent) {
			if (!it->left)
				continue;
			parent = it->parent;
			left   = it->left;
			prev   = it->previous();

			it->parent  = prev;
			prev->right = it;

			left->parent  = parent;
			parent->right = left;
		}

		this->_root = it;
	}

}

#endif
