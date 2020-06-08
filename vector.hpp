/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: excalibur <excalibur@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/18 12:45:54 by excalibur         #+#    #+#             */
/*   Updated: 2020/06/08 21:27:53 by excalibur        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Documentation :
** (fr) https://github.com/rchallie/ft_containers/blob/master/vector.txt
** http://www.cplusplus.com/reference/vector/vector/?kw=vector
** (fr) https://docs.microsoft.com/fr-fr/cpp/standard-library/vector-class?view=vs-2019
*/

#ifndef VECTOR_HPP
# define VECTOR_HPP

// LIBS ========================================================================
# include <memory>
# include <algorithm>
# include <cstddef>
# include <tgmath.h>
# include "Utils.hpp"
// =============================================================================

// CLASS DEFINITIONS ===========================================================
namespace ft
{
    template < class T, class Alloc = std::allocator<T> >
    class vector
    {   
        public:

            /*
            ** The first template parameter (T)
            */
            typedef T                                           value_type;

            /*
            ** The second template parameter (Alloc)
            */
            typedef Alloc                                       allocator_type;

            /*
            ** allocator_type::reference
            ** A type provides a reference to an element stored in
            ** a vector.
            ** For the default allocator is a reference to value_type
            ** (value_type&)
            */
            typedef typename allocator_type::reference          reference;

            /*
            ** allocator_type::const_reference
            ** Type that give a reference to a const element stored.
            ** Usefull to read and perform const operator.
            ** A type const_reference can't be used to modify the value
            ** of an element.
            ** For the default allocator is a const reference to value_type
            ** (const value_type&)
            */
            typedef typename allocator_type::const_reference    const_reference;
            
            /*
            ** allocator_type::pointer
            ** Type that give a pointer to an element stored.
            ** A type pointer can be used to modify the value of
            ** an element.
            ** For the default allocator is a pointer to value_type
            ** (value_type*)
            */
            typedef typename allocator_type::pointer            pointer;

            /*
            ** allocator_type::const_pointer
            ** Type that give a const pointer to an element stored.
            ** Can't be used to modify the value of an element.
            ** An iterator is prefered to access to an element.
            ** For the default allocator is a const pointer to value_type
            ** (const value_type*)
            */
            typedef typename allocator_type::const_pointer      const_pointer;

            /*
            ** A random access iterator to value_type
            ** That can read or modify any element stored.
            ** Convertible to const_iterator;
            */
            /** ________________________ WIP ________________________
             * (Need to be replace by own reverse iterator)
            */
            typedef ft::random_access_iterator<value_type>               iterator;

            /*
            ** A random access iterator to const value_type
            ** That can read element stored.
            */
            /** ________________________ WIP ________________________
             * (Need to be replace by own reverse iterator)
            */
            typedef ft::random_access_iterator<const value_type>            const_iterator;
            
            /*
            ** ft::reverse_iterator<iterator>
            ** That can read or modify any element in a reversed vector.
            ** Used to iterate through the vector in reverse.
            */
            /** ________________________ WIP ________________________
             * (Need to be replace by own reverse iterator)
            */
            typedef ft::reverse_iterator<iterator>             reverse_iterator;

            /*
            ** ft::reverse_iterator<const_iterator>
            ** That can read any element in a reversed the vector.
            ** Can't be used to modify, used to iterate through the
            ** the vector in reverse.
            */
            /** ________________________ WIP ________________________
             * (Need to be replace by own reverse iterator)
            */
            typedef ft::reverse_iterator<const_iterator>       const_reverse_iterator;

            /*
            ** A signed integral type:
            ** Usually the same as ptrdiff_t.
            ** Can represent the difference between iterators to the
            ** element actually stored.
            ** Can be described as te number of element between two pointers.
            ** (Pointer to an element contains its address).
            */
            typedef typename ft::random_access_iterator<T>::difference_type    difference_type; 

            /*
            ** An unsigned integral type that can represent any
            ** non-negative value of difference_type
            ** Usually the same as size_t.
            ** Is the number of elements in a vector.
            */
            typedef typename allocator_type::size_type          size_type;
            
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
            explicit vector (const allocator_type& alloc = allocator_type())
            :
                _alloc(alloc),
                _start(u_nullptr),
                _end(u_nullptr),
                _end_capacity(u_nullptr)
            {}

