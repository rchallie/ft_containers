/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: excalibur <excalibur@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 18:25:12 by excalibur         #+#    #+#             */
/*   Updated: 2020/06/05 23:03:07 by excalibur        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include <cstddef>
# include <limits>
# include <sstream>
# include <typeinfo>

#  define U_SIZE_MAX std::numeric_limits<size_t>::max()

/*
** @brief Type of the null pointer constant.
** Permetted implicit conversions to null pointer ,
** similary conversions for all type of contant null pointer.
**
** From : (Take a look)
** https://www.amazon.com/dp/0201924889
*/
class nullptr_t
{
    public:
        /*
        ** @brief For conversion to any type
        ** of null non-member pointer.
        */
        template<class T>
        operator T*() const { return (0); }

        /*
        ** @brief For conversion to any type of null
        ** member pointer.
        */
        template<class C, class T>
        operator T C::*() const { return (0); }

    private:
        
        /*
        ** @brief It's imposible to get an address of
        ** a nullptr.
        */
        void operator&() const;

} u_nullptr = {};

namespace ft
{
    /*
    ** @brief Transfom "n" to std::string.
    **
    ** @param n the object to convert. (Sure for
    ** classic number types).
    ** @return Converted "n".
    ** 
    ** Take a look:
    ** http://www.cplusplus.com/articles/D9j2Nwbp/
    */
    template <typename T>
        std::string to_string(T n)
        {
            /* Stream used to convert */
            std::ostringstream ss;
            ss << n;
            return (ss.str());
        }
    
    /*
    ** @brief The type T is enabled as member type enable_if::type
    ** if Cond is true. Otherwise, enable_if::type is not defined.
    ** Usefull when a particular condition is not met, in this case
    ** the member enable_if::type will ne be defined and attempting
    ** to compile using to should fail. (If this is use in template
    ** of a function, for exemple, like the type is not defined the 
    ** compiler will not compile and use the function).
    **
    ** @template_param Cond A compile-time constant of type bool.
    ** @template_param T A type.
    */
    template<bool Cond, class T = void> struct enable_if {};
    template<class T> struct enable_if<true, T> { typedef T type; };

    /*
    ** All the next part is an adaptation of is_integral.
    ** "is_integral" for this project in C++98 is a structure 
    ** that contain if the type given to it is a type from this list :
    **  - bool
    **  - char
    **  - char16_t
    **  - char32_t
    **  - wchar_t
    **  - signed char
    **  - short int
    **  - int
    **  - long int
    **  - long long int
    **  - unsigned char
    **  - unsigned short int
    **  - unsigned int
    **  - unsigned long int
    **  - unsigned long long int
    */

    /*
    ** @brief The basic struct of is_integral has
    ** has a boolean that contain true if the type is from.
    ** the list, otherwise false.
    */
    template <bool is_integral, typename T>
        struct is_integral_res {
            typedef T type;
            static const bool value = is_integral;
            };

    /*
    ** @brief default template of the structure is_integral_type.
    ** If the type given in argument is from the list, the structure
    ** will be overide by nexts, in according to it type.
    ** If the type given is argument isn't in the list, 
    ** stocked value will be false. So it's not a integral type.
    */
    template <typename>
        struct is_integral_type : public is_integral_res<false, bool> {};

    /* @brief is_integral_type for bool. "value is true".*/
    template <>
        struct is_integral_type<bool> : public is_integral_res<true, bool> {};

    /* @brief is_integral_type for char. "value is true".*/
    template <>
        struct is_integral_type<char> : public is_integral_res<true, char> {};

    /* @brief is_integral_type for signed char. "value is true".*/
    template <>
        struct is_integral_type<signed char> : public is_integral_res<true, signed char> {};

    /* @brief is_integral_type for short int. "value is true".*/
    template <>
        struct is_integral_type<short int> : public is_integral_res<true, short int> {};
    
    /* @brief is_integral_type for int. "value is true".*/
    template <>
        struct is_integral_type<int> : public is_integral_res<true, int> {};

    /* @brief is_integral_type for long int. "value is true".*/
    template <>
        struct is_integral_type<long int> : public is_integral_res<true, long int> {};

