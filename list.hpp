/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 14:48:57 by abaur             #+#    #+#             */
/*   Updated: 2021/07/03 18:33:49 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
#define LIST_HPP

#include "lexicographical_compare.hpp"
#include "not_integer.hpp"
#include "reconstruct.hpp"
#include "reverse_iterator.hpp"
#include "swap.hpp"

#include <memory>
#include <stdexcept>
#include <stdlib.h>

namespace ft
{
	template <typename T, typename A = std::allocator<T> >
	class list
	{
	private:
		template <typename, typename>
		struct list_iterator;

	public:
		// ## Member types
		typedef T	value_type;
		typedef A	allocator_type;
		typedef typename allocator_type::reference      	reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer        	pointer;
		typedef typename allocator_type::const_pointer  	const_pointer;

		typedef list::list_iterator<      value_type,       list<T,A> >	iterator;
		typedef list::list_iterator<const value_type, const list<T,A> >	const_iterator;
		typedef ft::reverse_iterator<iterator>      	reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		typedef __gnu_cxx::ptrdiff_t	difference_type;
		typedef size_t	size_type;

		// ## Constructors
		explicit list(const allocator_type& allocator = allocator_type());
		explicit list(size_type size, const value_type& value = value_type(), const allocator_type& allocator = allocator_type());
		template <class IT>
		list(IT begin, IT end, const allocator_type& allocator = allocator_type(), NOT_INTEGER(IT) = 0);
		list(const list& other);
		~list();
		list& operator=(const list& other);

		// ## Iterators
		iterator	begin();
		iterator	end()  ;
		const_iterator	begin() const;
		const_iterator	end()   const;
		reverse_iterator	rbegin();
		reverse_iterator	rend()  ;
		const_reverse_iterator	rbegin() const;
		const_reverse_iterator	rend()   const;

		// ## Capacity
		size_type	size() const;
		size_type	max_size() const;
		bool	empty() const;

		// ## Element access
		reference      	front();
		const_reference	front() const;
		reference      	back();
		const_reference	back() const;

		// ## Modifiers
		template <class IT>
		void	assign(IT begin, IT end, NOT_INTEGER(IT) = 0);
		void	assign(size_type size, const value_type& value);
		void	push_front(const value_type& value);
		void	push_back (const value_type& value);
		void	pop_front();
		void	pop_back ();
		template <typename IT>
		void	insert(iterator index, IT begin, IT end, NOT_INTEGER(IT) = 0);
		void	insert(iterator index, const value_type& value);
		void	insert(iterator index, size_type amount, const value_type& value);
		iterator	erase(iterator position);
		iterator	erase(iterator begin, iterator end);
		void       	swap(list& other);
		void	resize(size_type size, value_type value = value_type());
		void	clear();

		// ## Operations
		void	splice(iterator index, list& source);
		void	splice(iterator index, list& source, iterator sourceIndex);
		void	splice(iterator index, list& source, iterator begin, iterator end);
		template <typename Predicate>
		void	remove_if(Predicate predicate);
		void	remove(const value_type& value);
		template <typename BinaryPredicate>
		void	unique(BinaryPredicate predicate);
		void	unique();
		template <typename Comparator>
		void	merge(list& other, Comparator comp);
		void	merge(list& other);
		template <typename Comparator>
		void	sort(Comparator comp);
		void	sort();
		void	reverse();

	private:
		struct lselt {
			value_type	value;
			lselt*	prev;
			lselt*	next;

			lselt(const value_type& value, lselt* prev = NULL, lselt* next = NULL);
			lselt(const lselt& other);
			lselt&	operator=(const lselt& other);
		};

		allocator_type	_allocator;
		size_type	_size;
		lselt*	_first;
		lselt*	_last;

		// Removes an element from the list.
		// The list itself is left in a valid state afterward.
		// The element itself is left untouched and can be destroyed or reinserted somewhere else.
		void	extract(lselt&);
		// Insert src right before dst. If dst is NULL, it will be inserted at the end of the list.
		// The list is left in a valid state afterward.
		void	insert(lselt& src, lselt* dst);
		template <typename ITT>
		lselt*	ItToNode(list_iterator<ITT, list>& it);


		template <typename V, typename Container>
		struct list_iterator
		{
		private:
			typedef typename Container::lselt	lselt;

		public:
			typedef V 	value_type;
			typedef V*	pointer;
			typedef V&	reference;
			typedef typename Container::size_type	size_type;
			typedef typename Container::size_type	difference_type;
			typedef std::bidirectional_iterator_tag	iterator_category;

			list_iterator(void);
			list_iterator(const list_iterator& other);
			list_iterator(Container* target, lselt* element);
			list_iterator&	operator=(const list_iterator& other);

			bool	operator==(const list_iterator& other) const;
			bool	operator!=(const list_iterator& other) const;

			V&	operator*() const;
			V*	operator->() const;

			list_iterator<V, Container>&	operator++();
			list_iterator<V, Container>&	operator--();
			list_iterator<V, Container> 	operator++(int);
			list_iterator<V, Container> 	operator--(int);

		private:
			Container*	target;
			lselt*	curr;
		};
	};


/******************************************************************************/
/* # List Elements                                                            */
/******************************************************************************/

	template <typename T, typename A>
	list<T,A>::lselt::lselt(const value_type& value, lselt* prev, lselt* next) {
		this->value = value;
		this->prev  = prev;
		this->next  = next;
	}
	template <typename T, typename A>
	list<T,A>::lselt::lselt(const lselt& other) {
		this->value = other.value;
		this->prev  = other.prev;
		this->next  = other.next;
	}
	template <typename T, typename A>
	typename list<T,A>::lselt&	list<T,A>::lselt::operator=(const lselt& other) {
		this->value = other.value;
		this->prev = other.prev;
		this->next = other.next;
	}


