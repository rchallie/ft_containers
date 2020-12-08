/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester_map.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchallie <rchallie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 18:22:17 by rchallie          #+#    #+#             */
/*   Updated: 2020/12/08 16:47:15 by rchallie         ###   ########.fr       */
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

	typename ft::map<Ta, Tb>::iterator ft_it;
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
		fs << "ft::map<int> ft_default_map;\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "std::map<int> stl_default_map;\n";
		fs.close();     
	}

    /* Range constrcutor */
    {

    }

    /* Copy constructor */
    {

    }

    /* Assign operator */
    {

    }

    /* Begin */
    {

    }

    /* Const begin */
    {

    }

    /* End */
    {

    }

    /* Const end */
    {

    }

    /* Reverse begin */
    {

    }

    /* Const reverse begin */
    {

    }

    /* Reverse end */
    {

    }

    /* Const reverse end */
    {

    }

    std::cout << std::endl;
	std::cout << "Capacity : ";

    /* Empty true */
    {

    }

    /* Empty false */
    {

    }

    /* Size */
    {

    }

    /* Size after resize */
    {

    }

    /* Maximum size */
    {

    }

    std::cout << std::endl;
	std::cout << "Element access : ";

    /* Operator [] */
    {

    }

    /* Operator [] exception */
    {

    }

    std::cout << std::endl;
	std::cout << "Modifier : ";

    /* Insert single */
    {

    }

    /* Insert hint */
    {

    }

    /* Insert Range */
    {

    }

    /* Erase single */
    {

    }

    /* Erase key */
    {

    }

    /* Erase range */
    {

    }

    /* Swap */
    {

    }

    /* Clear */
    {

    }

    std::cout << std::endl;
	std::cout << "Observers : ";

    /* Key comp */
    {

    }

    /* Value comp */
    {

    }

    std::cout << std::endl;
	std::cout << "Operations : ";

    /* Find */
    {

    }

    /* Const it Find */
    {

    }

    /* Count */
    {

    }

    /* Lower bound */
    {

    }
    
    /* Const it Lower bound */
    {

    }

    /* Upper bound */
    {
        
    }

    /* Const it Upper bound */
    {
        
    }

    /* Const it Equal range */
    {

    }

    /* Equal range */
    {

    }
}