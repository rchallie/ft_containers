/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchallie <rchallie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 22:01:32 by rchallie          #+#    #+#             */
/*   Updated: 2020/12/06 01:47:13 by rchallie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Documentation :
** (en) https://en.wikipedia.org/wiki/Doubly_linked_list
*/

#ifndef LIST_HPP
#define LIST_HPP

# include "./utils/utils.hpp"
# include "./utils/list_iterator.hpp"

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
			typedef ft::List_Iterator<T>  iterator;

			/*
			** A bidirectional iterator to const value_type
			** That can read element stored.
			*/
			typedef ft::List_Iterator<const T> const_iterator;

			/*
			** ft::reverse_iterator<iterator>
			** That can read or modify any element in a reversed container.
			** Used to iterate through the container in reverse.
			*/
			typedef ft::reverse_iterator<iterator> reverse_iterator;

			/*
			** ft::reverse_iterator<const_iterator>
			** That can read any element in a reversed the container.
			** Can't be used to modify, used to iterate through the
			** the container in reverse.
			*/
			typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

			/*
			** A signed integral type:
			** Usually the same as ptrdiff_t.
			** Can represent the difference between iterators to the
			** element actually stored.
			** Can be described as te number of element between two pointers.
			** (Pointer to an element contains its address).
			*/
			typedef typename iterator_traits<iterator>::difference_type difference_type;

			/*
			** An unsigned integral type that can represent any
			** non-negative value of difference_type
			** Usually the same as size_t.
			*/
			typedef size_t  size_type;

			explicit list (const allocator_type& alloc = allocator_type())
			:
				_alloc(alloc)
			{
				_last_node = _node_alloc.allocate(1);
				_node_alloc.construct(_last_node, Doubly_Linked_Node<T>());
				_last_node->prev = _last_node;
				_last_node->next = _last_node;
			}

			explicit list (size_type n, const value_type& val = value_type(),
											const allocator_type& alloc = allocator_type())
			:
				_alloc(alloc)
			{
				_last_node = _node_alloc.allocate(1);
				_node_alloc.construct(_last_node, Doubly_Linked_Node<T>());
				_last_node->prev = _last_node;
				_last_node->next = _last_node;
				this->insert(end(), n, val);
			}

			template <class InputIterator>
					list (InputIterator first, InputIterator last,
					const allocator_type& alloc = allocator_type(),
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = u_nullptr)
			:
				_alloc(alloc)
			{
				bool is_valid;
                if (!(is_valid = ft::is_input_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category >::value))
                    throw (ft::InvalidIteratorException<typename ft::is_input_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category >::type>());

				_last_node = _node_alloc.allocate(1);
				_node_alloc.construct(_last_node, Doubly_Linked_Node<T>());
				_last_node->prev = _last_node;
				_last_node->next = _last_node;
				this->insert(end(), first, last);
			}


			list (const list& x);

			~list()
			{
				this->clear();
				_node_alloc.destroy(_last_node);
				_node_alloc.deallocate(_last_node, 1);
			}

			list& operator= (const list & x);

            /*
            ** @brief Return an iterator pointing on the first element
            ** in the container. If the container is empty, the
            ** returned iterator value shall no be dereferenced.
            ** The iterator is of type iterator (bidirectional iterator
            ** on value_type reference).
            **
            ** @return The iterator to the first element.
            */
			iterator begin() { return (iterator(_last_node->next)); }

            /*
            ** @brief Return an iterator pointing on the first element
            ** in the container. If the container is empty, the
            ** returned iterator value shall no be dereferenced.
            ** The iterator is of type const_iterator (bidirectional
            ** iterator on const value_type reference).
            **
            ** @return The iterator to the first element.
            */
			const_iterator begin() const { return (const_iterator(reinterpret_cast<Doubly_Linked_Node<const int> *>(_last_node->next))); }

            /*
            ** @brief Return an iterator pointing on the past-the-end element
            ** in the container. Past-the-end is the theorical element
            ** following the last element in the container. If the container is
            ** empty, return the same than begin.
            ** The iterator is of type iterator (bidirectional iterator
            ** on value_type reference).
            **
            ** @return The iterator to the past-the-end element or begin if
            ** the container is empty.
            */
			iterator end() { return (iterator(_last_node)); }

            /*
            ** @brief Return an iterator pointing on the past-the-end element
            ** in the container. Past-the-end is the theorical element
            ** following the last element in the container. If the container is
            ** empty, return the same than begin.
            ** The iterator is of type const_iterator (bidirectional
            ** iterator on const value_type reference).
            **
            ** @return The iterator to the past-the-end element or begin if
            ** the container is empty.
            */
			const_iterator end() const { return (const_iterator(reinterpret_cast<Doubly_Linked_Node<const int> *>(_last_node))); }

            /*
            ** @brief Give a reverse iterator pointing to the last element
            ** in the container (this->end() - 1).
            ** This is a reversed bidirectional iterator.
            **
            ** @return A reverse Iterator to the reverse beginning of the.
            */
			reverse_iterator rbegin() { return (reverse_iterator(end())); }

            /*
            ** @brief Give a const reverse iterator pointing to the last 
            ** element in the container (this->end() - 1).
            ** This is a constant reversed bidirectional iterator.
            **
            ** @return A const reverse Iterator to the reverse beginning of the.
            */
			const_reverse_iterator rbegin() const { return (const_reverse_iterator(end())); }

            /*
            ** @brief Give a reverse iterator point to the
            ** theorical element preceding the first element
            ** in the container.
            **
            ** @return the reverse iterator.
            */
			reverse_iterator rend() { return (reverse_iterator(begin())); }

            /*
            ** @brief Give a const reverse iterator point to the
            ** theorical element preceding the first element
            ** in the container. 
            **
            ** @return the const reverse iterator.
            */
			const_reverse_iterator rend() const { return (reverse_iterator(begin())); }

            /*
            ** @brief Returns whether the container is empty.
            ** Does not modify container in any way.
            **
            ** @return true if the container size is 0, false otherwise.
            */
			bool empty() const { return (_last_node->next == _last_node ? true : false); }

			/*
			** @brief return the number of elements
			** in the container.
			**
			** @return the number of elements.
			*/
			size_type size() const { return (_listSize()); }

            /*
            ** @brief Returns the maximum potential number of elements the the
            ** container can hold.
            ** This size is due to known system or library limitations.
            ** The container is not garanteed to have this size, it can
            ** fail a allocation for exemple.
            ** 
            ** Documentation :
            ** https://www.viva64.com/en/a/0050/
            **
            ** @return The maximum potential number of elements the
            ** container can hold.
            ** (An unsigned integral type)
            */
			size_type max_size() const { return node_allocator().max_size(); }

            /*
            ** @brief Return a reference to the first element
            ** of the container. Call this on an empty container
            ** cause undefined behavior.
            **
            ** @return the reference.
            */
			reference front() { return (_last_node->next->data); }

            /*
            ** @brief Return a const reference to the first element
            ** of the container. Call this on an empty container
            ** cause undefined behavior.
            **
            ** @return The const reference.
            */
			const_reference front() const { return (_last_node->next->data); }

            /*
            ** @brief Return a reference to the last element in the container.
            ** If the container is empty, occur undefined behavior.
            **
            ** @return The reference to the last element.
            */
			reference back() { return (_last_node->prev->data); }

            /*
            ** @brief Return a const reference to the last element in the container.
            ** If the container is empty, occur undefined behavior.
            **
            ** @return The const reference to the last element.
            */
			const_reference back() const { return (_last_node->prev->data); }

            /*
            ** @brief Assign values between iterators [first; last]
            ** in the container in the same order. All element held
            ** in the container before the call of this function are
            ** destroyed and replaced by new content.
            **
            ** @param first,last the two iterators were the new
            ** element are.
            */
			template <class InputIterator>
					void assign (InputIterator first, InputIterator last)
			{
				this->clear();
				this->insert(this->end(), first, last);
			}

            /*
            ** @brief Assign new content ("val") to the container
            ** "n" times. All element held
            ** in the container before the call of this function are
            ** destroyed and replaced by new content.
            **
            ** @paran n the number of new elements.
            ** @param val the new element.
            */
			void assign (size_type n, const value_type& val)
			{
				this->clear();
				this->insert(this->end(), n, val);
			}

            /*
            ** @brief Add new element at the beginning of the container.
            ** The content of "val" is copied (moved) to the new element.
            ** 
            ** @param val The value to be copied.
            */
			void push_front (const value_type& val) { _insertBeginning(_createNode(val)); }

            /*
            ** @brief Delete the first element of the container.
            ** Reduce the size of the container of one.
            ** If the container is empty, cause undefined behavior.
            */
			void pop_front() { _delete(_last_node->next); }

            /*
            ** @brief Add new element at the end of the container.
            ** The content of "val" is copied (moved) to the new element.
            ** 
            ** @param val The value to be copied.
            */
			void push_back(const value_type& val) { _insertEnd(_createNode(val)); }

            /*
            ** @brief Delete the last element of the container.
            ** Reduce the size of the container of one.
            ** If the container is empty, cause undefined behavior.
            */
			void pop_back() { _delete(_last_node->prev); }

            /*
            ** @brief Insert an element a the position. Can ecrease de size
            ** of the container. This action add a node to the list.
            **
            ** @param position The position where insert.
            ** @param val The element to insert.
            ** @return An iterator to the new element in the container.
            */
			iterator insert (iterator position, const value_type& val)
			{ return (_insertBefore(position._node, _createNode(val))); }

            /*
            ** @brief Insert an element a the position. Can ecrease de size
            ** of the container. This action add "n" nodes to the list.
            **
            ** @param position The position where insert.
            ** @param val The element to insert.
            ** @return An iterator to the new element in the container.
            */
			void insert (iterator position, size_type n, const value_type& val)
			{
				while (n--)
					_insertBefore(position._node, _createNode(val));
			}

            /*
            ** @brief Insert element in range from ["first" to
            ** "last") at "position". Can increase the size of
            ** the container. Throw if the iterator given is not valid.
            **
            ** @param position the position where insert.
            ** @param first the first element in the range.
            ** @param last the last element in the range.
            */
			template <class InputIterator>
				void insert (iterator position, InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = u_nullptr)
			{
				bool is_valid;
                if (!(is_valid = ft::is_input_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category >::value))
                    throw (ft::InvalidIteratorException<typename ft::is_input_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category >::type>());

				difference_type n = ft::distance(first, last);
				while (n--)
					_insertBefore(position._node, _copyNode((first++)._node));
			}

            /*
            ** @brief Remove element from the container at "position".
            ** Reduce the size of 1;
            **
            ** @param position the iterator pointing to the
            ** element to remove.
            ** @return an iterator to the next element after position. 
            */
			iterator erase (iterator position)
			{
				iterator rtn(position._node->next);
				_delete(position._node);
				return (rtn);
			}

            /*
            ** @brief Remove a range of element.
            ** Reduce the size by the number of element removed.
            ** 
            ** @param first the first element in the range.
            ** @param last the last element in the range.
            ** @return An iterator that point to the first element
            ** after "last".
            */
			iterator erase (iterator first, iterator last)
			{
				iterator rtn(last._node->next);

				while (first != last)
					_delete((first++)._node);

				return (rtn);
			}

            /*
            ** @brief Exchanges the content with "x" content.
            ** "x" is of same type. Elements of "x" are elements
            ** of this container and elements of this are of "x".
            ** All iterators, references, pointer on the swaped
            ** objects stay valid.
            **
            ** @param x the container to swap.
            */
			void swap (list& x)
			{
				if (x == *this)
					return;

				allocator_type 			save_alloc = x._alloc;
				node_allocator			save_node_alloc = x._node_alloc;
				Doubly_Linked_Node<T>	*save_last_node = x._last_node;

				x._alloc = this->_alloc;
				x._node_alloc = this->_node_alloc;
				x._last_node = this->_last_node;

				this->_alloc = save_alloc;
				this->_node_alloc = save_node_alloc;
				this->_last_node = save_last_node;
			}

            /*
            ** @brief Resizes the container so that it contain "n"
            ** element. If "n" is smaller than the actual size
            ** the container is reduced to "n". If it is greater,
            ** val is inserting at the end "n - size()" times.
            **
            ** @param n the new size of the container.
            ** @param val the element to set.
            */
			void resize (size_type n, value_type val = value_type())
			{
				if (this->max_size() - this->size() < n)
                    throw (std::length_error("list::resize"));
				if (n > this->size())
				{
					n -= this->size();
					while (n--)
						this->_insertBefore(_last_node, _createNode(val));
				}
				else
				{
                    while (this->size() > n)
                        this->pop_back();
                }
			}

            /*
            ** @brief Removes (destroy) all elements from the
            ** container. Final size is 0.
            */
			void clear()
			{
				Doubly_Linked_Node<T> *tmp = _last_node->next;
				Doubly_Linked_Node<T> *next_tmp;
				while (tmp != _last_node)
				{
					next_tmp = tmp->next;
					_delete(tmp);
					tmp = next_tmp;
				}
			}

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
				rebind<Doubly_Linked_Node<T> >::other node_allocator;
			typedef typename node_allocator::pointer	_node_pointer;

			allocator_type 			_alloc;
			node_allocator			_node_alloc;
			Doubly_Linked_Node<T>	*_last_node;

			/*
			** @brief Create new node.
			*/
			Doubly_Linked_Node<T> *_createNode(const T& data, Doubly_Linked_Node<T> * prev = u_nullptr, Doubly_Linked_Node<T> * next = u_nullptr)
			{
				Doubly_Linked_Node<T> *new_node = _node_alloc.allocate(1);
				_node_alloc.construct(new_node, Doubly_Linked_Node<T>(data));
				new_node->prev = prev;
				new_node->next = next;
				return (new_node);
			}

			Doubly_Linked_Node<T> *_copyNode(const Doubly_Linked_Node<T> * node)
			{
				Doubly_Linked_Node<T> *new_node = _node_alloc.allocate(1);
				_node_alloc.construct(new_node, Doubly_Linked_Node<T>(node->data));
				new_node->prev = node->prev;
				new_node->next = node->next;
				return (new_node);
			}

			/*
			** @brief Give the list size.
			**
			** @return the list size.
			*/
			size_type _listSize(void) const
			{
				size_type count = 0;
				Doubly_Linked_Node<T> *tmp = _last_node->next;

				while (tmp != _last_node)
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
				if (_last_node->next == _last_node)
				{
					_last_node->next = new_node;
					_last_node->prev = new_node;
					new_node->prev = _last_node;
					new_node->next = _last_node;
				}
				else
					_insertBefore(_last_node->next, new_node);
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
				if (_last_node->next == _last_node)
					_insertBeginning(new_node);
				else
					_insertAfter(_last_node->prev, new_node);
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
			iterator _insertAfter(Doubly_Linked_Node<T> *prev, Doubly_Linked_Node<T> *new_node)
			{
				new_node->prev = prev;
				if (prev->next == _last_node)
				{
					new_node->next = _last_node;
					_last_node->prev = new_node;
				}
				else
				{
					new_node->next = prev->next;
					prev->next->prev = new_node;
				}
				prev->next = new_node;
				return (iterator(prev->next));
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
			iterator _insertBefore(Doubly_Linked_Node<T> *next,  Doubly_Linked_Node<T> *new_node)
			{
				new_node->next = next;
				if (next->prev == _last_node)
				{
					new_node->prev = _last_node;
					_last_node->next = new_node;
				}
				else
				{
					new_node->prev = next->prev;
					next->prev->next = new_node;
				}
				next->prev = new_node;
				return (iterator(next->prev));
			}

			/*
			** @brief Delete an node from the
			** list.
			**
			** @param the node to delete.
			*/
			void _delete(Doubly_Linked_Node<T> *node)
			{
				if (node->prev == _last_node)
					_last_node->next = node->next;
				else
					node->prev->next = node->next;
				if (node->next == _last_node)
					_last_node->prev = node->prev;
				else
					node->next->prev = node->prev;

				_node_alloc.destroy(node);
				_node_alloc.deallocate(node, 1);
			}
	};

    /*
    ** @brief Compare list container to know
    ** if they are equal. Start to check if the size
    ** is different.
    **
    ** @param lhs list to compare with "rhs".
    ** @param rhs list for comparison of "lhs".
    ** @return true if they are equal, false otherwise.
    */
	template <class T, class Alloc>
		bool operator== (const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs)
		{
			if (lhs.size() != rhs.size())
				return (false);
			typename ft::list<T>::const_iterator first1 = lhs.begin();
			typename ft::list<T>::const_iterator first2 = rhs.begin();
			while (first1 != lhs.end())
			{
				if (first2 == rhs.end() || *first1 != *first2)
					return (false);
				++first1;
				++first2;
			}
			return (true);
		}

    /*
    ** @brief Compare list container to know
    ** if they are different. Equivalent to !(lsh == rhs).
    **
    ** @param lhs list to compare with "rhs".
    ** @param rhs list for comparison of "lhs".
    ** @return true if they are different, false otherwise.
    */
	template <class T, class Alloc>
		bool operator!= (const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs)
        {
            return (!(lhs == rhs));
        }

    /*
    ** @brief Compare list container to know
    ** if "lhs" elements are lexicographicalement less than "rhs".
    **
    ** @param lhs list to compare with "rhs".
    ** @param rhs list for comparison of "lhs".
    ** @return true if "lhs" is lexicographicalement less, false otherwise.
    */
	template <class T, class Alloc>
		bool operator<  (const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs)
        {
            return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
        }

    /*
    ** @brief Compare list container to know
    ** if "lhs" elements are lexicographicalement less or equal than "rhs".
    **
    ** @param lhs list to compare with "rhs".
    ** @param rhs list for comparison of "lhs".
    ** @return true if "lhs" is lexicographicalement less or equal, false otherwise.
    */
	template <class T, class Alloc>
		bool operator<= (const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs)
		{
            return (!(rhs < lhs));
		}

    /*
    ** @brief Compare list container to know
    ** if "lhs" elements are lexicographicalement superior than "rhs".
    **
    ** @param lhs list to compare with "rhs".
    ** @param rhs list for comparison of "lhs".
    ** @return true if "lhs" is lexicographicalement superior, false otherwise.
    */
	template <class T, class Alloc>
		bool operator>  (const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs)
		{
            return (rhs < lhs);
		}

    /*
    ** @brief Compare list container to know
    ** if "lhs" elements are lexicographicalement superior or equal than "rhs".
    **
    ** @param lhs list to compare with "rhs".
    ** @param rhs list for comparison of "lhs".
    ** @return true if "lhs" is lexicographicalement superior or equal, false otherwise.
    */
	template <class T, class Alloc>
		bool operator>= (const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs)
		{
            return (!(lhs < rhs));
		}

    /*
    ** @brief Overload of swap (list).
    ** The contents of container are swaped.
    **
    ** @param x, y the containers to swap.
    */
	template <class T, class Alloc>
		void swap (ft::list<T,Alloc>& x, ft::list<T,Alloc>& y)
		{
			x.swap(y);
		}
}


#endif