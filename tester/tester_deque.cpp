/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester_deque.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchallie <rchallie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 16:50:03 by rchallie          #+#    #+#             */
/*   Updated: 2020/12/08 19:19:23 by rchallie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <deque>
# include "tester.hpp"
# include "../containers/deque.hpp"

template <class T>
std::string equalContent(
    const std::deque<T> & stl_deque,
    const ft::deque<T> & ft_deque
)
{
    typename ft::deque<T>::const_iterator ft_it;
    typename std::deque<T>::const_iterator stl_it;
    if (ft_deque.size() != stl_deque.size())
        return ("✘");
    stl_it = stl_deque.begin();
    for(ft_it = ft_deque.begin(); ft_it != ft_deque.end(); ft_it++)
    {
        if (*ft_it != *stl_it)
            return ("✘");
        stl_it++;
    }
    return ("✔");
}

template <class T>
bool printDequeAttributes(
    std::fstream& fs,
    std::deque<T>& stl_deque,
    ft::deque<T>& ft_deque
)
{
    /* STL Values */
    std::string stl_empty = ((stl_deque.empty() == 1) ? "true" : "false");
    size_t stl_size = stl_deque.size();
    size_t stl_max_size = stl_deque.max_size();

    /* FT Values */
    std::string ft_empty = ((ft_deque.empty() == 1) ? "true" : "false");
    size_t ft_size = ft_deque.size();
    size_t ft_max_size = ft_deque.max_size();

    /* FT Result compare values */
    bool empty = equalbool(ft_empty, stl_empty);
    bool size = equalbool(ft_size, stl_size);
    bool max_size = equalbool(ft_max_size, stl_max_size);
    std::string content = equalContent(stl_deque, ft_deque);
    
    fs << "\n══════════════════════════════════════════════════════════════\n";
    fs << "deques attributes : \n";
    fs << "STL : \n";
    fs << "Empty       : " << stl_empty  << std::endl;
    fs << "Size        : " << stl_size  << std::endl;
    fs << "Max size    : " << stl_max_size  << std::endl;
    fs << "Content     : [";
    
    typename std::deque<T>::const_iterator stl_it;
    for (stl_it = stl_deque.begin();  stl_it != stl_deque.end(); stl_it++)
    {
        fs << *stl_it;
        if (stl_it + 1 != stl_deque.end())
            fs << ", ";
    }
    fs << "]\n";

    fs << std::endl;

    fs << "FT : \n";
    fs << "Empty    [" << equal(ft_empty, stl_empty) << "]: " << ft_empty  << std::endl;
    fs << "Size     [" << equal(ft_size, stl_size) << "]: " << ft_size  << std::endl;
    fs << "Max size [" << equal(ft_max_size, stl_max_size) << "]: " << ft_max_size  << std::endl;

    fs << "Content  [" << content << "]: [";

    typename ft::deque<T>::const_iterator ft_it;
    for(ft_it = ft_deque.begin(); ft_it != ft_deque.end(); ft_it++)
    {
        fs << *ft_it;
        if (ft_it + 1 != ft_deque.end())
            fs << ", ";
    }
    fs << "]\n";

    fs << "══════════════════════════════════════════════════════════════\n";

    /* Error case */
    if (empty == false)
        return (false);
    else if (size == false)
        return (false);
    else if (max_size == false)
        return (false);
    else if (content == "✘")
        return (false);
    return (true);
}

