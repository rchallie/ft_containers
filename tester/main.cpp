/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchallie <rchallie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 17:53:07 by rchallie          #+#    #+#             */
/*   Updated: 2020/12/10 21:36:17 by rchallie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"

#include <stack>

int main()
{
    test_vector();
    std::cout << "\n";
    test_list();
    std::cout << "\n";
    test_map();
    std::cout << "\n";
    test_deque();
    std::cout << "\n";
    test_stack();
    std::cout << "\n";
    test_queue();
}