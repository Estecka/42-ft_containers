/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 15:02:08 by abaur             #+#    #+#             */
/*   Updated: 2021/04/24 14:33:33 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "vector_iterator.hpp"

#include <memory>
#include <iterator>

namespace ft
{
	template <typename T, typename Alloc = std::allocator<T> >
	class vector
	{
	public:
	// ## Member types
		typedef T    	value_type;
		typedef Alloc	allocator_type;
		typedef typename allocator_type::reference      	reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer        	pointer;
		typedef typename allocator_type::const_pointer  	const_pointer;

		friend	struct vector_iterator<pointer, vector<T,Alloc> >;
		friend	struct vector_iterator<const_pointer, const vector<T,Alloc> >;
		typedef vector_iterator<reference, vector<T,Alloc> >            	iterator;
		typedef vector_iterator<const_reference, const vector<T,Alloc> >	const_iterator;
		typedef std::reverse_iterator<iterator>      	reverse_iterator;
		typedef std::reverse_iterator<const_iterator>	const_reverse_iterator;

		typedef __gnu_cxx::ptrdiff_t	difference_type;
		typedef size_t   	size_type;

	// ## Constructors
		explicit vector(const allocator_type& allocator = allocator_type());
		explicit vector(size_type size, const value_type& value = value_type(), const allocator_type& allocator = allocator_type());
		template <class IT>
		vector(IT begin, IT end, const allocator_type& allocator = allocator_type());
		vector(const vector& other);
		~vector();
		vector& operator=(const vector& other);

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
		size_type	capacity() const;
		size_type	max_size() const;
		bool	empty() const;
		void	resize(size_type size, value_type value = value_type());
		void	reserve(size_type capacity);

	// ## Element access
		reference      	operator[](size_t index);
		const_reference	operator[](size_t index) const;
		reference      	at(size_t index);
		const_reference	at(size_t index) const;
		reference      	front();
		const_reference	front() const;
		reference      	back();
		const_reference	back() const;

	// ## Modifiers
		template <class IT>
		void	assign(IT begin, IT end);
		void	assign(size_type size, const value_type& value);
		void	push_back(const value_type& value);
		void	pop_back(const value_type& value);
		void	insert(iterator index, const value_type& value);
		void	insert(iterator index, size_type amount, const value_type& value);
		template <typename IT>
		void	insert(iterator index, IT begin, IT end);
		iterator	erase(iterator position);
		iterator	erase(iterator begin, iterator end);
		void       	swap(vector& other);
		friend void	swap(vector& a, vector& b);
		void	clear();
		

	private:
		allocator_type	_allocator;
		value_type*	_c;
		size_type	_capacity;
		size_type	_size;
	};

	// ## Constructors
	template <typename T, typename A>
	vector<T,A>::vector(const A& allocator) {
		this->_allocator = allocator;
		this->_c        = NULL;
		this->_capacity = 0;
		this->_size     = 0;
	}
	template <typename T, typename A>
	vector<T,A>::vector(size_type size, const value_type& value, const A& allocator) {
		this->_allocator = allocator;
		this->_capacity = size;
		this->_size     = size;
		this->_c = new value_type[size];
		for (size_type i=0; i<size; i++)
			_c[i] = value;
	}
	template <typename T, typename A>
	template <typename IT>
	vector<T,A>::vector(IT begin, IT end, const A& allocator) {
		if (begin > end)
			throw std::logic_error("End came before Begin.");
		this->_allocator = allocator;
		this->_capacity = end - begin;
		this->_size     = _capacity;
		this->_c = new value_type[_capacity];
		for (size_type i=0; i<_size && begin<end; i++,begin++)
			_c[i] = *begin;
	}
	template <typename T, typename A>
	vector<T,A>::~vector() {
		if (this->_c)
			delete[] _c;
		this->_c = NULL;
	}

	template <typename T, typename A>
	typename vector<T,A>::iterator	vector<T,A>::begin() { return iterator(this, 0);     }
	template <typename T, typename A>
	typename vector<T,A>::iterator	vector<T,A>::end()   { return iterator(this, _size); }
	template <typename T, typename A>
	typename vector<T,A>::const_iterator	vector<T,A>::begin() const { return const_iterator(this, 0);     }
	template <typename T, typename A>
	typename vector<T,A>::const_iterator	vector<T,A>::end()   const { return const_iterator(this, _size); }
	template <typename T, typename A>
	typename vector<T,A>::reverse_iterator	vector<T,A>::rbegin() { return iterator(this, 0);     }
	template <typename T, typename A>
	typename vector<T,A>::reverse_iterator	vector<T,A>::rend()   { return iterator(this, _size); }
	template <typename T, typename A>
	typename vector<T,A>::const_reverse_iterator	vector<T,A>::rbegin() const { return reverse_iterator(iterator(this, 0));     }
	template <typename T, typename A>
	typename vector<T,A>::const_reverse_iterator	vector<T,A>::rend()   const { return const_reverse_iterator(const_iterator(this, _size)); }
}

#endif
