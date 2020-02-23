#ifndef BINARY_TREE_H_
#define BINARY_TREE_H_

binary_tree_t *make_empty(binary_tree_t *root);
binary_tree_t *find(element_type_t item, binary_tree_t *root);
binary_tree_t *find_min(binary_tree_t *root);
binary_tree_t *find_max(binary_tree_t *root);
binary_tree_t *insert(element_type_t item, binary_tree_t *root);
binary_tree_t *delete(element_type_t item, binary_tree_t *root);
element_type_t retrieve(binary_tree_t *root);


#endif /* BINARY_TREE_H_ */
