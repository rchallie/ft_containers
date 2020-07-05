/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: excalibur <excalibur@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 15:44:08 by excalibur         #+#    #+#             */
/*   Updated: 2020/07/01 09:29:54 by excalibur        ###   ########.fr       */
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
                typedef ft::pair<key_type, mapped_type> value_type;

                /* The third template parameter (Compare) */
                typedef Compare     key_compare;

                /* Function class to compare elements */
                class value_compare : ft::binary_function<value_type, value_type, bool>
                {
                    friend class map;
                    
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
                        _key_comp(comp),
                        _alloc(alloc),
                        _bst()
                    {}
                    
                // template <class InputIterator>
                //     Map (InputIterator first, InputIterator last,
                //         const key_keyare& comp = key_compare(),
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
                    _key_comp(x._comp),
                    _alloc(x._alloc),
                    _bst(x._bst)
                {}

                /*
                ** @brief Destruct the Map container.
                */
                virtual ~Map() {}

                Map& operator= (const Map& x);

                // Iterators :
                
                /*
                ** @brief Return an iterator that pointing to the
                ** first element in the container. If the container is
                ** empty, the iterator value can't be dereferenced.
                **
                ** @return the iterator.
                */
                iterator begin()
                { return iterator(_bst.get_root_node(), _bst.get_lower_node()); }

                /*
                ** @brief Return an const iterator that pointing to the
                ** first element in the container. If the container is
                ** empty, the const iterator value can't be dereferenced.
                **
                ** @return the const iterator.
                */
                const_iterator begin() const
                { return const_iterator(_bst.get_root_node(), _bst.get_lower_node()); }

                /*
                ** @brief Return an iterator that pointing to the element
                ** that is concidered to be the last element in the container.
                ** This iterator really pointing to a value that can't be
                ** dereferenced, it is most often used like comparison with
                ** begin().
                **
                ** @return the iterator.
                */
                iterator end()
                { return (iterator(_bst.get_root_node(), u_nullptr)); }

                /*
                ** @brief Return an const iterator that pointing to the element
                ** that is concidered to be the last element in the container.
                ** This const iterator really pointing to a value that can't be
                ** dereferenced, it is most often used like comparison with
                ** begin().
                **
                ** @return the const iterator.
                */
                const_iterator end() const
                { return (const_iterator(_bst.get_root_node(), u_nullptr)); }

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

                /*
                ** @brief If "k" match with the key of an
                ** element in the container, this will return 
                ** the mapped value from this element. If "k" doesn't
                ** match, this will insert a new element with "k" like
                ** key and a mapped value initialized.
                **
                ** @param k the key.
                ** @return an reference to the mapped value.
                */
                mapped_type& operator[] (const key_type& k)
                { return ((*((this->insert(ft::make_pair(k,mapped_type()))).first)).second); }

                // Modifiers:

                ft::pair<iterator, bool> insert (const value_type& val)
                {
                    bool exist = (this->find(val.first) == this->end()) ? true : false;
                    if (exist == false)
                        return (ft::make_pair(this->find(val.first), exist));
                    _bst.insert(val);
                    return (ft::make_pair(iterator(_bst.get_root_node(), _bst.search(val)), exist));
                }

                iterator insert (iterator position, const value_type& val);

                template <class InputIterator>
                    void insert (InputIterator first, InputIterator last);

                /*
                ** @brief Remove the element in the container at the iterator
                ** position. Reduce the size of the container.
                **
                ** @param position the iterator pointing to the element to remove.
                */
                void erase (iterator position)
                { _bst.remove((*position)); }

                /*
                ** @brief Remove the element in the container that has like key
                ** "k". Reduce the size of the container.
                **
                ** @param k the key.
                ** @return The number of element removed, 0 if no element have "k"
                ** like key, 1 otherwise.
                */
                size_type erase (const key_type& k)
                {
                    const_iterator it = this->find(k);

                    if (it == this->end())
                        return (0);
                    _bst.remove((*it));
                    return (1);
                }

                void erase (iterator first, iterator last)
                {
                    while (first != last)
                    {
                        this->erase(*first++);
                    }
                }

                void swap (Map& x);

                void clear();

                // Observers:

                /*
                ** @brief Return a copy of the key comparison object.
                **
                ** @param the key comparison object.
                */
                key_compare key_comp() const
                { return (key_compare()); }

                /*
                ** @brief Return a copy of the value comparison object.
                **
                ** @param the value comparison object.
                */
                value_compare value_comp() const
                { return (value_compare()); }

                // Operations:

                /*
                ** @brief Search in the container to find the pair
                ** that have like key "k".
                **
                ** @param k the key to find.
                ** @return an iterator pointing to the pair object that
                ** have like key "k". 
                */
                iterator find (const key_type& k)
                {
                    const_iterator it = this->begin();

                    for (; it != this->end(); it++)
                        if (_key_comp(it->first, k) == false && _key_comp(k, it->first) == false)
                            return (it);
                    return (this->end());
                }

                /*
                ** @brief Search in the container to find the pair
                ** that have like key "k".
                **
                ** @param k the key to find.
                ** @return an const iterator pointing to the pair object that
                ** have like key "k". 
                */
                const_iterator find (const key_type& k) const
                {
                    const_iterator it = this->begin();

                    for (; it != this->end(); it++)
                        if (_key_comp(it->first, k) == false && _key_comp(k, it->first) == false)
                            return (it);
                    return (this->end());
                }

                /*
                ** @brief Search in the container the number of
                ** element that contain "k" like key. Like all element in
                ** the container are unique he can return only 1 if it exist
                ** 0 otherwise.
                **
                ** @param k the key.
                ** @return the number of elements.
                */
                size_type count (const key_type& k) const
                { return ((this->find(k) != this->end()) ? 1 : 0); }

                /*
                ** @brief Return a iterator pointing to the first element
                ** in the container who have a key that is not
                ** concidered to go before "k". If an element have "k"
                ** like key, give an iterator to it.
                **
                ** @param k the key.
                ** @return the iterator.
                */
                iterator lower_bound (const key_type& k)
                {
                    const_iterator it = this->begin();

                    for(; it != this->end(); it++)
                        if (_key_comp(it->first, k) == false)
                            return (it);
                    return (this->end());
                }

                /*
                ** @brief Return a const iterator pointing to the first element
                ** in the container who have a key that is not
                ** concidered to go before "k". If an element have "k"
                ** like key, give an const iterator to it.
                **
                ** @param k the key.
                ** @return the iterator.
                */
                const_iterator lower_bound (const key_type& k) const
                {
                    const_iterator it = this->begin();

                    for(; it != this->end(); it++)
                        if (_key_comp(it->first, k) == false)
                            return (it);
                    return (this->end());
                }

                /*
                ** @brief return an iterator pointing to the next element
                ** whose key is concidered to go after "k".
                **
                ** @param k the key.
                ** @return the iterator.
                */
                iterator upper_bound (const key_type& k)
                {
                    const_iterator it = this->begin();

                    for (; it != this->end(); it++)
                        if (_key_comp(it->first, k) == false && it->first != k)
                            return (it);
                    return (this->end());
                }
                
                /*
                ** @brief return an const iterator pointing to the next element
                ** whose key is concidered to go after "k".
                **
                ** @param k the key.
                ** @return the const iterator.
                */
                const_iterator upper_bound (const key_type& k) const
                {
                    const_iterator it = this->begin();

                    for (; it != this->end(); it++)
                        if (_key_comp(it->first, k) == false && it->first != k)
                            return (it);
                    return (this->end());
                }

                /*
                ** @brief Return all the element that have "k" like key.
                ** Like all element in map are unique, that give a pair
                ** that contain two const iterator. The first iterator
                ** pointing to the lower bound of "k" and the second pointing
                ** to the upper bound of "k".
                **
                ** @param k the key.
                ** @return the pair containing the two const iterator.
                */
                ft::pair<const_iterator, const_iterator> equal_range (const key_type& k) const
                { return (ft::make_pair(this->lower_bound(k), this->upper_bound(k))); }

                /*
                ** @brief Return all the element that have "k" like key.
                ** Like all element in map are unique, that give a pair
                ** that contain two iterator. The first iterator
                ** pointing to the lower bound of "k" and the second pointing
                ** to the upper bound of "k".
                **
                ** @param k the key.
                ** @return the pair containing the two iterator.
                */
                ft::pair<iterator, iterator> equal_range (const key_type& k)
                { return (ft::make_pair(this->lower_bound(k), this->upper_bound(k))); }
                
            private:

                typedef ft::Binary_search_tree<value_type> bst;
                
                typedef typename bst::node_pointer node_pointer;

                key_compare _key_comp;
                allocator_type _alloc;
                bst _bst;
        };

}

// =============================================================================


#endif