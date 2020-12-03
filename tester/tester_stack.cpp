/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester_stack.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchallie <rchallie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 00:25:51 by rchallie          #+#    #+#             */
/*   Updated: 2020/12/03 23:44:35 by rchallie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"
#include "../containers/stack.hpp"
#include <stack>

template <class T>
std::string equalContent(
    std::stack<T> stl_stack,
    ft::stack<T> ft_stack
)
{
    while (42)
    {
        if (stl_stack.size() == 0 || ft_stack.size() == 0)
            break;
        if (ft_stack.top() != stl_stack.top())
            return ("✘");
        ft_stack.pop();
        stl_stack.pop();
    }
    return ("✔");
}

template <class T>
bool printStackAttributes(
    std::fstream& fs,
    std::stack<T> stl_stack,
    ft::stack<T> ft_stack
)
{
    /* STL Values */
    std::string stl_empty = ((stl_stack.empty() == 1) ? "true" : "false");
    size_t stl_size = stl_stack.size();

    /* FT Values */
    std::string ft_empty = ((ft_stack.empty() == 1) ? "true" : "false");
    size_t ft_size = ft_stack.size();

    /* FT Result compare values */
    bool empty = equalbool(ft_empty, stl_empty);
    bool size = equalbool(ft_size, stl_size);
    std::string content = equalContent(stl_stack, ft_stack);
    
    fs << "\n══════════════════════════════════════════════════════════════\n";
    fs << "stacks attributes : \n";
    fs << "STL : \n";
    fs << "Empty       : " << stl_empty  << std::endl;
    fs << "Size        : " << stl_size  << std::endl;
    fs << "Content     : [";

    while (42)
    {
        if (stl_stack.size() == 0)
            break;
        fs << stl_stack.top();
        stl_stack.pop();
        if (stl_stack.size() != 0)
            fs << ", ";
    }

    fs << "]\n";

    fs << std::endl;

    fs << "FT : \n";
    fs << "Empty    [" << equal(ft_empty, stl_empty) << "]: " << ft_empty  << std::endl;
    fs << "Size     [" << equal(ft_size, stl_size) << "]: " << ft_size  << std::endl;

    fs << "Content  [" << content << "]: [";

    while (42)
    {
        if (ft_stack.size() == 0)
            break;
        fs << ft_stack.top();
        ft_stack.pop();
        if (ft_stack.size() != 0)
            fs << ", ";
    }
    fs << "]\n";

    fs << "══════════════════════════════════════════════════════════════\n";

    /* Error case */
    if (empty == false)
        return (false);
    else if (size == false)
        return (false);
    else if (content == "✘")
        return (false);
    return (true);
}

