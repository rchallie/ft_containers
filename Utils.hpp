/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: excalibur <excalibur@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 18:25:12 by excalibur         #+#    #+#             */
/*   Updated: 2020/06/24 22:34:19 by excalibur        ###   ########.fr       */
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
static class nullptr_t
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
    ** Base class for standard binary function objects.
    ** (Doc = http://www.cplusplus.com/reference/functional/binary_function/?kw=binary_function)
    ** It have no operator "()" like functin objects, 
    ** it is up to the class deriving from it to define it.
    ** It just has 3 public data memebers that are typedefs of the
    ** template parameters.
    ** (the operator "()", permet to use a class with the same syntax
    ** as a function call).
    */
    template <class Arg1, class Arg2, class Result>
        struct binary_function
        {
            /* The first argument type */
            typedef Arg1 first_argument_type;

            /* The second arguement type */
            typedef Arg2 second_argument_type;

            /* The result type */
            typedef Result result_type;
        };
    
    /*
    ** A binary function object class who will return
    ** whether the first arguement compares less than the second.
    ** (using "<" operator).
    */
    template <class T>
        struct less : binary_function<T, T, bool>
        {
            bool operator() (const T& x, const T& y) const { return (x < y); }
        };

    /*
    ** Couple a pair of values, which may be of different types
    ** (T1 and T2)
    */
    template <class T1, class T2>
        struct pair
        {
            public :

                // Member types :

                /* The first template argument type */
                typedef T1 first_type;

                /* The second template argument type */
                typedef T2 second_type;

                // Member variables :

                /* The first value in the pair */
                T1 first;

                /* The second value in the pair */
                T2 second;

                /*
                ** @brief Default.
                ** Construct a pair object with its element
                ** value-initialized.
                */
                pair()
                :
                    first(),
                    second()
                {}

                /*
                ** @brief Copy.
                ** The pair is initialized with the content
                ** of "pr". The "pr" first is passed to this
                ** first, same for second of each.
                **
                ** @param pr the pair to copy.
                */
                template<class U, class V>
                    pair (const pair<U, V>& pr)
                    :
                        first(pr.first),
                        second(pr.second)
                    {}

                /*
                ** @brief Initialization.
                ** Member "first" is constructed with a.
                ** Member "second" is constructed with b.
                **
                ** @param a to member first.
                ** @param b to member second.
                */
                pair (const first_type& a, const second_type& b)
                :
                    first(a),
                    second(b)
                {}

                /*
                ** @brief Assigns "pr" member (first, second) to this.
                **
                ** @param pr the pair object to copy.
                */
                pair& operator= (const pair& pr)
                {
                    first = pr.first;
                    second = pr.second;
                    return (*this);
                }
        };
    
    /*
    ** @brief Equal comparison between two pair object.
    **
    ** @param lhs Base of comparison.
    ** @param rhs To compare with "lsh".
    ** @return True if the condition is hold, otherwise false.
    */
    template <class T1, class T2>
        bool operator== (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
        {
            return (lhs.first == rhs.first && lhs.second == rhs.second);
        }

    /*
    ** @brief Difference comparison between two pair object.
    **
    ** @param lhs Base of comparison.
    ** @param rhs To compare with "lsh".
    ** @return True if the condition is hold, otherwise false.
    */
    template <class T1, class T2>
        bool operator!= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
        {
            return !(lhs == rhs);
        }
    
    /*
    ** @brief Inferior comparison between two pair object.
    **
    ** @param lhs Base of comparison.
    ** @param rhs To compare with "lsh".
    ** @return True if the condition is hold, otherwise false.
    */
    template <class T1, class T2>
        bool operator<  (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
        {
            return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
        }

    /*
    ** @brief Inferior or equal comparison between two pair object.
    **
    ** @param lhs Base of comparison.
    ** @param rhs To compare with "lsh".
    ** @return True if the condition is hold, otherwise false.
    */
    template <class T1, class T2>
        bool operator<= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
        {
            return !(rhs < lhs);
        }

    /*
    ** @brief Superior comparison between two pair object.
    **
    ** @param lhs Base of comparison.
    ** @param rhs To compare with "lsh".
    ** @return True if the condition is hold, otherwise false.
    */
    template <class T1, class T2>
        bool operator>  (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
        {
            return (rhs < lhs);
        }

    /*
    ** @brief Superior or equal comparison between two pair object.
    **
    ** @param lhs Base of comparison.
    ** @param rhs To compare with "lsh".
    ** @return True if the condition is hold, otherwise false.
    */
    template <class T1, class T2>
        bool operator>= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
        {
            return !(lhs < rhs);
        }
    
    /*
    ** @bref Construct a pair object with
    ** "x" and "y".
    **
    ** @param x, y elements. (cna have different types).
    ** @return the pair object.
    */
    template <class T1, class T2>
        ft::pair<T1,T2> make_pair(T1 x, T2 y)
        {
            return (ft::pair<T1, T2>(x, y));
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
    ** has a boolean ("value") that contain true if the type is from.
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
    ** @brief This will return a structure
    ** that contain a boolean "value" true if the
    ** iterator given is tagged with a ft iterator
    ** tag, otherwise "value" is false.
    */
    template <typename T>
        struct is_ft_iterator_tagged : public valid_iterator_tag_res<false, T> { };
    
    /* Check is_ft_iterator_tagged from ft::random_access_iterator_tag */
    template <>
        struct is_ft_iterator_tagged<ft::random_access_iterator_tag>
            : public valid_iterator_tag_res<true, ft::random_access_iterator_tag> { };

    /* Check is_ft_iterator_tagged from ft::bidirectional_iterator_tag */
    template <>
        struct is_ft_iterator_tagged<ft::bidirectional_iterator_tag>
            : public valid_iterator_tag_res<true, ft::bidirectional_iterator_tag> { };

    /* Check is_ft_iterator_tagged from ft::forward_iterator_tag */
    template <>
        struct is_ft_iterator_tagged<ft::forward_iterator_tag>
            : public valid_iterator_tag_res<true, ft::forward_iterator_tag> { };

    /* Check is_ft_iterator_tagged from ft::input_iterator_tag */
    template <>
        struct is_ft_iterator_tagged<ft::input_iterator_tag>
            : public valid_iterator_tag_res<true, ft::input_iterator_tag> { };

    /* Check is_ft_iterator_tagged from ft::output_iterator_tag */
    template <>
        struct is_ft_iterator_tagged<ft::output_iterator_tag>
            : public valid_iterator_tag_res<true, ft::output_iterator_tag> { };

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

    template <class T>
        class bidirectional_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
        {  
            /* Category of the iterator. */
            typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category     iterator_category;
            
            /* Type of elements pointed. */
            typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::value_type            value_type;
            
            /* Type to represent the difference between two iterators. */
            typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type       difference_type;
            
            /* Type to represent a pointer to an element pointed */
            typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::pointer               pointer;
            
            /* Type to represent a reference to an element pointed */
            typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::reference             reference;
            
            private:
                /* Element pointed by the iterator. */
                pointer _elem;
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
                ** @return true if the element pointed by the iretator is 
                ** the same than "rhs", otherwise false.
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
                reference operator*(void) const { return (*_elem); }

                /*
                ** @brief Give the lvalue of the element where is the
                ** random access iterator.
                **
                ** @return the lvalue (the pointer to the element).
                */
                pointer operator->(void) { return &(this->operator*()); }

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
                random_access_iterator operator++(int)
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
                random_access_iterator operator--(int)
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
                random_access_iterator operator+(difference_type n) const { return (_elem + n); }
                
                /*
                ** @brief Give a random access iterator where the
                ** element is pointed at this - "n" in memory.
                **
                ** @param n the number of elements.
                ** @return the random access iterator.
                */
                random_access_iterator operator-(difference_type n) const { return (_elem - n); }

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

            /* Iterator's type. */
            typedef Iterator    iterator_type;

            /* Preserves Iterator's category. */
            typedef typename ft::iterator_traits<Iterator>::iterator_category iterator_category;
            
            /* Preserves Iterator's value type. */
            typedef typename ft::iterator_traits<Iterator>::value_type      value_type;
            
            /* Preserves Iterator's difference type. */
            typedef typename ft::iterator_traits<Iterator>::difference_type     difference_type;
            
            /* Preserves Iterator's pointer. */
            typedef typename ft::iterator_traits<Iterator>::pointer     pointer;
            
            /* Preserves Iterator's reference. */
            typedef typename ft::iterator_traits<Iterator>::reference   reference;
            
            /*
            ** @brief Default.
            ** Construct a reverse iterator object.
            ** This will points to no object.
            */
            reverse_iterator() : _elem() {}

            /*
            ** @brief Initialization.
            ** Construct a reverse iterator object from
            ** an original iteretor "it".
            ** The behavior of the constructed object
            ** replicate the orignal, but he iterates
            ** in the reverse order.
            **
            ** @param it The iterator to replicate.
            */
            explicit reverse_iterator (iterator_type it) : _elem(it) {}

            /*
            ** @brief Copy.
            ** Contruct a reverse iterator from other reverse iterator.
            ** Save the sense of iterateration as "rev_it".
            **
            ** @param rev_it original reverse iterator.
            */
            template <class Iter>
                reverse_iterator (const reverse_iterator<Iter>& rev_it) : _elem(rev_it.base()) {}

            /* Added to follow subject obligation */
            virtual ~reverse_iterator() {}

            /*
            ** @brief Return a copy of the base iterator.
            ** Same type as the usert to construct the reverse_iterator.
            ** But pointing to the element next of this.
            ** (A reverse iterator always pointing to an element at
            ** an offset of -1).
            **
            ** @return A copy of the base iterator.
            */
            iterator_type base() const { return (_elem); }

            /*
            ** @brief Return a reference to the element pointed
            ** by the iterator.
            **
            ** @return The reference.
            */
            reference operator*() const
            {
                iterator_type tmp = _elem;
                return (*(--tmp));
            }

            /*
            ** @brief Return a reverse iterator pointing to
            ** the element at n position away from the pointed
            ** element of the iterator.
            ** This function need the base iterator to be a
            ** "random-access iterator".
            **
            ** @param "n" Number of elements to offset.
            ** @return An iterator pointing to the element at "n"
            ** position away.
            */
            reverse_iterator operator+ (difference_type n) const { return (reverse_iterator(_elem - n)); }

            /*
            ** @brief Advances the reverse_iterator by one position.
            ** Pre-increment.
            **
            ** @return return "(*this)" incremented.
            */
            reverse_iterator& operator++()
            {
                --_elem;
                return (*this);
            }

            /*
            ** @brief Advances the reverse_iterator by one position.
            ** Post-increment.
            **
            ** @return the value "(*this)" value had before the
            ** call.
            */
            reverse_iterator operator++(int)
            {
                reverse_iterator tmp = *this;
                ++(*this);
                return (tmp);
            }

            /*
            ** @brief Advances the "reverse_iterator" by n element positions.
            ** This function need the base iterator to be a
            ** "random-access iterator".
            **
            ** @param n the number of element.
            ** @return the reverse iterator itself (*this).
            */
            reverse_iterator& operator+= (difference_type n)
            {
                _elem -= n;
                return (*this);
            }

            /*
            ** @brief Return a reverse iterator pointing to the element
            ** located n positions before the element the iterator
            ** currently points to.
            ** This function need the base iterator to be a
            ** "random-access iterator".
            **
            ** @param n the number of element.
            ** @return An iterator pointing to the element
            ** n position before the currently pointed one.
            */
            reverse_iterator operator- (difference_type n) const { return (reverse_iterator(_elem + n)); }

            /*
            ** @brief Decreases the reverse iterator by one position.
            **
            ** @return "(*this)".
            */
            reverse_iterator& operator--()
            {
                ++_elem;
                return (*this);
            }

            /*
            ** @brief Decreases the reverse iterator by one position.
            **
            ** @retun "(*this)" value before the call.
            */
            reverse_iterator operator--(int)
            {
                reverse_iterator tmp = *this;
                --(*this);
                return (tmp);
            }

            /*
            ** @brief Decreases the reverse iterator by "n" element
            ** postion.
            ** This function need the base iterator to be a
            ** "random-access iterator".
            **
            ** @param n Number of elements to offset.
            ** @return "(*this)".
            */
            reverse_iterator& operator-= (difference_type n)
            {
                _elem += n;
                return (*this);
            }

            /*
            ** @brief Give a pointer to the element
            ** pointed.
            **
            ** @return A pointer to the element pointed.
            */
            pointer operator->() const { return &(operator*()); }

            /*
            ** @brief Accesse the element at "n" positions
            ** away from the element currently pointed.
            ** Cause undefined behavior if the element
            ** does not exist.
            **
            ** @param n The number of positions.
            ** @return A reference at "n".
            */
            reference operator[] (difference_type n) const { return (this->base()[-n - 1]); }

        private:
            iterator_type     _elem;
    };

    /*
    ** @brief Equal comparison between two reverse iterator.
    **
    ** @param lhs Base of comparison.
    ** @param rhs To compare with "lsh".
    ** @return True if the condition is hold, otherwise false.
    */
    template <class Iterator>
        bool operator== (const reverse_iterator<Iterator>& lhs,
                        const reverse_iterator<Iterator>& rhs) { return (lhs.base() == rhs.base()); }

    /*
    ** @brief Different comparison between two reverse iterator.
    **
    ** @param lhs Base of comparison.
    ** @param rhs To compare with "lsh".
    ** @return True if the condition is hold, otherwise false.
    */
    template <class Iterator>
        bool operator!= (const reverse_iterator<Iterator>& lhs,
                        const reverse_iterator<Iterator>& rhs) { return (lhs.base() != rhs.base()); }

    /*
    ** @brief Inferior comparison between two reverse iterator.
    **
    ** @param lhs Base of comparison.
    ** @param rhs To compare with "lsh".
    ** @return True if the condition is hold, otherwise false.
    */
    template <class Iterator>
        bool operator<  (const reverse_iterator<Iterator>& lhs,
                        const reverse_iterator<Iterator>& rhs) { return (lhs.base() > rhs.base()); }

    /*
    ** @brief Inferior or equal comparison between two reverse iterator.
    **
    ** @param lhs Base of comparison.
    ** @param rhs To compare with "lsh".
    ** @return True if the condition is hold, otherwise false.
    */
    template <class Iterator>
        bool operator<= (const reverse_iterator<Iterator>& lhs,
                        const reverse_iterator<Iterator>& rhs) { return (lhs.base() >= rhs.base()); }

    /*
    ** @brief Superior comparison between two reverse iterator.
    **
    ** @param lhs Base of comparison.
    ** @param rhs To compare with "lsh".
    ** @return True if the condition is hold, otherwise false.
    */
    template <class Iterator>
        bool operator>  (const reverse_iterator<Iterator>& lhs,
                        const reverse_iterator<Iterator>& rhs) { return (lhs.base() < rhs.bash()); }

    /*
    ** @brief Superior or equal comparison between two reverse iterator.
    **
    ** @param lhs Base of comparison.
    ** @param rhs To compare with "lsh".
    ** @return True if the condition is hold, otherwise false.
    */
    template <class Iterator>
        bool operator>= (const reverse_iterator<Iterator>& lhs,
                        const reverse_iterator<Iterator>& rhs) { return (lhs.base() <= rhs.base()); }

    /*
    ** @brief Give a reverse iterator pointing to
    ** "rev_it" plus "n".
    **
    ** @param n The number of location away the element pointed 
    ** by rev_it.
    ** @param rev_it The reverse iterator.
    ** @return A reverse iterator pointing to n element
    ** after rev_it pointed element.
    */
    template <class Iterator>
        reverse_iterator<Iterator> operator+ (
            typename reverse_iterator<Iterator>::difference_type n,
            const reverse_iterator<Iterator>& rev_it) { return (rev_it + n); }

    /*
    ** @brief The distance between lhs and rhs.
    **
    ** @param lhs Base of comparison.
    ** @param rhs To compare with "lsh".
    ** @return The number of elements between lsh and rhs.
    */
    template <class Iterator>
        typename reverse_iterator<Iterator>::difference_type operator- (
            const reverse_iterator<Iterator>& lhs,
            const reverse_iterator<Iterator>& rhs) { return (lhs.base() - rhs.base()); }

    /* Lexicographical comparison */

    /*
    ** @brief Return true if the range [first1, last2) compare
    ** lexicographically lest than the range [first2, last2).
    **
    ** @param first1, last1 the start and the end of the first range.
    ** @param first2, last2 the start and the end of the second range.
    ** @return true if the first range compares lexicographically less
    ** than the second, false otherwise.
    */
    template <class InputIterator1, class InputIterator2>
        bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                        InputIterator2 first2, InputIterator2 last2)
        {
            while (first1 != last1)
            {
                if (first2 == last2 || *first2 < *first1) return false;
                else if (*first1 < *first2) return true;
                ++first1;
                ++first2;
            }
            return (first2 != last2);
        }

    /*
    ** @brief Return true if the range [first1, last2) compare
    ** lexicographically lest than the range [first2, last2).
    ** The comparision is effectued by "comp".
    **
    ** @param first1, last1 the start and the end of the first range.
    ** @param first2, last2 the start and the end of the second range.
    ** @param comp the function that will compare.
    ** @return true if the first range compares lexicographically less
    ** than the second, false otherwise.
    */
    template <class InputIterator1, class InputIterator2, class Compare>
        bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                        InputIterator2 first2, InputIterator2 last2,
                                        Compare comp)
        {
            while (first1 != last1)
            {
                if (first2 == last2 || comp(*first2, *first1)) return false;
                else if (comp(*first1, *first2)) return true;
                ++first1;
                ++first2;
            }
            return (first2 != last2);
        }
    
    // Node :

    template <typename T>
    struct Node
    {
        public :

            /* First template argument, the type of stocked value */
            typedef T   value_type;

            value_type value;
            Node* left;
            Node* right;

            /*
            ** @brief Default.
            ** Create a Node with default initisialized value.
            ** Left and right branch pointer to a "u_nullptr" (t_nullptr).
            */
            Node ()
            :
                value(),
                left(u_nullptr),
                right(u_nullptr)
            {}
            
            /*
            ** @brief Value.
            ** Create a Node with value defined by a copy of "val".
            ** Left and right branch pointer to a "u_nullptr" (t_nullptr).
            **
            ** @param val the value to copy.
            */
            Node (const value_type& val)
            :
                value(val),
                left(u_nullptr),
                right(u_nullptr)
            {}

            /*
            ** @brief Copy.
            ** Create a Node that a copy of "nd".
            ** The value is initalized by a copy of "nd" value.
            ** Left and right branch point to the same than "nb" branches.
            **
            ** @param nd the Node to copy.
            */
            Node (const Node& nd)
            :
                value(nd.value),
                left(nd.left),
                right(nd.right)
            {}

            virtual ~Node() {}

            /*
            ** @brief Equal operator.
            ** Create a Node that a copy of "nd".
            ** The value is initalized by a copy of "nd" value.
            ** Left and right branch point to the same than "nb" branches.
            **
            ** @param nd the Node to copy.
            ** @return *this.
            */
            Node &operator=(const Node& nd)
            {
                if (nd == *this)
                    return (*this);
                
                this->value = nd.value;
                this->left = nd.left;
                this->right = nd.right;
                
                return (*this);
            }

            /*
            ** @brief Compare two node to know
            ** if they contains the same value.
            **
            ** @param nd the node to compare.
            ** @return true if the value are the same
            ** otherwise no.
            */
            bool operator==(const Node& nd)
            {
                if (value == nd.value)
                    return (true);
                return (false);
            }
    };

    // Binary Search Tree :

    /*
    ** Iterator class for binary search tree.
    ** This is a bidirectional iterator.
    */
    template <typename T>
    class BST_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
    {
        public:

            /* The iterator category */
            typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category iterator_category;

            /* The value_type pointed by the iterator (BST)*/
            typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::value_type    value_type;

            /* The difference type */
            typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type   difference_type;

            /* The pointer to the value */
            typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::pointer   pointer;

            /* The reference to the value */
            typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::reference reference;
    
            //Node

            /* A Binary search tree contain node that contain a type of value */ 
            typedef typename value_type::value_type     bst_value_type;

            /* A binary search tree contain node, that a pointer type to a node */
            typedef typename value_type::node_pointer   bst_node_pointer;
            
            /*
            ** @brief Default.
            ** Create an iterator that pointing to inisialized 
            ** binary search tree.
            */
            BST_iterator()
            :
                _bst(),
                _elem()
            {}

            /*
            ** @brief Create an iterator
            ** from "bst" that has a binary search tree.
            **
            ** @param bst the binary search tree that will be iterate.
            */
            BST_iterator(const value_type bst)
            :
                _bst(bst),
                _elem(bst->get_lower_node())
            {}

            /*
            ** @brief Copy constructor.
            ** Create a new Binary search tree iterator to be 
            ** a copy of another.
            **
            ** @param bst_it the binary search tree to be inpired by.
            */
            BST_iterator(const BST_iterator& bst_it)
            :
                _bst(bst_it._bst),
                _elem(bst_it._elem)
            {}

            // Added for subject
            virtual ~BST_iterator() { }

            /*
            ** @brief Assignement operator.
            ** Create an iterator that will iterate the same than
            ** "bst_it".
            **
            ** @param bst_it the binary search tree to be inpired by.
            ** @return a reference to this.
            */
            BST_iterator &operator=(const BST_iterator& bst_it)
            {
                if (bst_it == *this)
                    return (*this);
                this->_bst = &bst_it._bst;
                this->_elem = bst_it._elem;
                return (*this);
            }

            /*
            ** @brief Strictment equal operator.
            ** Return a boolean that contain if this iterator
            ** and other one contain to equal binary search tree.
            **
            ** @param bst_it the other binaray search tree iterator.
            ** @return true if the two iterator iterate on two equal
            ** tree, otherwise false.
            */
            bool operator==(const BST_iterator& bst_it)
            { return (_bst == bst_it._bst); }

            /*
            ** @brief Different operator.
            ** Return a boolean that contain if this iterator
            ** and other one contain are two different binary search tree.
            **
            ** @param bst_it the other binaray search tree iterator.
            ** @return true if the two iterator iterate on two different
            ** tree, otherwise false.
            */
            bool operator!=(const BST_iterator& bst_it)
            { return (_bst != bst_it._bst); }

            /*
            ** @brief Give a reference to the value that contain
            ** the binary search tree (value on a node) at the iterator
            ** position.
            **
            ** @return the const reference.
            */
            bst_value_type& operator*() const
            { return (_elem->value); }

            /*
            ** @brief Give a pointer to the value that contain
            ** the binary search tree (value on a node) at the iterator
            ** position.
            **
            ** @return the const pointer.
            */
            bst_value_type* operator->() const
            { return (&_elem->value); }

            /*
            ** @brief Increment the iterator to the next value
            ** after the value in the tree at iterator position.
            **
            ** @return a reference to this.
            */
            BST_iterator& operator++(void)
            {
                _elem = _bst.next(_elem);
                return (*this);
            }

            /*
            ** @brief Post increment the iterator to the next value
            ** after the value in the tree at iterator position.
            **
            ** @return this before the incrementation.
            */
            BST_iterator operator++(int)
            {
                BST_iterator tmp(*this);
                operator++();
                return (tmp);
            }

            /*
            ** @brief Decrement the iterator to the previous value
            ** before the value in the tree at iterator position.
            **
            ** @return a reference to this.
            */
            BST_iterator& operator--(void)
            {
                _elem = _bst.prev(_elem);
                return (*this);
            }
            /*
            ** @brief Post decrement the iterator to the previous value
            ** before the value in the tree at iterator position.
            **
            ** @return this before the incrementation.
            */
            BST_iterator operator--(int)
            {
                BST_iterator tmp(*this);
                operator--();
                return (tmp);
            }

        private:

            value_type _bst;
            bst_node_pointer _elem;
    };
    
    /*
    ** Iterator class for const binary search tree.
    ** The difference between this class and normal binary search tree iterator
    ** is that the binary search tree used by this iterator is const, the value
    ** pointed by the tree are const, and the given pointer are const.
    ** This is a bidirectional iterator.
    ** Refere to BST_iterator.
    */
    template <typename T>
    class BST_const_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
    {
        public:

            typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category iterator_category;

            typedef const typename ft::iterator<ft::bidirectional_iterator_tag, T>::value_type    value_type;

            typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type   difference_type;

            typedef const typename ft::iterator<ft::bidirectional_iterator_tag, T>::pointer   pointer;

            typedef const typename ft::iterator<ft::bidirectional_iterator_tag, T>::reference reference;
    
            //Node
            typedef const typename value_type::value_type     bst_value_type;

            typedef const typename value_type::node_pointer   bst_node_pointer;
            
            BST_const_iterator()
            :
                _elem()
            {}

            BST_const_iterator(const value_type bst)
            :
                _bst(bst),
                _elem(bst->get_lower_node())
            {}

            // Added for subject
            virtual ~BST_const_iterator() { }

            BST_const_iterator &operator=(const BST_const_iterator& bst_it)
            {
                if (bst_it == *this)
                    return (*this);
                this->_bst = &bst_it._bst;
                this->_elem = bst_it._elem;
                return (*this);
            }

            bool operator==(const BST_const_iterator& bst_it)
            { return (_bst == bst_it._bst); }

            bool operator!=(const BST_const_iterator& bst_it)
            { return (_bst != bst_it._bst); }

            const bst_value_type& operator*() const
            { return (_elem->value); }

            bst_node_pointer operator->() const
            { return (&_elem->value); }

            const BST_const_iterator& operator++(void)
            {
                _elem = _bst.next(_elem);
                return (*this);
            }

            BST_const_iterator operator++(int)
            {
                BST_const_iterator tmp(*this);
                operator++();
                return (tmp);
            }

            BST_const_iterator& operator--(void)
            {
                _elem = _bst.prev(_elem);
                return (*this);
            }

            BST_const_iterator operator--(int)
            {
                BST_const_iterator tmp(*this);
                operator--();
                return (tmp);
            }

        private:

            value_type _bst;
            bst_node_pointer _elem;
    };
    
    /*
    ** Binary Search Tree:
    ** Classement method of nodes values in tree. If a node value is
    ** superior to the a node, it's classed at right, otherwise at left
    ** if it's lower. Like :
    **
    **                  42
    **                 /  \
    **               15    58
    **              /  \
    **             2    26    
    */
    template <typename T, class Node = ft::Node<T>,
        class Type_Alloc = std::allocator<T>, class Node_Alloc = std::allocator<Node>,
        class Compare = ft::less<T> >
    class Binary_search_tree
    {
        public :

            /* Self type */
            typedef Binary_search_tree  self;

            /* A reference to the self type */
            typedef self&   self_reference;
            
            /* The first template argument */
            typedef T   value_type;

            /* The second template argument */
            typedef Node    node_type;

            typedef node_type*  node_pointer;

            /* The third template argument */
            typedef Type_Alloc       value_allocator_type;

            /* The fourth template argument */
            typedef Node_Alloc       node_allocator_type;

            /* The fifth template argument */
            typedef Compare     value_compare;

            /* Iterator of the binary search tree */
            typedef BST_iterator<self> iterator;

            /* Iterator pointing to a const self. Everything in this is
                const, the BST, the node, the value pointed by the node */
            typedef BST_const_iterator<const self> const_iterator;

            /*
            ** @brief Default constructor.
            ** Create a binary search tree, pointing to a
            ** null_ptr.
            */
            Binary_search_tree ()
            :
                _root(u_nullptr)
            {}

            /*
            ** @brief From value constructor.
            ** Create a binary search tree that will
            ** point to an object of type from value_type.
            **
            ** @param val the value to point (copy).
            */
            Binary_search_tree (const value_type& val)
            :
                _root(_BST_new_node(val))
            {}

            /*
            ** @brief From node constructor.
            ** Create a binary search tree that will point
            ** to an object from a node. That will create a copy
            ** from the node.
            **
            ** @param root the node containing the value to point.
            */
            Binary_search_tree (const node_type& root)
            :
                _root(_BST_new_node(root.value, root.left, root.right))
            {}

            /*
            ** @brief Copy constructor.
            ** Create an binary search tree from another by copying it.
            **
            ** @param bst the binary search tree to copy.
            */
            Binary_search_tree (const Binary_search_tree& bst)
            :
                _root(bst._root),
                _alloc_node(bst._alloc_node)
            {}

            /* Destructor */
            virtual ~Binary_search_tree()
            { }

            /*
            ** @brief Assignement operator.
            ** Assign values of this to "bst" values.
            ** 
            ** @param bst the binary search tree to inspire.
            ** @return a reference to this. 
            */
            self_reference operator=(const Binary_search_tree& bst)
            {
                if (bst == *this)
                    return (*this);

                this->_alloc_node = bst._alloc_node;
                this->_root = bst._root;

                return (*this);
            }
            
            /*
            ** @brief Insert value on the tree.
            **
            ** @param val the value to insert.
            */
            void insert(const value_type& val)
            { this->_root = _BST_insert(val, this->_root); }

            /*
            ** @brief Search the value on the tree
            ** and give a pointer to the node containing
            ** the value.
            **
            ** @param val the value to search.
            ** @return a pointer to the node that containing
            ** the value. If the value doesn't exist, that return
            ** a u_nullptr. 
            */
            node_pointer search(const value_type& val)
            { return (_BST_search(val, this->_root)); }

            /*
            ** @brief Remove the value from the tree.
            **
            ** @param val the value to remove.
            */
            void remove(const value_type& val)
            { _BST_remove_node(val, _root); }

            /*
            ** @brief Give a pointer to the node that 
            ** is the root of the tree.
            **
            ** @return the pointer.
            */
            node_pointer get_root_node(void)
            { return (this->_root); }

            /*
            ** @brief Get the lowest value of the tree.
            **
            ** @return a pointer to the node that contain the
            ** lowest value.
            */
            node_pointer get_lower_node(void) const
            { return (_BST_get_lower_node(this->_root)); }

            /*
            ** @brief Get the higher value of the tree.
            **
            ** @return a pointer to the node that contain the
            ** highest value.
            */
            node_pointer get_higher_node(void) const
            { return (_BST_get_higher_node(this->_root)); }

            /*
            ** @brief Get the node that contain the next value
            ** after that of "find_after".
            **
            ** @param find_after a pointer to a node
            ** that contain the value of reference to find the next.
            ** @return a pointer to the node that contain the next value.
            */
            node_pointer next(node_pointer find_after)
            { return (_BST_next(this->_root, find_after)); }

            /*
            ** @brief Get the node that contain the previous value
            ** after that of "find_after".
            **
            ** @param find_after a pointer to a node
            ** that contain the value of reference to find the previous.
            ** @return a pointer to the node that contain the previous value.
            */
            node_pointer prev(node_pointer find_before)
            { return (_BST_prev(this->_root, find_before)); }

            /*
            ** @brief Strictment equal operator.
            ** Return a bool to know if two bst contains the sames
            ** values.
            **
            ** @param bst the tree to compare.
            ** @return true if the trees are the same, otherwise no.
            */
            bool operator==(const ft::Binary_search_tree<T>& bst)
            { return (_BST_operator_strict_equal(this->_root, bst._root)); }

        private:

            node_pointer _root;
            node_allocator_type _alloc_node;
            value_compare comp;

            /* Refere to insert() */
            node_pointer _BST_insert(const value_type& val, node_pointer root)
            {
                if (root == u_nullptr)
                    return (_BST_new_node(val));
                else if (comp(val, root->value))
                    root->left = _BST_insert(val, root->left);
                else
                    root->right = _BST_insert(val, root->right);
                return (root);
            }

            /* Refere to search() */
            node_pointer _BST_search(const value_type& val, node_pointer root)
            {
                if (root == u_nullptr || root->value == val)
                    return (root);
                else if (comp(val, root->value))
                    return (_BST_search(val, root->left));
                else
                    return (_BST_search(val, root->right));
            }

            /*
            ** @brief Create a new node for the tree.
            ** This node contain "val".
            **
            ** @param the value that the node will contain.
            ** @param left, right the node that the new node will
            ** point at left/right.
            ** @return a pointer to the new node.
            */
            node_pointer _BST_new_node(const value_type& val,
                node_pointer left = u_nullptr, node_pointer right = u_nullptr)
            {
                node_pointer nd;
                nd = _alloc_node.allocate( 1 );
                nd->value = val;
                nd->left = left;
                nd->right = right;
                return (nd);
            }

            /* Refere to remove() */
            node_pointer _BST_remove_node(const value_type& val, node_pointer root)
            {
                if (root == u_nullptr)
                    return (root);
                
                if (comp(val, root->value))
                    root->left = _BST_remove_node(val, root->left);
                else if (!(comp(val, root->value)) && val != root->value)
                    root->right = _BST_remove_node(val, root->right);
                else
                {
                    if (root->left == u_nullptr)
                    {
                        node_pointer tmp = root->right;
                        _alloc_node.deallocate(root, 1);
                        return (tmp);
                    }
                    else if (root->right == u_nullptr)
                    {
                        node_pointer tmp = root->left;
                        _alloc_node.deallocate(root, 1);
                        return (tmp);
                    }

                    node_pointer tmp = root->right;

                    for (; tmp != u_nullptr && tmp->left != u_nullptr; tmp = tmp->left);
                    
                    root->value = tmp->value;

                    _BST_remove_node(tmp->value, root->right);
                }

                return (root);
            }

            /* Refere to get_lower_node() */
            node_pointer _BST_get_lower_node(node_pointer root) const
            {
                while (root != u_nullptr && root->left != u_nullptr)
                    root = root->left;
                return (root);
            }

            /* Refere to get_higher_node() */
            node_pointer _BST_get_higher_node(node_pointer root) const
            {
                while (root != u_nullptr && root->right != u_nullptr)
                    root = root->right;
                return (root);
            }

            /* Refere to next() */
            node_pointer _BST_next(node_pointer root, node_pointer after)
            {
                if (after->right != u_nullptr)
                    return (_BST_get_lower_node(after->right));
                
                node_pointer rtn = u_nullptr;

                while (root != u_nullptr)
                {
                    if (after->value < root->value)
                    {
                        rtn = root;
                        root = root->left;
                    }
                    else if (after->value > root->value)
                        root = root->right;
                    else
                        break;
                }

                return (rtn);
            }

            /* Refere to previous() */
            node_pointer _BST_prev(node_pointer root, node_pointer before)
            {
                if (before->left != u_nullptr)
                    return (_BST_get_higher_node(before->left));
                
                node_pointer rtn = u_nullptr;

                while (root != u_nullptr)
                {
                    if (before->value < root->value)
                        root = root->left;
                    else if (before->value > root->value)
                    {
                        rtn = root;
                        root = root->right;
                    }
                    else
                        break;
                }
                return (rtn);
            }

            /* Refere to operator==() */
            bool _BST_operator_strict_equal(node_pointer root, node_pointer root2)
            {
                if (root == u_nullptr && root2 == u_nullptr)
                    return (true);
                else if ((root == u_nullptr && root2 != u_nullptr)
                    || (root != u_nullptr && root2 == u_nullptr))
                    return (false);

                if (root->value != root2->value)
                    return (false);
                
                if (((root->left != u_nullptr && root2->left == u_nullptr)
                    || (root->left == u_nullptr && root2->left != u_nullptr))
                    || ((root->right != u_nullptr && root2->right == u_nullptr)
                    || (root->right == u_nullptr && root2->right != u_nullptr)))
                        return (false);

                if (root->left != u_nullptr && root->left != u_nullptr)
                    if (_BST_operator_strict_equal(root->left, root2->left) == false)
                        return (false);
                if (root->right != u_nullptr && root->right != u_nullptr)
                    if (_BST_operator_strict_equal(root->right, root2->right) == false)
                        return (false);
                return (true);
            }
    };

    /*
    ** @brief An overload operator to check
    ** if to binary search tree has the same values.
    **
    ** @param lhs, rhs the binary search tree to compare.
    ** @return true if the trees are the sames, otherwise false.
    */
    template<typename T>
    bool operator==(ft::Binary_search_tree<T> lhs, ft::Binary_search_tree<T> rhs)
    {
        return (lhs.operator==(rhs));
    }

} /* End of namespace */

# endif