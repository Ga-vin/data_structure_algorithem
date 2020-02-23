#ifndef COMMON_H_
#define COMMON_H_

/**
 * @def New data type to be used frequently
 */
typedef unsigned int    uint32_t;
typedef uint32_t        element_type_t;

/**
 * @struct Definition for binary tree structure
 */
struct _binary_tree {
    element_type_t item;
    struct _binary_tree *left;
    struct _binary_tree *right;
} binary_tree_t;

#endif /* COMMON_H_ */
