/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_search_tree.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchallie <rchallie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 17:12:26 by rchallie          #+#    #+#             */
/*   Updated: 2020/12/10 21:32:14 by rchallie         ###   ########.fr       */
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
			typedef ft::BST_const_iterator<Node, Compare> const_iterator;
			
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
			** It's at that use the tree to delete all nodes.
			*/
			~Binary_search_tree ()
			{
				_node_alloc.destroy(_last_node);
				_node_alloc.deallocate(_last_node, 1);	
			}

			/*
			** @brief Insert a new node that contain "to_insert".
			*/
			ft::pair<iterator, bool> insertPair(value_type to_insert)
			{
				Node * new_node = _node_alloc.allocate(1);
				Node * prev_node = _last_node;
				Node * start_node = _last_node->parent;

				// side == false = left; side == true = right;
				bool side = true;

				while (start_node != _last_node)
				{
					int curkey = start_node->value.first;
					if (curkey == to_insert.first)
						return (ft::make_pair(iterator(start_node, _last_node), false));
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
				
				_last_node->left = _BST_get_lower_node(_last_node->parent);
				_last_node->right = _BST_get_higher_node(_last_node->parent);
				_last_node->value.first += 1;
				return (ft::make_pair(iterator(new_node, _last_node), true));
			}

			/*
			** @brief need a pair create like : make_pair(key, mapped_type())
			*/
			void removeByKey(value_type to_remove)
			{ _removeByKey(_last_node->parent, to_remove); }

			/*
			** @brief need a pair create like : make_pair(key, mapped_type())
			*/
			node_pointer searchByKey(value_type to_remove)
			{
				node_pointer node = _last_node->parent;

				while (node != _last_node)
				{
					if (node->value.first == to_remove.first)
						return (node);
					if (node->value.first > to_remove.first)
						node = node->left;
					else
						node = node->right;
				}
				return (node);
			}

			/*
			** @brief Swap this elements with "x" elements
			*/
			void swap(self& x)
			{
				if (&x == this)
					return ;
				
				node_pointer save = this->_last_node;
				this->_last_node = x._last_node;
				x._last_node = save;
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
			node_pointer _BST_get_lower_node(node_pointer root)
			{
				while (root != _last_node && root->left != _last_node)
					root = root->left;
				return (root);
			}

			/*
			** @brief Give node pointer on higher key.
			*/
			node_pointer _BST_get_higher_node(node_pointer root)
			{
				while (root != _last_node && root->right != _last_node)
					root = root->right;
				return (root);
			}

			/*
			** @brief Used to re set link between node is necessary, and
			** delete node.
			*/
			void _replaceNodeInParent(node_pointer node, node_pointer new_node)
			{
				if (node->parent != _last_node)
				{
					if (_last_node->parent == node)
						_last_node->parent = new_node;

					if (node == node->parent->left)
						node->parent->left = new_node;
					else
						node->parent->right = new_node;
				}
				else
					_last_node->parent = new_node;

				_last_node->left = _BST_get_lower_node(_last_node->parent);
				_last_node->right = _BST_get_higher_node(_last_node->parent);
				_last_node->value.first -= 1;
				
				new_node->parent = node->parent;
				
				_node_alloc.destroy(node);
				_node_alloc.deallocate(node, 1);
			}

			/*
			** @brief used to move replacer node and re set all link between
			** node where it's necessary and delete to_remove.
			*/
			void _replaceDoubleChildren(node_pointer& to_remove, node_pointer new_node)
			{
				if (new_node->parent != _last_node)
				{
					if (new_node->parent != to_remove)
						new_node->parent->left = new_node->right;
				}
				
				new_node->parent = to_remove->parent;
				if (to_remove->left != new_node)
					new_node->left = to_remove->left;
				if (to_remove->right != new_node)
					new_node->right = to_remove->right;

				if (to_remove->parent != _last_node)
				{
					if (to_remove->parent->left == to_remove)
						to_remove->parent->left = new_node;
					else if (to_remove->parent->right == to_remove)
						to_remove->parent->right = new_node;
				}
				else
					_last_node->parent = new_node;
					
				if (to_remove->left != _last_node && to_remove->left != new_node)
					to_remove->left->parent = new_node;
				if (to_remove->right != _last_node && to_remove->right != new_node)
					to_remove->right->parent = new_node;

				if (to_remove->parent != _last_node)
				{
					to_remove->left = _last_node;
					to_remove->right = _last_node;
					to_remove->parent = new_node;
				}

				_last_node->left = _BST_get_lower_node(_last_node->parent);
				_last_node->right = _BST_get_higher_node(_last_node->parent);
				_last_node->value.first -= 1;

				_node_alloc.destroy(to_remove);
				_node_alloc.deallocate(to_remove, 1);
			}

			/*
			** @brief need a pair create like : make_pair(key, mapped_type())
			*/
			void _removeByKey(node_pointer node, value_type to_remove)
			{
				if (to_remove.first < node->value.first)
				{
					_removeByKey(node->left, to_remove);
					return ;
				}

				if (to_remove.first > node->value.first)
				{
					_removeByKey(node->right, to_remove);
					return ;
				}

				if (node->left != _last_node && node->right != _last_node)
				{
					node_pointer successor = _BST_get_lower_node(node->right);
					_replaceDoubleChildren(node, successor);
					return ;
				}
				else if (node->left != _last_node)
					_replaceNodeInParent(node, node->left);
				else if (node->right != _last_node)
					_replaceNodeInParent(node, node->right);
				else
					_replaceNodeInParent(node, _last_node);
			}
	};
}

#endif