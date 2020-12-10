/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchallie <rchallie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 11:10:54 by rchallie          #+#    #+#             */
/*   Updated: 2020/12/10 21:34:35 by rchallie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "deque.hpp"

namespace ft
{
	template <class T, class Container = ft::deque<T> > class stack
	{
		public:

			/*
			** The first template parameter (T)
			*/
			typedef T	value_type;

			/*
			** The second template parameter (container)
			** It's the type of underlying container object.
			*/
			typedef Container container_type;

			/*
			** The size type (usually size_t)
			*/
			typedef size_t	size_type;

			/*
			** Default constructor.
			** Construct an empty stack container adaptor object.
			**
			** @param Container object, is the type of the
			** underlying container type.
			*/
			explicit stack (const container_type& ctnr = container_type())
			:
				ct(ctnr)
			{}

			/*
			** @brief Destroy the container object.
			** Detroy all elements in the container.
			** Use the destructor of the underlying containter object.
			*/
			~stack()
			{}

			/*
			** @brief Call member "empty()" of the underlying
			** container object.
			**
			** @return true if the container is empty, otherwise
			** false.
			*/
			bool empty() const { return (this->ct.empty()); }

			/*
			** @brief Call member "size()" of the underlying
			** container object.
			**
			** @return the size of the container. (Number of elements
			** in it).
			*/
			size_type size() const { return (this->ct.size()); }

			/*
			** @brief Give a reference to the last
			** element inserted in the container.
			** Call member "back()" of the underlying container
			** object.
			**
			** @return a reference to the top element in the stack.
			*/
			value_type& top() { return (this->ct.back()); }

			/*
			** @brief Give a constant reference to the last
			** element inserted in the container.
			** Call member "back()" of the underlying container
			** object.
			**
			** @return a constant reference to the top element in the stack.
			*/
			const value_type& top() const { return (this->ct.back()); }

			/*
			** @brief insert a new element at the top of the
			** stack. The element is a copy of value parameter.
			** Call member "push_back()" of the underlying container
			** object.
			**
			** @param val the value to insert.
			*/
			void push (const value_type& val) { this->ct.push_back(val); }

			/*
			** @brief Remove the element on the top of the stack.
			** The element removed the last inserted on the stack.
			** Call the member "pop_back()" of the underlying container
			** object.
			*/
			void pop() { this->ct.pop_back(); }

			/*
			** @brief Declarations of prototypes for the
			** non members functions that needs to access
			** the protected variable.
			*/

			template <class Tn, class ContainerN>
				friend bool operator== (const ft::stack<Tn, ContainerN>& lhs, const ft::stack<Tn, ContainerN>& rhs);

			template <class Tn, class ContainerN>
				friend bool operator!= (const ft::stack<Tn, ContainerN>& lhs, const ft::stack<Tn, ContainerN>& rhs);
			
			template <class Tn, class ContainerN>
				friend bool operator< (const ft::stack<Tn, ContainerN>& lhs, const ft::stack<Tn, ContainerN>& rhs);

			template <class Tn, class ContainerN>
				friend bool operator<= (const ft::stack<Tn, ContainerN>& lhs, const ft::stack<Tn, ContainerN>& rhs);

			template <class Tn, class ContainerN>
				friend bool operator> (const ft::stack<Tn, ContainerN>& lhs, const ft::stack<Tn, ContainerN>& rhs);

			template <class Tn, class ContainerN>
				friend bool operator>= (const ft::stack<Tn, ContainerN>& lhs, const ft::stack<Tn, ContainerN>& rhs);

		protected:
			container_type ct;
	};

	// Each of the operator call the same operator of the
	// underlying container objects.

    /*
    ** @brief Compare stack container to know
    ** if they are different. Equivalent to !(lsh == rhs).
    **
    ** @param lhs stack to compare with "rhs".
    ** @param rhs stack for comparison of "lhs".
    ** @return true if they are different, false otherwise.
    */
	template <class T, class Container>
		bool operator== (const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
		{ return (lhs.ct == rhs.ct); }

    /*
    ** @brief Compare stack container to know
    ** if they are different. Equivalent to !(lsh == rhs).
    **
    ** @param lhs stack to compare with "rhs".
    ** @param rhs stack for comparison of "lhs".
    ** @return true if they are different, false otherwise.
    */
	template <class T, class Container>
		bool operator!= (const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
		{ return (lhs.ct != rhs.ct); }

    /*
    ** @brief Compare stack container to know
    ** if "lhs" elements are less than "rhs".
    **
    ** @param lhs stack to compare with "rhs".
    ** @param rhs stack for comparison of "lhs".
    ** @return true if "lhs" is less, false otherwise.
    */
	template <class T, class Container>
		bool operator< (const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
		{ return (lhs.ct < rhs.ct); }

    /*
    ** @brief Compare stack container to know
    ** if "lhs" elements are less or equal than "rhs".
    **
    ** @param lhs stack to compare with "rhs".
    ** @param rhs stack for comparison of "lhs".
    ** @return true if "lhs" is less of equal, false otherwise.
    */
	template <class T, class Container>
		bool operator<= (const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
		{ return (lhs.ct <= rhs.ct); }	
	
    /*
    ** @brief Compare stack container to know
    ** if "lhs" elements are superior than "rhs".
    **
    ** @param lhs stack to compare with "rhs".
    ** @param rhs stack for comparison of "lhs".
    ** @return true if "lhs" is superior, false otherwise.
    */
	template <class T, class Container>
		bool operator> (const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
		{ return (lhs.ct > rhs.ct); }

    /*
    ** @brief Compare stack container to know
    ** if "lhs" elements are superior or equal than "rhs".
    **
    ** @param lhs stack to compare with "rhs".
    ** @param rhs stack for comparison of "lhs".
    ** @return true if "lhs" is superior or equal, false otherwise.
    */
	template <class T, class Container>
		bool operator>= (const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
		{ return (lhs.ct >= rhs.ct); }	
}

#endif