/******************************************************************************/
/* # Iterator                                                                 */
/******************************************************************************/
	
	template <typename T, typename A>
	template <typename V, typename C>
	list<T,A>::list_iterator<V,C>::list_iterator(void) {
		this->target = NULL;
		this->curr   = NULL;
	}
	template <typename T, typename A>
	template <typename V, typename C>
	list<T,A>::list_iterator<V,C>::list_iterator(const list_iterator& other) {
		this->target = other.target;
		this->curr   = other.curr;
	}
	template <typename T, typename A>
	template <typename V, typename C>
	list<T,A>::list_iterator<V,C>::list_iterator(C* target, lselt* element) {
		this->target = target;
		this->curr   = element;
	}
	template <typename T, typename A>
	template <typename V, typename C>
	typename list<T,A>::template list_iterator<V,C>&	list<T,A>::list_iterator<V,C>::operator=(const list_iterator& other) {
		this->target = other.target;
		this->curr   = other.curr;
		return *this;
	}


	template <typename T, typename A>
	template <typename V, typename C>
	bool	list<T,A>::list_iterator<V,C>::operator==(const list_iterator& other) const {
		return this->target == other.target && this->curr == other.curr;
	}
	template <typename T, typename A>
	template <typename V, typename C>
	bool	list<T,A>::list_iterator<V,C>::operator!=(const list_iterator& other) const {
		return this->target != other.target || this->curr != other.curr;
	}

	template <typename T, typename A>
	template <typename V, typename C>
	V&	list<T,A>::list_iterator<V,C>::operator*() const {
		if (!this->curr)
			throw std::logic_error("Attempted to dereference a terminating list iterator.");
		return this->curr->value;
	}
	template <typename T, typename A>
	template <typename V, typename C>
	V*	list<T,A>::list_iterator<V,C>::operator->() const {
		return &*(*this);
	}

	template <typename T, typename A>
	template <typename V, typename C>
	typename list<T,A>::template list_iterator<V,C>&	list<T,A>::list_iterator<V,C>::operator++() {
		if (!curr)
			throw std::out_of_range("Past-the-End list iterator.");
		this->curr = curr->next;
		return (*this);
	}
	template <typename T, typename A>
	template <typename V, typename C>
	typename list<T,A>::template list_iterator<V,C>&	list<T,A>::list_iterator<V,C>::operator--() {
		if (!curr)
			curr = target->_last;
		else if (!curr->prev)		
			throw std::out_of_range("Past-the-Beginning list iterator.");
		else
			curr = curr->prev;
		return (*this);
	}
	template <typename T, typename A>
	template <typename V, typename C>
	typename list<T,A>::template list_iterator<V,C> 	list<T,A>::list_iterator<V,C>::operator++(int) {
		list_iterator tmp(*this);
		++(*this);
		return tmp;
	}
	template <typename T, typename A>
	template <typename V, typename C>
	typename list<T,A>::template list_iterator<V,C> 	list<T,A>::list_iterator<V,C>::operator--(int) {
		list_iterator tmp(*this);
		--(*this);
		return tmp;
	}


