/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.queue.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 15:24:51 by abaur             #+#    #+#             */
/*   Updated: 2021/06/16 18:27:26 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queue.hpp"
#include <queue>

#include "tester.hpp"

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
