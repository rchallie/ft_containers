/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester_vector.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchallie <rchallie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 17:54:42 by rchallie          #+#    #+#             */
/*   Updated: 2020/12/08 19:14:23 by rchallie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <vector>
# include <fstream>
# include <string>

# include "../containers/vector.hpp"
# include "../containers/utils/random_access_iterator.hpp"
# include "tester.hpp"

template <class T>
std::string equalContent(
    const std::vector<T> & stl_vector,
    const ft::vector<T> & ft_vector
)
{
    typename ft::vector<T>::const_iterator ft_it;
    typename std::vector<T>::const_iterator stl_it;
    if (ft_vector.size() != stl_vector.size())
        return ("✘");
    stl_it = stl_vector.begin();
    for(ft_it = ft_vector.begin(); ft_it != ft_vector.end(); ft_it++)
    {
        if (*ft_it != *stl_it)
            return ("✘");
        stl_it++;
    }
    return ("✔");
}

template <class T>
bool printVectorAttributes(
    std::fstream& fs,
    std::vector<T>& stl_vector,
    ft::vector<T>& ft_vector
)
{
    /* STL Values */
    std::string stl_empty = ((stl_vector.empty() == 1) ? "true" : "false");
    size_t stl_size = stl_vector.size();
    size_t stl_max_size = stl_vector.max_size();
    size_t stl_capacity = stl_vector.capacity();

    /* FT Values */
    std::string ft_empty = ((ft_vector.empty() == 1) ? "true" : "false");
    size_t ft_size = ft_vector.size();
    size_t ft_max_size = ft_vector.max_size();
    size_t ft_capacity = ft_vector.capacity();

    /* FT Result compare values */
    bool empty = equalbool(ft_empty, stl_empty);
    bool size = equalbool(ft_size, stl_size);
    bool max_size = equalbool(ft_max_size, stl_max_size);
    bool capacity = equalbool(ft_capacity, stl_capacity);
    std::string content = equalContent(stl_vector, ft_vector);
    
    fs << "\n══════════════════════════════════════════════════════════════\n";
    fs << "Vectors attributes : \n";
    fs << "STL : \n";
    fs << "Empty       : " << stl_empty  << std::endl;
    fs << "Size        : " << stl_size  << std::endl;
    fs << "Max size    : " << stl_max_size  << std::endl;
    fs << "Capacity    : " << stl_capacity  << std::endl;
    fs << "Content     : [";
    
    typename std::vector<T>::const_iterator stl_it;
    for (stl_it = stl_vector.begin();  stl_it != stl_vector.end(); stl_it++)
    {
        fs << *stl_it;
        if (stl_it + 1 != stl_vector.end())
            fs << ", ";
    }
    fs << "]\n";

    fs << std::endl;

    fs << "FT : \n";
    fs << "Empty    [" << equal(ft_empty, stl_empty) << "]: " << ft_empty  << std::endl;
    fs << "Size     [" << equal(ft_size, stl_size) << "]: " << ft_size  << std::endl;
    fs << "Max size [" << equal(ft_max_size, stl_max_size) << "]: " << ft_max_size  << std::endl;
    fs << "Capacity [" << equal(ft_capacity, stl_capacity) << "]: " << ft_capacity  << std::endl;

    fs << "Content  [" << content << "]: [";

    typename ft::vector<T>::const_iterator ft_it;
    for(ft_it = ft_vector.begin(); ft_it != ft_vector.end(); ft_it++)
    {
        fs << *ft_it;
        if (ft_it + 1 != ft_vector.end())
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
    else if (capacity == false)
        return (false);
    else if (content == "✘")
        return (false);
    return (true);
}