/******************************************************************************/
/* # List                                                                     */
/******************************************************************************/

	// ## Constructors
	template<typename T, typename A>
	list<T,A>::list(const allocator_type& allocator) {
		this->_allocator = allocator;
		this->_size  = 0;
		this->_first = NULL;
		this->_last  = NULL;
	}

	template <typename T, typename A>
	list<T,A>::list(size_type size, const value_type& value, const allocator_type& allocator)
	{
		this->_allocator = allocator;
		if (size <= 0) {
			this->_size  = 0;
			this->_first = NULL;
			this->_last  = NULL;
		}
		else {
			this->_first = new lselt(value);
			this->_last  = _first;
			for (this->_size=1; this->_size<size; this->_size++) {
				lselt* prev = _last;
				this->_last = new lselt(value, prev, NULL);
				prev->next = _last;
			}
		}
	}
	template <typename T, typename A>
	template <class IT>
	list<T,A>::list(IT begin, IT end, const allocator_type& allocator, NOT_INTEGER(IT)) {
		this->_allocator = allocator;
		if (end == begin) {
			this->_size  = 0;
			this->_first = NULL;
			this->_last  = NULL;
		}
		else {
			this->_first = new lselt(*begin);
			this->_last  = _first;
			this->_size  = 1;
			for (begin++; begin!=end; begin++) {
				lselt* prev = _last;
				this->_last = new lselt(*begin, prev, NULL);
				prev->next  = _last;
				_size++;
			}
		}
	}
	template <typename T, typename A>
	list<T,A>::list(const list& other) {
		this->_allocator = other._allocator;
		if (other._size <= 0) {
			this->_size  = 0;
			this->_first = NULL;
			this->_last  = NULL;
		}
		else {
			this->_first = new lselt(other.front());
			this->_last  =  _first;
			this->_size  = 1;
			for (lselt* ilt=other._first->next; ilt!=NULL; ilt=ilt->next) {
				lselt* prev = this->_last;
				this->_last = new lselt(ilt->value, prev, NULL);
				prev->next = _last;
				this->_size++;
			}
		}
	}
	template <typename T, typename A>
	list<T,A>::~list() {
		this->clear();
	}

	template <typename T, typename A>
	list<T,A>& list<T,A>::operator=(const list& other){
		this->assign(other.begin(), other.end());
		return *this;
	}

	// ## Iterators
	template<typename T, typename A>
	typename list<T,A>::iterator	list<T,A>::begin() { return iterator(this, _first); }
	template<typename T, typename A>
	typename list<T,A>::iterator	list<T,A>::end()   { return iterator(this, NULL);   }
	template<typename T, typename A>
	typename list<T,A>::const_iterator	list<T,A>::begin() const { return const_iterator(this, _first); }
	template<typename T, typename A>
	typename list<T,A>::const_iterator	list<T,A>::end()   const { return const_iterator(this, NULL);   }
	template<typename T, typename A>
	typename list<T,A>::reverse_iterator	list<T,A>::rbegin() { return reverse_iterator(iterator(this, NULL));   }
	template<typename T, typename A>
	typename list<T,A>::reverse_iterator	list<T,A>::rend()   { return reverse_iterator(iterator(this, _first)); }
	template<typename T, typename A>
	typename list<T,A>::const_reverse_iterator	list<T,A>::rbegin() const { return const_reverse_iterator(const_iterator(this, NULL));   }
	template<typename T, typename A>
	typename list<T,A>::const_reverse_iterator	list<T,A>::rend()   const { return const_reverse_iterator(const_iterator(this, _first)); }


	// ## Capacity
	template <typename T, typename A>
	typename list<T,A>::size_type	list<T,A>::size() const {
		return this->_size;
	}
	template <typename T, typename A>
	typename list<T,A>::size_type	list<T,A>::max_size() const {
		return std::allocator<lselt>().max_size();
	}
	template <typename T, typename A>
	bool	list<T,A>::empty() const {
		return this->_size == 0;
	}

	// ## Element Access
	template <typename T, typename A>
	typename list<T,A>::reference      	list<T,A>::front() {
		return _first->value;
	}
	template <typename T, typename A>
	typename list<T,A>::const_reference	list<T,A>::front() const {
		return _first->value;
	}
	template <typename T, typename A>
	typename list<T,A>::reference      	list<T,A>::back() {
		return _last->value;
	}
	template <typename T, typename A>
	typename list<T,A>::const_reference	list<T,A>::back() const {
		return _last->value;
	}

	// ## Modifiers
	template <typename T, typename A>
	template <class IT>
	void	list<T,A>::assign(IT begin, IT end, NOT_INTEGER(IT)){
		iterator dst = this->begin();
		IT       src = begin;
		size_type targetsize = 0;

		for (; dst!=this->end() && src!=end; dst++, src++) {
			reconstruct(*dst, *src);
			targetsize++;
		}

		while (targetsize < this->_size)
			this->pop_back();

		for (; src != end; src++)
			this->push_back(*src);
	}
	template <typename T, typename A>
	void	list<T,A>::assign(size_type size, const value_type& value){
		while (size < this->_size)
			this->pop_back();

		if (0 < this->_size)
		for (iterator it=this->begin(); it!=this->end(); it++) {
			reconstruct(*it, value);
			size--;
		}

		for (size_type i=0; i<size; i++)
			this->push_back(value);
	}

	template <typename T, typename A>
	void	list<T,A>::push_front(const value_type& value) {
		lselt* neo = new lselt(value, NULL, _first);
		if (_first)
			_first->prev = neo;
		_first = neo;
		if (!_last)
			_last = neo;
		_size++;
	}
	template <typename T, typename A>
	void	list<T,A>::push_back (const value_type& value) {
		lselt* neo = new lselt(value, _last, NULL);
		if (_last)
			_last->next = neo;
		_last = neo;
		if (!_first)
			_first = neo;
		_size++;
	}
	template <typename T, typename A>
	void	list<T,A>::pop_front() {
		if (!_first)
			throw std::length_error("Popped empty list.");

		if (_first == _last){
			delete _first;
			_last  = NULL;
			_first = NULL;
		} 
		else {
			_first = _first->next;
			delete _first->prev;
			_first->prev = NULL;
		}

		_size--;
	}
	template <typename T, typename A>
	void	list<T,A>::pop_back () {
		if (!_last)
			throw std::length_error("Popped empty list.");

		if (_first == _last) {
			delete _last;
			_last  = NULL;
			_first = NULL;
		}
		else {
			_last = _last->prev;
			delete _last->next;
			_last->next = NULL;
		}

		_size--;
	}

	template <typename T, typename A>
	void	list<T,A>::insert(iterator index, const value_type& value) {
		lselt* elt = new lselt(value);
		this->insert(*elt, ItToNode(index));
	}
	template <typename T, typename A>
	void	list<T,A>::insert(iterator index, size_type amount, const value_type& value) {
		while (0 < amount--)
			this->insert(index, value);
	}
	template <typename T, typename A>
	template <typename IT>
	void	list<T,A>::insert(iterator index, IT begin, IT end, NOT_INTEGER(IT)) {
		for (IT it=begin; it!=end; it++)
			this->insert(index, *it);
	}

	template <typename T, typename A>
	typename list<T,A>::iterator	list<T,A>::erase(iterator position) {
		lselt* elt = ItToNode(position);
		if (elt == NULL)
			return this->end();

		position++;
		this->extract(*elt);
		delete elt;
		return position;
	}
	template <typename T, typename A>
	typename list<T,A>::iterator	list<T,A>::erase(iterator begin, iterator end) {
		if (begin == end)
			return end;

		lselt* first = ItToNode(begin);
		lselt* last  = ItToNode(end);
		last = last ? last->prev : this->_last;

		if (first->prev)
			first->prev->next = last->next;
		if (last->next)
			last->next->prev = first->prev;

		if (this->_first == first)
			this->_first = last->next;
		if (this->_last == last)
			this->_last = first->prev;

		lselt* nextilt = NULL; // Extra steps required to avoid invalid reads.
		lselt* lastilt = last->next;
		for (lselt* ilt=first; ilt!=lastilt; ilt=nextilt) {
			nextilt = ilt->next; 
			delete ilt;
			this->_size--;
		}
		return end;
	}

	template <typename T, typename A>
	void	list<T,A>::swap(list& other){
		ft::swap(this->_allocator, other._allocator);
		ft::swap(this->_size,      other._size     );
		ft::swap(this->_first,     other._first    );
		ft::swap(this->_last,      other._last     );
	}
	template <typename T, typename A>
	void	swap(list<T,A>& a, list<T,A>& b){
		a.swap(b);
	}

	template <typename T, typename A>
	void	list<T,A>::resize(size_type targetsize, value_type value) {
		while (this->_size < targetsize)
			this->push_back(value);
		while (this->_size > targetsize)
			this->pop_back();
	}


	template <typename T, typename A>
	void	list<T,A>::clear() {
		lselt*	next;
		for (lselt* ilt=this->_first; ilt!=NULL; ilt=next) {
			next = ilt->next;
			delete ilt;
		}
		this->_size  = 0;
		this->_first = NULL;
		this->_last  = NULL;
	}

