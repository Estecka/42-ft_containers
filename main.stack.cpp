/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.stack.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 15:24:51 by abaur             #+#    #+#             */
/*   Updated: 2021/06/11 19:06:21 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NS
 #error define NS needs to be explicitely set to either `std` or `ft`
#endif

#include "stack.hpp"
#include <stack>

#include "dump.hpp"
#include <typeinfo>

#include <iostream>

#pragma clang diagnostic ignored "-Wunused-function"

extern int	main() {
	NS::stack<int> stack;

	stack.empty();
	stack.size();
	stack.top();
	((const ft::stack<int>&)stack).top();
	stack.push(3);
	stack.pop();
}
