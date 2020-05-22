/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: excalibur <excalibur@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/18 12:45:54 by excalibur         #+#    #+#             */
/*   Updated: 2020/05/23 00:04:52 by excalibur        ###   ########.fr       */
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
// =============================================================================

// PROTOTYPES ==================================================================
// =============================================================================

// CLASS DEFINITIONS ===========================================================
namespace ft
{
    template < class T, class Alloc = std::allocator<T> >
    class vector
    {
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
        typedef std::random_access_iterator_tag             iterator;

        /*
        ** A random access iterator to const value_type
        ** That can read element stored.
        */
        typedef std::random_access_iterator_tag             const_iterator;
        
        /*
        ** std::reverse_iterator<iterator>
        ** That can read or modify any element in a reversed vector.
        ** Used to iterate through the vector in reverse.
        */
        typedef std::reverse_iterator<iterator>             reverse_iterator;

        /*
        ** std::reverse_iterator<const_iterator>
        ** That can read any element in a reversed the vector.
        ** Can't be used to modify, used to iterate through the
        ** the vector in reverse.
        */
        typedef std::reverse_iterator<const_iterator>       const_reverse_iterator;

        /*
        ** A signed integral type:
        ** Usually the same as ptrdiff_t.
        ** Can represent the difference between iterators to the
        ** element actually stored.
        ** Can be described as te number of element between two pointers.
        ** (Pointer to an element contains its address).
        */
        typedef typename allocator_type::difference_type    difference_type; 

        /*
        ** An unsigned integral type that can represent any
        ** non-negative value of difference_type
        ** Usually the same as size_t.
        ** Is the number of elements in a vector.
        */
        typedef typename allocator_type::size_type          size_type;
        
        public:
            // Coplien
            vector() {};
            vector(const vector&);
            virtual ~vector() {};
            vector &operator=(const vector& op);

            // Getter - Setter

            // Additionnal

            // Exceptions
    };
}
// =============================================================================

// FUNCTIONS SUP PROTOYPES =====================================================
// =============================================================================

#endif