    /* @brief is_integral_type for long long int. "value is true".*/
    template <>
        struct is_integral_type<long long int> : public is_integral_res<true, long long int> {};

    /* @brief is_integral_type for unsigned char. "value is true".*/
    template <>
        struct is_integral_type<unsigned char> : public is_integral_res<true, unsigned char> {};

    /* @brief is_integral_type for unsigned short int. "value is true".*/
    template <>
        struct is_integral_type<unsigned short int> : public is_integral_res<true, unsigned short int> {};

    /* @brief is_integral_type for unsigned int. "value is true".*/
    template <>
        struct is_integral_type<unsigned int> : public is_integral_res<true, unsigned int> {};

    /* @brief is_integral_type for unsigned long int. "value is true".*/
    template <>
        struct is_integral_type<unsigned long int> : public is_integral_res<true, unsigned long int> {};
    
    /* @brief is_integral_type for unsigned long long int. "value is true".*/
    template <>
        struct is_integral_type<unsigned long long int> : public is_integral_res<true, unsigned long long int> {};

    /*
    ** @brief Give a structure who contain is the
    ** typename given in template is integral or not,
    ** stocked in "value".
    */
    template <typename T>
        struct is_integral : public is_integral_type<T> { };

    /*  End of is_integral. */

    /*
    ** @brief Empty class to identify the category of an
    ** "random access iterator". This type of iterator is the
    ** most complete iterators. Is particularity is that, it
    ** allow to access elements at an arbitrary offset.
    ** Take a look :
    ** http://www.cplusplus.com/reference/iterator/RandomAccessIterator/
    */
    class random_access_iterator_tag { };

    /*
    ** @brief Empty class to identify the category of an
    ** "bidirectional iterator". Bidirectional can be used to access
    ** the sequence of elements in a range in both directions.
    ** Take a look :
    ** http://www.cplusplus.com/reference/iterator/BidirectionalIterator/
    */
    class bidirectional_iterator_tag { };

    /*
    ** @brief Empty class to identify the category of an
    ** "forward iterator". Forward iterator can be used to 
    ** access the sequence of elements in a range in the direction
    ** that goes (begin to end).
    ** Take a look :
    ** http://www.cplusplus.com/reference/iterator/ForwardIterator/
    */
    class forward_iterator_tag { };

    /*
    ** @brief Empty class to identify the category of an
    ** "input iterator". Input iterator can be used in sequential
    ** input operations, values are read only once and the iterator
    ** is icremented.
    ** Take a look :
    ** http://www.cplusplus.com/reference/iterator/InputIterator/
    */
    class input_iterator_tag { };

    /*
    ** @brief Empty class to identify the category of an
    ** "output iterator". Output iterator can be used in sequential
    ** output operations, values pointed by the iterator is written
    ** a value only once and the iterator is incremented.
    ** Take a look :
    ** http://www.cplusplus.com/reference/iterator/OutputIterator/
    */
    class output_iterator_tag { };

    /*
    ** @brief Validity of an iterator from is tag.
    ** This is the base struct for all is_..._iterator_tag.
    ** A boolean is defined by the template and saved in
    ** structure. Type too.
    */
    template <bool is_valid, typename T>
        struct valid_iterator_tag_res { typedef T type; const static bool value = is_valid; };
    
    /*
    ** @brief Basic to check if the typename given
    ** is an input_iterator. Based on valid_iterator_tag_res.
    ** In this if the typename is not from the possible
    ** input iterator form, validity is set to false.
    */
    template <typename T>
        struct is_input_iterator_tagged : public valid_iterator_tag_res<false, T> { };

    /* Check is_input_iterator_tagged from ft::random_access_iterator_tag */
    template <>
        struct is_input_iterator_tagged<ft::random_access_iterator_tag>
            : public valid_iterator_tag_res<true, ft::random_access_iterator_tag> { };

    /* Check is_input_iterator_tagged from ft::bidirectional_iterator_tag */
    template <>
        struct is_input_iterator_tagged<ft::bidirectional_iterator_tag>
            : public valid_iterator_tag_res<true, ft::bidirectional_iterator_tag> { };