// ## Operations
	template <typename T, typename A>
	void	list<T,A>::splice(iterator dstpos, list& src) {
		if (src._size <= 0)
			return;
		else
			this->splice(dstpos, src, src.begin(), src.end());
	}
	template <typename T, typename A>
	void	list<T,A>::splice(iterator dstpos, list& src, iterator srcpos) {
		this->splice(dstpos, src, srcpos, ++srcpos);
	}
	template <typename T, typename A>
	void	list<T,A>::splice(iterator dstpos, list& src, iterator srcbegin, iterator srcend) {
		size_type amount = 0;
		for (iterator it=srcbegin; it!=srcend; it++)
			amount++;
		if (amount <= 0)
			return;

		lselt* srcleft  = src.ItToNode(srcbegin);
		lselt* srcright = src.ItToNode(--srcend);
		lselt* dstleft  = NULL;
		lselt* dstright = NULL;
		if (dstpos == this->end())
			dstleft = this->_last;
		else {
			dstright  = ItToNode(dstpos);
			dstleft   = dstright->prev;
		}

		// Extract elts from the source.
		if (srcleft->prev)
			srcleft->prev->next = srcright->next;
		else
			src._first = srcright->next;
		if (srcright->next)
			srcright->next->prev = srcleft->prev;
		else
			src._last  = srcleft ->prev;
		src._size -= amount;

		// Insert the dangling elts into the destination
		if (dstleft)
			dstleft ->next = srcleft ;
		else
			this->_first = srcleft ;
		if (dstright)
			dstright->prev = srcright;
		else
			this->_last  = srcright;
		srcleft ->prev = dstleft;
		srcright->next = dstright;
		this->_size += amount;
	}

	template <typename T, typename A>
	void	list<T,A>::remove(const value_type& value) {
		lselt* ilt = this->_first;
		lselt* next;

		while (ilt != NULL) {
			next = ilt->next;
			if (ilt->value == value) {
				this->extract(*ilt);
				delete ilt;
			}
			ilt = next;
		}
	}
	template <typename T, typename A>
	template <typename P>
	void	list<T,A>::remove_if(P predicate) {
		lselt* ilt = this->_first;
		lselt* next;

		while (ilt != NULL) {
			next = ilt->next;
			if (predicate(ilt->value)) {
				this->extract(*ilt);
				delete ilt;
			}
			ilt = next;
		}
	}

	template <typename T>
	static bool	unique(const T& a, const T& b) {
		return a == b;
	}
	template <typename T, typename A>
	void	list<T,A>::unique() {
		this->unique(&ft::unique<T>);
	}
	template <typename T, typename A>
	template <typename P>
	void	list<T,A>::unique(P predicate) {
		for (lselt* ilt=_first; ilt!=NULL && ilt->next!=NULL; ilt=ilt->next) {
			while (predicate(ilt->next->value, ilt->value)) {
				lselt* del = ilt->next;
				this->extract(*del);
				delete del;
			}
		}
	}

	template <typename T>
	static bool	issmallerthan(T& a, T& b) {
		return a < b;
	}

	template <typename T, typename A>
	void	list<T,A>::sort() {
		return this->sort(&ft::issmallerthan<T>);
	}
	template <typename T, typename A>
	template <typename C>
	void	list<T,A>::sort(C goesbefore) {
		for (lselt* ilt=this->_first; ilt!=NULL && ilt->next!=NULL; ilt=ilt->next) {
			while (ilt->next && !goesbefore(ilt->value, ilt->next->value))
			{
				lselt* transit = ilt->next;
				this->extract(*ilt->next);
				for (lselt* jlt=ilt; true; jlt=jlt->prev) {
					if (jlt->prev == NULL || !goesbefore(transit->value, jlt->prev->value)) {
						this->insert(*transit, jlt);
						break;
					}
				}
			}
		}
	}

	template <typename T, typename A>
	void	list<T,A>::merge(list& other) {
		return this->merge(other, &ft::issmallerthan<T>);
	}
	template <typename T, typename A>
	template <typename C>
	void	list<T,A>::merge(list& other, C goesbefore) {
		if (this->empty())
			return ft::swap(*this, other);
		
		iterator srcit = other.begin();
		iterator dstit = this->begin();
		while (srcit != other.end()) {
			iterator nextit = srcit;
			nextit++;

			while (dstit!=this->end() && !goesbefore(*srcit, *dstit))
				dstit++;
			this->splice(dstit, other, srcit);

			srcit = nextit;
		}
	}

	template <typename T, typename A>
	void	list<T,A>::reverse() {
		ft::swap(this->_first, this->_last);

		for (lselt* ilt=_first; ilt!=NULL; ilt=ilt->next)
			ft::swap(ilt->prev, ilt->next);
	}

