/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchallie <rchallie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 17:50:14 by rchallie          #+#    #+#             */
/*   Updated: 2020/11/29 17:20:04 by rchallie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

#include "utils.hpp"

namespace ft
{
    
    /*
    ** @brief Random-access iterators allow to access elements at an
    ** arbitrary offset position relative to the element they point
    ** to. This is the most complete iterators. All pointer types
    ** are also valid random-access-iterators.
    */
    template <typename T>
        class random_access_iterator : ft::iterator<ft::random_access_iterator_tag, T>
        {
            public:
                
                /* Category of the iterator. */
                typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category     iterator_category;
                
                /* Type of elements pointed. */
                typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type            value_type;
                
                /* Type to represent the difference between two iterators. */
                typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type       difference_type;
                
                /* Type to represent a pointer to an element pointed */
                typedef T*               pointer;
                
                /* Type to represent a reference to an element pointed */
                typedef T&             reference;
                
                /*
                ** @brief Default construtor:
                ** The random access iterator point to null.
                */
                random_access_iterator(void)
                :
                    _elem(u_nullptr)
                {}

                /*
                ** @brief Constructor from pointer:
                ** Construct a random access iterator and point to the
                ** element passed in argument.
                **
                ** @param elem the pointer to the element to iterate. 
                */
                random_access_iterator(pointer elem)
                :
                    _elem(elem)
                {}

                /*
                ** Copy constructor:
                ** Construct a random access iterator and copy the pointer
                ** who point to the element from "op" to this.
                **
                ** @param op the const reference to the random access iterator
                ** to copy.
                */
                random_access_iterator(const random_access_iterator& op)
                :
                    _elem(op._elem)
                {}

                /*
                ** Copy assignation:
                ** Give a random access iterator who is a copy
                ** from "op".
                **
                ** @param op the const reference to the random access
                ** iterator to copy.
                ** @return the random access iterator.
                */
                random_access_iterator &operator=(const random_access_iterator& op)
                {
                    if (this == &op)
		                return (*this);
                    this->_elem = op._elem;
                    return (*this);
                }

                /* Destructor: */
                virtual ~random_access_iterator() {}

                /*
                ** @brief Give a pointer to the
                ** element where the iterator point.
                **
                ** @return the iterator.
                */
                pointer base() const
                { return (this->_elem); }

                /*
                ** @brief Give a reference to the rvalue pointed by the 
                ** random access iterator.
                **
                ** @return the rvalue (value where point the pointer).
                */
                reference operator*(void) const { return (*_elem); }

                /*
                ** @brief Give the lvalue of the element where is the
                ** random access iterator.
                **
                ** @return the lvalue (the pointer to the element).
                */
                pointer operator->(void) { return &(this->operator*()); }

                /*
                ** @brief Preincrement the iterator to point to the
                ** next element in memory.
                **
                ** @return A reference of to this random access iterator
                ** where it point to the next element in memory.
                */
                random_access_iterator& operator++(void)
                {
                    _elem++;
                    return (*this);
                }

                /*
                ** @brief Postincrement the iterator to point to the
                ** next element in memory.
                **
                ** @return a random access iterator incremented (copy
                ** of this).
                */
                random_access_iterator operator++(int)
                {
                    random_access_iterator rtn(*this);
                    operator++();
                    return (rtn);
                }

                /*
                ** @brief Predecrement the iterator to point to the
                ** previous element in memory.
                **
                ** @return A reference of to this random access iterator
                ** where it point to the previous element in memory.
                */
                random_access_iterator& operator--(void)
                {
                    _elem--;
                    return (*this);
                }

                /*
                ** @brief Postdecrement the iterator to point to the
                ** previous element in memory.
                **
                ** @return a random access iterator decremented (copy
                ** of this).
                */
                random_access_iterator operator--(int)
                {
                    random_access_iterator rtn(*this);
                    operator--();
                    return (rtn);
                }

                /*
                ** @brief Give a random access iterator where the
                ** element is pointed at this + "n" in memory.
                **
                ** @param n the number of elements.
                ** @return the random access iterator.
                */
                random_access_iterator operator+(difference_type n) const { return (_elem + n); }

                /*
                ** @brief Give a random access iterator where the
                ** element is pointed at this - "n" in memory.
                **
                ** @param n the number of elements.
                ** @return the random access iterator.
                */
                random_access_iterator operator-(difference_type n) const { return (_elem - n); }

                /*
                ** @brief Give a reference to this random access iterator
                ** where the element pointed is at the actual pointer memory 
                ** plus "n".
                **
                ** @param n the number of elements.
                ** @return the random access iterator.
                */
                random_access_iterator& operator+=(difference_type n)
                {
                    _elem += n;
                    return (*this);
                }

                /*
                ** @brief Give a reference to this random access iterator
                ** where the element pointed is at the actual pointer memory 
                ** minus "n".
                **
                ** @param n the number of elements.
                ** @return the random access iterator.
                */
                random_access_iterator& operator-=(difference_type n)
                {
                    _elem -= n;
                    return (*this);
                }

                /*
                ** @brief Give a reference to the elements at an arbitrary offset 
                ** position relative to the element pointed by the random access
                ** iterator.
                ** 
                ** @param n the offset position.
                ** @return the reference.
                */
                reference operator[](difference_type n) { return (*(operator+(n))); }

                operator random_access_iterator<const T> () const
                { return (random_access_iterator<const T>(this->_elem)); }

                private:
                    /* Element pointed by the iterator. */
                    pointer _elem;
        };

    /*
    ** @brief Check if the pointer of "lhs"
    ** is equal than "rhs" in the memory.
    **
    ** @param lhs the random access iterator to compare.
    ** @param rhs the random access iterator with who check.
    ** @return true if the pointer of lhs
    ** if equal than "rhs", otherwise false.
    */
    template <typename T>
    typename ft::random_access_iterator<T>::difference_type
    operator==(const ft::random_access_iterator<T> lhs,
              const ft::random_access_iterator<T> rhs)
    {
        return (lhs.base() == rhs.base());
    }

    /* For iterator == const_iterator */
    template<typename T_L, typename T_R>
    typename ft::random_access_iterator<T_L>::difference_type
    operator==(const ft::random_access_iterator<T_L> lhs,
              const ft::random_access_iterator<T_R> rhs)
    {
        return (lhs.base() == rhs.base());
    }

    /*
    ** @brief Check if the pointer of "lhs"
    ** is different than "rhs" in the memory.
    **
    ** @param lhs the random access iterator to compare.
    ** @param rhs the random access iterator with who check.
    ** @return true if the pointer of lhs
    ** if different than "rhs", otherwise false.
    */
    template <typename T>
    typename ft::random_access_iterator<T>::difference_type
    operator!=(const ft::random_access_iterator<T> lhs,
              const ft::random_access_iterator<T> rhs)
    {
        return (lhs.base() != rhs.base());
    }

    /* For iterator != const_iterator */
    template<typename T_L, typename T_R>
    typename ft::random_access_iterator<T_L>::difference_type
    operator!=(const ft::random_access_iterator<T_L> lhs,
              const ft::random_access_iterator<T_R> rhs)
    {
        return (lhs.base() != rhs.base());
    }

    /*
    ** @brief Check if the pointer of "lhs"
    ** is lower than "rhs" in the memory.
    **
    ** @param lhs the random access iterator to compare.
    ** @param rhs the random access iterator with who check.
    ** @return true if the pointer of lhs
    ** if lower than "rhs", otherwise false.
    */
    template <typename T>
    typename ft::random_access_iterator<T>::difference_type
    operator<(const ft::random_access_iterator<T> lhs,
              const ft::random_access_iterator<T> rhs)
    {
        return (lhs.base() < rhs.base());
    }

    /* For iterator < const_iterator */
    template<typename T_L, typename T_R>
    typename ft::random_access_iterator<T_L>::difference_type
    operator<(const ft::random_access_iterator<T_L> lhs,
              const ft::random_access_iterator<T_R> rhs)
    {
        return (lhs.base() < rhs.base());
    }

    /*
    ** @brief Check if the pointer of "lhs"
    ** is upper than "rhs" in the memory.
    **
    ** @param lhs the random access iterator to compare.
    ** @param rhs the random access iterator with who check.
    ** @return true if the pointer of lhs
    ** if upper than "rhs", otherwise false.
    */
    template <typename T>
    typename ft::random_access_iterator<T>::difference_type
    operator>(const ft::random_access_iterator<T> lhs,
              const ft::random_access_iterator<T> rhs)
    {
        return (lhs.base() > rhs.base());
    }

    /* For iterator > const_iterator */
    template<typename T_L,
             typename T_R>
    typename ft::random_access_iterator<T_L>::difference_type
    operator>(const ft::random_access_iterator<T_L> lhs,
              const ft::random_access_iterator<T_R> rhs)
    {
        return (lhs.base() > rhs.base());
    }

    /*
    ** @brief Check if the pointer of "lhs"
    ** is lower or equal than "rhs" in the memory.
    **
    ** @param lhs the random access iterator to compare.
    ** @param rhs the random access iterator with who check.
    ** @return true if the pointer of lhs
    ** if lower or equal than "rhs", otherwise false.
    */
    template <typename T>
    typename ft::random_access_iterator<T>::difference_type
    operator<=(const ft::random_access_iterator<T> lhs,
              const ft::random_access_iterator<T> rhs)
    {
        return (lhs.base() <= rhs.base());
    }

    /* For iterator <= const_iterator */
    template<typename T_L, typename T_R>
    typename ft::random_access_iterator<T_L>::difference_type
    operator<=(const ft::random_access_iterator<T_L> lhs,
              const ft::random_access_iterator<T_R> rhs)
    {
        return (lhs.base() <= rhs.base());
    }

    /*
    ** @brief Check if the pointer of "lhs"
    ** is upper or equal than "rhs" in the memory.
    **
    ** @param lhs the random access iterator to compare.
    ** @param rhs the random access iterator with who check.
    ** @return true if the pointer of lhs
    ** if upper or equal than "rhs", otherwise false.
    */
    template <typename T>
    typename ft::random_access_iterator<T>::difference_type
    operator>=(const ft::random_access_iterator<T> lhs,
              const ft::random_access_iterator<T> rhs)
    {
        return (lhs.base() >= rhs.base());
    }

    /* For iterator >= const_iterator */
    template<typename T_L,
             typename T_R>
    typename ft::random_access_iterator<T_L>::difference_type
    operator>=(const ft::random_access_iterator<T_L> lhs,
              const ft::random_access_iterator<T_R> rhs)
    {
        return (lhs.base() >= rhs.base());
    }

    /*
    ** @brief Give a random access iterator pointing to
    ** "rai" plus "n".
    **
    ** @param n The number of location away the element pointed 
    ** by rai.
    ** @param rai The random access iterator.
    ** @return A random access iterator pointing to n element
    ** after rai pointed element.
    */
    template<typename T>
    ft::random_access_iterator<T> operator+(
        typename ft::random_access_iterator<T>::difference_type n,
        typename ft::random_access_iterator<T>& rai)
        {
            return (&(*rai) + n);
        }

    /*
    ** @brief Give the difference between the address
    ** of two random access iterators.
    **
    ** @param lhs,rhs the two random access iterator with whom 
    ** to make a difference.
    ** @return The difference.
    */
    template <typename T>
    typename ft::random_access_iterator<T>::difference_type
    operator-(const ft::random_access_iterator<T> lhs,
              const ft::random_access_iterator<T> rhs)
    {
        return (lhs.base() - rhs.base());
    }

    /* For iterator - const_iterator */
    template<typename T_L, typename T_R>
    typename ft::random_access_iterator<T_L>::difference_type
    operator-(const ft::random_access_iterator<T_L> lhs,
              const ft::random_access_iterator<T_R> rhs)
    {
        return (lhs.base() - rhs.base());
    }

}

#endif