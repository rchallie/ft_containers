/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester_map.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchallie <rchallie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 18:22:17 by rchallie          #+#    #+#             */
/*   Updated: 2020/12/10 21:40:05 by rchallie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map>
#include "tester.hpp"
#include "../containers/map.hpp"
#include "../containers/utils/binary_search_tree.hpp"

template <class Ta, class Tb>
std::string equalContent(
	const std::map<Ta, Tb> & stl_map,
	const ft::map<Ta, Tb> & ft_map
)
{
	typename ft::map<Ta, Tb>::const_iterator ft_it;
	typename std::map<Ta, Tb>::const_iterator stl_it;
	if (ft_map.size() != stl_map.size())
		return ("✘");
	stl_it = stl_map.begin();
	for(ft_it = ft_map.begin(); ft_it != ft_map.end(); ft_it++)
	{
		if ((*ft_it).first != (*stl_it).first || (*ft_it).second != (*stl_it).second)
			return ("✘");
		stl_it++;
	}
	return ("✔");
}

template <class Ta, class Tb>
bool printMapAttributes(
	std::fstream& fs,
	std::map<Ta, Tb>& stl_map,
	ft::map<Ta, Tb>& ft_map
)
{
	/* STL Values */
	std::string stl_empty = ((stl_map.empty() == 1) ? "true" : "false");
	size_t stl_size = stl_map.size();
	size_t stl_max_size = stl_map.max_size();

	/* FT Values */
	std::string ft_empty = ((ft_map.empty() == 1) ? "true" : "false");
	size_t ft_size = ft_map.size();
	size_t ft_max_size = ft_map.max_size();

	/* FT Result compare values */
	bool empty = equalbool(ft_empty, stl_empty);
	bool size = equalbool(ft_size, stl_size);
	bool max_size = equalbool(ft_max_size, stl_max_size);
	std::string content = equalContent(stl_map, ft_map);
	
	fs << "\n══════════════════════════════════════════════════════════════\n";
	fs << "maps attributes : \n";
	fs << "STL : \n";
	fs << "Empty       : " << stl_empty  << std::endl;
	fs << "Size        : " << stl_size  << std::endl;
	fs << "Max size    : " << stl_max_size  << std::endl;
	fs << "Content     : [";
	
	typename std::map<Ta, Tb>::const_iterator stl_it;
	for (stl_it = stl_map.begin();  stl_it != stl_map.end(); stl_it++)
	{
		fs << "[";
		fs << (*stl_it).first;
		fs << ", ";
		fs << (*stl_it).second;
		fs << "]";
		fs << ", ";
	}
	fs << "]\n";

	fs << std::endl;

	fs << "FT : \n";
	fs << "Empty    [" << equal(ft_empty, stl_empty) << "]: " << ft_empty  << std::endl;
	fs << "Size     [" << equal(ft_size, stl_size) << "]: " << ft_size  << std::endl;
	fs << "Max size [" << equal(ft_max_size, stl_max_size) << "]: " << ft_max_size  << std::endl;

	fs << "Content  [" << content << "]: [";

	typename ft::map<Ta, Tb>::const_iterator ft_it;
	for(ft_it = ft_map.begin(); ft_it != ft_map.end(); ft_it++)
	{
		fs << "[";
		fs << (*ft_it).first;
		fs << ", ";
		fs << (*ft_it).second;
		fs << "]";
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

void test_map()
{

	std::cout << UNDERLINE << "MAP :\n" << NORMAL ;

	mkdir("./tester/maps_output", 0777);
	
	std::fstream fs;

	/* Constructors */
	std::cout << "Constructors : ";

	/* Default constructor */
	{
		std::map<int, std::string> stl_default_map;
		ft::map<int, std::string> ft_default_map;

		fs.open("./tester/maps_output/constructor_default", std::fstream::in | std::fstream::out | std::fstream::trunc);
		std::cout << ((printMapAttributes(fs, stl_default_map, ft_default_map) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "ft::map<int, std::string> ft_default_map;\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "std::map<int, std::string> stl_default_map;\n";
		fs.close();     
	}

	/* Range constrcutor */
	{
		const int range_int[] = {-652, -4, 98, 54, -210};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		for (int i = 0; i < 5; i++)
		{
			stl_map.insert(std::make_pair(range_int[i], range_str[i]));
			ft_map.insert(ft::make_pair(range_int[i], range_str[i]));
		}

		fs.open("./tester/maps_output/constructor_range", std::fstream::in | std::fstream::out | std::fstream::trunc);
		
		printMapAttributes(fs, stl_map, ft_map);

		std::map<int, std::string> stl_map_copy(stl_map.begin(), stl_map.end());
		ft::map<int, std::string> ft_map_copy(ft_map.begin(), ft_map.end());

		std::cout << ((printMapAttributes(fs, stl_map_copy, ft_map_copy) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {-652, -4, 98, 54, -210};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_map.insert(ft::make_pair(range_int[i], range_str[i]));\n";
		fs << "ft::map<int, std::string> ft_map_copy(ft_map.begin(), ft_map.end());\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {-652, -4, 98, 54, -210};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_map.insert(std::make_pair(range_int[i], range_str[i]));\n";
		fs << "std::map<int, std::string> stl_map_copy(stl_map.begin(), stl_map.end());\n";
		fs.close();
	}

	/* Copy constructor */
	{
		const int range_int[] = {842, 695, -98, -2, -4};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		for (int i = 0; i < 5; i++)
		{
			stl_map.insert(std::make_pair(range_int[i], range_str[i]));
			ft_map.insert(ft::make_pair(range_int[i], range_str[i]));
		}

		fs.open("./tester/maps_output/constructor_copy", std::fstream::in | std::fstream::out | std::fstream::trunc);
		
		printMapAttributes(fs, stl_map, ft_map);

		std::map<int, std::string> stl_map_copy(stl_map);
		ft::map<int, std::string> ft_map_copy(ft_map);

		std::cout << ((printMapAttributes(fs, stl_map_copy, ft_map_copy) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {842, 695, -98, -2, -4};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_map.insert(ft::make_pair(range_int[i], range_str[i]));\n";
		fs << "ft::map<int, std::string> ft_map_copy(ft_map);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {842, 695, -98, -2, -4};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_map.insert(std::make_pair(range_int[i], range_str[i]));\n";
		fs << "std::map<int, std::string> stl_map_copy(stl_map);\n";
		fs.close();
	}

	/* Assign operator */
	{
		const int range_int[] = {478, 952, 12, -96, -9};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		for (int i = 0; i < 5; i++)
		{
			stl_map.insert(std::make_pair(range_int[i], range_str[i]));
			ft_map.insert(ft::make_pair(range_int[i], range_str[i]));
		}

		fs.open("./tester/maps_output/operator_assign", std::fstream::in | std::fstream::out | std::fstream::trunc);
		
		printMapAttributes(fs, stl_map, ft_map);

		std::map<int, std::string> stl_map_copy = stl_map;
		ft::map<int, std::string> ft_map_copy = ft_map;

		std::cout << ((printMapAttributes(fs, stl_map_copy, ft_map_copy) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {478, 952, 12, -96, -9};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_map.insert(ft::make_pair(range_int[i], range_str[i]));\n";
		fs << "ft::map<int, std::string> ft_map_copy = ft_map;\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {478, 952, 12, -96, -9};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_map.insert(std::make_pair(range_int[i], range_str[i]));\n";
		fs << "std::map<int, std::string> stl_map_copy = stl_map;\n";
		fs.close();
	}

	std::cout << std::endl;
	std::cout << "Iterators : ";

	/* Begin */
	{
		const int range_int[] = {1485, 5, 89, 652, -94};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		for (int i = 0; i < 5; i++)
		{
			stl_map.insert(std::make_pair(range_int[i], range_str[i]));
			ft_map.insert(ft::make_pair(range_int[i], range_str[i]));
		}

		fs.open("./tester/maps_output/begin", std::fstream::in | std::fstream::out | std::fstream::trunc);
		
		printMapAttributes(fs, stl_map, ft_map);
		std::cout << "[";
		std::cout << ((printSingleValue(fs, (*stl_map.begin()).first, (*ft_map.begin()).first) == true) ? "[OK]" : "[NOP]");
		std::cout << ((printSingleValue(fs, (*stl_map.begin()).second, (*ft_map.begin()).second) == true) ? "[OK]" : "[NOP]");
		std::cout << "]";

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {1485, 5, 89, 652, -94};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_map.insert(ft::make_pair(range_int[i], range_str[i]));\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {1485, 5, 89, 652, -94};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_map.insert(std::make_pair(range_int[i], range_str[i]));\n";
		fs.close(); 
	}

	/* Const begin */
	{
		const int range_int[] = {48, 9, 12, 63, 99};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		for (int i = 0; i < 5; i++)
		{
			stl_map.insert(std::make_pair(range_int[i], range_str[i]));
			ft_map.insert(ft::make_pair(range_int[i], range_str[i]));
		}

		fs.open("./tester/maps_output/begin_const", std::fstream::in | std::fstream::out | std::fstream::trunc);
		
		std::map<int, std::string>::const_iterator stl_it = stl_map.begin();
		ft::map<int, std::string>::const_iterator ft_it = ft_map.begin();

		printMapAttributes(fs, stl_map, ft_map);
		std::cout << "[";
		std::cout << ((printSingleValue(fs, (*stl_it).first, (*ft_it).first) == true) ? "[OK]" : "[NOP]");
		std::cout << ((printSingleValue(fs, (*stl_it).second, (*ft_it).second) == true) ? "[OK]" : "[NOP]");
		std::cout << "]";

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {48, 9, 12, 63, 99};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_map.insert(ft::make_pair(range_int[i], range_str[i]));\n";
		fs << "ft::map<int, std::string>::const_iterator ft_it = ft_map.begin();\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {48, 9, 12, 63, 99};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_map.insert(std::make_pair(range_int[i], range_str[i]));\n";
		fs << "std::map<int, std::string>::const_iterator stl_it = stl_map.begin();\n";
		fs.close(); 
	}

	/* End */
	{
		const int range_int[] = {-99, 584, 965, 366, 77};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		for (int i = 0; i < 5; i++)
		{
			stl_map.insert(std::make_pair(range_int[i], range_str[i]));
			ft_map.insert(ft::make_pair(range_int[i], range_str[i]));
		}

		fs.open("./tester/maps_output/end", std::fstream::in | std::fstream::out | std::fstream::trunc);
		
		std::map<int, std::string>::iterator stl_it = stl_map.end();
		ft::map<int, std::string>::iterator ft_it = ft_map.end();

		printMapAttributes(fs, stl_map, ft_map);

		--stl_it;
		--ft_it;

		std::cout << "[";
		std::cout << ((printSingleValue(fs, (*stl_it).first, (*ft_it).first) == true) ? "[OK]" : "[NOP]");
		std::cout << ((printSingleValue(fs, (*stl_it).second, (*ft_it).second) == true) ? "[OK]" : "[NOP]");
		std::cout << "]";

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {-99, 584, 965, 366, 77};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_map.insert(ft::make_pair(range_int[i], range_str[i]));\n";
		fs << "ft::map<int, std::string>::iterator ft_it = ft_map.end();\n";
		fs << "--ft_it;\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {-99, 584, 965, 366, 77};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_map.insert(std::make_pair(range_int[i], range_str[i]));\n";
		fs << "std::map<int, std::string>::iterator stl_it = stl_map.end();\n";
		fs << "--stl_it;\n";
		fs.close(); 
	}

	/* Const end */
	{
		const int range_int[] = {154, 966, 3, -84, 75};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		for (int i = 0; i < 5; i++)
		{
			stl_map.insert(std::make_pair(range_int[i], range_str[i]));
			ft_map.insert(ft::make_pair(range_int[i], range_str[i]));
		}

		fs.open("./tester/maps_output/end_const", std::fstream::in | std::fstream::out | std::fstream::trunc);
		
		std::map<int, std::string>::const_iterator stl_it = stl_map.end();
		ft::map<int, std::string>::const_iterator ft_it = ft_map.end();

		printMapAttributes(fs, stl_map, ft_map);

		--stl_it;
		--ft_it;

		std::cout << "[";
		std::cout << ((printSingleValue(fs, (*stl_it).first, (*ft_it).first) == true) ? "[OK]" : "[NOP]");
		std::cout << ((printSingleValue(fs, (*stl_it).second, (*ft_it).second) == true) ? "[OK]" : "[NOP]");
		std::cout << "]";

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {154, 966, 3, -84, 75};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_map.insert(ft::make_pair(range_int[i], range_str[i]));\n";
		fs << "ft::map<int, std::string>::const_iterator ft_it = ft_map.end();\n";
		fs << "--ft_it;\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {154, 966, 3, -84, 75};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_map.insert(std::make_pair(range_int[i], range_str[i]));\n";
		fs << "std::map<int, std::string>::const_iterator stl_it = stl_map.end();\n";
		fs << "--stl_it;\n";
		fs.close();
	}

	/* Reverse begin */
	{
		const int range_int[] = {1458, -985, 58, 632, 65};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		for (int i = 0; i < 5; i++)
		{
			stl_map.insert(std::make_pair(range_int[i], range_str[i]));
			ft_map.insert(ft::make_pair(range_int[i], range_str[i]));
		}

		fs.open("./tester/maps_output/reverse_begin", std::fstream::in | std::fstream::out | std::fstream::trunc);
		
		std::map<int, std::string>::reverse_iterator stl_it = stl_map.rbegin();
		ft::map<int, std::string>::reverse_iterator ft_it = ft_map.rbegin();

		printMapAttributes(fs, stl_map, ft_map);

		++stl_it;
		++ft_it;

		std::cout << "[";
		std::cout << ((printSingleValue(fs, (*stl_it).first, (*ft_it).first) == true) ? "[OK]" : "[NOP]");
		std::cout << ((printSingleValue(fs, (*stl_it).second, (*ft_it).second) == true) ? "[OK]" : "[NOP]");
		std::cout << "]";

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {1458, -985, 58, 632, 65};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_map.insert(ft::make_pair(range_int[i], range_str[i]));\n";
		fs << "ft::map<int, std::string>::reverse_iterator ft_it = ft_map.rbegin();\n";
		fs << "++ft_it;\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {1458, -985, 58, 632, 65};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_map.insert(std::make_pair(range_int[i], range_str[i]));\n";
		fs << "std::map<int, std::string>::reverse_iterator stl_it = stl_map.rbegin();\n";
		fs << "++stl_it;\n";
		fs.close();
	}

	/* Const reverse begin */
	{
		const int range_int[] = {859, 99, -325, -65, -98};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		for (int i = 0; i < 5; i++)
		{
			stl_map.insert(std::make_pair(range_int[i], range_str[i]));
			ft_map.insert(ft::make_pair(range_int[i], range_str[i]));
		}

		fs.open("./tester/maps_output/reverse_begin_const", std::fstream::in | std::fstream::out | std::fstream::trunc);
		
		std::map<int, std::string>::const_reverse_iterator stl_it = stl_map.rbegin();
		ft::map<int, std::string>::const_reverse_iterator ft_it = ft_map.rbegin();

		printMapAttributes(fs, stl_map, ft_map);

		std::cout << "[";
		std::cout << ((printSingleValue(fs, (*stl_it).first, (*ft_it).first) == true) ? "[OK]" : "[NOP]");
		std::cout << ((printSingleValue(fs, (*stl_it).second, (*ft_it).second) == true) ? "[OK]" : "[NOP]");
		std::cout << "]";

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {859, 99, -325, -65, -98};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_map.insert(ft::make_pair(range_int[i], range_str[i]));\n";
		fs << "ft::map<int, std::string>::const_reverse_iterator ft_it = ft_map.rbegin();\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {859, 99, -325, -65, -98};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_map.insert(std::make_pair(range_int[i], range_str[i]));\n";
		fs << "std::map<int, std::string>::const_reverse_iterator stl_it = stl_map.rbegin();\n";
		fs.close();
	}

	/* Reverse end */
	{
		const int range_int[] = {325, -657, -942, -8, 66};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		for (int i = 0; i < 5; i++)
		{
			stl_map.insert(std::make_pair(range_int[i], range_str[i]));
			ft_map.insert(ft::make_pair(range_int[i], range_str[i]));
		}

		fs.open("./tester/maps_output/reverse_end", std::fstream::in | std::fstream::out | std::fstream::trunc);
		
		std::map<int, std::string>::reverse_iterator stl_it = stl_map.rend();
		ft::map<int, std::string>::reverse_iterator ft_it = ft_map.rend();

		printMapAttributes(fs, stl_map, ft_map);

		--stl_it;
		--ft_it;

		std::cout << "[";
		std::cout << ((printSingleValue(fs, (*stl_it).first, (*ft_it).first) == true) ? "[OK]" : "[NOP]");
		std::cout << ((printSingleValue(fs, (*stl_it).second, (*ft_it).second) == true) ? "[OK]" : "[NOP]");
		std::cout << "]";

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {325, -657, -942, -8, 66};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_map.insert(ft::make_pair(range_int[i], range_str[i]));\n";
		fs << "ft::map<int, std::string>::reverse_iterator ft_it = ft_map.rend();\n";
		fs << "--ft_it;\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {325, -657, -942, -8, 66};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_map.insert(std::make_pair(range_int[i], range_str[i]));\n";
		fs << "std::map<int, std::string>::reverse_iterator stl_it = stl_map.rend();\n";
		fs << "--stl_it;\n";
		fs.close();
	}


	/* Const reverse end */
	{
		const int range_int[] = {-99, 584, 965, 366, 77};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		for (int i = 0; i < 5; i++)
		{
			stl_map.insert(std::make_pair(range_int[i], range_str[i]));
			ft_map.insert(ft::make_pair(range_int[i], range_str[i]));
		}

		fs.open("./tester/maps_output/reverse_end_const", std::fstream::in | std::fstream::out | std::fstream::trunc);
		
		std::map<int, std::string>::const_reverse_iterator stl_it = stl_map.rend();
		ft::map<int, std::string>::const_reverse_iterator ft_it = ft_map.rend();

		printMapAttributes(fs, stl_map, ft_map);

		--(--stl_it);
		--(--ft_it);

		std::cout << "[";
		std::cout << ((printSingleValue(fs, (*stl_it).first, (*ft_it).first) == true) ? "[OK]" : "[NOP]");
		std::cout << ((printSingleValue(fs, (*stl_it).second, (*ft_it).second) == true) ? "[OK]" : "[NOP]");
		std::cout << "]";

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {-99, 584, 965, 366, 77};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_map.insert(ft::make_pair(range_int[i], range_str[i]));\n";
		fs << "ft::map<int, std::string>::const_reverse_iterator ft_it = ft_map.rend();\n";
		fs << "--(--ft_it);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {-99, 584, 965, 366, 77};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_map.insert(std::make_pair(range_int[i], range_str[i]));\n";
		fs << "std::map<int, std::string>::const_reverse_iterator stl_it = stl_map.rend();\n";
		fs << "--(--stl_it);\n";
		fs.close(); 
	}

	std::cout << std::endl;
	std::cout << "Capacity : ";

	/* Empty true */
	{
		std::map<int, std::string> stl_default_map;
		ft::map<int, std::string> ft_default_map;

		fs.open("./tester/maps_output/empty_true", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printMapAttributes(fs, stl_default_map, ft_default_map);
		std::cout << ((printBoolResult(fs, stl_default_map.empty(), ft_default_map.empty()) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "ft::map<int, std::string> ft_default_map;\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "std::map<int, std::string> stl_default_map;\n";
		fs.close();  
	}

	/* Empty false */
	{
		const int range_int[] = {1452, 3651, -98, 84, 899};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		for (int i = 0; i < 5; i++)
		{
			stl_map.insert(std::make_pair(range_int[i], range_str[i]));
			ft_map.insert(ft::make_pair(range_int[i], range_str[i]));
		}

		fs.open("./tester/maps_output/empty_false", std::fstream::in | std::fstream::out | std::fstream::trunc);
		
		printMapAttributes(fs, stl_map, ft_map);
		std::cout << ((printBoolResult(fs, stl_map.empty(), ft_map.empty()) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {1452, 3651, -98, 84, 899};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_map.insert(ft::make_pair(range_int[i], range_str[i]));\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {1452, 3651, -98, 84, 899};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_map.insert(std::make_pair(range_int[i], range_str[i]));\n";
		fs.close(); 
	}

	/* Size */
	{
		const int range_int[] = {9, -84, -45, -67, -9};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		for (int i = 0; i < 5; i++)
		{
			stl_map.insert(std::make_pair(range_int[i], range_str[i]));
			ft_map.insert(ft::make_pair(range_int[i], range_str[i]));
		}

		fs.open("./tester/maps_output/size", std::fstream::in | std::fstream::out | std::fstream::trunc);
		
		printMapAttributes(fs, stl_map, ft_map);
		std::cout << "[";
		std::cout << ((printSingleValue(fs, stl_map.size(), ft_map.size()) == true) ? "[OK]" : "[NOP]");

		stl_map.insert(std::make_pair(42, "Represent"));
		ft_map.insert(ft::make_pair(42, "Represent"));

		std::cout << ((printSingleValue(fs, stl_map.size(), ft_map.size()) == true) ? "[OK]" : "[NOP]");

		std::cout << "]";

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {9, -84, -45, -67, -9};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_map.insert(ft::make_pair(range_int[i], range_str[i]));\n";
		fs << "Sending output...\n";
		fs << "ft_map.insert(ft::make_pair(42, \"Represent\"));\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {9, -84, -45, -67, -9};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_map.insert(std::make_pair(range_int[i], range_str[i]));\n";
		fs << "Sending output...\n";
		fs << "stl_map.insert(std::make_pair(42, \"Represent\"));\n";
		fs.close(); 
	}

	/* Maximum size */
	{
		std::map<int, std::string> stl_default_map;
		ft::map<int, std::string> ft_default_map;

		fs.open("./tester/maps_output/max_size", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printMapAttributes(fs, stl_default_map, ft_default_map);
		std::cout << ((printSingleValue(fs, stl_default_map.max_size(), ft_default_map.max_size()) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "ft::map<int, std::string> ft_default_map;\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "std::map<int, std::string> stl_default_map;\n";
		fs.close();  
	}

	std::cout << std::endl;
	std::cout << "Element access : ";

	/* Operator [] */
	{
		const int range_int[] = {1489, -98, -9, -46, 256};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		for (int i = 0; i < 5; i++)
		{
			stl_map.insert(std::make_pair(range_int[i], range_str[i]));
			ft_map.insert(ft::make_pair(range_int[i], range_str[i]));
		}

		fs.open("./tester/maps_output/operator_at", std::fstream::in | std::fstream::out | std::fstream::trunc);
		
		printMapAttributes(fs, stl_map, ft_map);

		std::cout << "[";
		std::cout << ((printSingleValue(fs, stl_map[-9], ft_map[-9]) == true) ? "[OK]" : "[NOP]");

		stl_map[-9] = "Changed";
		ft_map[-9] = "Changed";

		std::cout << ((printSingleValue(fs, stl_map[-9], ft_map[-9]) == true) ? "[OK]" : "[NOP]");
		std::cout << "]";
		
		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {1489, -98, -9, -46, 256};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_map.insert(ft::make_pair(range_int[i], range_str[i]));\n";
		fs << "Sending output...\n";
		fs << "ft_map[-9] = \"Changed\";\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {1489, -98, -9, -46, 256};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_map.insert(std::make_pair(range_int[i], range_str[i]));\n";
		fs << "Sending output...\n";
		fs << "stl_map[-9] = \"Changed\";\n";
		fs.close(); 
	}

	std::cout << std::endl;
	std::cout << "Modifier : ";

	/* Insert single */
	{
		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		stl_map.insert(std::make_pair(42, "La famille"));
		ft_map.insert(ft::make_pair(42, "La famille"));

		fs.open("./tester/maps_output/insert_single", std::fstream::in | std::fstream::out | std::fstream::trunc);
		std::cout << ((printMapAttributes(fs, stl_map, ft_map) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "ft::map<int, std::string> ft_map;\n";
		fs << "ft_map.insert(ft::make_pair(42, \"La famille\"));\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "std::map<int, std::string> stl_map;\n";
		fs << "stl_map.insert(std::make_pair(42, \"La famille\"));\n";
		fs.close();  
	}

	/* Insert hint */
	{
		const int range_int[] = {584, 96, 21, -54, 36};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		for (int i = 0; i < 5; i++)
		{
			stl_map.insert(std::make_pair(range_int[i], range_str[i]));
			ft_map.insert(ft::make_pair(range_int[i], range_str[i]));
		}

		fs.open("./tester/maps_output/insert_hint", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printMapAttributes(fs, stl_map, ft_map);
		
		stl_map.insert(++(stl_map.begin()), std::make_pair(42, "Nice"));
		ft_map.insert(++(ft_map.begin()), ft::make_pair(42, "Nice"));

		std::cout << ((printMapAttributes(fs, stl_map, ft_map) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {584, 96, 21, -54, 36};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_map.insert(ft::make_pair(range_int[i], range_str[i]));\n";
		fs << "ft_map.insert(++(ft_map.begin()), ft::make_pair(42, \"Nice\"));\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {584, 96, 21, -54, 36};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_map.insert(std::make_pair(range_int[i], range_str[i]));\n";
		fs << "stl_map.insert(++(stl_map.begin()), std::make_pair(42, \"Nice\"));\n";
		fs.close(); 
	}

	/* Insert Range */
	{
		const int range_int[] = {754, -985, 58, 999, 5};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map_one;
		ft::map<int, std::string> ft_map_one;
		std::map<int, std::string> stl_map_two;
		ft::map<int, std::string> ft_map_two;

		for (int i = 0; i < 5; i++)
		{
			stl_map_one.insert(std::make_pair(range_int[i], range_str[i]));
			ft_map_one.insert(ft::make_pair(range_int[i], range_str[i]));
			stl_map_two.insert(std::make_pair(range_int[i] + 266, range_str[i] + "_two"));
			ft_map_two.insert(ft::make_pair(range_int[i] + 266, range_str[i] + "_two"));
		}

		fs.open("./tester/maps_output/insert_range", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printMapAttributes(fs, stl_map_one, ft_map_one);
		printMapAttributes(fs, stl_map_two, ft_map_two);
		
		stl_map_one.insert(stl_map_two.begin(), stl_map_two.end());
		ft_map_one.insert(ft_map_two.begin(), ft_map_two.end());

		std::cout << ((printMapAttributes(fs, stl_map_one, ft_map_one) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {754, -985, 58, 999, 5};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map_one;\n";
		fs << "ft::map<int, std::string> ft_map_two;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "{\n";
		fs << "	ft_map_one.insert(ft::make_pair(range_int[i], range_str[i]));\n";
		fs << "	ft_map_two.insert(ft::make_pair(range_int[i] + 266, range_str[i] + \"_two\"));\n";
		fs << "}\n";
		fs << "Sending output...\n";
		fs << "ft_map_one.insert(ft_map_two.begin(), ft_map_two.end());\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {754, -985, 58, 999, 5};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map_one;\n";
		fs << "std::map<int, std::string> stl_map_two;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "{\n";
		fs << "	stl_map_one.insert(std::make_pair(range_int[i], range_str[i]));\n";
		fs << "	stl_map_two.insert(std::make_pair(range_int[i] + 266, range_str[i] + \"_two\"));\n";
		fs << "}\n";
		fs << "Sending output...\n";
		fs << "stl_map_one.insert(stl_map_two.begin(), stl_map_two.end());\n";
		fs.close(); 

	}

	/* Erase single */
	{
		const int range_int[] = {-9, -84, -77, 24, 56};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		for (int i = 0; i < 5; i++)
		{
			stl_map.insert(std::make_pair(range_int[i], range_str[i]));
			ft_map.insert(ft::make_pair(range_int[i], range_str[i]));
		}

		fs.open("./tester/maps_output/erase_single", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printMapAttributes(fs, stl_map, ft_map);
		
		stl_map.erase(stl_map.begin());
		ft_map.erase(ft_map.begin());

		std::cout << ((printMapAttributes(fs, stl_map, ft_map) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {-9, -84, -77, 24, 56};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_map.insert(ft::make_pair(range_int[i], range_str[i]));\n";
		fs << "ft_map.erase(ft_map.begin());\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {-9, -84, -77, 24, 56};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_map.insert(std::make_pair(range_int[i], range_str[i]));\n";
		fs << "stl_map.erase(stl_map.begin());\n";
		fs.close(); 
	}

	/* Erase key */
	{
		const int range_int[] = {1452, 3651, -98, 84, 899};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		for (int i = 0; i < 5; i++)
		{
			stl_map.insert(std::make_pair(range_int[i], range_str[i]));
			ft_map.insert(ft::make_pair(range_int[i], range_str[i]));
		}

		fs.open("./tester/maps_output/erase_key", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printMapAttributes(fs, stl_map, ft_map);
		
		stl_map.erase(-98);
		ft_map.erase(-98);

		std::cout << ((printMapAttributes(fs, stl_map, ft_map) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {1452, 3651, -98, 84, 899};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_map.insert(ft::make_pair(range_int[i], range_str[i]));\n";
		fs << "ft_map.erase(-98);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {1452, 3651, -98, 84, 899};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_map.insert(std::make_pair(range_int[i], range_str[i]));\n";
		fs << "stl_map.erase(-98);\n";
		fs.close(); 
	}

	/* Erase range */
	{
        const int range_int[] = {-854, 1, 965, -9, 755};
        const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

        for (int i = 0; i < 5; i++)
        {
            stl_map.insert(std::make_pair(range_int[i], range_str[i]));
            ft_map.insert(ft::make_pair(range_int[i], range_str[i]));
        }

		fs.open("./tester/maps_output/erase_range", std::fstream::in | std::fstream::out | std::fstream::trunc);
        printMapAttributes(fs, stl_map, ft_map);
	    
		std::map<int, std::string>::iterator stl_it_beg = stl_map.begin();
		ft::map<int, std::string>::iterator ft_it_beg = ft_map.begin();
		std::map<int, std::string>::iterator stl_it_end = stl_map.end();
		ft::map<int, std::string>::iterator ft_it_end = ft_map.end();

		for (int i = 0; i < 2; i++)
		{
			stl_it_beg++;
			ft_it_beg++;
		}
		stl_it_end--;
		ft_it_end--;

        stl_map.erase(stl_it_beg, stl_it_end);
        ft_map.erase(ft_it_beg, ft_it_end);

        std::cout << ((printMapAttributes(fs, stl_map, ft_map) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "const int range_int[] = {-854, 1, 965, -9, 755};\n";
        fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    ft_map.insert(ft::make_pair(range_int[i], range_str[i]));\n";
		fs << "ft::map<int, std::string>::iterator ft_it_beg = ft_map.begin();\n";
		fs << "ft::map<int, std::string>::iterator ft_it_end = ft_map.end();\n";
		fs << "for (int i = 0; i < 2; i++)\n";
		fs << "	ft_it_beg++;\n";
		fs << "ft_it_end--;\n";
        fs << "ft_map.erase(ft_it_beg, ft_it_end);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "const int range_int[] = {-854, 1, 965, -9, 755};\n";
        fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map;\n";
        fs << "for (int i = 0; i < 5; i++)\n";
        fs << "    stl_map.insert(std::make_pair(range_int[i], range_str[i]));\n";
		fs << "std::map<int, std::string>::iterator stl_it_beg = stl_map.begin();\n";
		fs << "std::map<int, std::string>::iterator stl_it_end = stl_map.end();\n";
		fs << "for (int i = 0; i < 2; i++)\n";
		fs << "	stl_it_beg++;\n";
		fs << "stl_it_end--;\n";
        fs << "stl_map.erase(stl_it_beg, stl_it_end);\n";
		fs.close(); 
	}

	/* Swap */
	{
		const int range_int[] = {489, 851, 32, -98, 8};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map_one;
		ft::map<int, std::string> ft_map_one;
		std::map<int, std::string> stl_map_two;
		ft::map<int, std::string> ft_map_two;

		for (int i = 0; i < 5; i++)
		{
			stl_map_one.insert(std::make_pair(range_int[i], range_str[i]));
			ft_map_one.insert(ft::make_pair(range_int[i], range_str[i]));
			stl_map_two.insert(std::make_pair(range_int[i] + 120, range_str[i]));
			ft_map_two.insert(ft::make_pair(range_int[i] + 120, range_str[i]));
		}

		fs.open("./tester/maps_output/swap", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printMapAttributes(fs, stl_map_one, ft_map_one);
		printMapAttributes(fs, stl_map_two, ft_map_two);
		
		stl_map_one.swap(stl_map_two);
		ft_map_one.swap(ft_map_two);

		std::cout << ((printMapAttributes(fs, stl_map_one, ft_map_one) == true) ? "[OK]" : "[NOP]");
		std::cout << ((printMapAttributes(fs, stl_map_two, ft_map_two) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {489, 851, 32, -98, 8};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map_one;\n";
		fs << "ft::map<int, std::string> ft_map_two;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "{\n";
		fs << "		ft_map_one.insert(ft::make_pair(range_int[i], range_str[i]));\n";
		fs << "		ft_map_two.insert(ft::make_pair(range_int[i] + 120, range_str[i]));\n";
		fs << "}\n";
		fs << "Sending Output...\n";
		fs << "ft_map_one.swap(ft_map_two);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {489, 851, 32, -98, 8};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map_one;\n";
		fs << "std::map<int, std::string> stl_map_two;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "{\n";
		fs << "		stl_map_one.insert(std::make_pair(range_int[i], range_str[i]));\n";
		fs << "		stl_map_two.insert(std::make_pair(range_int[i] + 120, range_str[i]));\n";
		fs << "}\n";
		fs << "Sending Output...\n";
		fs << "stl_map_one.swap(stl_map_two);\n";
		fs.close();
	}

	/* Clear */
	{
		const int range_int[] = {148, 9874, -987, 52, 96};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		for (int i = 0; i < 5; i++)
		{
			stl_map.insert(std::make_pair(range_int[i], range_str[i]));
			ft_map.insert(ft::make_pair(range_int[i], range_str[i]));
		}

		fs.open("./tester/maps_output/clear", std::fstream::in | std::fstream::out | std::fstream::trunc);
		printMapAttributes(fs, stl_map, ft_map);
		
		stl_map.clear();
		ft_map.clear();

		std::cout << ((printMapAttributes(fs, stl_map, ft_map) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {148, 9874, -987, 52, 96};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_map.insert(ft::make_pair(range_int[i], range_str[i]));\n";
		fs << "ft_map.clear()\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {148, 9874, -987, 52, 96};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_map.insert(std::make_pair(range_int[i], range_str[i]));\n";
		fs << "stl_map.clear()\n";
		fs.close();
	}

	std::cout << std::endl;
	std::cout << "Observers : ";

	/* Key comp */
	{
		std::map<int, std::string>::key_compare stl_key = std::map<int, std::string>().key_comp();
		ft::map<int, std::string>::key_compare ft_key = ft::map<int, std::string>().key_comp();

		bool stl_res = stl_key(42, 99);
		bool ft_res = ft_key(42, 99);

		fs.open("./tester/maps_output/key_comp", std::fstream::in | std::fstream::out | std::fstream::trunc);
		std::cout << ((printBoolResult(fs, stl_res, ft_res) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "ft::map<int, std::string>::key_compare ft_key = ft::map<int, std::string>().key_comp();\n";
		fs << "bool ft_res = ft_key(42, 99);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "std::map<int, std::string>::key_compare stl_key = std::map<int, std::string>().key_comp();\n";
		fs << "bool stl_res = stl_key(42, 99);\n";
		fs.close();  
	}

	/* Value comp */
	{
		std::map<int, std::string>::value_compare stl_key = std::map<int, std::string>().value_comp();
		ft::map<int, std::string>::value_compare ft_key = ft::map<int, std::string>().value_comp();

		bool stl_res = stl_key(std::make_pair(99, "End"), std::make_pair(42, "Noice"));
		bool ft_res = ft_key(ft::make_pair(99, "End"), ft::make_pair(42, "Noice"));

		fs.open("./tester/maps_output/value_comp", std::fstream::in | std::fstream::out | std::fstream::trunc);
		std::cout << ((printBoolResult(fs, stl_res, ft_res) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "ft::map<int, std::string>::value_compare ft_key = ft::map<int, std::string>().value_comp();\n";
		fs << "bool ft_res = ft_key(ft::make_pair(99, \"End\"), ft::make_pair(42, \"Noice\"));\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "std::map<int, std::string>::value_compare stl_key = std::map<int, std::string>().value_comp();\n";
		fs << "bool stl_res = stl_key(std::make_pair(99, \"End\"), std::make_pair(42, \"Noice\"));\n";
		fs.close();  
	}

	std::cout << std::endl;
	std::cout << "Operations : ";

	/* Find exist */
	{
		const int range_int[] = {954, 12, -965, 42, 1000};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		for (int i = 0; i < 5; i++)
		{
			stl_map.insert(std::make_pair(range_int[i], range_str[i]));
			ft_map.insert(ft::make_pair(range_int[i], range_str[i]));
		}

		fs.open("./tester/maps_output/find_exist", std::fstream::in | std::fstream::out | std::fstream::trunc);

		std::map<int, std::string>::iterator stl_it = stl_map.find(42);		
		ft::map<int, std::string>::iterator ft_it = ft_map.find(42);
		
		printMapAttributes(fs, stl_map, ft_map);
		
		std::cout << "[";
		std::cout << ((printSingleValue(fs, (*stl_it).first, (*ft_it).first) == true) ? "[OK]" : "[NOP]");
		std::cout << ((printSingleValue(fs, (*stl_it).second, (*ft_it).second) == true) ? "[OK]" : "[NOP]");
		std::cout << "]";

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {954, 12, -965, 42, 1000};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_map.insert(ft::make_pair(range_int[i], range_str[i]));\n";
		fs << "ft::map<int, std::string>::iterator ft_it = ft_map.find(42);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {954, 12, -965, 42, 1000};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_map.insert(std::make_pair(range_int[i], range_str[i]));\n";
		fs << "std::map<int, std::string>::iterator stl_it = stl_map.find(42);\n";
		fs.close(); 
	}

	/* Find not exist*/
	{
		const int range_int[] = {14, 985, 578, -23, 47};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		for (int i = 0; i < 5; i++)
		{
			stl_map.insert(std::make_pair(range_int[i], range_str[i]));
			ft_map.insert(ft::make_pair(range_int[i], range_str[i]));
		}

		fs.open("./tester/maps_output/find_not_exist", std::fstream::in | std::fstream::out | std::fstream::trunc);

		std::map<int, std::string>::iterator stl_it = stl_map.find(42);		
		ft::map<int, std::string>::iterator ft_it = ft_map.find(42);
		
		printMapAttributes(fs, stl_map, ft_map);
		
		std::cout << ((printBoolResult(fs, (stl_it == stl_map.end()), (ft_it == ft_map.end())) == true) ? "[OK]" : "[NOP]");

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {14, 985, 578, -23, 47};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_map.insert(ft::make_pair(range_int[i], range_str[i]));\n";
		fs << "ft::map<int, std::string>::iterator ft_it = ft_map.find(42);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {14, 985, 578, -23, 47};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_map.insert(std::make_pair(range_int[i], range_str[i]));\n";
		fs << "std::map<int, std::string>::iterator stl_it = stl_map.find(42);\n";
		fs.close(); 
	}

	/* Const it Find */
	{
		const int range_int[] = {842, -965, 99, 52, 65};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		for (int i = 0; i < 5; i++)
		{
			stl_map.insert(std::make_pair(range_int[i], range_str[i]));
			ft_map.insert(ft::make_pair(range_int[i], range_str[i]));
		}

		fs.open("./tester/maps_output/find_const_exist", std::fstream::in | std::fstream::out | std::fstream::trunc);

		std::map<int, std::string>::const_iterator stl_it = stl_map.find(99);		
		ft::map<int, std::string>::const_iterator ft_it = ft_map.find(99);
		
		printMapAttributes(fs, stl_map, ft_map);
		
		std::cout << "[";
		std::cout << ((printSingleValue(fs, (*stl_it).first, (*ft_it).first) == true) ? "[OK]" : "[NOP]");
		std::cout << ((printSingleValue(fs, (*stl_it).second, (*ft_it).second) == true) ? "[OK]" : "[NOP]");
		std::cout << "]";

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {842, -965, 99, 52, 65};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_map.insert(ft::make_pair(range_int[i], range_str[i]));\n";
		fs << "ft::map<int, std::string>::const_iterator ft_it = ft_map.find(99);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {842, -965, 99, 52, 65};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_map.insert(std::make_pair(range_int[i], range_str[i]));\n";
		fs << "std::map<int, std::string>::const_iterator stl_it = stl_map.find(99);\n";
		fs.close();
	}

	/* Count */
	{
		const int range_int[] = {842, 654, 95, -98, -8};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		for (int i = 0; i < 5; i++)
		{
			stl_map.insert(std::make_pair(range_int[i], range_str[i]));
			ft_map.insert(ft::make_pair(range_int[i], range_str[i]));
		}

		fs.open("./tester/maps_output/count", std::fstream::in | std::fstream::out | std::fstream::trunc);
		
		printMapAttributes(fs, stl_map, ft_map);

		std::cout << "[";
		std::cout << ((printBoolResult(fs, (stl_map.count(-98) > 0), (ft_map.count(-98) > 0)) == true) ? "[OK]" : "[NOP]");
		std::cout << ((printBoolResult(fs, (stl_map.count(42) > 0), (ft_map.count(42) > 0)) == true) ? "[OK]" : "[NOP]");
		std::cout << "]";

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {842, 654, 95, -98, -8};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_map.insert(ft::make_pair(range_int[i], range_str[i]));\n";
		fs << "Search for -98 & 42\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {842, 654, 95, -98, -8};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_map.insert(std::make_pair(range_int[i], range_str[i]));\n";
		fs << "Search for -98 & 42\n";
		fs.close(); 
	}

	/* Lower bound */
	{
		const int range_int[] = {351, -999, 5, 76, 61};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		for (int i = 0; i < 5; i++)
		{
			stl_map.insert(std::make_pair(range_int[i], range_str[i]));
			ft_map.insert(ft::make_pair(range_int[i], range_str[i]));
		}

		fs.open("./tester/maps_output/lower_bound", std::fstream::in | std::fstream::out | std::fstream::trunc);
		
		printMapAttributes(fs, stl_map, ft_map);

		std::map<int, std::string>::iterator stl_it = stl_map.lower_bound(80);
		ft::map<int, std::string>::iterator ft_it = ft_map.lower_bound(80);

		std::cout << "[";
		std::cout << ((printSingleValue(fs, (*stl_it).first, (*ft_it).first) == true) ? "[OK]" : "[NOP]");
		std::cout << ((printSingleValue(fs, (*stl_it).second, (*ft_it).second) == true) ? "[OK]" : "[NOP]");
		std::cout << "]";

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {351, -999, 5, 76, 61};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_map.insert(ft::make_pair(range_int[i], range_str[i]));\n";
		fs << "ft::map<int, std::string>::iterator ft_it = ft_map.lower_bound(80);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {351, -999, 5, 76, 61};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_map.insert(std::make_pair(range_int[i], range_str[i]));\n";
		fs << "std::map<int, std::string>::iterator stl_it = stl_map.lower_bound(80);\n";
		fs.close(); 
	}
	
	/* Const it Lower bound */
	{
		const int range_int[] = {554, 62, 345, 98, -77};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		for (int i = 0; i < 5; i++)
		{
			stl_map.insert(std::make_pair(range_int[i], range_str[i]));
			ft_map.insert(ft::make_pair(range_int[i], range_str[i]));
		}

		fs.open("./tester/maps_output/lower_bound_const", std::fstream::in | std::fstream::out | std::fstream::trunc);
		
		printMapAttributes(fs, stl_map, ft_map);

		std::map<int, std::string>::const_iterator stl_it = stl_map.lower_bound(80);
		ft::map<int, std::string>::const_iterator ft_it = ft_map.lower_bound(80);

		std::cout << "[";
		std::cout << ((printSingleValue(fs, (*stl_it).first, (*ft_it).first) == true) ? "[OK]" : "[NOP]");
		std::cout << ((printSingleValue(fs, (*stl_it).second, (*ft_it).second) == true) ? "[OK]" : "[NOP]");
		std::cout << "]";

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {554, 62, 345, 98, -77};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_map.insert(ft::make_pair(range_int[i], range_str[i]));\n";
		fs << "ft::map<int, std::string>::const_iterator ft_it = ft_map.lower_bound(80);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {554, 62, 345, 98, -77};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_map.insert(std::make_pair(range_int[i], range_str[i]));\n";
		fs << "std::map<int, std::string>::const_iterator stl_it = stl_map.lower_bound(80);\n";
		fs.close(); 
	}

	/* Upper bound */
	{
		const int range_int[] = {45, -84, 957, 966, 3};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		for (int i = 0; i < 5; i++)
		{
			stl_map.insert(std::make_pair(range_int[i], range_str[i]));
			ft_map.insert(ft::make_pair(range_int[i], range_str[i]));
		}

		fs.open("./tester/maps_output/upper_bound", std::fstream::in | std::fstream::out | std::fstream::trunc);
		
		printMapAttributes(fs, stl_map, ft_map);

		std::map<int, std::string>::iterator stl_it = stl_map.upper_bound(950);
		ft::map<int, std::string>::iterator ft_it = ft_map.upper_bound(950);

		std::cout << "[";
		std::cout << ((printSingleValue(fs, (*stl_it).first, (*ft_it).first) == true) ? "[OK]" : "[NOP]");
		std::cout << ((printSingleValue(fs, (*stl_it).second, (*ft_it).second) == true) ? "[OK]" : "[NOP]");
		std::cout << "]";

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {45, -84, 957, 966, 3};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_map.insert(ft::make_pair(range_int[i], range_str[i]));\n";
		fs << "ft::map<int, std::string>::iterator ft_it = ft_map.upper_bound(950);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {45, -84, 957, 966, 3};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_map.insert(std::make_pair(range_int[i], range_str[i]));\n";
		fs << "std::map<int, std::string>::iterator stl_it = stl_map.upper_bound(950);\n";
		fs.close(); 
	}

	/* Const it Upper bound */
	{
		const int range_int[] = {963, 654, 789, -9, 85};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		for (int i = 0; i < 5; i++)
		{
			stl_map.insert(std::make_pair(range_int[i], range_str[i]));
			ft_map.insert(ft::make_pair(range_int[i], range_str[i]));
		}

		fs.open("./tester/maps_output/upper_bound_const", std::fstream::in | std::fstream::out | std::fstream::trunc);
		
		printMapAttributes(fs, stl_map, ft_map);

		std::map<int, std::string>::const_iterator stl_it = stl_map.upper_bound(950);
		ft::map<int, std::string>::const_iterator ft_it = ft_map.upper_bound(950);

		std::cout << "[";
		std::cout << ((printSingleValue(fs, (*stl_it).first, (*ft_it).first) == true) ? "[OK]" : "[NOP]");
		std::cout << ((printSingleValue(fs, (*stl_it).second, (*ft_it).second) == true) ? "[OK]" : "[NOP]");
		std::cout << "]";

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {963, 654, 789, -9, 85};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_map.insert(ft::make_pair(range_int[i], range_str[i]));\n";
		fs << "ft::map<int, std::string>::const_iterator ft_it = ft_map.upper_bound(950);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {963, 654, 789, -9, 85};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_map.insert(std::make_pair(range_int[i], range_str[i]));\n";
		fs << "std::map<int, std::string>::const_iterator stl_it = stl_map.upper_bound(950);\n";
		fs.close();
	}

	/* Equal range */
	{
		const int range_int[] = {-741, 520, 65, -84, -1};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		for (int i = 0; i < 5; i++)
		{
			stl_map.insert(std::make_pair(range_int[i], range_str[i]));
			ft_map.insert(ft::make_pair(range_int[i], range_str[i]));
		}

		fs.open("./tester/maps_output/equal_range_const", std::fstream::in | std::fstream::out | std::fstream::trunc);
		
		printMapAttributes(fs, stl_map, ft_map);

		std::cout << "[";
		std::cout << ((printSingleValue(fs, (*(stl_map.equal_range(65).first)).first, (*(ft_map.equal_range(65).first)).first) == true) ? "[OK]" : "[NOP]");
		std::cout << ((printSingleValue(fs, (*(stl_map.equal_range(65).second)).first, (*(ft_map.equal_range(65).second)).first) == true) ? "[OK]" : "[NOP]");
		std::cout << "]";

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {-741, 520, 65, -84, -1};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_map.insert(ft::make_pair(range_int[i], range_str[i]));\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {-741, 520, 65, -84, -1};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_map.insert(std::make_pair(range_int[i], range_str[i]));\n";
		fs.close();
	}

	std::cout << "\n";
}