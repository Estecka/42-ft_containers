/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 14:01:22 by abaur             #+#    #+#             */
/*   Updated: 2021/06/01 14:06:46 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SWAP_HPP
#define SWAP_HPP

namespace ft
{
	template <typename T>
	void	swap(T& a, T& b) {
		T	olda(a);

		a = b;
		b = olda;
	}
} 

#endif
