/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 14:48:57 by abaur             #+#    #+#             */
/*   Updated: 2021/06/01 14:27:29 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
#define LIST_HPP

#include <memory>
#include <stdlib.h>

#include "reconstruct.hpp"
#include "reverse_iterator.hpp"
#include "swap.hpp"
#include "list_iterator.hpp"
#include "not_integer.hpp"

namespace ft
{
	template <typename T, typename A>
	class	list;
	template <typename T, typename A>
	void	swap(list<T,A>& a, list<T,A>& b);


	template <typename T, typename A = std::allocator<T> >
	class list
	{
	public:
		// ## Member types
		typedef T	value_type;
		typedef A	allocator_type;
		typedef typename allocator_type::reference      	reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer        	pointer;
		typedef typename allocator_type::const_pointer  	const_pointer;

		friend	struct ft::list_iterator<      value_type,       list<T,A> >;
		friend	struct ft::list_iterator<const value_type, const list<T,A> >;
		typedef ft::list_iterator<      value_type,       list<T,A> >	iterator;
		typedef ft::list_iterator<const value_type, const list<T,A> >	const_iterator;
		typedef ft::reverse_iterator<iterator>      	reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		typedef __gnu_cxx::ptrdiff_t	difference_type;
		typedef size_t   	size_type;

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
		friend void	ft::swap<T,A>(list<T,A>& a, list<T,A>& b);
		void	resize(size_type size, value_type value = value_type());
		void	clear();

		// ## Operations
		void	splice(iterator index, list& source);
		void	splice(iterator index, list& source, iterator sourceIndex);
		void	splice(iterator index, list& source, iterator begin, iterator end);
		template <typename Predicate>
		void	removeif(Predicate predicate);
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
	};

	// ## List Elements
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
		lselt* current = _first;
		lselt* next;
		while (current) {
			next = current->next;
			delete current;
			current = next;
		}
	}

	// list& operator=(const list& other);

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

		if (index == this->end()) {
			elt->prev = this->_last;
			elt->next = NULL;
			this->_last = elt;
		}
		else if (index == this->begin()) {
			elt->prev = NULL;
			elt->next = this->_first;
			this->_first = elt;
		}
		else {
			elt->next = index.curr;
			elt->prev = index.curr->prev;
		}

		if (elt->prev)
			elt->prev->next = elt;
		if (elt->next)
			elt->next->prev = elt;

		this->_size++;
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
		if (position == this->end())
			return this->end();

		lselt* elt = position.curr;
		position++;
		if (elt->prev)
			elt->prev->next = elt->next;
		if (elt->next)
			elt->next->prev = elt->prev;

		if (this->_first == elt)
			this->_first = elt->next;
		if (this->_last == elt)
			this->_last = elt->prev;

		delete elt;
		this->_size--;
		return position;
	}
	template <typename T, typename A>
	typename list<T,A>::iterator	list<T,A>::erase(iterator begin, iterator end) {
		if (begin == end)
			return end;

		lselt* first = begin.curr;
		lselt* last  = (end==this->end()) ? this->_last : end.curr->prev;

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
		list	oldthis(*this);
		
		this->assign(other.begin(),   other.end()  );
		other.assign(oldthis.begin(), oldthis.end());
	}
	template <typename T, typename A>
	void	swap(list<T,A>& a, list<T,A>& b){

		ft::swap(a._allocator, b._allocator);
		ft::swap(a._size,  b._size );
		ft::swap(a._first, b._first);
		ft::swap(a._last,  b._last );
	}

	template <typename T, typename A>
	void	list<T,A>::resize(size_type targetsize, value_type value) {
		while (this->_size < targetsize)
			this->push_back(value);
		while (this->_size > targetsize)
			this->pop_back();
	}
}

#endif
