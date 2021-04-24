/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 15:02:08 by abaur             #+#    #+#             */
/*   Updated: 2021/04/24 16:04:37 by abaur            ###   ########.fr       */
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
		void	pop_back();
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
		return iterator(this, 0);
	}
	template <typename T, typename A>
	typename vector<T,A>::reverse_iterator	vector<T,A>::rend() {
		return iterator(this, _size);
	}
	template <typename T, typename A>
	typename vector<T,A>::const_reverse_iterator	vector<T,A>::rbegin() const {
		return reverse_iterator(iterator(this, 0));    
	}
	template <typename T, typename A>
	typename vector<T,A>::const_reverse_iterator	vector<T,A>::rend() const {
		return const_reverse_iterator(const_iterator(this, _size));
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
		if (this->capacity < targetCapacity)
		{
			value_type* old_c = this->_c;
			this->_c = new value_type[targetCapacity];
			this->_capacity = targetCapacity;
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
	typename vector<T,A>::reference      	vector<T,A>::operator[](size_t index){
		return this->_c[index];
	}
	template <typename T, typename A>
	typename vector<T,A>::const_reference	vector<T,A>::operator[](size_t index) const{
		return this->_c[index];
	}
	template <typename T, typename A>
	typename vector<T,A>::reference      	vector<T,A>::at(size_t index){
		if (index < 0 || this->_size <= index)
			throw std::out_of_range("Index is out of Range");
		return (*this)[index];
	}
	template <typename T, typename A>
	typename vector<T,A>::const_reference	vector<T,A>::at(size_t index) const{
		if (index < 0 || this->_size <= index)
			throw std::out_of_range("Index is out of Range");
		return (*this)[index];
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
	void	vector<T,A>::assign(IT begin, IT end){
		if (end < begin)
			throw std::logic_error("End came before Begin");
		this->reserve(end - begin);
		for (size_type i=0; begin<end; i++,begin++)
			(*this)[i] = *begin;
		this->_size = end - begin;
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
	/*
	template <typename T, typename A>
	void	vector<T,A>::insert(iterator index, const value_type& value){
		
	}
	template <typename T, typename A>
	void	vector<T,A>::insert(iterator index, size_type amount, const value_type& value){
		
	}
	template <typename T, typename A>
	template <typename IT>
	void	vector<T,A>::insert(iterator index, IT begin, IT end){
		
	}
	template <typename T, typename A>
	typename vector<T,A>::iterator	vector<T,A>::erase(iterator position){
		
	}
	template <typename T, typename A>
	typename vector<T,A>::iterator	vector<T,A>::erase(iterator begin, iterator end){
		
	}
	template <typename T, typename A>
	void       	vector<T,A>::swap(vector& other){
		
	}
	template <typename T, typename A>
	void	swap(vector<T,A>& a, vector<T,A>& b){
		
	}
	template <typename T, typename A>
	void	vector<T,A>::clear(){
		
	}
	*/
}

#endif
