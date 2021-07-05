/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 21:38:57 by abaur             #+#    #+#             */
/*   Updated: 2021/07/05 18:09:11 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

namespace ft
{
	template<typename IT>
	struct reverse_iterator
	{
	public:
		typedef IT	iterator_type;
		typedef typename IT::size_type       	size_type;
		typedef typename IT::difference_type 	difference_type;
		typedef typename IT::pointer   	pointer;
		typedef typename IT::reference 	reference;
		typedef typename IT::iterator_category	iterator_category;

		reverse_iterator(void);
		template <typename IT2>
		reverse_iterator(const reverse_iterator<IT2>& other);
		reverse_iterator(IT base);

		IT	base() const;

		bool	operator==(const reverse_iterator& other) const;
		bool	operator!=(const reverse_iterator& other) const;
		bool	operator<=(const reverse_iterator& other) const;
		bool	operator>=(const reverse_iterator& other) const;
		bool	operator< (const reverse_iterator& other) const;
		bool	operator> (const reverse_iterator& other) const;

		typename IT::reference	operator*() const;
		typename IT::pointer  	operator->() const;
		typename IT::reference	operator[](size_type offset) const;

		reverse_iterator<IT>&	operator++();
		reverse_iterator<IT>&	operator--();
		reverse_iterator<IT> 	operator++(int);
		reverse_iterator<IT> 	operator--(int);

		reverse_iterator<IT> 	operator+ (int offset) const;
		reverse_iterator<IT> 	operator- (int offset) const;
		reverse_iterator<IT>&	operator-=(int offset);
		reverse_iterator<IT>&	operator+=(int offset);
		difference_type	operator+ (const reverse_iterator& other) const;
		difference_type	operator- (const reverse_iterator& other) const;

	private:
		IT _base;
	};

/******************************************************************************/
/* # Implementation                                                           */
/******************************************************************************/

	template <typename IT>
	reverse_iterator<IT>::reverse_iterator(void){};
	template <typename IT>
	template <typename IT2>
	reverse_iterator<IT>::reverse_iterator(const reverse_iterator<IT2>& other)
	: _base(other.base())
	{};
	template <typename IT>
	reverse_iterator<IT>::reverse_iterator(IT base)
	: _base(base)
	{};

	template<typename IT>
	IT	reverse_iterator<IT>::base() const { return this->_base; }
	
	template <typename IT>
	bool	reverse_iterator<IT>::operator==(const reverse_iterator& other) const {
		return this->_base == other._base;
	}
	template <typename IT>
	bool	reverse_iterator<IT>::operator!=(const reverse_iterator& other) const {
		return this->_base != other._base;
	}
	template <typename IT>
	bool	reverse_iterator<IT>::operator<=(const reverse_iterator& other) const {
		return this->_base >= other._base;
	}
	template <typename IT>
	bool	reverse_iterator<IT>::operator>=(const reverse_iterator& other) const {
		return this->_base <= other._base;
	}
	template <typename IT>
	bool	reverse_iterator<IT>::operator< (const reverse_iterator& other) const {
		return this->_base > other._base;
	}
	template <typename IT>
	bool	reverse_iterator<IT>::operator> (const reverse_iterator& other) const {
		return this->_base < other._base;
	}

	template <typename IT>
	typename IT::reference	reverse_iterator<IT>::operator*() const {
		IT tmp = _base;
		return *--tmp;
	}
	template <typename IT>
	typename IT::pointer	reverse_iterator<IT>::operator->() const {
		return &**this;
	}
	template <typename IT>
	typename IT::reference	reverse_iterator<IT>::operator[](size_type offset) const {
		return _base[-1 - offset];
	}

	template <typename IT>
	reverse_iterator<IT>&	reverse_iterator<IT>::operator++() {
		--_base;
		return (*this);
	}
	template <typename IT>
	reverse_iterator<IT>&	reverse_iterator<IT>::operator--() {
		++_base;
		return (*this);
	}
	template <typename IT>
	reverse_iterator<IT> 	reverse_iterator<IT>::operator++(int) {
		reverse_iterator old(*this);
		_base--;
		return old;
	}
	template <typename IT>
	reverse_iterator<IT> 	reverse_iterator<IT>::operator--(int) {
		reverse_iterator old(*this);
		_base++;
		return old;
	}

	template<typename IT>
	reverse_iterator<IT> 	reverse_iterator<IT>::operator+ (int offset) const {
		return reverse_iterator(_base - offset);
	}
	template<typename IT>
	reverse_iterator<IT> 	reverse_iterator<IT>::operator- (int offset) const {
		return reverse_iterator(_base + offset);
	}
	template<typename IT>
	reverse_iterator<IT>&	reverse_iterator<IT>::operator-=(int offset) {
		_base += offset;
		return *this;
	}
	template<typename IT>
	reverse_iterator<IT>&	reverse_iterator<IT>::operator+=(int offset) {
		_base -= offset;
		return *this;
	}
	template<typename IT>
	typename reverse_iterator<IT>::difference_type	reverse_iterator<IT>::operator+ (const reverse_iterator& other) const {
		return other._base + this->_base;
	}
	template<typename IT>
	typename reverse_iterator<IT>::difference_type	reverse_iterator<IT>::operator- (const reverse_iterator& other) const {
		return other._base - this->_base;
	}

}

template<typename IT>
ft::reverse_iterator<IT> 	operator+ (int offset, ft::reverse_iterator<IT> it) {
	return it + offset;
}

#endif