            /*
            ** @brief Fill.
            ** Constructs a container with "n" elements.
            ** Each element is a copy of val.
            **
            ** @param n The number of elements.
            ** @param val The element.
            ** @param allocator_type Allocator object.
            */
            explicit vector (size_type n, const value_type& val = value_type(),
                 const allocator_type& alloc = allocator_type())
            :
                _alloc(alloc),
                _start(u_nullptr),
                _end(u_nullptr),
                _end_capacity(u_nullptr)
            {
                _start = _alloc.allocate( n );
                _end_capacity = _start + n;
                _end = _start;
                while (n--)
                {
                    _alloc.construct(_end, val);
                    _end++;
                }
            }

            /*
            ** @brief Range.
            ** Constructs a container with as many elements as the
            ** range [first,last), with each element constructed from
            ** its corresponding element in that range, in the same order.
            ** (Adapted to counter the effect of :
            ** vector(static_cast<size_type>(first), static_cast<value_type>(last), a))
            **
            ** @param first An iterator is the first value in x.
            ** @param last An iterator is the last value in x.
            */
            template <class InputIterator>
                    vector (InputIterator first, InputIterator last,
                            const allocator_type& alloc = allocator_type(),
                            typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = u_nullptr)
            :
                _alloc(alloc)
            {
                bool is_valid;
                if (!(is_valid = ft::is_input_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category >::value))
                    throw (ft::InvalidIteratorException<typename ft::is_input_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category >::type>());
                difference_type n = ft::distance(first, last);
                _start = _alloc.allocate( n );
                _end_capacity = _start + n;
                _end = _start;
                while (n--)
                {
                    _alloc.construct(_end, *first);
                    _end++;
                }
            }
            
            /*
            ** Copy
            */
            /** ________________________ WIP ________________________
             * Need const iterator
            */
            vector (const vector& x);
            // :
            //     _alloc(x._alloc),
            //     _start(u_nullptr),
            //     _end(u_nullptr),
            //     _end_capacity(u_nullptr)
            // {
            //     // _start = _alloc.allocate( x.capacity() );
            //     // _end_capacity = _start + x.capacity();
            //     // _end = _start;
            //     iterator x_it;
            //     for (x_it = x.begin(); x_it >= x.begin(); x_it--)
            //         this->push_back(*x_it);
            // }
            
            /** ________________________ WIP ________________________*/
            virtual ~vector() { _alloc.deallocate(_start, _end_capacity - _start); };
            
            /** ________________________ WIP ________________________*/
            vector &operator=(const vector& op);

            // Iterators:

            /*
            ** @brief Return an iterator pointing on the first element
            ** in the container. If the container is empty, the
            ** returned iterator value shall no be dereferenced.
            ** The iterator is of type iterator (random access iterator
            ** on value_type reference).
            **
            ** @return The iterator to the first element.
            */
            iterator begin() { return (_start); };

            /*
            ** @brief Return an iterator pointing on the first element
            ** in the container. If the container is empty, the
            ** returned iterator value shall no be dereferenced.
            ** The iterator is of type const_iterator (random access
            ** iterator on const value_type reference).
            **
            ** @return The iterator to the first element.
            */
            const_iterator begin() const { return (_start); }

            /*
            ** @brief Return an iterator pointing on the past-the-end element
            ** in the vector container. Past-the-end is the theorical element
            ** following the last element in the container. If the container is
            ** empty, return the same than begin.
            ** The iterator is of type iterator (random access iterator
            ** on value_type reference).
            **
            ** @return The iterator to the past-the-end element or begin if
            ** the container is empty.
            */
            iterator end()
            {
                if (this->empty())
                    return (this->begin());
                return (_end);
            }

            /*
            ** @brief Return an iterator pointing on the past-the-end element
            ** in the vector container. Past-the-end is the theorical element
            ** following the last element in the container. If the container is
            ** empty, return the same than begin.
            ** The iterator is of type const_iterator (random access
            ** iterator on const value_type reference).
            **
            ** @return The iterator to the past-the-end element or begin if
            ** the container is empty.
            */
            const_iterator end() const
            {
                if (this->empty())
                    return (this->begin());
                return (_end);
            };

            /*
            ** @brief Give a reverse iterator pointing to the last element
            ** in the container (this->end() - 1).
            ** This is a reversed random access iterator.
            **
            ** @return A reverse Iterator to the reverse beginning of the.
            */
            reverse_iterator rbegin() { return (reverse_iterator(this->end())); }

            /*
            ** @brief Give a const reverse iterator pointing to the last 
            ** element in the container (this->end() - 1).
            ** This is a constant reversed random access iterator.
            **
            ** @return A const reverse Iterator to the reverse beginning of the.
            */
            const_reverse_iterator rbegin() const { return (reverse_iterator(this->end())); }

