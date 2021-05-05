/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 14:48:57 by abaur             #+#    #+#             */
/*   Updated: 2021/05/05 17:42:40 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
#define LIST_HPP

#include <memory>
#include <stdlib.h>

#include "reverse_iterator.hpp"
#include "list_iterator.hpp"

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
		list(IT begin, IT end, const allocator_type& allocator = allocator_type());
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
		void	assign(IT begin, IT end);
		void	assign(size_type size, const value_type& value);
		void	push_front(const value_type& value);
		void	push_back (const value_type& value);
		void	pop_front();
		void	pop_back ();
		void	insert(iterator index, const value_type& value);
		void	insert(iterator index, size_type amount, const value_type& value);
		template <typename IT>
		void	insert(iterator index, IT begin, IT end);
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
	list<T,A>::list(IT begin, IT end, const allocator_type& allocator) {
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
	void	list<T,A>::push_front(const value_type& value) {
		lselt* neo = new lselt(value);
		if (_first)
			_first->prev = neo;
		_first = neo;
		if (!_last)
			_last = neo;
		_size++;
	}
	template <typename T, typename A>
	void	list<T,A>::push_back (const value_type& value) {
		lselt* neo = new lselt(value);
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
}

#endif
