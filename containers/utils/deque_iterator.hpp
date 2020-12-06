/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_iterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchallie <rchallie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 16:39:39 by rchallie          #+#    #+#             */
/*   Updated: 2020/12/04 18:16:44 by rchallie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEQUE_ITERATOR_HPP
# define DEQUE_ITERATOR_HPP

#include "utils.hpp"

namespace ft
{
    template<typename T>
    class Deque_Iterator : public ft::iterator<ft::random_access_iterator_tag, T>
    {
        public:
            /* Category of the iterator. */
            typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category     iterator_category;
            
            /* Type of elements pointed. */
            typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type            value_type;
            
            /* Type to represent the difference between two iterators. */
            typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type       difference_type;
            
            /* Type to represent a pointer to an element pointed */
            typedef T*  pointer;
            
            /* Type to represent a reference to an element pointed */
            typedef T&  reference;

            typedef T**       map_pointer;
            
            Deque_Iterator()
            :
                _map(),
                _elem(),
                _start_cur_block(),
                _end_cur_block()
            {}

            Deque_Iterator(pointer elem, map_pointer map)
            :
                _map(map),
                _elem(elem),
                _start_cur_block(*map),
                _end_cur_block(*map + _deque_block_size(sizeof(value_type)))
            {}

            Deque_Iterator(const Deque_Iterator& di)
            :
                _map(di._map),
                _elem(di._elem),
                _start_cur_block(di._start_cur_block),
                _end_cur_block(di._end_cur_block)
            {}

            Deque_Iterator& operator=(const Deque_Iterator& di)
            {
                this->_map = di._map;
                this->_elem = di._elem;
                this->_start_cur_block = di._start_cur_block;
                this->_end_cur_block = di._end_cur_block;
                return (*this);
            }

            ~Deque_Iterator() {}

            reference operator*()
            { return (*this->_elem); }

            pointer operator->()
            { return (this->_elem); }

            Deque_Iterator& operator++(void)
            {
                ++this->_elem;
                if (this->_elem == this->_end_cur_block)
                {
                    this->_map++;
                    this->_start_cur_block = *this->_map;
                    this->_end_cur_block = this->_start_cur_block + difference_type(_deque_block_size(sizeof(value_type)));
                    this->_elem = this->_start_cur_block;
                }
                return (*this);
            }

            Deque_Iterator operator++(int)
            {
                Deque_Iterator tmp(*this);
                operator++();
                return (tmp);
            }

            Deque_Iterator& operator--(void)
            {
                if (this->_elem == this->_start_cur_block)
                {
                    this->_map--;
                    this->_start_cur_block = *this->_map;
                    this->_end_cur_block = this->_start_cur_block + _deque_block_size(sizeof(value_type));
                    this->_elem = this->_end_cur_block;
                }
                this->_elem--;
                return (*this);
            }

            Deque_Iterator operator--(int)
            {
                Deque_Iterator tmp(*this);
                operator--();
                return (tmp);
            }

            Deque_Iterator operator+(difference_type n) const
            {
                Deque_Iterator tmp(*this);
                while (n--)
                {
                    tmp._elem++;
                    if (tmp._elem == tmp._end_cur_block)
                    {
                        tmp._map++;
                        tmp._start_cur_block = *tmp._map;
                        tmp._end_cur_block = tmp._start_cur_block + tmp._deque_block_size(sizeof(value_type));
                        tmp._elem = tmp._start_cur_block;
                    }
                }
                return (tmp);
            }

            Deque_Iterator operator-(difference_type n) const
            {
                Deque_Iterator tmp(*this);
                while (n--)
                {
                    if (tmp._elem == tmp._start_cur_block)
                    {
                        tmp._map--;
                        tmp._start_cur_block = *tmp._map;
                        tmp._end_cur_block = tmp._start_cur_block + tmp._deque_block_size(sizeof(value_type));
                        tmp._elem = tmp._end_cur_block;
                    }
                    tmp._elem--;
                }
                return (tmp);
            }

            Deque_Iterator& operator+=(difference_type n)
            {
                while (n--)
                    operator++();
                return (*this);
            }

            Deque_Iterator& operator-=(difference_type n)
            {
                while (n--)
                    operator--();
                return (*this);
            }

            reference operator[](difference_type n)
            {
                return (*((*this) + n));
            }

            map_pointer _map;
            pointer _elem;
            pointer _start_cur_block;
            pointer _end_cur_block;

            size_t _deque_block_size(size_t size) const
            { return ((size < 512) ? size_t(512 / sizeof(value_type)) : size_t(1)); }

            /*
            ** @brief Operator to cast Deque_Iterator<T> to const Deque_Iterator<const T>
            **
            ** @return a new Deque_Iterator converted to const.
            */
            operator Deque_Iterator<const T> () const
            { return (Deque_Iterator<const T>(this->_elem, const_cast<const int **>(this->_map))); }
    };

    template<typename T>
    typename ft::Deque_Iterator<T>::difference_type
    operator==(const ft::Deque_Iterator<T>& lhs,
              const ft::Deque_Iterator<T>& rhs)
    {
        return (lhs._elem == rhs._elem);
    }

    template<typename T_L,
            typename T_R>
    typename ft::Deque_Iterator<T_L>::difference_type
    operator==(const ft::Deque_Iterator<T_L>& lhs,
              const ft::Deque_Iterator<T_R>& rhs)
    {
        return (lhs._elem == rhs._elem);
    }

    template<typename T>
    typename ft::Deque_Iterator<T>::difference_type
    operator!=(const ft::Deque_Iterator<T>& lhs,
              const ft::Deque_Iterator<T>& rhs)
    {
        return (lhs._elem != rhs._elem);
    }

    template<typename T_L,
            typename T_R>
    typename ft::Deque_Iterator<T_L>::difference_type
    operator!=(const ft::Deque_Iterator<T_L>& lhs,
              const ft::Deque_Iterator<T_R>& rhs)
    {
        return (lhs._elem != rhs._elem);
    }

    template<typename T>
    ft::Deque_Iterator<T> operator+(
        typename ft::Deque_Iterator<T>::difference_type n,
        const ft::Deque_Iterator<T>& di)
    {
        return (di + n);
    }

    template<typename T>
    typename ft::Deque_Iterator<T>::difference_type
    operator-(const ft::Deque_Iterator<T>& lhs,
              const ft::Deque_Iterator<T>& rhs)
    {
        /* nbr block between the two iterator blocks * nbr of element in one block
        + (difference between this iterator element - start of is block)
        + (iterator, with which to make a difference, end block - it element) */
        return (typename ft::Deque_Iterator<T>::difference_type(
            ((lhs._map - rhs._map - 1)
            * lhs._deque_block_size(sizeof(T)))
            + (lhs._elem - lhs._start_cur_block) + (rhs._end_cur_block - rhs._elem)));
    }

    template<typename T_L,
            typename T_R>
    typename ft::Deque_Iterator<T_L>::difference_type
    operator-(const ft::Deque_Iterator<T_L>& lhs,
              const ft::Deque_Iterator<T_R>& rhs)
    {
        /* nbr block between the two iterator blocks * nbr of element in one block
        + (difference between this iterator element - start of is block)
        + (iterator, with which to make a difference, end block - it element) */
        return (typename ft::Deque_Iterator<T_L>::difference_type(
            ((lhs._map - rhs._map - 1)
            * lhs._deque_block_size(sizeof(T_L)))
            + (lhs._elem - lhs._start_cur_block) + (rhs._end_cur_block - rhs._elem))); 
    }

    template<typename T>
    typename ft::Deque_Iterator<T>::difference_type
    operator<(const ft::Deque_Iterator<T>& lhs,
              const ft::Deque_Iterator<T>& rhs)
    {
        if (lhs._map == rhs._map)
            return (lhs._elem < rhs._elem);
        return (lhs._map < rhs._map);
    }

    template<typename T_L,
            typename T_R>
    typename ft::Deque_Iterator<T_L>::difference_type
    operator<(const ft::Deque_Iterator<T_L>& lhs,
              const ft::Deque_Iterator<T_R>& rhs)
    {
        if (lhs._map == rhs._map)
            return (lhs._elem < rhs._elem);
        return (lhs._map < rhs._map);
    }

    template<typename T>
    typename ft::Deque_Iterator<T>::difference_type
    operator>(const ft::Deque_Iterator<T>& lhs,
              const ft::Deque_Iterator<T>& rhs)
    {
        if (lhs._map == rhs._map)
            return (lhs._elem > rhs._elem);
        return (lhs._map > rhs._map);
    }

    template<typename T_L,
            typename T_R>
    typename ft::Deque_Iterator<T_L>::difference_type
    operator>(const ft::Deque_Iterator<T_L>& lhs,
              const ft::Deque_Iterator<T_R>& rhs)
    {
        if (lhs._map == rhs._map)
            return (lhs._elem > rhs._elem);
        return (lhs._map > rhs._map);
    }

    template<typename T>
    typename ft::Deque_Iterator<T>::difference_type
    operator<=(const ft::Deque_Iterator<T>& lhs,
              const ft::Deque_Iterator<T>& rhs)
    {
        if (lhs._map == rhs._map)
            return (lhs._elem <= rhs._elem);
        return (lhs._map <= rhs._map);
    }

    template<typename T_L,
            typename T_R>
    typename ft::Deque_Iterator<T_L>::difference_type
    operator<=(const ft::Deque_Iterator<T_L>& lhs,
              const ft::Deque_Iterator<T_R>& rhs)
    {
        if (lhs._map == rhs._map)
            return (lhs._elem <= rhs._elem);
        return (lhs._map <= rhs._map);
    }

    template<typename T>
    typename ft::Deque_Iterator<T>::difference_type
    operator>=(const ft::Deque_Iterator<T>& lhs,
              const ft::Deque_Iterator<T>& rhs)
    {
        if (lhs._map == rhs._map)
            return (lhs._elem >= rhs._elem);
        return (lhs._map >= rhs._map);
    }

    template<typename T_L,
            typename T_R>
    typename ft::Deque_Iterator<T_L>::difference_type
    operator>=(const ft::Deque_Iterator<T_L>& lhs,
              const ft::Deque_Iterator<T_R>& rhs)
    {
        if (lhs._map == rhs._map)
            return (lhs._elem >= rhs._elem);
        return (lhs._map >= rhs._map);
    }
}

#endif