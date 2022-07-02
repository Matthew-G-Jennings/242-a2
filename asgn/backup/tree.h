#ifndef TREE_H_
#define TREE_H_

#include <stdio.h>

/**
 * Defines a tree data structure. Tree can be either a BST
 * or RBT depending on arugments passed at initialization.
 *
 * @author Jeremy Shanks, Will Johnstone, Matthew Jennings
 */

/* Defines a tree stucture. */
typedef struct tree_node *tree;

/* Defines an enumerated type to determine type of tree ADT. */
typedef enum tree_e { BST, RBT } tree_t;

static tree_t tree_type = BST;

/**
 * Frees all memory that has been malloced associated with
 * the given tree.
 *
 * @param t tree to free.
 */
extern tree tree_free(tree t);

/**
 * Creates a new tree and allocates memory as required.
 *
 * @param type what type of tree ADT.
 *
 * @return the newly created tree table.
 */
extern tree tree_new(tree_t type);

/**
 * Insertion function. Inserts a given string into a given tree ADT.
 * Allocates memory as required.
 *
 * @param t tree ADT to insert in to.
 * @param str the string to insert.
 */
extern tree tree_insert(tree t, char *str);

/**
 * Searches a given tree ADT for a given word. Used for
 * the dictionary functionality.
 *
 * @param t tree ADT to search.
 * @param str string variable to search.
 *
 * @return if the string is present in the ADT returns 1.
 */
extern int tree_search(tree t, char *str);

/**
 * Iterates through the tree ADT hitting
 * every key in ascending key order.
 *
 * @param t the tree ADT to print.
 * @param f utility function to perform on each tree node.
 */
extern void tree_inorder(tree t, void f(int freq, char *str));

/**
 * Iterates through the tree by visiting
 * every node in such a way that the "shape" of the tree
 * is exposed.
 *
 * @param t the tree ADT to print.
 * @param f utility function to perform on each tree node.
 */
extern void tree_preorder(tree t, void f(int freq, char *str));

/**
 * Rotating left moves branches from the right to
 * the left.
 *
 * @param t tree ADT to rotate around as the pivot.
 *
 * @return rotated ADT around pivot.
 */
extern tree tree_rotate_left(tree t);

/**
 * Rotating right moves branches from the left to
 * the right.
 *
 * @param t tree ADT to rotate around as the pivot.
 *
 * @return rotated ADT around pivot.
 */
extern tree tree_rotate_right(tree t);

/**
 * Returns the length of the longest path
 * between the root node and the furthest
 * leaf node.
 *
 * @param t tree ADT to measure depth on.
 *
 * @return integer representing the depth.
 */
extern int tree_depth(tree t);

/**
 * Output a DOT description of this tree to the given output stream.
 * DOT is a plain text graph description language (see www.graphviz.org).
 * You can create a viewable graph with the command
 *
 *    dot -Tpdf < dotfile > dotfile.pdf
 *
 * where 'dotfile' is a file that has been written by tree_output_dot()
 *
 * You can also use png, ps, jpg, svg... instead of pdf
 *
 * @param t the tree to output the DOT description of.
 * @param out the stream to write the DOT description to.
 */
extern void tree_output_dot(tree t, FILE *out);

#endif
