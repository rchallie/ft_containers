/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchallie <rchallie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 11:01:04 by excalibur         #+#    #+#             */
/*   Updated: 2020/12/06 01:33:38 by rchallie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEQUE_HPP
# define DEQUE_HPP

# include "./utils/utils.hpp"
# include "./utils/deque_iterator.hpp"

namespace ft
{
    template <class T, class Alloc = std::allocator<T> > class deque
    {
        public:

            /*
            ** The first template parameter (T)
            */
            typedef T   value_type;

            /*
            ** The second template parameter (Alloc)
            */
            typedef Alloc   allocator_type;

            /*
            ** allocator_type::reference
            ** A type provides a reference to an element stored in
            ** a deque.
            ** For the default allocator is a reference to value_type
            ** (value_type&)
            */
            typedef typename allocator_type::reference     reference;

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
            ** A random access iterator to value_type
            ** That can read or modify any element stored.
            ** Convertible to const_iterator;
            */
            typedef ft::Deque_Iterator<value_type> iterator;

            /*
            ** A random access iterator to const value_type
            ** That can read element stored.
            */
            typedef ft::Deque_Iterator<const value_type> const_iterator;

            /*
            ** ft::reverse_iterator<iterator>
            ** That can read or modify any element in a reversed deque.
            ** Used to iterate through the deque in reverse.
            */
            typedef ft::reverse_iterator<iterator> reverse_iterator;

            /*
            ** ft::reverse_iterator<const_iterator>
            ** That can read any element in a reversed the deque.
            ** Can't be used to modify, used to iterate through the
            ** the deque in reverse.
            */
            typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

            /*
            ** A signed integral type:
            ** Usually the same as ptrdiff_t.
            ** Can represent the difference between iterators to the
            ** element actually stored.
            ** Can be described as te number of element between two pointers.
            ** (Pointer to an element contains its address).
            */
            typedef typename ft::iterator_traits<iterator>::difference_type difference_type;

            /*
            ** An unsigned integral type that can represent any
            ** non-negative value of difference_type
            ** Usually the same as size_t.
            */
            typedef size_t  size_type;

            // Constructors:

            /*
            ** @brief Default.
            ** Constructs an empty container, with no elements.
            ** 
            ** @param Allocator object.
            ** The container keeps and uses an internal copy of this
            ** allocator. It's an alias to the second template parameter.
            ** If in template this second argument is not defined,
            ** std::allocator will be used.
            */
            explicit deque (const allocator_type& alloc = allocator_type())
            :
                _alloc(alloc)
            { _deque_initialize_map(0); }

            /*
            ** @brief Fill.
            ** Constructs a container with "n" elements.
            ** Each element is a copy of val.
            **
            ** @param n The number of elements.
            ** @param val The element.
            ** @param allocator_type Allocator object.
            */
            explicit deque (size_type n, const value_type& val = value_type(),
                            const allocator_type& alloc = allocator_type())
            :
                _alloc(alloc)
            {
                _deque_initialize_map(n);
                while (n--)
                {
                    _alloc.construct(this->_data_end._elem, val);
                    this->_data_end++;
                }
            }
            
            /*
            ** @brief Range.
            ** Constructs a container with as many elements as the
            ** range [first,last), with each element constructed from
            ** its corresponding element in that range, in the same order.
            ** (Adapted to counter the effect of :
            ** deque(static_cast<size_type>(first), static_cast<value_type>(last), a))
            **
            ** @param first An iterator is the first value in x.
            ** @param last An iterator is the last value in x.
            */
            template <class InputIterator>
                deque (InputIterator first, InputIterator last,
                        const allocator_type& alloc = allocator_type(),
                        typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = u_nullptr)
            :
                _alloc(alloc)
            {
                bool is_valid;
                if (!(is_valid = ft::is_input_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category >::value))
                    throw (ft::InvalidIteratorException<typename ft::is_input_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category >::type>());
                
                difference_type n = ft::distance(first, last);
                _deque_initialize_map(n);
                while (n--)
                {
                    _alloc.construct(this->_data_end._elem, *first++);
                    this->_data_end++;
                }
            }
            
            /*
            ** @brief Copy.
            ** Construct a deque, initializing its contents
            ** with a copy of each element of "x" elements in 
            ** the same order. Use a copy of "x" allocator.
            **
            ** @param "x" the deque container to copy.
            */
            deque (const deque& x)
            :
                _alloc(x._alloc)
            {
                _deque_initialize_map(x._data_end._map - x._data_start._map);

                difference_type n = ft::distance(x._data_start, x._data_end);
                iterator first = x._data_start;
                while (n--)
                {
                    _alloc.construct(this->_data_end._elem, *first++);
                    this->_data_end++;
                }
            }

            /*
            ** @brief Destroy the container object.
            ** Destroy all elements in the container and deallocate
            ** the container capacity.
            */
            ~deque() {

                map_pointer map_start = this->_data_start._map;
                map_pointer map_end = this->_data_end._map;

                while (map_start != map_end + 1)
                    _alloc.deallocate(*(map_start++), _deque_block_size(sizeof(value_type)));
                
                _map_alloc.deallocate(this->_map_start, this->_map_end - this->_map_start);
            }
            
            /*
            ** @brief Assigns contents from "x" to the container.
            ** Replace content of this and according size.
            ** All elements before the call are destroyed.
            **
            ** @param x the container which we inspire.
            ** @return *this.
            */ 
            deque& operator= (const deque& x)
            {
                if (x == *this)
                    return (*this);
                this->clear();
                difference_type n = ft::distance(x._data_start, x._data_end);
                iterator first = x._data_start;
                while (n--)
                    this->push_back(*first++);
                return (*this);
            }

            // Iterators :
            
            /*
            ** @brief Return an iterator pointing
            ** to the first element in the container.
            ** The iterator is a random access iterator.
            ** It the container is empty, the returned value shall
            ** not be dereferenced.
            **
            ** @return the iterator.
            */
            iterator begin()
            { return (this->_data_start); }

            /*
            ** @brief Return an const iterator pointing
            ** to the first element in the container.
            ** The iterator is a random access iterator.
            ** It the container is empty, the returned value shall
            ** not be dereferenced.
            **
            ** @return the const iterator.
            */
            const_iterator begin() const
            { return (this->_data_start); }

            /*
            ** @brief Return an iterator pointing
            ** to the past-the-end theorical element that
            ** would follow the last element of the container.
            ** Because the iterator pointing to an non existing
            ** element, it's used in combinaison with the begin()
            ** to travel all the container. If the container is empty
            ** the return is the same than begin().
            **
            ** @return the iterator.
            */
            iterator end()
            {
                if (this->empty())
                    return (this->begin());
                return (this->_data_end);
            }

            /*
            ** @brief Return an const iterator pointing
            ** to the past-the-end theorical element that
            ** would follow the last element of the container.
            ** Because the iterator pointing to an non existing
            ** element, it's used in combinaison with the begin()
            ** to travel all the container. If the container is empty
            ** the return is the same than begin().
            **
            ** @return the const iterator.
            */
            const_iterator end() const
            {
                if (this->empty())
                    return (this->begin());
                return (this->_data_end);
            }

            /*
            ** @brief Return a reverse iterator pointing to
            ** the last element in the container.
            ** That pointing to the previous element that end().
            **
            ** @return the reverse iterator.
            */
            reverse_iterator rbegin()
            { return (reverse_iterator(this->_data_end)); }

            /*
            ** @brief Return a const reverse iterator pointing to
            ** the last element in the container.
            ** That pointing to the previous element that end().
            **
            ** @return the const reverse iterator.
            */
            const_reverse_iterator rbegin() const
            { return (const_reverse_iterator(this->_data_end)); }

            /*
            ** @brief Return a reverse iterator pointing to the
            ** theorical element preceding the first element
            ** in the container.
            **
            ** @return the reverse iterator.
            */
            reverse_iterator rend()
            { return (reverse_iterator(iterator(this->_data_start))); }

            /*
            ** @brief Return a const reverse iterator pointing to the
            ** theorical element preceding the first element
            ** in the container.
            **
            ** @return the const reverse iterator.
            */
            const_reverse_iterator rend() const
            { return (const_reverse_iterator(this->_data_start)); }

            // Capacity:

            /*
            ** @brief return the number of elements
            ** in the container.
            **
            ** @return the size.
            */
            size_type size() const
            { return (this->_data_end - this->_data_start); }

            /*
            ** @brief Return the maximum of elements
            ** that the deque container can hold.
            **
            ** @return the maximum number of elements.
            */
            size_type max_size() const
            { return (allocator_type().max_size()); }

            /*
            ** @brief Resizes the container so that it contain "n"
            ** element. If "n" is smaller than the actual size
            ** the container is reduced to "n". If it is greater,
            ** val is inserting at the end "n - size()" times.
            **
            ** @param n the new size of the container.
            ** @param val the element to set.
            */
            void resize(size_type n, value_type val = value_type())
            {
                if (this->max_size() - this->size() < n)
                    throw (std::length_error("deque::resize"));
                if (n > this->size())
                {
                    n -= this->size();
                    while (n--)
                        this->push_back(val); // Change to insert
                }
                else
                {
                    while (this->size() > n)
                        this->pop_back();
                }
            }

            /*
            ** @brief Return an boolean that is "true" if the
            ** container size is 0, otherwise "false".
            **
            ** @return the boolean.
            */
            bool empty() const
            { return ((this->size() == 0) ? true : false); }

            // Element access:

            /*
            ** @brief Give a reference to the element at "n"
            ** in the container.
            **
            ** @param n the position of the element.
            ** @return the reference.
            */
            reference operator[] (size_type n)
            { return (this->_data_start[n]); }

            /*
            ** @brief Give a const reference to the element at "n"
            ** in the container.
            **
            ** @param n the position of the element.
            ** @return the const reference.
            */
            const_reference operator[] (size_type n) const
            { return (this->_data_start[n]); }

            /*
            ** @brief Give a reference to the element at "n"
            ** in the container. If "n" is out of range (if it
            ** greater or equal than the size of the container)
            ** throwing an out_of_range exception.
            **
            ** @param n the position of the element.
            ** @return the reference.
            */
            reference at (size_type n)
            {
                checkRange(n);
                return (this->_data_start[n]);
            }

            /*
            ** @brief Give a const reference to the element at "n"
            ** in the container. If "n" is out of range (if it
            ** greater or equal than the size of the container)
            ** throwing an out_of_range exception.
            **
            ** @param n the position of the element.
            ** @return the const reference.
            */
            const_reference at (size_type n) const
            {
                checkRange(n);
                return (this->_data_start[n]);
            }

            /*
            ** @brief Give a reference to the first element
            ** in the container.
            **
            ** @return the reference.
            */
            reference front()
            { return (*this->_data_start); }

            /*
            ** @brief Give a const reference to the first element
            ** in the container.
            **
            ** @return the const reference.
            */
            const_reference front() const
            { return (*this->_data_start); }

            /*
            ** @brief Give a reference to the last element
            ** in the container.
            **
            ** @return the reference.
            */
            reference back()
            { return (*(this->_data_end - 1)); }

            /*
            ** @brief Give a const reference to the last element
            ** in the container.
            **
            ** @return the const reference.
            */
            const_reference back() const
            { return (*(this->_data_end - 1)); }

            // Modifiers:

            /*
            ** @brief Assign values between iterators [first; last]
            ** in the container in the same order. All element held
            ** in the container before the call of this function are
            ** destroyed and replaced by new content.
            **
            ** @param first,last the two iterators were the new
            ** element are.
            */
            template <class InputIterator>
                void assign(InputIterator first, InputIterator last,
                            typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = u_nullptr)
                {
                    bool is_valid;
                    if (!(is_valid = ft::is_input_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category>::value))
                        throw (ft::InvalidIteratorException<typename ft::is_input_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category>::type>());
                    
                    this->clear();
                    this->_data_end = this->_data_start;
                    while (first != last)
                        this->push_back(*first++); // Change to insert
                }

            /*
            ** @brief Assign new content ("val") to the container
            ** "n" times. All element held
            ** in the container before the call of this function are
            ** destroyed and replaced by new content.
            **
            ** @paran n the number of new elements.
            ** @param val the new element.
            */
            void assign (size_type n, const value_type& val)
            {
                this->clear();
                this->_data_end = this->_data_start;
                while (n--)
                    this->push_back(val); // Change to insert
            }

            /*
            ** @brief Add a new element at the end of the
            ** container.
            **
            ** @param val the value to copied in the container.
            */
            void push_back (const value_type& val)
            {
                _alloc.construct(this->_data_end._elem, val);
                if (this->_data_end._elem == this->_data_end._end_cur_block - 1
                    && ((this->_data_end._map + 1) - this->_data_start._map == this->_map_end - this->_map_start - 1))
                    _deque_realloc_map_back(1);
                this->_data_end++;
                if (*(this->_data_end._map) == 0)
                {
                    *(this->_data_end._map) = _deque_create_block();
                    this->_data_end._start_cur_block = *this->_data_end._map;
                    this->_data_end._end_cur_block = this->_data_end._start_cur_block + _deque_block_size(sizeof(value_type));
                    this->_data_end._elem = this->_data_end._start_cur_block;
                }
            }

            /*
            ** @brief Add a new element before the first element
            ** in the container.
            **
            ** @param val the value to copied in the container.
            */
            void push_front (const value_type& val)
            {
                if (this->_data_start._elem == this->_data_start._start_cur_block
                    && (this->_data_end._map - (this->_data_start._map - 1) == this->_map_end - this->_map_start))
                        _deque_realloc_map_front(1);
                this->_data_start--;
                if (*(this->_data_start._map) == 0)
                {
                    *(this->_data_start._map) = _deque_create_block();
                    this->_data_start._start_cur_block = *this->_data_start._map;
                    this->_data_start._end_cur_block = this->_data_start._start_cur_block + _deque_block_size(sizeof(value_type));
                    this->_data_start._elem = this->_data_start._end_cur_block - 1;
                }
                _alloc.construct(this->_data_start._elem, val);
            }

            /*
            ** @brief Remove the last element in the
            ** deque container. The removed element is
            ** destroyed.
            */
            void pop_back()
            {
                if (this->_data_end._elem != this->_data_end._start_cur_block)
                {
                    this->_data_end--;
                    _alloc.destroy(&(*this->_data_end));
                }
                else
                {
                    _alloc.deallocate(*(this->_data_end._map), _deque_block_size(sizeof(value_type)));
                    _map_alloc.destroy(this->_data_end._map);
                    _map_alloc.construct(this->_data_end._map, 0);
                    this->_data_end._map = this->_data_end._map - 1;
                    this->_data_end._start_cur_block = *this->_data_end._map;
                    this->_data_end._end_cur_block = this->_data_end._start_cur_block + _deque_block_size(sizeof(value_type));
                    this->_data_end._elem = this->_data_end._end_cur_block - 1;
                    _alloc.destroy(&(*this->_data_end));
                }
            }

            /*
            ** @brief Remove the first element in the
            ** deque container. The removed element is
            ** destroyed.
            */
            void pop_front()
            {
                if (this->_data_start._elem != this->_data_start._end_cur_block - 1)
                {
                    _alloc.destroy(&(*this->_data_start));
                    this->_data_start++;
                }
                else
                {
                    _alloc.destroy(&(*this->_data_start));
                    this->_data_start++;
                    _alloc.deallocate(*(this->_data_start._map - 1), _deque_block_size(sizeof(value_type)));
                    _map_alloc.destroy(this->_data_start._map - 1);
                    _map_alloc.construct(this->_data_start._map - 1, 0);
                }
            }

            /*
            ** @brief Insert an element a the position. Can ecrease de size
            ** of the container. This action force the container to
            ** realocate all the elements that were after "postion"
            ** to their new positions.
            **
            ** @param position The position where insert.
            ** @param val The element to insert.
            ** @return An iterator to the new element in the container.
            */
            iterator insert (iterator position, const value_type& val)
            {
                if (position == this->_data_start)
                {
                    this->push_front(val);
                    return (this->_data_start);
                }
                else if (position == this->_data_end)
                {
                    this->push_back(val);
                    return (this->_data_end);
                }
                else
                {
                    difference_type n = ft::distance(position, this->_data_end);
                    this->push_back(this->back());
                    for (size_type i = 0; i < (size_type)n + 1; i++)
                    {
                        this->_alloc.construct((this->_data_end - i)._elem, *(this->_data_end - 1 - i)._elem);
                        this->_alloc.destroy(&(*(this->_data_end - 1 - i)));
                    }
                    this->_alloc.construct((this->_data_end - n - 1)._elem, val);
                    return (this->_data_end - n - 1);
                }
            }

            /*
            ** @brief Insert an element a "n" amount of time
            ** before the specified position. Can ecrease de capacity
            ** of the container. This action force the container to
            ** realocate all the elements that were after "position"
            ** to their new positions.
            **
            ** @param position The position where insert.
            ** @param n Amout of element to insert.
            ** @param val The element to insert.
            */
            void insert (iterator position, size_type n, const value_type& val)
            {
                if (position == this->_data_start)
                {
                    while (n--)
                        push_front(n);
                }
                else if (position == this->_data_end)
                {
                    while (n--)
                        push_back(n);
                }
                else
                {
                    map_pointer         save_map_start = this->_data_start._map;
                    map_pointer         save_map_end = this->_data_end._map;
                    map_pointer         save_map_ext_start = this->_map_start;
                    map_pointer         save_map_ext_end = this->_map_end;
                    iterator            save_data_start = this->_data_start;
                    iterator            save_data_end = this->_data_end;

                    size_type     save_diff_from_start = ft::distance(this->_data_start, position);
                    size_type     save_size_end = this->size();

                    _deque_initialize_map((save_data_end - save_data_start) + n);

                    size_type count = 0;
                    for (; count < save_diff_from_start; count++)
                        _alloc.construct((this->_data_end++)._elem, *(save_data_start + count)._elem);
                    while (n--)
                        _alloc.construct((this->_data_end++)._elem, val);
                    for(; count < save_size_end; count++)
                        _alloc.construct((this->_data_end++)._elem,
                            *(save_data_start + count)._elem);

                    while (save_map_start != save_map_end + 1)
                        _alloc.deallocate(*(save_map_start++), _deque_block_size(sizeof(value_type)));
                    _map_alloc.deallocate(save_map_ext_start, save_map_ext_end - save_map_ext_start);
                }
            }

            /*
            ** @brief Insert element in range from ["first" to
            ** "last") at "position". Can increase the size of
            ** the container. Throw if the iterator given is not valid.
            ** Reallocate all elements after the dist between first and last.
            **
            ** @param position the position where insert.
            ** @param first the first element in the range.
            ** @param last the last element in the range.
            */
            template <class InputIterator>
                void insert (iterator position, InputIterator first, InputIterator last,
                typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = u_nullptr)
            {
                bool is_valid;
                if (!(is_valid = ft::is_input_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category >::value))
                    throw (ft::InvalidIteratorException<typename ft::is_input_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category >::type>());
                
                difference_type n = ft::distance(first, last);
                if (position == this->_data_start)
                {
                    while (n--)
                        push_front(*(--last));
                }
                else if (position == this->_data_end)
                {
                    while (n--)
                        push_back(*(first++));
                }
                else
                {
                    map_pointer         save_map_start = this->_data_start._map;
                    map_pointer         save_map_end = this->_data_end._map;
                    map_pointer         save_map_ext_start = this->_map_start;
                    map_pointer         save_map_ext_end = this->_map_end;
                    iterator            save_data_start = this->_data_start;
                    iterator            save_data_end = this->_data_end;

                    size_type     save_diff_from_start = ft::distance(this->_data_start, position);
                    size_type     save_size_end = this->size();

                    _deque_initialize_map((save_data_end - save_data_start) + n);

                    size_type count = 0;
                    for (; count < save_diff_from_start; count++)
                        _alloc.construct((this->_data_end++)._elem, *(save_data_start + count)._elem);
                    while (n--)
                        _alloc.construct((this->_data_end++)._elem, *first++);
                    for(; count < save_size_end; count++)
                        _alloc.construct((this->_data_end++)._elem,
                            *(save_data_start + count)._elem);

                    while (save_map_start != save_map_end + 1)
                        _alloc.deallocate(*(save_map_start++), _deque_block_size(sizeof(value_type)));
                    _map_alloc.deallocate(save_map_ext_start, save_map_ext_end - save_map_ext_start);
                }
            }

            /*
            ** @brief Remove element from the container at "position".
            ** Reduce the size of 1;
            **
            ** @param position the iterator pointing to the
            ** element to remove.
            ** @return a pointer to the element a "&(*position) + 1"; 
            */
            iterator erase (iterator position)
            {
                if (position == this->_data_start)
                {
                    pop_front();
                    return (this->_data_start);
                }
                else if (position == this->_data_end)
                {
                    pop_back();
                    return (this->_data_end - 1);
                }
                else
                {
                    map_pointer         save_map_start = this->_data_start._map;
                    map_pointer         save_map_end = this->_data_end._map;
                    map_pointer         save_map_ext_start = this->_map_start;
                    map_pointer         save_map_ext_end = this->_map_end;
                    iterator            save_data_start = this->_data_start;
                    iterator            save_data_end = this->_data_end;

                    difference_type dist = ft::distance(this->_data_start, this->_data_end);
                    difference_type diff_start_pos = ft::distance(this->_data_start, position);
                    _deque_initialize_map((save_data_end - save_data_start) - 1);

                    iterator rtn;
                    size_type count = 0;
                    while (dist--)
                    {
                        if (dist != diff_start_pos)
                        {
                            if (save_data_start == position)
                                rtn = this->_data_end;
                            _alloc.construct((this->_data_end++)._elem, *(save_data_start + count)._elem);
                        }
                        count++;
                    }

                    while (save_map_start != save_map_end + 1)
                        _alloc.deallocate(*(save_map_start++), _deque_block_size(sizeof(value_type)));
                    _map_alloc.deallocate(save_map_ext_start, save_map_ext_end - save_map_ext_start);
                    return (rtn);
                }
            }

            /*
            ** @brief Remove a range of element.
            ** Reduce the size by the number of element removed.
            ** 
            ** @param first the first element in the range.
            ** @param last the last element in the range.
            ** @return An iterator that point to the first element
            ** after "last".
            */
            iterator erase (iterator first, iterator last)
            {
                difference_type n = ft::distance(first, last);

                if (this->rangeHas(this->_data_end - 1, first, last) == true)
                {
                    while (n--)
                        pop_back();
                    return (this->_data_end - 1);
                }
                else if (this->rangeHas(this->_data_start, first, last) == true)
                {
                    while (n--)
                        pop_front();
                    return (this->_data_start);
                }
                else
                {
                    map_pointer         save_map_start = this->_data_start._map;
                    map_pointer         save_map_end = this->_data_end._map;
                    map_pointer         save_map_ext_start = this->_map_start;
                    map_pointer         save_map_ext_end = this->_map_end;
                    iterator            save_data_start = this->_data_start;
                    iterator            save_data_end = this->_data_end;

                    difference_type dist = ft::distance(this->_data_start, this->_data_end);
                    difference_type diff_start_pos = ft::distance(this->_data_start, last);
                    difference_type diff_end_pos = dist - ft::distance(last, this->_data_end);
                    _deque_initialize_map((save_data_end - save_data_start) - n);

                    iterator rtn;
                    size_type count = 0;
                    while (dist--)
                    {
                        if (dist < diff_start_pos - 1 || dist > diff_end_pos)
                        {
                            if (save_data_start == last + 1)
                                rtn = this->_data_end;
                            _alloc.construct((this->_data_end++)._elem, *(save_data_start + count)._elem);
                        }
                        count++;
                    }

                    while (save_map_start != save_map_end + 1)
                        _alloc.deallocate(*(save_map_start++), _deque_block_size(sizeof(value_type)));
                    _map_alloc.deallocate(save_map_ext_start, save_map_ext_end - save_map_ext_start);
                    return (rtn);
                }
                return (iterator());
            }

            /*
            ** @brief Exchanges the content with "x" content.
            ** "x" is of same type. Elements of "x" are elements
            ** of this container and elements of this are of "x".
            ** All iterators, references, pointer on the swaped
            ** objects stay valid.
            **
            ** @param x the deque to swap.
            */
            void swap (deque& x)
            {
                if (x == *this)
                    return;
                
                map_allocator_type  save_map_alloc = x._map_alloc;
                map_pointer         save_map_start = x._map_start;
                map_pointer         save_map_end = x._map_end;
                allocator_type      save_alloc = x._alloc;
                iterator            save_data_start = x._data_start;
                iterator            save_data_end = x._data_end;

                x._map_alloc = this->_map_alloc;
                x._map_start = this->_map_start;
                x._map_end = this->_map_end;
                x._alloc = this->_alloc;
                x._data_start = this->_data_start;
                x._data_end = this->_data_end;

                this->_map_alloc = save_map_alloc;
                this->_map_start = save_map_start;
                this->_map_end = save_map_end;
                this->_alloc = save_alloc;
                this->_data_start = save_data_start;
                this->_data_end = save_data_end;
            }

            /*
            ** @brief Removes (destroy) all elements from the
            ** container. Final size is 0.
            */
            void clear()
            {
                while (this->_data_end != this->_data_start)
                    this->pop_back();
            }

        private:

            typedef typename allocator_type::template
                rebind<pointer>::other map_allocator_type;
            typedef typename map_allocator_type::pointer map_pointer;

            map_allocator_type  _map_alloc;
            map_pointer         _map_start;
            map_pointer         _map_end;
            
            allocator_type      _alloc;
            iterator            _data_start;
            iterator            _data_end;

            /*
            ** @brief Check if "n" is in the range of the container.
            ** If "n" is out of range that's throw an std::out_of_range
            ** exception.
            **
            ** @param n The position of the element to check.
            */
            void checkRange(const size_type& n) const
            {
                if (n >= this->size())
                    throw (std::out_of_range("deque::checkRange: n (which is "
                            + ft::to_string(n) + ")>= this->size() (which is "
                            + ft::to_string(this->size()) + ")"));
            }

            bool rangeHas(iterator pos, iterator first, iterator last)
            {
                while (first != last)
                {
                    if (first == pos)
                        return (true);
                    ++first;
                }
                return (false);
            }
            
            /*
            ** @brief Return the size of the block memory.
            ** The buffer of 512 is conciderate tunable for
            ** binary compatibility and other library.
            ** Source :
            ** https://stackoverflow.com/questions/4097729/stddeque-memory-usage-visual-c-and-comparison-to-others
            **
            ** @param size the size of object that will be contained
            ** by the block.
            ** @return if the size is inferrior than the buffer
            ** we will have block of size 512 / sizeof(T), otherwise
            ** the block will have the size of the "T".
            */
            size_type _deque_block_size(size_type size)
            { return ((size < 512) ? size_type(512 / sizeof(value_type)) : size_type(1)); }

            /*
            ** size = number of element will be based on the container
            */
            map_pointer _deque_initialize_map(size_type size)
            {
                this->_map_alloc = map_allocator_type();

                size_type block_number = (size / _deque_block_size(sizeof(T))) + 1;
                size_type map_size = block_number + 2;
                this->_map_start = this->_map_alloc.allocate(map_size);
                this->_map_end = this->_map_start + map_size;

                _map_alloc.construct(this->_map_start, 0);
                _map_alloc.construct(this->_map_end - 1, 0);

                for (int i = 0; i < (this->_map_end - 1) - (this->_map_start + 1); i++)
                    _map_alloc.construct(this->_map_start + i + 1, _deque_create_block());

                this->_data_start = iterator(*(this->_map_start + 1), this->_map_start + 1);
                this->_data_end = this->_data_start;
                
                return (this->_map_start);
            }

            pointer _deque_create_block(void)
            { return (_alloc.allocate( _deque_block_size(sizeof(value_type)) )); }

            /*
            ** @param n number of block to add.
            */
            map_pointer _deque_realloc_map_back(size_type n)
            {
                size_type previous_map_size = (this->_map_end - this->_map_start);
                size_type next_map_size = previous_map_size + n;
                map_pointer new_map_start = this->_map_alloc.allocate(next_map_size);
                map_pointer new_map_end = new_map_start + next_map_size;

                for (size_type i = 0; i < previous_map_size; i++)
                {
                    _map_alloc.construct(new_map_start + i, *(this->_map_start + i));
                    _map_alloc.destroy(this->_map_start + i);
                }
                _map_alloc.construct(new_map_end - 1, 0);

                _map_alloc.deallocate(this->_map_start, this->_map_end - this->_map_start);

                this->_map_start = new_map_start;
                this->_map_end = new_map_end;

                this->_data_start._map = this->_map_start + 1;
                this->_data_end._map = this->_map_start + previous_map_size - 1;
                return (this->_map_start);
            }
            
            /*
            ** @param n number of block to add.
            */
            map_pointer _deque_realloc_map_front(size_type n)
            {
                size_type previous_map_size = (this->_map_end - this->_map_start);
                size_type next_map_size = previous_map_size + n;
                map_pointer new_map_start = this->_map_alloc.allocate(next_map_size + 1);
                map_pointer new_map_end = new_map_start + next_map_size;

                _map_alloc.construct(new_map_start, 0);

                for (int i = 0; i < this->_map_end - this->_map_start; i++)
                {
                    _map_alloc.construct(new_map_start + i + 1, *(this->_map_start + i));
                    _map_alloc.destroy(this->_map_start + i);
                }

                _map_alloc.deallocate(this->_map_start, this->_map_end - this->_map_start);

                this->_map_start = new_map_start;
                this->_map_end = new_map_end;
                
                this->_data_start._map = this->_map_start + 1;
                this->_data_end._map = this->_map_start + previous_map_size;

                return (this->_map_start);
            }
    };

    // Non-member function overloads
    
    /*
    ** @brief Compare deque container to know
    ** if they are equal. Start to check if the size
    ** is different.
    **
    ** @param lhs deque to compare with "rhs".
    ** @param rhs deque for comparison of "lhs".
    ** @return true if they are equal, false otherwise.
    */
    template <class T, class Alloc>
        bool operator== (const ft::deque<T, Alloc>& lhs, const ft::deque<T, Alloc>& rhs)
        {
            if (lhs.size() != rhs.size())
                return (false);
            typename ft::deque<T>::const_iterator first1 = lhs.begin();
            typename ft::deque<T>::const_iterator first2 = rhs.begin();
            while (first1 != lhs.end())
            {
                if (first2 == rhs.end() || *first1 != *first2)
                    return (false);
                ++first1;
                ++first2;
            }
            return (true);
        }

    /*
    ** @brief Compare deque container to know
    ** if they are different. Equivalent to !(lsh == rhs).
    **
    ** @param lhs deque to compare with "rhs".
    ** @param rhs deque for comparison of "lhs".
    ** @return true if they are different, false otherwise.
    */
    template <class T, class Alloc>
        bool operator!= (const deque<T, Alloc>& lhs, const deque<T, Alloc>& rhs)
        {
            return (!(lhs == rhs));
        }
    
    /*
    ** @brief Compare deque container to know
    ** if "lhs" elements are lexicographicalement less than "rhs".
    **
    ** @param lhs deque to compare with "rhs".
    ** @param rhs deque for comparison of "lhs".
    ** @return true if "lhs" is lexicographicalement less, false otherwise.
    */
    template <class T, class Alloc>
        bool operator<  (const deque<T, Alloc>& lhs, const deque<T, Alloc>& rhs)
        {
            return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
        }

    /*
    ** @brief Compare deque container to know
    ** if "lhs" elements are lexicographicalement less or equal than "rhs".
    **
    ** @param lhs deque to compare with "rhs".
    ** @param rhs deque for comparison of "lhs".
    ** @return true if "lhs" is lexicographicalement less or equal, false otherwise.
    */
    template <class T, class Alloc>
        bool operator<= (const deque<T, Alloc>& lhs, const deque<T, Alloc>& rhs)
        {
            return (!(rhs < lhs));
        }

    /*
    ** @brief Compare deque container to know
    ** if "lhs" elements are lexicographicalement superior than "rhs".
    **
    ** @param lhs deque to compare with "rhs".
    ** @param rhs deque for comparison of "lhs".
    ** @return true if "lhs" is lexicographicalement superior, false otherwise.
    */
    template <class T, class Alloc>
        bool operator>  (const deque<T, Alloc>& lhs, const deque<T, Alloc>& rhs)
        {
            return (rhs < lhs);
        }

    /*
    ** @brief Compare deque container to know
    ** if "lhs" elements are lexicographicalement superior or equal than "rhs".
    **
    ** @param lhs deque to compare with "rhs".
    ** @param rhs deque for comparison of "lhs".
    ** @return true if "lhs" is lexicographicalement superior or equal, false otherwise.
    */
    template <class T, class Alloc>
        bool operator>= (const deque<T, Alloc>& lhs, const deque<T, Alloc>& rhs)
        {
            return (!(lhs < rhs));
        }
    
    /*
    ** @brief Overload of swap (deque).
    ** The contents of container are swaped.
    **
    ** @param x, y the containers to swap.
    */
    template <class T, class Alloc>
        void swap (deque<T,Alloc>& x, deque<T,Alloc>&y)
        {
            x.swap(y);
        }
}

#endif