void test_stack()
{
    std::cout << UNDERLINE << "STACK :\n" << NORMAL ;

    mkdir("./tester/stacks_output", 0777);
    
    std::fstream fs;

    /* Member functions */
    std::cout << "Member functions : ";

    /* Default Constructor */
    {
        std::stack<int> stl_default;
        ft::stack<int> ft_default;

        fs.open("./tester/stacks_output/constructor_default", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printStackAttributes(fs, stl_default, ft_default) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::stack<int> ft_default;\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::stack<int> stl_default;\n";
        fs.close();

    }

    /* Empty true */
    {
        std::stack<int> stl_empty;
        ft::stack<int> ft_empty;

        fs.open("./tester/stacks_output/empty_true", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printStackAttributes(fs, stl_empty, ft_empty) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::stack<int> ft_empty;\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::stack<int> stl_empty;\n";
        fs.close();
    }

    /* Empty false */
    {
        std::stack<int> stl_empty;
        ft::stack<int> ft_empty;

        stl_empty.push(42);
        ft_empty.push(42);

        fs.open("./tester/stacks_output/empty_false", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printStackAttributes(fs, stl_empty, ft_empty) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::stack<int> ft_empty;\n";
        fs << "ft_empty.push(42);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::stack<int> stl_empty;\n";
        fs << "stl_empty.push(42);\n";
        fs.close();
    }

    /* Size */
    {
        std::stack<int> stl_size;
        ft::stack<int> ft_size;

        for (int i = 0; i < 42; i++)
        {
            stl_size.push(i);
            ft_size.push(i);
        }

        fs.open("./tester/stacks_output/size", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printStackAttributes(fs, stl_size, ft_size) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::stack<int> ft_size;\n";
        fs << "for (int i = 0; i < 42; i++)\n";
        fs << "     ft_size.push(i);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::stack<int> stl_size;\n";
        fs << "for (int i = 0; i < 42; i++)\n";
        fs << "     stl_size.push(i);\n";
        fs.close();
    }

    /* Top */
    {
        std::stack<int> stl_top;
        ft::stack<int> ft_top;

        for (int i = 0; i < 42; i++)
        {
            stl_top.push(i);
            ft_top.push(i);
        }

        fs.open("./tester/stacks_output/top", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printSingleValue(fs, stl_top.top(), ft_top.top()) == true) ? "[OK]" : "[NOP]");
        
        stl_top.pop();
        ft_top.pop();

        std::cout << ((printSingleValue(fs, stl_top.top(), ft_top.top()) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::stack<int> ft_top;\n";
        fs << "for (int i = 0; i < 42; i++)\n";
        fs << "     ft_top.push(i);\n";
        fs << "Send output...\n";
        fs << "ft_top.pop();\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::stack<int> stl_top;\n";
        fs << "for (int i = 0; i < 42; i++)\n";
        fs << "     stl_top.push(i);\n";
        fs << "Send output...\n";
        fs << "stl_top.pop();\n";
        fs.close();
    }

    /* Push */
    {
        std::stack<int> stl_size;
        ft::stack<int> ft_size;

        for (int i = 0; i < 42; i++)
        {
            stl_size.push(i * 2);
            ft_size.push(i * 2);
        }

        fs.open("./tester/stacks_output/push", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printStackAttributes(fs, stl_size, ft_size) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::stack<int> ft_size;\n";
        fs << "for (int i = 0; i < 42; i++)\n";
        fs << "     ft_size.push(i * 2);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::stack<int> stl_size;\n";
        fs << "for (int i = 0; i < 42; i++)\n";
        fs << "     stl_size.push(i * 2);\n";
        fs.close();
    }

    /* Pop */
    {
        std::stack<int> stl_pop;
        ft::stack<int> ft_pop;

        for (int i = 0; i < 42; i++)
        {
            stl_pop.push(i);
            ft_pop.push(i);
        }

        fs.open("./tester/stacks_output/pop", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printStackAttributes(fs, stl_pop, ft_pop) == true) ? "[OK]" : "[NOP]");
        
        stl_pop.pop();
        ft_pop.pop();

        std::cout << ((printStackAttributes(fs, stl_pop, ft_pop) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::stack<int> ft_pop;\n";
        fs << "for (int i = 0; i < 42; i++)\n";
        fs << "     ft_pop.push(i);\n";
        fs << "Send output...\n";
        fs << "ft_pop.pop();\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::stack<int> stl_pop;\n";
        fs << "for (int i = 0; i < 42; i++)\n";
        fs << "     stl_pop.push(i);\n";
        fs << "Send output...\n";
        fs << "stl_pop.pop();\n";
        fs.close();
    }

    std::cout << std::endl;
    std::cout << "Non-member function overloads : ";

    /* RL = relational operator */

    /* RL == true */
    {
        std::stack<int> stl_pop_one;
        std::stack<int> stl_pop_two;
        ft::stack<int> ft_pop_one;
        ft::stack<int> ft_pop_two;

        for (int i = 0; i < 42; i++)
        {
            stl_pop_one.push(i);
            stl_pop_two.push(i);
            ft_pop_one.push(i);
            ft_pop_two.push(i);
        }

        fs.open("./tester/stacks_output/operator_equal_true", std::fstream::in | std::fstream::out | std::fstream::trunc);
        printStackAttributes(fs, stl_pop_one, ft_pop_one);
        printStackAttributes(fs, stl_pop_two, ft_pop_two);
        
        std::cout << ((printBoolResult(fs, (stl_pop_one == stl_pop_two), (ft_pop_one == ft_pop_two)) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::stack<int> ft_pop;\n";
        fs << "for (int i = 0; i < 42; i++)\n";
        fs << "{\n";
        fs << "    ft_pop_one.push(i);\n";
        fs << "    ft_pop_two.push(i);\n";
        fs << "}\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::stack<int> stl_pop;\n";
        fs << "for (int i = 0; i < 42; i++)\n";
        fs << "{\n";
        fs << "    stl_pop_one.push(i);\n";
        fs << "    stl_pop_two.push(i);\n";
        fs << "}\n";
        fs.close();
    }

    /* RL == false */
    {
        std::stack<int> stl_pop_one;
        std::stack<int> stl_pop_two;
        ft::stack<int> ft_pop_one;
        ft::stack<int> ft_pop_two;

        for (int i = 0; i < 42; i++)
        {
            stl_pop_one.push(i);
            stl_pop_two.push(i * 2);
            ft_pop_one.push(i);
            ft_pop_two.push(i * 2);
        }

        fs.open("./tester/stacks_output/operator_equal_false", std::fstream::in | std::fstream::out | std::fstream::trunc);
        printStackAttributes(fs, stl_pop_one, ft_pop_one);
        printStackAttributes(fs, stl_pop_two, ft_pop_two);
        
        std::cout << ((printBoolResult(fs, (stl_pop_one == stl_pop_two), (ft_pop_one == ft_pop_two)) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::stack<int> ft_pop;\n";
        fs << "for (int i = 0; i < 42; i++)\n";
        fs << "{\n";
        fs << "    ft_pop_one.push(i);\n";
        fs << "    ft_pop_two.push(i * 2);\n";
        fs << "}\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::stack<int> stl_pop;\n";
        fs << "for (int i = 0; i < 42; i++)\n";
        fs << "{\n";
        fs << "    stl_pop_one.push(i);\n";
        fs << "    stl_pop_two.push(i * 2);\n";
        fs << "}\n";
        fs.close();
    }

    /* RL != true */
    {
        std::stack<int> stl_pop_one;
        std::stack<int> stl_pop_two;
        ft::stack<int> ft_pop_one;
        ft::stack<int> ft_pop_two;

        for (int i = 0; i < 42; i++)
        {
            stl_pop_one.push(i);
            stl_pop_two.push(i * 2);
            ft_pop_one.push(i);
            ft_pop_two.push(i * 2);
        }

        fs.open("./tester/stacks_output/operator_net_equal_true", std::fstream::in | std::fstream::out | std::fstream::trunc);
        printStackAttributes(fs, stl_pop_one, ft_pop_one);
        printStackAttributes(fs, stl_pop_two, ft_pop_two);
        
        std::cout << ((printBoolResult(fs, (stl_pop_one != stl_pop_two), (ft_pop_one != ft_pop_two)) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::stack<int> ft_pop;\n";
        fs << "for (int i = 0; i < 42; i++)\n";
        fs << "{\n";
        fs << "    ft_pop_one.push(i);\n";
        fs << "    ft_pop_two.push(i * 2);\n";
        fs << "}\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::stack<int> stl_pop;\n";
        fs << "for (int i = 0; i < 42; i++)\n";
        fs << "{\n";
        fs << "    stl_pop_one.push(i);\n";
        fs << "    stl_pop_two.push(i * 2);\n";
        fs << "}\n";
        fs.close();
    }

    /* RL != false */
    {
        std::stack<int> stl_pop_one;
        std::stack<int> stl_pop_two;
        ft::stack<int> ft_pop_one;
        ft::stack<int> ft_pop_two;

        for (int i = 0; i < 42; i++)
        {
            stl_pop_one.push(i);
            stl_pop_two.push(i);
            ft_pop_one.push(i);
            ft_pop_two.push(i);
        }

        fs.open("./tester/stacks_output/operator_not_equal_false", std::fstream::in | std::fstream::out | std::fstream::trunc);
        printStackAttributes(fs, stl_pop_one, ft_pop_one);
        printStackAttributes(fs, stl_pop_two, ft_pop_two);
        
        std::cout << ((printBoolResult(fs, (stl_pop_one != stl_pop_two), (ft_pop_one != ft_pop_two)) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::stack<int> ft_pop;\n";
        fs << "for (int i = 0; i < 42; i++)\n";
        fs << "{\n";
        fs << "    ft_pop_one.push(i);\n";
        fs << "    ft_pop_two.push(i);\n";
        fs << "}\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::stack<int> stl_pop;\n";
        fs << "for (int i = 0; i < 42; i++)\n";
        fs << "{\n";
        fs << "    stl_pop_one.push(i);\n";
        fs << "    stl_pop_two.push(i);\n";
        fs << "}\n";
        fs.close();
    }

    /* RL < true */
    {
        std::stack<int> stl_pop_one;
        std::stack<int> stl_pop_two;
        ft::stack<int> ft_pop_one;
        ft::stack<int> ft_pop_two;

        for (int i = 0; i < 42; i++)
        {
            stl_pop_one.push(i);
            ft_pop_one.push(i);
            if (i == 30)
            {
                stl_pop_two.push(i * 2);
                ft_pop_two.push(i * 2);
            }
            else
            {
                stl_pop_two.push(i);
                ft_pop_two.push(i);
            }
        }

        fs.open("./tester/stacks_output/operator_inf_true", std::fstream::in | std::fstream::out | std::fstream::trunc);
        printStackAttributes(fs, stl_pop_one, ft_pop_one);
        printStackAttributes(fs, stl_pop_two, ft_pop_two);
        
        std::cout << ((printBoolResult(fs, (stl_pop_one < stl_pop_two), (ft_pop_one < ft_pop_two)) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::stack<int> ft_pop;\n";
        fs << "for (int i = 0; i < 42; i++)\n";
        fs << "{\n";
        fs << "    ft_pop_one.push(i);\n";
        fs << "     if (i == 30)\n";
        fs << "         ft_pop_two.push(i * 2);\n";
        fs << "     else\n";
        fs << "         ft_pop_two.push(i);\n";
        fs << "}\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::stack<int> stl_pop;\n";
        fs << "for (int i = 0; i < 42; i++)\n";
        fs << "{\n";
        fs << "    stl_pop_one.push(i);\n";
        fs << "     if (i == 30)\n";
        fs << "         stl_pop_two.push(i * 2);\n";
        fs << "     else\n";
        fs << "         stl_pop_two.push(i);\n";
        fs << "}\n";
        fs.close();
    }

    /* RL < false */
    {
        std::stack<int> stl_pop_one;
        std::stack<int> stl_pop_two;
        ft::stack<int> ft_pop_one;
        ft::stack<int> ft_pop_two;

        for (int i = 0; i < 42; i++)
        {
            stl_pop_two.push(i);
            ft_pop_two.push(i);
            if (i == 30)
            {
                stl_pop_one.push(i * 2);
                ft_pop_one.push(i * 2);
            }
            else
            {
                stl_pop_one.push(i);
                ft_pop_one.push(i);
            }
        }

        fs.open("./tester/stacks_output/operator_inf_false", std::fstream::in | std::fstream::out | std::fstream::trunc);
        printStackAttributes(fs, stl_pop_one, ft_pop_one);
        printStackAttributes(fs, stl_pop_two, ft_pop_two);
        
        std::cout << ((printBoolResult(fs, (stl_pop_one < stl_pop_two), (ft_pop_one < ft_pop_two)) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::stack<int> ft_pop;\n";
        fs << "for (int i = 0; i < 42; i++)\n";
        fs << "{\n";
        fs << "    ft_pop_two.push(i);\n";
        fs << "     if (i == 30)\n";
        fs << "         ft_pop_one.push(i * 2);\n";
        fs << "     else\n";
        fs << "         ft_pop_one.push(i);\n";
        fs << "}\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::stack<int> stl_pop;\n";
        fs << "for (int i = 0; i < 42; i++)\n";
        fs << "{\n";
        fs << "    stl_pop_two.push(i);\n";
        fs << "     if (i == 30)\n";
        fs << "         stl_pop_two.push(i * 2);\n";
        fs << "     else\n";
        fs << "         stl_pop_one.push(i);\n";
        fs << "}\n";
        fs.close();
    }

    /* RL <= true */
    {
        std::stack<int> stl_pop_one;
        std::stack<int> stl_pop_two;
        ft::stack<int> ft_pop_one;
        ft::stack<int> ft_pop_two;

        for (int i = 0; i < 42; i++)
        {
            stl_pop_one.push(i);
            stl_pop_two.push(i * 2);
            ft_pop_one.push(i);
            ft_pop_two.push(i * 2);
        }

        fs.open("./tester/stacks_output/operator_inf_equal_true", std::fstream::in | std::fstream::out | std::fstream::trunc);
        printStackAttributes(fs, stl_pop_one, ft_pop_one);
        printStackAttributes(fs, stl_pop_two, ft_pop_two);
        
        std::cout << ((printBoolResult(fs, (stl_pop_one <= stl_pop_two), (ft_pop_one <= ft_pop_two)) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::stack<int> ft_pop;\n";
        fs << "for (int i = 0; i < 42; i++)\n";
        fs << "{\n";
        fs << "    ft_pop_one.push(i);\n";
        fs << "    ft_pop_two.push(i * 2);\n";
        fs << "}\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::stack<int> stl_pop;\n";
        fs << "for (int i = 0; i < 42; i++)\n";
        fs << "{\n";
        fs << "    stl_pop_one.push(i);\n";
        fs << "    stl_pop_two.push(i * 2);\n";
        fs << "}\n";
        fs.close();
    }

    /* RL <= true equal */
    {
        std::stack<int> stl_pop_one;
        std::stack<int> stl_pop_two;
        ft::stack<int> ft_pop_one;
        ft::stack<int> ft_pop_two;

        for (int i = 0; i < 42; i++)
        {
            stl_pop_one.push(i);
            stl_pop_two.push(i);
            ft_pop_one.push(i);
            ft_pop_two.push(i);
        }

        fs.open("./tester/stacks_output/operator_inf_equal_true", std::fstream::in | std::fstream::out | std::fstream::trunc);
        printStackAttributes(fs, stl_pop_one, ft_pop_one);
        printStackAttributes(fs, stl_pop_two, ft_pop_two);
        
        std::cout << ((printBoolResult(fs, (stl_pop_one <= stl_pop_two), (ft_pop_one <= ft_pop_two)) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::stack<int> ft_pop;\n";
        fs << "for (int i = 0; i < 42; i++)\n";
        fs << "{\n";
        fs << "    ft_pop_one.push(i);\n";
        fs << "    ft_pop_two.push(i);\n";
        fs << "}\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::stack<int> stl_pop;\n";
        fs << "for (int i = 0; i < 42; i++)\n";
        fs << "{\n";
        fs << "    stl_pop_one.push(i);\n";
        fs << "    stl_pop_two.push(i);\n";
        fs << "}\n";
        fs.close();
    }

    /* RL <= false */
    {
        std::stack<int> stl_pop_one;
        std::stack<int> stl_pop_two;
        ft::stack<int> ft_pop_one;
        ft::stack<int> ft_pop_two;

        for (int i = 0; i < 42; i++)
        {
            stl_pop_one.push(i * 2);
            stl_pop_two.push(i);
            ft_pop_one.push(i * 2);
            ft_pop_two.push(i);
        }

        fs.open("./tester/stacks_output/operator_inf_equal_false", std::fstream::in | std::fstream::out | std::fstream::trunc);
        printStackAttributes(fs, stl_pop_one, ft_pop_one);
        printStackAttributes(fs, stl_pop_two, ft_pop_two);
        
        std::cout << ((printBoolResult(fs, (stl_pop_one <= stl_pop_two), (ft_pop_one <= ft_pop_two)) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::stack<int> ft_pop;\n";
        fs << "for (int i = 0; i < 42; i++)\n";
        fs << "{\n";
        fs << "    ft_pop_one.push(i * 2);\n";
        fs << "    ft_pop_two.push(i);\n";
        fs << "}\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::stack<int> stl_pop;\n";
        fs << "for (int i = 0; i < 42; i++)\n";
        fs << "{\n";
        fs << "    stl_pop_one.push(i * 2);\n";
        fs << "    stl_pop_two.push(i);\n";
        fs << "}\n";
        fs.close();
    }

    /* RL > true */
    {
        std::stack<int> stl_pop_one;
        std::stack<int> stl_pop_two;
        ft::stack<int> ft_pop_one;
        ft::stack<int> ft_pop_two;

        for (int i = 0; i < 42; i++)
        {
            stl_pop_one.push(i * 2);
            stl_pop_two.push(i);
            ft_pop_one.push(i * 2);
            ft_pop_two.push(i);
        }

        fs.open("./tester/stacks_output/operator_sup_true", std::fstream::in | std::fstream::out | std::fstream::trunc);
        printStackAttributes(fs, stl_pop_one, ft_pop_one);
        printStackAttributes(fs, stl_pop_two, ft_pop_two);
        
        std::cout << ((printBoolResult(fs, (stl_pop_one > stl_pop_two), (ft_pop_one > ft_pop_two)) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::stack<int> ft_pop;\n";
        fs << "for (int i = 0; i < 42; i++)\n";
        fs << "{\n";
        fs << "    ft_pop_one.push(i * 2);\n";
        fs << "    ft_pop_two.push(i);\n";
        fs << "}\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::stack<int> stl_pop;\n";
        fs << "for (int i = 0; i < 42; i++)\n";
        fs << "{\n";
        fs << "    stl_pop_one.push(i * 2);\n";
        fs << "    stl_pop_two.push(i);\n";
        fs << "}\n";
        fs.close();
    }

    /* RL > false */
    {
        std::stack<int> stl_pop_one;
        std::stack<int> stl_pop_two;
        ft::stack<int> ft_pop_one;
        ft::stack<int> ft_pop_two;

        for (int i = 0; i < 42; i++)
        {
            stl_pop_one.push(i);
            stl_pop_two.push(i);
            ft_pop_one.push(i);
            ft_pop_two.push(i);
        }

        fs.open("./tester/stacks_output/operator_sup_false", std::fstream::in | std::fstream::out | std::fstream::trunc);
        printStackAttributes(fs, stl_pop_one, ft_pop_one);
        printStackAttributes(fs, stl_pop_two, ft_pop_two);
        
        std::cout << ((printBoolResult(fs, (stl_pop_one > stl_pop_two), (ft_pop_one > ft_pop_two)) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::stack<int> ft_pop;\n";
        fs << "for (int i = 0; i < 42; i++)\n";
        fs << "{\n";
        fs << "    ft_pop_one.push(i);\n";
        fs << "    ft_pop_two.push(i);\n";
        fs << "}\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::stack<int> stl_pop;\n";
        fs << "for (int i = 0; i < 42; i++)\n";
        fs << "{\n";
        fs << "    stl_pop_one.push(i);\n";
        fs << "    stl_pop_two.push(i);\n";
        fs << "}\n";
        fs.close();
    }

    /* RL >= true */
    {
        std::stack<int> stl_pop_one;
        std::stack<int> stl_pop_two;
        ft::stack<int> ft_pop_one;
        ft::stack<int> ft_pop_two;

        for (int i = 0; i < 42; i++)
        {
            stl_pop_one.push(i);
            stl_pop_two.push(i);
            ft_pop_one.push(i);
            ft_pop_two.push(i);
        }

        fs.open("./tester/stacks_output/operator_sup_equal_true", std::fstream::in | std::fstream::out | std::fstream::trunc);
        printStackAttributes(fs, stl_pop_one, ft_pop_one);
        printStackAttributes(fs, stl_pop_two, ft_pop_two);
        
        std::cout << ((printBoolResult(fs, (stl_pop_one >= stl_pop_two), (ft_pop_one >= ft_pop_two)) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::stack<int> ft_pop;\n";
        fs << "for (int i = 0; i < 42; i++)\n";
        fs << "{\n";
        fs << "    ft_pop_one.push(i);\n";
        fs << "    ft_pop_two.push(i);\n";
        fs << "}\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::stack<int> stl_pop;\n";
        fs << "for (int i = 0; i < 42; i++)\n";
        fs << "{\n";
        fs << "    stl_pop_one.push(i);\n";
        fs << "    stl_pop_two.push(i);\n";
        fs << "}\n";
        fs.close();
    }

    /* RL >= false */
    {
        std::stack<int> stl_pop_one;
        std::stack<int> stl_pop_two;
        ft::stack<int> ft_pop_one;
        ft::stack<int> ft_pop_two;

        for (int i = 0; i < 42; i++)
        {
            stl_pop_one.push(i);
            ft_pop_one.push(i);
            if (i == 30)
            {
                stl_pop_two.push(i * 2);
                ft_pop_two.push(i * 2);
            }
            else
            {
                stl_pop_two.push(i);
                ft_pop_two.push(i);
            }
        }

        fs.open("./tester/stacks_output/operator_sup_equal_false", std::fstream::in | std::fstream::out | std::fstream::trunc);
        printStackAttributes(fs, stl_pop_one, ft_pop_one);
        printStackAttributes(fs, stl_pop_two, ft_pop_two);
        
        std::cout << ((printBoolResult(fs, (stl_pop_one >= stl_pop_two), (ft_pop_one >= ft_pop_two)) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::stack<int> ft_pop;\n";
        fs << "for (int i = 0; i < 42; i++)\n";
        fs << "{\n";
        fs << "    ft_pop_one.push(i);\n";
        fs << "     if (i == 30)\n";
        fs << "         ft_pop_two.push(i * 2);\n";
        fs << "     else\n";
        fs << "         ft_pop_two.push(i);\n";
        fs << "}\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::stack<int> stl_pop;\n";
        fs << "for (int i = 0; i < 42; i++)\n";
        fs << "{\n";
        fs << "    stl_pop_one.push(i);\n";
        fs << "     if (i == 30)\n";
        fs << "         stl_pop_two.push(i * 2);\n";
        fs << "     else\n";
        fs << "         stl_pop_two.push(i);\n";
        fs << "}\n";
        fs.close();
    }

    std::cout << std::endl;
}