/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.queue.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 15:24:51 by abaur             #+#    #+#             */
/*   Updated: 2021/07/04 17:53:40 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queue.hpp"
#include <queue>

#include "tester.hpp"

extern int	main() {
	NS::queue<int> queue;
	NS::queue<int> queue2;

	queue.empty();
	queue.size();
	queue.push(3);
	queue.front();
	queue.back();
	((const ft::queue<int>&)queue).front();
	((const ft::queue<int>&)queue).back();
	queue.pop();

	NS::queue<int>* compares[] = { &queue, &queue2, };
	TestLexicograpCompare(compares, 2);
}