            /** ________________________ WIP ________________________*/
            reverse_iterator rend();

            /** ________________________ WIP ________________________*/
            const_reverse_iterator rend() const;

            // Capacity:
            
            /*
            ** @brief Returns the number of elements stored.
            ** It's not necessarily equal to the storage capacity
            **
            ** @return The number of elements in the container.
            ** (An unsigned integral type)
            */
            size_type   size(void) const { return (this->_end - this->_start); }

            /*
            ** @brief Returns the maximum potential number of elements the the
            ** vector can hold.
            ** This size is due to known system or library limitations.
            ** The vector is not garanteed to have this size, it can
            ** fail a allocation for exemple.
            ** 
            ** Documentation :
            ** https://www.viva64.com/en/a/0050/
            **
            ** @return The maximum potential number of elements the
            ** container can hold.
            ** (An unsigned integral type)
            */
            size_type   max_size(void) const { return (U_SIZE_MAX / sizeof(T)); }

            /** ________________________ WIP ________________________*/
            void        resize (size_type n, value_type val = value_type());

            /*
            ** @brief Return size of allocated storage capacity.
            ** Not necessarily equal to vector size. Can be equal
            ** or greater, because extra space allocated by the container
            ** forecast allocation system.
            **
            ** @return The size of currntly allocated storage capacity.
            ** The number elements it can hold.
            ** (An unsigned integral type)
            */
            size_type   capacity (void) const { return (this->_end_capacity - this->_start); }

            /*
            ** @brief Returns whether the container is empty.
            ** Does not modify container in any way.
            **
            ** @return true if the container size is 0, false otherwise.
            */
            bool        empty (void) const { return (size() == 0 ? true : false); }

            /** ________________________ WIP ________________________*/
            void        reserve (size_type n);

            // Element access:

            /*
            ** @brief Returns a reference to the element at
            ** position n in the vector container.
            ** If "n" is out of range that's causes undefined behavior.
            **
            ** @param n Position of the element in the container.
            ** @return The specified element at "n" position.
            */
            reference operator[] (size_type n) { return (*(_start + n)); }

            /*
            ** @brief Returns a const reference to the element at
            ** position n in the vector container.
            ** If "n" is out of range that's causes undefined behavior.
            **
            ** @param n Position of the element in the container.
            ** @return The specified element at "n" position.
            */
            const_reference operator[] (size_type n) const { return (*(_start + n)); }
            
            /*
            ** @brief Returns a reference to the element at
            ** position n in the vector container.
            ** The main difference between this function and the
            ** operator "[]" is that the function throw an
            ** std::out_of_range exception if "n" is out of the range of
            ** the container.
            **
            ** @param n Position of the element in the container.
            ** @return The specified element at "n" position.
            */
            reference at (size_type n)
            {
                checkRange(n);
                return ((*this)[n]);
            }

            /*
            ** @brief Returns a const reference to the element at
            ** position n in the vector container.
            ** The main difference between this function and the
            ** operator "[]" is that the function throw an
            ** std::out_of_range exception if "n" is out of the range of
            ** the container.
            **
            ** @param n Position of the element in the container.
            ** @return The specified element at "n" position.
            */
            const_reference at (size_type n) const
            {
                checkRange(n);
                return ((*this)[n]);
            }

            /*
            ** @brief Return a reference to the first element
            ** of the container. Call this on an empty container
            ** cause undefined behavior.
            **
            ** @return The reference.
            */
            reference front () { return (*_start); }

            /*
            ** @brief Return a const reference to the first element
            ** of the container. Call this on an empty container
            ** cause undefined behavior.
            **
            ** @return The const reference.
            */
            const_reference front () const { return (*_start); }
            
            /*
            ** @brief Return a reference to the last element in the container.
            ** If the container is empty, occur undefined behavior.
            **
            ** @return The reference to the last element.
            */
            reference back () { return (*(_end - 1)); }

            /*
            ** @brief Return a const reference to the last element in the container.
            ** If the container is empty, occur undefined behavior.
            **
            ** @return The const reference to the last element.
            */
            const_reference back () const { return (*(_end - 1)); }

            // Modifiers:

            /*
            ** Range (1)
            ** @brief Assigns new contents to the vector, replacing its current
            ** contents, add modifying its size accordingly.
            ** New elements are contruct from each of the elements in tht
            ** range, between first and last, in the same order.
            **
            ** @param
            */
            /** ________________________ WIP ________________________*/
            template <class InputIterator>
                void assign (InputIterator first, InputIterator last);
            
            /*
            ** Fill
            */
            /** ________________________ WIP ________________________*/
            void assign (size_type n, const value_type& val);

