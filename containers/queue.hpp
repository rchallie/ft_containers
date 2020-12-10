/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchallie <rchallie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 12:15:32 by rchallie          #+#    #+#             */
/*   Updated: 2020/12/10 21:35:11 by rchallie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_HPP
# define QUEUE_HPP

# include "deque.hpp"

namespace ft
{
	template <class T, class Container = ft::deque<T> > class queue
	{
		public:

			/*
			** The first template parameter (T)
			*/
			typedef T			value_type;

			/*
			** The second template parameter (container)
			** It's the type of underlying container object.
			*/
			typedef Container	container_type;

			/*
			** The size type (usually size_t)
			*/
			typedef size_t		size_type;

			/*
			** Default constructor.
			** Construct an empty queue container adaptor object.
			**
			** @param Container object, is the type of the
			** underlying container type.
			*/
			explicit queue (const container_type& ctnr = container_type())
			:
				ct(ctnr)
			{}

			/*
			** @brief Destroy the container object.
			** Detroy all elements in the container.
			** Use the destructor of the underlying containter object.
			*/
			~queue()
			{}

			/*
			** @brief Call member "empty()" of the underlying
			** container object.
			**
			** @return true if the container is empty, otherwise
			** false.
			*/
			bool empty() const { return (ct.empty()); }

			/*
			** @brief Call member "size()" of the underlying
			** container object.
			**
			** @return the size of the container. (Number of elements
			** in it).
			*/
			size_type size() const { return (ct.size()); }

			/*
			** @brief Give a reference to the oldest element in the
			** queue. It's the same element that is popped
			** out when member "pop()" is called.
			**
			** @return the reference.
			*/
			value_type& front() { return (ct.front()); }

			/*
			** @brief Give a constant reference to the oldest element
			** in the queue. It's the same element that is popped
			** out when member "pop()" is called.
			**
			** @return the const reference.
			*/
			const value_type& front() const { return (ct.front()); }

			/*
			** @brief Give a reference to the last
			** element inserted in the container.
			** Call member "back()" of the underlying container
			** object.
			**
			** @return a reference to the last element in the queue.
			*/
			value_type& back() { return (ct.back()); }
			
			/*
			** @brief Give a constant reference to the last
			** element inserted in the container.
			** Call member "back()" of the underlying container
			** object.
			**
			** @return a constant reference to the last element in the queue.
			*/
			const value_type& back() const { return (ct.back()); }

			/*
			** @brief insert a new element at the end of the
			** queue. The element is a copy of value parameter.
			** Call member "push_back()" of the underlying container
			** object.
			**
			** @param val the value to insert.
			*/
			void push (const value_type& val) { ct.push_back(val); }

			/*
			** @brief Remove the element is the oldest element on the queue.
			** Call the member "pop_back()" of the underlying container
			** object.
			*/
			void pop () { ct.pop_front(); }

			/*
			** @brief Declarations of prototypes for the
			** non members functions that needs to access
			** the protected variable.
			*/

			template <class Tn, class ContainerN>
				friend bool operator== (const ft::queue<Tn, ContainerN>& lhs, const ft::queue<Tn, ContainerN>& rhs);

			template <class Tn, class ContainerN>
				friend bool operator!= (const ft::queue<Tn, ContainerN>& lhs, const ft::queue<Tn, ContainerN>& rhs);
			
			template <class Tn, class ContainerN>
				friend bool operator< (const ft::queue<Tn, ContainerN>& lhs, const ft::queue<Tn, ContainerN>& rhs);

			template <class Tn, class ContainerN>
				friend bool operator<= (const ft::queue<Tn, ContainerN>& lhs, const ft::queue<Tn, ContainerN>& rhs);

			template <class Tn, class ContainerN>
				friend bool operator> (const ft::queue<Tn, ContainerN>& lhs, const ft::queue<Tn, ContainerN>& rhs);

			template <class Tn, class ContainerN>
				friend bool operator>= (const ft::queue<Tn, ContainerN>& lhs, const ft::queue<Tn, ContainerN>& rhs);

		protected:
			container_type ct;
	};

	// Each of the operator call the same operator of the
	// underlying container objects.

    /*
    ** @brief Compare queue container to know
    ** if they are different. Equivalent to !(lsh == rhs).
    **
    ** @param lhs queue to compare with "rhs".
    ** @param rhs queue for comparison of "lhs".
    ** @return true if they are different, false otherwise.
    */
	template <class T, class Container>
		bool operator== (const ft::queue<T, Container>& lhs, const ft::queue<T, Container>& rhs)
		{ return (lhs.ct == rhs.ct); }

    /*
    ** @brief Compare queue container to know
    ** if they are different. Equivalent to !(lsh == rhs).
    **
    ** @param lhs queue to compare with "rhs".
    ** @param rhs queue for comparison of "lhs".
    ** @return true if they are different, false otherwise.
    */
	template <class T, class Container>
		bool operator!= (const ft::queue<T, Container>& lhs, const ft::queue<T, Container>& rhs)
		{ return (lhs.ct != rhs.ct); }

    /*
    ** @brief Compare queue container to know
    ** if "lhs" elements are less than "rhs".
    **
    ** @param lhs queue to compare with "rhs".
    ** @param rhs queue for comparison of "lhs".
    ** @return true if "lhs" is less, false otherwise.
    */
	template <class T, class Container>
		bool operator< (const ft::queue<T, Container>& lhs, const ft::queue<T, Container>& rhs)
		{ return (lhs.ct < rhs.ct); }

    /*
    ** @brief Compare queue container to know
    ** if "lhs" elements are less or equal than "rhs".
    **
    ** @param lhs queue to compare with "rhs".
    ** @param rhs queue for comparison of "lhs".
    ** @return true if "lhs" is less of equal, false otherwise.
    */
	template <class T, class Container>
		bool operator<= (const ft::queue<T, Container>& lhs, const ft::queue<T, Container>& rhs)
		{ return (lhs.ct <= rhs.ct); }	
	
    /*
    ** @brief Compare queue container to know
    ** if "lhs" elements are superior than "rhs".
    **
    ** @param lhs queue to compare with "rhs".
    ** @param rhs queue for comparison of "lhs".
    ** @return true if "lhs" is superior, false otherwise.
    */
	template <class T, class Container>
		bool operator> (const ft::queue<T, Container>& lhs, const ft::queue<T, Container>& rhs)
		{ return (lhs.ct > rhs.ct); }

    /*
    ** @brief Compare queue container to know
    ** if "lhs" elements are superior or equal than "rhs".
    **
    ** @param lhs queue to compare with "rhs".
    ** @param rhs queue for comparison of "lhs".
    ** @return true if "lhs" is superior or equal, false otherwise.
    */
	template <class T, class Container>
		bool operator>= (const ft::queue<T, Container>& lhs, const ft::queue<T, Container>& rhs)
		{ return (lhs.ct >= rhs.ct); }	
}

#endif