// ## Privates
	template <typename T, typename A>
	void	list<T,A>::extract(lselt& element) {
		if (element.next)
			element.next->prev = element.prev;
		else
			this->_last = element.prev;
		if (element.prev)
			element.prev->next = element.next;
		else
			this->_first = element.next;
		this->_size--;
	}
	template <typename T, typename A>
	void	list<T,A>::insert(lselt& elt, lselt* dst) {
		if (dst == NULL) {
			elt.prev = this->_last;
			elt.next = NULL;
			this->_last = &elt;
			if (this->_size == 0)
				this->_first = &elt;
		}
		else if (dst == this->_first) {
			elt.prev = NULL;
			elt.next = this->_first;
			this->_first = &elt;
		}
		else {
			elt.next = dst;
			elt.prev = dst->prev;
		}

		if (elt.prev)
			elt.prev->next = &elt;
		if (elt.next)
			elt.next->prev = &elt;

		this->_size++;
	}
	template <typename T, typename A>
	template <typename ITT>
	typename list<T,A>::lselt*	list<T,A>::ItToNode(list_iterator<ITT, list>& it){
		T*	 adress;
		try {
			adress = &*it;
		} catch(std::logic_error&){
			return NULL;
		}

		for (lselt* ilt=_first; ilt!=NULL; ilt=ilt->next)
			if (&(ilt->value) == adress)
				return ilt;
		return NULL;
	}
}

// ## Operators
template <typename T, typename A>
bool	operator==(const ft::list<T,A>& a, const ft::list<T,A>& b) {
	return ft::lexicograph_compare(a, b) == 0;
}
template <typename T, typename A>
bool	operator!=(const ft::list<T,A>& a, const ft::list<T,A>& b) {
	return ft::lexicograph_compare(a, b) != 0;
}
template <typename T, typename A>
bool	operator< (const ft::list<T,A>& a, const ft::list<T,A>& b) {
	return ft::lexicograph_compare(a, b) <  0;
}
template <typename T, typename A>
bool	operator> (const ft::list<T,A>& a, const ft::list<T,A>& b) {
	return ft::lexicograph_compare(a, b) >  0;
}
template <typename T, typename A>
bool	operator<=(const ft::list<T,A>& a, const ft::list<T,A>& b) {
	return ft::lexicograph_compare(a, b) <= 0;
}
template <typename T, typename A>
bool	operator>=(const ft::list<T,A>& a, const ft::list<T,A>& b) {
	return ft::lexicograph_compare(a, b) >= 0;
}

#endif
