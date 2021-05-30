/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reconstruct.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 09:23:53 by abaur             #+#    #+#             */
/*   Updated: 2021/05/30 09:57:47 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RECONSTRUCT_HPP
#define RECONSTRUCT_HPP

#include <new>

namespace ft 
{
	// Destroys and constructs an object in-place, without reallocating memory,
	// and using copy-construction instead of the assignement operator.
	// @param T& object	The object to reconstruct.
	// @param const T&	The value to to copy into the object.
	template <typename T>
	void	reconstruct(T& object, const T& value)
	{
		object.~T();           // Manually destruct the object
		new(&object) T(value); // Manually re-call the constructor on the existing object
	}
}

#endif