    /* Check is_input_iterator_tagged from ft::forward_iterator_tag */
    template <>
        struct is_input_iterator_tagged<ft::forward_iterator_tag>
            : public valid_iterator_tag_res<true, ft::forward_iterator_tag> { };

    /* Check is_input_iterator_tagged from ft::input_iterator_tag */
    template <>
        struct is_input_iterator_tagged<ft::input_iterator_tag>
            : public valid_iterator_tag_res<true, ft::input_iterator_tag> { };

    /*
    ** @Brief Invalid iterator Exception.
    ** Based on std::exception. Called when
    ** the iterator tested does not meet demand.
    */
    template <typename T>
    class InvalidIteratorException : public std::exception
    {
        private:
            std::string _msg;
        
        public :
            InvalidIteratorException () throw() { _msg = "Is invalid iterator tag : " + std::string(typeid(T).name()); }
            InvalidIteratorException (const InvalidIteratorException&) throw() {}
            InvalidIteratorException& operator= (const InvalidIteratorException&) throw() {}
            virtual ~InvalidIteratorException() throw() {}
            virtual const char* what() const throw() { return (_msg.c_str()); }
    };

    /*
    ** @brief Iterator traits class defining properties of
    ** iterators. In this, iterator_traits obtains information
    ** from Iterator class in template argument.
    */
    template <class Iterator> struct iterator_traits
    {
        /* Result of subtracting one iterator from another, from Iterator. */
        typedef typename Iterator::difference_type       difference_type;

        /* Type of the element where iterator point, from Iterator. */
        typedef typename Iterator::value_type            value_type;

        /* Type of a pointer to an element where the iterator point, from Iterator. */
        typedef typename Iterator::pointer               pointer;

        /* Type of a reference where iterator point, from Iterator. */
        typedef typename Iterator::reference             reference;

        /* The iterator category from Iterator. */
        typedef typename Iterator::iterator_category     iterator_category;
    };
    
    /*
    ** @brief Iterator traits class defining properties of
    ** iterators. This create a default operation with an
    ** object (first argument in tempate argument).
    */
    template <class T> struct iterator_traits<T*>
    {
        /* Result of subtracting one iterator from another. */
        typedef ptrdiff_t                       difference_type;

        /* Type of the element where iterator point. */
        typedef T                               value_type;

        /* Type of a pointer to an element where the iterator point. */
        typedef T*                              pointer;

        /* Type of a reference where iterator point. */
        typedef T&                              reference;

        /* The iterator category from Iterator. */
        typedef ft::random_access_iterator_tag  iterator_category;
    };
    
    /*
    ** @brief Iterator traits class defining properties of
    ** iterators. This create a default operation with a
    ** const object (first argument in tempate argument).
    */
    template <class T> class iterator_traits<const T*>
    {
        /* Result of subtracting one iterator from another. */
        typedef ptrdiff_t                       difference_type;

        /* Type of the element where iterator point. */
        typedef T                               value_type;

        /* Type of a pointer to an element where the iterator point. */
        typedef const T*                        pointer;

        /* Type of a reference where iterator point. */
        typedef const T&                        reference;

        /* The iterator category from Iterator. */
        typedef ft::random_access_iterator_tag  iterator_category;
    };

    /*
    ** @brief Give a difference_type defined in ft::iterator_traits
    ** that's the difference of address in memory
    ** between last and first iterator.
    **
    ** @param first The first iterator.
    ** @param last The last iterator.
    ** @return The difference.
    */
    template<class InputIterator>
        typename ft::iterator_traits<InputIterator>::difference_type
            distance (InputIterator first, InputIterator last)
        {
            typename ft::iterator_traits<InputIterator>::difference_type rtn = 0;
            if (typeid(typename ft::iterator_traits<InputIterator>::iterator_category).name() == typeid(random_access_iterator_tag).name())
                return (last - first);
            while (first != last)
            {
                first++;
                rtn++;
            }
            return (rtn);
        }

