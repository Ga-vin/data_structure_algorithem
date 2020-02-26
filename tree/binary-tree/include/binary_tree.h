#ifndef BINARY_TREE_H_
#define BINARY_TREE_H_

/**
 * @struct Definition for binary tree structure
 */
struct _binary_tree {
    element_type_t item;
    struct _binary_tree *left;
    struct _binary_tree *right;
} binary_tree_t;

binary_tree_t *make_empty(binary_tree_t *root);
binary_tree_t *find(element_type_t item, binary_tree_t *root);
binary_tree_t *find_min_recur(binary_tree_t *root);
binary_tree_t *find_max_recur(binary_tree_t *root);
binary_tree_t *find_min_iter(binary_tree_t *root);
binary_tree_t *find_max_iter(binary_tree_t *root);
binary_tree_t *insert(element_type_t item, binary_tree_t *root);
binary_tree_t *delete(element_type_t item, binary_tree_t *root);
element_type_t retrieve(binary_tree_t *root);


#endif /* BINARY_TREE_H_ */
