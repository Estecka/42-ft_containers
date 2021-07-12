/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   less.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 15:29:07 by abaur             #+#    #+#             */
/*   Updated: 2021/07/12 16:58:34 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LESS_HPP
#define LESS_HPP

#include "lexicographical_compare.hpp"
#include "pair.hpp"

#include <iostream>

namespace ft
{
	template <typename T>
	short	lexicograph_compare(const T&, const T&);
	template <>
	short	lexicograph_compare(const std::string&, const std::string&);

	template <typename T>
	struct less {
		bool	operator()(T a, T b) const { return a < b; }
	};

	template <>
	struct less<std::string> {
		bool	operator()(const std::string& a, const std::string& b) const { return ft::lexicograph_compare(a,b) < 0; }
	};
	template <>
	struct less<const std::string> {
		bool	operator()(const std::string& a, const std::string& b) const { return ft::lexicograph_compare(a,b) < 0; }
	};
	template <typename K, typename V>
	struct less<ft::pair<K,V> > {
		bool	operator()(const ft::pair<K,V>& a, const ft::pair<K,V>& b) const { return less<K>()(a.first, b.first) ?: less<V>()(a.second, b.second); }
	};
	template <typename K, typename V>
	struct less<const ft::pair<K,V> > {
		bool	operator()(const ft::pair<K,V>& a, const ft::pair<K,V>& b) const { return less<K>()(a.first, b.first) ?: less<V>()(a.second, b.second); }
	};
}

#endif
