/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 14:48:57 by abaur             #+#    #+#             */
/*   Updated: 2021/05/01 16:00:31 by abaur            ###   ########.fr       */
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
	// # PROTOTYPES
	// ==================
	public:
		// ## Member types
		typedef T	value_type;
		typedef A	allocator_type;
		typedef typename allocator_type::reference      	reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer        	pointer;
		typedef typename allocator_type::const_pointer  	const_pointer;

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

	// # IMPLEMENTATIONS
	// ==================

	};
}

#endif
