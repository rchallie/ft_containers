/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: excalibur <excalibur@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 15:44:08 by excalibur         #+#    #+#             */
/*   Updated: 2020/06/23 23:00:46 by excalibur        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Documentation :
** (fr) https://github.com/rchallie/ft_containers/blob/master/map.txt
** http://www.cplusplus.com/reference/map/map/?kw=map
*/

/* TODO Tomorrow :
    - Node
    - Binary Search Tree for pair
    - Bidirectional iterator
    */
   
#ifndef MAP_HPP
 #define MAP_HPP

// LIBS ========================================================================
# include "Utils.hpp"
// =============================================================================

// CLASS DEFINITIONS ===========================================================

namespace ft
{

    template < class Key, class T, class Compare = ft::less<Key>,
                class Alloc = std::allocator<ft::pair<const Key, T> > >
        class Map
        {
            public:

                /* The first template parameter (Key) */
                typedef Key     key_type;

                /* The second template parameter (T) */
                typedef T       mapped_type;

                /* The map value type */
                typedef ft::pair<const key_type, mapped_type> value_type;

                /* The third template parameter (Compare) */
                typedef Compare     key_compare;

                /* Function class to compare elements */
                class value_compare : ft::binary_function<value_type, value_type, bool>
                {
                    protected:
                        Compare comp;
                        value_compare (Compare c) : comp(c) {}
                    
                    public:

                        /* Result type, first argument type and second argument type are
                        ** stocked int binary_function.
                        */

                        /*
                        ** @brief Call the compare function to compare
                        ** "x" and "y".
                        **
                        ** @param x,y values to compare.
                        ** @return boolean from comparison function.
                        */
                        bool operator() (const value_type& x, const value_type& y) const
                        { return (comp(x.first, y.first)); }
                };

                /* The fourth template parameter (Alloc) */
                typedef Alloc  allocator_type;

                /* A reference to value_type */
                typedef typename allocator_type::reference   reference;

                /* A const reference to value_type */
                typedef typename allocator_type::const_reference const_reference;

                /* A pointer to value_type */
                typedef typename allocator_type::pointer     pointer;

                /* A const pointer to value_type */
                typedef typename allocator_type::const_pointer const_pointer;

                /* A bidirectional iterator to value_type */
                typedef typename ft::Binary_search_tree<value_type>::iterator iterator;

                /* A bidirectional iterator to const value_type */
                typedef typename ft::Binary_search_tree<const value_type>::const_iterator const_iterator;

            private:

                ft::Binary_search_tree<value_type> _bst;
        };

}

// =============================================================================


#endif