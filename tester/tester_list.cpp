/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester_list.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchallie <rchallie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 00:08:51 by rchallie          #+#    #+#             */
/*   Updated: 2020/12/08 19:43:43 by rchallie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"
#include <list>
#include "../containers/list.hpp"

#include <cmath>

template <class T>
std::string equalContent(
	const std::list<T> & stl_list,
	const ft::list<T> & ft_list
)
{
	typename ft::list<T>::const_iterator ft_it;
	typename std::list<T>::const_iterator stl_it;
	if (ft_list.size() != stl_list.size())
		return ("✘");
	stl_it = stl_list.begin();
	for(ft_it = ft_list.begin(); ft_it != ft_list.end(); ft_it++)
	{
		if (*ft_it != *stl_it)
			return ("✘");
		stl_it++;
	}
	return ("✔");
}

template <class T>
bool printListAttributes(
	std::fstream& fs,
	std::list<T>& stl_list,
	ft::list<T>& ft_list
)
{
	/* STL Values */
	std::string stl_empty = ((stl_list.empty() == 1) ? "true" : "false");
	size_t stl_size = stl_list.size();
	size_t stl_max_size = stl_list.max_size();

	/* FT Values */
	std::string ft_empty = ((ft_list.empty() == 1) ? "true" : "false");
	size_t ft_size = ft_list.size();
	size_t ft_max_size = ft_list.max_size();

	/* FT Result compare values */
	bool empty = equalbool(ft_empty, stl_empty);
	bool size = equalbool(ft_size, stl_size);
	bool max_size = equalbool(ft_max_size, stl_max_size);
	std::string content = equalContent(stl_list, ft_list);
	
	fs << "\n══════════════════════════════════════════════════════════════\n";
	fs << "lists attributes : \n";
	fs << "STL : \n";
	fs << "Empty       : " << stl_empty  << std::endl;
	fs << "Size        : " << stl_size  << std::endl;
	fs << "Max size    : " << stl_max_size  << std::endl;
	fs << "Content     : [";
	
	typename std::list<T>::const_iterator stl_it;
	for (stl_it = stl_list.begin();  stl_it != stl_list.end(); stl_it++)
	{
		fs << *stl_it;
		fs << ", ";
	}
	fs << "]\n";

	fs << std::endl;

	fs << "FT : \n";
	fs << "Empty    [" << equal(ft_empty, stl_empty) << "]: " << ft_empty  << std::endl;
	fs << "Size     [" << equal(ft_size, stl_size) << "]: " << ft_size  << std::endl;
	fs << "Max size [" << equal(ft_max_size, stl_max_size) << "]: " << ft_max_size  << std::endl;

	fs << "Content  [" << content << "]: [";

	typename ft::list<T>::const_iterator ft_it;
	for(ft_it = ft_list.begin(); ft_it != ft_list.end(); ft_it++)
	{
		fs << *ft_it;
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

bool is_negative(const int& value) { return (value < 0); }

struct is_near {
  bool operator() (double first, double second)
  { return (fabs(first-second)<5.0); }
};

void test_list()
{
	std::cout << UNDERLINE << "LIST :\n" << NORMAL ;

	mkdir("./tester/lists_output", 0777);
	
	std::fstream fs;

	/* Constructors */
	std::cout << "Constructors : ";

	/* Default constructor */
	{
		std::list<int> stl_default_list;
		ft::list<int> ft_default_list;

		fs.open("./tester/lists_output/constructor_default", std::fstream::in | std::fstream::out | std::fstream::trunc);
		std::cout << ((printListAttributes(fs, stl_default_list, ft_default_list) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "ft::list<int> ft_default_list;\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "std::list<int> stl_default_list;\n";
		fs.close();     
	}

	/* Fill constructor */
	{
		std::list<int> stl_fill_list(10, 42);
		ft::list<int> ft_fill_list(10, 42);

		fs.open("./tester/lists_output/constructor_fill", std::fstream::in | std::fstream::out | std::fstream::trunc);
		std::cout << ((printListAttributes(fs, stl_fill_list, ft_fill_list) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "ft::list<int> ft_fill_list(10, 42);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "std::list<int> stl_fill_list(10, 42);\n";
		fs.close();    
	}

	/* Range constructor */
	{
		int range[] = {4152, -895, 84, -42, 1};

		std::list<int> stl_list;
		ft::list<int> ft_list;

		for (int i = 0; i < 5; i++)
		{
			stl_list.push_back(range[i]);
			ft_list.push_back(range[i]);
		}

		std::list<int> stl_list_range(stl_list.begin(), stl_list.end());
		ft::list<int> ft_list_range(ft_list.begin(), ft_list.end());

		fs.open("./tester/lists_output/constructor_range", std::fstream::in | std::fstream::out | std::fstream::trunc);
		std::cout << ((printListAttributes(fs, stl_list_range, ft_list_range) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {4152, -895, 84, -42, 1};\n";
		fs << "ft::list<int> ft_list;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_list.push_back(range[i]);\n";
		fs << "ft::list<int> ft_list_range(ft_list.begin(), ft_list.end());\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {4152, -895, 84, -42, 1};\n";
		fs << "std::list<int> stl_list;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_list.push_back(range[i]);\n";
		fs << "std::list<int> stl_list_range(stl_list.begin(), stl_list.end());\n";
		fs.close();     
	}

	/* Copy constructor */
	{
		int range[] = {145, 32555, 9657, 4878, -8};

		std::list<int> stl_list;
		ft::list<int> ft_list;

		for (int i = 0; i < 5; i++)
		{
			stl_list.push_back(range[i]);
			ft_list.push_back(range[i]);
		}

		fs.open("./tester/lists_output/constructor_copy", std::fstream::in | std::fstream::out | std::fstream::trunc);

		std::list<int> stl_copy(stl_list);
		ft::list<int> ft_copy(ft_list);

		std::cout << ((printListAttributes(fs, stl_copy, ft_copy) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {145, 32555, 9657, 4878, -8};\n";
		fs << "ft::list<int> ft_list;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_list.push_back(range[i]);\n";
		fs << "ft::list<int> ft_copy(ft_list);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {145, 32555, 9657, 4878, -8};\n";
		fs << "std::list<int> stl_list;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_list.push_back(range[i]);\n";
		fs << "std::list<int> stl_copy(stl_list);\n";
		fs.close();
	}

	/* Operator assignation */
	{
		int range[] = {117, -965, -785, -632, 65};

		std::list<int> stl_list;
		ft::list<int> ft_list;

		for (int i = 0; i < 5; i++)
		{
			stl_list.push_back(range[i]);
			ft_list.push_back(range[i]);
		}

		fs.open("./tester/lists_output/operator_assign", std::fstream::in | std::fstream::out | std::fstream::trunc);

		std::list<int> stl_assign = stl_list;
		ft::list<int> ft_assign = ft_list;

		std::cout << ((printListAttributes(fs, stl_assign, ft_assign) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {117, -965, -785, -632, 65};\n";
		fs << "ft::list<int> ft_list;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_list.push_back(range[i]);\n";
		fs << "ft::list<int> ft_assign = ft_list;\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {117, -965, -785, -632, 65};\n";
		fs << "std::list<int> stl_list;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_list.push_back(range[i]);\n";
		fs << "std::list<int> stl_assign = stl_list;\n";
		fs.close();
	}

	std::cout << "\n";
	std::cout << "Iterators : ";

	/* begin() */
	{
		int range[] = {4, -9854, 75554, 12, -36};

		std::list<int> stl_list;
		ft::list<int> ft_list;

		for (int i = 0; i < 5; i++)
		{
			stl_list.push_back(range[i]);
			ft_list.push_back(range[i]);
		}

		fs.open("./tester/lists_output/begin", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printListAttributes(fs, stl_list, ft_list);
		std::cout << ((printSingleValue(fs, *stl_list.begin(), *ft_list.begin()) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {4, -9854, 75554, 12, -36};\n";
		fs << "ft::list<int> ft_list;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_list.push_back(range[i]);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {4, -9854, 75554, 12, -36};\n";
		fs << "std::list<int> stl_list;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_list.push_back(range[i]);\n";
		fs.close();  
	}

	/* Const begin() */
	{
		const int range[] = {4, -9854, 75554, 12, -36};

		std::list<int> stl_list;
		ft::list<int> ft_list;

		for (int i = 0; i < 5; i++)
		{
			stl_list.push_back(range[i]);
			ft_list.push_back(range[i]);
		}

		std::list<int>::const_iterator stl_const_it = stl_list.begin();
		ft::list<int>::const_iterator ft_const_it = ft_list.begin();

		const int stl_begin = *stl_const_it;
		const int ft_begin = *ft_const_it;

		fs.open("./tester/lists_output/begin_const", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printListAttributes(fs, stl_list, ft_list);
		std::cout << ((printSingleValue(fs, stl_begin, ft_begin) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range[] = {4, -9854, 75554, 12, -36};\n";
		fs << "ft::list<int> ft_list;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_list.push_back(range[i]);\n";
		fs << "ft::list<int>::const_iterator ft_const_it = ft_list.begin();\n";
		fs << "const int ft_begin = *ft_const_it;\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range[] = {4, -9854, 75554, 12, -36};\n";
		fs << "std::list<int> stl_list;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_list.push_back(range[i]);\n";
		fs << "std::list<int>::const_iterator stl_const_it = stl_list.begin();\n";
		fs << "const int stl_begin = *stl_const_it;\n";
		fs.close();
	}

	/* end() */
	{
		int range[] = {485, 1452, -985, 44, 6};

		std::list<int> stl_list;
		ft::list<int> ft_list;

		for (int i = 0; i < 5; i++)
		{
			stl_list.push_back(range[i]);
			ft_list.push_back(range[i]);
		}

		fs.open("./tester/lists_output/end", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printListAttributes(fs, stl_list, ft_list);

		int stl_test = *(--(stl_list.end()));
		int ft_test = *(--(ft_list.end()));

		std::cout << ((printSingleValue(fs, stl_test, ft_test) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {485, 1452, -985, 44, 6};\n";
		fs << "ft::list<int> ft_list;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_list.push_back(range[i]);\n";
		fs << "int ft_test = *(--(ft_list.end()));\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {485, 1452, -985, 44, 6};\n";
		fs << "std::list<int> stl_list;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_list.push_back(range[i]);\n";
		fs << "int stl_test = *(--(stl_list.end()));\n";
		fs.close();  
	}

	/* Const end() */
	{
		const int range[] = {4, -9854, 75554, 12, -36};

		std::list<int> stl_list;
		ft::list<int> ft_list;

		for (int i = 0; i < 5; i++)
		{
			stl_list.push_back(range[i]);
			ft_list.push_back(range[i]);
		}

		std::list<int>::const_iterator stl_const_it = stl_list.end();
		ft::list<int>::const_iterator ft_const_it = ft_list.end();

		const int stl_end = *(--stl_const_it);
		const int ft_end = *(--ft_const_it);

		fs.open("./tester/lists_output/end_const", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printListAttributes(fs, stl_list, ft_list);
		std::cout << ((printSingleValue(fs, stl_end, ft_end) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range[] = {4, -9854, 75554, 12, -36};\n";
		fs << "ft::list<int> ft_list;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_list.push_back(range[i]);\n";
		fs << "ft::list<int>::const_iterator ft_const_it = ft_list.end();\n";
		fs << "const int ft_end = *(--ft_const_it);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range[] = {4, -9854, 75554, 12, -36};\n";
		fs << "std::list<int> stl_list;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_list.push_back(range[i]);\n";
		fs << "std::list<int>::const_iterator stl_const_it = stl_list.end();\n";
		fs << "const int stl_end = *(--stl_const_it);\n";
		fs.close();
	}

	/* rbegin() */
	{
		int range[] = {147, 842, -364, 84, 5};

		std::list<int> stl_list;
		ft::list<int> ft_list;

		for (int i = 0; i < 5; i++)
		{
			stl_list.push_back(range[i]);
			ft_list.push_back(range[i]);
		}

		fs.open("./tester/lists_output/reverse_begin", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printListAttributes(fs, stl_list, ft_list);

		int stl_test = *stl_list.rbegin();
		int ft_test = *ft_list.rbegin();

		std::cout << ((printSingleValue(fs, stl_test, ft_test) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {147, 842, -364, 84, 5};\n";
		fs << "ft::list<int> ft_list;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_list.push_back(range[i]);\n";
		fs << "int ft_test = *ft_list.rbegin();\n";
		fs << "\nCompared with:\n";
		fs << "int range[] = {147, 842, -364, 84, 5};\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "std::list<int> stl_list;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_list.push_back(range[i]);\n";
		fs << "int stl_test = *stl_list.rbegin();\n";
		fs.close();   
	}

	/* Const rbegin() */
	{
		const int range[] = {145, 6521, -985, 6, -9};

		std::list<int> stl_list;
		ft::list<int> ft_list;

		for (int i = 0; i < 5; i++)
		{
			stl_list.push_back(range[i]);
			ft_list.push_back(range[i]);
		}

		std::list<int>::reverse_iterator stl_const_it = stl_list.rbegin();
		ft::list<int>::reverse_iterator ft_const_it = ft_list.rbegin();

		const int stl_rbegin = *stl_const_it;
		const int ft_rbegin = *ft_const_it;

		fs.open("./tester/lists_output/reverse_begin_const", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printListAttributes(fs, stl_list, ft_list);
		std::cout << ((printSingleValue(fs, stl_rbegin, ft_rbegin) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range[] = {145, 6521, -985, 6, -9};\n";
		fs << "ft::list<int> ft_list;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_list.push_back(range[i]);\n";
		fs << "ft::list<int>::reverse_iterator ft_const_it = ft_list.rbegin();\n";
		fs << "const int ft_rbegin = *ft_const_it;\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range[] = {145, 6521, -985, 6, -9};\n";
		fs << "std::list<int> stl_list;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_list.push_back(range[i]);\n";
		fs << "std::list<int>::reverse_iterator stl_const_it = stl_list.rbegin();\n";
		fs << "const int stl_rbegin = *stl_const_it;\n";
		fs.close();
	}

	/* rend() */
	{
		int range[] = {148, 21, -984, 58, 6};

		std::list<int> stl_list;
		ft::list<int> ft_list;

		for (int i = 0; i < 5; i++)
		{
			stl_list.push_back(range[i]);
			ft_list.push_back(range[i]);
		}

		fs.open("./tester/lists_output/reverse_end", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printListAttributes(fs, stl_list, ft_list);

		int stl_test = *(--(stl_list.rend()));
		int ft_test = *(--(ft_list.rend()));

		std::cout << ((printSingleValue(fs, stl_test, ft_test) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {148, 21, -984, 58, 6};\n";
		fs << "ft::list<int> ft_list;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_list.push_back(range[i]);\n";
		fs << "int ft_test = *(--(ft_list.rend()));\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {148, 21, -984, 58, 6};\n";
		fs << "std::list<int> stl_list;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_list.push_back(range[i]);\n";
		fs << "int stl_test = *(--(stl_list.rend()));\n";
		fs.close();  
	}

	/* Const rend() */
	{
		const int range[] = {145, 842, -95, 32, 5};

		std::list<int> stl_list;
		ft::list<int> ft_list;

		for (int i = 0; i < 5; i++)
		{
			stl_list.push_back(range[i]);
			ft_list.push_back(range[i]);
		}

		std::list<int>::const_reverse_iterator stl_const_it = stl_list.rend();
		ft::list<int>::const_reverse_iterator ft_const_it = ft_list.rend();

		const int stl_rend = *(--stl_const_it);
		const int ft_rend = *(--ft_const_it);

		fs.open("./tester/lists_output/reverse_end_const", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printListAttributes(fs, stl_list, ft_list);
		std::cout << ((printSingleValue(fs, stl_rend, ft_rend) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range[] = {145, 842, -95, 32, 5};\n";
		fs << "ft::list<int> ft_list;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_list.push_back(range[i]);\n";
		fs << "ft::list<int>::const_reverse_iterator ft_const_it = ft_list.rend();\n";
		fs << "const int ft_rend = *(--ft_const_it);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range[] = {145, 842, -95, 32, 5};\n";
		fs << "std::list<int> stl_list;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_list.push_back(range[i]);\n";
		fs << "std::list<int>::const_reverse_iterator stl_const_it = stl_list.rend();\n";
		fs << "const int stl_rend = *(--stl_const_it);\n";
		fs.close();
	}

	std::cout << "\n";
	std::cout << "Capacity : ";

	/* Empty true */
	{
		std::list<int> stl_default_list;
		ft::list<int> ft_default_list;

		fs.open("./tester/lists_output/empty_true", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printListAttributes(fs, stl_default_list, ft_default_list);
		std::cout << ((printBoolResult(fs, stl_default_list.empty(), ft_default_list.empty()) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "ft::list<int> ft_default_list;\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "std::list<int> stl_default_list;\n";
		fs.close();  
	}

	/* Empty false */
	{
		std::list<int> stl_default_list(10, 42);
		ft::list<int> ft_default_list(10, 42);

		fs.open("./tester/lists_output/empty_false", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printListAttributes(fs, stl_default_list, ft_default_list);
		std::cout << ((printBoolResult(fs, stl_default_list.empty(), ft_default_list.empty()) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "ft::list<int> ft_default_list(10, 42);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "std::list<int> stl_default_list(10, 42);\n";
		fs.close();  
	}

	/* Size */
	{
		std::list<int> stl_default_list(4245, 42);
		ft::list<int> ft_default_list(4245, 42);

		fs.open("./tester/lists_output/size", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printListAttributes(fs, stl_default_list, ft_default_list);
		std::cout << ((printSingleValue(fs, stl_default_list.size(), ft_default_list.size()) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "ft::list<int> ft_default_list(4245, 42);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "std::list<int> stl_default_list(4245, 42);\n";
		fs.close();  
	}

	/* Size after remove */
	{

	}

	/* Max size */
	{
		std::list<int> stl_default_list;
		ft::list<int> ft_default_list;

		fs.open("./tester/lists_output/max_size", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printListAttributes(fs, stl_default_list, ft_default_list);
		std::cout << ((printSingleValue(fs, stl_default_list.max_size(), ft_default_list.max_size()) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "ft::list<int> ft_default_list;\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "std::list<int> stl_default_list;\n";
		fs.close();  
	}

	std::cout << "\n";
	std::cout << "Element access : ";

	/* Front */
	{
		int range[] = {485, 1452, -985, 44, 6};

		std::list<int> stl_list;
		ft::list<int> ft_list;

		for (int i = 0; i < 5; i++)
		{
			stl_list.push_back(range[i]);
			ft_list.push_back(range[i]);
		}

		fs.open("./tester/lists_output/front", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printListAttributes(fs, stl_list, ft_list);
		std::cout << ((printSingleValue(fs, stl_list.front(), ft_list.front()) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {485, 1452, -985, 44, 6};\n";
		fs << "ft::list<int> ft_list;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_list.push_back(range[i]);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {485, 1452, -985, 44, 6};\n";
		fs << "std::list<int> stl_list;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_list.push_back(range[i]);\n";
		fs.close(); 
	}

	/* Back */
	{
		int range[] = {236, 548, -8, -744, 325};

		std::list<int> stl_list;
		ft::list<int> ft_list;

		for (int i = 0; i < 5; i++)
		{
			stl_list.push_back(range[i]);
			ft_list.push_back(range[i]);
		}

		fs.open("./tester/lists_output/back", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printListAttributes(fs, stl_list, ft_list);
		std::cout << ((printSingleValue(fs, stl_list.back(), ft_list.back()) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {236, 548, -8,-744, 325};\n";
		fs << "ft::list<int> ft_list;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_list.push_back(range[i]);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {236, 548, -8,-744, 325};\n";
		fs << "std::list<int> stl_list;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_list.push_back(range[i]);\n";
		fs.close(); 
	}

	std::cout << "\n";
	std::cout << "Modifier : ";
	
	/* Assign Range */
	{
		int range[] = {65, 423, -874, 57, 963};

		std::list<int> stl_list(40, 22);
		ft::list<int> ft_list(40, 22);

		std::list<int> stl_range;
		ft::list<int> ft_range;  

		for (int i = 0; i < 5; i++)
		{
			stl_range.push_back(range[i]);
			ft_range.push_back(range[i]);
		}

		fs.open("./tester/lists_output/assign_range", std::fstream::in | std::fstream::out | std::fstream::trunc);
		
		printListAttributes(fs, stl_list, ft_list);

		stl_list.assign(stl_range.begin(), stl_range.end());
		ft_list.assign(ft_range.begin(), ft_range.end());
		
		std::cout << ((printListAttributes(fs, stl_list, ft_list) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {65, 423, -874, 57, 963};\n";
		fs << "ft::list<int> ft_list;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_range.push_back(range[i]);\n";
		fs << "Sending output...\n";
		fs << "ft_list.assign(ft_range.begin(), ft_range.end());\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {65, 423, -874, 57, 963};\n";
		fs << "std::list<int> stl_list;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_range.push_back(range[i]);\n";
		fs << "Sending output...\n";
		fs << "stl_list.assign(stl_range.begin(), stl_range.end());\n";
		fs.close(); 

	}

	/* Assign fill */
	{
		int range[] = {14, 85, -694, 753, 658};

		std::list<int> stl_list;
		ft::list<int> ft_list;

		for (int i = 0; i < 5; i++)
		{
			stl_list.push_back(range[i]);
			ft_list.push_back(range[i]);
		}

		fs.open("./tester/lists_output/assign_fill", std::fstream::in | std::fstream::out | std::fstream::trunc);
		
		printListAttributes(fs, stl_list, ft_list);

		stl_list.assign(19, 42);
		ft_list.assign(19, 42);
		
		std::cout << ((printListAttributes(fs, stl_list, ft_list) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {14, 85, -694, 753, 658};\n";
		fs << "ft::list<int> ft_list;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_list.push_back(range[i]);\n";
		fs << "Sending output...\n";
		fs << "ft_list.assign(19, 42);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {14, 85, -694, 753, 658};\n";
		fs << "std::list<int> stl_list;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_list.push_back(range[i]);\n";
		fs << "Sending output...\n";
		fs << "stl_list.assign(19, 42);\n";
		fs.close(); 
	}

	/* Push front */
	{
		int range[] = {5, -9841, 578, 65, -24};

		std::list<int> stl_list;
		ft::list<int> ft_list;

		for (int i = 0; i < 5; i++)
		{
			stl_list.push_front(range[i]);
			ft_list.push_front(range[i]);
		}

		fs.open("./tester/lists_output/push_front", std::fstream::in | std::fstream::out | std::fstream::trunc);
		std::cout << ((printListAttributes(fs, stl_list, ft_list) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {5, -9841, 578, 65, -24};\n";
		fs << "ft::list<int> ft_list;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_list.push_front(range[i]);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {5, -9841, 578, 65, -24};\n";
		fs << "std::list<int> stl_list;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_list.push_front(range[i]);\n";
		fs.close(); 
	}

	/* Pop front */
	{
		int range[] = {24, 9855, -321, 65, 49};

		std::list<int> stl_list;
		ft::list<int> ft_list;

		for (int i = 0; i < 5; i++)
		{
			stl_list.push_back(range[i]);
			ft_list.push_back(range[i]);
		}

		fs.open("./tester/lists_output/pop_front", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printListAttributes(fs, stl_list, ft_list);
		
		stl_list.pop_front();
		ft_list.pop_front();
		
		std::cout << ((printListAttributes(fs, stl_list, ft_list) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {24, 9855, -321, 65, 49};\n";
		fs << "ft::list<int> ft_list;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_list.push_back(range[i]);\n";
		fs << "Sending output...\n";
		fs << "ft_list.pop_front();\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {24, 9855, -321, 65, 49};\n";
		fs << "std::list<int> stl_list;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_list.push_back(range[i]);\n";
		fs << "Sending output...\n";
		fs << "stl_list.pop_front();\n";
		fs.close(); 
	}

	/* Push_back */
	{
		int range[] = {-874, 844, 5, 12, 63};

		std::list<int> stl_list;
		ft::list<int> ft_list;

		for (int i = 0; i < 5; i++)
		{
			stl_list.push_back(range[i]);
			ft_list.push_back(range[i]);
		}

		fs.open("./tester/lists_output/push_back", std::fstream::in | std::fstream::out | std::fstream::trunc);
		std::cout << ((printListAttributes(fs, stl_list, ft_list) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {-874, 844, 5, 12, 63};\n";
		fs << "ft::list<int> ft_list;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_list.push_back(range[i]);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {-874, 844, 5, 12, 63};\n";
		fs << "std::list<int> stl_list;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_list.push_back(range[i]);\n";
		fs.close(); 
	}

	/* Pop back */
	{
		int range[] = {-874, 844, 5, 12, 63};

		std::list<int> stl_list;
		ft::list<int> ft_list;

		for (int i = 0; i < 5; i++)
		{
			stl_list.push_back(range[i]);
			ft_list.push_back(range[i]);
		}

		fs.open("./tester/lists_output/pop_back", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printListAttributes(fs, stl_list, ft_list);
		
		stl_list.pop_back();
		ft_list.pop_back();
		
		std::cout << ((printListAttributes(fs, stl_list, ft_list) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {-874, 844, 5, 12, 63};\n";
		fs << "ft::list<int> ft_list;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_list.push_back(range[i]);\n";
		fs << "Sending output...\n";
		fs << "ft_list.pop_back();\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {-874, 844, 5, 12, 63};\n";
		fs << "std::list<int> stl_list;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_list.push_back(range[i]);\n";
		fs << "Sending output...\n";
		fs << "stl_list.pop_back();\n";
		fs.close(); 
	}

	/* Insert single */
	{
		int range[] = {9657, 842, 1, 4, -999};

		std::list<int> stl_list;
		ft::list<int> ft_list;

		for (int i = 0; i < 5; i++)
		{
			stl_list.push_back(range[i]);
			ft_list.push_back(range[i]);
		}

		fs.open("./tester/lists_output/insert_single", std::fstream::in | std::fstream::out | std::fstream::trunc);
		
		std::list<int>::iterator stl_it = stl_list.begin();
		ft::list<int>::iterator ft_it = ft_list.begin();

		for (int i = 0; i < 3; i++)
		{
			stl_it++;
			ft_it++;
		}

		stl_list.insert(stl_it, 42);
		ft_list.insert(ft_it, 42);

		std::cout << ((printListAttributes(fs, stl_list, ft_list) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {9657, 842, 1, 4, -999};\n";
		fs << "ft::list<int> ft_list;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_list.push_back(range[i]);\n";
		fs << "ft::list<int>::iterator ft_it = ft_list.begin();\n";
		fs << "for (int i = 0; i < 3; i++)\n";
		fs << "    ft_it++;\n";
		fs << "ft_list.insert(ft_it, 42);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {9657, 842, 1, 4, -999};\n";
		fs << "std::list<int> stl_list;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_list.push_back(range[i]);\n";
		fs << "std::list<int>::iterator stl_it = stl_list.begin();\n";
		fs << "for (int i = 0; i < 3; i++)\n";
		fs << "    stl_it++;\n";
		fs << "stl_list.insert(stl_it, 42);\n";
		fs.close(); 
	}

	/* Insert fill */
	{
		int range[] = {426, 351, -957, 684, -852465173};

		std::list<int> stl_list;
		ft::list<int> ft_list;

		for (int i = 0; i < 5; i++)
		{
			stl_list.push_back(range[i]);
			ft_list.push_back(range[i]);
		}

		fs.open("./tester/lists_output/insert_fill", std::fstream::in | std::fstream::out | std::fstream::trunc);
		
		std::list<int>::iterator stl_it = stl_list.begin();
		ft::list<int>::iterator ft_it = ft_list.begin();

		for (int i = 0; i < 1; i++)
		{
			stl_it++;
			ft_it++;
		}

		stl_list.insert(stl_it, 10, 42);
		ft_list.insert(ft_it, 10, 42);

		std::cout << ((printListAttributes(fs, stl_list, ft_list) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {426, 351, -957, 684, -852465173};\n";
		fs << "ft::list<int> ft_list;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_list.push_back(range[i]);\n";
		fs << "ft::list<int>::iterator ft_it = ft_list.begin();\n";
		fs << "for (int i = 0; i < 1; i++)\n";
		fs << "    ft_it++;\n";
		fs << "ft_list.insert(ft_it, 10, 42);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {426, 351, -957, 684, -852465173};\n";
		fs << "std::list<int> stl_list;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_list.push_back(range[i]);\n";
		fs << "std::list<int>::iterator stl_it = stl_list.begin();\n";
		fs << "for (int i = 0; i < 1; i++)\n";
		fs << "    stl_it++;\n";
		fs << "stl_list.insert(stl_it, 10, 42);\n";
		fs.close();
	}

	/* Insert range */
	{
		int range[] = {147, 852, -369, 45, 98};

		std::list<int> stl_list;
		ft::list<int> ft_list;

		for (int i = 0; i < 5; i++)
		{
			stl_list.push_back(range[i]);
			ft_list.push_back(range[i]);
		}

		fs.open("./tester/lists_output/insert_range", std::fstream::in | std::fstream::out | std::fstream::trunc);
		
		std::list<int> stl_test;
		ft::list<int> ft_test;

		stl_test.insert(stl_test.begin(), stl_list.begin(), stl_list.end());
		ft_test.insert(ft_test.begin(), ft_list.begin(), ft_list.end());

		std::cout << ((printListAttributes(fs, stl_test, ft_test) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {147, 852, -369, 45, 98};\n";
		fs << "ft::list<int> ft_list;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_list.push_back(range[i]);\n";
		fs << "ft::list<int> ft_test;\n";
		fs << "ft_test.insert(ft_test.begin(), ft_list.begin(), ft_list.end());\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {147, 852, -369, 45, 98};\n";
		fs << "std::list<int> stl_list;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_list.push_back(range[i]);\n";
		fs << "std::list<int> stl_test;\n";
		fs << "stl_test.insert(stl_test.begin(), stl_list.begin(), stl_list.end());\n";
		fs.close();
	}

	/* Erase single */
	{
		int range[] = {147, 951, 753, -675, -316};

		std::list<int> stl_list;
		ft::list<int> ft_list;

		for (int i = 0; i < 5; i++)
		{
			stl_list.push_back(range[i]);
			ft_list.push_back(range[i]);
		}

		fs.open("./tester/lists_output/erase_single", std::fstream::in | std::fstream::out | std::fstream::trunc);

		std::list<int>::iterator stl_it = stl_list.begin();
		ft::list<int>::iterator ft_it = ft_list.begin();

		for (int i = 0; i < 2; i++)
		{
			stl_it++;
			ft_it++;
		}

		stl_list.erase(stl_it);
		ft_list.erase(ft_it);

		std::cout << ((printListAttributes(fs, stl_list, ft_list) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {147, 951, 753, -675, -316};\n";
		fs << "ft::list<int> ft_list;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_list.push_back(range[i]);\n";
		fs << "ft::list<int>::iterator ft_it = ft_list.begin();\n";
		fs << "for (int i = 0; i < 2; i++)\n";
		fs << "    ft_it++;\n";
		fs << "ft_list.erase(ft_it);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {147, 951, 753, -675, -316};\n";
		fs << "std::list<int> stl_list;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_list.push_back(range[i]);\n";
		fs << "std::list<int>::iterator stl_it = stl_list.begin();\n";
		fs << "for (int i = 0; i < 2; i++)\n";
		fs << "    stl_it++;\n";
		fs << "stl_list.erase(stl_it);\n";
		fs.close();
	}

	/* Erase range */
	{
		std::list<int> stl_list(20, 42);
		ft::list<int> ft_list(20, 42);

		fs.open("./tester/lists_output/erase_range", std::fstream::in | std::fstream::out | std::fstream::trunc);

		std::list<int>::iterator stl_it_beg = stl_list.begin();
		ft::list<int>::iterator ft_it_beg = ft_list.begin();
		std::list<int>::iterator stl_it_end = stl_list.end();
		ft::list<int>::iterator ft_it_end = ft_list.end();

		for (int i = 0; i < 5; i++)
		{
			stl_it_beg++;
			ft_it_beg++;
			stl_it_end--;
			ft_it_end--;
		}

		stl_list.erase(stl_it_beg, stl_it_end);
		ft_list.erase(ft_it_beg, ft_it_end);

		std::cout << ((printListAttributes(fs, stl_list, ft_list) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "ft::list<int> ft_list(20, 42);\n";
		fs << "ft::list<int>::iterator ft_it_beg = ft_list.begin();\n";
		fs << "ft::list<int>::iterator ft_it_end = ft_list.end();\n";
		fs << "for (int i = 0; i < 5; i++);\n";
		fs << "{\n";
		fs << "    ft_it_beg++;\n";
		fs << "    ft_it_end--;\n";
		fs << "}\n";
		fs << "ft_list.erase(ft_it_beg, ft_it_end);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "std::list<int> stl_list(20, 42);\n";
		fs << "std::list<int>::iterator stl_it_beg = stl_list.begin();\n";
		fs << "std::list<int>::iterator stl_it_end = stl_list.end();\n";
		fs << "for (int i = 0; i < 5; i++);\n";
		fs << "{\n";
		fs << "    stl_it_beg++;\n";
		fs << "    stl_it_end--;\n";
		fs << "}\n";
		fs << "ft_list.erase(ft_it_beg, ft_it_end);\n";
		fs.close();
	}

	/* Swap member */
	{
		std::list<int> stl_swap_one(10, 42);
		ft::list<int> ft_swap_one(10, 42);
		std::list<int> stl_swap_tow(24, 19);
		ft::list<int> ft_swap_tow(24, 19);

		fs.open("./tester/lists_output/swap_member", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printListAttributes(fs, stl_swap_one, ft_swap_one);
		printListAttributes(fs, stl_swap_tow, ft_swap_tow);

		stl_swap_one.swap(stl_swap_tow);
		ft_swap_one.swap(ft_swap_tow);

		std::cout << ((printListAttributes(fs, stl_swap_one, ft_swap_one) == true) ? "[OK]" : "[NOP]");
		std::cout << ((printListAttributes(fs, stl_swap_tow, ft_swap_tow)  == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "ft::list<int> ft_swap_one(10, 42);\n";
		fs << "ft::list<int> ft_swap_tow(24, 19);\n";
		fs << "Sending output of swap_one...\n";
		fs << "ft_swap_one.swap(ft_swap_tow);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "std::list<int> stl_swap_one(10, 42);\n";
		fs << "std::list<int> stl_swap_tow(24, 19);\n";
		fs << "Sending output of swap_two...\n";
		fs << "stl_swap_one.swap(stl_swap_tow);\n";
		fs.close();
	}

	/* Resize extension */
	{
		std::list<int> stl_fill_list(10, 42);
		ft::list<int> ft_fill_list(10, 42);

		fs.open("./tester/lists_output/resize_extension", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printListAttributes(fs, stl_fill_list, ft_fill_list);

		stl_fill_list.resize(42, 19);
		ft_fill_list.resize(42, 19);

		std::cout << ((printListAttributes(fs, stl_fill_list, ft_fill_list) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "ft::list<int> ft_fill_list(10, 42);\n";
		fs << "Sending Output...\n";
		fs << "ft_fill_list.resize(42, 19);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "std::list<int> stl_fill_list(10, 42);\n";
		fs << "Sending Output...\n";
		fs << "stl_fill_list.resize(42, 19);\n";
		fs.close();   
	}

	/* Resize reduction */
	{
		std::list<int> stl_fill_list(39, 45);
		ft::list<int> ft_fill_list(39, 45);

		fs.open("./tester/lists_output/resize_reduction", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printListAttributes(fs, stl_fill_list, ft_fill_list);

		stl_fill_list.resize(14, 18);
		ft_fill_list.resize(14, 18);

		std::cout << ((printListAttributes(fs, stl_fill_list, ft_fill_list) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "ft::list<int> ft_fill_list(39, 45);\n";
		fs << "Sending Output...\n";
		fs << "ft_fill_list.resize(14, 18);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "std::list<int> stl_fill_list(39, 45);\n";
		fs << "Sending Output...\n";
		fs << "stl_fill_list.resize(14, 18);\n";
		fs.close();  
	}

	/* Clear */
	{
		std::list<int> stl_fill_list(10, 42);
		ft::list<int> ft_fill_list(10, 42);

		fs.open("./tester/lists_output/clear", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printListAttributes(fs, stl_fill_list, ft_fill_list);

		stl_fill_list.clear();
		ft_fill_list.clear();
		
		std::cout << ((printListAttributes(fs, stl_fill_list, ft_fill_list) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "ft::list<int> ft_fill_list;\n";
		fs << "Sending output...\n";
		fs << "ft_fill_list.clear();\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "std::list<int> stl_fill_list;\n";
		fs << "Sending output...\n";
		fs << "stl_fill_list.clear();\n";
		fs.close();  
	}

	std::cout << "\n";
	std::cout << "Operation : ";

	/* Splice entire list */
	{
		int range[] = {251, -955, 5742, 3, -64};

		std::list<int> stl_list;
		ft::list<int> ft_list;

		std::list<int> stl_list_sec;
		ft::list<int> ft_list_sec;

		for (int i = 0; i < 5; i++)
		{
			stl_list.push_back(range[i]);
			ft_list.push_back(range[i]);
			stl_list_sec.push_back(range[i] + 666);
			ft_list_sec.push_back(range[i] + 666);
		}

		fs.open("./tester/lists_output/splice_entire", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printListAttributes(fs, stl_list, ft_list);

		std::list<int>::iterator stl_list_it = stl_list.begin();
		ft::list<int>::iterator ft_list_it = ft_list.begin();

		for (int i = 0; i < 3; i++)
		{
			stl_list_it++;
			ft_list_it++;
		}

		stl_list.splice(stl_list_it, stl_list_sec);
		ft_list.splice(ft_list_it, ft_list_sec);

		std::cout << ((printListAttributes(fs, stl_list, ft_list) == true) ? "[OK]" : "[NOP]");
		std::cout << ((printListAttributes(fs, stl_list_sec, ft_list_sec) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {251, -955, 5742, 3, -64};\n";
		fs << "ft::list<int> ft_list;\n";
		fs << "ft::list<int> ft_list_sec;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "{\n";
		fs << "    ft_list.push_back(range[i]);\n";
		fs << "    ft_list_sec.push_back(range[i] + 666);\n";
		fs << "}\n";
		fs << "Sending Output ft_list...\n";
		fs << "ft::list<int>::iterator ft_list_it = ft_list.begin();\n";
		fs << "for (int i = 0; i < 3; i++)\n";
		fs << "    ft_list_it++;\n";
		fs << "ft_list.splice(ft_list_it, ft_list_sec);\n";
		fs << "Sending Output ft_list...\n";
		fs << "Sending Output ft_list_sec...\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {251, -955, 5742, 3, -64};\n";
		fs << "std::list<int> stl_list;\n";
		fs << "std::list<int> stl_list_sec;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "{\n";
		fs << "    stl_list.push_back(range[i]);\n";
		fs << "    stl_list_sec.push_back(range[i] + 666);\n";
		fs << "}\n";
		fs << "Sending Output stl_list...\n";
		fs << "std::list<int>::iterator stl_list_it = stl_list.begin();\n";
		fs << "for (int i = 0; i < 3; i++)\n";
		fs << "    stl_list_it++;\n";
		fs << "stl_list.splice(stl_list_it, stl_list_sec);\n";
		fs << "Sending Output stl_list...\n";
		fs << "Sending Output stl_list_sec...\n";        
		fs.close();  
	}

	/* Splice single */
	{
		int range[] = {251, -955, 5742, 3, -64};

		std::list<int> stl_list;
		ft::list<int> ft_list;

		std::list<int> stl_list_sec;
		ft::list<int> ft_list_sec;

		for (int i = 0; i < 5; i++)
		{
			stl_list.push_back(range[i]);
			ft_list.push_back(range[i]);
			stl_list_sec.push_back(range[i] + 666);
			ft_list_sec.push_back(range[i] + 666);
		}

		fs.open("./tester/lists_output/splice_single", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printListAttributes(fs, stl_list, ft_list);

		std::list<int>::iterator stl_list_it = stl_list.begin();
		ft::list<int>::iterator ft_list_it = ft_list.begin();

		for (int i = 0; i < 3; i++)
		{
			stl_list_it++;
			ft_list_it++;
		}

		stl_list.splice(stl_list_it, stl_list_sec, stl_list_sec.begin());
		ft_list.splice(ft_list_it, ft_list_sec, ft_list_sec.begin());

		std::cout << ((printListAttributes(fs, stl_list, ft_list) == true) ? "[OK]" : "[NOP]");
		std::cout << ((printListAttributes(fs, stl_list_sec, ft_list_sec) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {251, -955, 5742, 3, -64};\n";
		fs << "ft::list<int> ft_list;\n";
		fs << "ft::list<int> ft_list_sec;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "{\n";
		fs << "    ft_list.push_back(range[i]);\n";
		fs << "    ft_list_sec.push_back(range[i] + 666);\n";
		fs << "}\n";
		fs << "Sending Output ft_list...\n";
		fs << "ft::list<int>::iterator ft_list_it = ft_list.begin();\n";
		fs << "for (int i = 0; i < 3; i++)\n";
		fs << "    ft_list_it++;\n";
		fs << "ft_list.splice(ft_list_it, ft_list_sec, ft_list_sec.begin());\n";
		fs << "Sending Output ft_list...\n";
		fs << "Sending Output ft_list_sec...\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {251, -955, 5742, 3, -64};\n";
		fs << "std::list<int> stl_list;\n";
		fs << "std::list<int> stl_list_sec;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "{\n";
		fs << "    stl_list.push_back(range[i]);\n";
		fs << "    stl_list_sec.push_back(range[i] + 666);\n";
		fs << "}\n";
		fs << "Sending Output stl_list...\n";
		fs << "std::list<int>::iterator stl_list_it = stl_list.begin();\n";
		fs << "for (int i = 0; i < 3; i++)\n";
		fs << "    stl_list_it++;\n";
		fs << "stl_list.splice(stl_list_it, stl_list_sec, stl_list_sec.begin());\n";
		fs << "Sending Output stl_list...\n";
		fs << "Sending Output stl_list_sec...\n";      
		fs.close();
	}

	/* Splice range */
	{
		int range[] = {147,852,369,-852,95};

		std::list<int> stl_list;
		ft::list<int> ft_list;

		std::list<int> stl_list_sec;
		ft::list<int> ft_list_sec;

		for (int i = 0; i < 5; i++)
		{
			stl_list.push_back(range[i]);
			ft_list.push_back(range[i]);
			stl_list_sec.push_back(range[i] + 666);
			ft_list_sec.push_back(range[i] + 666);
		}

		fs.open("./tester/lists_output/splice_range", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printListAttributes(fs, stl_list, ft_list);

		std::list<int>::iterator stl_list_it = stl_list.begin();
		ft::list<int>::iterator ft_list_it = ft_list.begin();

		for (int i = 0; i < 3; i++)
		{
			stl_list_it++;
			ft_list_it++;
		}

		stl_list.splice(stl_list_it, stl_list_sec, ++(stl_list_sec.begin()), --(stl_list_sec.end()));
		ft_list.splice(ft_list_it, ft_list_sec, ++(ft_list_sec.begin()), --(ft_list_sec.end()));

		std::cout << ((printListAttributes(fs, stl_list, ft_list) == true) ? "[OK]" : "[NOP]");
		std::cout << ((printListAttributes(fs, stl_list_sec, ft_list_sec) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {147,852,369,-852,95};\n";
		fs << "ft::list<int> ft_list;\n";
		fs << "ft::list<int> ft_list_sec;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "{\n";
		fs << "    ft_list.push_back(range[i]);\n";
		fs << "    ft_list_sec.push_back(range[i] + 666);\n";
		fs << "}\n";
		fs << "Sending Output ft_list...\n";
		fs << "ft::list<int>::iterator ft_list_it = ft_list.begin();\n";
		fs << "for (int i = 0; i < 3; i++)\n";
		fs << "    ft_list_it++;\n";
		fs << "ft_list.splice(ft_list_it, ft_list_sec, ++(ft_list_sec.begin()), --(ft_list_sec.end()));\n";
		fs << "Sending Output ft_list...\n";
		fs << "Sending Output ft_list_sec...\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {147,852,369,-852,95};\n";
		fs << "std::list<int> stl_list;\n";
		fs << "std::list<int> stl_list_sec;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "{\n";
		fs << "    stl_list.push_back(range[i]);\n";
		fs << "    stl_list_sec.push_back(range[i] + 666);\n";
		fs << "}\n";
		fs << "Sending Output stl_list...\n";
		fs << "std::list<int>::iterator stl_list_it = stl_list.begin();\n";
		fs << "for (int i = 0; i < 3; i++)\n";
		fs << "    stl_list_it++;\n";
		fs << "stl_list.splice(stl_list_it, stl_list_sec, ++(stl_list_sec.begin()), --(stl_list_sec.end()));\n";
		fs << "Sending Output stl_list...\n";
		fs << "Sending Output stl_list_sec...\n"; 
		fs.close();  
	}

	/* remove */
	{
		int range[] = {4152, -895, 84, -895, -895};

		std::list<int> stl_list;
		ft::list<int> ft_list;

		for (int i = 0; i < 5; i++)
		{
			stl_list.push_back(range[i]);
			ft_list.push_back(range[i]);
		}

		fs.open("./tester/lists_output/remove", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printListAttributes(fs, stl_list, ft_list);
		
		stl_list.remove(-895);
		ft_list.remove(-895);

		std::cout << ((printListAttributes(fs, stl_list, ft_list) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {4152, -895, 84, -895, -895};\n";
		fs << "ft::list<int> ft_list;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_list.push_back(range[i]);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {4152, -895, 84, -895, -895};\n";
		fs << "std::list<int> stl_list;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_list.push_back(range[i]);\n";
		fs.close();  
	}

	/* Remove if */
	{
		int range[] = {147, -985, 854, 96, -2};

		std::list<int> stl_list;
		ft::list<int> ft_list;

		for (int i = 0; i < 5; i++)
		{
			stl_list.push_back(range[i]);
			ft_list.push_back(range[i]);
		}

		fs.open("./tester/lists_output/remove_if", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printListAttributes(fs, stl_list, ft_list);
		
		stl_list.remove_if(is_negative);
		ft_list.remove_if(is_negative);

		std::cout << ((printListAttributes(fs, stl_list, ft_list) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {147, -985, 854, 96, -2};\n";
		fs << "ft::list<int> ft_list;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_list.push_back(range[i]);\n";
		fs << "ft_list.remove_if(is_negative);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {147, -985, 854, 96, -2};\n";
		fs << "std::list<int> stl_list;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_list.push_back(range[i]);\n";
		fs << "stl_list.remove_if(is_negative);\n";
		fs.close();  
	}

	/* unique() */
	{
		int range[] = {12, 52, 52, 52, 48, 52, 996, 996, 7};

		std::list<int> stl_list;
		ft::list<int> ft_list;

		for (int i = 0; i < 9; i++)
		{
			stl_list.push_back(range[i]);
			ft_list.push_back(range[i]);
		}

		fs.open("./tester/lists_output/unique", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printListAttributes(fs, stl_list, ft_list);
		
		stl_list.unique();
		ft_list.unique();

		std::cout << ((printListAttributes(fs, stl_list, ft_list) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {12, 52, 52, 52, 48, 52, 996, 996, 7};\n";
		fs << "ft::list<int> ft_list;\n";
		fs << "for (int i = 0; i < 9; i++)\n";
		fs << "    ft_list.push_back(range[i]);\n";
		fs << "ft_list.unique();\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {12, 52, 52, 52, 48, 52, 996, 996, 7};\n";
		fs << "std::list<int> stl_list;\n";
		fs << "for (int i = 0; i < 9; i++)\n";
		fs << "    stl_list.push_back(range[i]);\n";
		fs << "stl_list.unique();\n";
		fs.close();  
	}

	/* Unique specific */
	{
		int range[] = {8, 12, 58, 42, 45, 46, 99};

		std::list<int> stl_list;
		ft::list<int> ft_list;

		for (int i = 0; i < 7; i++)
		{
			stl_list.push_back(range[i]);
			ft_list.push_back(range[i]);
		}

		fs.open("./tester/lists_output/unique_specific", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printListAttributes(fs, stl_list, ft_list);
		
		stl_list.unique(is_near());
		ft_list.unique(is_near());

		std::cout << ((printListAttributes(fs, stl_list, ft_list) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {8, 12, 58, 42, 45, 46, 99};\n";
		fs << "ft::list<int> ft_list;\n";
		fs << "for (int i = 0; i < 9; i++)\n";
		fs << "    ft_list.push_back(range[i]);\n";
		fs << "ft_list.unique();\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {8, 12, 58, 42, 45, 46, 99};\n";
		fs << "std::list<int> stl_list;\n";
		fs << "for (int i = 0; i < 9; i++)\n";
		fs << "    stl_list.push_back(range[i]);\n";
		fs << "stl_list.unique();\n";
		fs.close();  
	}

	/* Merge */
	{
		int range[] = {8, 12, 58, 42, 45, 46, 99};

		std::list<int> stl_list;
		ft::list<int> ft_list;

		std::list<int> stl_list_two;
		ft::list<int> ft_list_two;

		for (int i = 0; i < 7; i++)
		{
			stl_list.push_back(range[i]);
			ft_list.push_back(range[i]);
			stl_list_two.push_back(range[i] + 42);
			ft_list_two.push_back(range[i] + 42);
		}

		fs.open("./tester/lists_output/merge", std::fstream::in | std::fstream::out | std::fstream::trunc);
		
		stl_list.sort();
		stl_list_two.sort();

		ft_list.sort();
		ft_list_two.sort();

		printListAttributes(fs, stl_list, ft_list);
		printListAttributes(fs, stl_list_two, ft_list_two);

		stl_list.merge(stl_list_two);
		ft_list.merge(ft_list_two);

		std::cout << ((printListAttributes(fs, stl_list, ft_list) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {8, 12, 58, 42, 45, 46, 99};\n";
		fs << "ft::list<int> ft_list;\n";
		fs << "ft::list<int> ft_list_two;\n";
		fs << "for (int i = 0; i < 7; i++)\n";
		fs << "{\n";
		fs << "    ft_list.push_back(range[i]);\n";
		fs << "    ft_list_two.push_back(range[i] + 42);\n";
		fs << "}\n";
		fs << "ft_list.sort();\n";
		fs << "ft_list_two.sort();\n";
		fs << "Sending output...\n";
		fs << "ft_list.merge(ft_list_two);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {8, 12, 58, 42, 45, 46, 99};\n";
		fs << "std::list<int> stl_list;\n";
		fs << "std::list<int> stl_list_two;\n";
		fs << "for (int i = 0; i < 7; i++)\n";
		fs << "{\n";
		fs << "    stl_list.push_back(range[i]);\n";
		fs << "    stl_list_two.push_back(range[i] + 42);\n";
		fs << "}\n";
		fs << "stl_list.sort();\n";
		fs << "stl_list_two.sort();\n";
		fs << "Sending output...\n";
		fs << "stl_list.merge(stl_list_two);\n";
		fs.close();
	}

	/* Merge compare */
	{
		int range[] = {14, -20, 51, 92, 97, 124, 0};

		std::list<int> stl_list;
		ft::list<int> ft_list;

		std::list<int> stl_list_two;
		ft::list<int> ft_list_two;

		for (int i = 0; i < 7; i++)
		{
			stl_list.push_back(range[i]);
			ft_list.push_back(range[i]);
			stl_list_two.push_back(range[i] + 42);
			ft_list_two.push_back(range[i] + 42);
		}

		fs.open("./tester/lists_output/merge_compare", std::fstream::in | std::fstream::out | std::fstream::trunc);
		
		stl_list.sort();
		stl_list_two.sort();

		ft_list.sort();
		ft_list_two.sort();

		printListAttributes(fs, stl_list, ft_list);
		printListAttributes(fs, stl_list_two, ft_list_two);

		stl_list.merge(stl_list_two, std::less<int>());
		ft_list.merge(ft_list_two, std::less<int>());

		std::cout << ((printListAttributes(fs, stl_list, ft_list) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {14, -20, 51, 92, 97, 124, 0};\n";
		fs << "ft::list<int> ft_list;\n";
		fs << "ft::list<int> ft_list_two;\n";
		fs << "for (int i = 0; i < 7; i++)\n";
		fs << "{\n";
		fs << "    ft_list.push_back(range[i]);\n";
		fs << "    ft_list_two.push_back(range[i] + 42);\n";
		fs << "}\n";
		fs << "ft_list.sort();\n";
		fs << "ft_list_two.sort();\n";
		fs << "Sending output...\n";
		fs << "ft_list.merge(ft_list_two, std::less<int>());\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {14, -20, 51, 92, 97, 124, 0};\n";
		fs << "std::list<int> stl_list;\n";
		fs << "std::list<int> stl_list_two;\n";
		fs << "for (int i = 0; i < 7; i++)\n";
		fs << "{\n";
		fs << "    stl_list.push_back(range[i]);\n";
		fs << "    stl_list_two.push_back(range[i] + 42);\n";
		fs << "}\n";
		fs << "stl_list.sort();\n";
		fs << "stl_list_two.sort();\n";
		fs << "Sending output...\n";
		fs << "stl_list.merge(stl_list_two, std::less<int>());\n";
		fs.close();
	}


	/* Sort */
	{
		int range[] = {88, 44, -3, 867, 442};

		std::list<int> stl_list;
		ft::list<int> ft_list;

		for (int i = 0; i < 5; i++)
		{
			stl_list.push_back(range[i]);
			ft_list.push_back(range[i]);
		}

		fs.open("./tester/lists_output/sort", std::fstream::in | std::fstream::out | std::fstream::trunc);
		
		printListAttributes(fs, stl_list, ft_list);

		stl_list.sort();
		ft_list.sort();
		
		std::cout << ((printListAttributes(fs, stl_list, ft_list) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {88, 44, -3, 867, 442};\n";
		fs << "ft::list<int> ft_list;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_list.push_back(range[i]);\n";
		fs << "Sending Output...\n";
		fs << "ft_list.sort();\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {88, 44, -3, 867, 442};\n";
		fs << "std::list<int> stl_list;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_list.push_back(range[i]);\n";
		fs << "Sending Output...\n";
		fs << "stl_list.sort();\n";
		fs.close(); 
	}

	/* Sort compare */
	{
		int range[] = {145, 965, 325, -654, -9};

		std::list<int> stl_list;
		ft::list<int> ft_list;

		for (int i = 0; i < 5; i++)
		{
			stl_list.push_back(range[i]);
			ft_list.push_back(range[i]);
		}

		fs.open("./tester/lists_output/sort_compare", std::fstream::in | std::fstream::out | std::fstream::trunc);
		
		printListAttributes(fs, stl_list, ft_list);

		stl_list.sort(std::less<int>());
		ft_list.sort(std::less<int>());
		
		std::cout << ((printListAttributes(fs, stl_list, ft_list) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {145, 965, 325, 654, 9};\n";
		fs << "ft::list<int> ft_list;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_list.push_back(range[i]);\n";
		fs << "Sending Output...\n";
		fs << "ft_list.sort(std::less<int>());\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {145, 965, 325, 654, 9};\n";
		fs << "std::list<int> stl_list;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_list.push_back(range[i]);\n";
		fs << "Sending Output...\n";
		fs << "stl_list.sort(std::less<int>());\n";
		fs.close(); 
	}

	/* reverse */
	{
		int range[] = {842, 985, -9666, 98, -7};

		std::list<int> stl_list;
		ft::list<int> ft_list;

		for (int i = 0; i < 5; i++)
		{
			stl_list.push_back(range[i]);
			ft_list.push_back(range[i]);
		}

		fs.open("./tester/lists_output/reverse", std::fstream::in | std::fstream::out | std::fstream::trunc);
		
		printListAttributes(fs, stl_list, ft_list);

		stl_list.reverse();
		ft_list.reverse();
		
		std::cout << ((printListAttributes(fs, stl_list, ft_list) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {842, 985, -9666, 98, -7};\n";
		fs << "ft::list<int> ft_list;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_list.push_back(range[i]);\n";
		fs << "Sending Output...\n";
		fs << "ft_list.reverse();\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range[] = {842, 985, -9666, 98, -7};\n";
		fs << "std::list<int> stl_list;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_list.push_back(range[i]);\n";
		fs << "Sending Output...\n";
		fs << "stl_list.reverse();\n";
		fs.close();     
	}

	std::cout << "\n";
	std::cout << "Non member function overloads : ";

	/* RL = Relation operators */

    /* RL '==' true */
    {
        int range_array[] = {1458, -98, 745, 62, 9};

        std::list<int> stl_list_one;
        std::list<int> stl_list_two;
        ft::list<int> ft_list_one;
        ft::list<int> ft_list_two;

        for (int i = 0; i < 5; i++)
        {
            stl_list_one.push_back(range_array[i]);
            stl_list_two.push_back(range_array[i]);
            ft_list_one.push_back(range_array[i]);
            ft_list_two.push_back(range_array[i]);
        }

        fs.open("./tester/lists_output/operator_equal_true", std::fstream::in | std::fstream::out | std::fstream::trunc);
        printListAttributes(fs, stl_list_one, ft_list_one);
        printListAttributes(fs, stl_list_two, ft_list_two);

        std::cout << ((printBoolResult(fs, (stl_list_one == stl_list_two), (ft_list_one == ft_list_two))) ? "[OK]" : "[NOP]");
    
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {1458, -98, 745, 62, 9};\n";
        fs << "ft::list<int> ft_list_one;\n";
        fs << "ft::list<int> ft_list_two;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "{\n";
        fs << "    ft_list_one.push_back(range_array[i]);\n";
        fs << "    ft_list_two.push_back(range_array[i]);\n";
        fs << "}\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {1458, -98, 745, 62, 9};\n";
        fs << "std::list<int> stl_list_one;\n";
        fs << "std::list<int> stl_list_two;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "{\n";
        fs << "    stl_list_one.push_back(range_array[i]);\n";
        fs << "    stl_list_two.push_back(range_array[i]);\n";
        fs << "}\n";
        fs.close();
    }

    /* RL '==' false */
    {
        int range_array_one[] = {1458, -98, 745, 62, 9};
        int range_array_two[] = {1458, 9, 458, 5, -88};

        std::list<int> stl_list_one;
        std::list<int> stl_list_two;
        ft::list<int> ft_list_one;
        ft::list<int> ft_list_two;

        for (int i = 0; i < 5; i++)
        {
            stl_list_one.push_back(range_array_one[i]);
            stl_list_two.push_back(range_array_two[i]);
            ft_list_one.push_back(range_array_one[i]);
            ft_list_two.push_back(range_array_two[i]);
        }

        fs.open("./tester/lists_output/operator_equal_false", std::fstream::in | std::fstream::out | std::fstream::trunc);

        printListAttributes(fs, stl_list_one, ft_list_one);
        printListAttributes(fs, stl_list_two, ft_list_two);

        std::cout << ((printBoolResult(fs, (stl_list_one == stl_list_two), (ft_list_one == ft_list_two))) ? "[OK]" : "[NOP]");
    
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {1458, -98, 745, 62, 9};\n";
        fs << "int range_array_two[] = {1458, 9, 458, 5, -88};\n";
        fs << "ft::list<int> ft_list_one;\n";
        fs << "ft::list<int> ft_list_two;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "{\n";
        fs << "    ft_list_one.push_back(range_array_one[i]);\n";
        fs << "    ft_list_two.push_back(range_array_two[i]);\n";
        fs << "}\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {1458, -98, 745, 62, 9};\n";
        fs << "int range_array_two[] = {1458, 9, 458, 5, -88};\n";
        fs << "std::list<int> stl_list_one;\n";
        fs << "std::list<int> stl_list_two;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "{\n";
        fs << "    stl_list_one.push_back(range_array_one[i]);\n";
        fs << "    stl_list_two.push_back(range_array_two[i]);\n";
        fs << "}\n";
        fs.close();
    }

    /* RL '!=' true */
    {
        int range_array_one[] = {144, 335, 5, 0, -54};
        int range_array_two[] = {1458, -98, 745, 62, 9};

        std::list<int> stl_list_one;
        std::list<int> stl_list_two;
        ft::list<int> ft_list_one;
        ft::list<int> ft_list_two;

        for (int i = 0; i < 5; i++)
        {
            stl_list_one.push_back(range_array_one[i]);
            stl_list_two.push_back(range_array_two[i]);
            ft_list_one.push_back(range_array_one[i]);
            ft_list_two.push_back(range_array_two[i]);
        }

        fs.open("./tester/lists_output/operator_not_equal_true", std::fstream::in | std::fstream::out | std::fstream::trunc);

        printListAttributes(fs, stl_list_one, ft_list_one);
        printListAttributes(fs, stl_list_two, ft_list_two);

        std::cout << ((printBoolResult(fs, (stl_list_one != stl_list_two), (ft_list_one != ft_list_two))) ? "[OK]" : "[NOP]");
    
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 335, 5, 0, -54};\n";
        fs << "int range_array_two[] = {1458, -98, 745, 62, 9};\n";
        fs << "ft::list<int> ft_list_one;\n";
        fs << "ft::list<int> ft_list_two;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "{\n";
        fs << "    ft_list_one.push_back(range_array_one[i]);\n";
        fs << "    ft_list_two.push_back(range_array_two[i]);\n";
        fs << "}\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 335, 5, 0, -54};\n";
        fs << "int range_array_two[] = {1458, -98, 745, 62, 9};\n";
        fs << "std::list<int> stl_list_one;\n";
        fs << "std::list<int> stl_list_two;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "{\n";
        fs << "    stl_list_one.push_back(range_array_one[i]);\n";
        fs << "    stl_list_two.push_back(range_array_two[i]);\n";
        fs << "}\n";
        fs.close();
    }

    /* RL '!=' false */
    {
        int range_array[] = {1458, -98, 745, 62, 9};

        std::list<int> stl_list_one;
        std::list<int> stl_list_two;
        ft::list<int> ft_list_one;
        ft::list<int> ft_list_two;

        for (int i = 0; i < 5; i++)
        {
            stl_list_one.push_back(range_array[i]);
            stl_list_two.push_back(range_array[i]);
            ft_list_one.push_back(range_array[i]);
            ft_list_two.push_back(range_array[i]);
        }

        fs.open("./tester/lists_output/operator_not_equal_false", std::fstream::in | std::fstream::out | std::fstream::trunc);
        printListAttributes(fs, stl_list_one, ft_list_one);
        printListAttributes(fs, stl_list_two, ft_list_two);

        std::cout << ((printBoolResult(fs, (stl_list_one != stl_list_two), (ft_list_one != ft_list_two))) ? "[OK]" : "[NOP]");
    
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {1458, -98, 745, 62, 9};\n";
        fs << "ft::list<int> ft_list_one;\n";
        fs << "ft::list<int> ft_list_two;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "{\n";
        fs << "    ft_list_one.push_back(range_array[i]);\n";
        fs << "    ft_list_two.push_back(range_array[i]);\n";
        fs << "}\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array[] = {1458, -98, 745, 62, 9};\n";
        fs << "std::list<int> stl_list_one;\n";
        fs << "std::list<int> stl_list_two;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "{\n";
        fs << "    stl_list_one.push_back(range_array[i]);\n";
        fs << "    stl_list_two.push_back(range_array[i]);\n";
        fs << "}\n";
        fs.close();
    }

    /* RL '<' true */
    {
        int range_array_one[] = {144, 335, 1, -98, 5};
        int range_array_two[] = {144, 335, 5, 0, -54};

        std::list<int> stl_list_one;
        std::list<int> stl_list_two;
        ft::list<int> ft_list_one;
        ft::list<int> ft_list_two;

        for (int i = 0; i < 5; i++)
        {
            stl_list_one.push_back(range_array_one[i]);
            stl_list_two.push_back(range_array_two[i]);
            ft_list_one.push_back(range_array_one[i]);
            ft_list_two.push_back(range_array_two[i]);
        }

        fs.open("./tester/lists_output/operator_inferior_true", std::fstream::in | std::fstream::out | std::fstream::trunc);

        printListAttributes(fs, stl_list_one, ft_list_one);
        printListAttributes(fs, stl_list_two, ft_list_two);

        std::cout << ((printBoolResult(fs, (stl_list_one < stl_list_two), (ft_list_one < ft_list_two))) ? "[OK]" : "[NOP]");
    
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 335, 1, -98, 5};\n";
        fs << "int range_array_two[] = {144, 335, 5, 0, -54};\n";
        fs << "ft::list<int> ft_list_one;\n";
        fs << "ft::list<int> ft_list_two;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "{\n";
        fs << "    ft_list_one.push_back(range_array_one[i]);\n";
        fs << "    ft_list_two.push_back(range_array_two[i]);\n";
        fs << "}\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 335, 1, -98, 5};\n";
        fs << "int range_array_two[] = {144, 335, 5, 0, -54};\n";
        fs << "std::list<int> stl_list_one;\n";
        fs << "std::list<int> stl_list_two;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "{\n";
        fs << "    stl_list_one.push_back(range_array_one[i]);\n";
        fs << "    stl_list_two.push_back(range_array_two[i]);\n";
        fs << "}\n";
        fs.close();
    }

    /* RL '<' false */
    {
        int range_array_one[] = {6780, 335, 1, -98, 5};
        int range_array_two[] = {144, 335, 5, 0, -54};

        std::list<int> stl_list_one;
        std::list<int> stl_list_two;
        ft::list<int> ft_list_one;
        ft::list<int> ft_list_two;

        for (int i = 0; i < 5; i++)
        {
            stl_list_one.push_back(range_array_one[i]);
            stl_list_two.push_back(range_array_two[i]);
            ft_list_one.push_back(range_array_one[i]);
            ft_list_two.push_back(range_array_two[i]);
        }

        fs.open("./tester/lists_output/operator_inferior_false", std::fstream::in | std::fstream::out | std::fstream::trunc);

        printListAttributes(fs, stl_list_one, ft_list_one);
        printListAttributes(fs, stl_list_two, ft_list_two);

        std::cout << ((printBoolResult(fs, (stl_list_one < stl_list_two), (ft_list_one < ft_list_two))) ? "[OK]" : "[NOP]");
    
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {6780, 335, 1, -98, 5};\n";
        fs << "int range_array_two[] = {144, 335, 5, 0, -54};\n";
        fs << "ft::list<int> ft_list_one;\n";
        fs << "ft::list<int> ft_list_two;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "{\n";
        fs << "    ft_list_one.push_back(range_array_one[i]);\n";
        fs << "    ft_list_two.push_back(range_array_two[i]);\n";
        fs << "}\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {6780, 335, 1, -98, 5};\n";
        fs << "int range_array_two[] = {144, 335, 5, 0, -54};\n";
        fs << "std::list<int> stl_list_one;\n";
        fs << "std::list<int> stl_list_two;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "{\n";
        fs << "    stl_list_one.push_back(range_array_one[i]);\n";
        fs << "    stl_list_two.push_back(range_array_two[i]);\n";
        fs << "}\n";
        fs.close();
    }

    /* RL '<=' true */
    {
        int range_array_one[] = {144, 335, 1, -98, 5};
        int range_array_two[] = {144, 335, 5, 0, -54};

        std::list<int> stl_list_one;
        std::list<int> stl_list_two;
        ft::list<int> ft_list_one;
        ft::list<int> ft_list_two;

        for (int i = 0; i < 5; i++)
        {
            stl_list_one.push_back(range_array_one[i]);
            stl_list_two.push_back(range_array_two[i]);
            ft_list_one.push_back(range_array_one[i]);
            ft_list_two.push_back(range_array_two[i]);
        }

        fs.open("./tester/lists_output/operator_inf_or_equal_true", std::fstream::in | std::fstream::out | std::fstream::trunc);

        printListAttributes(fs, stl_list_one, ft_list_one);
        printListAttributes(fs, stl_list_two, ft_list_two);

        std::cout << ((printBoolResult(fs, (stl_list_one <= stl_list_two), (ft_list_one <= ft_list_two))) ? "[OK]" : "[NOP]");
    
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 335, 1, -98, 5};\n";
        fs << "int range_array_two[] = {144, 335, 5, 0, -54};\n";
        fs << "ft::list<int> ft_list_one;\n";
        fs << "ft::list<int> ft_list_two;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "{\n";
        fs << "    ft_list_one.push_back(range_array_one[i]);\n";
        fs << "    ft_list_two.push_back(range_array_two[i]);\n";
        fs << "}\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 335, 1, -98, 5};\n";
        fs << "int range_array_two[] = {144, 335, 5, 0, -54};\n";
        fs << "std::list<int> stl_list_one;\n";
        fs << "std::list<int> stl_list_two;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "{\n";
        fs << "    stl_list_one.push_back(range_array_one[i]);\n";
        fs << "    stl_list_two.push_back(range_array_two[i]);\n";
        fs << "}\n";
        fs.close();
    }

    /* RL '<=' true equal */
    {
        int range_array_one[] = {144, 335, 5, 0, -54};
        int range_array_two[] = {144, 335, 5, 0, -54};

        std::list<int> stl_list_one;
        std::list<int> stl_list_two;
        ft::list<int> ft_list_one;
        ft::list<int> ft_list_two;

        for (int i = 0; i < 5; i++)
        {
            stl_list_one.push_back(range_array_one[i]);
            stl_list_two.push_back(range_array_two[i]);
            ft_list_one.push_back(range_array_one[i]);
            ft_list_two.push_back(range_array_two[i]);
        }

        fs.open("./tester/lists_output/operator_inf_or_equal_true_equal", std::fstream::in | std::fstream::out | std::fstream::trunc);

        printListAttributes(fs, stl_list_one, ft_list_one);
        printListAttributes(fs, stl_list_two, ft_list_two);

        std::cout << ((printBoolResult(fs, (stl_list_one <= stl_list_two), (ft_list_one <= ft_list_two))) ? "[OK]" : "[NOP]");
    
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 335, 5, 0, -54};\n";
        fs << "int range_array_two[] = {144, 335, 5, 0, -54};\n";
        fs << "ft::list<int> ft_list_one;\n";
        fs << "ft::list<int> ft_list_two;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "{\n";
        fs << "    ft_list_one.push_back(range_array_one[i]);\n";
        fs << "    ft_list_two.push_back(range_array_two[i]);\n";
        fs << "}\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 335, 5, 0, -54};\n";
        fs << "int range_array_two[] = {144, 335, 5, 0, -54};\n";
        fs << "std::list<int> stl_list_one;\n";
        fs << "std::list<int> stl_list_two;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "{\n";
        fs << "    stl_list_one.push_back(range_array_one[i]);\n";
        fs << "    stl_list_two.push_back(range_array_two[i]);\n";
        fs << "}\n";
        fs.close();
    }

    /* RL '<=' false */
    {
        int range_array_one[] = {144, 9999, 5, 0, -54};
        int range_array_two[] = {144, 335, 5, 0, -54};

        std::list<int> stl_list_one;
        std::list<int> stl_list_two;
        ft::list<int> ft_list_one;
        ft::list<int> ft_list_two;

        for (int i = 0; i < 5; i++)
        {
            stl_list_one.push_back(range_array_one[i]);
            stl_list_two.push_back(range_array_two[i]);
            ft_list_one.push_back(range_array_one[i]);
            ft_list_two.push_back(range_array_two[i]);
        }

        fs.open("./tester/lists_output/operator_inf_or_equal_false", std::fstream::in | std::fstream::out | std::fstream::trunc);

        printListAttributes(fs, stl_list_one, ft_list_one);
        printListAttributes(fs, stl_list_two, ft_list_two);

        std::cout << ((printBoolResult(fs, (stl_list_one <= stl_list_two), (ft_list_one <= ft_list_two))) ? "[OK]" : "[NOP]");
    
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 9999, 5, 0, -54};\n";
        fs << "int range_array_two[] = {144, 335, 5, 0, -54};\n";
        fs << "ft::list<int> ft_list_one;\n";
        fs << "ft::list<int> ft_list_two;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "{\n";
        fs << "    ft_list_one.push_back(range_array_one[i]);\n";
        fs << "    ft_list_two.push_back(range_array_two[i]);\n";
        fs << "}\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 9999, 5, 0, -54};\n";
        fs << "int range_array_two[] = {144, 335, 5, 0, -54};\n";
        fs << "std::list<int> stl_list_one;\n";
        fs << "std::list<int> stl_list_two;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "{\n";
        fs << "    stl_list_one.push_back(range_array_one[i]);\n";
        fs << "    stl_list_two.push_back(range_array_two[i]);\n";
        fs << "}\n";
        fs.close();
    }

    /* RL '>' true */
    {
        int range_array_one[] = {144, 9999, 5, 0, -54};
        int range_array_two[] = {144, 335, 5, 0, -54};

        std::list<int> stl_list_one;
        std::list<int> stl_list_two;
        ft::list<int> ft_list_one;
        ft::list<int> ft_list_two;

        for (int i = 0; i < 5; i++)
        {
            stl_list_one.push_back(range_array_one[i]);
            stl_list_two.push_back(range_array_two[i]);
            ft_list_one.push_back(range_array_one[i]);
            ft_list_two.push_back(range_array_two[i]);
        }

        fs.open("./tester/lists_output/operator_superior_true", std::fstream::in | std::fstream::out | std::fstream::trunc);

        printListAttributes(fs, stl_list_one, ft_list_one);
        printListAttributes(fs, stl_list_two, ft_list_two);

        std::cout << ((printBoolResult(fs, (stl_list_one > stl_list_two), (ft_list_one > ft_list_two))) ? "[OK]" : "[NOP]");
    
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 9999, 5, 0, -54};\n";
        fs << "int range_array_two[] = {144, 335, 5, 0, -54};\n";
        fs << "ft::list<int> ft_list_one;\n";
        fs << "ft::list<int> ft_list_two;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "{\n";
        fs << "    ft_list_one.push_back(range_array_one[i]);\n";
        fs << "    ft_list_two.push_back(range_array_two[i]);\n";
        fs << "}\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 9999, 5, 0, -54};\n";
        fs << "int range_array_two[] = {144, 335, 5, 0, -54};\n";
        fs << "std::list<int> stl_list_one;\n";
        fs << "std::list<int> stl_list_two;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "{\n";
        fs << "    stl_list_one.push_back(range_array_one[i]);\n";
        fs << "    stl_list_two.push_back(range_array_two[i]);\n";
        fs << "}\n";
        fs.close();
    }

    /* RL '>' false */
    {
        int range_array_one[] = {144, 335, 5, 0, -54};
        int range_array_two[] = {144, 335, 77, 0, -54};

        std::list<int> stl_list_one;
        std::list<int> stl_list_two;
        ft::list<int> ft_list_one;
        ft::list<int> ft_list_two;

        for (int i = 0; i < 5; i++)
        {
            stl_list_one.push_back(range_array_one[i]);
            stl_list_two.push_back(range_array_two[i]);
            ft_list_one.push_back(range_array_one[i]);
            ft_list_two.push_back(range_array_two[i]);
        }

        fs.open("./tester/lists_output/operator_superior_false", std::fstream::in | std::fstream::out | std::fstream::trunc);

        printListAttributes(fs, stl_list_one, ft_list_one);
        printListAttributes(fs, stl_list_two, ft_list_two);

        std::cout << ((printBoolResult(fs, (stl_list_one > stl_list_two), (ft_list_one > ft_list_two))) ? "[OK]" : "[NOP]");
    
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 335, 5, 0, -54};\n";
        fs << "int range_array_two[] = {144, 335, 77, 0, -54};\n";
        fs << "ft::list<int> ft_list_one;\n";
        fs << "ft::list<int> ft_list_two;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "{\n";
        fs << "    ft_list_one.push_back(range_array_one[i]);\n";
        fs << "    ft_list_two.push_back(range_array_two[i]);\n";
        fs << "}\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 335, 5, 0, -54};\n";
        fs << "int range_array_two[] = {144, 335, 77, 0, -54};\n";
        fs << "std::list<int> stl_list_one;\n";
        fs << "std::list<int> stl_list_two;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "{\n";
        fs << "    stl_list_one.push_back(range_array_one[i]);\n";
        fs << "    stl_list_two.push_back(range_array_two[i]);\n";
        fs << "}\n";
        fs.close();
    }

    /* RL '>=' true */
    {
        int range_array_one[] = {144, 335, 78, 0, -54};
        int range_array_two[] = {144, 335, 77, 0, -54};

        std::list<int> stl_list_one;
        std::list<int> stl_list_two;
        ft::list<int> ft_list_one;
        ft::list<int> ft_list_two;

        for (int i = 0; i < 5; i++)
        {
            stl_list_one.push_back(range_array_one[i]);
            stl_list_two.push_back(range_array_two[i]);
            ft_list_one.push_back(range_array_one[i]);
            ft_list_two.push_back(range_array_two[i]);
        }

        fs.open("./tester/lists_output/operator_sup_or_equal_true", std::fstream::in | std::fstream::out | std::fstream::trunc);

        printListAttributes(fs, stl_list_one, ft_list_one);
        printListAttributes(fs, stl_list_two, ft_list_two);

        std::cout << ((printBoolResult(fs, (stl_list_one > stl_list_two), (ft_list_one > ft_list_two))) ? "[OK]" : "[NOP]");
    
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 335, 78, 0, -54};\n";
        fs << "int range_array_two[] = {144, 335, 77, 0, -54};\n";
        fs << "ft::list<int> ft_list_one;\n";
        fs << "ft::list<int> ft_list_two;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "{\n";
        fs << "    ft_list_one.push_back(range_array_one[i]);\n";
        fs << "    ft_list_two.push_back(range_array_two[i]);\n";
        fs << "}\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 335, 78, 0, -54};\n";
        fs << "int range_array_two[] = {144, 335, 77, 0, -54};\n";
        fs << "std::list<int> stl_list_one;\n";
        fs << "std::list<int> stl_list_two;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "{\n";
        fs << "    stl_list_one.push_back(range_array_one[i]);\n";
        fs << "    stl_list_two.push_back(range_array_two[i]);\n";
        fs << "}\n";
        fs.close();
    }

    /* RL '>=' false */
    {
        int range_array_one[] = {144, 335, 5, 0, -54};
        int range_array_two[] = {144, 335, 77, 0, -54};

        std::list<int> stl_list_one;
        std::list<int> stl_list_two;
        ft::list<int> ft_list_one;
        ft::list<int> ft_list_two;

        for (int i = 0; i < 5; i++)
        {
            stl_list_one.push_back(range_array_one[i]);
            stl_list_two.push_back(range_array_two[i]);
            ft_list_one.push_back(range_array_one[i]);
            ft_list_two.push_back(range_array_two[i]);
        }

        fs.open("./tester/lists_output/operator_sup_or_equal_false", std::fstream::in | std::fstream::out | std::fstream::trunc);

        printListAttributes(fs, stl_list_one, ft_list_one);
        printListAttributes(fs, stl_list_two, ft_list_two);

        std::cout << ((printBoolResult(fs, (stl_list_one > stl_list_two), (ft_list_one > ft_list_two))) ? "[OK]" : "[NOP]");
    
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 335, 5, 0, -54};\n";
        fs << "int range_array_two[] = {144, 335, 77, 0, -54};\n";
        fs << "ft::list<int> ft_list_one;\n";
        fs << "ft::list<int> ft_list_two;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "{\n";
        fs << "    ft_list_one.push_back(range_array_one[i]);\n";
        fs << "    ft_list_two.push_back(range_array_two[i]);\n";
        fs << "}\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 335, 5, 0, -54};\n";
        fs << "int range_array_two[] = {144, 335, 77, 0, -54};\n";
        fs << "std::list<int> stl_list_one;\n";
        fs << "std::list<int> stl_list_two;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "{\n";
        fs << "    stl_list_one.push_back(range_array_one[i]);\n";
        fs << "    stl_list_two.push_back(range_array_two[i]);\n";
        fs << "}\n";
        fs.close();
    }

    /* Swap non member */
    {
        int range_array_one[] = {144, 335, 5, 0, -54};
        int range_array_two[] = {47, -98, 58, 611, -4};

        std::list<int> stl_list_one;
        std::list<int> stl_list_two;
        ft::list<int> ft_list_one;
        ft::list<int> ft_list_two;

        for (int i = 0; i < 5; i++)
        {
            stl_list_one.push_back(range_array_one[i]);
            stl_list_two.push_back(range_array_two[i]);
            ft_list_one.push_back(range_array_one[i]);
            ft_list_two.push_back(range_array_two[i]);
        }

        std::swap(stl_list_one, stl_list_two);
        ft::swap(ft_list_one, ft_list_two);
        
        fs.open("./tester/lists_output/swap_no_member", std::fstream::in | std::fstream::out | std::fstream::trunc);

        std::cout << ((printListAttributes(fs, stl_list_one, ft_list_one)) ? "[OK]" : "[NOP]");
        std::cout << ((printListAttributes(fs, stl_list_two, ft_list_two)) ? "[OK]" : "[NOP]");
    
        fs << "\nCode executed:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 335, 5, 0, -54};\n";
        fs << "int range_array_two[] = {47, -98, 58, 611, -4};\n";
        fs << "ft::list<int> ft_list_one;\n";
        fs << "ft::list<int> ft_list_two;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "{\n";
        fs << "    ft_list_one.push_back(range_array_one[i]);\n";
        fs << "    ft_list_two.push_back(range_array_two[i]);\n";
        fs << "}\n";
        fs << "ft::swap(ft_list_one, ft_list_two);\n";
        fs << "\nCompared with:\n";
        fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "int range_array_one[] = {144, 335, 5, 0, -54};\n";
        fs << "int range_array_two[] = {47, -98, 58, 611, -4};\n";
        fs << "std::list<int> stl_list_one;\n";
        fs << "std::list<int> stl_list_two;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "{\n";
        fs << "    stl_list_one.push_back(range_array_one[i]);\n";
        fs << "    stl_list_two.push_back(range_array_two[i]);\n";
        fs << "}\n";
        fs << "std::swap(stl_list_one, stl_list_two);\n";
        fs.close();  
    }

	std::cout << std::endl;
}