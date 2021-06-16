/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.stack.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 15:24:51 by abaur             #+#    #+#             */
/*   Updated: 2021/06/16 18:28:33 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.hpp"
#include <stack>

#include "tester.hpp"

extern int	main() {
	NS::stack<int> stack;

	stack.empty();
	stack.size();
	stack.push(3);
	stack.top();
	((const ft::stack<int>&)stack).top();
	stack.pop();
}
