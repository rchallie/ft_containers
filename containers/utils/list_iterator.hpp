/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_iterator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchallie <rchallie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 17:45:48 by rchallie          #+#    #+#             */
/*   Updated: 2020/12/05 22:10:07 by rchallie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_ITERATOR_HPP
# define LIST_ITERATOR_HPP

#include "utils.hpp"

namespace ft
{
    template <typename T>
    class List_Iterator : public ft::iterator<ft::bidirectional_iterator_tag, T>
    {
        public:
            /* Category of the iterator. */
            typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category     iterator_category;
            
            /* Type of elements pointed. */
            typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::value_type            value_type;
            
            /* Type to represent the difference between two iterators. */
            typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type       difference_type;
            
            /* Type to represent a pointer to an element pointed */
            typedef T*  pointer;
            
            /* Type to represent a reference to an element pointed */
            typedef T&  reference;

            /*
            ** @brief Default construtor:
            ** The bidirectional iterator point to null.
            */
            List_Iterator()
            :
                _node(u_nullptr)
            {}

            /*
            ** @brief Constructor from pointer:
            ** Construct a bidirectional iterator and point to the
            ** element passed in argument.
            **
            ** @param elem the pointer to the element to iterate. 
            */
            List_Iterator(Doubly_Linked_Node<T> *init_node)
            :
                _node(init_node)
            {}

            /*
            ** Copy constructor:
            ** Construct a bidirectional iterator and copy the pointer
            ** who point to the element from "x" to this.
            **
            ** @param op the const reference to the bidirectional iterator
            ** to copy.
            */
            List_Iterator(const List_Iterator& x)
            :
                _node(x._node)
            {}

            /*
            ** Copy assignation:
            ** Give a bidirectional iterator who is a copy
            ** from "x".
            **
            ** @param op the const reference to the bidirectional
            ** iterator to copy.
            ** @return the bidirectional iterator.
            */
            List_Iterator &operator= (const List_Iterator& x)
            {
                if (&x == this)
                    return (*this);
                this->_node = x._node;
                return (*this);
            }

            /* Destructor: */
            virtual ~List_Iterator() {}

            /*
            ** @brief Give a reference to the rvalue pointed by the 
            ** bidirectionnal iterator.
            **
            ** @return the rvalue (value where point the pointer).
            */
            reference operator* (void) { return (_node->data); }

            /*
            ** @brief Give the lvalue of the element where is the
            ** bidirectional iterator.
            **
            ** @return the lvalue (the pointer to the element).
            */
            pointer operator->(void) { return &(this->operator*()); }
    
            /*
            ** @brief Preincrement the iterator to point to the
            ** next element of the list.
            **
            ** @return A reference of to this bidiretional iterator
            ** where it point to the next element of the list.
            */
            List_Iterator& operator++(void)
            {
                this->_node = this->_node->next;
                return (*this);
            }

            /*
            ** @brief Postincrement the iterator to point to the
            ** next element of the list.
            **
            ** @return a bidiretional iterator incremented (copy
            ** of this).
            */
            List_Iterator operator++(int)
            {
                List_Iterator rtn(*this);
                operator++();
                return (rtn);
            }

            /*
            ** @brief Predecrement the iterator to point to the
            ** previous element in the list.
            **
            ** @return A reference of to this bidirectional iterator
            ** where it point to the previous element in the list.
            */
            List_Iterator& operator--(void)
            {
                this->_node = this->_node->prev;
                return (*this);
            }

            /*
            ** @brief Postdecrement the iterator to point to the
            ** previous element in the list.
            **
            ** @return a bidirectional iterator decremented (copy
            ** of this).
            */
            List_Iterator operator--(int)
            {
                List_Iterator rtn(*this);
                operator--();
                return (rtn);
            }

            operator List_Iterator<const T> () const
            { return (List_Iterator<const T>(reinterpret_cast<Doubly_Linked_Node<const int> *>(this->_node))); }

            Doubly_Linked_Node<T> *_node;
    };
    
    /*
    ** @brief Check if the pointer of "lhs"
    ** is equal than "rhs" in the memory.
    **
    ** @param lhs the bidirectional iterator to compare.
    ** @param rhs the bidirectional iterator with who check.
    ** @return true if the pointer of lhs
    ** if equal than "rhs", otherwise false.
    */
    template <typename T>
    typename ft::List_Iterator<T>::difference_type
    operator==(const ft::List_Iterator<T> lhs,
              const ft::List_Iterator<T> rhs)
    {
        return (lhs._node == rhs._node);
    }

    /* For iterator == const_iterator */
    template<typename T_L, typename T_R>
    typename ft::List_Iterator<T_L>::difference_type
    operator==(const ft::List_Iterator<T_L> lhs,
              const ft::List_Iterator<T_R> rhs)
    {
        return (lhs._node == rhs._node);
    }

    /*
    ** @brief Check if the pointer of "lhs"
    ** is equal than "rhs" in the memory.
    **
    ** @param lhs the bidirectional iterator to compare.
    ** @param rhs the bidirectional iterator with who check.
    ** @return true if the pointer of lhs
    ** if equal than "rhs", otherwise false.
    */
    template <typename T>
    typename ft::List_Iterator<T>::difference_type
    operator!=(const ft::List_Iterator<T> lhs,
              const ft::List_Iterator<T> rhs)
    {
        return (lhs._node != rhs._node);
    }

    /* For iterator != const_iterator */
    template<typename T_L, typename T_R>
    typename ft::List_Iterator<const T_L>::difference_type
    operator!=(const ft::List_Iterator<T_L> lhs,
              const ft::List_Iterator<T_R> rhs)
    {
        return (lhs._node != rhs._node);
    }
}

#endif