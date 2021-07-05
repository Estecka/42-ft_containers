/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 15:02:08 by abaur             #+#    #+#             */
/*   Updated: 2021/07/05 17:19:24 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "vector_iterator.hpp"

#include "lexicographical_compare.hpp"
#include "not_integer.hpp"
#include "reverse_iterator.hpp"
#include "swap.hpp"

#include <sstream>

namespace ft
{
	template <typename T, typename A>
	class	vector;
	template <typename T, typename A>
	void	swap(vector<T,A>& a, vector<T,A>& b);


	template <typename T, typename A = std::allocator<T> >
	class vector
	{
	public:
	// ## Member types
		typedef T    	value_type;
		typedef A	allocator_type;
		typedef typename allocator_type::reference      	reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer        	pointer;
		typedef typename allocator_type::const_pointer  	const_pointer;

		typedef ft::vector_iterator<      value_type,       vector<T,A> >	iterator;
		typedef ft::vector_iterator<const value_type, const vector<T,A> >	const_iterator;
		typedef ft::reverse_iterator<iterator>      	reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		typedef __gnu_cxx::ptrdiff_t	difference_type;
		typedef size_t   	size_type;

	// ## Constructors
		explicit vector(const allocator_type& allocator = allocator_type());
		explicit vector(size_type size, const value_type& value = value_type(), const allocator_type& allocator = allocator_type());
		template <class IT>
		vector(IT begin, IT end, const allocator_type& allocator = allocator_type(), NOT_INTEGER(IT) = 0);
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
		reference      	operator[](size_type index);
		const_reference	operator[](size_type index) const;
		reference      	at(size_type index);
		const_reference	at(size_type index) const;
		reference      	front();
		const_reference	front() const;
		reference      	back();
		const_reference	back() const;

	// ## Modifiers
		template <class IT>
		void	assign(IT begin, IT end, NOT_INTEGER(IT) = 0);
		void	assign(size_type size, const value_type& value);
		void	push_back(const value_type& value);
		void	pop_back();
		iterator	insert(iterator index, const value_type& value);
		template <typename IT>
		void	insert(iterator index, IT begin, IT end, NOT_INTEGER(IT) = 0);
		void	insert(iterator index, size_type amount, const value_type& value);
		iterator	erase(iterator position);
		iterator	erase(iterator begin, iterator end);
		void       	swap(vector& other);
		void	clear();
		

	private:
		allocator_type	_allocator;
		value_type*	_c;
		size_type	_capacity;
		size_type	_size;

		template <class IT>
		static size_type	_InputIterCount(IT begin, IT end);
	};

/******************************************************************************/
/* # Implementations                                                          */
/******************************************************************************/

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
	vector<T,A>::vector(const vector& other) {
		this->_allocator = other._allocator;
		this->_capacity = other._capacity;
		this->_size     = other._size;
		this->_c = new value_type[_capacity];
		for (size_type i=0; i<_size; i++)
			this->_c[i] = other._c[i];
	}
	template <typename T, typename A>
	template <typename IT>
	vector<T,A>::vector(IT begin, IT end, const A& allocator, NOT_INTEGER(IT)) {
		size_type amount = _InputIterCount(begin, end);

		this->_allocator = allocator;
		this->_capacity = amount;
		this->_size     = amount;
		this->_c = new value_type[_capacity];
		for (size_type i=0; begin!=end; i++,begin++)
			(*this)[i] = *begin;
	}
	template <typename T, typename A>
	vector<T,A>::~vector() {
		if (this->_c)
			delete[] _c;
		this->_c = NULL;
	}

	template <typename T, typename A>
	vector<T,A>& vector<T,A>::operator=(const vector& other) {
		if (this->_c)
			delete[] _c;
		this->_capacity = 0;
		this->_size     = 0;

		this->_c = new value_type[other._capacity];
		this->_capacity = other._capacity;
		this->_size     = other._size;
		for (size_type i=0; i<_size; i++)
			(*this)[i] = other[i];

		return *this;
	}
	

