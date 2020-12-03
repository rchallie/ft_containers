/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester_queue.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchallie <rchallie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 00:37:19 by rchallie          #+#    #+#             */
/*   Updated: 2020/12/03 23:44:26 by rchallie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"
#include "../containers/queue.hpp"
#include <queue>

template <class T>
std::string equalContent(
    std::queue<T> stl_queue,
    ft::queue<T> ft_queue
)
{
    while (42)
    {
        if (stl_queue.size() == 0 || ft_queue.size() == 0)
            break;
        if (ft_queue.front() != stl_queue.front())
            return ("✘");
        ft_queue.pop();
        stl_queue.pop();
    }
    return ("✔");
}


template <class T>
bool printQueueAttributes(
    std::fstream& fs,
    std::queue<T> stl_queue,
    ft::queue<T> ft_queue
)
{
    /* STL Values */
    std::string stl_empty = ((stl_queue.empty() == 1) ? "true" : "false");
    size_t stl_size = stl_queue.size();

    /* FT Values */
    std::string ft_empty = ((ft_queue.empty() == 1) ? "true" : "false");
    size_t ft_size = ft_queue.size();

    /* FT Result compare values */
    bool empty = equalbool(ft_empty, stl_empty);
    bool size = equalbool(ft_size, stl_size);
    std::string content = equalContent(stl_queue, ft_queue);
    
    fs << "\n══════════════════════════════════════════════════════════════\n";
    fs << "queues attributes : \n";
    fs << "STL : \n";
    fs << "Empty       : " << stl_empty  << std::endl;
    fs << "Size        : " << stl_size  << std::endl;
    fs << "Content     : [";

    while (42)
    {
        if (stl_queue.size() == 0)
            break;
        fs << stl_queue.front();
        stl_queue.pop();
        if (stl_queue.size() != 0)
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
        if (ft_queue.size() == 0)
            break;
        fs << ft_queue.front();
        ft_queue.pop();
        if (ft_queue.size() != 0)
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

void test_queue()
{
    std::cout << UNDERLINE << "QUEUE :\n" << NORMAL ;

    mkdir("./tester/queues_output", 0777);
    
    std::fstream fs;

    /* Member functions */
    std::cout << "Member functions : ";

    /* Default constructor */
    {
        std::queue<int> stl_queue;
        ft::queue<int> ft_queue;

        fs.open("./tester/queues_output/constructor_default", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printQueueAttributes(fs, stl_queue, ft_queue) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::queue<int> ft_queue;\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::queue<int> stl_queue;\n";
        fs.close();
    }

    /* Empty true */
    {
        std::queue<int> stl_queue;
        ft::queue<int> ft_queue;

        fs.open("./tester/queues_output/empty_true", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printQueueAttributes(fs, stl_queue, ft_queue) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::queue<int> ft_queue;\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::queue<int> stl_queue;\n";
        fs.close();
    }

    /* Empty false */
    {
        std::queue<int> stl_queue;
        ft::queue<int> ft_queue;

        stl_queue.push(42);
        ft_queue.push(42);

        fs.open("./tester/queues_output/empty_false", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printQueueAttributes(fs, stl_queue, ft_queue) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::queue<int> ft_queue;\n";
        fs << "ft_queue.push(42);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::queue<int> stl_queue;\n";
        fs << "stl_queue.push(42);\n";
        fs.close();
    }

    /* Size */
    {
        std::queue<int> stl_queue;
        ft::queue<int> ft_queue;

        for (int i = 0; i < 42; i++)
        {
            stl_queue.push(42);
            ft_queue.push(42);
        }

        fs.open("./tester/queues_output/size", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printQueueAttributes(fs, stl_queue, ft_queue) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::queue<int> ft_queue;\n";
        fs << "ft_queue.push(42);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::queue<int> stl_queue;\n";
        fs << "stl_queue.push(42);\n";
        fs.close();
    }

    /* Front */
    {
        std::queue<int> stl_queue;
        ft::queue<int> ft_queue;

        for (int i = 0; i < 42; i++)
        {
            stl_queue.push(i);
            ft_queue.push(i);
        }

        fs.open("./tester/queues_output/front", std::fstream::in | std::fstream::out | std::fstream::trunc);
        printQueueAttributes(fs, stl_queue, ft_queue);
        
        std::cout << ((printSingleValue(fs, stl_queue.front(), ft_queue.front()) == true) ? "[OK]" : "[NOP]");

        stl_queue.pop();
        ft_queue.pop();
        
        std::cout << ((printSingleValue(fs, stl_queue.front(), ft_queue.front()) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::queue<int> ft_queue;\n";
        fs << "for (int i = 0; i < 42; i++)\n";
        fs << " ft_queue.push(i);\n";
        fs << "Output...\n";
        fs << "ft_queue.pop();\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::queue<int> stl_queue;\n";
        fs << "for (int i = 0; i < 42; i++)\n";
        fs << " stl_queue.push(i);\n";
        fs << "Output...\n";
        fs << "stl_queue.pop();\n";
        fs.close();
    }

    /* Back */
    {
        std::queue<int> stl_queue;
        ft::queue<int> ft_queue;

        for (int i = 0; i < 42; i++)
        {
            stl_queue.push(i);
            ft_queue.push(i);
        }

        fs.open("./tester/queues_output/back", std::fstream::in | std::fstream::out | std::fstream::trunc);
        printQueueAttributes(fs, stl_queue, ft_queue);
        
        std::cout << ((printSingleValue(fs, stl_queue.back(), ft_queue.back()) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::queue<int> ft_queue;\n";
        fs << "for (int i = 0; i < 42; i++)\n";
        fs << " ft_queue.push(i);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::queue<int> stl_queue;\n";
        fs << "for (int i = 0; i < 42; i++)\n";
        fs << " stl_queue.push(i);\n";
        fs.close();
    }

    /* Push */
    {
        std::queue<int> stl_queue;
        ft::queue<int> ft_queue;

        stl_queue.push(42);
        ft_queue.push(42);

        fs.open("./tester/queues_output/push", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printQueueAttributes(fs, stl_queue, ft_queue) == true) ? "[OK]" : "[NOP]");

        stl_queue.push(19);
        ft_queue.push(19);

        std::cout << ((printQueueAttributes(fs, stl_queue, ft_queue) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::queue<int> ft_queue;\n";
        fs << "ft_queue.push(42);\n";
        fs << "Output...\n";
        fs << "ft_queue.push(19);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::queue<int> stl_queue;\n";
        fs << "stl_queue.push(42);\n";
        fs << "Output...\n";
        fs << "ft_queue.push(19);\n";
        fs.close();
    }

    /* Pop */
    {
        std::queue<int> stl_queue;
        ft::queue<int> ft_queue;

        stl_queue.push(42);
        ft_queue.push(42);

        fs.open("./tester/queues_output/push", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printQueueAttributes(fs, stl_queue, ft_queue) == true) ? "[OK]" : "[NOP]");

        stl_queue.pop();
        ft_queue.pop();

        std::cout << ((printQueueAttributes(fs, stl_queue, ft_queue) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::queue<int> ft_queue;\n";
        fs << "ft_queue.push(42);\n";
        fs << "Output...\n";
        fs << "ft_queue.pop();\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::queue<int> stl_queue;\n";
        fs << "stl_queue.push(42);\n";
        fs << "Output...\n";
        fs << "ft_queue.pop();\n";
        fs.close();
    }

    std::cout << std::endl;
    std::cout << "Non-member function overloads : ";

    /* RL = relational operator */

    /* RL == true */
    {
        std::queue<int> stl_pop_one;
        std::queue<int> stl_pop_two;
        ft::queue<int> ft_pop_one;
        ft::queue<int> ft_pop_two;

        for (int i = 0; i < 42; i++)
        {
            stl_pop_one.push(i);
            stl_pop_two.push(i);
            ft_pop_one.push(i);
            ft_pop_two.push(i);
        }

        fs.open("./tester/queues_output/operator_equal_true", std::fstream::in | std::fstream::out | std::fstream::trunc);
        printQueueAttributes(fs, stl_pop_one, ft_pop_one);
        printQueueAttributes(fs, stl_pop_two, ft_pop_two);
        
        std::cout << ((printBoolResult(fs, (stl_pop_one == stl_pop_two), (ft_pop_one == ft_pop_two)) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::queue<int> ft_pop;\n";
        fs << "for (int i = 0; i < 42; i++)\n";
        fs << "{\n";
        fs << "    ft_pop_one.push(i);\n";
        fs << "    ft_pop_two.push(i);\n";
        fs << "}\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::queue<int> stl_pop;\n";
        fs << "for (int i = 0; i < 42; i++)\n";
        fs << "{\n";
        fs << "    stl_pop_one.push(i);\n";
        fs << "    stl_pop_two.push(i);\n";
        fs << "}\n";
        fs.close();
    }

    /* RL == false */
    {
        std::queue<int> stl_pop_one;
        std::queue<int> stl_pop_two;
        ft::queue<int> ft_pop_one;
        ft::queue<int> ft_pop_two;

        for (int i = 0; i < 42; i++)
        {
            stl_pop_one.push(i);
            stl_pop_two.push(i * 2);
            ft_pop_one.push(i);
            ft_pop_two.push(i * 2);
        }

        fs.open("./tester/queues_output/operator_equal_false", std::fstream::in | std::fstream::out | std::fstream::trunc);
        printQueueAttributes(fs, stl_pop_one, ft_pop_one);
        printQueueAttributes(fs, stl_pop_two, ft_pop_two);
        
        std::cout << ((printBoolResult(fs, (stl_pop_one == stl_pop_two), (ft_pop_one == ft_pop_two)) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::queue<int> ft_pop;\n";
        fs << "for (int i = 0; i < 42; i++)\n";
        fs << "{\n";
        fs << "    ft_pop_one.push(i);\n";
        fs << "    ft_pop_two.push(i * 2);\n";
        fs << "}\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::queue<int> stl_pop;\n";
        fs << "for (int i = 0; i < 42; i++)\n";
        fs << "{\n";
        fs << "    stl_pop_one.push(i);\n";
        fs << "    stl_pop_two.push(i * 2);\n";
        fs << "}\n";
        fs.close();
    }

    /* RL != true */
    {
        std::queue<int> stl_pop_one;
        std::queue<int> stl_pop_two;
        ft::queue<int> ft_pop_one;
        ft::queue<int> ft_pop_two;

        for (int i = 0; i < 42; i++)
        {
            stl_pop_one.push(i);
            stl_pop_two.push(i * 2);
            ft_pop_one.push(i);
            ft_pop_two.push(i * 2);
        }

        fs.open("./tester/queues_output/operator_net_equal_true", std::fstream::in | std::fstream::out | std::fstream::trunc);
        printQueueAttributes(fs, stl_pop_one, ft_pop_one);
        printQueueAttributes(fs, stl_pop_two, ft_pop_two);
        
        std::cout << ((printBoolResult(fs, (stl_pop_one != stl_pop_two), (ft_pop_one != ft_pop_two)) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::queue<int> ft_pop;\n";
        fs << "for (int i = 0; i < 42; i++)\n";
        fs << "{\n";
        fs << "    ft_pop_one.push(i);\n";
        fs << "    ft_pop_two.push(i * 2);\n";
        fs << "}\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::queue<int> stl_pop;\n";
        fs << "for (int i = 0; i < 42; i++)\n";
        fs << "{\n";
        fs << "    stl_pop_one.push(i);\n";
        fs << "    stl_pop_two.push(i * 2);\n";
        fs << "}\n";
        fs.close();
    }

    /* RL != false */
    {
        std::queue<int> stl_pop_one;
        std::queue<int> stl_pop_two;
        ft::queue<int> ft_pop_one;
        ft::queue<int> ft_pop_two;

        for (int i = 0; i < 42; i++)
        {
            stl_pop_one.push(i);
            stl_pop_two.push(i);
            ft_pop_one.push(i);
            ft_pop_two.push(i);
        }

        fs.open("./tester/queues_output/operator_not_equal_false", std::fstream::in | std::fstream::out | std::fstream::trunc);
        printQueueAttributes(fs, stl_pop_one, ft_pop_one);
        printQueueAttributes(fs, stl_pop_two, ft_pop_two);
        
        std::cout << ((printBoolResult(fs, (stl_pop_one != stl_pop_two), (ft_pop_one != ft_pop_two)) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::queue<int> ft_pop;\n";
        fs << "for (int i = 0; i < 42; i++)\n";
        fs << "{\n";
        fs << "    ft_pop_one.push(i);\n";
        fs << "    ft_pop_two.push(i);\n";
        fs << "}\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::queue<int> stl_pop;\n";
        fs << "for (int i = 0; i < 42; i++)\n";
        fs << "{\n";
        fs << "    stl_pop_one.push(i);\n";
        fs << "    stl_pop_two.push(i);\n";
        fs << "}\n";
        fs.close();
    }

    /* RL < true */
    {
        std::queue<int> stl_pop_one;
        std::queue<int> stl_pop_two;
        ft::queue<int> ft_pop_one;
        ft::queue<int> ft_pop_two;

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

        fs.open("./tester/queues_output/operator_inf_true", std::fstream::in | std::fstream::out | std::fstream::trunc);
        printQueueAttributes(fs, stl_pop_one, ft_pop_one);
        printQueueAttributes(fs, stl_pop_two, ft_pop_two);
        
        std::cout << ((printBoolResult(fs, (stl_pop_one < stl_pop_two), (ft_pop_one < ft_pop_two)) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::queue<int> ft_pop;\n";
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
        fs << "std::queue<int> stl_pop;\n";
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
        std::queue<int> stl_pop_one;
        std::queue<int> stl_pop_two;
        ft::queue<int> ft_pop_one;
        ft::queue<int> ft_pop_two;

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

        fs.open("./tester/queues_output/operator_inf_false", std::fstream::in | std::fstream::out | std::fstream::trunc);
        printQueueAttributes(fs, stl_pop_one, ft_pop_one);
        printQueueAttributes(fs, stl_pop_two, ft_pop_two);
        
        std::cout << ((printBoolResult(fs, (stl_pop_one < stl_pop_two), (ft_pop_one < ft_pop_two)) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::queue<int> ft_pop;\n";
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
        fs << "std::queue<int> stl_pop;\n";
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
        std::queue<int> stl_pop_one;
        std::queue<int> stl_pop_two;
        ft::queue<int> ft_pop_one;
        ft::queue<int> ft_pop_two;

        for (int i = 0; i < 42; i++)
        {
            stl_pop_one.push(i);
            stl_pop_two.push(i * 2);
            ft_pop_one.push(i);
            ft_pop_two.push(i * 2);
        }

        fs.open("./tester/queues_output/operator_inf_equal_true", std::fstream::in | std::fstream::out | std::fstream::trunc);
        printQueueAttributes(fs, stl_pop_one, ft_pop_one);
        printQueueAttributes(fs, stl_pop_two, ft_pop_two);
        
        std::cout << ((printBoolResult(fs, (stl_pop_one <= stl_pop_two), (ft_pop_one <= ft_pop_two)) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::queue<int> ft_pop;\n";
        fs << "for (int i = 0; i < 42; i++)\n";
        fs << "{\n";
        fs << "    ft_pop_one.push(i);\n";
        fs << "    ft_pop_two.push(i * 2);\n";
        fs << "}\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::queue<int> stl_pop;\n";
        fs << "for (int i = 0; i < 42; i++)\n";
        fs << "{\n";
        fs << "    stl_pop_one.push(i);\n";
        fs << "    stl_pop_two.push(i * 2);\n";
        fs << "}\n";
        fs.close();
    }

    /* RL <= true equal */
    {
        std::queue<int> stl_pop_one;
        std::queue<int> stl_pop_two;
        ft::queue<int> ft_pop_one;
        ft::queue<int> ft_pop_two;

        for (int i = 0; i < 42; i++)
        {
            stl_pop_one.push(i);
            stl_pop_two.push(i);
            ft_pop_one.push(i);
            ft_pop_two.push(i);
        }

        fs.open("./tester/queues_output/operator_inf_equal_true", std::fstream::in | std::fstream::out | std::fstream::trunc);
        printQueueAttributes(fs, stl_pop_one, ft_pop_one);
        printQueueAttributes(fs, stl_pop_two, ft_pop_two);
        
        std::cout << ((printBoolResult(fs, (stl_pop_one <= stl_pop_two), (ft_pop_one <= ft_pop_two)) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::queue<int> ft_pop;\n";
        fs << "for (int i = 0; i < 42; i++)\n";
        fs << "{\n";
        fs << "    ft_pop_one.push(i);\n";
        fs << "    ft_pop_two.push(i);\n";
        fs << "}\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::queue<int> stl_pop;\n";
        fs << "for (int i = 0; i < 42; i++)\n";
        fs << "{\n";
        fs << "    stl_pop_one.push(i);\n";
        fs << "    stl_pop_two.push(i);\n";
        fs << "}\n";
        fs.close();
    }

    /* RL <= false */
    {
        std::queue<int> stl_pop_one;
        std::queue<int> stl_pop_two;
        ft::queue<int> ft_pop_one;
        ft::queue<int> ft_pop_two;

        for (int i = 0; i < 42; i++)
        {
            stl_pop_one.push(i * 2);
            stl_pop_two.push(i);
            ft_pop_one.push(i * 2);
            ft_pop_two.push(i);
        }

        fs.open("./tester/queues_output/operator_inf_equal_false", std::fstream::in | std::fstream::out | std::fstream::trunc);
        printQueueAttributes(fs, stl_pop_one, ft_pop_one);
        printQueueAttributes(fs, stl_pop_two, ft_pop_two);
        
        std::cout << ((printBoolResult(fs, (stl_pop_one <= stl_pop_two), (ft_pop_one <= ft_pop_two)) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::queue<int> ft_pop;\n";
        fs << "for (int i = 0; i < 42; i++)\n";
        fs << "{\n";
        fs << "    ft_pop_one.push(i * 2);\n";
        fs << "    ft_pop_two.push(i);\n";
        fs << "}\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::queue<int> stl_pop;\n";
        fs << "for (int i = 0; i < 42; i++)\n";
        fs << "{\n";
        fs << "    stl_pop_one.push(i * 2);\n";
        fs << "    stl_pop_two.push(i);\n";
        fs << "}\n";
        fs.close();
    }

    /* RL > true */
    {
        std::queue<int> stl_pop_one;
        std::queue<int> stl_pop_two;
        ft::queue<int> ft_pop_one;
        ft::queue<int> ft_pop_two;

        for (int i = 0; i < 42; i++)
        {
            stl_pop_one.push(i * 2);
            stl_pop_two.push(i);
            ft_pop_one.push(i * 2);
            ft_pop_two.push(i);
        }

        fs.open("./tester/queues_output/operator_sup_true", std::fstream::in | std::fstream::out | std::fstream::trunc);
        printQueueAttributes(fs, stl_pop_one, ft_pop_one);
        printQueueAttributes(fs, stl_pop_two, ft_pop_two);
        
        std::cout << ((printBoolResult(fs, (stl_pop_one > stl_pop_two), (ft_pop_one > ft_pop_two)) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::queue<int> ft_pop;\n";
        fs << "for (int i = 0; i < 42; i++)\n";
        fs << "{\n";
        fs << "    ft_pop_one.push(i * 2);\n";
        fs << "    ft_pop_two.push(i);\n";
        fs << "}\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::queue<int> stl_pop;\n";
        fs << "for (int i = 0; i < 42; i++)\n";
        fs << "{\n";
        fs << "    stl_pop_one.push(i * 2);\n";
        fs << "    stl_pop_two.push(i);\n";
        fs << "}\n";
        fs.close();
    }

    /* RL > false */
    {
        std::queue<int> stl_pop_one;
        std::queue<int> stl_pop_two;
        ft::queue<int> ft_pop_one;
        ft::queue<int> ft_pop_two;

        for (int i = 0; i < 42; i++)
        {
            stl_pop_one.push(i);
            stl_pop_two.push(i);
            ft_pop_one.push(i);
            ft_pop_two.push(i);
        }

        fs.open("./tester/queues_output/operator_sup_false", std::fstream::in | std::fstream::out | std::fstream::trunc);
        printQueueAttributes(fs, stl_pop_one, ft_pop_one);
        printQueueAttributes(fs, stl_pop_two, ft_pop_two);
        
        std::cout << ((printBoolResult(fs, (stl_pop_one > stl_pop_two), (ft_pop_one > ft_pop_two)) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::queue<int> ft_pop;\n";
        fs << "for (int i = 0; i < 42; i++)\n";
        fs << "{\n";
        fs << "    ft_pop_one.push(i);\n";
        fs << "    ft_pop_two.push(i);\n";
        fs << "}\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::queue<int> stl_pop;\n";
        fs << "for (int i = 0; i < 42; i++)\n";
        fs << "{\n";
        fs << "    stl_pop_one.push(i);\n";
        fs << "    stl_pop_two.push(i);\n";
        fs << "}\n";
        fs.close();
    }

    /* RL >= true */
    {
        std::queue<int> stl_pop_one;
        std::queue<int> stl_pop_two;
        ft::queue<int> ft_pop_one;
        ft::queue<int> ft_pop_two;

        for (int i = 0; i < 42; i++)
        {
            stl_pop_one.push(i);
            stl_pop_two.push(i);
            ft_pop_one.push(i);
            ft_pop_two.push(i);
        }

        fs.open("./tester/queues_output/operator_sup_equal_true", std::fstream::in | std::fstream::out | std::fstream::trunc);
        printQueueAttributes(fs, stl_pop_one, ft_pop_one);
        printQueueAttributes(fs, stl_pop_two, ft_pop_two);
        
        std::cout << ((printBoolResult(fs, (stl_pop_one >= stl_pop_two), (ft_pop_one >= ft_pop_two)) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::queue<int> ft_pop;\n";
        fs << "for (int i = 0; i < 42; i++)\n";
        fs << "{\n";
        fs << "    ft_pop_one.push(i);\n";
        fs << "    ft_pop_two.push(i);\n";
        fs << "}\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::queue<int> stl_pop;\n";
        fs << "for (int i = 0; i < 42; i++)\n";
        fs << "{\n";
        fs << "    stl_pop_one.push(i);\n";
        fs << "    stl_pop_two.push(i);\n";
        fs << "}\n";
        fs.close();
    }

    /* RL >= false */
    {
        std::queue<int> stl_pop_one;
        std::queue<int> stl_pop_two;
        ft::queue<int> ft_pop_one;
        ft::queue<int> ft_pop_two;

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

        fs.open("./tester/queues_output/operator_sup_equal_false", std::fstream::in | std::fstream::out | std::fstream::trunc);
        printQueueAttributes(fs, stl_pop_one, ft_pop_one);
        printQueueAttributes(fs, stl_pop_two, ft_pop_two);
        
        std::cout << ((printBoolResult(fs, (stl_pop_one >= stl_pop_two), (ft_pop_one >= ft_pop_two)) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::queue<int> ft_pop;\n";
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
        fs << "std::queue<int> stl_pop;\n";
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