            /*
            ** @brief Add new element at the end of the vector.
            ** The content of "val" is copied (moved) to the new element.
            ** 
            ** @param val The value to be copied.
            */
            void push_back (const value_type& val)
            {                
                if (_end == _end_capacity)
                    this->extend();
                _alloc.construct(_end, val);
                _end++;
            }

            /** ________________________ WIP ________________________*/
            void pop_back()
            {
                _alloc.destroy(&this->back());
                if (this->size() > 0)
                    _end--;
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
            /** ________________________ WIP ________________________*/
            iterator insert (iterator position, const value_type& val)
            {
                int pos_advance = &(*position) - _start;
                if (_end == _end_capacity)
                {
                    this->extend();
                    position = _start + pos_advance;
                }
                int end_len = _end - &(*position);
                while (end_len--)
                {
                    *(_end + end_len) = *(position + end_len);
                }
                _end++;
                *position = val;
                return (position);
            }

            /*
            ** @brief Insert an element a "n" amount of time
            ** before the specified position. Can ecrease de size
            ** of the container. This action force the container to
            ** realocate all the elements that were after "postion"
            ** to their new positions.
            **
            ** @param position The position where insert.
            ** @param n Amout of element to insert.
            ** @param val The element to insert.
            */
            /** ________________________ WIP ________________________*/
            void insert (iterator position, size_type n, const value_type& val)
            {
                if ((int)n < 0)
                    throw (std::length_error("ft::insert (fill)"));
                while (n--)
                {
                    position = this->insert(position, val);
                    position++;
                }
            }

            /*
            ** Range:
            */
            // /** ________________________ WIP ________________________*/
            // template <class InputIterator>
            //     void insert (iterator position, InputIterator first, InputIterator last);

            /** ________________________ WIP ________________________*/
            iterator erase (iterator position);

            /** ________________________ WIP ________________________*/
            iterator erase (iterator first, iterator last);

            /** ________________________ WIP ________________________*/
            void swap (vector& x);

            /** ________________________ WIP ________________________*/
            void clear();

        private:
            allocator_type  _alloc;
            pointer         _start;
            pointer         _end;
            pointer         _end_capacity;

            /*
            ** @brief Extend the actual capacity of the container
            ** logarithmically of one with a base of two. 
            ** Move (copy) values from the container inside and
            ** deallocate previous allocation.
            */
            void extend(void)
            {
                pointer prev_start = _start;
                pointer prev_end = _end;
                size_type prev_size = this->size();
                size_type prev_capacity = this->capacity();
                double expos = log2(this->capacity());
                int next_capacity = pow(2, ((expos == -INFINITY) ? 0 : expos + 1));
                
                _start = _alloc.allocate( next_capacity );
                _end_capacity = _start + next_capacity;
                _end = _start;
                while (prev_start != prev_end)
                {
                    _alloc.construct(_end, *prev_start);
                    _end++;
                    prev_start++;
                }
                _alloc.deallocate(prev_start - prev_size, prev_capacity);
            }

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
                    throw (std::out_of_range("vector::checkRange: n (which is "
                            + ft::to_string(n) + ") >= this->size() (which is "
                            + ft::to_string(this->size()) + ")"));
            }
    };

    // Non-member function overloads
    
    /*
    ** @brief Compare vector container to know
    ** if they are equal. Start to check if the size
    ** is different.
    **
    ** @param lhs Vector to compare with "rhs".
    ** @param rhs Vector for comparison of "lhs".
    ** @return true if they are equal, false otherwise.
    */
    template <class T, class Alloc>
        bool operator== (const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
        {
            if (lhs.size() != rhs.size())
                return (false);
            return (&lhs == &rhs);
        }

    /*
    ** Need implement lexicographical_compare
    */ 
    /** ________________________ WIP ________________________*/
    template <class T, class Alloc>
        bool operator!= (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
        {
            return (!(lhs == rhs));
        }
    
    /** ________________________ WIP ________________________*/
    template <class T, class Alloc>
        bool operator<  (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
        {
            return (&lhs < &rhs);
        }

    /** ________________________ WIP ________________________*/
    template <class T, class Alloc>
        bool operator<= (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
        {
            return (!(lhs < rhs));
        }

    /** ________________________ WIP ________________________*/
    template <class T, class Alloc>
        bool operator>  (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
        {
            return (rhs < lhs);
        }

    /** ________________________ WIP ________________________*/
    template <class T, class Alloc>
        bool operator>= (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
        {
            return (!(lhs < rhs));
        }
}
// =============================================================================

#endif