// ## Iterators
	template <typename T, typename A>
	typename vector<T,A>::iterator	vector<T,A>::begin()  {
		return iterator(this, 0);
	}
	template <typename T, typename A>
	typename vector<T,A>::iterator	vector<T,A>::end() {
		return iterator(this, _size);
	}
	template <typename T, typename A>
	typename vector<T,A>::const_iterator	vector<T,A>::begin() const  {
		return const_iterator(this, 0);    
	}
	template <typename T, typename A>
	typename vector<T,A>::const_iterator	vector<T,A>::end() const  {
		return const_iterator(this, _size);
	}
	template <typename T, typename A>
	typename vector<T,A>::reverse_iterator	vector<T,A>::rbegin() {
		return reverse_iterator(iterator(this, _size));
	}
	template <typename T, typename A>
	typename vector<T,A>::reverse_iterator	vector<T,A>::rend() {
		return reverse_iterator(iterator(this, 0));
	}
	template <typename T, typename A>
	typename vector<T,A>::const_reverse_iterator	vector<T,A>::rbegin() const {
		return const_reverse_iterator(const_iterator(this, _size));    
	}
	template <typename T, typename A>
	typename vector<T,A>::const_reverse_iterator	vector<T,A>::rend() const {
		return const_reverse_iterator(const_iterator(this, 0));
	}


// ## Capacity
	template <typename T, typename A>
	typename vector<T,A>::size_type	vector<T,A>::size() const {
		return this->_size;
	}
	template <typename T, typename A>
	typename vector<T,A>::size_type	vector<T,A>::capacity() const {
		return this->_capacity;
	}
	template <typename T, typename A>
	typename vector<T,A>::size_type	vector<T,A>::max_size() const {
		return this->_allocator.max_size();
	}
	template <typename T, typename A>
	bool	vector<T,A>::empty() const {
		return !this->_size;
	}
	template <typename T, typename A>
	void	vector<T,A>::resize(size_type targetSize, value_type value) {
		this->reserve(targetSize);
		for (size_type i=this->_size; i<targetSize; i++)
			this->_c[i] = value;
		this->_size = targetSize;
	}
	template <typename T, typename A>
	void	vector<T,A>::reserve(size_type targetCapacity) {
		if (this->_capacity < targetCapacity)
		{
			size_type newCap = _capacity;
			if (!newCap)
				newCap = targetCapacity;
			else while (newCap < targetCapacity)
				newCap *= 2;

			value_type* old_c = this->_c;
			this->_c = new value_type[newCap];
			this->_capacity = newCap;
			if (old_c != NULL)
			{
				for (size_type i=0; i<_size; i++)
					this->_c[i] = old_c[i];
				delete[] old_c;
			}
		}
	}


// ## Element access
	template <typename T, typename A>
	typename vector<T,A>::reference      	vector<T,A>::operator[](size_type index){
		return this->_c[index];
	}
	template <typename T, typename A>
	typename vector<T,A>::const_reference	vector<T,A>::operator[](size_type index) const{
		return this->_c[index];
	}
	template <typename T, typename A>
	typename vector<T,A>::reference      	vector<T,A>::at(size_type index){
		if (index < 0 || this->_size <= index) {
			std::ostringstream msg;
			msg << "Index is out of range: " << index << " out of " << _size;
			throw std::out_of_range(msg.str());
		}
		return (*this)[index];
	}
	template <typename T, typename A>
	typename vector<T,A>::const_reference	vector<T,A>::at(size_type index) const {
		return (*(vector*)this).at(index);
	}
	template <typename T, typename A>
	typename vector<T,A>::reference      	vector<T,A>::front(){
		return (*this)[0];
	}
	template <typename T, typename A>
	typename vector<T,A>::const_reference	vector<T,A>::front() const{
		return (*this)[0];
	}
	template <typename T, typename A>
	typename vector<T,A>::reference      	vector<T,A>::back(){
		return (*this)[_size-1];
	}
	template <typename T, typename A>
	typename vector<T,A>::const_reference	vector<T,A>::back() const{
		return (*this)[_size-1];
	}


