/** ********************************************************************************
 **
 ** @file    binary_tree.c
 **
 ** @author  Gavin.Bai
 **
 ** @date    2020.02.23
 **
 ** @brief   Implementation for binary tree which do all operations
 ** *******************************************************************************/    

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "common.h"
#include "binary_tree.h"

/* ********************************************************************************
 * @see    make_empty
 * @brief  Make binary tree all nodes are free
 * @param  root -- root of binary tree
 * @return the left, right or root of any node
 * *******************************************************************************/
binary_tree_t *make_empty(binary_tree_t *root)
{
    if (root) {
	make_empty(root->left);
	make_empty(root->right);
	free(root);
    }

    return (NULL);
}

/* ********************************************************************************
 * @see    find
 * @brief  Find the node which has same element value with specified it
 * @param  item -- specified element value
 * @param  root -- root of binary tree
 * @return the node which has same value with specified one, or NULL
 * *******************************************************************************/
binary_tree_t *find(element_type_t item, binary_tree_t *root)
{
    if ( !root) {
	return (NULL);
    }

    if ( item < root->item) {
	return find(item, root->left);
    } else if ( item > root->item) {
	return find(item, root-right);
    } else {
	return (root);
    }
}

/* ********************************************************************************
 * @see    find_min_recur
 * @brief  Find minimal element value which the node has with recursion method
 * @param  root -- root of binary tree
 * @return the node which has minimal element value, or NULL
 * *******************************************************************************/
binary_tree_t *find_min_recur(binary_tree_t *root)
{
    if ( !root) {
	return (NULL);
    }

    if ( !root->left) {
	return (root);
    } else {
	return find_min(root->left);
    }
}

/* ********************************************************************************
 * @see    find_max_recur
 * @brief  Find maxima element value which the node has with recursion method
 * @param  root -- root of binary tree
 * @return the node which has maxima element value, or NULL
 * *******************************************************************************/
binary_tree_t *find_max_recur(binary_tree_t *root)
{
    if ( !root) {
	return (NULL);
    }

    if ( !root->right) {
	return (root);
    } else {
	return find_max(root->right);
    }
}

/* ********************************************************************************
 * @see    find_min_iter
 * @brief  Find minimal element value which the node has with iteration method
 * @param  root -- root of binary tree
 * @return the node which has minimal element value, or NULL
 * *******************************************************************************/
binary_tree_t *find_min_iter(binary_tree_t *root)
{
    if ( !root) {
	while ( NULL != root->left) {
	    root = root->left;
	}
    }

    return (root);
}

/* ********************************************************************************
 * @see    find_max_iter
 * @brief  Find maxima element value which the node has with iteration method
 * @param  root -- root of binary tree
 * @return the node which has maxima element value, or NULL
 * *******************************************************************************/
binary_tree_t *find_max_iter(binary_tree_t *root)
{
    if ( !root) {
	while ( NULL != root->right) {
	    root = root->right;
	}
    }

    return (root);
}

/* ********************************************************************************
 * @see    insert
 * @brief  Insert specific value into the binary tree in right node location
 * @param  item -- item to be inserted into the tree
 * @param  root -- root of binary tree
 * @return the node which has been inserted tree
 * *******************************************************************************/
binary_tree_t *insert(element_type_t item, binary_tree_t *root)
{
    if ( !root) {
	/**
	 * root of tree is NULL
	 */
	root = (binary_tree_t *)malloc(sizeof(binary_tree_t));
	if ( !root) {
	    fprintf(stderr, "[ERROR] malloc new node for the tree fail\n");
	} else {
	    root->item = item;
	    root->left = root->right = NULL;
	}
    } else {
	if ( item < root->item) {
	    root->left = insert(item, root->left);
	} else if ( item > root->item) {
	    root->right = insert(item, root->right);
	}
    }

    return (root);
}

/* ********************************************************************************
 * @see    delete
 * @brief  Delete specific value from the binary tree in right node location
 * @param  item -- item to be deleted from the tree
 * @param  root -- root of binary tree
 * @return the node pointer which has been deleted tree
 * *******************************************************************************/
binary_tree_t *delete(element_type_t item, binary_tree_t *root)
{
    binary_tree_t *ttree = NULL;
    
    if ( !root) {
	return (NULL);
    } else {
	if ( item > root->item) {
	    root->right = delete(item, root->right);
	} else if ( item < root->item) {
	    root->left = delete(item, root->left);
	} else {
	    if ( root->left && root->right) {
		ttree       = find_min_recur(root->right);
		root->item  = ttree->item;
		root->right = delete(root->item, root->right);
	    } else {
		ttree = root;
		if ( !ttree->left) {
		    root = root->right;
		} else if ( !ttree->right) {
		    root = root->left;
		}
		free(ttree);
	    }
	}
    }

    return (root);
}
