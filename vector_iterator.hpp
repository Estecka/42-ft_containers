/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 17:30:07 by abaur             #+#    #+#             */
/*   Updated: 2021/07/05 19:26:59 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR
#define VECTOR_ITERATOR

#include <stdlib.h>
#include <stdexcept>

namespace ft
{
	template <typename T, typename Container>
	struct vector_iterator
	{
	public:
		typedef T 	value_type;
		typedef T*	pointer;
		typedef T&	reference;
		typedef typename Container::size_type      	size_type;
		typedef typename Container::difference_type	difference_type;
		typedef std::random_access_iterator_tag	iterator_category;

		vector_iterator(void);
		vector_iterator(const typename Container::iterator& other);
		vector_iterator(const typename Container::const_iterator& other);
		vector_iterator(Container* target, T* ptr);
		vector_iterator&	operator=(const vector_iterator& other);
		template <typename T2, class C2>
		bool	operator==(const vector_iterator<T2,C2>& other) const;
		template <typename T2, class C2>
		bool	operator!=(const vector_iterator<T2,C2>& other) const;
		template <typename T2, class C2>
		bool	operator<=(const vector_iterator<T2,C2>& other) const;
		template <typename T2, class C2>
		bool	operator>=(const vector_iterator<T2,C2>& other) const;
		template <typename T2, class C2>
		bool	operator< (const vector_iterator<T2,C2>& other) const;
		template <typename T2, class C2>
		bool	operator> (const vector_iterator<T2,C2>& other) const;

		T&	operator*() const;
		T*	operator->() const;
		T&	operator[](size_type offset) const;

		vector_iterator<T, Container>&	operator++();
		vector_iterator<T, Container>&	operator--();
		vector_iterator<T, Container> 	operator++(int);
		vector_iterator<T, Container> 	operator--(int);

		vector_iterator<T, Container> 	operator+ (int offset) const;
		vector_iterator<T, Container> 	operator- (int offset) const;
		vector_iterator<T, Container>&	operator-=(int offset);
		vector_iterator<T, Container>&	operator+=(int offset);
		template <typename T2, typename C2>
		difference_type	operator+ (const vector_iterator<T2,C2>& other) const;
		template <typename T2, typename C2>
		difference_type	operator- (const vector_iterator<T2,C2>& other) const;

	private:
		Container*	target;
		T*	ptr;

		template <typename T2, class C2>
		static T2*	GetPointer(const vector_iterator<T2,C2>& other);
		void	AssertTarget(const vector_iterator& other) const;
	};

/******************************************************************************/
/* # Implementation                                                           */
/******************************************************************************/

	template<typename T, typename C>
	vector_iterator<T,C>::vector_iterator(void){
		this->target = NULL;
		this->ptr = NULL;
	}
	template<typename T, typename C>
	vector_iterator<T,C>::vector_iterator(const typename C::iterator& other){
		*this = *(const vector_iterator*)&other;
	}
	template<typename T, typename C>
	vector_iterator<T,C>::vector_iterator(const typename C::const_iterator& other){
		*this = *(const vector_iterator*)&other;
		return;

		// Asserts at compile time that this does not unconst a const_iterator.
		value_type* v = (typename C::const_iterator::value_type*)NULL;
		(void)v;
	}
	template<typename T, typename C>
	vector_iterator<T,C>::vector_iterator(C* target, T* ptr){
		this->target = target;
		this->ptr = ptr;
	}
	template<typename T, typename C>
	vector_iterator<T,C>&	vector_iterator<T,C>::operator=(const vector_iterator& other){
		this->target = other.target;
		this->ptr = other.ptr;
		return *this;
	}

	
	template <typename T,  class C >
	template <typename T2, class C2>
	bool	vector_iterator<T,C>::operator==(const vector_iterator<T2,C2>& other) const {
		return this->ptr == GetPointer(other);
	}
	template <typename T,  class C >
	template <typename T2, class C2>
	bool	vector_iterator<T,C>::operator!=(const vector_iterator<T2,C2>& other) const {
		return this->ptr != GetPointer(other);
	}
	template <typename T,  class C >
	template <typename T2, class C2>
	bool	vector_iterator<T,C>::operator<=(const vector_iterator<T2,C2>& other) const {
		return this->ptr <= GetPointer(other);
	}
	template <typename T,  class C >
	template <typename T2, class C2>
	bool	vector_iterator<T,C>::operator>=(const vector_iterator<T2,C2>& other) const {
		return this->ptr >= GetPointer(other);
	}
	template <typename T,  class C >
	template <typename T2, class C2>
	bool	vector_iterator<T,C>::operator< (const vector_iterator<T2,C2>& other) const {
		return this->ptr < GetPointer(other);
	}
	template <typename T,  class C >
	template <typename T2, class C2>
	bool	vector_iterator<T,C>::operator> (const vector_iterator<T2,C2>& other) const {
		return this->ptr > GetPointer(other);
	}

	template <typename T, typename C>
	T&	vector_iterator<T,C>::operator*() const {
		return *this->ptr;
	}
	template <typename T, typename C>
	T*	vector_iterator<T,C>::operator->() const {
		return this->ptr;
	}
	template <typename T, typename C>
	T&	vector_iterator<T,C>::operator[](size_type offset) const {
		return *(this->ptr + offset);
	}



	template <typename T, typename C>
	vector_iterator<T, C>&	vector_iterator<T, C>::operator++(){
		++this->ptr;
		return *this;
	}
	template <typename T, typename C>
	vector_iterator<T, C>&	vector_iterator<T, C>::operator--(){
		--this->ptr;
		return *this;
	}
	template <typename T, typename C>
	vector_iterator<T, C> 	vector_iterator<T, C>::operator++(int){
		vector_iterator tmp(*this);
		this->ptr++;
		return tmp;
	}
	template <typename T, typename C>
	vector_iterator<T, C> 	vector_iterator<T, C>::operator--(int){
		vector_iterator tmp(*this);
		this->ptr--;
		return tmp;
	}


	template <typename T, typename C>
	vector_iterator<T,C> 	vector_iterator<T,C>::operator+ (int offset) const {
		return vector_iterator(target, this->ptr + offset);
	}
	template <typename T, typename C>
	vector_iterator<T,C> 	vector_iterator<T,C>::operator- (int offset) const {
		return vector_iterator(target, this->ptr - offset);
	}
	template <typename T,  class C>
	template <typename T2, class C2>
	typename vector_iterator<T,C>::difference_type 	vector_iterator<T,C>::operator+ (const vector_iterator<T2,C2>& other) const {
		return this->ptr + GetPointer(other);
	}
	template <typename T,  class C>
	template <typename T2, class C2>
	typename vector_iterator<T,C>::difference_type 	vector_iterator<T,C>::operator- (const vector_iterator<T2,C2>& other) const {
		return this->ptr - GetPointer(other);
	}
	template <typename T, typename C>
	vector_iterator<T,C>&	vector_iterator<T,C>::operator+=(int offset) {
		this->ptr += offset;
		return *this;
	}
	template <typename T, typename C>
	vector_iterator<T,C>&	vector_iterator<T,C>::operator-=(int offset) {
		this->ptr -= offset;
		return *this;
	}

	template <typename T, typename C>
	void	vector_iterator<T,C>::AssertTarget(const vector_iterator& other) const {
		if (this->target != other.target)
			throw std::domain_error("Iterators point to different Vectors");
	}
	template <typename T , typename C >
	template <typename T2, typename C2>
	T2*	vector_iterator<T,C>::GetPointer(const vector_iterator<T2,C2>& other) {
		return (T2*)((vector_iterator&)other).ptr;
	}
}

template <typename T, typename C>
ft::vector_iterator<T,C> 	operator+ (int offset, const ft::vector_iterator<T,C>& it) {
	return it + offset;
}

#endif
