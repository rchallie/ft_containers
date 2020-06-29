/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: excalibur <excalibur@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 15:44:08 by excalibur         #+#    #+#             */
/*   Updated: 2020/06/29 20:24:45 by excalibur        ###   ########.fr       */
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
                typedef typename ft::Binary_search_tree<value_type>::const_iterator const_iterator;

                // typedef typename ft::...:reverse_iterator    reverse_iterator;

                // typedef typename ft::...:const_reverse_iterator const_reverse_iterator;
            
                typedef typename ft::iterator_traits<iterator>::difference_type difference_type;

                typedef size_t size_type;

                /*
                ** @brief Default.
                ** Create a map container object.
                ** Construct an empty container, with no elements.
                **
                ** @param comp the comparator object.
                ** @param alloc the allocator object.
                */
                explicit Map (const key_compare& comp = key_compare(),
                                const allocator_type& alloc = allocator_type())
                    :
                        _comp(comp),
                        _alloc(alloc),
                        _bst()
                    {}
                    
                // template <class InputIterator>
                //     Map (InputIterator first, InputIterator last,
                //         const key_compare& comp = key_compare(),
                //         const allocator_type& alloc = allocator_type());

                /*
                ** @brief Copy.
                ** Create a map container object.
                ** Construct a container with a copy of each of the element
                ** in x.
                ** the elements in "x".
                **
                ** @param x the map to copy.
                */
                Map (const Map& x)
                :
                    _comp(x._comp),
                    _alloc(x._alloc),
                    _bst(x._bst)
                {}

                /*
                ** @brief Destruct the Map container.
                */
                virtual ~Map() {}

                Map& operator= (const Map& x);

                // Iterators :
                
                iterator begin()
                { return iterator(_bst.get_lower_node()); }

                const_iterator begin() const
                { return const_iterator(_bst.get_lower_node()); }

                iterator end()
                { return (iterator(_bst.get_header_node())); }

                const_iterator end() const
                { return (const_iterator(_bst.get_header_node())); }

                // reverse_iterator rbegin();

                // const_reverse_iterator rbegin() const;

                // reverse_iterator rend();

                // const_reverse_iterator rend() const;

                // Capacity

                /*
                ** @brief Give a boolean that represent
                ** if the container is empty.
                **
                ** return true if the container is empty,
                ** otherwise false.
                */
                bool empty() const
                { return ((_bst.size() != 0) ? false : true); }

                /*
                ** @brief Give the size of the container.
                **
                ** @return the size.
                */
                size_type size() const
                { return (size_type(_bst.size())); }

                /*
                ** @brief Give the maximum number of elements
                ** that the container can hold.
                ** This maximum potential size due to library implementation.
                ** Here it's the number of node that how many node
                ** a binary search tree can create.
                **
                ** @return the maximum size. 
                */
                size_type max_size() const
                { return (_bst.max_size()); }

                // Element access:

                mapped_type& operator[] (const key_type& k);

                // Modifiers:

                ft::pair<iterator, bool> insert (const value_type& val)
                {
                    bool exist = (_bst.search(val) == u_nullptr) ? true : false;
                    _bst.insert(val);
                    node_pointer node = _bst.search(val);
                    return (ft::make_pair(iterator(node), exist));
                }

                iterator insert (iterator position, const value_type& val);

                template <class InputIterator>
                    void insert (InputIterator first, InputIterator last);

                void erase (iterator position);

                size_type erase (const key_type& k);

                void erase (iterator first, iterator last);

                void swap (Map& x);

                void clear();

                // Observers:

                key_compare key_comp() const;

                value_compare value_comp() const;

                // Operations:

                /*
                ** @brief Search in the container to find the pair
                ** that have like key "k".
                **
                ** @param k the key to find.
                ** @return the pair object that contain 
                */
                iterator find (const key_type& k)
                {
                    // ft::Node<value_type>* root = _bst.get_lower_node();   
                    // value_compare comp = key_compare;
                    // ft::pair<key_type, value_type> tmp = ft::make_pair(k, mapped_type());
                    
                    // while (root)
                    // {
                    //     if (comp(root->value, tmp) == false && comp (tmp, root->value) == false)
                    //         return (root);
                    //     root = _bst.next(root);
                    // }
                    // return (this->end());
                }

                const_iterator find (const key_type& k) const
                {
ç
                }

                size_type count (const key_type& k) const;

                iterator lower_bound (const key_type& k);

                const_iterator lower_bound (const key_type& k) const;

                iterator upper_bound (const key_type& k);

                const_iterator upper_bound (const key_type& k) const;

                ft::pair<const_iterator, const_iterator> equal_range (const key_type& k) const;

                ft::pair<iterator, iterator> equal_range (const key_type& k);
                
            private:

                typedef ft::Binary_search_tree<value_type> bst;
                
                typedef typename bst::node_pointer node_pointer;

                key_compare _comp;
                allocator_type _alloc;
                bst _bst;
        };

}

// =============================================================================


#endif