/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 15:02:08 by abaur             #+#    #+#             */
/*   Updated: 2021/04/22 16:10:48 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <iterator>

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

	struct iterator;
	struct const_iterator;
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
	value_type*	_c;
	size_type	_capacity;
	size_type	_size;
};



#endif
