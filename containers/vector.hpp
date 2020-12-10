/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchallie <rchallie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/18 12:45:54 by excalibur         #+#    #+#             */
/*   Updated: 2020/12/10 21:42:20 by rchallie         ###   ########.fr       */
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
# include <algorithm>
# include <cstddef>
# include <tgmath.h>
# include "./utils/utils.hpp"
# include "./utils/random_access_iterator.hpp"

// =============================================================================

// CLASS DEFINITIONS ===========================================================

namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
	class vector
	{   
		public:

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
			typedef ft::random_access_iterator<value_type>               iterator;

			/*
			** A random access iterator to const value_type
			** That can read element stored.
			*/
			typedef ft::random_access_iterator<const value_type>            const_iterator;
			
			/*
			** ft::reverse_iterator<iterator>
			** That can read or modify any element in a reversed vector.
			** Used to iterate through the vector in reverse.
			*/
			typedef ft::reverse_iterator<iterator>             reverse_iterator;

			/*
			** ft::reverse_iterator<const_iterator>
			** That can read any element in a reversed the vector.
			** Can't be used to modify, used to iterate through the
			** the vector in reverse.
			*/
			typedef ft::reverse_iterator<const_iterator>       const_reverse_iterator;

			/*
			** A signed integral type:
			** Usually the same as ptrdiff_t.
			** Can represent the difference between iterators to the
			** element actually stored.
			** Can be described as te number of element between two pointers.
			** (Pointer to an element contains its address).
			*/
			typedef typename ft::iterator_traits<iterator>::difference_type    difference_type; 

			/*
			** An unsigned integral type that can represent any
			** non-negative value of difference_type
			** Usually the same as size_t.
			*/
			typedef typename allocator_type::size_type          size_type;
			
			// Constructors:
			
			/*
			** @brief Default.
			** Constructs an empty container, with no elements.
			** 
			** @param Allocator object.
			** The container keeps and uses an internal copy of this
			** allocator. It's an alias to the second template parameter.
			** If in template this second argument is not defined,
			** std::allocator will be used.
			*/
			explicit vector (const allocator_type& alloc = allocator_type())
			:
				_alloc(alloc),
				_start(u_nullptr),
				_end(u_nullptr),
				_end_capacity(u_nullptr)
			{}

			/*
			** @brief Fill.
			** Constructs a container with "n" elements.
			** Each element is a copy of val.
			**
			** @param n The number of elements.
			** @param val The element.
			** @param allocator_type Allocator object.
			*/
			explicit vector (size_type n, const value_type& val = value_type(),
				 const allocator_type& alloc = allocator_type())
			:
				_alloc(alloc),
				_start(u_nullptr),
				_end(u_nullptr),
				_end_capacity(u_nullptr)
			{
				_start = _alloc.allocate( n );
				_end_capacity = _start + n;
				_end = _start;
				while (n--)
				{
					_alloc.construct(_end, val);
					_end++;
				}
			}

			/*
			** @brief Range.
			** Constructs a container with as many elements as the
			** range [first,last), with each element constructed from
			** its corresponding element in that range, in the same order.
			** (Adapted to counter the effect of :
			** vector(static_cast<size_type>(first), static_cast<value_type>(last), a))
			**
			** @param first An iterator is the first value in x.
			** @param last An iterator is the last value in x.
			*/
			template <class InputIterator>
					vector (InputIterator first, InputIterator last,
							const allocator_type& alloc = allocator_type(),
							typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = u_nullptr)
			:
				_alloc(alloc)
			{
				bool is_valid;
				if (!(is_valid = ft::is_ft_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category >::value))
					throw (ft::InvalidIteratorException<typename ft::is_ft_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category >::type>());
				
				difference_type n = ft::distance(first, last);
				_start = _alloc.allocate( n );
				_end_capacity = _start + n;
				_end = _start;
				while (n--)
				{
					_alloc.construct(_end, *first++);
					_end++;
				}
			}
			
			/*
			** @brief Copy.
			** Construct a vector, initializing its contents
			** with a copy of each element of "x" elements in 
			** the same order. Use a copy of "x" allocator.
			**
			** @param "x" the vector container to copy.
			*/
			vector (const vector& x)
			:
				_alloc(x._alloc),
				_start(u_nullptr),
				_end(u_nullptr),
				_end_capacity(u_nullptr)
			{
				this->insert(this->begin(), x.begin(), x.end());
			}
			
			/*
			** @brief Destroy the container object.
			** Destroy all elements in the container and deallocate
			** the container capacity.
			*/ 
			~vector()
			{
				this->clear();
				_alloc.deallocate(_start, this->capacity());
			}
						
			/*
			** @brief Assigns contents from "x" to the container.
			** Replace content of this and according size.
			** All elements before the call are destroyed.
			**
			** @param x the container which we inspire.
			** @return *this.
			*/ 
			vector &operator=(const vector& x)
			{
				if (x == *this)
					return (*this);
				this->clear();
				this->insert(this->end(), x.begin(), x.end());
				return (*this);
			}

			// Iterators:

			/*
			** @brief Return an iterator pointing on the first element
			** in the container. If the container is empty, the
			** returned iterator value shall no be dereferenced.
			** The iterator is of type iterator (random access iterator
			** on value_type reference).
			**
			** @return The iterator to the first element.
			*/
			iterator begin() { return (_start); };

			/*
			** @brief Return an iterator pointing on the first element
			** in the container. If the container is empty, the
			** returned iterator value shall no be dereferenced.
			** The iterator is of type const_iterator (random access
			** iterator on const value_type reference).
			**
			** @return The iterator to the first element.
			*/
			const_iterator begin() const { return (_start); }

			/*
			** @brief Return an iterator pointing on the past-the-end element
			** in the vector container. Past-the-end is the theorical element
			** following the last element in the container. If the container is
			** empty, return the same than begin.
			** The iterator is of type iterator (random access iterator
			** on value_type reference).
			**
			** @return The iterator to the past-the-end element or begin if
			** the container is empty.
			*/
			iterator end()
			{
				if (this->empty())
					return (this->begin());
				return (_end);
			}

			/*
			** @brief Return an iterator pointing on the past-the-end element
			** in the vector container. Past-the-end is the theorical element
			** following the last element in the container. If the container is
			** empty, return the same than begin.
			** The iterator is of type const_iterator (random access
			** iterator on const value_type reference).
			**
			** @return The iterator to the past-the-end element or begin if
			** the container is empty.
			*/
			const_iterator end() const
			{
				if (this->empty())
					return (this->begin());
				return (_end);
			}

			/*
			** @brief Give a reverse iterator pointing to the last element
			** in the container (this->end() - 1).
			** This is a reversed random access iterator.
			**
			** @return A reverse Iterator to the reverse beginning of the.
			*/
			reverse_iterator rbegin() { return (reverse_iterator(this->end())); }

			/*
			** @brief Give a const reverse iterator pointing to the last 
			** element in the container (this->end() - 1).
			** This is a constant reversed random access iterator.
			**
			** @return A const reverse Iterator to the reverse beginning of the.
			*/
			const_reverse_iterator rbegin() const { return (reverse_iterator(this->end())); }

			/*
			** @brief Give a reverse iterator point to the
			** theorical element preceding the first element
			** in the container.
			**
			** @return the reverse iterator.
			*/
			reverse_iterator rend() { return (reverse_iterator(this->begin())); }

			/*
			** @brief Give a const reverse iterator point to the
			** theorical element preceding the first element
			** in the container. 
			**
			** @return the const reverse iterator.
			*/
			const_reverse_iterator rend() const { return (reverse_iterator(this->begin())); }

			// Capacity:
			
			/*
			** @brief Returns the number of elements stored.
			** It's not necessarily equal to the storage capacity
			**
			** @return The number of elements in the container.
			** (An unsigned integral type)
			*/
			size_type   size(void) const { return (this->_end - this->_start); }

			/*
			** @brief Returns the maximum potential number of elements the the
			** vector can hold.
			** This size is due to known system or library limitations.
			** The vector is not garanteed to have this size, it can
			** fail a allocation for exemple.
			** 
			** Documentation :
			** https://www.viva64.com/en/a/0050/
			**
			** @return The maximum potential number of elements the
			** container can hold.
			** (An unsigned integral type)
			*/
			size_type   max_size(void) const { return allocator_type().max_size(); }

			/*
			** @brief Resizes the container so that it contain "n"
			** element. If "n" is smaller than the actual size
			** the container is reduced to "n". If it is greater,
			** val is inserting at the end and according capacity
			** to allocation calcul system.
			**
			** @param n the new size of the container.
			** @param val the element to set.
			*/
			void        resize (size_type n, value_type val = value_type())
			{
				if (n > this->max_size())
					throw (std::length_error("vector::resize"));
				else if (n < this->size())
				{
					while (this->size() > n)
					{
						--_end;
						_alloc.destroy(_end);
					}
				}
				else
					this->insert(this->end(), n - this->size(), val);
			}

			/*
			** @brief Return size of allocated storage capacity.
			** Not necessarily equal to vector size. Can be equal
			** or greater, because extra space allocated by the container
			** forecast allocation system.
			**
			** @return The size of currntly allocated storage capacity.
			** The number elements it can hold.
			** (An unsigned integral type)
			*/
			size_type   capacity (void) const { return (this->_end_capacity - this->_start); }

			/*
			** @brief Returns whether the container is empty.
			** Does not modify container in any way.
			**
			** @return true if the container size is 0, false otherwise.
			*/
			bool        empty (void) const { return (size() == 0 ? true : false); }

			/*
			** @brief Request that the vector capacity be at least
			** enougth to contain "n" element.
			** If n is greater that the actual capacity a reallocation
			** can be happen, otherwise nothing happen.
			**
			** @param n the capacity asked.
			*/
			void        reserve (size_type n)
			{
				if (n > this->max_size())
					throw (std::length_error("vector::reserve"));
				else if (n > this->capacity())
				{
					pointer prev_start = _start;
					pointer prev_end = _end;
					size_type prev_size = this->size();
					size_type prev_capacity = this->capacity();
					
					_start = _alloc.allocate( n );
					_end_capacity = _start + n;
					_end = _start;
					while (prev_start != prev_end)
					{
						_alloc.construct(_end, *prev_start);
						_end++;
						prev_start++;
					}
					_alloc.deallocate(prev_start - prev_size, prev_capacity);
				}
			}

			// Element access:

			/*
			** @brief Returns a reference to the element at
			** position n in the vector container.
			** If "n" is out of range that's causes undefined behavior.
			**
			** @param n Position of the element in the container.
			** @return The specified element at "n" position.
			*/
			reference operator[] (size_type n) { return (*(_start + n)); }

			/*
			** @brief Returns a const reference to the element at
			** position n in the vector container.
			** If "n" is out of range that's causes undefined behavior.
			**
			** @param n Position of the element in the container.
			** @return The specified element at "n" position.
			*/
			const_reference operator[] (size_type n) const { return (*(_start + n)); }
			
			/*
			** @brief Returns a reference to the element at
			** position n in the vector container.
			** The main difference between this function and the
			** operator "[]" is that the function throw an
			** std::out_of_range exception if "n" is out of the range of
			** the container.
			**
			** @param n Position of the element in the container.
			** @return The specified element at "n" position.
			*/
			reference at (size_type n)
			{
				checkRange(n);
				return ((*this)[n]);
			}

			/*
			** @brief Returns a const reference to the element at
			** position n in the vector container.
			** The main difference between this function and the
			** operator "[]" is that the function throw an
			** std::out_of_range exception if "n" is out of the range of
			** the container.
			**
			** @param n Position of the element in the container.
			** @return The specified element at "n" position.
			*/
			const_reference at (size_type n) const
			{
				checkRange(n);
				return ((*this)[n]);
			}

			/*
			** @brief Return a reference to the first element
			** of the container. Call this on an empty container
			** cause undefined behavior.
			**
			** @return The reference.
			*/
			reference front () { return (*_start); }

			/*
			** @brief Return a const reference to the first element
			** of the container. Call this on an empty container
			** cause undefined behavior.
			**
			** @return The const reference.
			*/
			const_reference front () const { return (*_start); }
			
			/*
			** @brief Return a reference to the last element in the container.
			** If the container is empty, occur undefined behavior.
			**
			** @return The reference to the last element.
			*/
			reference back () { return (*(_end - 1)); }

			/*
			** @brief Return a const reference to the last element in the container.
			** If the container is empty, occur undefined behavior.
			**
			** @return The const reference to the last element.
			*/
			const_reference back () const { return (*(_end - 1)); }

			// Modifiers:

			/*
			** Range (1)
			** @brief Assigns new contents to the vector, replacing its current
			** contents, add modifying its size accordingly.
			** New elements are contruct from each of the elements in tht
			** range, between first and last, in the same order.
			**
			** @param first the first element in the range.
			** @param last the last element in the range.
			*/
			template <class InputIterator>
				void assign (InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = u_nullptr)
				{
					bool is_valid;
					if (!(is_valid = ft::is_ft_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category>::value))
						throw (ft::InvalidIteratorException<typename ft::is_ft_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category >::type>());
					this->clear();
					size_type dist = ft::distance(first, last);
					if (size_type(_end_capacity - _start) >= dist)
					{
						for(; &(*first) != &(*last); first++, _end++)
							_alloc.construct(_end, *first);
					}
					else
					{
						pointer new_start = pointer();
						pointer new_end = pointer();
						pointer new_end_capacity = pointer();

						new_start = _alloc.allocate(dist);
						new_end = new_start;
						new_end_capacity = new_start + dist;

						for(; &(*first) != &(*last); first++, new_end++)
							_alloc.construct(new_end, *first);
						
						_alloc.deallocate(_start, this->capacity());

						_start = new_start;
						_end = new_end;
						_end_capacity = new_end_capacity;
					}
				}
			
			/*
			** @brief Fill assign.
			** Clear the container, fill it with val "n" times.
			** According size to "n".
			**
			** @param "n" the number of element.
			** @param "val" the value of element.
			*/
			void assign (size_type n, const value_type& val)
			{
				this->clear();
				if (n == 0)
					return ;
				if (size_type(_end_capacity - _start) >= n)
				{
					while (n)
					{
						_alloc.construct(_end++ , val);
						n--;
					}
				}
				else
				{
					_alloc.deallocate(_start, this->capacity());
					_start = _alloc.allocate( n );
					_end = _start;
					_end_capacity = _start + n;
					while (n)
					{
						_alloc.construct(_end++, val);
						n--;
					}
				}
			}

			/*
			** @brief Add new element at the end of the vector.
			** The content of "val" is copied (moved) to the new element.
			** 
			** @param val The value to be copied.
			*/
			void push_back (const value_type& val)
			{                
				if (_end == _end_capacity)
				{
					int next_capacity = (this->size() > 0) ? (int)(this->size() * 2) : 1;
					this->reserve(next_capacity);
				}
				_alloc.construct(_end, val);
				_end++;
			}

			/*
			** @brief Delete the last element of the container.
			** Reduce the size of the vector of one.
			** If the container is empty, cause undefined behavior.
			*/
			void pop_back()
			{
				_alloc.destroy(&this->back());
				_end--;
			}

			/*
			** @brief Insert an element a the position. Can ecrease de size
			** of the container. This action force the container to
			** realocate all the elements that were after "postion"
			** to their new positions.
			**
			** @param position The position where insert.
			** @param val The element to insert.
			** @return An iterator to the new element in the container.
			*/
			iterator insert (iterator position, const value_type& val)
			{
				size_type pos_len = &(*position) - _start;
				if (size_type(_end_capacity - _end) >= this->size() + 1)
				{
					for (size_type i = 0; i < pos_len; i++)
						_alloc.construct(_end - i, *(_end - i - 1));
					_end++;
					_alloc.construct(&(*position), val);
				}
				else
				{
					pointer new_start = pointer();
					pointer new_end = pointer();
					pointer new_end_capacity = pointer();

					int next_capacity = (this->size() * 2 > 0) ? this->size() * 2 : 1; 
					new_start = _alloc.allocate( next_capacity );
					new_end = new_start + this->size() + 1;
					new_end_capacity = new_start + next_capacity;

					for (size_type i = 0; i < pos_len; i++)
						_alloc.construct(new_start + i, *(_start + i));
					_alloc.construct(new_start + pos_len, val);
					for (size_type j = 0; j < this->size() - pos_len; j++)
						_alloc.construct(new_end - j - 1, *(_end - j - 1));

					for (size_type l = 0; l < this->size(); l++)
						_alloc.destroy(_start + l);
					if (_start)
						_alloc.deallocate(_start, this->capacity());
					
					_start = new_start;
					_end = new_end;
					_end_capacity = new_end_capacity;
				}
				return (iterator(_start + pos_len));
			}

			/*
			** @brief Insert an element a "n" amount of time
			** before the specified position. Can ecrease de capacity
			** of the container. This action force the container to
			** realocate all the elements that were after "position"
			** to their new positions.
			**
			** @param position The position where insert.
			** @param n Amout of element to insert.
			** @param val The element to insert.
			*/
			void insert (iterator position, size_type n, const value_type& val)
			{
				if (n == 0)
					return ;
				if (n > this->max_size())
					throw (std::length_error("vector::insert (fill)"));
				size_type pos_len = &(*position) - _start;
				if (size_type(_end_capacity - _end) >= n)
				{
					for (size_type i = 0; i < this->size() - pos_len; i++)
						_alloc.construct(_end - i + (n - 1), *(_end - i - 1));
					_end += n;
					while (n)
					{
						_alloc.construct(&(*position) + (n - 1), val);
						n--;
					}
				}
				else
				{
					pointer new_start = pointer();
					pointer new_end = pointer();
					pointer new_end_capacity = pointer();
					
					int next_capacity = (this->capacity() > 0) ? (int)(this->size() * 2) : 1;
					new_start = _alloc.allocate(next_capacity);
					new_end_capacity = new_start + next_capacity;

					if (size_type(new_end_capacity - new_start) < this->size() + n)
					{
						if (new_start)
							_alloc.deallocate(new_start, new_start - new_end_capacity);
						next_capacity = this->size() + n;
						new_start = _alloc.allocate(next_capacity);
						new_end = new_start + this->size() + n;
						new_end_capacity = new_start + next_capacity;
					}

					new_end = new_start + this->size() + n;

					for (int i = 0; i < (&(*position) - _start); i++)
						_alloc.construct(new_start + i, *(_start + i));
					for (size_type k = 0; k < n; k++)
						_alloc.construct(new_start + pos_len + k, val);
					for (size_type j = 0; j < (this->size() - pos_len); j++)
						_alloc.construct(new_end - j - 1, *(_end - j - 1));

					for (size_type u = 0; u < this->size(); u++)
						_alloc.destroy(_start + u);
					_alloc.deallocate(_start, this->capacity());

					_start = new_start;
					_end = new_end;
					_end_capacity = new_end_capacity;
				}
			}

			/*
			** @brief Insert element in range from ["first" to
			** "last") at "position". Can increase the capacity of
			** the container. Throw if the iterator given is not valid.
			** Reallocate all elements after the dist between first and last.
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
				if (!(is_valid = ft::is_ft_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category >::value))
					throw (ft::InvalidIteratorException<typename ft::is_ft_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category >::type>());
				
				size_type dist = ft::distance(first, last);
				if (size_type(_end_capacity - _end) >= dist)
				{
					for(size_type i = 0; i < this->size() - (&(*position) - _start); i++)
						_alloc.construct(_end - i + (dist - 1), *(_end - i - 1));
					_end += dist;
					for (; &(*first) != &(*last); first++, position++)
						_alloc.construct(&(*position), *first);
				}
				else
				{
					pointer new_start = pointer();
					pointer new_end = pointer();
					pointer new_end_capacity = pointer();

					new_start = _alloc.allocate( this->size() * 2 );
					new_end = new_start + this->size() + dist;
					new_end_capacity = new_start + ( this->size() * 2 );

					if (size_type(new_end_capacity - new_start) < this->size() + dist)
					{
						if (new_start)
							_alloc.deallocate(new_start, new_end_capacity - new_start);
						new_start = _alloc.allocate (this->size() + dist);
						new_end = new_start + this->size() + dist;
						new_end_capacity = new_end;
					}

					for (int i = 0; i < &(*position) - _start; i++)
						_alloc.construct(new_start + i, *(_start + i));
					for (int j = 0; &(*first) != &(*last); first++, j++)
						_alloc.construct(new_start + (&(*position) - _start) + j, *first);
					for (size_type k = 0; k < this->size() - (&(*position) - _start); k++)
						_alloc.construct(new_start + (&(*position) - _start) + dist + k, *(_start + (&(*position) - _start) + k));

					for (size_type l = 0; l < this->size(); l++)
						_alloc.destroy(_start + l);
					_alloc.deallocate(_start, this->capacity());

					_start = new_start;
					_end = new_end;
					_end_capacity = new_end_capacity;
				}
			}

			/*
			** @brief Remove element from the vector at "position".
			** Reduce the size of 1;
			**
			** @param position the iterator pointing to the
			** element to remove.
			** @return a pointer to the element a "&(*position) + 1"; 
			*/
			iterator erase (iterator position)
			{
				pointer p_pos = &(*position);
				_alloc.destroy(&(*position));
				if (&(*position) + 1 == _end)
					_alloc.destroy(&(*position));
				else
				{
					for (int i = 0; i < _end - &(*position) - 1; i++)
					{
						_alloc.construct(&(*position) + i, *(&(*position) + i + 1));
						_alloc.destroy(&(*position) + i + 1);
					}
				}
				_end -= 1;
				return (iterator(p_pos));
			}

			/*
			** @brief Remove element from the vector a range of element.
			** Reduce the size by the number of element removed.
			** 
			** @param first the first element in the range.
			** @param last the last element in the range.
			** @return An iterator that point to the first element
			** after "last".
			*/
			iterator erase (iterator first, iterator last)
			{
				pointer p_first = &(*first);
				for (; &(*first) != &(*last); first++)
					_alloc.destroy(&(*first));
				for (int i = 0; i < _end - &(*last); i++)
				{
					_alloc.construct(p_first + i, *(&(*last) + i));
					_alloc.destroy(&(*last) + i);
				}
				_end -= (&(*last) - p_first);
				return (iterator(p_first));
			}

			/*
			** @brief Exchanges the content with "x" content.
			** "x" is of same type. Elements of "x" are elements
			** of this container and elements of this are of "x".
			** All iterators, references, pointer on the swaped
			** objects stay valid.
			**
			** @param x the vector to swap.
			*/
			void swap (vector& x)
			{
				if (x == *this)
					return;
				
				pointer save_start = x._start;
				pointer save_end = x._end;
				pointer save_end_capacity = x._end_capacity;
				allocator_type save_alloc = x._alloc;

				x._start = this->_start;
				x._end = this->_end;
				x._end_capacity = this->_end_capacity;
				x._alloc = this->_alloc;

				this->_start = save_start;
				this->_end = save_end;
				this->_end_capacity = save_end_capacity;
				this->_alloc = save_alloc;
			}

			/*
			** @brief Removes (destroy) all elements from the
			** container. Final size is 0.
			*/
			void clear()
			{
				size_type save_size = this->size();
				for (size_type i = 0; i < save_size; i++)
				{
					_end--;
					_alloc.destroy(_end);
				}
			}

		private:
			allocator_type  _alloc;
			pointer         _start;
			pointer         _end;
			pointer         _end_capacity;

			/*
			** @brief Check if "n" is in the range of the container.
			** If "n" is out of range that's throw an std::out_of_range
			** exception.
			**
			** @param n The position of the element to check.
			*/
			void checkRange(const size_type& n) const
			{
				if (n >= this->size())
					throw (std::out_of_range("vector::checkRange: n (which is "
							+ ft::to_string(n) + ") >= this->size() (which is "
							+ ft::to_string(this->size()) + ")"));
			}
	};

	// Non-member function overloads
	
	/*
	** @brief Compare vector container to know
	** if they are equal. Start to check if the size
	** is different.
	**
	** @param lhs vector to compare with "rhs".
	** @param rhs vector for comparison of "lhs".
	** @return true if they are equal, false otherwise.
	*/
	template <class T, class Alloc>
		bool operator== (const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
		{
			if (lhs.size() != rhs.size())
				return (false);
			typename ft::vector<T>::const_iterator first1 = lhs.begin();
			typename ft::vector<T>::const_iterator first2 = rhs.begin();
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
	** @brief Compare vector container to know
	** if they are different. Equivalent to !(lsh == rhs).
	**
	** @param lhs vector to compare with "rhs".
	** @param rhs vector for comparison of "lhs".
	** @return true if they are different, false otherwise.
	*/
	template <class T, class Alloc>
		bool operator!= (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
		{
			return (!(lhs == rhs));
		}
	
	/*
	** @brief Compare vector container to know
	** if "lhs" elements are lexicographicalement less than "rhs".
	**
	** @param lhs vector to compare with "rhs".
	** @param rhs vector for comparison of "lhs".
	** @return true if "lhs" is lexicographicalement less, false otherwise.
	*/
	template <class T, class Alloc>
		bool operator<  (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
		{
			return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		}

	/*
	** @brief Compare vector container to know
	** if "lhs" elements are lexicographicalement less or equal than "rhs".
	**
	** @param lhs vector to compare with "rhs".
	** @param rhs vector for comparison of "lhs".
	** @return true if "lhs" is lexicographicalement less or equal, false otherwise.
	*/
	template <class T, class Alloc>
		bool operator<= (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
		{
			return (!(rhs < lhs));
		}

	/*
	** @brief Compare vector container to know
	** if "lhs" elements are lexicographicalement superior than "rhs".
	**
	** @param lhs vector to compare with "rhs".
	** @param rhs vector for comparison of "lhs".
	** @return true if "lhs" is lexicographicalement superior, false otherwise.
	*/
	template <class T, class Alloc>
		bool operator>  (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
		{
			return (rhs < lhs);
		}

	/*
	** @brief Compare vector container to know
	** if "lhs" elements are lexicographicalement superior or equal than "rhs".
	**
	** @param lhs vector to compare with "rhs".
	** @param rhs vector for comparison of "lhs".
	** @return true if "lhs" is lexicographicalement superior or equal, false otherwise.
	*/
	template <class T, class Alloc>
		bool operator>= (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
		{
			return (!(lhs < rhs));
		}
	
	/*
	** @brief Overload of swap (vector).
	** The contents of container are swaped.
	**
	** @param x, y the containers to swap.
	*/
	template <class T, class Alloc>
		void swap (vector<T,Alloc>& x, vector<T,Alloc>&y)
		{
			x.swap(y);
		}
}

// =============================================================================

#endif