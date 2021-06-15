/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   less.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 15:29:07 by abaur             #+#    #+#             */
/*   Updated: 2021/06/15 15:30:57 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LESS_HPP
#define LESS_HPP

namespace ft
{
	template <typename T>
	struct less {
		bool	operator()(T a, T b) { return a<b; }
	};
}

#endif