void test_vector()
{
    std::cout << UNDERLINE << "VECTORS :\n" << NORMAL ;

    mkdir("./tester/vectors_output", 0777);
    
    std::fstream fs;

    /* Constructors */
    std::cout << "Constructors : ";

    /* Default constructor */
    {
        std::vector<int> stl_default_vector;
        ft::vector<int> ft_default_vector;

        fs.open("./tester/vectors_output/constructor_default", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printVectorAttributes(fs, stl_default_vector, ft_default_vector) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::vector<int> ft_default_vector;\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::vector<int> stl_default_vector;\n";
        fs.close();
    }

    /* Default constructor pointer */
    {
        std::vector<int> *stl_pointer_default_vector = new std::vector<int>;
        ft::vector<int> *ft_pointer_default_vector = new ft::vector<int>;

        fs.open("./tester/vectors_output/constructor_default_pointer", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printVectorAttributes(fs, *stl_pointer_default_vector, *ft_pointer_default_vector) == true) ? "[OK]" : "[NOP]");
        
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::vector<int> *ft_pointer_default_vector = new ft::vector<int>;\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::vector<int> *stl_pointer_default_vector = new std::vector<int>;\n";
        fs.close();

        delete stl_pointer_default_vector;
        delete ft_pointer_default_vector;
    }

    /* Fill constructor */
    {
        std::vector<int> stl_fill_vector(0);
        ft::vector<int> ft_fill_vector(0);

        fs.open("./tester/vectors_output/constructor_fill_empty", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printVectorAttributes(fs, stl_fill_vector, ft_fill_vector) == true) ? "[OK]" : "[NOP]");
        
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::vector<int> ft_fill_vector(0);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::vector<int> stl_fill_vector(0);\n";
        fs.close();
    }

    /* Fill constructor sized */
    {
        std::vector<int> stl_fill_vector_sized(19);
        ft::vector<int> ft_fill_vector_sized(19);

        fs.open("./tester/vectors_output/constructor_fill_sized", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printVectorAttributes(fs, stl_fill_vector_sized, ft_fill_vector_sized) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::vector<int> ft_fill_vector_sized(19);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::vector<int> stl_fill_vector_sized(19);\n";
        fs.close();
    }

    /* Fill constructor sized & valued */
    {
        std::vector<int> stl_fill_vector_sized(19, 42);
        ft::vector<int> ft_fill_vector_sized(19, 42);

        fs.open("./tester/vectors_output/constructor_fill_sized_valued", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printVectorAttributes(fs, stl_fill_vector_sized, ft_fill_vector_sized) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::vector<int> ft_fill_vector_sized(19, 42);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::vector<int> stl_fill_vector_sized(19, 42);\n";
        fs.close();
    }

    /* Range constructor */
    {
        int range_array[] = { 45, 87846, 12, 965, 5 };

        std::vector<int>::iterator stl_iterator(&(range_array[0]));
        ft::vector<int>::iterator ft_iterator(&(range_array[0]));

        fs.open("./tester/vectors_output/constructor_range", std::fstream::in | std::fstream::out | std::fstream::trunc);

        std::vector<int> stl_range_vector(stl_iterator, stl_iterator + 5);
        ft::vector<int> ft_range_vector(ft_iterator, ft_iterator + 5);

        std::cout << ((printVectorAttributes(fs, stl_range_vector, ft_range_vector) == true) ? "[OK]" : "[NOP]");
        
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = { 45, 87846, 12, 965, 5 };\n";
        fs << "ft::vector<int>::iterator ft_iterator(&(range_array[0]));\n";
        fs << "ft::vector<int> ft_range_vector(ft_iterator, ft_iterator + 5);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = { 45, 87846, 12, 965, 5 };\n";
        fs << "std::vector<int>::iterator stl_iterator(&(range_array[0]));\n";
        fs << "std::vector<int> stl_range_vector(stl_iterator, stl_iterator + 5);\n";
        fs.close();
    }

    /* Copy constructor */
    {
        int range_array[] = { -89, 561, 874, 7777 , 987, -6 };
        
        std::vector<int>::iterator stl_iterator(&(range_array[0]));
        ft::vector<int>::iterator ft_iterator(&(range_array[0]));

        std::vector<int> stl_range_vector(stl_iterator, stl_iterator + 6);
        ft::vector<int> ft_range_vector(ft_iterator, ft_iterator + 6);

        fs.open("./tester/vectors_output/constructor_copy", std::fstream::in | std::fstream::out | std::fstream::trunc);

        std::vector<int> stl_copy_vector(stl_range_vector);
        ft::vector<int> ft_copy_vector(ft_range_vector);

        std::cout << ((printVectorAttributes(fs, stl_copy_vector, ft_copy_vector) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = { -89, 561, 874, 7777 , 987, -6 };\n";
        fs << "ft::vector<int>::iterator ft_iterator(&(range_array[0]));\n";
        fs << "ft::vector<int> ft_range_vector(ft_iterator, ft_iterator + 6);\n";
        fs << "ft::vector<int> ft_copy_vector(ft_range_vector);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = { -89, 561, 874, 7777 , 987, -6 };\n";
        fs << "std::vector<int>::iterator stl_iterator(&(range_array[0]));\n";
        fs << "std::vector<int> stl_range_vector(stl_iterator, stl_iterator + 6);\n";
        fs << "std::vector<int> stl_copy_vector(stl_range_vector);\n";
        fs.close();
    }

    std::cout << "\n";
    std::cout << "Assign : ";

    /* Assign operator */
    {
        int range_array[] = { 74, 569, -8822, 8515, 5 };

        std::vector<int>::iterator stl_iterator(&(range_array[0]));
        ft::vector<int>::iterator ft_iterator(&(range_array[0]));

        std::vector<int> stl_range_vector(stl_iterator, stl_iterator + 5);
        ft::vector<int> ft_range_vector(ft_iterator, ft_iterator + 5);

        fs.open("./tester/vectors_output/operator_assign", std::fstream::in | std::fstream::out | std::fstream::trunc);

        std::vector<int> stl_assign_vector = stl_range_vector;
        ft::vector<int> ft_assign_vector = ft_range_vector;

        std::cout << ((printVectorAttributes(fs, stl_assign_vector, ft_assign_vector) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = { 74, 569, -8822, 8515, 5 };\n";
        fs << "ft::vector<int>::iterator ft_iterator(&(range_array[0]));\n";
        fs << "ft::vector<int> ft_range_vector(ft_iterator, ft_iterator + 5);\n";
        fs << "ft::vector<int> ft_assign_vector = ft_range_vector;\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = { 74, 569, -8822, 8515, 5 };\n";
        fs << "std::vector<int>::iterator stl_iterator(&(range_array[0]));\n";
        fs << "std::vector<int> stl_range_vector(stl_iterator, stl_iterator + 5);\n";
        fs << "std::vector<int> stl_assign_vector = stl_range_vector;\n";
        fs.close();
    }

    std::cout << "\n";
    std::cout << "Iterator : ";

    /* Iterator begin() */
    {
        int range_array[] = { 87, 92, -5, 8984, 96 };

        std::vector<int>::iterator stl_iterator(&(range_array[0]));
        ft::vector<int>::iterator ft_iterator(&(range_array[0]));

        std::vector<int> stl_range_vector(stl_iterator, stl_iterator + 5);
        ft::vector<int> ft_range_vector(ft_iterator, ft_iterator + 5);
    
        fs.open("./tester/vectors_output/iterator_begin", std::fstream::in | std::fstream::out | std::fstream::trunc);
        
        int from_stl = *(stl_range_vector.begin());
        int from_ft = *(ft_range_vector.begin());

        std::cout << ((printSingleValue(fs, from_stl, from_ft) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = { 87, 92, -5, 8984, 96 };\n";
        fs << "ft::vector<int>::iterator ft_iterator(&(range_array[0]));\n";
        fs << "ft::vector<int> ft_range_vector(ft_iterator, ft_iterator + 5);\n";
        fs << "int from_ft = *(ft_range_vector.begin());\n";
        fs << "    ^^^^^^^\n";
        fs << "    Compared value";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = { 87, 92, -5, 8984, 96 };\n";
        fs << "std::vector<int>::iterator stl_iterator(&(range_array[0]));\n";
        fs << "std::vector<int> stl_range_vector(stl_iterator, stl_iterator + 5);\n";
        fs << "int from_stl = *(stl_range_vector.begin());\n";
        fs << "    ^^^^^^^^\n";
        fs << "    Compared value";
        fs.close();
    }

    /* Const iterator begin() */
    {
        int range_array[] = { 87, 92, -5, 8984, 96 };

        std::vector<int>::const_iterator stl_iterator(&(range_array[0]));
        ft::vector<int>::const_iterator ft_iterator(&(range_array[0]));

        std::vector<int> stl_range_vector(stl_iterator, stl_iterator + 5);
        ft::vector<int> ft_range_vector(ft_iterator, ft_iterator + 5);
    
        fs.open("./tester/vectors_output/iterator_const_begin", std::fstream::in | std::fstream::out | std::fstream::trunc);
        
        std::vector<int>::const_iterator stl_const_it = stl_range_vector.begin();
        ft::vector<int>::const_iterator ft_const_it = ft_range_vector.begin();
        const int from_stl = *(stl_const_it);
        const int from_ft = *(ft_const_it);

        std::cout << ((printSingleValue(fs, from_stl, from_ft) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = { 87, 92, -5, 8984, 96 };\n";
        fs << "ft::vector<int>::const_iterator ft_iterator(&(range_array[0]));\n";
        fs << "ft::vector<int> ft_range_vector(ft_iterator, ft_iterator + 5);\n";
        fs << "ft::vector<int>::const_iterator ft_const_it = ft_range_vector.begin();\n";
        fs << "int from_ft = *(ft_const_it);\n";
        fs << "    ^^^^^^^\n";
        fs << "    Compared value";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = { 87, 92, -5, 8984, 96 };\n";
        fs << "std::vector<int>::const_iterator stl_iterator(&(range_array[0]));\n";
        fs << "std::vector<int> stl_range_vector(stl_iterator, stl_iterator + 5);\n";
        fs << "std::vector<int>::const_iterator stl_const_it = stl_range_vector.begin();\n";
        fs << "int from_stl = *(stl_const_it);\n";
        fs << "    ^^^^^^^^\n";
        fs << "    Compared value";
        fs.close();
    }

    /* Iterator end() */
    {
        int range_array[] = { 48, 967, 52, -45, -9, 956551, 44};

        std::vector<int>::iterator stl_iterator(&(range_array[0]));
        ft::vector<int>::iterator ft_iterator(&(range_array[0]));

        std::vector<int> stl_range_vector(stl_iterator, stl_iterator + 7);
        ft::vector<int> ft_range_vector(ft_iterator, ft_iterator + 7);
    
        fs.open("./tester/vectors_output/iterator_end", std::fstream::in | std::fstream::out | std::fstream::trunc);
        
        int from_stl = *(stl_range_vector.end() - 1);
        int from_ft = *(ft_range_vector.end() - 1);

        std::cout << ((printSingleValue(fs, from_stl, from_ft) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = { 48, 967, 52, -45, -9, 956551, 44};\n";
        fs << "ft::vector<int>::iterator ft_iterator(&(range_array[0]));\n";
        fs << "ft::vector<int> ft_range_vector(ft_iterator, ft_iterator + 7);\n";
        fs << "int from_ft = *(ft_range_vector.end() - 1);\n";
        fs << "    ^^^^^^^\n";
        fs << "    Compared value";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = { 48, 967, 52, -45, -9, 956551, 44};\n";
        fs << "std::vector<int>::iterator stl_iterator(&(range_array[0]));\n";
        fs << "std::vector<int> stl_range_vector(stl_iterator, stl_iterator + 7);\n";
        fs << "int from_stl = *(stl_range_vector.end() - 1);\n";
        fs << "    ^^^^^^^^\n";
        fs << "    Compared value";
        fs.close();
    }

    /* Const iterator end() */
    {
        int range_array[] = { 95, 89, -6121, 48, 5 };

        std::vector<int>::const_iterator stl_iterator(&(range_array[0]));
        ft::vector<int>::const_iterator ft_iterator(&(range_array[0]));

        std::vector<int> stl_range_vector(stl_iterator, stl_iterator + 5);
        ft::vector<int> ft_range_vector(ft_iterator, ft_iterator + 5);
    
        fs.open("./tester/vectors_output/iterator_const_end", std::fstream::in | std::fstream::out | std::fstream::trunc);
        
        std::vector<int>::const_iterator stl_const_it = stl_range_vector.end() - 1;
        ft::vector<int>::const_iterator ft_const_it = ft_range_vector.end() - 1;
        const int from_stl = *(stl_const_it);
        const int from_ft = *(ft_const_it);

        std::cout << ((printSingleValue(fs, from_stl, from_ft) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = { 95, 89, -6121, 48, 5 };\n";
        fs << "ft::vector<int>::const_iterator ft_iterator(&(range_array[0]));\n";
        fs << "ft::vector<int> ft_range_vector(ft_iterator, ft_iterator + 5);\n";
        fs << "std::vector<int>::const_iterator stl_const_it = stl_range_vector.end() - 1;\n";
        fs << "int from_ft = *(ft_const_it);\n";
        fs << "    ^^^^^^^\n";
        fs << "    Compared value";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = { 95, 89, -6121, 48, 5 };\n";
        fs << "std::vector<int>::const_iterator stl_iterator(&(range_array[0]));\n";
        fs << "std::vector<int> stl_range_vector(stl_iterator, stl_iterator + 5);\n";
        fs << "ft::vector<int>::const_iterator ft_const_it = ft_range_vector.end() - 1;\n";
        fs << "int from_stl = *(stl_const_it);\n";
        fs << "    ^^^^^^^^\n";
        fs << "    Compared value";
        fs.close();
    }

    /* Iterator rbegin() */
    {
        int range_array[] = {250, -1200, -98657, 2, 34};

        std::vector<int>::iterator stl_iterator(&(range_array[0]));
        ft::vector<int>::iterator ft_iterator(&(range_array[0]));

        std::vector<int> stl_range_vector(stl_iterator, stl_iterator + 5);
        ft::vector<int> ft_range_vector(ft_iterator, ft_iterator + 5);
    
        fs.open("./tester/vectors_output/iterator_reverse_begin", std::fstream::in | std::fstream::out | std::fstream::trunc);
        
        int from_stl = *(stl_range_vector.rbegin());
        int from_ft = *(ft_range_vector.rbegin());

        std::cout << ((printSingleValue(fs, from_stl, from_ft) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {250, -1200, -98657, 2, 34};\n";
        fs << "ft::vector<int>::iterator ft_iterator(&(range_array[0]));\n";
        fs << "ft::vector<int> ft_range_vector(ft_iterator, ft_iterator + 5);\n";
        fs << "int from_ft = *(ft_range_vector.rbegin());\n";
        fs << "    ^^^^^^^\n";
        fs << "    Compared value";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {250, -1200, -98657, 2, 34};\n";
        fs << "std::vector<int>::iterator stl_iterator(&(range_array[0]));\n";
        fs << "std::vector<int> stl_range_vector(stl_iterator, stl_iterator + 5);\n";
        fs << "int from_stl = *(stl_range_vector.rbegin());\n";
        fs << "    ^^^^^^^^\n";
        fs << "    Compared value";
        fs.close();
    }

    /* Const iterator rbegin() */
    {
        int range_array[] = { 958, -561, 54, 789, -8};

        std::vector<int>::const_iterator stl_iterator(&(range_array[0]));
        ft::vector<int>::const_iterator ft_iterator(&(range_array[0]));

        std::vector<int> stl_range_vector(stl_iterator, stl_iterator + 5);
        ft::vector<int> ft_range_vector(ft_iterator, ft_iterator + 5);
    
        fs.open("./tester/vectors_output/iterator_const_reverse_begin", std::fstream::in | std::fstream::out | std::fstream::trunc);
        
        std::vector<int>::const_reverse_iterator stl_const_it = stl_range_vector.rbegin();
        ft::vector<int>::const_reverse_iterator ft_const_it = ft_range_vector.rbegin();
        const int from_stl = *(stl_const_it);
        const int from_ft = *(ft_const_it);

        std::cout << ((printSingleValue(fs, from_stl, from_ft) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = { 958, -561, 54, 789, -8};\n";
        fs << "ft::vector<int>::const_iterator ft_iterator(&(range_array[0]));\n";
        fs << "ft::vector<int> ft_range_vector(ft_iterator, ft_iterator + 5);\n";
        fs << "ft::vector<int>::const_reverse_iterator ft_const_it = ft_range_vector.rbegin();\n";
        fs << "int from_ft = *(ft_const_it);\n";
        fs << "    ^^^^^^^\n";
        fs << "    Compared value";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = { 958, -561, 54, 789, -8};\n";
        fs << "std::vector<int>::const_iterator stl_iterator(&(range_array[0]));\n";
        fs << "std::vector<int> stl_range_vector(stl_iterator, stl_iterator + 5);\n";
        fs << "std::vector<int>::const_reverse_iterator stl_const_it = stl_range_vector.rbegin();\n";
        fs << "int from_stl = *(stl_const_it);\n";
        fs << "    ^^^^^^^^\n";
        fs << "    Compared value";
        fs.close();
    }

        /* Iterator rend() */
    {
        int range_array[] = {78, -951, 562, 8, 745, 51236, 6987};

        std::vector<int>::iterator stl_iterator(&(range_array[0]));
        ft::vector<int>::iterator ft_iterator(&(range_array[0]));

        std::vector<int> stl_range_vector(stl_iterator, stl_iterator + 7);
        ft::vector<int> ft_range_vector(ft_iterator, ft_iterator + 7);
    
        fs.open("./tester/vectors_output/iterator_reverse_end", std::fstream::in | std::fstream::out | std::fstream::trunc);
        
        int from_stl = *(stl_range_vector.rend() - 1);
        int from_ft = *(ft_range_vector.rend() - 1);

        std::cout << ((printSingleValue(fs, from_stl, from_ft) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {78, -951, 562, 8, 745, 51236, 6987};\n";
        fs << "ft::vector<int>::iterator ft_iterator(&(range_array[0]));\n";
        fs << "ft::vector<int> ft_range_vector(ft_iterator, ft_iterator + 7);\n";
        fs << "int from_ft = *(ft_range_vector.rend() - 1);\n";
        fs << "    ^^^^^^^\n";
        fs << "    Compared value";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {78, -951, 562, 8, 745, 51236, 6987};\n";
        fs << "std::vector<int>::iterator stl_iterator(&(range_array[0]));\n";
        fs << "std::vector<int> stl_range_vector(stl_iterator, stl_iterator + 7);\n";
        fs << "int from_stl = *(stl_range_vector.rend() - 1);\n";
        fs << "    ^^^^^^^^\n";
        fs << "    Compared value";
        fs.close();
    }

    /* Const iterator rend() */
    {
        int range_array[] = { 8, -5615, 412, 89, 475};

        std::vector<int>::const_iterator stl_iterator(&(range_array[0]));
        ft::vector<int>::const_iterator ft_iterator(&(range_array[0]));

        std::vector<int> stl_range_vector(stl_iterator, stl_iterator + 5);
        ft::vector<int> ft_range_vector(ft_iterator, ft_iterator + 5);
    
        fs.open("./tester/vectors_output/iterator_const_reverse_end", std::fstream::in | std::fstream::out | std::fstream::trunc);
        
        std::vector<int>::const_reverse_iterator stl_const_it = stl_range_vector.rend() - 1;
        ft::vector<int>::const_reverse_iterator ft_const_it = ft_range_vector.rend() - 1;
        const int from_stl = *(stl_const_it);
        const int from_ft = *(ft_const_it);

        std::cout << ((printSingleValue(fs, from_stl, from_ft) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = { 8, -5615, 412, 89, 475};\n";
        fs << "ft::vector<int>::const_iterator ft_iterator(&(range_array[0]));\n";
        fs << "ft::vector<int> ft_range_vector(ft_iterator, ft_iterator + 5);\n";
        fs << "std::vector<int>::const_reverse_iterator stl_const_it = stl_range_vector.rend() - 1;\n";
        fs << "int from_ft = *(ft_const_it);\n";
        fs << "    ^^^^^^^\n";
        fs << "    Compared value";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = { 8, -5615, 412, 89, 475};\n";
        fs << "std::vector<int>::const_iterator stl_iterator(&(range_array[0]));\n";
        fs << "std::vector<int> stl_range_vector(stl_iterator, stl_iterator + 5);\n";
        fs << "ft::vector<int>::const_reverse_iterator ft_const_it = ft_range_vector.rend() - 1;\n";
        fs << "int from_stl = *(stl_const_it);\n";
        fs << "    ^^^^^^^^\n";
        fs << "    Compared value";
        fs.close();
    }

    std::cout << "\n";
    std::cout << "Capacity : ";

    /* Size small */
    {
        std::vector<int> stl_filled(20);
        ft::vector<int> ft_filled(20);

        fs.open("./tester/vectors_output/size_small", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printVectorAttributes(fs, stl_filled, ft_filled) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::vector<int> ft_filled(20);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::vector<int> stl_filled(20);\n";
        fs.close();
    }

    /* Size big */
    {
        std::vector<int> stl_filled(100000);
        ft::vector<int> ft_filled(100000);

        fs.open("./tester/vectors_output/size_big", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printVectorAttributes(fs, stl_filled, ft_filled) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::vector<int> ft_filled(1000000);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::vector<int> stl_filled(1000000);\n";
        fs.close();
    }

    /* Maximum size */
    {
        std::vector<int> stl_base;
        ft::vector<int> ft_base;

        fs.open("./tester/vectors_output/maximum_size", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printVectorAttributes(fs, stl_base, ft_base) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::vector<int> ft_base;\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::vector<int> stl_base;\n";
        fs.close();    
    }

    /* Resize extension */
    {
        std::vector<int> stl_base(40);
        ft::vector<int> ft_base(40);

        stl_base.resize(85);
        ft_base.resize(85);

        fs.open("./tester/vectors_output/resize_extension", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printVectorAttributes(fs, stl_base, ft_base) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::vector<int> ft_base(40);\n";
        fs << "ft_base.resize(85);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::vector<int> stl_base(40);\n";
        fs << "stl_base.resize(85);\n";
        fs.close();    
    }

    /* Resize reduction */
    {
        std::vector<int> stl_base(40);
        ft::vector<int> ft_base(40);

        stl_base.resize(3);
        ft_base.resize(3);

        fs.open("./tester/vectors_output/resize_reduction", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printVectorAttributes(fs, stl_base, ft_base) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::vector<int> ft_base(40);\n";
        fs << "ft_base.resize(3);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::vector<int> stl_base(40);\n";
        fs << "stl_base.resize(3);\n";
        fs.close();    
    }

    /* Capacity short */
    {
        std::vector<int> stl_base(40);
        ft::vector<int> ft_base(40);

        stl_base.push_back(42);
        ft_base.push_back(42);
        stl_base.push_back(69);
        ft_base.push_back(69);

        fs.open("./tester/vectors_output/capacity_short", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printVectorAttributes(fs, stl_base, ft_base) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::vector<int> ft_base(40);\n";
        fs << "ft_base.push_back(42);\n";
        fs << "ft_base.push_back(69);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::vector<int> stl_base(40);\n";
        fs << "stl_base.push_back(42);\n";
        fs << "stl_base.push_back(69);\n";
        fs.close();    
    }

    /* Capacity big */
    {
        std::vector<int> stl_base(40000);
        ft::vector<int> ft_base(40000);

        fs.open("./tester/vectors_output/capacity_big", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printVectorAttributes(fs, stl_base, ft_base) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::vector<int> ft_base(40000);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::vector<int> stl_base(40000);\n";
        fs.close();
    }

    /* Empty true */
    {
        std::vector<int> stl_base;
        ft::vector<int> ft_base;

        fs.open("./tester/vectors_output/empty_true", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printVectorAttributes(fs, stl_base, ft_base) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::vector<int> ft_base;\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::vector<int> stl_base;\n";
        fs.close();
    }

    /* Empty false */
    {
        std::vector<int> stl_base(5);
        ft::vector<int> ft_base(5);

        fs.open("./tester/vectors_output/empty_false", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printVectorAttributes(fs, stl_base, ft_base) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::vector<int> ft_base(5);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::vector<int> stl_base(5);\n";
        fs.close();
    }

    /* Empty after resize */
    {
        std::vector<int> stl_base(5);
        ft::vector<int> ft_base(5);

        stl_base.resize(0);
        ft_base.resize(0);

        fs.open("./tester/vectors_output/empty_after_resize", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printVectorAttributes(fs, stl_base, ft_base) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::vector<int> ft_base(5);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::vector<int> stl_base(5);\n";
        fs << "stl_base.resize(0);\n";
        fs.close();
    }

    /* Reserve normal */
    {
        std::vector<int> stl_base;
        ft::vector<int> ft_base;

        stl_base.reserve(100);
        ft_base.reserve(100);
        
        stl_base.push_back(42);
        ft_base.push_back(42);
        
        fs.open("./tester/vectors_output/reserve", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printVectorAttributes(fs, stl_base, ft_base) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::vector<int> ft_base;\n";
        fs << "ft_base.reserve(100);\n";
        fs << "ft_base.push_back(42);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::vector<int> stl_base;\n";
        fs << "stl_base.reserve(100);\n";
        fs << "stl_base.push_back(42);\n";
        fs.close();
    }

    std::cout << "\n";
    std::cout << "Element access : ";

    /* Operator [] */
    {
        int range_array[] = { 8, -5615, 412, 89, 475};

        std::vector<int>::iterator stl_iterator_beg(&(range_array[0]));
        ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));

        std::vector<int> stl_operator(stl_iterator_beg, stl_iterator_beg + 5);
        ft::vector<int> ft_operator(ft_iterator_beg, ft_iterator_beg + 5);

        fs.open("./tester/vectors_output/operator_at", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printSingleValue(fs, stl_operator[1], ft_operator[1]) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = { 8, -5615, 412, 89, 475};\n";
        fs << "ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));\n";
        fs << "ft::vector<int> ft_operator(ft_iterator_beg, ft_iterator_beg + 5);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = { 8, -5615, 412, 89, 475};\n";
        fs << "std::vector<int>::iterator stl_iterator_beg(&(range_array[0]));\n";
        fs << "std::vector<int> stl_operator(stl_iterator_beg, stl_iterator_beg + 5);\n";
        fs.close();
    }

    /* Const Operator [] */
    {
        int range_array[] = {8, -98, 541, 53361, 9};

        std::vector<int>::iterator stl_iterator_beg(&(range_array[0]));
        ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));

        std::vector<int> stl_operator(stl_iterator_beg, stl_iterator_beg + 5);
        ft::vector<int> ft_operator(ft_iterator_beg, ft_iterator_beg + 5);

        const int stl_const = stl_operator[1];
        const int ft_const = ft_operator[1];
        
        fs.open("./tester/vectors_output/operator_at_const", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printSingleValue(fs, stl_const, ft_const) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {8, -98, 541, 53361, 9};\n";
        fs << "ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));\n";
        fs << "ft::vector<int> ft_operator(ft_iterator_beg, ft_iterator_beg + 5);\n";
        fs << "const int stl_const = stl_operator[1];\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {8, -98, 541, 53361, 9};\n";
        fs << "std::vector<int>::iterator stl_iterator_beg(&(range_array[0]));\n";
        fs << "std::vector<int> stl_operator(stl_iterator_beg, stl_iterator_beg + 5);\n";
        fs << "const int stl_const = stl_operator[1];\n";
        fs.close();
    }

    /* Normal at() */
    {
        int range_array[] = {8, -986, -8, 66, 7};

        std::vector<int>::iterator stl_iterator_beg(&(range_array[0]));
        ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));

        std::vector<int> stl_at(stl_iterator_beg, stl_iterator_beg + 5);
        ft::vector<int> ft_at(ft_iterator_beg, ft_iterator_beg + 5);

        fs.open("./tester/vectors_output/at", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printSingleValue(fs, stl_at.at(3), ft_at.at(3)) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {8, -986, -8, 66, 7};\n";
        fs << "ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));\n";
        fs << "ft::vector<int> ft_at(ft_iterator_beg, ft_iterator_beg + 5);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {8, -986, -8, 66, 7};\n";
        fs << "std::vector<int>::iterator stl_iterator_beg(&(range_array[0]));\n";
        fs << "std::vector<int> stl_at(stl_iterator_beg, stl_iterator_beg + 5);\n";
        fs.close();
    }    

    /* Const at() */
    {
        int range_array[] = {845, -9, 47, 4, -825};

        std::vector<int>::iterator stl_iterator_beg(&(range_array[0]));
        ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));

        std::vector<int> stl_at(stl_iterator_beg, stl_iterator_beg + 5);
        ft::vector<int> ft_at(ft_iterator_beg, ft_iterator_beg + 5);

        const int stl_const = stl_at.at(4);
        const int ft_const = ft_at.at(4);
        
        fs.open("./tester/vectors_output/const_at", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printSingleValue(fs, stl_const, ft_const) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {845, -9, 47, 4, -825};\n";
        fs << "ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));\n";
        fs << "ft::vector<int> ft_at(ft_iterator_beg, ft_iterator_beg + 5);\n";
        fs << "const int stl_const = stl_at.at(4);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {845, -9, 47, 4, -825};\n";
        fs << "std::vector<int>::iterator stl_iterator_beg(&(range_array[0]));\n";
        fs << "std::vector<int> stl_at(stl_iterator_beg, stl_iterator_beg + 5);\n";
        fs << "const int ft_const = ft_at.at(4);\n";
        fs.close();
    }

    /* Normal front() */
    {
        int range_array[] = {2, 0, 982, -9, 87};

        std::vector<int>::iterator stl_iterator_beg(&(range_array[0]));
        ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));

        std::vector<int> stl_front(stl_iterator_beg, stl_iterator_beg + 5);
        ft::vector<int> ft_front(ft_iterator_beg, ft_iterator_beg + 5);

        fs.open("./tester/vectors_output/front", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printSingleValue(fs, stl_front.front(), ft_front.front()) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {2, 0, 982, -9, 87};\n";
        fs << "ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));\n";
        fs << "ft::vector<int> ft_front(ft_iterator_beg, ft_iterator_beg + 5);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {2, 0, 982, -9, 87};\n";
        fs << "std::vector<int>::iterator stl_iterator_beg(&(range_array[0]));\n";
        fs << "std::vector<int> stl_front(stl_iterator_beg, stl_iterator_beg + 5);\n";
        fs.close();
    }

    /* Const front() */
    {
        int range_array[] = {5589, -97, -98, -63, 8};

        std::vector<int>::iterator stl_iterator_beg(&(range_array[0]));
        ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));

        std::vector<int> stl_front(stl_iterator_beg, stl_iterator_beg + 5);
        ft::vector<int> ft_front(ft_iterator_beg, ft_iterator_beg + 5);

        const int stl_const = stl_front.front();
        const int ft_const = ft_front.front();

        fs.open("./tester/vectors_output/front_const", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printSingleValue(fs, stl_const, ft_const) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {5589, -97, -98, -63, 8};\n";
        fs << "ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));\n";
        fs << "ft::vector<int> ft_front(ft_iterator_beg, ft_iterator_beg + 5);\n";
        fs << "const int ft_const = ft_front.front();\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {5589, -97, -98, -63, 8};\n";
        fs << "std::vector<int>::iterator stl_iterator_beg(&(range_array[0]));\n";
        fs << "std::vector<int> stl_front(stl_iterator_beg, stl_iterator_beg + 5);\n";
        fs << "const int stl_const = stl_front.front();\n";
        fs.close();
    }

    /* Normal back() */
    {
        int range_array[] = {2, 0, 982, -9, 87};

        std::vector<int>::iterator stl_iterator_beg(&(range_array[0]));
        ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));

        std::vector<int> stl_back(stl_iterator_beg, stl_iterator_beg + 5);
        ft::vector<int> ft_back(ft_iterator_beg, ft_iterator_beg + 5);

        fs.open("./tester/vectors_output/back", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printSingleValue(fs, stl_back.back(), ft_back.back()) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {2, 0, 982, -9, 87};\n";
        fs << "ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));\n";
        fs << "ft::vector<int> ft_back(ft_iterator_beg, ft_iterator_beg + 5);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {2, 0, 982, -9, 87};\n";
        fs << "std::vector<int>::iterator stl_iterator_beg(&(range_array[0]));\n";
        fs << "std::vector<int> stl_back(stl_iterator_beg, stl_iterator_beg + 5);\n";
        fs.close();
    }

    /* Const back() */
    {
        int range_array[] = {5589, -97, -98, -63, 8};

        std::vector<int>::iterator stl_iterator_beg(&(range_array[0]));
        ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));

        std::vector<int> stl_back(stl_iterator_beg, stl_iterator_beg + 5);
        ft::vector<int> ft_back(ft_iterator_beg, ft_iterator_beg + 5);

        const int stl_const = stl_back.back();
        const int ft_const = ft_back.back();

        fs.open("./tester/vectors_output/back_const", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printSingleValue(fs, stl_const, ft_const) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {5589, -97, -98, -63, 8};\n";
        fs << "ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));\n";
        fs << "ft::vector<int> ft_back(ft_iterator_beg, ft_iterator_beg + 5);\n";
        fs << "const int ft_const = ft_back.back();\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {5589, -97, -98, -63, 8};\n";
        fs << "std::vector<int>::iterator stl_iterator_beg(&(range_array[0]));\n";
        fs << "std::vector<int> stl_back(stl_iterator_beg, stl_iterator_beg + 5);\n";
        fs << "const int stl_const = stl_back.back();\n";
        fs.close();
    }
 
    std::cout << "\n";
    std::cout << "Modifiers : ";

    /* Assign range */
    {
        int range_array[] = {84, 522, -654, -7623, 4};

        std::vector<int>::iterator stl_iterator_beg(&(range_array[0]));
        ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));

        std::vector<int> stl_assign;
        ft::vector<int> ft_assign;

        stl_assign.assign(stl_iterator_beg, stl_iterator_beg + 5);
        ft_assign.assign(ft_iterator_beg, ft_iterator_beg + 5);

        fs.open("./tester/vectors_output/assign_range", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printVectorAttributes(fs, stl_assign, ft_assign) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {84, 522, -654, -7623, 4};\n";
        fs << "ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));\n";
        fs << "ft::vector<int> ft_assign;\n";
        fs << "ft_assign.assign(ft_iterator_beg, ft_iterator_beg + 5);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {84, 522, -654, -7623, 4};\n";
        fs << "std::vector<int>::iterator stl_iterator_beg(&(range_array[0]));\n";
        fs << "std::vector<int> stl_assign;\n";
        fs << "stl_assign.assign(stl_iterator_beg, stl_iterator_beg + 5);\n";
        fs.close();
    }

    /* Assign range replace */
    {
        int range_array[] = {547, 98, -6, 0, 47};

        std::vector<int>::iterator stl_iterator_beg(&(range_array[0]));
        ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));

        std::vector<int> stl_assign(42);
        ft::vector<int> ft_assign(42);

        stl_assign.assign(stl_iterator_beg, stl_iterator_beg + 5);
        ft_assign.assign(ft_iterator_beg, ft_iterator_beg + 5);

        fs.open("./tester/vectors_output/assign_range_replace", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printVectorAttributes(fs, stl_assign, ft_assign) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {547, 98, -6, 0, 47};\n";
        fs << "ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));\n";
        fs << "ft::vector<int> ft_assign;\n";
        fs << "ft_assign.assign(ft_iterator_beg, ft_iterator_beg + 5);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {547, 98, -6, 0, 47};\n";
        fs << "std::vector<int>::iterator stl_iterator_beg(&(range_array[0]));\n";
        fs << "std::vector<int> stl_assign;\n";
        fs << "stl_assign.assign(stl_iterator_beg, stl_iterator_beg + 5);\n";
        fs.close();
    }

    /* Assign fill */
    {
        std::vector<int> stl_assign_fill;
        ft::vector<int> ft_assign_fill;

        stl_assign_fill.assign(87, 42);
        ft_assign_fill.assign(87, 42);
        
        fs.open("./tester/vectors_output/assign_fill", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printVectorAttributes(fs, stl_assign_fill, ft_assign_fill) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::vector<int> ft_assign_fill;\n";
        fs << "ft_assign_fill.assign(87, 42);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";    
        fs << "std::vector<int> stl_assign_fill;\n";
        fs << "stl_assign_fill.assign(87, 42);\n";
        fs.close();
    }

    /* Assign fill Replace */
    {
        std::vector<int> stl_assign_fill(42);
        ft::vector<int> ft_assign_fill(42);

        stl_assign_fill.assign(420, 14);
        ft_assign_fill.assign(420, 14);
        
        fs.open("./tester/vectors_output/assign_fill_replace", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printVectorAttributes(fs, stl_assign_fill, ft_assign_fill) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::vector<int> ft_assign_fill;\n";
        fs << "ft_assign_fill.assign(87, 42);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";    
        fs << "std::vector<int> stl_assign_fill;\n";
        fs << "stl_assign_fill.assign(87, 42);\n";
        fs.close();
    }

    /* Push back empty */
    {
        std::vector<int> stl_pushback;
        ft::vector<int> ft_pushback;

        stl_pushback.push_back(42);
        ft_pushback.push_back(42);

        fs.open("./tester/vectors_output/push_back_empty", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printVectorAttributes(fs, stl_pushback, ft_pushback) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::vector<int> ft_pushback;\n";
        fs << "ft_pushback.push_back(42);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::vector<int> stl_pushback;\n";
        fs << "stl_pushback.push_back(42);\n";
        fs.close();
    }

    /* Push back */
    {
        std::vector<int> stl_pushback(7);
        ft::vector<int> ft_pushback(7);

        stl_pushback.push_back(42);
        ft_pushback.push_back(42);

        fs.open("./tester/vectors_output/push_back", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printVectorAttributes(fs, stl_pushback, ft_pushback) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "ft::vector<int> ft_pushback(7);\n";
        fs << "ft_pushback.push_back(42);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "std::vector<int> stl_pushback(7);\n";
        fs << "stl_pushback.push_back(42);\n";
        fs.close();
    }

    /* Pop back */
    {
        int range_array[] = {547, 98, -6, 0, 47};

        std::vector<int>::iterator stl_iterator_beg(&(range_array[0]));
        ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));

        std::vector<int> stl_popback(stl_iterator_beg, stl_iterator_beg + 5);
        ft::vector<int> ft_popback(ft_iterator_beg, ft_iterator_beg + 5);

        stl_popback.pop_back();
        ft_popback.pop_back();
        
        fs.open("./tester/vectors_output/pop_back", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printVectorAttributes(fs, stl_popback, ft_popback) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {547, 98, -6, 0, 47};\n";
        fs << "ft::vector<int> ft_popback(ft_iterator_beg, ft_iterator_beg + 5);\n";
        fs << "ft_popback.pop_back();\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {547, 98, -6, 0, 47};\n";
        fs << "std::vector<int>::iterator stl_iterator_beg(&(range_array[0]));\n";
        fs << "stl_popback.pop_back();\n";
        fs.close();
    }

    /* Insert single element */
    {
        int range_array[] = {478, 87, -85, 44, 7};

        std::vector<int>::iterator stl_iterator_beg(&(range_array[0]));
        ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));

        std::vector<int> stl_insert(stl_iterator_beg, stl_iterator_beg + 5);
        ft::vector<int> ft_insert(ft_iterator_beg, ft_iterator_beg + 5);

        stl_insert.insert(stl_insert.begin() + 2, 9999);
        ft_insert.insert(ft_insert.begin() + 2, 9999);
        
        fs.open("./tester/vectors_output/insert_single", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printVectorAttributes(fs, stl_insert, ft_insert) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {478, 87, -85, 44, 7};\n";
        fs << "ft::vector<int> ft_insert(ft_iterator_beg, ft_iterator_beg + 5);\n";
        fs << "ft_insert.pop_back();\n";
        fs << "ft_insert.insert(ft_insert.begin() + 2, 9999);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {478, 87, -85, 44, 7};\n";
        fs << "std::vector<int>::iterator stl_iterator_beg(&(range_array[0]));\n";
        fs << "stl_insert.insert(stl_insert.begin() + 2, 9999);\n";
        fs.close();
    }

    /* Insert fill */
    {
        int range_array[] = {47, 152, -325, 9, 14444};

        std::vector<int>::iterator stl_iterator_beg(&(range_array[0]));
        ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));

        std::vector<int> stl_insert(stl_iterator_beg, stl_iterator_beg + 5);
        ft::vector<int> ft_insert(ft_iterator_beg, ft_iterator_beg + 5);

        stl_insert.insert(stl_insert.begin() + 2, 6, 4269);
        ft_insert.insert(ft_insert.begin() + 2, 6, 4269);
        
        fs.open("./tester/vectors_output/insert_fill", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printVectorAttributes(fs, stl_insert, ft_insert) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {47, 152, -325, 9, 14444};\n";
        fs << "ft::vector<int> ft_insert(ft_iterator_beg, ft_iterator_beg + 5);\n";
        fs << "ft_insert.insert(ft_insert.begin() + 2, 6, 4269);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {47, 152, -325, 9, 14444};\n";
        fs << "std::vector<int>::iterator stl_iterator_beg(&(range_array[0]));\n";
        fs << "stl_insert.insert(stl_insert.begin() + 2, 6, 4269);\n";
        fs.close();
    }

    /* Insert range */
    {
        int range_array[] = {47, 152, -325, 9, 14444};
        
        std::vector<int>::iterator stl_iterator_beg(&(range_array[0]));
        ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));

        std::vector<int> stl_insert(4);
        ft::vector<int> ft_insert(4);

        stl_insert.insert(stl_insert.end(), stl_iterator_beg, stl_iterator_beg + 5);
        ft_insert.insert(ft_insert.end(), ft_iterator_beg, ft_iterator_beg + 5);

        fs.open("./tester/vectors_output/insert_range", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printVectorAttributes(fs, stl_insert, ft_insert) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {47, 152, -325, 9, 14444};\n";
        fs << "ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));\n";
        fs << "ft::vector<int> ft_insert(4);\n";
        fs << "ft_insert.insert(ft_insert.end(), ft_iterator_beg, ft_iterator_beg + 5);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {47, 152, -325, 9, 14444};\n";
        fs << "std::vector<int>::iterator stl_iterator_beg(&(range_array[0]));\n";
        fs << "std::vector<int> stl_insert(4);\n";
        fs << "stl_insert.insert(stl_insert.end(), stl_iterator_beg, stl_iterator_beg + 5);\n";
        fs.close();
    }

    /* Erase single element */
    {
        int range_array[] = {47, 152, -325, 9, 14444};

        std::vector<int>::iterator stl_iterator_beg(&(range_array[0]));
        ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));

        std::vector<int> stl_erase(stl_iterator_beg, stl_iterator_beg + 5);
        ft::vector<int> ft_erase(ft_iterator_beg, ft_iterator_beg + 5);

        stl_erase.erase(stl_erase.begin() + 2);
        ft_erase.erase(ft_erase.begin() + 2);
        
        fs.open("./tester/vectors_output/erase_single", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printVectorAttributes(fs, stl_erase, ft_erase) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {47, 152, -325, 9, 14444};\n";
        fs << "ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));\n";
        fs << "ft::vector<int> ft_erase(ft_iterator_beg, ft_iterator_beg + 5);\n";
        fs << "ft_erase.erase(ft_erase.begin());\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {47, 152, -325, 9, 14444};\n";
        fs << "std::vector<int>::iterator stl_iterator_beg(&(range_array[0]));\n";
        fs << "std::vector<int> stl_erase(stl_iterator_beg, stl_iterator_beg + 5);\n";
        fs << "stl_erase.erase(stl_erase.begin());\n";
        fs.close();
    }

    /* Erase range */
    {
        int range_array[] = {1458, -98, 745, 62, 9};

        std::vector<int>::iterator stl_iterator_beg(&(range_array[0]));
        ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));

        std::vector<int> stl_erase(stl_iterator_beg, stl_iterator_beg + 5);
        ft::vector<int> ft_erase(ft_iterator_beg, ft_iterator_beg + 5);

        stl_erase.erase(stl_erase.begin() + 1, stl_erase.end() - 2);
        ft_erase.erase(ft_erase.begin() + 1, ft_erase.end() - 2);
        
        fs.open("./tester/vectors_output/erase_range", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printVectorAttributes(fs, stl_erase, ft_erase) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {1458, -98, 745, 62, 9};\n";
        fs << "ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));\n";
        fs << "ft::vector<int> ft_erase(ft_iterator_beg, ft_iterator_beg + 5);\n";
        fs << "ft_erase.erase(ft_erase.begin() + 1, ft_erase.end() - 2);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {1458, -98, 745, 62, 9};\n";
        fs << "std::vector<int>::iterator stl_iterator_beg(&(range_array[0]));\n";
        fs << "std::vector<int> stl_erase(stl_iterator_beg, stl_iterator_beg + 5);\n";
        fs << "stl_erase.erase(stl_erase.begin() + 1, stl_erase.end() - 2);\n";
        fs.close();
    }

    /* Swap */
    {
        int range_array_one[] = {1458, -98, 745, 62, 9};
        int range_array_two[] = {478, 87, -15, 44, 7};

        std::vector<int>::iterator stl_iterator_beg_one(&(range_array_one[0]));
        std::vector<int>::iterator stl_iterator_beg_two(&(range_array_two[0]));
        ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));
        ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));

        std::vector<int> stl_swap_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);
        std::vector<int> stl_swap_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);
        ft::vector<int> ft_swap_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);
        ft::vector<int> ft_swap_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);

        stl_swap_one.swap(stl_swap_two);
        ft_swap_one.swap(ft_swap_two);

        fs.open("./tester/vectors_output/swap_member", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printVectorAttributes(fs, stl_swap_one, ft_swap_one) == true) ? "[OK]" : "[NOP]");
        std::cout << ((printVectorAttributes(fs, stl_swap_two, ft_swap_two) == true) ? "[OK]" : "[NOP]");
        
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {1458, -98, 745, 62, 9};\n";
        fs << "int range_array_two[] = {478, 87, -15, 44, 7};       \n";
        fs << "ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));\n";
        fs << "ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));\n";
        fs << "ft::vector<int> ft_swap_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);\n";
        fs << "ft::vector<int> ft_swap_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);\n";
        fs << "ft_swap_one.swap(ft_swap_two);\n";

        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {1458, -98, 745, 62, 9};\n";
        fs << "int range_array_two[] = {478, 87, -15, 44, 7};\n";
        fs << "std::vector<int>::iterator stl_iterator_beg_one(&(range_array_one[0]));\n";
        fs << "std::vector<int>::iterator stl_iterator_beg_two(&(range_array_two[0]));\n";
        fs << "std::vector<int> stl_swap_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);\n";
        fs << "std::vector<int> stl_swap_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);\n";
        fs << "stl_swap_one.swap(stl_swap_two);\n";
        fs.close();
    }

    /* Clear */
    {
        int range_array[] = {-455, 2, 1347, 75, 945};

        std::vector<int>::iterator stl_iterator_beg(&(range_array[0]));
        ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));

        std::vector<int> stl_clear(stl_iterator_beg, stl_iterator_beg + 5);
        ft::vector<int> ft_clear(ft_iterator_beg, ft_iterator_beg + 5);

        stl_clear.clear();
        ft_clear.clear();
        
        fs.open("./tester/vectors_output/clear", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printVectorAttributes(fs, stl_clear, ft_clear) == true) ? "[OK]" : "[NOP]");
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {-455, 2, 1347, 75, 945};\n";
        fs << "ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));\n";
        fs << "ft::vector<int> ft_clear(ft_iterator_beg, ft_iterator_beg + 5);\n";
        fs << "ft_clear.clear();\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {-455, 2, 1347, 75, 945};\n";
        fs << "std::vector<int>::iterator stl_iterator_beg(&(range_array[0]));\n";
        fs << "std::vector<int> stl_clear(stl_iterator_beg, stl_iterator_beg + 5);\n";
        fs << "stl_clear.clear();\n";
        fs.close();
    }

    std::cout << "\n";
    std::cout << "Non member function overloads : ";

    /* RL = Relation operator */

    /* RL '==' true */
    {
        int range_array_one[] = {1458, -98, 745, 62, 9};
        int range_array_two[] = {1458, -98, 745, 62, 9};

        std::vector<int>::iterator stl_iterator_beg_one(&(range_array_one[0]));
        std::vector<int>::iterator stl_iterator_beg_two(&(range_array_two[0]));
        ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));
        ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));

        std::vector<int> stl_equal_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);
        std::vector<int> stl_equal_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);
        ft::vector<int> ft_equal_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);
        ft::vector<int> ft_equal_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);

        fs.open("./tester/vectors_output/operator_equal_true", std::fstream::in | std::fstream::out | std::fstream::trunc);
        printVectorAttributes(fs, stl_equal_one, ft_equal_one);
        printVectorAttributes(fs, stl_equal_two, ft_equal_two);

        std::cout << ((printBoolResult(fs, (stl_equal_one == stl_equal_two), (ft_equal_one == ft_equal_two))) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {1458, -98, 745, 62, 9};\n";
        fs << "int range_array_two[] = {1458, -98, 745, 62, 9};       \n";
        fs << "ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));\n";
        fs << "ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));\n";
        fs << "ft::vector<int> ft_equal_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);\n";
        fs << "ft::vector<int> ft_equal_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);\n";

        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {1458, -98, 745, 62, 9};\n";
        fs << "int range_array_two[] = {1458, -98, 745, 62, 9};\n";
        fs << "std::vector<int>::iterator stl_iterator_beg_one(&(range_array_one[0]));\n";
        fs << "std::vector<int>::iterator stl_iterator_beg_two(&(range_array_two[0]));\n";
        fs << "std::vector<int> stl_equal_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);\n";
        fs << "std::vector<int> stl_equal_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);\n";
        fs.close();
    }

    /* RL '==' false */
    {
        int range_array_one[] = {144, 335, 5, 0, -54};
        int range_array_two[] = {1458, -98, 745, 62, 9};

        std::vector<int>::iterator stl_iterator_beg_one(&(range_array_one[0]));
        std::vector<int>::iterator stl_iterator_beg_two(&(range_array_two[0]));
        ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));
        ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));

        std::vector<int> stl_equal_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);
        std::vector<int> stl_equal_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);
        ft::vector<int> ft_equal_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);
        ft::vector<int> ft_equal_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);

        fs.open("./tester/vectors_output/operator_equal_false", std::fstream::in | std::fstream::out | std::fstream::trunc);
        printVectorAttributes(fs, stl_equal_one, ft_equal_one);
        printVectorAttributes(fs, stl_equal_two, ft_equal_two);

        std::cout << ((printBoolResult(fs, (stl_equal_one == stl_equal_two), (ft_equal_one == ft_equal_two))) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 335, 5, 0, -54};\n";
        fs << "int range_array_two[] = {1458, -98, 745, 62, 9};       \n";
        fs << "ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));\n";
        fs << "ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));\n";
        fs << "ft::vector<int> ft_equal_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);\n";
        fs << "ft::vector<int> ft_equal_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);\n";

        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 335, 5, 0, -54};\n";
        fs << "int range_array_two[] = {1458, -98, 745, 62, 9};\n";
        fs << "std::vector<int>::iterator stl_iterator_beg_one(&(range_array_one[0]));\n";
        fs << "std::vector<int>::iterator stl_iterator_beg_two(&(range_array_two[0]));\n";
        fs << "std::vector<int> stl_equal_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);\n";
        fs << "std::vector<int> stl_equal_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);\n";
        fs.close();
    }

    /* RL '!=' true */
    {
        int range_array_one[] = {144, 335, 5, 0, -54};
        int range_array_two[] = {1458, -98, 745, 62, 9};

        std::vector<int>::iterator stl_iterator_beg_one(&(range_array_one[0]));
        std::vector<int>::iterator stl_iterator_beg_two(&(range_array_two[0]));
        ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));
        ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));

        std::vector<int> stl_operator_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);
        std::vector<int> stl_operator_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);
        ft::vector<int> ft_operator_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);
        ft::vector<int> ft_operator_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);

        fs.open("./tester/vectors_output/operator_not_equal_true", std::fstream::in | std::fstream::out | std::fstream::trunc);
        printVectorAttributes(fs, stl_operator_one, ft_operator_one);
        printVectorAttributes(fs, stl_operator_two, ft_operator_two);

        std::cout << ((printBoolResult(fs, (stl_operator_one != stl_operator_two), (ft_operator_one != ft_operator_two))) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 335, 5, 0, -54};\n";
        fs << "int range_array_two[] = {1458, -98, 745, 62, 9};       \n";
        fs << "ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));\n";
        fs << "ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));\n";
        fs << "ft::vector<int> ft_operator_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);\n";
        fs << "ft::vector<int> ft_operator_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);\n";

        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 335, 5, 0, -54};\n";
        fs << "int range_array_two[] = {1458, -98, 745, 62, 9};\n";
        fs << "std::vector<int>::iterator stl_iterator_beg_one(&(range_array_one[0]));\n";
        fs << "std::vector<int>::iterator stl_iterator_beg_two(&(range_array_two[0]));\n";
        fs << "std::vector<int> stl_operator_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);\n";
        fs << "std::vector<int> stl_operator_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);\n";
        fs.close();
    }

    /* RL '!=' false */
    {
        int range_array_one[] = {144, 335, 5, 0, -54};
        int range_array_two[] = {144, 335, 5, 0, -54};

        std::vector<int>::iterator stl_iterator_beg_one(&(range_array_one[0]));
        std::vector<int>::iterator stl_iterator_beg_two(&(range_array_two[0]));
        ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));
        ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));

        std::vector<int> stl_operator_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);
        std::vector<int> stl_operator_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);
        ft::vector<int> ft_operator_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);
        ft::vector<int> ft_operator_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);

        fs.open("./tester/vectors_output/operator_not_equal_false", std::fstream::in | std::fstream::out | std::fstream::trunc);
        printVectorAttributes(fs, stl_operator_one, ft_operator_one);
        printVectorAttributes(fs, stl_operator_two, ft_operator_two);

        std::cout << ((printBoolResult(fs, (stl_operator_one != stl_operator_two), (ft_operator_one != ft_operator_two))) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 335, 5, 0, -54};\n";
        fs << "int range_array_two[] = {144, 335, 5, 0, -54};       \n";
        fs << "ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));\n";
        fs << "ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));\n";
        fs << "ft::vector<int> ft_operator_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);\n";
        fs << "ft::vector<int> ft_operator_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);\n";

        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 335, 5, 0, -54};\n";
        fs << "int range_array_two[] = {144, 335, 5, 0, -54};\n";
        fs << "std::vector<int>::iterator stl_iterator_beg_one(&(range_array_one[0]));\n";
        fs << "std::vector<int>::iterator stl_iterator_beg_two(&(range_array_two[0]));\n";
        fs << "std::vector<int> stl_operator_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);\n";
        fs << "std::vector<int> stl_operator_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);\n";
        fs.close();
    }
    
    /* RL '<' true */
    {
        int range_array_one[] = {144, 335, 1, -98, 5};
        int range_array_two[] = {144, 335, 5, 0, -54};

        std::vector<int>::iterator stl_iterator_beg_one(&(range_array_one[0]));
        std::vector<int>::iterator stl_iterator_beg_two(&(range_array_two[0]));
        ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));
        ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));

        std::vector<int> stl_operator_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);
        std::vector<int> stl_operator_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);
        ft::vector<int> ft_operator_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);
        ft::vector<int> ft_operator_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);

        fs.open("./tester/vectors_output/operator_inferior_true", std::fstream::in | std::fstream::out | std::fstream::trunc);
        printVectorAttributes(fs, stl_operator_one, ft_operator_one);
        printVectorAttributes(fs, stl_operator_two, ft_operator_two);

        std::cout << ((printBoolResult(fs, (stl_operator_one < stl_operator_two), (ft_operator_one < ft_operator_two))) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 335, 1, -98, 5};\n";
        fs << "int range_array_two[] = {144, 335, 5, 0, -54};       \n";
        fs << "ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));\n";
        fs << "ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));\n";
        fs << "ft::vector<int> ft_operator_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);\n";
        fs << "ft::vector<int> ft_operator_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);\n";

        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 335, 1, -98, 5};\n";
        fs << "int range_array_two[] = {144, 335, 5, 0, -54};\n";
        fs << "std::vector<int>::iterator stl_iterator_beg_one(&(range_array_one[0]));\n";
        fs << "std::vector<int>::iterator stl_iterator_beg_two(&(range_array_two[0]));\n";
        fs << "std::vector<int> stl_operator_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);\n";
        fs << "std::vector<int> stl_operator_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);\n";
        fs.close();
    }

    /* RL '<' false */
    {
        int range_array_one[] = {6780, 335, 1, -98, 5};
        int range_array_two[] = {144, 335, 5, 0, -54};

        std::vector<int>::iterator stl_iterator_beg_one(&(range_array_one[0]));
        std::vector<int>::iterator stl_iterator_beg_two(&(range_array_two[0]));
        ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));
        ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));

        std::vector<int> stl_operator_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);
        std::vector<int> stl_operator_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);
        ft::vector<int> ft_operator_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);
        ft::vector<int> ft_operator_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);

        fs.open("./tester/vectors_output/operator_inferior_false", std::fstream::in | std::fstream::out | std::fstream::trunc);
        printVectorAttributes(fs, stl_operator_one, ft_operator_one);
        printVectorAttributes(fs, stl_operator_two, ft_operator_two);

        std::cout << ((printBoolResult(fs, (stl_operator_one < stl_operator_two), (ft_operator_one < ft_operator_two))) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {6780, 335, 1, -98, 5};\n";
        fs << "int range_array_two[] = {144, 335, 5, 0, -54};       \n";
        fs << "ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));\n";
        fs << "ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));\n";
        fs << "ft::vector<int> ft_operator_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);\n";
        fs << "ft::vector<int> ft_operator_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);\n";

        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {6780, 335, 1, -98, 5};\n";
        fs << "int range_array_two[] = {144, 335, 5, 0, -54};\n";
        fs << "std::vector<int>::iterator stl_iterator_beg_one(&(range_array_one[0]));\n";
        fs << "std::vector<int>::iterator stl_iterator_beg_two(&(range_array_two[0]));\n";
        fs << "std::vector<int> stl_operator_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);\n";
        fs << "std::vector<int> stl_operator_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);\n";
        fs.close();
    }

    /* RL '<=' true */
    {
        int range_array_one[] = {144, 335, 1, -98, 5};
        int range_array_two[] = {144, 335, 5, 0, -54};

        std::vector<int>::iterator stl_iterator_beg_one(&(range_array_one[0]));
        std::vector<int>::iterator stl_iterator_beg_two(&(range_array_two[0]));
        ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));
        ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));

        std::vector<int> stl_operator_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);
        std::vector<int> stl_operator_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);
        ft::vector<int> ft_operator_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);
        ft::vector<int> ft_operator_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);

        fs.open("./tester/vectors_output/operator_inf_or_equal_true", std::fstream::in | std::fstream::out | std::fstream::trunc);
        printVectorAttributes(fs, stl_operator_one, ft_operator_one);
        printVectorAttributes(fs, stl_operator_two, ft_operator_two);

        std::cout << ((printBoolResult(fs, (stl_operator_one <= stl_operator_two), (ft_operator_one <= ft_operator_two))) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 335, 1, -98, 5};\n";
        fs << "int range_array_two[] = {144, 335, 5, 0, -54};       \n";
        fs << "ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));\n";
        fs << "ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));\n";
        fs << "ft::vector<int> ft_operator_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);\n";
        fs << "ft::vector<int> ft_operator_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);\n";

        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 335, 1, -98, 5};\n";
        fs << "int range_array_two[] = {144, 335, 5, 0, -54};\n";
        fs << "std::vector<int>::iterator stl_iterator_beg_one(&(range_array_one[0]));\n";
        fs << "std::vector<int>::iterator stl_iterator_beg_two(&(range_array_two[0]));\n";
        fs << "std::vector<int> stl_operator_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);\n";
        fs << "std::vector<int> stl_operator_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);\n";
        fs.close();
    }

    /* RL '<=' true equal */
    {
        int range_array_one[] = {144, 335, 5, 0, -54};
        int range_array_two[] = {144, 335, 5, 0, -54};

        std::vector<int>::iterator stl_iterator_beg_one(&(range_array_one[0]));
        std::vector<int>::iterator stl_iterator_beg_two(&(range_array_two[0]));
        ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));
        ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));

        std::vector<int> stl_operator_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);
        std::vector<int> stl_operator_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);
        ft::vector<int> ft_operator_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);
        ft::vector<int> ft_operator_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);

        fs.open("./tester/vectors_output/operator_inf_or_equal_true_equal", std::fstream::in | std::fstream::out | std::fstream::trunc);
        printVectorAttributes(fs, stl_operator_one, ft_operator_one);
        printVectorAttributes(fs, stl_operator_two, ft_operator_two);

        std::cout << ((printBoolResult(fs, (stl_operator_one <= stl_operator_two), (ft_operator_one <= ft_operator_two))) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 335, 5, 0, -54};\n";
        fs << "int range_array_two[] = {144, 335, 5, 0, -54};       \n";
        fs << "ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));\n";
        fs << "ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));\n";
        fs << "ft::vector<int> ft_operator_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);\n";
        fs << "ft::vector<int> ft_operator_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);\n";

        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 335, 5, 0, -54};\n";
        fs << "int range_array_two[] = {144, 335, 5, 0, -54};\n";
        fs << "std::vector<int>::iterator stl_iterator_beg_one(&(range_array_one[0]));\n";
        fs << "std::vector<int>::iterator stl_iterator_beg_two(&(range_array_two[0]));\n";
        fs << "std::vector<int> stl_operator_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);\n";
        fs << "std::vector<int> stl_operator_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);\n";
        fs.close();
    }

    /* RL '<=' false */
    {
        int range_array_one[] = {144, 9999, 5, 0, -54};
        int range_array_two[] = {144, 335, 5, 0, -54};

        std::vector<int>::iterator stl_iterator_beg_one(&(range_array_one[0]));
        std::vector<int>::iterator stl_iterator_beg_two(&(range_array_two[0]));
        ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));
        ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));

        std::vector<int> stl_operator_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);
        std::vector<int> stl_operator_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);
        ft::vector<int> ft_operator_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);
        ft::vector<int> ft_operator_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);

        fs.open("./tester/vectors_output/operator_inf_or_equal_false", std::fstream::in | std::fstream::out | std::fstream::trunc);
        printVectorAttributes(fs, stl_operator_one, ft_operator_one);
        printVectorAttributes(fs, stl_operator_two, ft_operator_two);

        std::cout << ((printBoolResult(fs, (stl_operator_one <= stl_operator_two), (ft_operator_one <= ft_operator_two))) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 9999, 5, 0, -54};\n";
        fs << "int range_array_two[] = {144, 335, 5, 0, -54};       \n";
        fs << "ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));\n";
        fs << "ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));\n";
        fs << "ft::vector<int> ft_operator_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);\n";
        fs << "ft::vector<int> ft_operator_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);\n";

        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 9999, 5, 0, -54};\n";
        fs << "int range_array_two[] = {144, 335, 5, 0, -54};\n";
        fs << "std::vector<int>::iterator stl_iterator_beg_one(&(range_array_one[0]));\n";
        fs << "std::vector<int>::iterator stl_iterator_beg_two(&(range_array_two[0]));\n";
        fs << "std::vector<int> stl_operator_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);\n";
        fs << "std::vector<int> stl_operator_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);\n";
        fs.close();
    }

    /* RL '>' true */
    {
        int range_array_one[] = {144, 9999, 5, 0, -54};
        int range_array_two[] = {144, 335, 5, 0, -54};

        std::vector<int>::iterator stl_iterator_beg_one(&(range_array_one[0]));
        std::vector<int>::iterator stl_iterator_beg_two(&(range_array_two[0]));
        ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));
        ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));

        std::vector<int> stl_operator_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);
        std::vector<int> stl_operator_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);
        ft::vector<int> ft_operator_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);
        ft::vector<int> ft_operator_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);

        fs.open("./tester/vectors_output/operator_superior_true", std::fstream::in | std::fstream::out | std::fstream::trunc);
        printVectorAttributes(fs, stl_operator_one, ft_operator_one);
        printVectorAttributes(fs, stl_operator_two, ft_operator_two);

        std::cout << ((printBoolResult(fs, (stl_operator_one > stl_operator_two), (ft_operator_one > ft_operator_two))) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 9999, 5, 0, -54};\n";
        fs << "int range_array_two[] = {144, 335, 5, 0, -54};       \n";
        fs << "ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));\n";
        fs << "ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));\n";
        fs << "ft::vector<int> ft_operator_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);\n";
        fs << "ft::vector<int> ft_operator_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);\n";

        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 9999, 5, 0, -54};\n";
        fs << "int range_array_two[] = {144, 335, 5, 0, -54};\n";
        fs << "std::vector<int>::iterator stl_iterator_beg_one(&(range_array_one[0]));\n";
        fs << "std::vector<int>::iterator stl_iterator_beg_two(&(range_array_two[0]));\n";
        fs << "std::vector<int> stl_operator_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);\n";
        fs << "std::vector<int> stl_operator_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);\n";
        fs.close();
    }

    /* RL '>' false */
    {
        int range_array_one[] = {144, 335, 5, 0, -54};
        int range_array_two[] = {144, 335, 77, 0, -54};

        std::vector<int>::iterator stl_iterator_beg_one(&(range_array_one[0]));
        std::vector<int>::iterator stl_iterator_beg_two(&(range_array_two[0]));
        ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));
        ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));

        std::vector<int> stl_operator_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);
        std::vector<int> stl_operator_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);
        ft::vector<int> ft_operator_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);
        ft::vector<int> ft_operator_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);

        fs.open("./tester/vectors_output/operator_superior_false", std::fstream::in | std::fstream::out | std::fstream::trunc);
        printVectorAttributes(fs, stl_operator_one, ft_operator_one);
        printVectorAttributes(fs, stl_operator_two, ft_operator_two);

        std::cout << ((printBoolResult(fs, (stl_operator_one > stl_operator_two), (ft_operator_one > ft_operator_two))) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 335, 5, 0, -54};\n";
        fs << "int range_array_two[] = {144, 335, 77, 0, -54};       \n";
        fs << "ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));\n";
        fs << "ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));\n";
        fs << "ft::vector<int> ft_operator_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);\n";
        fs << "ft::vector<int> ft_operator_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);\n";

        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 335, 5, 0, -54};\n";
        fs << "int range_array_two[] = {144, 335, 77, 0, -54};\n";
        fs << "std::vector<int>::iterator stl_iterator_beg_one(&(range_array_one[0]));\n";
        fs << "std::vector<int>::iterator stl_iterator_beg_two(&(range_array_two[0]));\n";
        fs << "std::vector<int> stl_operator_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);\n";
        fs << "std::vector<int> stl_operator_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);\n";
        fs.close();
    }

    /* RL '>=' true */
    {
        int range_array_one[] = {144, 335, 78, 0, -54};
        int range_array_two[] = {144, 335, 77, 0, -54};

        std::vector<int>::iterator stl_iterator_beg_one(&(range_array_one[0]));
        std::vector<int>::iterator stl_iterator_beg_two(&(range_array_two[0]));
        ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));
        ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));

        std::vector<int> stl_operator_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);
        std::vector<int> stl_operator_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);
        ft::vector<int> ft_operator_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);
        ft::vector<int> ft_operator_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);

        fs.open("./tester/vectors_output/operator_sup_or_equal_true", std::fstream::in | std::fstream::out | std::fstream::trunc);
        printVectorAttributes(fs, stl_operator_one, ft_operator_one);
        printVectorAttributes(fs, stl_operator_two, ft_operator_two);

        std::cout << ((printBoolResult(fs, (stl_operator_one >= stl_operator_two), (ft_operator_one >= ft_operator_two))) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 335, 78, 0, -54};\n";
        fs << "int range_array_two[] = {144, 335, 77, 0, -54};       \n";
        fs << "ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));\n";
        fs << "ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));\n";
        fs << "ft::vector<int> ft_operator_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);\n";
        fs << "ft::vector<int> ft_operator_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);\n";

        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 335, 5, 0, -54};\n";
        fs << "int range_array_two[] = {144, 335, 77, 0, -54};\n";
        fs << "std::vector<int>::iterator stl_iterator_beg_one(&(range_array_one[0]));\n";
        fs << "std::vector<int>::iterator stl_iterator_beg_two(&(range_array_two[0]));\n";
        fs << "std::vector<int> stl_operator_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);\n";
        fs << "std::vector<int> stl_operator_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);\n";
        fs.close();
    }

    /* RL '>=' false */
    {
        int range_array_one[] = {144, 335, 5, 0, -54};
        int range_array_two[] = {144, 335, 77, 0, -54};

        std::vector<int>::iterator stl_iterator_beg_one(&(range_array_one[0]));
        std::vector<int>::iterator stl_iterator_beg_two(&(range_array_two[0]));
        ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));
        ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));

        std::vector<int> stl_operator_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);
        std::vector<int> stl_operator_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);
        ft::vector<int> ft_operator_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);
        ft::vector<int> ft_operator_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);

        fs.open("./tester/vectors_output/operator_sup_or_equal_false", std::fstream::in | std::fstream::out | std::fstream::trunc);
        printVectorAttributes(fs, stl_operator_one, ft_operator_one);
        printVectorAttributes(fs, stl_operator_two, ft_operator_two);

        std::cout << ((printBoolResult(fs, (stl_operator_one >= stl_operator_two), (ft_operator_one >= ft_operator_two))) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 335, 5, 0, -54};\n";
        fs << "int range_array_two[] = {144, 335, 77, 0, -54};       \n";
        fs << "ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));\n";
        fs << "ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));\n";
        fs << "ft::vector<int> ft_operator_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);\n";
        fs << "ft::vector<int> ft_operator_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);\n";

        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 335, 5, 0, -54};\n";
        fs << "int range_array_two[] = {144, 335, 77, 0, -54};\n";
        fs << "std::vector<int>::iterator stl_iterator_beg_one(&(range_array_one[0]));\n";
        fs << "std::vector<int>::iterator stl_iterator_beg_two(&(range_array_two[0]));\n";
        fs << "std::vector<int> stl_operator_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);\n";
        fs << "std::vector<int> stl_operator_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);\n";
        fs.close();
    }

    /* Swap */
    {
        int range_array_one[] = {144, 335, 5, 0, -54};
        int range_array_two[] = {47, -98, 58, 611, -4};

        std::vector<int>::iterator stl_iterator_beg_one(&(range_array_one[0]));
        std::vector<int>::iterator stl_iterator_beg_two(&(range_array_two[0]));
        ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));
        ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));

        std::vector<int> stl_swap_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);
        std::vector<int> stl_swap_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);
        ft::vector<int> ft_swap_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);
        ft::vector<int> ft_swap_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);

        std::swap(stl_swap_one, stl_swap_two);
        ft::swap(ft_swap_one, ft_swap_two);

        fs.open("./tester/vectors_output/swap_no_member", std::fstream::in | std::fstream::out | std::fstream::trunc);
        std::cout << ((printVectorAttributes(fs, stl_swap_one, ft_swap_one) == true) ? "[OK]" : "[NOP]");
        std::cout << ((printVectorAttributes(fs, stl_swap_two, ft_swap_two) == true) ? "[OK]" : "[NOP]");

        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 335, 5, 0, -54};\n";
        fs << "int range_array_two[] = {47, -98, 58, 611, -4};       \n";
        fs << "ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));\n";
        fs << "ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));\n";
        fs << "ft::vector<int> ft_swap_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);\n";
        fs << "ft::vector<int> ft_swap_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);\n";

        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 335, 5, 0, -54};\n";
        fs << "int range_array_two[] = {47, -98, 58, 611, -4};\n";
        fs << "std::vector<int>::iterator stl_iterator_beg_one(&(range_array_one[0]));\n";
        fs << "std::vector<int>::iterator stl_iterator_beg_two(&(range_array_two[0]));\n";
        fs << "std::vector<int> stl_swap_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);\n";
        fs << "std::vector<int> stl_swap_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);\n";
        fs.close();       
    }

    std::cout << "\n";
}
