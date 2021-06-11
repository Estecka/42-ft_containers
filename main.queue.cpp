/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.queue.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 15:24:51 by abaur             #+#    #+#             */
/*   Updated: 2021/06/11 19:25:10 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NS
 #error define NS needs to be explicitely set to either `std` or `ft`
#endif

#include "queue.hpp"
#include <queue>

#include "dump.hpp"
#include <typeinfo>

#include <iostream>

#pragma clang diagnostic ignored "-Wunused-function"

extern int	main() {
	NS::queue<int> queue;

	queue.empty();
	queue.size();
	queue.push(3);
	queue.front();
	queue.back();
	((const ft::queue<int>&)queue).front();
	((const ft::queue<int>&)queue).back();
	queue.pop();
}