    /*
    ** @brief Base class for iterator, not really usefull, but type
    ** defined can be use for iterator_traits. An iterator permeted to
    ** take any element range in an object and using a set of operators.
    */
    template <class Category, class T, class Distance = ptrdiff_t,
        class Pointer = T*, class Reference = T&>
        class iterator
        {
            public:
                /* Type of elements pointed. */
                typedef T           value_type;

                /* Type to represent the difference between two iterators. */
                typedef Distance    difference_type;

                /* Type to represent a pointer to an element pointed */
                typedef Pointer     pointer;

                /* Type to represent a reference to an element pointed */
                typedef Reference   reference;

                /* Category of the iterator. */
                typedef Category    iterator_category;
        };

    /*
    ** @brief Random-access iterators allow to access elements at an
    ** arbitrary offset position relative to the element they point
    ** to. This is the most complete iterators. All pointer types
    ** are also valid random-access-iterators.
    */
    template <class T>
        class random_access_iterator : ft::iterator<ft::random_access_iterator_tag, T>
        {
            public:
                
                /* Category of the iterator. */
                typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category     iterator_category;
                
                /* Type of elements pointed. */
                typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type            value_type;
                
                /* Type to represent the difference between two iterators. */
                typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type       difference_type;
                
                /* Type to represent a pointer to an element pointed */
                typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer               pointer;
                
                /* Type to represent a reference to an element pointed */
                typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference             reference;
                
                /*
                ** @brief Default construtor:
                ** The random access iterator point to null.
                */
                random_access_iterator(void)
                :
                    _elem(u_nullptr)
                {}

                /*
                ** @brief Constructor from pointer:
                ** Construct a random access iterator and point to the
                ** element passed in argument.
                **
                ** @param elem the pointer to the element to iterate. 
                */
                random_access_iterator(pointer elem)
                :
                    _elem(elem)
                {}

                /*
                ** Copy constructor:
                ** Construct a random access iterator and copy the pointer
                ** who point to the element from "op" to this.
                **
                ** @param op the const reference to the random access iterator
                ** to copy.
                */
                random_access_iterator(const random_access_iterator& op)
                :
                    _elem(op._elem)
                {}

                /*
                ** Copy assignation:
                ** Give a random access iterator who is a copy
                ** from "op".
                **
                ** @param op the const reference to the random access
                ** iterator to copy.
                ** @return the random access iterator.
                */
                random_access_iterator &operator=(const random_access_iterator& op)
                {
                    if (this == &op)
		                return (*this);
                    this->_elem = op._elem;
                    return (*this);
                }

                /* Destructor: */
                virtual ~random_access_iterator() {}

                /*
                ** @brief Comparation for equivalence of equality.
                **
                ** @param rhs the const reference to the random access
                ** iterator to compare.
                ** @return true if the element pointed by the iretator is the
                ** same than "rhs", otherwise false.
                */
                bool operator==(const random_access_iterator& rhs) { return (rhs._elem == _elem); }
            
                /*
                ** @brief Comparation for equivalence of inequality.
                **
                ** @param rhs the const reference to the random access
                ** iterator to compare.
                ** @return true if the element pointed by the iretator is not 
                ** the same than "rhs", otherwise false.
                */
                bool operator!=(const random_access_iterator& rhs) { return (rhs._elem != _elem); }

                /*
                ** @brief Give a reference to the rvalue pointed by the 
                ** random access iterator.
                **
                ** @return the rvalue (value where point the pointer).
                */
                reference operator*(void) { return (*_elem); }

                /*
                ** @brief Give the lvalue of the element where is the
                ** random access iterator.
                **
                ** @return the lvalue (the pointer to the element).
                */
                pointer operator->(void) { return &(*this); }

                /*
                ** @brief Preincrement the iterator to point to the
                ** next element in memory.
                **
                ** @return A reference of to this random access iterator
                ** where it point to the next element in memory.
                */
                random_access_iterator& operator++(void)
                {
                    _elem++;
                    return (*this);
                }

                /*
                ** @brief Postincrement the iterator to point to the
                ** next element in memory.
                **
                ** @return a random access iterator incremented (copy
                ** of this).
                */
                random_access_iterator operator++(value_type)
                {
                    random_access_iterator rtn(*this);
                    operator++();
                    return (rtn);
                }

