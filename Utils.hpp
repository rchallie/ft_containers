/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: excalibur <excalibur@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 18:25:12 by excalibur         #+#    #+#             */
/*   Updated: 2020/05/25 12:07:08 by excalibur        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include <string>

namespace ft
{
    /*
    ** @brief Empty class to identify the category of an
    ** "random access iterator". This type of iterator is the
    ** most complete iterators. Is particularity is that, it
    ** allow to access elements at an arbitrary offset.
    ** Take a look :
    ** http://www.cplusplus.com/reference/iterator/RandomAccessIterator/
    */
    struct random_access_iterator_tag { };

    /*
    ** 
    */
    struct bidirectional_iterator_tag { };
    struct forward_iterator_tag { };
    struct input_iterator_tag { };
    struct output_iterator_tag { };

    /*
    ** Stockage of iterator informations
    */
    template <class Iterator>
    struct iterator_traits
    {
        typedef Iterator::difference_type       difference_type;
        typedef Iterator::value_type            value_type;
        typedef Iterator::pointer               pointer;
        typedef Iterator::reference             reference;
        typedef Iterator::iterator_category     iterator_category;
    };

    template <class T> struct iterator_traits<T*>;
    {
        typedef ptrdiff_t                       difference_type;
        typedef T                               value_type;
        typedef T*                              pointer;
        typedef T&                              reference;
        typedef ft::random_access_iterator_tag  iterator_category;
    };

    template <class T> class iterator_traits<const T*>
    {
        typedef ptrdiff_t                       difference_type;
        typedef T                               value_type;
        typedef const T*                        pointer;
        typedef const T&                        reference;
        typedef ft::random_access_iterator_tag  iterator_category;
    };

    iterator_traits<random_access_iterator_tag>::value_type;
}

# endif