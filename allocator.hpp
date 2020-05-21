/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocator.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: excalibur <excalibur@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/18 12:45:54 by excalibur         #+#    #+#             */
/*   Updated: 2020/05/22 00:00:03 by excalibur        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * DOCUMENTATION :
 * http://www.cplusplus.com/reference/memory/allocator/?kw=allocator
 * https://docs.microsoft.com/fr-fr/cpp/standard-library/allocator-class?view=vs-2019
 * https://docs.roguewave.com/sourcepro/11.1/html/toolsug/11-6.html
 */

#ifndef ALLOCATOR_HPP
# define ALLOCATOR_HPP

// LIBS ========================================================================
// =============================================================================

// PROTOTYPES ==================================================================
// =============================================================================

// CLASS DEFINITIONS ===========================================================
namespace ft
{
    template < class T >
    class allocator
    {
        // Members : 

        /*
        ** Element type
        ** Type manage by the allocator
        */
        typedef T           value_type;
        
        /*
        ** Pointer to element
        ** Give a pointer to the element actually manage by the allocator
        */
        typedef T*          pointer;

        /*
        ** Reference to element
        ** Give a reference to the element actually manage by the allocator
        */
        typedef T&          reference;

        /*
        ** Pointer to constant element
        ** Give a pointer to the element actually manage by the allocator
        */
        typedef const T*    const_pointer;

        /*
        ** Reference to constant element
        ** Give a constant reference to the element actually manage by the allocator
        */
        typedef const T&    cont_reference; 
 
        /*
        ** Quantities of elements
        ** 0 or previous value obtained by a call to allocate and not yet freed with
        ** deallocate.
        */
        typedef size_t      size_type;

        /*
        ** Difference between two pointers
        ** Can represent the difference between values from pointers to the
        ** element actually manage by the allocator
        */
        typedef ptrdiff_t   difference_type;

        public:
            // Coplien

            /*
            ** Contructors
            ** Do nothing. But an allocator object construct
            ** from another allocator object need to have the same
            ** value and allow exchange and free of the two allocator objects
            */
            allocator();
            allocator(const allocator&);
            
            /*
            ** Destructor
            ** Do nothing.
            */
            virtual ~allocator();

            /*
            ** Copy
            */
            allocator<T> &operator=(const allocator& op) { return *this; }

            // Functions

            //  ______________________ WIP ______________________________ 
            pointer         address ( reference x ) const;
            const_pointer   address ( const_reference x ) const;
    };
}

// =============================================================================

// FUNCTIONS SUP PROTOYPES =====================================================
// =============================================================================

#endif