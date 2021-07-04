/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 17:30:07 by abaur             #+#    #+#             */
/*   Updated: 2021/07/04 19:40:20 by abaur            ###   ########.fr       */
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
		typedef typename Container::size_type	size_type;
		typedef typename Container::size_type	difference_type;
		typedef std::random_access_iterator_tag	iterator_category;

		vector_iterator(void);
		vector_iterator(const typename Container::iterator& other);
		vector_iterator(const typename Container::const_iterator& other);
		vector_iterator(Container* target, size_type index);
		vector_iterator&	operator=(const vector_iterator& other);
		bool	operator==(const vector_iterator& other) const;
		bool	operator!=(const vector_iterator& other) const;
		bool	operator<=(const vector_iterator& other) const;
		bool	operator>=(const vector_iterator& other) const;
		bool	operator< (const vector_iterator& other) const;
		bool	operator> (const vector_iterator& other) const;

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
		size_type	operator+ (const vector_iterator& other) const;
		size_type	operator- (const vector_iterator& other) const;

	private:
		Container*	target;
		size_type	index;

		void	AssertTarget(const vector_iterator& other) const;
	};

/******************************************************************************/
/* # Implementation                                                           */
/******************************************************************************/

	template<typename T, typename C>
	vector_iterator<T,C>::vector_iterator(void){
		this->target = NULL;
		this->index = 0;
	}
	template<typename T, typename C>
	vector_iterator<T,C>::vector_iterator(const typename C::iterator& other){
		*this = *(const vector_iterator*)&other;
	}
	template<typename T, typename C>
	vector_iterator<T,C>::vector_iterator(const typename C::const_iterator& other){
		*this = *(const vector_iterator*)&other;
	}
	template<typename T, typename C>
	vector_iterator<T,C>::vector_iterator(C* target, size_type index){
		this->target = target;
		this->index = index;
	}
	template<typename T, typename C>
	vector_iterator<T,C>&	vector_iterator<T,C>::operator=(const vector_iterator& other){
		this->target = other.target;
		this->index = other.index;
		return *this;
	}

	
	template <typename T, typename C>
	bool	vector_iterator<T,C>::operator==(const vector_iterator& other) const {
		return this->target == other.target && this->index == other.index;
	}
	template <typename T, typename C>
	bool	vector_iterator<T,C>::operator!=(const vector_iterator& other) const {
		return this->target != other.target || this->index != other.index;
	}
	template <typename T, typename C>
	bool	vector_iterator<T,C>::operator<=(const vector_iterator& other) const {
		AssertTarget(other);
		return this->index <= other.index;
	}
	template <typename T, typename C>
	bool	vector_iterator<T,C>::operator>=(const vector_iterator& other) const {
		AssertTarget(other);
		return this->index >= other.index;
	}
	template <typename T, typename C>
	bool	vector_iterator<T,C>::operator< (const vector_iterator& other) const {
		AssertTarget(other);
		return this->index < other.index;
	}
	template <typename T, typename C>
	bool	vector_iterator<T,C>::operator> (const vector_iterator& other) const {
		AssertTarget(other);
		return this->index > other.index;
	}

	template <typename T, typename C>
	T&	vector_iterator<T,C>::operator*() const {
		return (*target).at(this->index);
	}
	template <typename T, typename C>
	T*	vector_iterator<T,C>::operator->() const {
		return &(*target).at(this->index);
	}
	template <typename T, typename C>
	T&	vector_iterator<T,C>::operator[](size_type offset) const {
		return (*target)[this->index + offset];
	}



	template <typename T, typename C>
	vector_iterator<T, C>&	vector_iterator<T, C>::operator++(){
		++this->index;
		return *this;
	}
	template <typename T, typename C>
	vector_iterator<T, C>&	vector_iterator<T, C>::operator--(){
		--this->index;
		return *this;
	}
	template <typename T, typename C>
	vector_iterator<T, C> 	vector_iterator<T, C>::operator++(int){
		vector_iterator tmp(target, index);
		this->index++;
		return tmp;
	}
	template <typename T, typename C>
	vector_iterator<T, C> 	vector_iterator<T, C>::operator--(int){
		vector_iterator tmp(target, index);
		this->index--;
		return tmp;
	}

	template <typename T, typename C>
	vector_iterator<T,C> 	vector_iterator<T,C>::operator+ (int offset) const {
		return vector_iterator(target, this->index + offset);
	}
	template <typename T, typename C>
	vector_iterator<T,C> 	vector_iterator<T,C>::operator- (int offset) const {
		return vector_iterator(target, this->index - offset);
	}
	template <typename T, typename C>
	typename vector_iterator<T,C>::size_type 	vector_iterator<T,C>::operator+ (const vector_iterator& other) const {
		AssertTarget(other);
		return this->index + other.index;
	}
	template <typename T, typename C>
	typename vector_iterator<T,C>::size_type 	vector_iterator<T,C>::operator- (const vector_iterator& other) const {
		AssertTarget(other);
		return this->index - other.index;
	}
	template <typename T, typename C>
	vector_iterator<T,C>&	vector_iterator<T,C>::operator+=(int offset) {
		this->index += offset;
		return *this;
	}
	template <typename T, typename C>
	vector_iterator<T,C>&	vector_iterator<T,C>::operator-=(int offset) {
		this->index -= offset;
		return *this;
	}

	template <typename T, typename C>
	void	vector_iterator<T,C>::AssertTarget(const vector_iterator& other) const {
		if (this->target != other.target)
			throw std::domain_error("Iterators point to different Vectors");
	}
}

#endif
