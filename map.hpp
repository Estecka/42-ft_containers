/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 16:09:02 by abaur             #+#    #+#             */
/*   Updated: 2021/07/12 18:01:18 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include "less.hpp"
#include "pair.hpp"
#include "reverse_iterator.hpp"
#include "reconstruct.hpp"
#include "swap.hpp"

#include <memory>
#include <new>
#include <stdexcept>
#include <stdlib.h>

namespace ft
{
	template <
		typename K,
		typename V,
		typename C = ft::less<K>,
		typename A = std::allocator< pair<const K,V> >
		>
	class map 
	{
	private:
		template <typename T, typename M>
		struct map_iterator;

	public:
		typedef K	key_type;
		typedef V	mapped_type;
		typedef pair<K,V>	pair_type;
		typedef pair_type	value_type;
		typedef C                  	key_compare;

		typedef A	allocator_type;
		typedef typename allocator_type::reference      	reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer      	pointer;
		typedef typename allocator_type::const_pointer	const_pointer;

		typedef map::map_iterator<      pair_type,       map>	iterator;
		typedef map::map_iterator<const pair_type, const map>	const_iterator;
		typedef ft::reverse_iterator<iterator>      	      reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		typedef __gnu_cxx::ptrdiff_t	difference_type;
		typedef size_t   	size_type;

		struct value_compare
		{
			ft::less<key_type>	less;
			bool	operator()(const pair_type& a, const pair_type& b) { return less(a.first, b.first); }
		};

	private:
		struct node {
			pair_type	value;
			node*	parent;
			node*	left;
			node*	right;
			int  	weight;

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
		value_compare 	_vcomp;
		node*	_root;
		size_type	_size;

		node*	first() const;
		node*	last() const;
		node*	at(const key_type& key) const;
		node*	closest(const key_type& key) const;
		node*	upper_boundn(const key_type& key) const;
		node*	lower_boundn(const key_type& key) const;

		void	erase(node&);
		void	erase_reconnect(node* parent, node* left, node* right, bool left_to_parent);
		// Recursively frees the node and its children.
		void	clear(node&);
		// Restructures the tree into a simple chained list.
		void	linearize();
		template <typename ITT>
		node*	ItToNode(const map_iterator<ITT, map>& it);

		template <typename T, typename Container>
		struct map_iterator 
		{
		private:
			typedef typename map::node	node;

		public:
			typedef T	value_type;
			typedef T*	pointer;
			typedef T&	reference;
			typedef typename Container::size_type	size_type;
			typedef typename Container::size_type	difference_type;
			typedef std::bidirectional_iterator_tag	iterator_category;

		public:
			map_iterator();
			map_iterator(const map::iterator& other);
			map_iterator(const map::const_iterator& other);
			map_iterator(Container& target, node* position);
			map_iterator&	operator=(const map_iterator& other);

			bool	operator==(const map::iterator& other) const;
			bool	operator!=(const map::iterator& other) const;
			bool	operator==(const map::const_iterator& other) const;
			bool	operator!=(const map::const_iterator& other) const;

			value_type&	operator*() const;
			value_type*	operator->() const;

			map_iterator&	operator++();
			map_iterator&	operator--();
			map_iterator 	operator++(int);
			map_iterator 	operator--(int);

		private:
			Container*	target;
			node*     	position;

			template<typename T2, typename C2>
			static const node*	GetNode(const map_iterator<T2,C2>&);
		};
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
/* # Iterators                                                                */
/******************************************************************************/

	template <typename K, typename V, typename C, typename A>
	template <typename T, typename M>
	map<K,V,C,A>::map_iterator<T,M>::map_iterator()
	: target(), position() {
	}
	template <typename K, typename V, typename C, typename A>
	template <typename T, class M>
	map<K,V,C,A>::map_iterator<T,M>::map_iterator(const iterator& other) {
		*this = *(const map_iterator*)&other;
	}
	template <typename K, typename V, typename C, typename A>
	template <typename T, class M>
	map<K,V,C,A>::map_iterator<T,M>::map_iterator(const const_iterator& other) {
		*this = *(const map_iterator*)&other;
		return;

		// Asserts at compile time that this does not unconst a const_iterator.
		T* nil = (const T*)NULL;
		(void)nil;
	}
	template <typename K, typename V, typename C, typename A>
	template <typename T, class M>
	map<K,V,C,A>::map_iterator<T,M>::map_iterator(M& target, node* position)
	: target(&target), position(position) {
	}

	template <typename K, typename V, typename C, typename A>
	template <typename T, class M>
	typename map<K,V,C,A>::template map_iterator<T,M>&	map<K,V,C,A>::map_iterator<T,M>::operator=(const map_iterator& other){
		this->target   = other.target;
		this->position = other.position;
		return *this;
	}
	template <typename K, typename V, typename C, typename A>
	template <typename T, class M>
	bool	map<K,V,C,A>::map_iterator<T,M>::operator==(const iterator& other) const {
		return this->position == GetNode(other);
	}
	template <typename K, typename V, typename C, typename A>
	template <typename T, class M>
	bool	map<K,V,C,A>::map_iterator<T,M>::operator!=(const iterator& other) const {
		return this->position != GetNode(other);
	}
	template <typename K, typename V, typename C, typename A>
	template <typename T, class M>
	bool	map<K,V,C,A>::map_iterator<T,M>::operator==(const const_iterator& other) const {
		return this->position == GetNode(other);
	}
	template <typename K, typename V, typename C, typename A>
	template <typename T, class M>
	bool	map<K,V,C,A>::map_iterator<T,M>::operator!=(const const_iterator& other) const {
		return this->position != GetNode(other);
	}

	template <typename K, typename V, typename C, typename A>
	template <typename T, class M>
	typename map<K,V,C,A>::template map_iterator<T,M>::value_type&	map<K,V,C,A>::map_iterator<T,M>::operator*() const {
		if (!position)
			throw std::logic_error("Attempted to dereference a terminating map iterator.");
		return (position->value);
	}
	template <typename K, typename V, typename C, typename A>
	template <typename T, class M>
	typename map<K,V,C,A>::template map_iterator<T,M>::value_type*	map<K,V,C,A>::map_iterator<T,M>::operator->() const {
		return &**this;
	}

	template <typename K, typename V, typename C, typename A>
	template <typename T, class M>
	typename map<K,V,C,A>::template map_iterator<T,M>&	map<K,V,C,A>::map_iterator<T,M>::operator++(){
		if (this->position) {
			this->position = position->next();
			return *this;
		}
		else
			throw std::length_error("Past-the-end map iterator.");
	}
	template <typename K, typename V, typename C, typename A>
	template <typename T, class M>
	typename map<K,V,C,A>::template map_iterator<T,M>&	map<K,V,C,A>::map_iterator<T,M>::operator--(){
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
	template <typename K, typename V, typename C, typename A>
	template <typename T, class M>
	typename map<K,V,C,A>::template map_iterator<T,M> 	map<K,V,C,A>::map_iterator<T,M>::operator++(int){
		map_iterator	oldthis(*this);
		++*this;
		return oldthis;
	}
	template <typename K, typename V, typename C, typename A>
	template <typename T, class M>
	typename map<K,V,C,A>::template map_iterator<T,M> 	map<K,V,C,A>::map_iterator<T,M>::operator--(int){
		map_iterator	oldthis(*this);
		--*this;
		return oldthis;
	}
	template <typename K, typename V, typename C, typename A>
	template <typename T , class M >
	template <typename T2, class M2>
	const typename map<K,V,C,A>::node*	map<K,V,C,A>::map_iterator<T,M>::GetNode(const map_iterator<T2,M2>& other){
		return ((const map_iterator*)&other)->position;
	}


/******************************************************************************/
/* # Map                                                                      */
/******************************************************************************/

// ## Constructors
	template <typename K, typename V, typename C, typename A>
	map<K,V,C,A>::map(const key_compare& comp, const allocator_type& alloc) {
		this->_allocator = alloc;
		this->_kcomp = comp;
		this->_vcomp = value_compare();
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
		this->_vcomp = value_compare();
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
	typename map<K,V,C,A>::const_reverse_iterator	map<K,V,C,A>::rbegin() const { return const_reverse_iterator(this->end());   }
	template <typename K, typename V, typename C, typename A>
	typename map<K,V,C,A>::const_reverse_iterator	map<K,V,C,A>::rend()   const { return const_reverse_iterator(this->begin()); }

// ## Capacity
	template <typename K, typename V, typename C, typename A>
	bool	map<K,V,C,A>::empty() const {
		return this->_size <= 0;
	}
	template <typename K, typename V, typename C, typename A>
	typename map<K,V,C,A>::size_type	map<K,V,C,A>::size() const {
		return this->_size;
	}
	template <typename K, typename V, typename C, typename A>
	typename map<K,V,C,A>::size_type	map<K,V,C,A>::max_size() const {
		return std::allocator<node>().max_size();
	}
	template <typename K, typename V, typename C, typename A>
	typename map<K,V,C,A>::mapped_type&	map<K,V,C,A>::operator[](const key_type& key) {
		return (this->insert(pair_type(key, mapped_type())).first)->second;
	}
	template <typename K, typename V, typename C, typename A>
	typename map<K,V,C,A>::node*	map<K,V,C,A>::at(const key_type& key) const {
		node* it = _root;

		while (it != NULL) {
			if (_kcomp(key, it->value.first))
				it = it->left;
			else if (_kcomp(it->value.first, key))
				it = it->right;
			else
				return it;
		}
		return NULL;
	}
	template <typename K, typename V, typename C, typename A>
	typename map<K,V,C,A>::node*	map<K,V,C,A>::closest(const key_type& key) const {
		node* it = _root;
		node* previt = NULL;

		while (it != NULL) {
			previt = it;
			if (_kcomp(key, it->value.first))
				it = it->left;
			else if (_kcomp(it->value.first, key))
				it = it->right;
			else
				return it;
		}
		return previt;
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
		node*	parent  = NULL;
		node**	current = &_root;

		while (*current != NULL) {
			parent = (*current);
			if (_kcomp(item.first, (**current).value.first))
				current = &(**current).left;
			else if (_kcomp((**current).value.first, item.first))
				current = &(**current).right;
			else
				return ft::pair<iterator,bool> (iterator(*this, *current), false);
		}

		*current = new node(item);
		(**current).parent = parent;
		_size++;
		return ft::pair<iterator,bool> (iterator(*this, *current), true);
	}
	template <typename K, typename V, typename C, typename A>
	typename map<K,V,C,A>::iterator	map<K,V,C,A>::insert(iterator previt, const pair_type& pair) {
		node* prevlt = ItToNode(previt);
		if (prevlt == NULL || !_kcomp(prevlt->value.first, pair.first))
			invalid_hint:
			return this->insert(pair).first;

		node* nextlt = prevlt->next();
		if (nextlt != NULL && !_kcomp(pair.first, nextlt->value.first))
			goto invalid_hint;

		node* it = new node(pair);
		it->parent = prevlt;
		it->right  = prevlt->right;
		it->parent->right = it;
		if (it->right)
			it->right->parent = it;

		this->_size++;
		return iterator(*this, it);
	}

	template <typename K, typename V, typename C, typename A>
	void	map<K,V,C,A>::erase(iterator position) {
		node*	target = ItToNode(position);
		if (target != NULL)
			this->erase(*target);
	}
	template <typename K, typename V, typename C, typename A>
	typename map<K,V,C,A>::size_type	map<K,V,C,A>::erase(const key_type& key) {
		node* position = this->at(key);
		if (position) {
			this->erase(*position);
			return 1;
		}
		else
			return 0;
	}
	template <typename K, typename V, typename C, typename A>
	void	map<K,V,C,A>::erase(node& position) {
		node*	parent = position.parent;
		node*	left   = position.left;
		node*	right  = position.right;
		bool	left_to_parent = (parent && parent->left==&position);

		delete &position;
		this->_size--;
		this->erase_reconnect(parent, left, right, left_to_parent);
	}
	template <typename K, typename V, typename C, typename A>
	void	map<K,V,C,A>::erase(iterator begin, iterator end) {
		node*	first = ItToNode(begin);
		node*	last  = ItToNode(end);

		node*	iltpp;
		for (node*ilt=first; ilt!=last; ilt=iltpp) {
			iltpp = ilt->next();
			this->erase(*ilt);
		}
	}
	template <typename K, typename V, typename C, typename A>
	void	map<K,V,C,A>::erase_reconnect(node* parent, node* left, node* right, bool left_to_parent) {
		node*	firstheir  = left ? left  : right;
		node*	secondheir = left ? right : NULL;

		if (parent) {
			if (left_to_parent)
				parent->left  = firstheir;
			else
				parent->right = firstheir;
		}
		else
			this->_root = firstheir;

		if (firstheir) {
			firstheir->parent = parent;
			if (secondheir) {
				secondheir->parent = &firstheir->rightmost();
				secondheir->parent->right = secondheir;
			}
		}
	}

	template <typename K, typename V, typename C, typename A>
	void	map<K,V,C,A>::swap(map& other) {
		ft::swap(this->_allocator, other._allocator);
		ft::swap(this->_kcomp,     other._kcomp    );
		ft::swap(this->_root,      other._root     );
		ft::swap(this->_size,      other._size     );
	}
	template <typename K, typename V, typename C, typename A>
	void	swap(map<K,V,C,A>& a, map<K,V,C,A>& b) {
		a.swap(b);
	}

	template <typename K, typename V, typename C, typename A>
	void	map<K,V,C,A>::clear() {
		if (this->_root)
			this->clear(*_root);
		this->_size = 0;
		this->_root = NULL;
	}
	template <typename K, typename V, typename C, typename A>
	void	map<K,V,C,A>::clear(node& root) {
		if (root.left)
			this->clear(*root.left);
		if (root.right)
			this->clear(*root.right);
		delete &root;
	}

// ## Observers
	template <typename K, typename V, typename C, typename A>
	typename map<K,V,C,A>::key_compare	map<K,V,C,A>::key_comp() const {
		return this->_kcomp;
	}
	template <typename K, typename V, typename C, typename A>
	typename map<K,V,C,A>::value_compare	map<K,V,C,A>::value_comp() const {
		return this->_vcomp;
	}

// ## Operations
	template <typename K, typename V, typename C, typename A>
	typename map<K,V,C,A>::iterator	map<K,V,C,A>::find(const key_type& key) {
		return iterator(*this, at(key));
	}
	template <typename K, typename V, typename C, typename A>
	typename map<K,V,C,A>::const_iterator	map<K,V,C,A>::find(const key_type& key) const {
		return const_iterator(*this, at(key));
	}

	template <typename K, typename V, typename C, typename A>
	typename map<K,V,C,A>::size_type	map<K,V,C,A>::count(const key_type& key) const {
		return this->at(key) ? 1 : 0;
	}

	template <typename K, typename V, typename C, typename A>
	typename map<K,V,C,A>::iterator	map<K,V,C,A>::upper_bound(const key_type& key) {
		return iterator(*this, upper_boundn(key));
	}
	template <typename K, typename V, typename C, typename A>
	typename map<K,V,C,A>::const_iterator	map<K,V,C,A>::upper_bound(const key_type& key) const {
		return const_iterator(*this, upper_boundn(key));
	}
	template <typename K, typename V, typename C, typename A>
	typename map<K,V,C,A>::node*	map<K,V,C,A>::upper_boundn(const key_type& key) const {
		if (this->_size <= 0)
			return NULL;
		node* closest = this->closest(key);
		if (!_kcomp(key, closest->value.first))
			return closest->next();
		else
			return closest;
	}

	template <typename K, typename V, typename C, typename A>
	typename map<K,V,C,A>::iterator	map<K,V,C,A>::lower_bound(const key_type& key) {
		return iterator(*this, lower_boundn(key));
	}
	template <typename K, typename V, typename C, typename A>
	typename map<K,V,C,A>::const_iterator	map<K,V,C,A>::lower_bound(const key_type& key) const {
		return const_iterator(*this, lower_boundn(key));
	}
	template <typename K, typename V, typename C, typename A>
	typename map<K,V,C,A>::node*	map<K,V,C,A>::lower_boundn(const key_type& key) const {
		if (this->_size <= 0)
			return NULL;
		node* closest = this->closest(key);
		if (_kcomp(closest->value.first, key))
			return closest->next();
		else
			return closest;
	}

	template <typename K, typename V, typename C, typename A>
	ft::pair<typename map<K,V,C,A>::iterator, typename map<K,V,C,A>::iterator>	map<K,V,C,A>::equal_range(const key_type& key) {
		return ft::pair<iterator, iterator>(
			this->lower_bound(key),
			this->upper_bound(key)
		);
	}
	template <typename K, typename V, typename C, typename A>
	ft::pair<typename map<K,V,C,A>::const_iterator, typename map<K,V,C,A>::const_iterator>	map<K,V,C,A>::equal_range(const key_type& key) const {
		return ft::pair<const_iterator, const_iterator>(
			this->lower_bound(key),
			this->upper_bound(key)
		);
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

	template <typename K, typename V, typename C, typename A>
	template <typename ITT>
	typename map<K,V,C,A>::node*	map<K,V,C,A>::ItToNode(const map_iterator<ITT, map>& it){
		key_type key;
		try {
			key = (*it).first;
		} catch (std::logic_error&) {
			return NULL;
		}
		return this->at(key);
	}
}

// ## Operators
template <typename K, typename V, typename C, typename A>
bool	operator==(const ft::map<K,V,C,A>& a, const ft::map<K,V,C,A>& b) {
	if (a.size() != b.size())
		return false;
	return ft::lexicograph_compare(a, b) == 0;
}
template <typename K, typename V, typename C, typename A>
bool	operator!=(const ft::map<K,V,C,A>& a, const ft::map<K,V,C,A>& b) {
	if (a.size() != b.size())
		return true;
	return ft::lexicograph_compare(a, b) != 0;
}
template <typename K, typename V, typename C, typename A>
bool	operator< (const ft::map<K,V,C,A>& a, const ft::map<K,V,C,A>& b) {
	return ft::lexicograph_compare(a, b) <  0;
}
template <typename K, typename V, typename C, typename A>
bool	operator> (const ft::map<K,V,C,A>& a, const ft::map<K,V,C,A>& b) {
	return ft::lexicograph_compare(a, b) >  0;
}
template <typename K, typename V, typename C, typename A>
bool	operator<=(const ft::map<K,V,C,A>& a, const ft::map<K,V,C,A>& b) {
	return ft::lexicograph_compare(a, b) <= 0;
}
template <typename K, typename V, typename C, typename A>
bool	operator>=(const ft::map<K,V,C,A>& a, const ft::map<K,V,C,A>& b) {
	return ft::lexicograph_compare(a, b) >= 0;
}

#endif
