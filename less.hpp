/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   less.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 15:29:07 by abaur             #+#    #+#             */
/*   Updated: 2021/06/27 17:42:37 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LESS_HPP
#define LESS_HPP

#include "lexicographical_compare.hpp"

namespace ft
{
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
}

#endif
