/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.stack.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 15:24:51 by abaur             #+#    #+#             */
/*   Updated: 2021/07/04 17:37:12 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.hpp"
#include <stack>

#include "tester.hpp"

extern int	main() {
	NS::stack<int> stack;
	NS::stack<int> stack2;

	stack.empty();
	stack.size();
	stack.push(3);
	stack.top();
	((const ft::stack<int>&)stack).top();
	stack.pop();

	NS::stack<int>*	compares[] = { &stack, &stack2, };
	TestLexicograpCompare(compares, 2);
}