                /*
                ** @brief Predecrement the iterator to point to the
                ** previous element in memory.
                **
                ** @return A reference of to this random access iterator
                ** where it point to the previous element in memory.
                */
                random_access_iterator& operator--(void)
                {
                    _elem--;
                    return (*this);
                }

                /*
                ** @brief Postdecrement the iterator to point to the
                ** previous element in memory.
                **
                ** @return a random access iterator decremented (copy
                ** of this).
                */
                random_access_iterator operator--(value_type)
                {
                    random_access_iterator rtn(*this);
                    operator--();
                    return (rtn);
                }

                /*
                ** @brief Give a random access iterator where the
                ** element is pointed at this + "n" in memory.
                **
                ** @param n the number of elements.
                ** @return the random access iterator.
                */
                random_access_iterator operator+(difference_type n) { return (_elem + n); }
                
                /*
                ** @brief Give a random access iterator where the
                ** element is pointed at this - "n" in memory.
                **
                ** @param n the number of elements.
                ** @return the random access iterator.
                */
                random_access_iterator operator-(difference_type n) { return (_elem - n); }

                /*
                ** @brief Give the difference between the address
                ** of iterators.
                **
                ** @param n the random access iterator with whom 
                ** to make a difference.
                ** @return The difference.
                */
                difference_type operator-(const random_access_iterator& n) { return (_elem - n._elem); }

                /*
                ** @brief Check if the pointer of this random access iterator
                ** is lower than "rhs" in the memory.
                **
                ** @param rhs the random access iterator with who check.
                ** @return true if the pointer of this random access iterator
                ** if lower than "rhs", otherwise false;
                */
                bool operator<(const random_access_iterator& rhs) { return (_elem < rhs._elem); }
                
                /*
                ** @brief Check if the pointer of this random access iterator
                ** is upper than "rhs" in the memory.
                **
                ** @param rhs the random access iterator with who check.
                ** @return true if the pointer of this random access iterator
                ** if upper than "rhs", otherwise false;
                */
                bool operator>(const random_access_iterator& rhs) { return (!(operator<(rhs))); }

                /*
                ** @brief Check if the pointer of this random access iterator
                ** is lower or equal than "rhs" in the memory.
                **
                ** @param rhs the random access iterator with who check.
                ** @return true if the pointer of this random access iterator
                ** if lower or equal than "rhs", otherwise false;
                */
                bool operator<=(const random_access_iterator& ths) { return (_elem <= ths._elem); }

                /*
                ** @brief Check if the pointer of this random access iterator
                ** is upper or equal than "rhs" in the memory.
                **
                ** @param rhs the random access iterator with who check.
                ** @return true if the pointer of this random access iterator
                ** if upper or equal than "rhs", otherwise false;
                */
                bool operator>=(const random_access_iterator& rhs) { return (!(operator<=(rhs))); }

                /*
                ** @brief Give a reference to this random access iterator
                ** where the element pointed is at the actual pointer memory 
                ** plus "n".
                **
                ** @param n the number of elements.
                ** @return the random access iterator.
                */
                random_access_iterator& operator+=(difference_type n)
                {
                    _elem += n;
                    return (*this);
                }

                /*
                ** @brief Give a reference to this random access iterator
                ** where the element pointed is at the actual pointer memory 
                ** minus "n".
                **
                ** @param n the number of elements.
                ** @return the random access iterator.
                */
                random_access_iterator& operator-=(difference_type n)
                {
                    _elem -= n;
                    return (*this);
                }

                /*
                ** @brief Give a reference to the elements at an arbitrary offset 
                ** position relative to the element pointed by the random access
                ** iterator.
                ** 
                ** @param n the offset position.
                ** @return the reference.
                */
                reference operator[](difference_type n) { return (*(operator+(n))); }

            private:
                /* Element pointed by the iterator. */
                pointer _elem;
        };