// ## Modifiers
	template <typename T, typename A>
	template <class IT>
	void	vector<T,A>::assign(IT begin, IT end, NOT_INTEGER(IT)){
		size_type amount = _InputIterCount(begin, end);

		this->reserve(amount);
		this->_size = amount;
		for (size_type i=0; begin!=end; i++,begin++)
			(*this)[i] = *begin;
	}
	template <typename T, typename A>
	void	vector<T,A>::assign(size_type targetSize, const value_type& value){
		this->reserve(targetSize);
		for (size_type i=0; i<targetSize; i++)
			(*this)[i] = value;
		this->_size = targetSize;
	}
	template <typename T, typename A>
	void	vector<T,A>::push_back(const value_type& value){
		this->reserve(_size + 1);
		(*this)[_size++] = value;
	}
	template <typename T, typename A>
	void	vector<T,A>::pop_back(){
		if (this->_size < 1)
			throw std::length_error("Can't pop an empty vector.");
		this->_size--;
	}
	template <typename T, typename A>
	template <typename IT>
	void	vector<T,A>::insert(iterator index, IT begin, IT end, typename not_integer<IT>::_true){
		size_type amount = _InputIterCount(begin, end);

		this->reserve(_size + amount);

		if (this->_size)
		for (iterator it=this->end()-1; true; it--){
			it[amount] = it[0];
			if (it <= index)
				break;
		}
		this->_size += amount;
		for (iterator it=index; it<(index+amount); it++)
			*it = *(begin++);
	}
	template <typename T, typename A>
	typename vector<T,A>::iterator	vector<T,A>::insert(iterator index, const value_type& value){
		this->insert(index, 1, (const value_type&)value);
		return index;
	}
	template <typename T, typename A>
	void	vector<T,A>::insert(iterator index, size_type amount, const value_type& value){
		if (amount < 0)
			return;
		this->reserve(_size + amount);

		// Displace existing content
		if (this->_size > 0)
		for (iterator it=this->end()-1; true; it--){
			it[amount] = it[0];
			if (it<=index)
				break;
		}
		this->_size += amount;
		// Insert new content
		for (iterator it=index; it<(index+amount); it++)
			*it = value;
	}
	template <typename T, typename A>
	typename vector<T,A>::iterator	vector<T,A>::erase(iterator position){
		return this->erase(position, position+1);
	}
	template <typename T, typename A>
	typename vector<T,A>::iterator	vector<T,A>::erase(iterator begin, iterator end){
		if (end < begin)
			throw std::invalid_argument("End came before Begin");

		size_type amount = end - begin;
		for (iterator it=begin; (it+amount)<this->end(); it++)
			it[0] = it[amount];

		this->_size -= amount;
		return begin;
	}
	template <typename T, typename A>
	void	vector<T,A>::swap(vector& other){
		ft::swap(this->_allocator, other._allocator);
		ft::swap(this->_c,         other._c        );
		ft::swap(this->_size,      other._size     );
		ft::swap(this->_capacity,  other._capacity );
	}
	template <typename T, typename A>
	void	swap(vector<T,A>& a, vector<T,A>& b){
		a.swap(b);
	}
	template <typename T, typename A>
	void	vector<T,A>::clear(){
		this->_size = 0;
	}

// ## Private
	template <typename T, typename A>
	template <typename IT>
	typename vector<T,A>::size_type	vector<T,A>::_InputIterCount(IT begin, IT end){
		size_type c = 0;
		for (IT it=begin; it!=end; ++it)
			++c;
		return c;
	}

}

// ## Operators
template <typename T, typename A>
bool	operator==(const ft::vector<T,A>& a, const ft::vector<T,A>& b) {
	return ft::lexicograph_compare(a, b) == 0;
}
template <typename T, typename A>
bool	operator!=(const ft::vector<T,A>& a, const ft::vector<T,A>& b) {
	return ft::lexicograph_compare(a, b) != 0;
}
template <typename T, typename A>
bool	operator< (const ft::vector<T,A>& a, const ft::vector<T,A>& b) {
	return ft::lexicograph_compare(a, b) <  0;
}
template <typename T, typename A>
bool	operator> (const ft::vector<T,A>& a, const ft::vector<T,A>& b) {
	return ft::lexicograph_compare(a, b) >  0;
}
template <typename T, typename A>
bool	operator<=(const ft::vector<T,A>& a, const ft::vector<T,A>& b) {
	return ft::lexicograph_compare(a, b) <= 0;
}
template <typename T, typename A>
bool	operator>=(const ft::vector<T,A>& a, const ft::vector<T,A>& b) {
	return ft::lexicograph_compare(a, b) >= 0;
}

#endif
