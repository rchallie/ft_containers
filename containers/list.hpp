/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchallie <rchallie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 22:01:32 by rchallie          #+#    #+#             */
/*   Updated: 2020/12/03 22:44:32 by rchallie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
#define LIST_HPP

# include "./utils/utils.hpp"

namespace ft
{
    template < class T, class Alloc = std::allocator<T> > class list
    {
        typedef T   value_type;

        typedef Alloc   allocator_type;

        typedef typename allocator_type::reference   reference;

        typedef typename allocator_type::const_reference const_reference;

        typedef typename allocator_type::pointer     pointer;

        typedef typename allocator_type::const_pointer const_pointer;

        //typedef ft::List_iterator<T>  iterator;

        //typedef ft::List_iterator<const T> const_iterator;

        //typdef ft::reverse_iterator<iterator> reverse_iterator;

        //typdef ft::reverse_iterator<const_iterator> const_reverse_iterator;

        //typedef typename iterator_traits<iterator>::difference_type difference_type;

        typedef size_t  size_type;

        public :

            explicit list (const allocator_type& alloc = allocator_type());

            explicit list (size_type n, const value_type& val = value_type(),
                            const allocator_type& alloc = allocator_type());

            /*
            template <class InputIterator>
                list (InputIterator first, InputIterator last,
                const allocator_type& alloc = allocator_type());
            */


            list (const list& x);

            ~list();

            list& operator= (const list & x);

            // iterator begin();

            // const_iterator begin() const;

            // iterator end();

            // const_iterator end() const;

            // reverse_iterator rbegin();

            // const_reverse_iterator rbegin() const;

            // reverse_iterator rend();

            // const_reverse_iterator rend() const;

            // bool empty() const;

            // size_type size() const;

            // size_type max_size() const;

            // reference front();

            // const_reference front() const;

            // reference back();

            // const_reference back() const;

            /*
            template <class InputIterator>
                void assign (InputIterator first, InputIterator last);
            */

            // void assign (size_type n, const value_type& val);

            // void push_front (const value_type& val);

            // void pop_front();

            // void push_back();

            // void pop_back();

            // iterator insert (iterator position, const value_type& val);

            // void insert (iterator position, size_type n, const value_type& val);

            /*
            template <class InputIterator>
                void insert (iterator position, InputIterator first, InputIterator last);
            */

           // iterator erase (iterator position);

           // iterator erase (iterator first, iterator last);

           // void swap (list& x):

           // void resize (size_type n, value_type val = value_type());

           // void clear();

           // void splice (iterator position, list& x);

           // void splice (iterator position, list& x, iterator i);

           // void splice (iterator position, list& x, iterator first, iterator last);

            // void remove(const value_type& val);

            /*
            template <class Predicate>
                void remove_if (Predicate pred);
            */

            // void unique();

            /*
            template <class BinaryPredicate>
                void unique (BinaryPredicate binary_pred);
            */
        
            // void merge();

            /*
            template <class Compare>
                void merge (list& x, Compare comp);
            */

            // void sort();

            /*
            template <class Compare>
                void sort (Compare comp);
            */

            // void reverse();



        private :

            Alloc _alloc;
    };

/*
template <class T, class Alloc>
  bool operator== (const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs);
template <class T, class Alloc>
  bool operator!= (const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs);
template <class T, class Alloc>
  bool operator<  (const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs);
template <class T, class Alloc>
  bool operator<= (const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs);
template <class T, class Alloc>
  bool operator>  (const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs);
template <class T, class Alloc>
  bool operator>= (const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs);
*/

/*
template <class T, class Alloc>
  void swap (ft::list<T,Alloc>& x, ft::list<T,Alloc>& y);
*/
}


#endif