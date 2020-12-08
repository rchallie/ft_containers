/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_search_tree.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchallie <rchallie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 17:12:26 by rchallie          #+#    #+#             */
/*   Updated: 2020/12/08 16:53:56 by rchallie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_SEARCH_TREE_HPP
# define BINARY_SEARCH_TREE_HPP

#include "./utils.hpp"
#include "./binary_search_tree_iterator.hpp"

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

namespace ft
{
    template <class T, class Compare = ft::less<T>, class Node = ft::BST_Node<T>,
            class Type_Alloc = std::allocator<T>, class Node_Alloc = std::allocator<Node> >
    class Binary_search_tree
    {
        public :

            /* Self type */
            typedef Binary_search_tree  self;

            /* A reference to the self type */
            typedef self&   self_reference;
            
            /* The first template argument */
            typedef T   value_type;

            /* Stored Node type */
            typedef Node node_type;

            /* Pointer to stored node */
            typedef Node *  node_pointer;
            
            /* Node allocator */
            typedef Node_Alloc  node_alloc;

            /* Iterator on stored node */
            typedef ft::BST_iterator<Node, Compare> iterator;

            /* Same than iterator, here for base container template */
            typedef ft::BST_iterator<Node, Compare> const_iterator;
            
            /* Size_t */
            typedef size_t size_type;

            /*
            ** @brief Contruct an empty binary search tree
            */
            Binary_search_tree (const node_alloc& node_alloc_init = node_alloc())
            :
                _node_alloc(node_alloc_init)
            {
                _last_node = _node_alloc.allocate(1);
				_node_alloc.construct(_last_node, Node(_last_node, _last_node, _last_node));
            }

            /*
            ** @brief Insert a new node that contain "to_insert".
            */
            iterator insertPair(value_type to_insert)
            {
                Node * new_node = _node_alloc.allocate(1);
                Node * prev_node = _last_node;
                Node * start_node = _last_node->parent;

                // side == false = left; side == true = right;
                bool side = true;
                bool newone = true;

                while (start_node != _last_node)
                {
                    int curkey = start_node->value.first;
                    if (curkey == to_insert.first)
                    {
                        newone = false;
                        start_node->value.second = to_insert.second;
                        return ;
                    }
                    prev_node = start_node;
                    if (to_insert.first > curkey)
                    {
                        side = true;
                        start_node = start_node->right;
                    }
                    else
                    {
                        side = false;
                        start_node = start_node->left;
                    }
                }
				_node_alloc.construct(new_node, Node(to_insert, prev_node, _last_node, _last_node));
                
                if (prev_node == _last_node)
                    _last_node->parent = new_node;
                else if (side == true)
                    prev_node->right = new_node;
                else
                    prev_node->left = new_node;
                
                _last_node->left = _BST_get_lower_node();
                _last_node->right = _BST_get_higher_node();

                return (make_pair(iterator(new_node, _last_node), newone));
            }

            /*
            ** @brief return max_size of allocator.
            */
            size_type max_size() const
            { return (node_alloc().max_size()); }

            // last_node parent = root of tree, last_node right = last node, last_node left = first node
            node_pointer    _last_node;
            node_alloc      _node_alloc;

            private :

                /*
                ** @brief Give node pointer on lower key.
                */
                node_pointer _BST_get_lower_node()
                {
                    node_pointer root = _last_node->parent;
                    while (root != _last_node && root->left != _last_node)
                        root = root->left;
                    return (root);
                }

                /*
                ** @brief Give node pointer on higher key.
                */
                node_pointer _BST_get_higher_node()
                {
                    node_pointer root = _last_node->parent;
                    while (root != _last_node && root->right != _last_node)
                        root = root->right;
                    return (root);
                }
    };
}

#endif