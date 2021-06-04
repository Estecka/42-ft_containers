/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_iterator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 14:56:38 by abaur             #+#    #+#             */
/*   Updated: 2021/06/04 16:52:56 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_ITERATOR
#define LIST_ITERATOR

#include <iterator>

#include "not_integer.hpp"

namespace ft
{
	template <typename T, typename Container>
	struct list_iterator
	{
	private:
		typedef typename Container::lselt	lselt;

		friend	void Container::insert(list_iterator, const T&);
		friend	list_iterator Container::erase(list_iterator);
		friend	list_iterator Container::erase(list_iterator, list_iterator);
		friend	void Container::splice(list_iterator, Container&, list_iterator, list_iterator);

	public:
		typedef T 	value_type;
		typedef T*	pointer;
		typedef T&	reference;
		typedef typename Container::size_type	size_type;
		typedef typename Container::size_type	difference_type;
		typedef std::bidirectional_iterator_tag	iterator_category;

		list_iterator(void);
		list_iterator(const list_iterator& other);
		list_iterator(Container* target, lselt* element);
		list_iterator&	operator=(const list_iterator& other);

		bool	operator==(const list_iterator& other) const;
		bool	operator!=(const list_iterator& other) const;

		T&	operator*() const;
		T*	operator->() const;

		list_iterator<T, Container>&	operator++();
		list_iterator<T, Container>&	operator--();
		list_iterator<T, Container> 	operator++(int);
		list_iterator<T, Container> 	operator--(int);

	private:
		Container*	target;
		lselt*	curr;
	};

	
	template <typename T, typename C>
	list_iterator<T,C>::list_iterator(void) {
		this->target = NULL;
		this->curr   = NULL;
	}
	template <typename T, typename C>
	list_iterator<T,C>::list_iterator(const list_iterator& other) {
		this->target = other.target;
		this->curr   = other.curr;
	}
	template <typename T, typename C>
	list_iterator<T,C>::list_iterator(C* target, lselt* element) {
		this->target = target;
		this->curr   = element;
	}
	template <typename T, typename C>
	list_iterator<T,C>&	list_iterator<T,C>::operator=(const list_iterator& other) {
		this->target = other.target;
		this->curr   = other.curr;
		return *this;
	}


	template <typename T, typename C>
	bool	list_iterator<T,C>::operator==(const list_iterator& other) const {
		return this->target == other.target && this->curr == other.curr;
	}
	template <typename T, typename C>
	bool	list_iterator<T,C>::operator!=(const list_iterator& other) const {
		return this->target != other.target || this->curr != other.curr;
	}

	template <typename T, typename C>
	T&	list_iterator<T,C>::operator*() const {
		return this->curr->value;
	}
	template <typename T, typename C>
	T*	list_iterator<T,C>::operator->() const {
		return &*(*this);
	}

	template <typename T, typename C>
	list_iterator<T, C>&	list_iterator<T,C>::operator++() {
		if (!curr)
			throw std::out_of_range("Past-the-End list iterator.");
		this->curr = curr->next;
		return (*this);
	}
	template <typename T, typename C>
	list_iterator<T, C>&	list_iterator<T,C>::operator--() {
		if (!curr)
			curr = target->_last;
		else if (!curr->prev)		
			throw std::out_of_range("Past-the-Beginning list iterator.");
		else
			curr = curr->prev;
		return (*this);
	}
	template <typename T, typename C>
	list_iterator<T, C> 	list_iterator<T,C>::operator++(int) {
		list_iterator tmp(*this);
		++(*this);
		return tmp;
	}
	template <typename T, typename C>
	list_iterator<T, C> 	list_iterator<T,C>::operator--(int) {
		list_iterator tmp(*this);
		--(*this);
		return tmp;
	}
}

#endif
