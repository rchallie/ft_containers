/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchallie <rchallie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 17:14:11 by rchallie          #+#    #+#             */
/*   Updated: 2020/12/08 23:01:18 by rchallie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

#include "./utils/utils.hpp"
#include "./utils/binary_search_tree.hpp"

namespace ft
{
    template < class Key, class T, class Compare = ft::less<Key>,
                class Alloc = std::allocator<ft::pair<const Key, T> > >
    class map
    {
        public:

			/*
			** The first template parameter (Key)
			*/
            typedef Key     key_type;

			/*
			** The second template parameter (T)
			*/
            typedef T       mapped_type;

            /*
            ** Type of stocked value create with Key and T.
            ** pair<Key, T>
            */
            typedef ft::pair<key_type, mapped_type> value_type;

            /*
			** The third template parameter (Compare)
			*/
            typedef Compare     key_compare;

            /* 
            ** Function class to compare elements
            */
            class value_compare : ft::binary_function<value_type, value_type, bool>
            {
                friend class map;
                
                protected:
                    Compare comp;
                    value_compare (Compare c) : comp(c) {}
                
                public:

                    /* 
                    ** Result type, first argument type and second argument type are
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

			/*
			** The fourth template parameter (Alloc)
			*/
            typedef Alloc  allocator_type;


			/*
			** allocator_type::reference
			** A type provides a reference to an element stored in
			** a list.
			** For the default allocator is a reference to value_type
			** (value_type&)
			*/
            typedef typename allocator_type::reference   reference;

			/*
			** allocator_type::const_reference
			** Type that give a reference to a const element stored.
			** Usefull to read and perform const operator.
			** A type const_reference can't be used to modify the value
			** of an element.
			** For the default allocator is a const reference to value_type
			** (const value_type&)
			*/
            typedef typename allocator_type::const_reference const_reference;

			/*
			** allocator_type::pointer
			** Type that give a pointer to an element stored.
			** A type pointer can be used to modify the value of
			** an element.
			** For the default allocator is a pointer to value_type
			** (value_type*)
			*/
            typedef typename allocator_type::pointer     pointer;

			/*
			** allocator_type::const_pointer
			** Type that give a const pointer to an element stored.
			** Can't be used to modify the value of an element.
			** An iterator is prefered to access to an element.
			** For the default allocator is a const pointer to value_type
			** (const value_type*)
			*/
            typedef typename allocator_type::const_pointer const_pointer;

			/*
			** A bidirectional iterator to value_type
			** That can read or modify any element stored.
			** Convertible to const_iterator;
			*/
            typedef typename ft::Binary_search_tree<value_type, key_compare>::iterator iterator;

			/*
			** A bidirectional iterator to const value_type
			** That can read element stored.
			*/
            typedef typename ft::Binary_search_tree<value_type, key_compare>::const_iterator const_iterator;

			/*
			** ft::reverse_iterator<iterator>
			** That can read or modify any element in a reversed container.
			** Used to iterate through the container in reverse.
			*/
            typedef typename ft::reverse_iterator<iterator>    reverse_iterator;

			/*
			** ft::reverse_iterator<const_iterator>
			** That can read any element in a reversed the container.
			** Can't be used to modify, used to iterate through the
			** the container in reverse.
			*/
            typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;
        
            /*
			** A signed integral type:
			** Usually the same as ptrdiff_t.
			** Can represent the difference between iterators to the
			** element actually stored.
			** Can be described as the number of element between two pointers.
			** (Pointer to an element contains its address).
			*/
            typedef typename ft::iterator_traits<iterator>::difference_type difference_type;

			/*
			** An unsigned integral type that can represent any
			** non-negative value of difference_type
			** Usually the same as size_t.
			*/
            typedef size_t size_type;

			/*
			** @brief Default :
			** Construct an empty map container object.
			**
			** @param alloc the Allocator type.
			*/
            explicit map (const key_compare& comp = key_compare(),
                const allocator_type& alloc = allocator_type())
            :
                _alloc(alloc),
                _comp(comp),
                _bst()
            {}

            // template <class InputIterator>
            //     map (InputIterator first, InputIterator last,
            //         const key_compare& comp = key_compare(),
            //         const allocator_type& alloc = allocator_type());
            
            // map(const map& x);

            // ~map();

            // map& operator= (const map& x);

			/*
			** @brief Return an iterator pointing on the first element
			** in the container. If the container is empty, the
			** returned iterator value shall no be dereferenced.
			** The iterator is of type iterator (bidirectional iterator
			** on value_type reference).
			**
			** @return The iterator to the first element.
			*/
            iterator begin()
            { return (iterator(_bst._last_node->left, _bst._last_node)); }

			/*
			** @brief Return a const iterator pointing on the first element
			** in the container. If the container is empty, the
			** returned iterator value shall no be dereferenced.
			** The iterator is of type const_iterator (bidirectional
			** iterator on const value_type reference).
			**
			** @return The const iterator to the first element.
			*/
            const_iterator begin() const
            { return (const_iterator(_bst._last_node->left, _bst._last_node)); }

			/*
			** @brief Return an iterator pointing on the past-the-end element
			** in the container. Past-the-end is the theorical element
			** following the last element in the container. If the container is
			** empty, return the same than begin.
			** The iterator is of type iterator (bidirectional iterator
			** on value_type reference).
			**
			** @return The iterator to the past-the-end element or begin if
			** the container is empty.
			*/
            iterator end()
            { return (iterator(_bst._last_node, _bst._last_node)); }

			/*
			** @brief Return a const iterator pointing on the past-the-end element
			** in the container. Past-the-end is the theorical element
			** following the last element in the container. If the container is
			** empty, return the same than begin.
			** The iterator is of type const_iterator (bidirectional
			** iterator on const value_type reference).
			**
			** @return The const iterator to the past-the-end element or begin if
			** the container is empty.
			*/
            const_iterator end() const
            { return (const_iterator(_bst._last_node, _bst._last_node)); }

            // reverse_iterator rbegin();

            // const_reverse_iterator rbegin() const;

            // reverse_iterator rend();

            // const_reverse_iterator rend() const;

			/*
			** @brief Returns whether the container is empty.
			** Does not modify container in any way.
			**
			** @return true if the container size is 0, false otherwise.
			*/
            bool empty() const
            { return (_bst._last_node->parent == _bst._last_node); }

			/*
			** @brief return the number of elements
			** in the container.
			**
			** @return the number of elements.
			*/
            size_type size() const
            {
                size_type rtn = 0;

                const_iterator beg = this->begin();
                const_iterator end = this->end();

                while (beg++ != end)
                    rtn++;
                return (rtn);
            }

			/*
			** @brief Returns the maximum potential number of elements the the
			** container can hold.
			** This size is due to known system or library limitations.
			** The container is not garanteed to have this size, it can
			** fail a allocation for exemple.
			** 
			** Documentation :
			** https://www.viva64.com/en/a/0050/
			**
			** @return The maximum potential number of elements the
			** container can hold.
			** (An unsigned integral type)
			*/
            size_type max_size() const
            { return (_bst.max_size()); }

            // mapped_type& operator[] (const key_type& k);

            /*
            ** @brief Insert a "value_type" (pair) in the container.
            ** Can increase the container size.
            **
            ** @param val the pair to add to the container.
            ** @return An pair containing in key the iterator
            ** position of the inserted value and contain
            ** a bool at true if a new element was inserted
            ** or false if an equivalent key already exist, on value.
            */
            pair<iterator,bool> insert (const value_type& val)
            {
                return (_bst.insertPair(val));
            }

            // iterator insert (iterator position, const value_type& val);

            /*
            template <class InputIterator>
                void insert (InputIterator first, InputIterator last);
            */

            // void erase (iterator position);

            // size_type erase (const key_type& k);
   
            //  void erase (iterator first, iterator last);

            // void swap (map& x);

            // void clear();

            // key_compare key_comp() const;

            // value_compare value_comp() const;

            // iterator find (const key_type& k);

            // const_iterator find (const key_type& k) const;

            // size_type count (const key_type& k) const;

            // iterator lower_bound (const key_type& k);

            // const_iterator lower_bound (const key_type& k) const;

            // iterator upper_bound (const key_type& k);

            // const_iterator upper_bound (const key_type& k) const;

            // pair<const_iterator,const_iterator> equal_range (const key_type& k) const;
            
            // pair<iterator,iterator>             equal_range (const key_type& k);

        private:

            allocator_type                          _alloc;
            Compare                                 _comp;
            Binary_search_tree<value_type, Compare>  _bst;

    };
}

#endif