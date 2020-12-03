/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchallie <rchallie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 22:01:32 by rchallie          #+#    #+#             */
/*   Updated: 2020/12/04 00:56:08 by rchallie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Documentation :
** (en) https://en.wikipedia.org/wiki/Doubly_linked_list
*/

#ifndef LIST_HPP
#define LIST_HPP

# include "./utils/utils.hpp"

namespace ft
{
	template < class T, class Alloc = std::allocator<T> > class list
	{
		public :

            /*
            ** The first template parameter (T)
            */
			typedef T											value_type;

            /*
            ** The second template parameter (Alloc)
            */
			typedef Alloc   allocator_type;

            /*
            ** allocator_type::reference
            ** A type provides a reference to an element stored in
            ** a list.
            ** For the default allocator is a reference to value_type
            ** (value_type&)
            */
			typedef typename allocator_type::reference   		reference;

            /*
            ** allocator_type::const_reference
            ** Type that give a reference to a const element stored.
            ** Usefull to read and perform const operator.
            ** A type const_reference can't be used to modify the value
            ** of an element.
            ** For the default allocator is a const reference to value_type
            ** (const value_type&)
            */
			typedef typename allocator_type::const_reference 	const_reference;

            /*
            ** allocator_type::pointer
            ** Type that give a pointer to an element stored.
            ** A type pointer can be used to modify the value of
            ** an element.
            ** For the default allocator is a pointer to value_type
            ** (value_type*)
            */
			typedef typename allocator_type::pointer     		pointer;

            /*
            ** allocator_type::const_pointer
            ** Type that give a const pointer to an element stored.
            ** Can't be used to modify the value of an element.
            ** An iterator is prefered to access to an element.
            ** For the default allocator is a const pointer to value_type
            ** (const value_type*)
            */
			typedef typename allocator_type::const_pointer 		const_pointer;

            /*
            ** A bidirectional iterator to value_type
            ** That can read or modify any element stored.
            ** Convertible to const_iterator;
            */
			//typedef ft::List_iterator<T>  iterator;

            /*
            ** A bidirectional iterator to const value_type
            ** That can read element stored.
            */
			//typedef ft::List_iterator<const T> const_iterator;

            /*
            ** ft::reverse_iterator<iterator>
            ** That can read or modify any element in a reversed container.
            ** Used to iterate through the container in reverse.
            */
			//typdef ft::reverse_iterator<iterator> reverse_iterator;

            /*
            ** ft::reverse_iterator<const_iterator>
            ** That can read any element in a reversed the container.
            ** Can't be used to modify, used to iterate through the
            ** the container in reverse.
            */
			//typdef ft::reverse_iterator<const_iterator> const_reverse_iterator;

            /*
            ** A signed integral type:
            ** Usually the same as ptrdiff_t.
            ** Can represent the difference between iterators to the
            ** element actually stored.
            ** Can be described as te number of element between two pointers.
            ** (Pointer to an element contains its address).
            */
			//typedef typename iterator_traits<iterator>::difference_type difference_type;

            /*
            ** An unsigned integral type that can represent any
            ** non-negative value of difference_type
            ** Usually the same as size_t.
            */
			typedef size_t  size_type;

			explicit list (const allocator_type& alloc = allocator_type())
			:
				_alloc(alloc),
				_first_node(u_nullptr),
				_last_node(u_nullptr)
			{}

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

            /*
            ** @brief return the number of elements
            ** in the container.
            **
            ** @return the size.
            */
			size_type size() const
			{ return (_listSize()); }

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

            typedef typename allocator_type::template
				rebind<Doubly_Linked_Node<T>>::other node_allocator;
			typedef typename node_allocator::pointer	_node_pointer;

			Alloc 					_alloc;
			node_allocator			_node_alloc;
			Doubly_Linked_Node<T>	*_first_node;	
			Doubly_Linked_Node<T>	*_last_node;

			/*
			** @brief Create new node.
			*/
			Doubly_Linked_Node<T> *createNode(const T& data, Doubly_Linked_Node<T> * prev = u_nullptr, Doubly_Linked_Node<T> * next = u_nullptr)
			{
				Doubly_Linked_Node<T> *new_node = _node_alloc.allocate(1);
				_node_alloc.construct(new_node, 0);
				new_node->data = data;
				new_node->prev = prev;
				new_node->next = next;
				return (new_node);
			}

			/*
			** @brief Give the list size.
			**
			** @return the list size.
			*/
			size_type _listSize(void)
			{
				size_type count = 0;
				Doubly_Linked_Node<T> tmp = _first_node;

				while (tmp != u_nullptr)
				{
					tmp = tmp->next;
					count++;
				}
				return (count);
			}

			/*
			** @brief insert a doubly linked node to the beginning
			** of the doubly linked list. If the list is empty
			** the first and the last node are set to "new_node".
			** Usefull for possibly empty list.
			**
			** @param new_node the new node.
			*/
			void _insertBeginning(Doubly_Linked_Node<T>	*new_node)
			{
				if (_first_node == u_nullptr)
				{
					_first_node = new_node;
					_last_node = new_node;
					new_node->prev = u_nullptr;
					new_node->next = u_nullptr;
				}
				else
					_insertBefore(_first_node, new_node);
			}

			/*
			** @brief insert a doubly linked node to the end
			** of the doubly linked list. If the list is empty
			** the first and the last node are set to "new_node".
			**
			** @param new_node the new node.
			*/
			void _insertEnd(Doubly_Linked_Node<T>	*new_node)
			{
				if (_last_node == u_nullptr)
					_insertBeginning(new_node);
				else
					_insertAfter(_last_node, new_node);
			}

			/*
			** @brief insert a doubly linked node after "prev".
			** Set "prev" next node to "new_node", "new_node" previous
			** to "prev", and if it's not u_nullptr, set "prev" primary 
			** next to "new_node" next.
			**
			** @param prev the previous node before the new one.
			** @param new_node the new node to insert.
			*/
			void _insertAfter(Doubly_Linked_Node<T> *prev, Doubly_Linked_Node<T> *new_node)
			{
				new_node->prev = prev;
				if (prev->next == u_nullptr)
				{
					new_node->next = u_nullptr;
					_last_node = new_node;
				}
				else
				{
					new_node->next = prev->next;
					prev->next->prev = new_node;
				}
				prev->next = new_node;
			}

			/*
			** @brief insert a doubly linked node previous "next".
			** Set "next" previous node to "new_node", "new_node" next
			** to "next", and if it's not u_nullptr, set "next" primary
			** previous to "new_node" previous.
			**
			** @param next the next node after the new one.
			** @param new_node the new node to insert.
			*/
			void _insertBefore(Doubly_Linked_Node<T> *next,  Doubly_Linked_Node<T> *new_node)
			{
				new_node->next = next;
				if (next->prev == u_nullptr)
				{
					new_node->prev = u_nullptr;
					_first_node = new_node;
				}
				else
				{
					new_node->prev = next->prev;
					next->prev->next = new_node;
				}
				next->prev = new_node;
			}

			void _delete(Doubly_Linked_Node<T> *node)
			{
				if (node->prev == u_nullptr)
					_first_node = node->next;
				else
					_node->prev->next = node->next;
				if (node->next == u_nullptr)
					_last_node = node->prev;
				else
					_node->next->prev = node->prev;

				_node_alloc.destroy(node);
				_node_alloc.deallocate(node, 1);
			}
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