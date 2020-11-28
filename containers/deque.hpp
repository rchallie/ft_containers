/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchallie <rchallie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 11:01:04 by excalibur         #+#    #+#             */
/*   Updated: 2020/11/27 17:47:08 by rchallie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEQUE_HPP
# define DEQUE_HPP

# include "./utils/utils.hpp"

namespace ft
{
    template <class T, class Alloc = std::allocator<T> > class deque
    {
        public:

            typedef T   value_type;

            typedef Alloc   allocator_type;

            typedef typename allocator_type::reference     reference;

            typedef typename allocator_type::const_reference const_reference;

            typedef typename allocator_type::pointer     pointer;

            typedef typename allocator_type::const_pointer const_pointer;

            typedef ft::Deque_Iterator<T, T*, reference> iterator;

            typedef ft::Deque_Iterator<value_type, const_pointer, const_reference> const_iterator;

            typedef ft::reverse_iterator<iterator> reverse_iterator;

            typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

            typedef typename ft::iterator_traits<iterator>::difference_type difference_type;

            typedef size_t  size_type;
    
            explicit deque (const allocator_type& alloc = allocator_type())
            :
                _alloc(alloc)
            { _deque_initialize_map(0); }

            explicit deque (size_type n, const value_type& val = value_type(),
                            const allocator_type& alloc = allocator_type());
            
            // template <class InputIterator>
            //     deque (InputIterator first, InputIterator last,
            //             const allocator_type& alloc = allocator_type());

            deque (const deque& x);

            ~deque() {

                map_pointer map_start = this->_data_start._map;
                map_pointer map_end = this->_data_end._map;

                while (map_start != map_end + 1)
                    _alloc.deallocate(*(map_start++), _deque_block_size(sizeof(value_type)));
                
                _map_alloc.deallocate(this->_map_start, this->_map_end - this->_map_start);
            }

            deque& operator= (const deque& x);

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
            { return (U_SIZE_MAX / sizeof(T)); }

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
                        this->pop_back(); // Change to erase
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

            // iterator insert (iterator position, const value_type& val);

            // void insert (iterator position, size_type n, const value_type& val);

            // template <class InputIterator>
            //     void insert (iterator position, InputIterator first, InputIterator last);

            // iterator erase (iterator position);

            // iterator erase (iterator first, iterator last);

            void swap (deque& x);

            void clear()
            {
                while (this->_data_end != this->_data_start)
                    this->pop_back();
            }

        private:

            typedef typename allocator_type::template rebind<pointer>::other map_allocator_type;
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

                std::cout << "========================\n";
                    
                this->_data_start._map = this->_map_start + 1;
                this->_data_end._map = this->_map_start + previous_map_size - 1;
                return (this->_map_start);
            }
            
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
}

#endif