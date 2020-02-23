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
 * @see    find_min
 * @brief  Find minimal element value which the node has 
 * @param  root -- root of binary tree
 * @return the node which has minimal element value, or NULL
 * *******************************************************************************/
binary_tree_t *find_min(binary_tree_t *root)
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