    /*
    ** @brief Overload of addition between
    ** and diffrence type defined in random access
    ** iterator and a random access iterator.
    **
    ** @param n the difference type.
    ** @param rai the random access iterator.
    ** @return the addition of the pointer of the iterator 
    ** plus the difference type, in memory.
    */
    template<typename T>
    ft::random_access_iterator<T> operator+(
        typename ft::random_access_iterator<T>::difference_type n, typename ft::random_access_iterator<T>& rai)
        {
            return (&(*rai) + n);
        }

    template <class Iterator>
    class reverse_iterator
    {
        public:

            typedef Iterator    iterator_type;
            typedef typename ft::iterator_traits<Iterator>::iterator_category iterator_category;
            typedef typename ft::iterator_traits<Iterator>::value_type      value_type;
            typedef typename ft::iterator_traits<Iterator>::difference_type     difference_type;
            typedef typename ft::iterator_traits<Iterator>::pointer     pointer;
            typedef typename ft::iterator_traits<Iterator>::reference   reference;
            
            /*
            ** @brief Default.
            */
            /** ________________________ WIP ________________________*/
            reverse_iterator();

            /*
            ** @brief Initialization.
            */
            /** ________________________ WIP ________________________*/
            explicit reverse_iterator (iterator_type it);

            /*
            ** @brief Copy.
            */
            /** ________________________ WIP ________________________*/
            template <class Iter>
                reverse_iterator (const reverse_iterator<Iter>& rev_it);

            /** ________________________ WIP ________________________*/
            iterator_type base() const;

            /** ________________________ WIP ________________________*/
            reference operator*() const;

            /** ________________________ WIP ________________________*/
            reverse_iterator operator+ (difference_type n) const;

            /** ________________________ WIP ________________________*/
            reverse_iterator& operator++();

            /** ________________________ WIP ________________________*/
            reverse_iterator operator++(int);

            /** ________________________ WIP ________________________*/
            reverse_iterator& operator+= (difference_type n);

            /** ________________________ WIP ________________________*/
            reverse_iterator operator- (difference_type n) const;

            /** ________________________ WIP ________________________*/
            reverse_iterator& operator--();

            /** ________________________ WIP ________________________*/
            reverse_iterator operator--(int);

            /** ________________________ WIP ________________________*/
            reverse_iterator& operator-= (difference_type n);

            /** ________________________ WIP ________________________*/
            pointer operator->() const { return &(*this); }

            /** ________________________ WIP ________________________*/
            reference operator[] (difference_type n) const;

        private:
    };

    /** ________________________ WIP ________________________*/
    template <class Iterator>
        bool operator== (const reverse_iterator<Iterator>& lhs,
                        const reverse_iterator<Iterator>& rhs);

    /** ________________________ WIP ________________________*/
    template <class Iterator>
        bool operator!= (const reverse_iterator<Iterator>& lhs,
                        const reverse_iterator<Iterator>& rhs);

    /** ________________________ WIP ________________________*/
    template <class Iterator>
        bool operator<  (const reverse_iterator<Iterator>& lhs,
                        const reverse_iterator<Iterator>& rhs);

    /** ________________________ WIP ________________________*/
    template <class Iterator>
        bool operator<= (const reverse_iterator<Iterator>& lhs,
                        const reverse_iterator<Iterator>& rhs);

    /** ________________________ WIP ________________________*/
    template <class Iterator>
        bool operator>  (const reverse_iterator<Iterator>& lhs,
                        const reverse_iterator<Iterator>& rhs);

    /** ________________________ WIP ________________________*/
    template <class Iterator>
        bool operator>= (const reverse_iterator<Iterator>& lhs,
                        const reverse_iterator<Iterator>& rhs);

    /** ________________________ WIP ________________________*/
    template <class Iterator>
        reverse_iterator<Iterator> operator+ (
            typename reverse_iterator<Iterator>::difference_type n,
            const reverse_iterator<Iterator>& rev_it);

    /** ________________________ WIP ________________________*/
    template <class Iterator>
        typename reverse_iterator<Iterator>::difference_type operator- (
            const reverse_iterator<Iterator>& lhs,
            const reverse_iterator<Iterator>& rhs);

} /* End of namespace */

# endif