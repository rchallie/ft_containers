/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchallie <rchallie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 17:14:11 by rchallie          #+#    #+#             */
/*   Updated: 2020/12/10 21:35:37 by rchallie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

#include "./utils/utils.hpp"
#include "./utils/binary_search_tree.hpp"

namespace ft
{
	template < class Key, class T, class Compare = ft::less<Key>,
				class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		public:

			/*
			** The first template parameter (Key)
			*/
			typedef Key     key_type;

			/*
			** The second template parameter (T)
			*/
			typedef T       mapped_type;

			/*
			** Type of stocked value create with Key and T.
			** pair<Key, T>
			*/
			typedef ft::pair<key_type, mapped_type> value_type;

			/*
			** The third template parameter (Compare)
			*/
			typedef Compare     key_compare;

			/* 
			** Function class to compare elements
			*/
			class value_compare : ft::binary_function<value_type, value_type, bool>
			{
				friend class map<key_type, mapped_type, key_compare, Alloc>;
				
				protected:
					Compare comp;
					value_compare (Compare c) : comp(c) {}
				
				public:

					/* 
					** Result type, first argument type and second argument type are
					** stocked int binary_function.
					*/

					/*
					** @brief Call the compare function to compare
					** "x" and "y".
					**
					** @param x,y values to compare.
					** @return boolean from comparison function.
					*/
					bool operator() (const value_type& x, const value_type& y) const
					{ return (comp(x.first, y.first)); }
			};

			/*
			** The fourth template parameter (Alloc)
			*/
			typedef Alloc  allocator_type;

			/*
			** allocator_type::reference
			** A type provides a reference to an element stored in
			** the container.
			** For the default allocator is a reference to value_type
			** (value_type&)
			*/
			typedef typename allocator_type::reference   reference;

			/*
			** allocator_type::const_reference
			** Type that give a reference to a const element stored.
			** Usefull to read and perform const operator.
			** A type const_reference can't be used to modify the value
			** of an element.
			** For the default allocator is a const reference to value_type
			** (const value_type&)
			*/
			typedef typename allocator_type::const_reference const_reference;

			/*
			** allocator_type::pointer
			** Type that give a pointer to an element stored.
			** A type pointer can be used to modify the value of
			** an element.
			** For the default allocator is a pointer to value_type
			** (value_type*)
			*/
			typedef typename allocator_type::pointer     pointer;

			/*
			** allocator_type::const_pointer
			** Type that give a const pointer to an element stored.
			** Can't be used to modify the value of an element.
			** An iterator is prefered to access to an element.
			** For the default allocator is a const pointer to value_type
			** (const value_type*)
			*/
			typedef typename allocator_type::const_pointer const_pointer;

			/*
			** A bidirectional iterator to value_type
			** That can read or modify any element stored.
			** Convertible to const_iterator;
			*/
			typedef typename ft::Binary_search_tree<value_type, key_compare>::iterator iterator;

			/*
			** A bidirectional iterator to const value_type
			** That can read element stored.
			*/
			typedef typename ft::Binary_search_tree<value_type, key_compare>::const_iterator const_iterator;

			/*
			** ft::reverse_iterator<iterator>
			** That can read or modify any element in a reversed container.
			** Used to iterate through the container in reverse.
			*/
			typedef typename ft::reverse_iterator<iterator>    reverse_iterator;

			/*
			** ft::reverse_iterator<const_iterator>
			** That can read any element in a reversed the container.
			** Can't be used to modify, used to iterate through the
			** the container in reverse.
			*/
			typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;
		
			/*
			** A signed integral type:
			** Usually the same as ptrdiff_t.
			** Can represent the difference between iterators to the
			** element actually stored.
			** Can be described as the number of element between two pointers.
			** (Pointer to an element contains its address).
			*/
			typedef typename ft::iterator_traits<iterator>::difference_type difference_type;

			/*
			** An unsigned integral type that can represent any
			** non-negative value of difference_type
			** Usually the same as size_t.
			*/
			typedef size_t size_type;

			/*
			** @brief Default :
			** Construct an empty map container object.
			**
			** @param alloc the Allocator type.
			*/
			explicit map (const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
			:
				_alloc(alloc),
				_comp(comp),
				_bst()
			{}

			/*
			** @brief Iterator:
			** Construct a list container, of size last-first containing
			** value of [first, last).
			**
			** @param first,last the range of content.
			** @param alloc the allocator type.
			*/
			template <class InputIterator>
				map (InputIterator first, InputIterator last,
					const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type(),
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = u_nullptr)
			:	
				_alloc(alloc),
				_comp(comp),
				_bst()
			{
				bool is_valid;
				if (!(is_valid = ft::is_input_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category >::value))
					throw (ft::InvalidIteratorException<typename ft::is_input_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category >::type>());
				this->insert(first, last);
			}
			
			/*
			** @brief Copy :
			** Construct the container to be a copy of "x".
			**
			** @param x the lsit to copy.
			*/
			map(const map& x)
			:
				_alloc(x._alloc),
				_comp(x._comp),
				_bst()
			{
				this->insert(x.begin(), x.end());
			}

			/*
			** @brief Destructor:
			** Clear the container and deallocate everythings.
			*/
			~map()
			{ this->clear(); }

			/*
			** @brief Assign "x" to this.
			**
			** @param x the list where get elements.
			** @return this list.
			*/
			map& operator= (const map& x)
			{
				if (&x == this)
					return (*this);
				this->clear();
				this->insert(x.begin(), x.end());
				return (*this);
			}

			/*
			** @brief Return an iterator pointing on the first element
			** in the container. If the container is empty, the
			** returned iterator value shall no be dereferenced.
			** The iterator is of type iterator (bidirectional iterator
			** on value_type reference).
			**
			** @return The iterator to the first element.
			*/
			iterator begin()
			{ return (iterator(_bst._last_node->left, _bst._last_node)); }

			/*
			** @brief Return a const iterator pointing on the first element
			** in the container. If the container is empty, the
			** returned iterator value shall no be dereferenced.
			** The iterator is of type const_iterator (bidirectional
			** iterator on const value_type reference).
			**
			** @return The const iterator to the first element.
			*/
			const_iterator begin() const
			{ return (const_iterator(_bst._last_node->left, _bst._last_node)); }

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
			iterator end()
			{ return (iterator(_bst._last_node, _bst._last_node)); }

			/*
			** @brief Return a const iterator pointing on the past-the-end element
			** in the container. Past-the-end is the theorical element
			** following the last element in the container. If the container is
			** empty, return the same than begin.
			** The iterator is of type const_iterator (bidirectional
			** iterator on const value_type reference).
			**
			** @return The const iterator to the past-the-end element or begin if
			** the container is empty.
			*/
			const_iterator end() const
			{ return (const_iterator(_bst._last_node, _bst._last_node)); }

			/*
			** @brief Give a reverse iterator pointing to the last element
			** in the container (this->end() - 1).
			** This is a reversed bidirectional iterator.
			**
			** @return A reverse Iterator to the reverse beginning of the container.
			*/
			reverse_iterator rbegin()
			{ return (reverse_iterator(this->end())); }

			/*
			** @brief Give a const reverse iterator pointing to the last 
			** element in the container (this->end() - 1).
			** This is a constant reversed bidirectional iterator.
			**
			** @return A const reverse Iterator to the reverse beginning of the container.
			*/
			const_reverse_iterator rbegin() const
			{ return (const_reverse_iterator(this->end())); }

			/*
			** @brief Give a reverse iterator point to the
			** theorical element preceding the first element
			** in the container.
			**
			** @return the reverse iterator.
			*/
			reverse_iterator rend()
			{ return (reverse_iterator(this->begin())); }

			/*
			** @brief Give a const reverse iterator point to the
			** theorical element preceding the first element
			** in the container. 
			**
			** @return the const reverse iterator.
			*/
			const_reverse_iterator rend() const
			{ return (const_reverse_iterator(this->begin())); }

			/*
			** @brief Returns whether the container is empty.
			** Does not modify container in any way.
			**
			** @return true if the container size is 0, false otherwise.
			*/
			bool empty() const
			{ return (_bst._last_node->parent == _bst._last_node); }

			/*
			** @brief return the number of elements
			** in the container.
			**
			** @return the number of elements.
			*/
			size_type size() const
			{ return (_bst._last_node->value.first); }

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
			size_type max_size() const
			{ return (_bst.max_size()); }

			/*
			** @brief If "k" match with the key of an
			** element in the container, this will return 
			** the mapped value from this element. If "k" doesn't
			** match, this will insert a new element with "k" like
			** key and a mapped value initialized.
			**
			** @param k the key.
			** @return an reference to the mapped value.
			*/
			mapped_type& operator[] (const key_type& k)
			{
				iterator tmp = this->find(k);

				if (tmp == this->end())
					this->insert(ft::make_pair(k, mapped_type()));
				tmp = this->find(k);
				return ((*tmp).second);
			} 

			/*
			** @brief Insert a "value_type" (pair) in the container.
			** Can increase the container size.
			**
			** @param val the pair to add to the container.
			** @return An pair containing in key the iterator
			** position of the inserted value and contain
			** a bool at true if a new element was inserted
			** or false if an equivalent key already exist, on value.
			*/
			pair<iterator,bool> insert (const value_type& val)
			{ return (_bst.insertPair(val)); }

			/*
			** @brief Use "position" like an hint to know
			** where "val" can be insert. Like this information
			** can be wrong and that the allocation system is
			** based on a strict stoage, "position" is not used.
			**
			** @param position hint.
			** @param val the pair to insert in the container.
			** @return an iterator pointing to the newly inserted
			** value or to the already existed value.
			*/
			iterator insert (iterator position, const value_type& val)
			{
				(void)position;
				return (_bst.insertPair(val).first);
			}

			/*
			** @brief Insert element in range from ["first" to
			** "last"). Can increase the size of
			** the container. Throw if the iterator given is not valid.
			**
			** @param first the first element in the range.
			** @param last the last element in the range.
			*/
			template <class InputIterator>
				void insert (InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = u_nullptr)
			{
				bool is_valid;
				if (!(is_valid = ft::is_input_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category >::value))
					throw (ft::InvalidIteratorException<typename ft::is_input_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category >::type>());

				difference_type n = ft::distance(first, last);
				while (n--)
					this->insert(*(first++));
			}

			/*
			** @brief Remove the element in the container at the iterator
			** position. Reduce the size of the container.
			**
			** @param position the iterator pointing to the element to remove.
			*/
			void erase (iterator position)
			{ this->erase((*position).first); }

			/*
			** @brief Remove the element in the container that has like key
			** "k". Reduce the size of the container.
			**
			** @param k the key.
			** @return The number of element removed, 0 if no element have "k"
			** like key, 1 otherwise.
			*/
			size_type erase (const key_type& k)
			{
				if (this->find(k) == this->end())
					return (0);
				_bst.removeByKey(ft::make_pair(k, mapped_type()));
				return (1);
			}

			/*
			** @brief Remove a range [first, last) element of the container.
			** The container size is reduced by the number of element
			** int the range.
			**
			** @param first,last the range.
			*/
			void erase (iterator first, iterator last)
			{
				while (first != last)
					this->erase((*(first++)).first);
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
			void swap (map& x)
			{ _bst.swap(x._bst); }

			/*
			** @brief Removes (destroy) & deallocate
			** all elements from the container. Final size is 0.
			*/
			void clear()
			{ this->erase(this->begin(), this->end()); }

			/*
			** @brief Return a copy of the key comparison object.
			**
			** @param the key comparison object.
			*/
			key_compare key_comp() const
			{ return (key_compare()); }

			/*
			** @brief Return a copy of the value comparison object.
			**
			** @param the value comparison object.
			*/
			value_compare value_comp() const
			{ return (value_compare(key_compare())); }

			/*
			** @brief Search in the container to find the pair
			** that have like key "k".
			**
			** @param k the key to find.
			** @return an iterator pointing to the pair object that
			** have like key "k". 
			*/
			iterator find (const key_type& k)
			{ return (iterator(_bst.searchByKey(ft::make_pair(k, mapped_type())), _bst._last_node)); }

			/*
			** @brief Search in the container to find the pair
			** that have like key "k".
			**
			** @param k the key to find.
			** @return an const iterator pointing to the pair object that
			** have like key "k". 
			*/
			const_iterator find (const key_type& k) const
			{ return (const_iterator(_bst.searchByKey(ft::make_pair(k, mapped_type())), _bst._last_node)); }

			/*
			** @brief Search in the countair if an element
			** has "k" like key.
			**
			** @param k the key to find.
			** @return 1 if the container have an element
			** with k like key, 0 otherwise.
			*/
			size_type count (const key_type& k) const
			{
				const_iterator beg = this->begin();
				const_iterator end = this->end();

				while (beg != end)
					if ((*(beg++)).first == k)
						return (1);
				return (0);
			}

			/*
			** @brief Return a iterator pointing to the first element
			** in the container who have a key that is not
			** concidered to go before "k". If an element have "k"
			** like key, give an iterator to it.
			**
			** @param k the key.
			** @return the iterator.
			*/
			iterator lower_bound (const key_type& k)
			{
				iterator beg = this->begin();
				iterator end = this->end();

				while (beg != end)
				{
					if (_comp((*beg).first, k) == false)
						break;
					beg++;
				}
				return (beg);
			}

			/*
			** @brief Return a const iterator pointing to the first element
			** in the container who have a key that is not
			** concidered to go before "k". If an element have "k"
			** like key, give an const iterator to it.
			**
			** @param k the key.
			** @return the iterator.
			*/
			const_iterator lower_bound (const key_type& k) const
			{ return (const_iterator(this->lower_bound(k))); }

			/*
			** @brief return an iterator pointing to the next element
			** whose key is concidered to go after "k".
			**
			** @param k the key.
			** @return the iterator.
			*/
			iterator upper_bound (const key_type& k)
			{
				iterator beg = this->begin();
				iterator end = this->end();

				while (beg != end)
				{
					if (_comp(k, (*beg).first))
						break;
					beg++;
				}
				return (beg);
			}

			/*
			** @brief return an const iterator pointing to the next element
			** whose key is concidered to go after "k".
			**
			** @param k the key.
			** @return the const iterator.
			*/
			const_iterator upper_bound (const key_type& k) const
			{ return (const_iterator(this->upper_bound(k))); }

			/*
			** @brief Return all the element that have "k" like key.
			** Like all element in map are unique, that give a pair
			** that contain two const iterator. The first iterator
			** pointing to the lower bound of "k" and the second pointing
			** to the upper bound of "k".
			**
			** @param k the key.
			** @return the pair containing the two const iterator.
			*/
			ft::pair<const_iterator, const_iterator> equal_range (const key_type& k) const
			{ return (ft::make_pair(this->lower_bound(k), this->upper_bound(k))); }

			/*
			** @brief Return the element that have "k" like key.
			** Like all element in map are unique, that give a pair
			** that contain two iterator. The first iterator
			** pointing to the lower bound of "k" and the second pointing
			** to the upper bound of "k".
			**
			** @param k the key.
			** @return the pair containing the two iterator.
			*/
			ft::pair<iterator, iterator> equal_range (const key_type& k)
			{ return (ft::make_pair(this->lower_bound(k), this->upper_bound(k))); }

		private:

			allocator_type                          _alloc;
			Compare                                 _comp;
			Binary_search_tree<value_type, Compare>  _bst;

	};
}

#endif