void test_deque()
{
    std::cout << UNDERLINE << "DEQUE :\n" << NORMAL ;

    mkdir("./tester/deques_output", 0777);
    
    std::fstream fs;

    /* Constructors */
    std::cout << "Constructors : ";

    /* Default constructor */
    {
        std::deque<int> stl_default_deque;
        ft::deque<int> ft_default_deque;

        fs.open("./tester/deques_output/constructor_default", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printDequeAttributes(fs, stl_default_deque, ft_default_deque) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::deque<int> ft_default_deque;\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::deque<int> stl_default_deque;\n";
        fs.close();
    }

    /* Default constructor pointer */
    {
        std::deque<int> *stl_pointer_default_deque = new std::deque<int>;
        ft::deque<int> *ft_pointer_default_deque = new ft::deque<int>;

        fs.open("./tester/deques_output/constructor_default_pointer", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printDequeAttributes(fs, *stl_pointer_default_deque, *ft_pointer_default_deque) == true) ? "[OK]" : "[NOP]");
        
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::deque<int> *ft_pointer_default_deque = new ft::deque<int>;\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::deque<int> *stl_pointer_default_deque = new std::deque<int>;\n";
        fs.close();

        delete stl_pointer_default_deque;
        delete ft_pointer_default_deque;
    }

    /* Fill constructor */
    {
        std::deque<int> stl_fill_deque(0);
        ft::deque<int> ft_fill_deque(0);

        fs.open("./tester/deques_output/constructor_fill_empty", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printDequeAttributes(fs, stl_fill_deque, ft_fill_deque) == true) ? "[OK]" : "[NOP]");
        
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::deque<int> ft_fill_deque(0);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::deque<int> stl_fill_deque(0);\n";
        fs.close();
    }

    /* Fill constructor sized */
    {
        std::deque<int> stl_fill_deque_sized(19);
        ft::deque<int> ft_fill_deque_sized(19);

        fs.open("./tester/deques_output/constructor_fill_sized", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printDequeAttributes(fs, stl_fill_deque_sized, ft_fill_deque_sized) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::deque<int> ft_fill_deque_sized(19);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::deque<int> stl_fill_deque_sized(19);\n";
        fs.close();
    }

    /* Fill constructor sized & valued */
    {
        std::deque<int> stl_fill_deque_sized(19, 42);
        ft::deque<int> ft_fill_deque_sized(19, 42);

        fs.open("./tester/deques_output/constructor_fill_sized_valued", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printDequeAttributes(fs, stl_fill_deque_sized, ft_fill_deque_sized) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::deque<int> ft_fill_deque_sized(19, 42);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::deque<int> stl_fill_deque_sized(19, 42);\n";
        fs.close();
    }

    /* Fill constructor sized & valued big */
    {
        std::deque<int> stl_fill_deque_sized(4000, 42);
        ft::deque<int> ft_fill_deque_sized(4000, 42);

        fs.open("./tester/deques_output/constructor_fill_sv_big", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printDequeAttributes(fs, stl_fill_deque_sized, ft_fill_deque_sized) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::deque<int> ft_fill_deque_sized(4000, 42);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::deque<int> stl_fill_deque_sized(4000, 42);\n";
        fs.close();
    }

    /* Range constructor */
    {
        int range_array[] = { 45, 87846, 12, 965, 5 };

        std::deque<int> stl_iterator;
        ft::deque<int> ft_iterator;

        for (int i = 0; i < 5; i++)
        {
            stl_iterator.push_back(range_array[i]);
            ft_iterator.push_back(range_array[i]);
        }

        fs.open("./tester/deques_output/constructor_range", std::fstream::in | std::fstream::out | std::fstream::trunc);

        std::deque<int> stl_range_deque(stl_iterator.begin(), stl_iterator.end());
        ft::deque<int> ft_range_deque(ft_iterator.begin(), ft_iterator.end());

        std::cout << ((printDequeAttributes(fs, stl_range_deque, ft_range_deque) == true) ? "[OK]" : "[NOP]");
        
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = { 45, 87846, 12, 965, 5 };\n";
        fs << "ft::deque<int>::iterator ft_iterator;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    ft_iterator.push_back(range_array[i]);\n";
        fs << "ft::deque<int> ft_range_deque(ft_iterator.begin(), ft_iterator.end());\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = { 45, 87846, 12, 965, 5 };\n";
        fs << "std::deque<int>::iterator stl_iterator;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    stl_iterator.push_back(range_array[i]);\n";
        fs << "std::deque<int> stl_range_deque(stl_iterator.begin(), stl_iterator.end());\n";
        fs.close();
    }

    /* Copy Constructor */
    {
        int range_array[] = { 58, 963, -478, 61, 25};

        std::deque<int> stl_iterator;
        ft::deque<int> ft_iterator;

        for (int i = 0; i < 5; i++)
        {
            stl_iterator.push_back(range_array[i]);
            ft_iterator.push_back(range_array[i]);
        }

        fs.open("./tester/deques_output/constructor_copy", std::fstream::in | std::fstream::out | std::fstream::trunc);

        std::deque<int> stl_range_deque(stl_iterator.begin(), stl_iterator.end());
        ft::deque<int> ft_range_deque(ft_iterator.begin(), ft_iterator.end());

        std::deque<int> stl_copy_deque(stl_range_deque);
        ft::deque<int> ft_copy_deque(ft_range_deque);

        std::cout << ((printDequeAttributes(fs, stl_copy_deque, ft_copy_deque) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = { 58, 963, -478, 61, 25};\n";
        fs << "ft::deque<int>::iterator ft_iterator;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    ft_iterator.push_back(range_array[i]);\n";
        fs << "ft::deque<int> ft_range_deque(ft_iterator.begin(), ft_iterator.end());\n";
        fs << "ft::deque<int> ft_copy_deque(ft_range_deque);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = { 58, 963, -478, 61, 25};\n";
        fs << "std::deque<int>::iterator stl_iterator;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    stl_iterator.push_back(range_array[i]);\n";
        fs << "std::deque<int> stl_range_deque(stl_iterator.begin(), stl_iterator.end());\n";
        fs << "std::deque<int> stl_copy_deque(stl_range_deque);\n";
        fs.close();
    }

    std::cout << "\n";
    std::cout << "Assign : ";

    /* Assign operator */
    {
        int range_array[] = {74, 569, -8822, 8515, 5 };

        std::deque<int> stl_iterator;
        ft::deque<int> ft_iterator;

        for (int i = 0; i < 5; i++)
        {
            stl_iterator.push_back(range_array[i]);
            ft_iterator.push_back(range_array[i]);
        }

        fs.open("./tester/deques_output/operator_assign", std::fstream::in | std::fstream::out | std::fstream::trunc);

        std::deque<int> stl_assign_deque(stl_iterator.begin(), stl_iterator.end());
        ft::deque<int> ft_assign_deque(ft_iterator.begin(), ft_iterator.end());

        std::deque<int> stl_assi_op_deque = stl_assign_deque;
        ft::deque<int> ft_assi_op_deque = ft_assign_deque;

        std::cout << ((printDequeAttributes(fs, stl_assi_op_deque, ft_assi_op_deque) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int assign_array[] = {74, 569, -8822, 8515, 5 };\n";
        fs << "ft::deque<int>::iterator ft_iterator;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    ft_iterator.push_back(assign_array[i]);\n";
        fs << "ft::deque<int> ft_assi_op_deque = ft_assign_deque;\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int assign_array[] = {74, 569, -8822, 8515, 5 };\n";
        fs << "std::deque<int>::iterator stl_iterator;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    stl_iterator.push_back(assign_array[i]);\n";
        fs << "std::deque<int> stl_assi_op_deque = stl_assign_deque;\n";
        fs.close();
    }

    std::cout << "\n";
    std::cout << "Iterator : ";

    /* Iterator begin() */
    {
        int range_array[] = { 87, 92, -5, 8984, 96 };

        std::deque<int> stl_iterator;
        ft::deque<int> ft_iterator;

        for (int i = 0; i < 5; i++)
        {
            stl_iterator.push_back(range_array[i]);
            ft_iterator.push_back(range_array[i]);
        }

        fs.open("./tester/deques_output/iterator_begin", std::fstream::in | std::fstream::out | std::fstream::trunc);

        std::cout << ((printSingleValue(fs, *stl_iterator.begin(), *ft_iterator.begin()) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = { 87, 92, -5, 8984, 96 };\n";
        fs << "ft::deque<int>::iterator ft_iterator;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    ft_iterator.push_back(range_array[i]);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = { 87, 92, -5, 8984, 96 };\n";
        fs << "std::deque<int>::iterator stl_iterator;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    stl_iterator.push_back(range_array[i]);\n";
        fs.close();
    }

    /* Const iterator begin() */
    {
        int range_array[] = { 87, 92, -5, 8984, 96 };

        std::deque<int> stl_iterator;
        ft::deque<int> ft_iterator;

        for (int i = 0; i < 5; i++)
        {
            stl_iterator.push_back(range_array[i]);
            ft_iterator.push_back(range_array[i]);
        }

        fs.open("./tester/deques_output/iterator_begin_const", std::fstream::in | std::fstream::out | std::fstream::trunc);

        std::deque<int>::const_iterator stl_const_it = stl_iterator.begin();
        ft::deque<int>::const_iterator ft_const_it = ft_iterator.begin();

        const int from_stl = *(stl_const_it);
        const int from_ft = *(ft_const_it);

        std::cout << ((printSingleValue(fs, from_stl, from_ft) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = { 87, 92, -5, 8984, 96 };\n";
        fs << "ft::deque<int>::iterator ft_iterator;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    ft_iterator.push_back(range_array[i]);\n";
        fs << "ft::deque<int>::const_iterator ft_const_it = ft_iterator.begin();\n";
        fs << "const int from_ft = *(ft_const_it);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = { 87, 92, -5, 8984, 96 };\n";
        fs << "std::deque<int>::iterator stl_iterator;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    stl_iterator.push_back(range_array[i]);\n";
        fs << "std::deque<int>::const_iterator stl_const_it = stl_iterator.begin();\n";
        fs << "const int from_stl = *(stl_const_it);\n";
        fs.close();
    }

    /* Iterator end() */
    {
        int range_array[] = {95, 89, -6121, 48, 5 };

        std::deque<int> stl_iterator;
        ft::deque<int> ft_iterator;

        for (int i = 0; i < 5; i++)
        {
            stl_iterator.push_back(range_array[i]);
            ft_iterator.push_back(range_array[i]);
        }

        fs.open("./tester/deques_output/iterator_end", std::fstream::in | std::fstream::out | std::fstream::trunc);

        std::cout << ((printSingleValue(fs, *(stl_iterator.end() - 1), *(ft_iterator.end() - 1)) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "/* Checked at end() - 1 */\n";
        fs << "int range_array[] = {95, 89, -6121, 48, 5 };\n";
        fs << "ft::deque<int>::iterator ft_iterator;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    ft_iterator.push_back(range_array[i]);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "/* Checked at end() - 1 */\n";
        fs << "int range_array[] = {95, 89, -6121, 48, 5 };\n";
        fs << "std::deque<int>::iterator stl_iterator;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    stl_iterator.push_back(range_array[i]);\n";
        fs.close();
    }

    /* Iterator end() const */
    {
        int range_array[] = { 52, -45, -9, 956551, 44};

        std::deque<int> stl_iterator;
        ft::deque<int> ft_iterator;

        for (int i = 0; i < 5; i++)
        {
            stl_iterator.push_back(range_array[i]);
            ft_iterator.push_back(range_array[i]);
        }

        fs.open("./tester/deques_output/iterator_end_const", std::fstream::in | std::fstream::out | std::fstream::trunc);

        std::deque<int>::const_iterator stl_const_it = stl_iterator.end();
        ft::deque<int>::const_iterator ft_const_it = ft_iterator.end();

        const int from_stl = *(stl_const_it - 1);
        const int from_ft = *(ft_const_it - 1);

        std::cout << ((printSingleValue(fs, from_stl, from_ft) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = { 52, -45, -9, 956551, 44};\n";
        fs << "ft::deque<int>::iterator ft_iterator;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    ft_iterator.push_back(range_array[i]);\n";
        fs << "ft::deque<int>::const_iterator ft_const_it = ft_iterator.end();\n";
        fs << "const int from_ft = *(ft_const_it - 1);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = { 52, -45, -9, 956551, 44};\n";
        fs << "std::deque<int>::iterator stl_iterator;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    stl_iterator.push_back(range_array[i]);\n";
        fs << "std::deque<int>::const_iterator stl_const_it = stl_iterator.end();\n";
        fs << "const int from_stl = *(stl_const_it - 1);\n";
        fs.close();
    }

    /* Reverse iterator rbegin() */
    {
        int range_array[] = { 250, -1200, -98657, 2, 34};

        std::deque<int> stl_iterator;
        ft::deque<int> ft_iterator;

        for (int i = 0; i < 5; i++)
        {
            stl_iterator.push_back(range_array[i]);
            ft_iterator.push_back(range_array[i]);
        }

        fs.open("./tester/deques_output/iterator_reverse_begin", std::fstream::in | std::fstream::out | std::fstream::trunc);

        std::cout << ((printSingleValue(fs, *stl_iterator.rbegin(), *ft_iterator.rbegin()) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = { 250, -1200, -98657, 2, 34};\n";
        fs << "ft::deque<int>::iterator ft_iterator;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    ft_iterator.push_back(range_array[i]);\n";
        fs << "ft::deque<int>::const_iterator ft_const_it = ft_iterator.rbegin();\n";
        fs << "const int from_ft = *(ft_const_it);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = { 250, -1200, -98657, 2, 34};\n";
        fs << "std::deque<int>::iterator stl_iterator;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    stl_iterator.push_back(range_array[i]);\n";
        fs << "std::deque<int>::const_iterator stl_const_it = stl_iterator.rbegin();\n";
        fs << "const int from_stl = *(stl_const_it);\n";
        fs.close();
    }

    /* Reverse iterator rbegin() const */
    {
        int range_array[] = { 52, -45, -9, 956551, 44};

        std::deque<int> stl_iterator;
        ft::deque<int> ft_iterator;

        for (int i = 0; i < 5; i++)
        {
            stl_iterator.push_back(range_array[i]);
            ft_iterator.push_back(range_array[i]);
        }

        fs.open("./tester/deques_output/iterator_reverse_begin_const", std::fstream::in | std::fstream::out | std::fstream::trunc);

        std::deque<int>::const_reverse_iterator stl_const_it = stl_iterator.rbegin();
        ft::deque<int>::const_reverse_iterator ft_const_it = ft_iterator.rbegin();

        const int from_stl = *(stl_const_it);
        const int from_ft = *(ft_const_it);

        std::cout << ((printSingleValue(fs, from_stl, from_ft) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = { 52, -45, -9, 956551, 44};\n";
        fs << "ft::deque<int>::iterator ft_iterator;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    ft_iterator.push_back(range_array[i]);\n";
        fs << "ft::deque<int>::const_iterator ft_const_it = ft_iterator.rbegin();\n";
        fs << "const int from_ft = *(ft_const_it);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = { 52, -45, -9, 956551, 44};\n";
        fs << "std::deque<int>::iterator stl_iterator;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    stl_iterator.push_back(range_array[i]);\n";
        fs << "std::deque<int>::const_iterator stl_const_it = stl_iterator.rbegin();\n";
        fs << "const int from_stl = *(stl_const_it);\n";
        fs.close();
    }

    /* Reverse iterator rend() */
    {
        int range_array[] = {95, 89, -6121, 48, 5 };

        std::deque<int> stl_iterator;
        ft::deque<int> ft_iterator;

        for (int i = 0; i < 5; i++)
        {
            stl_iterator.push_back(range_array[i]);
            ft_iterator.push_back(range_array[i]);
        }

        fs.open("./tester/deques_output/iterator_reverse_end", std::fstream::in | std::fstream::out | std::fstream::trunc);

        std::cout << ((printSingleValue(fs, *(stl_iterator.rend() - 1), *(ft_iterator.rend() - 1)) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "/* Checked at rend() - 1 */\n";
        fs << "int range_array[] = {95, 89, -6121, 48, 5 };\n";
        fs << "ft::deque<int>::iterator ft_iterator;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    ft_iterator.push_back(range_array[i]);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "/* Checked at rend() - 1 */\n";
        fs << "int range_array[] = {95, 89, -6121, 48, 5 };\n";
        fs << "std::deque<int>::iterator stl_iterator;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    stl_iterator.push_back(range_array[i]);\n";
        fs.close();
    }

    /* Reverse iterator rend() const */
    {
        int range_array[] = { 8, -5615, 412, 89, 475};

        std::deque<int> stl_iterator;
        ft::deque<int> ft_iterator;

        for (int i = 0; i < 5; i++)
        {
            stl_iterator.push_back(range_array[i]);
            ft_iterator.push_back(range_array[i]);
        }

        fs.open("./tester/deques_output/iterator_revese_rend_const", std::fstream::in | std::fstream::out | std::fstream::trunc);

        std::deque<int>::const_reverse_iterator stl_const_it = stl_iterator.rend();
        ft::deque<int>::const_reverse_iterator ft_const_it = ft_iterator.rend();

        const int from_stl = *(stl_const_it - 1);
        const int from_ft = *(ft_const_it - 1);

        std::cout << ((printSingleValue(fs, from_stl, from_ft) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = { 8, -5615, 412, 89, 475};\n";
        fs << "ft::deque<int>::iterator ft_iterator;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    ft_iterator.push_back(range_array[i]);\n";
        fs << "ft::deque<int>::const_iterator ft_const_it = ft_iterator.rend();\n";
        fs << "const int from_ft = *(ft_const_it - 1);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = { 8, -5615, 412, 89, 475};\n";
        fs << "std::deque<int>::iterator stl_iterator;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    stl_iterator.push_back(range_array[i]);\n";
        fs << "std::deque<int>::const_iterator stl_const_it = stl_iterator.rend();\n";
        fs << "const int from_stl = *(stl_const_it - 1);\n";
        fs.close();
    }
    
    std::cout << "\n";
    std::cout << "Capacity : ";

    /* Size small */
    {
        std::deque<int> stl_filled(20);
        ft::deque<int> ft_filled(20);

        fs.open("./tester/deques_output/size_small", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printDequeAttributes(fs, stl_filled, ft_filled) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::deque<int> ft_filled(20);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::deque<int> stl_filled(20);\n";
        fs.close();
    }

    /* Size big */
    {
        std::deque<int> stl_filled(1000000);
        ft::deque<int> ft_filled(1000000);

        fs.open("./tester/deques_output/size_big", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printDequeAttributes(fs, stl_filled, ft_filled) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::deque<int> ft_filled(1000000);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::deque<int> stl_filled(1000000);\n";
        fs.close();
    }

    /* Maximum size */
    {
        std::deque<int> stl_base;
        ft::deque<int> ft_base;

        fs.open("./tester/deques_output/maximum_size", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printDequeAttributes(fs, stl_base, ft_base) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::deque<int> ft_base;\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::deque<int> stl_base;\n";
        fs.close();    
    }

    /* Resize extension */
    {
        std::deque<int> stl_base(40);
        ft::deque<int> ft_base(40);

        stl_base.resize(85);
        ft_base.resize(85);

        fs.open("./tester/deques_output/resize_extension", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printDequeAttributes(fs, stl_base, ft_base) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::deque<int> ft_base(40);\n";
        fs << "ft_base.resize(85);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::deque<int> stl_base(40);\n";
        fs << "stl_base.resize(85);\n";
        fs.close();  
    }

    /* Resize reduction */
    {
        std::deque<int> stl_base(40);
        ft::deque<int> ft_base(40);

        stl_base.resize(3);
        ft_base.resize(3);

        fs.open("./tester/deques_output/resize_reduction", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printDequeAttributes(fs, stl_base, ft_base) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::deque<int> ft_base(40);\n";
        fs << "ft_base.resize(3);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::deque<int> stl_base(40);\n";
        fs << "stl_base.resize(3);\n";
        fs.close();   
    }

    /* Empty true */
    {
        std::deque<int> stl_base;
        ft::deque<int> ft_base;

        fs.open("./tester/deques_output/empty_true", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printDequeAttributes(fs, stl_base, ft_base) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::deque<int> ft_base;\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::deque<int> stl_base;\n";
        fs.close();
    }

    /* Empty false */
    {
        std::deque<int> stl_base(5);
        ft::deque<int> ft_base(5);

        fs.open("./tester/deques_output/empty_false", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printDequeAttributes(fs, stl_base, ft_base) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::deque<int> ft_base(5);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::deque<int> stl_base(5);\n";
        fs.close();
    }

    /* Empty after resize */
    {
        std::deque<int> stl_base(5);
        ft::deque<int> ft_base(5);

        stl_base.resize(0);
        ft_base.resize(0);

        fs.open("./tester/deques_output/empty_after_resize", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printDequeAttributes(fs, stl_base, ft_base) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::deque<int> ft_base(5);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::deque<int> stl_base(5);\n";
        fs << "stl_base.resize(0);\n";
        fs.close();
    }

    std::cout << "\n";
    std::cout << "Element access : ";

    /* Operator at */
    {
        int range_array[] = { 8, -5615, 412, 89, 475};

        std::deque<int> stl_iterator;
        ft::deque<int> ft_iterator;

        for (int i = 0; i < 5; i++)
        {
            stl_iterator.push_back(range_array[i]);
            ft_iterator.push_back(range_array[i]);
        }

        fs.open("./tester/deques_output/operator_at", std::fstream::in | std::fstream::out | std::fstream::trunc);

        int from_stl = stl_iterator[1];
        int from_ft = ft_iterator[1];

        std::cout << ((printSingleValue(fs, from_stl, from_ft) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = { 8, -5615, 412, 89, 475};\n";
        fs << "ft::deque<int>::iterator ft_iterator;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    ft_iterator.push_back(range_array[i]);\n";
        fs << "int from_ft = ft_iterator[1];\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = { 8, -5615, 412, 89, 475};\n";
        fs << "std::deque<int>::iterator stl_iterator;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    stl_iterator.push_back(range_array[i]);\n";
        fs << "int from_stl = stl_iterator[1];\n";
        fs.close();
    }

    /* Operator at const */
    {
        int range_array[] = {8, -98, 541, 53361, 9};

        std::deque<int> stl_iterator;
        ft::deque<int> ft_iterator;

        for (int i = 0; i < 5; i++)
        {
            stl_iterator.push_back(range_array[i]);
            ft_iterator.push_back(range_array[i]);
        }

        fs.open("./tester/deques_output/operator_at_const", std::fstream::in | std::fstream::out | std::fstream::trunc);

        const int from_stl = stl_iterator[1];
        const int from_ft = ft_iterator[1];

        std::cout << ((printSingleValue(fs, from_stl, from_ft) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {8, -98, 541, 53361, 9};\n";
        fs << "ft::deque<int>::iterator ft_iterator;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    ft_iterator.push_back(range_array[i]);\n";
        fs << "const int from_ft = ft_iterator[1];\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {8, -98, 541, 53361, 9};\n";
        fs << "std::deque<int>::iterator stl_iterator;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    stl_iterator.push_back(range_array[i]);\n";
        fs << "const int from_stl = stl_iterator[1];\n";
        fs.close();
    }

    /* at() */
    {
        int range_array[] = {8, -986, -8, 66, 7};

        std::deque<int> stl_iterator;
        ft::deque<int> ft_iterator;

        for (int i = 0; i < 5; i++)
        {
            stl_iterator.push_back(range_array[i]);
            ft_iterator.push_back(range_array[i]);
        }

        fs.open("./tester/deques_output/at", std::fstream::in | std::fstream::out | std::fstream::trunc);

        int from_stl = stl_iterator.at(3);
        int from_ft = ft_iterator.at(3);

        std::cout << ((printSingleValue(fs, from_stl, from_ft) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {8, -986, -8, 66, 7};\n";
        fs << "ft::deque<int>::iterator ft_iterator;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    ft_iterator.push_back(range_array[i]);\n";
        fs << "int from_ft = ft_iterator.at(3);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {8, -986, -8, 66, 7};\n";
        fs << "std::deque<int>::iterator stl_iterator;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    stl_iterator.push_back(range_array[i]);\n";
        fs << "int from_stl = stl_iterator.at(3);\n";
        fs.close();
    }

    /* at() const */
    {
        int range_array[] = {845, -9, 47, 4, -825};

        std::deque<int> stl_iterator;
        ft::deque<int> ft_iterator;

        for (int i = 0; i < 5; i++)
        {
            stl_iterator.push_back(range_array[i]);
            ft_iterator.push_back(range_array[i]);
        }

        fs.open("./tester/deques_output/at_const", std::fstream::in | std::fstream::out | std::fstream::trunc);

        const int from_stl = stl_iterator.at(2);
        const int from_ft = ft_iterator.at(2);

        std::cout << ((printSingleValue(fs, from_stl, from_ft) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {845, -9, 47, 4, -825};\n";
        fs << "ft::deque<int>::iterator ft_iterator;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    ft_iterator.push_back(range_array[i]);\n";
        fs << "const int from_ft = ft_iterator.at(2);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {845, -9, 47, 4, -825};\n";
        fs << "std::deque<int>::iterator stl_iterator;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    stl_iterator.push_back(range_array[i]);\n";
        fs << "const int from_stl = stl_iterator.at(2);\n";
        fs.close();
    }

    /* front() */
    {
        int range_array[] = {2, 0, 982, -9, 87};

        std::deque<int> stl_iterator;
        ft::deque<int> ft_iterator;

        for (int i = 0; i < 5; i++)
        {
            stl_iterator.push_back(range_array[i]);
            ft_iterator.push_back(range_array[i]);
        }

        fs.open("./tester/deques_output/front", std::fstream::in | std::fstream::out | std::fstream::trunc);

        int from_stl = stl_iterator.front();
        int from_ft = ft_iterator.front();

        std::cout << ((printSingleValue(fs, from_stl, from_ft) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {2, 0, 982, -9, 87};\n";
        fs << "ft::deque<int>::iterator ft_iterator;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    ft_iterator.push_back(range_array[i]);\n";
        fs << "int from_ft = ft_iterator.front();\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {2, 0, 982, -9, 87};\n";
        fs << "std::deque<int>::iterator stl_iterator;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    stl_iterator.push_back(range_array[i]);\n";
        fs << "int from_stl = stl_iterator.front();\n";
        fs.close();
    }

    /* front() const */
    {
        int range_array[] = {5589, -97, -98, -63, 8};

        std::deque<int> stl_iterator;
        ft::deque<int> ft_iterator;

        for (int i = 0; i < 5; i++)
        {
            stl_iterator.push_back(range_array[i]);
            ft_iterator.push_back(range_array[i]);
        }

        fs.open("./tester/deques_output/front_const", std::fstream::in | std::fstream::out | std::fstream::trunc);

        const int from_stl = stl_iterator.front();
        const int from_ft = ft_iterator.front();

        std::cout << ((printSingleValue(fs, from_stl, from_ft) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {5589, -97, -98, -63, 8};\n";
        fs << "ft::deque<int>::iterator ft_iterator;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    ft_iterator.push_back(range_array[i]);\n";
        fs << "const int from_ft = ft_iterator.front();\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {5589, -97, -98, -63, 8};\n";
        fs << "std::deque<int>::iterator stl_iterator;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    stl_iterator.push_back(range_array[i]);\n";
        fs << "const int from_stl = stl_iterator.front();\n";
        fs.close();
    }

    /* back() */
    {
        int range_array[] = {2, 0, 982, -9, 87};

        std::deque<int> stl_iterator;
        ft::deque<int> ft_iterator;

        for (int i = 0; i < 5; i++)
        {
            stl_iterator.push_back(range_array[i]);
            ft_iterator.push_back(range_array[i]);
        }

        fs.open("./tester/deques_output/back", std::fstream::in | std::fstream::out | std::fstream::trunc);

        int from_stl = stl_iterator.back();
        int from_ft = ft_iterator.back();

        std::cout << ((printSingleValue(fs, from_stl, from_ft) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {2, 0, 982, -9, 87};\n";
        fs << "ft::deque<int>::iterator ft_iterator;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    ft_iterator.push_back(range_array[i]);\n";
        fs << "int from_ft = ft_iterator.back();\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {2, 0, 982, -9, 87};\n";
        fs << "std::deque<int>::iterator stl_iterator;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    stl_iterator.push_back(range_array[i]);\n";
        fs << "int from_stl = stl_iterator.back();\n";
        fs.close();
    }

    /* back() const */
    {
        int range_array[] = {5589, -97, -98, -63, 8};

        std::deque<int> stl_iterator;
        ft::deque<int> ft_iterator;

        for (int i = 0; i < 5; i++)
        {
            stl_iterator.push_back(range_array[i]);
            ft_iterator.push_back(range_array[i]);
        }

        fs.open("./tester/deques_output/back_const", std::fstream::in | std::fstream::out | std::fstream::trunc);

        const int from_stl = stl_iterator.back();
        const int from_ft = ft_iterator.back();

        std::cout << ((printSingleValue(fs, from_stl, from_ft) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {5589, -97, -98, -63, 8};\n";
        fs << "ft::deque<int>::iterator ft_iterator;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    ft_iterator.push_back(range_array[i]);\n";
        fs << "const int from_ft = ft_iterator.back();\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {5589, -97, -98, -63, 8};\n";
        fs << "std::deque<int>::iterator stl_iterator;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    stl_iterator.push_back(range_array[i]);\n";
        fs << "const int from_stl = stl_iterator.back();\n";
        fs.close();
    }

    std::cout << "\n";
    std::cout << "Modifiers : ";

    /* Assign range */
    {
        int range_array[] = {5589, -97, -98, -63, 8};

        std::deque<int> stl_iterator;
        ft::deque<int> ft_iterator;

        for (int i = 0; i < 5; i++)
        {
            stl_iterator.push_back(range_array[i]);
            ft_iterator.push_back(range_array[i]);
        }

        fs.open("./tester/deques_output/assign_range", std::fstream::in | std::fstream::out | std::fstream::trunc);

        std::deque<int> stl_assign;
        ft::deque<int> ft_assign;

        stl_assign.assign(stl_iterator.begin(), stl_iterator.end());
        ft_assign.assign(ft_iterator.begin(), ft_iterator.end());

        std::cout << ((printDequeAttributes(fs, stl_assign, ft_assign) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {5589, -97, -98, -63, 8};\n";
        fs << "ft::deque<int>::iterator ft_iterator;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    ft_iterator.push_back(range_array[i]);\n";
        fs << "ft::deque<int> ft_assign;\n";
        fs << "ft_assign.assign(ft_iterator.begin(), ft_iterator.end());\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {5589, -97, -98, -63, 8};\n";
        fs << "std::deque<int>::iterator stl_iterator;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    stl_iterator.push_back(range_array[i]);\n";
        fs << "std::deque<int> stl_assign;\n";
        fs << "stl_assign.assign(stl_iterator.begin(), stl_iterator.end());\n";
        fs.close();
    } 

    /* Assign range replace */
    {
        int range_array[] = {5589, -97, -98, -63, 8};

        std::deque<int> stl_iterator;
        ft::deque<int> ft_iterator;

        for (int i = 0; i < 5; i++)
        {
            stl_iterator.push_back(range_array[i]);
            ft_iterator.push_back(range_array[i]);
        }

        fs.open("./tester/deques_output/assign_range_replace", std::fstream::in | std::fstream::out | std::fstream::trunc);

        std::deque<int> stl_assign(42);
        ft::deque<int> ft_assign(42);

        stl_assign.assign(stl_iterator.begin(), stl_iterator.end());
        ft_assign.assign(ft_iterator.begin(), ft_iterator.end());

        std::cout << ((printDequeAttributes(fs, stl_assign, ft_assign) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {5589, -97, -98, -63, 8};\n";
        fs << "ft::deque<int>::iterator ft_iterator;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    ft_iterator.push_back(range_array[i]);\n";
        fs << "ft::deque<int> ft_assign(42);\n";
        fs << "ft_assign.assign(ft_iterator.begin(), ft_iterator.end());\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {5589, -97, -98, -63, 8};\n";
        fs << "std::deque<int>::iterator stl_iterator;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    stl_iterator.push_back(range_array[i]);\n";
        fs << "std::deque<int> stl_assign(42);\n";
        fs << "stl_assign.assign(stl_iterator.begin(), stl_iterator.end());\n";
        fs.close();
    }

    /* Assign fill */
    {
        std::deque<int> stl_assign_fill;
        ft::deque<int> ft_assign_fill;

        stl_assign_fill.assign(87, 42);
        ft_assign_fill.assign(87, 42);
        
        fs.open("./tester/deques_output/assign_fill", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printDequeAttributes(fs, stl_assign_fill, ft_assign_fill) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::deque<int> ft_assign_fill;\n";
        fs << "ft_assign_fill.assign(87, 42);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";    
        fs << "std::deque<int> stl_assign_fill;\n";
        fs << "stl_assign_fill.assign(87, 42);\n";
        fs.close();      
    }

    /* Assign fill replace */
    {
        std::deque<int> stl_assign_fill(42);
        ft::deque<int> ft_assign_fill(42);

        stl_assign_fill.assign(420, 14);
        ft_assign_fill.assign(420, 14);
        
        fs.open("./tester/deques_output/assign_fill_replace", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printDequeAttributes(fs, stl_assign_fill, ft_assign_fill) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::deque<int> ft_assign_fill;\n";
        fs << "ft_assign_fill.assign(87, 42);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";    
        fs << "std::deque<int> stl_assign_fill;\n";
        fs << "stl_assign_fill.assign(87, 42);\n";
        fs.close();
    }

    /* Push back empty */
    {
        std::deque<int> stl_pushback;
        ft::deque<int> ft_pushback;

        stl_pushback.push_back(42);
        ft_pushback.push_back(42);

        fs.open("./tester/deques_output/push_back_empty", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printDequeAttributes(fs, stl_pushback, ft_pushback) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::deque<int> ft_pushback;\n";
        fs << "ft_pushback.push_back(42);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::deque<int> stl_pushback;\n";
        fs << "stl_pushback.push_back(42);\n";
        fs.close();
    }

    /* Push back */
    {
        int range_array[] = {5589, -97, -98, -63, 8};

        std::deque<int> stl_iterator;
        ft::deque<int> ft_iterator;

        for (int i = 0; i < 5; i++)
        {
            stl_iterator.push_back(range_array[i]);
            ft_iterator.push_back(range_array[i]);
        }

        fs.open("./tester/deques_output/push_back", std::fstream::in | std::fstream::out | std::fstream::trunc);

        stl_iterator.push_back(999);
        ft_iterator.push_back(999);

        std::cout << ((printDequeAttributes(fs, stl_iterator, ft_iterator) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {5589, -97, -98, -63, 8};\n";
        fs << "ft::deque<int>::iterator ft_iterator;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    ft_iterator.push_back(range_array[i]);\n";
        fs << "ft_iterator.push_back(999);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {5589, -97, -98, -63, 8};\n";
        fs << "std::deque<int>::iterator stl_iterator;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    stl_iterator.push_back(range_array[i]);\n";
        fs << "stl_iterator.push_back(999);\n";
        fs.close();
    }

    /* Push front empty */
    {
        std::deque<int> stl_pushback;
        ft::deque<int> ft_pushback;

        stl_pushback.push_back(42);
        ft_pushback.push_back(42);

        fs.open("./tester/deques_output/push_back_empty", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printDequeAttributes(fs, stl_pushback, ft_pushback) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::deque<int> ft_pushback;\n";
        fs << "ft_pushback.push_back(42);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::deque<int> stl_pushback;\n";
        fs << "stl_pushback.push_back(42);\n";
        fs.close();
    }

    /* Push front */
    {
        std::deque<int> stl_pushback(10);
        ft::deque<int> ft_pushback(10);

        stl_pushback.push_front(42);
        ft_pushback.push_front(42);

        fs.open("./tester/deques_output/push_front", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printDequeAttributes(fs, stl_pushback, ft_pushback) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::deque<int> ft_pushback(10);\n";
        fs << "ft_pushback.push_front(42);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::deque<int> stl_pushback(10);\n";
        fs << "stl_pushback.push_front(42);\n";
        fs.close();    
    }

    /* Pop back */
    {
        int range_array[] = {547, 98, -6, 0, 47};

        std::deque<int> stl_popback;
        ft::deque<int> ft_popback;

        for (int i = 0; i < 5; i++)
        {
            stl_popback.push_back(range_array[i]);
            ft_popback.push_back(range_array[i]);
        }

        stl_popback.pop_back();
        ft_popback.pop_back();
        
        fs.open("./tester/deques_output/pop_back", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printDequeAttributes(fs, stl_popback, ft_popback) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {547, 98, -6, 0, 47};\n";
        fs << "ft::deque<int> ft_popback;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    ft_popback.push_back(range_array[i]);\n";
        fs << "ft_popback.pop_back();\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {547, 98, -6, 0, 47};\n";
        fs << "std::deque<int> stl_popback;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    stl_popback.push_back(range_array[i]);\n";
        fs << "stl_popback.pop_back();\n";
        fs.close();
    }

    /* Pop front */
    {
        int range_array[] = {149, -78, 53, 5444, 62};

        std::deque<int> stl_popfront;
        ft::deque<int> ft_popfront;

        for (int i = 0; i < 5; i++)
        {
            stl_popfront.push_back(range_array[i]);
            ft_popfront.push_back(range_array[i]);
        }

        stl_popfront.pop_front();
        ft_popfront.pop_front();
        
        fs.open("./tester/deques_output/pop_front", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printDequeAttributes(fs, stl_popfront, ft_popfront) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {149, -78, 53, 5444, 62};\n";
        fs << "ft::deque<int> ft_popfront;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    ft_popfront.push_back(range_array[i]);\n";
        fs << "ft_popfront.pop_front();\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {149, -78, 53, 5444, 62};\n";
        fs << "std::deque<int> stl_popfront;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    stl_popfront.push_back(range_array[i]);\n";
        fs << "stl_popfront.pop_front();\n";
        fs.close();
    }

    /* Insert single begin */
    {
        int range_array[] = {147, 985, -9, -9965, 4};

        std::deque<int> stl_insert;
        ft::deque<int> ft_insert;

        for (int i = 0; i < 5; i++)
        {
            stl_insert.push_back(range_array[i]);
            ft_insert.push_back(range_array[i]);
        }

        stl_insert.insert(stl_insert.begin(), 42);
        ft_insert.insert(ft_insert.begin(), 42);
        
        fs.open("./tester/deques_output/insert_single_begin", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printDequeAttributes(fs, stl_insert, ft_insert) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {147, 985, -9, -9965, 4};\n";
        fs << "ft::deque<int> ft_insert;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    ft_insert.push_back(range_array[i]);\n";
        fs << "ft_insert.insert(ft_insert.begin(), 42);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {147, 985, -9, -9965, 4};\n";
        fs << "std::deque<int> stl_insert;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    stl_insert.push_back(range_array[i]);\n";
        fs << "stl_insert.insert(stl_insert.begin(), 42);\n";
        fs.close();
    }

    /* Insert single end */
    {
        int range_array[] = {147, 84, 55, -9, 777};

        std::deque<int> stl_insert;
        ft::deque<int> ft_insert;

        for (int i = 0; i < 5; i++)
        {
            stl_insert.push_back(range_array[i]);
            ft_insert.push_back(range_array[i]);
        }

        stl_insert.insert(stl_insert.end(), 42);
        ft_insert.insert(ft_insert.end(), 42);
        
        fs.open("./tester/deques_output/insert_single_end", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printDequeAttributes(fs, stl_insert, ft_insert) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {147, 84, 55, -9, 777};\n";
        fs << "ft::deque<int> ft_insert;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    ft_insert.push_back(range_array[i]);\n";
        fs << "ft_insert.insert(ft_insert.end(), 42);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {147, 84, 55, -9, 777};\n";
        fs << "std::deque<int> stl_insert;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    stl_insert.push_back(range_array[i]);\n";
        fs << "stl_insert.insert(stl_insert.end(), 42);\n";
        fs.close();
    }
    
    /* Insert single middle*/
    {
        int range_array[] = {654, 987, -32, 47, 85};

        std::deque<int> stl_insert;
        ft::deque<int> ft_insert;

        for (int i = 0; i < 5; i++)
        {
            stl_insert.push_back(range_array[i]);
            ft_insert.push_back(range_array[i]);
        }

        stl_insert.insert(stl_insert.begin() + 2, 42);
        ft_insert.insert(ft_insert.begin() + 2, 42);
        
        fs.open("./tester/deques_output/insert_single_middle", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printDequeAttributes(fs, stl_insert, ft_insert) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {654, 987, -32, 47, 85};\n";
        fs << "ft::deque<int> ft_insert;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    ft_insert.push_back(range_array[i]);\n";
        fs << "ft_insert.insert(ft_insert.begin() + 2, 42);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {654, 987, -32, 47, 85};\n";
        fs << "std::deque<int> stl_insert;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    stl_insert.push_back(range_array[i]);\n";
        fs << "stl_insert.insert(stl_insert.begin() + 2, 42);\n";
        fs.close();
    }

    /* Insert fill */
    {
        std::deque<int> stl_insert(10);
        ft::deque<int> ft_insert(10);

        stl_insert.insert(stl_insert.begin() + 2, 10, 42);
        ft_insert.insert(ft_insert.begin() + 2, 10, 42);

        fs.open("./tester/deques_output/insert_fill", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printDequeAttributes(fs, stl_insert, ft_insert) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::deque<int> ft_insert(10);\n";
        fs << "ft_insert.insert(ft_insert.begin() + 2, 10, 42);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::deque<int> stl_insert(10);\n";
        fs << "stl_insert.insert(stl_insert.begin() + 2, 10, 42);\n";
        fs.close();
    }

    /* Insert fill big */
    {
        std::deque<int> stl_insert(10);
        ft::deque<int> ft_insert(10);

        stl_insert.insert(stl_insert.begin() + 2, 10000, 42);
        ft_insert.insert(ft_insert.begin() + 2, 10000, 42);

        fs.open("./tester/deques_output/insert_fill_big", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printDequeAttributes(fs, stl_insert, ft_insert) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::deque<int> ft_insert(10);\n";
        fs << "ft_insert.insert(ft_insert.begin() + 2, 10000, 42);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::deque<int> stl_insert(10);\n";
        fs << "stl_insert.insert(stl_insert.begin() + 2, 10000, 42);\n";
        fs.close();
    }

    /* Insert range begin */
    {
        int range_array[] = {147, 985, -9, -9965, 4};

        std::deque<int> stl_range;
        ft::deque<int> ft_range;

        for (int i = 0; i < 5; i++)
        {
            stl_range.push_back(range_array[i]);
            ft_range.push_back(range_array[i]);
        }

        std::deque<int> stl_insert(10);
        ft::deque<int> ft_insert(10);

        stl_insert.insert(stl_insert.begin(), stl_range.begin(), stl_range.end());
        ft_insert.insert(ft_insert.begin(), ft_range.begin(), ft_range.end());

        fs.open("./tester/deques_output/insert_range_begin", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printDequeAttributes(fs, stl_insert, ft_insert) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::deque<int> ft_insert(10);\n";
        fs << "ft_insert.insert(ft_insert.begin(), ft_range.begin(), ft_range.end());\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::deque<int> stl_insert(10);\n";
        fs << "stl_insert.insert(stl_insert.begin(), stl_range.begin(), stl_range.end());\n";
        fs.close();
    }

    /* Insert range end */
    {
        int range_array[] = {147, 985, -9, -9965, 4};

        std::deque<int> stl_range;
        ft::deque<int> ft_range;

        for (int i = 0; i < 5; i++)
        {
            stl_range.push_back(range_array[i]);
            ft_range.push_back(range_array[i]);
        }

        std::deque<int> stl_insert(10);
        ft::deque<int> ft_insert(10);

        stl_insert.insert(stl_insert.end(), stl_range.begin(), stl_range.end());
        ft_insert.insert(ft_insert.end(), ft_range.begin(), ft_range.end());

        fs.open("./tester/deques_output/insert_range_end", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printDequeAttributes(fs, stl_insert, ft_insert) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::deque<int> ft_insert(10);\n";
        fs << "ft_insert.insert(ft_insert.end(), ft_range.begin(), ft_range.end());\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::deque<int> stl_insert(10);\n";
        fs << "stl_insert.insert(stl_insert.end(), stl_range.begin(), stl_range.end());\n";
        fs.close();
    }

    /* Insert range middle */
    {
        int range_array[] = {147, 985, -9, -9965, 4};

        std::deque<int> stl_range;
        ft::deque<int> ft_range;

        for (int i = 0; i < 5; i++)
        {
            stl_range.push_back(range_array[i]);
            ft_range.push_back(range_array[i]);
        }

        std::deque<int> stl_insert(10);
        ft::deque<int> ft_insert(10);

        stl_insert.insert(stl_insert.begin() + 2, stl_range.begin(), stl_range.end());
        ft_insert.insert(ft_insert.begin() + 2, ft_range.begin(), ft_range.end());

        fs.open("./tester/deques_output/insert_range_middle", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printDequeAttributes(fs, stl_insert, ft_insert) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {147, 985, -9, -9965, 4};\n";
        fs << "ft::deque<int> ft_range;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    ft_range.push_back(range_array[i]);\n";
        fs << "ft::deque<int> ft_insert(10);\n";
        fs << "ft_insert.insert(ft_insert.begin() + 2, ft_range.begin(), ft_range.end());\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {147, 985, -9, -9965, 4};\n";
        fs << "std::deque<int> stl_range;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    stl_range.push_back(range_array[i]);\n";
        fs << "std::deque<int> stl_insert(10);\n";
        fs << "stl_insert.insert(stl_insert.begin() + 2, stl_range.begin(), stl_range.end());\n";
        fs.close();
    }

    /* Erase simple */
    {
        int range_array[] = {147, -985, 666, 8, 9};

        std::deque<int> stl_range;
        ft::deque<int> ft_range;

        for (int i = 0; i < 5; i++)
        {
            stl_range.push_back(range_array[i]);
            ft_range.push_back(range_array[i]);
        }

        stl_range.erase(stl_range.begin() + 2);
        ft_range.erase(ft_range.begin() + 2);
        
        fs.open("./tester/deques_output/erase_simple", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printDequeAttributes(fs, stl_range, ft_range) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";    
        fs << "int range_array[] = {147, -985, 666, 8, 9};\n";
        fs << "ft::deque<int> ft_range;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    ft_range.push_back(range_array[i]);\n";
        fs << "ft_range.erase(ft_range.begin() + 2);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";    
        fs << "int range_array[] = {147, -985, 666, 8, 9};\n";
        fs << "std::deque<int> stl_range;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    stl_range.push_back(range_array[i]);\n";
        fs << "stl_range.erase(stl_range.begin() + 2);\n";
        fs.close();
    }

    /* Erase range begin */
    {
        int range_array[] = {147, -985, 666, 8, 9};

        std::deque<int> stl_range;
        ft::deque<int> ft_range;

        for (int i = 0; i < 5; i++)
        {
            stl_range.push_back(range_array[i]);
            ft_range.push_back(range_array[i]);
        }

        stl_range.erase(stl_range.begin(), stl_range.end() - 3);
        ft_range.erase(ft_range.begin(), ft_range.end() - 3);
        
        fs.open("./tester/deques_output/erase_range_begin", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printDequeAttributes(fs, stl_range, ft_range) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";    
        fs << "int range_array[] = {147, -985, 666, 8, 9};\n";
        fs << "ft::deque<int> ft_range;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    ft_range.push_back(range_array[i]);\n";
        fs << "ft_range.erase(ft_range.begin() + 2);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";    
        fs << "int range_array[] = {147, -985, 666, 8, 9};\n";
        fs << "std::deque<int> stl_range;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    stl_range.push_back(range_array[i]);\n";
        fs << "stl_range.erase(stl_range.begin() + 2);\n";
        fs.close();
    }

        /* Erase range end */
    {
        int range_array[] = {147, -985, 666, 8, 9};

        std::deque<int> stl_range;
        ft::deque<int> ft_range;

        for (int i = 0; i < 5; i++)
        {
            stl_range.push_back(range_array[i]);
            ft_range.push_back(range_array[i]);
        }

        stl_range.erase(stl_range.begin() + 2, stl_range.end());
        ft_range.erase(ft_range.begin() + 2, ft_range.end());
        
        fs.open("./tester/deques_output/erase_range_end", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printDequeAttributes(fs, stl_range, ft_range) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";    
        fs << "int range_array[] = {147, -985, 666, 8, 9};\n";
        fs << "ft::deque<int> ft_range;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    ft_range.push_back(range_array[i]);\n";
        fs << "ft_range.erase(ft_range.begin() + 2);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";    
        fs << "int range_array[] = {147, -985, 666, 8, 9};\n";
        fs << "std::deque<int> stl_range;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    stl_range.push_back(range_array[i]);\n";
        fs << "stl_range.erase(stl_range.begin() + 2);\n";
        fs.close();
    }

    /* Erase range  middle*/
    {
        int range_array[] = {147, -985, 666, 8, 9};

        std::deque<int> stl_range;
        ft::deque<int> ft_range;

        for (int i = 0; i < 5; i++)
        {
            stl_range.push_back(range_array[i]);
            ft_range.push_back(range_array[i]);
        }

        stl_range.erase(stl_range.begin() + 1, stl_range.end() - 2);
        ft_range.erase(ft_range.begin() + 1, ft_range.end() - 2);
        
        fs.open("./tester/deques_output/erase_range_middle", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printDequeAttributes(fs, stl_range, ft_range) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";    
        fs << "int range_array[] = {147, -985, 666, 8, 9};\n";
        fs << "ft::deque<int> ft_range;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    ft_range.push_back(range_array[i]);\n";
        fs << "ft_range.erase(ft_range.begin() + 2);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";    
        fs << "int range_array[] = {147, -985, 666, 8, 9};\n";
        fs << "std::deque<int> stl_range;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    stl_range.push_back(range_array[i]);\n";
        fs << "stl_range.erase(stl_range.begin() + 2);\n";
        fs.close();
    }

    /* Swap member */
    {
        int range_array_one[] = {1458, -98, 745, 62, 9};
        int range_array_two[] = {478, 87, -15, 44, 7};

        std::deque<int> stl_deque_one;
        std::deque<int> stl_deque_two;
        ft::deque<int> ft_deque_one;
        ft::deque<int> ft_deque_two;

        for (int i = 0; i < 5; i++)
        {
            stl_deque_one.push_back(range_array_one[i]);
            stl_deque_two.push_back(range_array_two[i]);
            ft_deque_one.push_back(range_array_one[i]);
            ft_deque_two.push_back(range_array_two[i]);
        }

        stl_deque_one.swap(stl_deque_two);
        ft_deque_one.swap(ft_deque_two);
        
        fs.open("./tester/deques_output/swap_member", std::fstream::in | std::fstream::out | std::fstream::trunc);

        std::cout << ((printDequeAttributes(fs, stl_deque_one, ft_deque_one)) ? "[OK]" : "[NOP]");
        std::cout << ((printDequeAttributes(fs, stl_deque_two, ft_deque_two)) ? "[OK]" : "[NOP]");
    
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {1458, -98, 745, 62, 9};\n";
        fs << "int range_array_two[] = {478, 87, -15, 44, 7};\n";
        fs << "ft::deque<int> ft_deque_one;\n";
        fs << "ft::deque<int> ft_deque_two;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "{\n";
        fs << "    ft_deque_one.push_back(range_array_one[i]);\n";
        fs << "    ft_deque_two.push_back(range_array_two[i]);\n";
        fs << "}\n";
        fs << "ft_deque_one.swap(ft_deque_two);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {1458, -98, 745, 62, 9};\n";
        fs << "int range_array_two[] = {478, 87, -15, 44, 7};\n";
        fs << "std::deque<int> stl_deque_one;\n";
        fs << "std::deque<int> stl_deque_two;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "{\n";
        fs << "    stl_deque_one.push_back(range_array_one[i]);\n";
        fs << "    stl_deque_two.push_back(range_array_two[i]);\n";
        fs << "}\n";
        fs << "stl_deque_one.swap(stl_deque_two);\n";
        fs.close();  
    }

    /* Clear */
    {
        std::deque<int> stl_clear(20);
        ft::deque<int> ft_clear(20);

        stl_clear.push_back(42);
        ft_clear.push_back(42);

        stl_clear.clear();
        ft_clear.clear();
        
        fs.open("./tester/deques_output/clear", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printDequeAttributes(fs, stl_clear, ft_clear) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::deque<int> ft_clear;\n";
        fs << "ft_clear.push_back(42);\n";
        fs << "ft_clear.clear();\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::deque<int> stl_clear;\n";
        fs << "stl_clear.push_back(42);\n";
        fs << "stl_clear.clear();\n";
        fs.close();
    }

    std::cout << "\n";
    std::cout << "Non member function overloads : ";

    /* RL = relation operator */

    /* RL '==' true */
    {
        int range_array[] = {1458, -98, 745, 62, 9};

        std::deque<int> stl_deque_one;
        std::deque<int> stl_deque_two;
        ft::deque<int> ft_deque_one;
        ft::deque<int> ft_deque_two;

        for (int i = 0; i < 5; i++)
        {
            stl_deque_one.push_back(range_array[i]);
            stl_deque_two.push_back(range_array[i]);
            ft_deque_one.push_back(range_array[i]);
            ft_deque_two.push_back(range_array[i]);
        }

        fs.open("./tester/deques_output/operator_equal_true", std::fstream::in | std::fstream::out | std::fstream::trunc);
        printDequeAttributes(fs, stl_deque_one, ft_deque_one);
        printDequeAttributes(fs, stl_deque_two, ft_deque_two);

        std::cout << ((printBoolResult(fs, (stl_deque_one == stl_deque_two), (ft_deque_one == ft_deque_two))) ? "[OK]" : "[NOP]");
    
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {1458, -98, 745, 62, 9};\n";
        fs << "ft::deque<int> ft_deque_one;\n";
        fs << "ft::deque<int> ft_deque_two;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "{\n";
        fs << "    ft_deque_one.push_back(range_array[i]);\n";
        fs << "    ft_deque_two.push_back(range_array[i]);\n";
        fs << "}\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {1458, -98, 745, 62, 9};\n";
        fs << "std::deque<int> stl_deque_one;\n";
        fs << "std::deque<int> stl_deque_two;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "{\n";
        fs << "    stl_deque_one.push_back(range_array[i]);\n";
        fs << "    stl_deque_two.push_back(range_array[i]);\n";
        fs << "}\n";
        fs.close();
    }

    /* RL '==' false */
    {
        int range_array_one[] = {1458, -98, 745, 62, 9};
        int range_array_two[] = {1458, 9, 458, 5, -88};

        std::deque<int> stl_deque_one;
        std::deque<int> stl_deque_two;
        ft::deque<int> ft_deque_one;
        ft::deque<int> ft_deque_two;

        for (int i = 0; i < 5; i++)
        {
            stl_deque_one.push_back(range_array_one[i]);
            stl_deque_two.push_back(range_array_two[i]);
            ft_deque_one.push_back(range_array_one[i]);
            ft_deque_two.push_back(range_array_two[i]);
        }

        fs.open("./tester/deques_output/operator_equal_false", std::fstream::in | std::fstream::out | std::fstream::trunc);

        printDequeAttributes(fs, stl_deque_one, ft_deque_one);
        printDequeAttributes(fs, stl_deque_two, ft_deque_two);

        std::cout << ((printBoolResult(fs, (stl_deque_one == stl_deque_two), (ft_deque_one == ft_deque_two))) ? "[OK]" : "[NOP]");
    
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {1458, -98, 745, 62, 9};\n";
        fs << "int range_array_two[] = {1458, 9, 458, 5, -88};\n";
        fs << "ft::deque<int> ft_deque_one;\n";
        fs << "ft::deque<int> ft_deque_two;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "{\n";
        fs << "    ft_deque_one.push_back(range_array_one[i]);\n";
        fs << "    ft_deque_two.push_back(range_array_two[i]);\n";
        fs << "}\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {1458, -98, 745, 62, 9};\n";
        fs << "int range_array_two[] = {1458, 9, 458, 5, -88};\n";
        fs << "std::deque<int> stl_deque_one;\n";
        fs << "std::deque<int> stl_deque_two;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "{\n";
        fs << "    stl_deque_one.push_back(range_array_one[i]);\n";
        fs << "    stl_deque_two.push_back(range_array_two[i]);\n";
        fs << "}\n";
        fs.close();
    }

    /* RL '!=' true */
    {
        int range_array_one[] = {144, 335, 5, 0, -54};
        int range_array_two[] = {1458, -98, 745, 62, 9};

        std::deque<int> stl_deque_one;
        std::deque<int> stl_deque_two;
        ft::deque<int> ft_deque_one;
        ft::deque<int> ft_deque_two;

        for (int i = 0; i < 5; i++)
        {
            stl_deque_one.push_back(range_array_one[i]);
            stl_deque_two.push_back(range_array_two[i]);
            ft_deque_one.push_back(range_array_one[i]);
            ft_deque_two.push_back(range_array_two[i]);
        }

        fs.open("./tester/deques_output/operator_not_equal_true", std::fstream::in | std::fstream::out | std::fstream::trunc);

        printDequeAttributes(fs, stl_deque_one, ft_deque_one);
        printDequeAttributes(fs, stl_deque_two, ft_deque_two);

        std::cout << ((printBoolResult(fs, (stl_deque_one != stl_deque_two), (ft_deque_one != ft_deque_two))) ? "[OK]" : "[NOP]");
    
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 335, 5, 0, -54};\n";
        fs << "int range_array_two[] = {1458, -98, 745, 62, 9};\n";
        fs << "ft::deque<int> ft_deque_one;\n";
        fs << "ft::deque<int> ft_deque_two;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "{\n";
        fs << "    ft_deque_one.push_back(range_array_one[i]);\n";
        fs << "    ft_deque_two.push_back(range_array_two[i]);\n";
        fs << "}\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 335, 5, 0, -54};\n";
        fs << "int range_array_two[] = {1458, -98, 745, 62, 9};\n";
        fs << "std::deque<int> stl_deque_one;\n";
        fs << "std::deque<int> stl_deque_two;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "{\n";
        fs << "    stl_deque_one.push_back(range_array_one[i]);\n";
        fs << "    stl_deque_two.push_back(range_array_two[i]);\n";
        fs << "}\n";
        fs.close();
    }

    /* RL '!=' false */
    {
        int range_array[] = {1458, -98, 745, 62, 9};

        std::deque<int> stl_deque_one;
        std::deque<int> stl_deque_two;
        ft::deque<int> ft_deque_one;
        ft::deque<int> ft_deque_two;

        for (int i = 0; i < 5; i++)
        {
            stl_deque_one.push_back(range_array[i]);
            stl_deque_two.push_back(range_array[i]);
            ft_deque_one.push_back(range_array[i]);
            ft_deque_two.push_back(range_array[i]);
        }

        fs.open("./tester/deques_output/operator_not_equal_false", std::fstream::in | std::fstream::out | std::fstream::trunc);
        printDequeAttributes(fs, stl_deque_one, ft_deque_one);
        printDequeAttributes(fs, stl_deque_two, ft_deque_two);

        std::cout << ((printBoolResult(fs, (stl_deque_one != stl_deque_two), (ft_deque_one != ft_deque_two))) ? "[OK]" : "[NOP]");
    
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {1458, -98, 745, 62, 9};\n";
        fs << "ft::deque<int> ft_deque_one;\n";
        fs << "ft::deque<int> ft_deque_two;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "{\n";
        fs << "    ft_deque_one.push_back(range_array[i]);\n";
        fs << "    ft_deque_two.push_back(range_array[i]);\n";
        fs << "}\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {1458, -98, 745, 62, 9};\n";
        fs << "std::deque<int> stl_deque_one;\n";
        fs << "std::deque<int> stl_deque_two;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "{\n";
        fs << "    stl_deque_one.push_back(range_array[i]);\n";
        fs << "    stl_deque_two.push_back(range_array[i]);\n";
        fs << "}\n";
        fs.close();
    }

    /* RL '<' true */
    {
        int range_array_one[] = {144, 335, 1, -98, 5};
        int range_array_two[] = {144, 335, 5, 0, -54};

        std::deque<int> stl_deque_one;
        std::deque<int> stl_deque_two;
        ft::deque<int> ft_deque_one;
        ft::deque<int> ft_deque_two;

        for (int i = 0; i < 5; i++)
        {
            stl_deque_one.push_back(range_array_one[i]);
            stl_deque_two.push_back(range_array_two[i]);
            ft_deque_one.push_back(range_array_one[i]);
            ft_deque_two.push_back(range_array_two[i]);
        }

        fs.open("./tester/deques_output/operator_inferior_true", std::fstream::in | std::fstream::out | std::fstream::trunc);

        printDequeAttributes(fs, stl_deque_one, ft_deque_one);
        printDequeAttributes(fs, stl_deque_two, ft_deque_two);

        std::cout << ((printBoolResult(fs, (stl_deque_one < stl_deque_two), (ft_deque_one < ft_deque_two))) ? "[OK]" : "[NOP]");
    
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 335, 1, -98, 5};\n";
        fs << "int range_array_two[] = {144, 335, 5, 0, -54};\n";
        fs << "ft::deque<int> ft_deque_one;\n";
        fs << "ft::deque<int> ft_deque_two;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "{\n";
        fs << "    ft_deque_one.push_back(range_array_one[i]);\n";
        fs << "    ft_deque_two.push_back(range_array_two[i]);\n";
        fs << "}\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 335, 1, -98, 5};\n";
        fs << "int range_array_two[] = {144, 335, 5, 0, -54};\n";
        fs << "std::deque<int> stl_deque_one;\n";
        fs << "std::deque<int> stl_deque_two;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "{\n";
        fs << "    stl_deque_one.push_back(range_array_one[i]);\n";
        fs << "    stl_deque_two.push_back(range_array_two[i]);\n";
        fs << "}\n";
        fs.close();
    }

    /* RL '<' false */
    {
        int range_array_one[] = {6780, 335, 1, -98, 5};
        int range_array_two[] = {144, 335, 5, 0, -54};

        std::deque<int> stl_deque_one;
        std::deque<int> stl_deque_two;
        ft::deque<int> ft_deque_one;
        ft::deque<int> ft_deque_two;

        for (int i = 0; i < 5; i++)
        {
            stl_deque_one.push_back(range_array_one[i]);
            stl_deque_two.push_back(range_array_two[i]);
            ft_deque_one.push_back(range_array_one[i]);
            ft_deque_two.push_back(range_array_two[i]);
        }

        fs.open("./tester/deques_output/operator_inferior_false", std::fstream::in | std::fstream::out | std::fstream::trunc);

        printDequeAttributes(fs, stl_deque_one, ft_deque_one);
        printDequeAttributes(fs, stl_deque_two, ft_deque_two);

        std::cout << ((printBoolResult(fs, (stl_deque_one < stl_deque_two), (ft_deque_one < ft_deque_two))) ? "[OK]" : "[NOP]");
    
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {6780, 335, 1, -98, 5};\n";
        fs << "int range_array_two[] = {144, 335, 5, 0, -54};\n";
        fs << "ft::deque<int> ft_deque_one;\n";
        fs << "ft::deque<int> ft_deque_two;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "{\n";
        fs << "    ft_deque_one.push_back(range_array_one[i]);\n";
        fs << "    ft_deque_two.push_back(range_array_two[i]);\n";
        fs << "}\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {6780, 335, 1, -98, 5};\n";
        fs << "int range_array_two[] = {144, 335, 5, 0, -54};\n";
        fs << "std::deque<int> stl_deque_one;\n";
        fs << "std::deque<int> stl_deque_two;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "{\n";
        fs << "    stl_deque_one.push_back(range_array_one[i]);\n";
        fs << "    stl_deque_two.push_back(range_array_two[i]);\n";
        fs << "}\n";
        fs.close();
    }

    /* RL '<=' true */
    {
        int range_array_one[] = {144, 335, 1, -98, 5};
        int range_array_two[] = {144, 335, 5, 0, -54};

        std::deque<int> stl_deque_one;
        std::deque<int> stl_deque_two;
        ft::deque<int> ft_deque_one;
        ft::deque<int> ft_deque_two;

        for (int i = 0; i < 5; i++)
        {
            stl_deque_one.push_back(range_array_one[i]);
            stl_deque_two.push_back(range_array_two[i]);
            ft_deque_one.push_back(range_array_one[i]);
            ft_deque_two.push_back(range_array_two[i]);
        }

        fs.open("./tester/deques_output/operator_inf_or_equal_true", std::fstream::in | std::fstream::out | std::fstream::trunc);

        printDequeAttributes(fs, stl_deque_one, ft_deque_one);
        printDequeAttributes(fs, stl_deque_two, ft_deque_two);

        std::cout << ((printBoolResult(fs, (stl_deque_one <= stl_deque_two), (ft_deque_one <= ft_deque_two))) ? "[OK]" : "[NOP]");
    
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 335, 1, -98, 5};\n";
        fs << "int range_array_two[] = {144, 335, 5, 0, -54};\n";
        fs << "ft::deque<int> ft_deque_one;\n";
        fs << "ft::deque<int> ft_deque_two;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "{\n";
        fs << "    ft_deque_one.push_back(range_array_one[i]);\n";
        fs << "    ft_deque_two.push_back(range_array_two[i]);\n";
        fs << "}\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 335, 1, -98, 5};\n";
        fs << "int range_array_two[] = {144, 335, 5, 0, -54};\n";
        fs << "std::deque<int> stl_deque_one;\n";
        fs << "std::deque<int> stl_deque_two;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "{\n";
        fs << "    stl_deque_one.push_back(range_array_one[i]);\n";
        fs << "    stl_deque_two.push_back(range_array_two[i]);\n";
        fs << "}\n";
        fs.close();
    }

    /* RL '<=' true equal */
    {
        int range_array_one[] = {144, 335, 5, 0, -54};
        int range_array_two[] = {144, 335, 5, 0, -54};

        std::deque<int> stl_deque_one;
        std::deque<int> stl_deque_two;
        ft::deque<int> ft_deque_one;
        ft::deque<int> ft_deque_two;

        for (int i = 0; i < 5; i++)
        {
            stl_deque_one.push_back(range_array_one[i]);
            stl_deque_two.push_back(range_array_two[i]);
            ft_deque_one.push_back(range_array_one[i]);
            ft_deque_two.push_back(range_array_two[i]);
        }

        fs.open("./tester/deques_output/operator_inf_or_equal_true_equal", std::fstream::in | std::fstream::out | std::fstream::trunc);

        printDequeAttributes(fs, stl_deque_one, ft_deque_one);
        printDequeAttributes(fs, stl_deque_two, ft_deque_two);

        std::cout << ((printBoolResult(fs, (stl_deque_one <= stl_deque_two), (ft_deque_one <= ft_deque_two))) ? "[OK]" : "[NOP]");
    
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 335, 5, 0, -54};\n";
        fs << "int range_array_two[] = {144, 335, 5, 0, -54};\n";
        fs << "ft::deque<int> ft_deque_one;\n";
        fs << "ft::deque<int> ft_deque_two;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "{\n";
        fs << "    ft_deque_one.push_back(range_array_one[i]);\n";
        fs << "    ft_deque_two.push_back(range_array_two[i]);\n";
        fs << "}\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 335, 5, 0, -54};\n";
        fs << "int range_array_two[] = {144, 335, 5, 0, -54};\n";
        fs << "std::deque<int> stl_deque_one;\n";
        fs << "std::deque<int> stl_deque_two;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "{\n";
        fs << "    stl_deque_one.push_back(range_array_one[i]);\n";
        fs << "    stl_deque_two.push_back(range_array_two[i]);\n";
        fs << "}\n";
        fs.close();
    }

    /* RL '<=' false */
    {
        int range_array_one[] = {144, 9999, 5, 0, -54};
        int range_array_two[] = {144, 335, 5, 0, -54};

        std::deque<int> stl_deque_one;
        std::deque<int> stl_deque_two;
        ft::deque<int> ft_deque_one;
        ft::deque<int> ft_deque_two;

        for (int i = 0; i < 5; i++)
        {
            stl_deque_one.push_back(range_array_one[i]);
            stl_deque_two.push_back(range_array_two[i]);
            ft_deque_one.push_back(range_array_one[i]);
            ft_deque_two.push_back(range_array_two[i]);
        }

        fs.open("./tester/deques_output/operator_inf_or_equal_false", std::fstream::in | std::fstream::out | std::fstream::trunc);

        printDequeAttributes(fs, stl_deque_one, ft_deque_one);
        printDequeAttributes(fs, stl_deque_two, ft_deque_two);

        std::cout << ((printBoolResult(fs, (stl_deque_one <= stl_deque_two), (ft_deque_one <= ft_deque_two))) ? "[OK]" : "[NOP]");
    
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 9999, 5, 0, -54};\n";
        fs << "int range_array_two[] = {144, 335, 5, 0, -54};\n";
        fs << "ft::deque<int> ft_deque_one;\n";
        fs << "ft::deque<int> ft_deque_two;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "{\n";
        fs << "    ft_deque_one.push_back(range_array_one[i]);\n";
        fs << "    ft_deque_two.push_back(range_array_two[i]);\n";
        fs << "}\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 9999, 5, 0, -54};\n";
        fs << "int range_array_two[] = {144, 335, 5, 0, -54};\n";
        fs << "std::deque<int> stl_deque_one;\n";
        fs << "std::deque<int> stl_deque_two;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "{\n";
        fs << "    stl_deque_one.push_back(range_array_one[i]);\n";
        fs << "    stl_deque_two.push_back(range_array_two[i]);\n";
        fs << "}\n";
        fs.close();
    }

    /* RL '>' true */
    {
        int range_array_one[] = {144, 9999, 5, 0, -54};
        int range_array_two[] = {144, 335, 5, 0, -54};

        std::deque<int> stl_deque_one;
        std::deque<int> stl_deque_two;
        ft::deque<int> ft_deque_one;
        ft::deque<int> ft_deque_two;

        for (int i = 0; i < 5; i++)
        {
            stl_deque_one.push_back(range_array_one[i]);
            stl_deque_two.push_back(range_array_two[i]);
            ft_deque_one.push_back(range_array_one[i]);
            ft_deque_two.push_back(range_array_two[i]);
        }

        fs.open("./tester/deques_output/operator_superior_true", std::fstream::in | std::fstream::out | std::fstream::trunc);

        printDequeAttributes(fs, stl_deque_one, ft_deque_one);
        printDequeAttributes(fs, stl_deque_two, ft_deque_two);

        std::cout << ((printBoolResult(fs, (stl_deque_one > stl_deque_two), (ft_deque_one > ft_deque_two))) ? "[OK]" : "[NOP]");
    
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 9999, 5, 0, -54};\n";
        fs << "int range_array_two[] = {144, 335, 5, 0, -54};\n";
        fs << "ft::deque<int> ft_deque_one;\n";
        fs << "ft::deque<int> ft_deque_two;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "{\n";
        fs << "    ft_deque_one.push_back(range_array_one[i]);\n";
        fs << "    ft_deque_two.push_back(range_array_two[i]);\n";
        fs << "}\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 9999, 5, 0, -54};\n";
        fs << "int range_array_two[] = {144, 335, 5, 0, -54};\n";
        fs << "std::deque<int> stl_deque_one;\n";
        fs << "std::deque<int> stl_deque_two;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "{\n";
        fs << "    stl_deque_one.push_back(range_array_one[i]);\n";
        fs << "    stl_deque_two.push_back(range_array_two[i]);\n";
        fs << "}\n";
        fs.close();
    }

    /* RL '>' false */
    {
        int range_array_one[] = {144, 335, 5, 0, -54};
        int range_array_two[] = {144, 335, 77, 0, -54};

        std::deque<int> stl_deque_one;
        std::deque<int> stl_deque_two;
        ft::deque<int> ft_deque_one;
        ft::deque<int> ft_deque_two;

        for (int i = 0; i < 5; i++)
        {
            stl_deque_one.push_back(range_array_one[i]);
            stl_deque_two.push_back(range_array_two[i]);
            ft_deque_one.push_back(range_array_one[i]);
            ft_deque_two.push_back(range_array_two[i]);
        }

        fs.open("./tester/deques_output/operator_superior_false", std::fstream::in | std::fstream::out | std::fstream::trunc);

        printDequeAttributes(fs, stl_deque_one, ft_deque_one);
        printDequeAttributes(fs, stl_deque_two, ft_deque_two);

        std::cout << ((printBoolResult(fs, (stl_deque_one > stl_deque_two), (ft_deque_one > ft_deque_two))) ? "[OK]" : "[NOP]");
    
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 335, 5, 0, -54};\n";
        fs << "int range_array_two[] = {144, 335, 77, 0, -54};\n";
        fs << "ft::deque<int> ft_deque_one;\n";
        fs << "ft::deque<int> ft_deque_two;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "{\n";
        fs << "    ft_deque_one.push_back(range_array_one[i]);\n";
        fs << "    ft_deque_two.push_back(range_array_two[i]);\n";
        fs << "}\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 335, 5, 0, -54};\n";
        fs << "int range_array_two[] = {144, 335, 77, 0, -54};\n";
        fs << "std::deque<int> stl_deque_one;\n";
        fs << "std::deque<int> stl_deque_two;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "{\n";
        fs << "    stl_deque_one.push_back(range_array_one[i]);\n";
        fs << "    stl_deque_two.push_back(range_array_two[i]);\n";
        fs << "}\n";
        fs.close();
    }

    /* RL '>=' true */
    {
        int range_array_one[] = {144, 335, 78, 0, -54};
        int range_array_two[] = {144, 335, 77, 0, -54};

        std::deque<int> stl_deque_one;
        std::deque<int> stl_deque_two;
        ft::deque<int> ft_deque_one;
        ft::deque<int> ft_deque_two;

        for (int i = 0; i < 5; i++)
        {
            stl_deque_one.push_back(range_array_one[i]);
            stl_deque_two.push_back(range_array_two[i]);
            ft_deque_one.push_back(range_array_one[i]);
            ft_deque_two.push_back(range_array_two[i]);
        }

        fs.open("./tester/deques_output/operator_sup_or_equal_true", std::fstream::in | std::fstream::out | std::fstream::trunc);

        printDequeAttributes(fs, stl_deque_one, ft_deque_one);
        printDequeAttributes(fs, stl_deque_two, ft_deque_two);

        std::cout << ((printBoolResult(fs, (stl_deque_one > stl_deque_two), (ft_deque_one > ft_deque_two))) ? "[OK]" : "[NOP]");
    
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 335, 78, 0, -54};\n";
        fs << "int range_array_two[] = {144, 335, 77, 0, -54};\n";
        fs << "ft::deque<int> ft_deque_one;\n";
        fs << "ft::deque<int> ft_deque_two;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "{\n";
        fs << "    ft_deque_one.push_back(range_array_one[i]);\n";
        fs << "    ft_deque_two.push_back(range_array_two[i]);\n";
        fs << "}\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 335, 78, 0, -54};\n";
        fs << "int range_array_two[] = {144, 335, 77, 0, -54};\n";
        fs << "std::deque<int> stl_deque_one;\n";
        fs << "std::deque<int> stl_deque_two;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "{\n";
        fs << "    stl_deque_one.push_back(range_array_one[i]);\n";
        fs << "    stl_deque_two.push_back(range_array_two[i]);\n";
        fs << "}\n";
        fs.close();
    }

    /* RL '>=' false */
    {
        int range_array_one[] = {144, 335, 5, 0, -54};
        int range_array_two[] = {144, 335, 77, 0, -54};

        std::deque<int> stl_deque_one;
        std::deque<int> stl_deque_two;
        ft::deque<int> ft_deque_one;
        ft::deque<int> ft_deque_two;

        for (int i = 0; i < 5; i++)
        {
            stl_deque_one.push_back(range_array_one[i]);
            stl_deque_two.push_back(range_array_two[i]);
            ft_deque_one.push_back(range_array_one[i]);
            ft_deque_two.push_back(range_array_two[i]);
        }

        fs.open("./tester/deques_output/operator_sup_or_equal_false", std::fstream::in | std::fstream::out | std::fstream::trunc);

        printDequeAttributes(fs, stl_deque_one, ft_deque_one);
        printDequeAttributes(fs, stl_deque_two, ft_deque_two);

        std::cout << ((printBoolResult(fs, (stl_deque_one > stl_deque_two), (ft_deque_one > ft_deque_two))) ? "[OK]" : "[NOP]");
    
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 335, 5, 0, -54};\n";
        fs << "int range_array_two[] = {144, 335, 77, 0, -54};\n";
        fs << "ft::deque<int> ft_deque_one;\n";
        fs << "ft::deque<int> ft_deque_two;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "{\n";
        fs << "    ft_deque_one.push_back(range_array_one[i]);\n";
        fs << "    ft_deque_two.push_back(range_array_two[i]);\n";
        fs << "}\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 335, 5, 0, -54};\n";
        fs << "int range_array_two[] = {144, 335, 77, 0, -54};\n";
        fs << "std::deque<int> stl_deque_one;\n";
        fs << "std::deque<int> stl_deque_two;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "{\n";
        fs << "    stl_deque_one.push_back(range_array_one[i]);\n";
        fs << "    stl_deque_two.push_back(range_array_two[i]);\n";
        fs << "}\n";
        fs.close();
    }

    /* Swap non member */
    {
        int range_array_one[] = {144, 335, 5, 0, -54};
        int range_array_two[] = {47, -98, 58, 611, -4};

        std::deque<int> stl_deque_one;
        std::deque<int> stl_deque_two;
        ft::deque<int> ft_deque_one;
        ft::deque<int> ft_deque_two;

        for (int i = 0; i < 5; i++)
        {
            stl_deque_one.push_back(range_array_one[i]);
            stl_deque_two.push_back(range_array_two[i]);
            ft_deque_one.push_back(range_array_one[i]);
            ft_deque_two.push_back(range_array_two[i]);
        }

        std::swap(stl_deque_one, stl_deque_two);
        ft::swap(ft_deque_one, ft_deque_two);
        
        fs.open("./tester/deques_output/swap_no_member", std::fstream::in | std::fstream::out | std::fstream::trunc);

        std::cout << ((printDequeAttributes(fs, stl_deque_one, ft_deque_one)) ? "[OK]" : "[NOP]");
        std::cout << ((printDequeAttributes(fs, stl_deque_two, ft_deque_two)) ? "[OK]" : "[NOP]");
    
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 335, 5, 0, -54};\n";
        fs << "int range_array_two[] = {47, -98, 58, 611, -4};\n";
        fs << "ft::deque<int> ft_deque_one;\n";
        fs << "ft::deque<int> ft_deque_two;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "{\n";
        fs << "    ft_deque_one.push_back(range_array_one[i]);\n";
        fs << "    ft_deque_two.push_back(range_array_two[i]);\n";
        fs << "}\n";
        fs << "ft::swap(ft_deque_one, ft_deque_two);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 335, 5, 0, -54};\n";
        fs << "int range_array_two[] = {47, -98, 58, 611, -4};\n";
        fs << "std::deque<int> stl_deque_one;\n";
        fs << "std::deque<int> stl_deque_two;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "{\n";
        fs << "    stl_deque_one.push_back(range_array_one[i]);\n";
        fs << "    stl_deque_two.push_back(range_array_two[i]);\n";
        fs << "}\n";
        fs << "std::swap(stl_deque_one, stl_deque_two);\n";
        fs.close();  
    }

    std::cout << std::endl;
}