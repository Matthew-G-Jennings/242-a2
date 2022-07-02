#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "mylib.h"

#define IS_BLACK(x) ((NULL == (x)) || (BLACK == (x)->colour))
#define IS_RED(x) ((NULL != (x)) && (RED == (x)->colour))

/**
 * Defines a tree data structure. Tree can be either a BST
 * or RBT depending on arugments passed at initialization.
 *
 * @author Jeremy Shanks, Will Johnstone, Matthew Jennings
 */

/**
 * Defines an colour for each node.
 */
typedef enum { RED, BLACK } node_colour;

/**
 * Defines a node of the tree.
 */
struct tree_node {
    char *key;
    int frequency;
    node_colour colour;
    tree left;
    tree right;
};

/**
 * Orchestrates the rebalancing of the tree to ensure
 * the rules of a red black tree are being followed.
 *
 * @param t tree to balance.
 *
 * @return the rebalanced tree.
 */
static tree tree_fix(tree t){
    if(IS_RED(t->left) && IS_RED(t->left->left)){
        /* t->right is b */
        if(IS_RED(t->right)){
        /* colour root (R) red and children (A, B) black */
        t->colour = RED;
        t->left->colour = BLACK;
        t->right->colour = BLACK;
        } else { /* t->right = b = must be BLACK */
        /* right-rotate root (R), colour new root (A) black, and new
        child (R) red */
        t->left->colour = BLACK;
        t->colour = RED;
        t = tree_rotate_right(t);
        }
    } else if(IS_RED(t->left) && IS_RED(t->left->right)){
        /* t->right is b */
        if(IS_RED(t->right)){
            /* colour root (R) red and children (A, B) black */
            t->colour = RED;
            t->left->colour = BLACK;
            t->right->colour = BLACK;
        } else { /* t->right = b = must be BLACK */
            /* left-rotate left child (A) , right-rotate
            root (R), colour root (D) black and new
            child (R) red */
            t->left->right->colour = BLACK;
            t->colour = RED;
            t->left = tree_rotate_left(t->left);
            t = tree_rotate_right(t);
        }
    } else if(IS_RED(t->right) && IS_RED(t->right->left)){
        /* t->left is A */
        if(IS_RED(t->left)){
            /* colour root (R) red and children (A,B) black */
            t->colour = RED;
            t->left->colour = BLACK;
            t->right->colour = BLACK;
        } else { /* t->left = b = must be BLACK */
            /* right-rotate right child (B), left-rotate
            root (R), colour root (E) black and new
            child (R) red */
            t->right->left->colour = BLACK;
            t->colour = RED;
            t->right = tree_rotate_right(t->right);
            t = tree_rotate_left(t);
        }
    } else if(IS_RED(t->right) && IS_RED(t->right->right)){
        /* t->left is A */
        if(IS_RED(t->left)){
            /* colour root (R) red and children (A,B) black */
            t->colour = RED;
            t->left->colour = BLACK;
            t->right->colour = BLACK;
        } else { /* t->right = b = must be BLACK */
            /* left-rotate root (R), colour root (B)
            black and new child (R) red */
            t->right->colour = BLACK;
            t->colour = RED;
            t = tree_rotate_left(t);
        }
    }
    return t;
}

/**
 * Insertion function. Inserts a given string into a given tree ADT.
 * Allocates memory as required. Used internally only, accessed using
 * tree_insert.
 *
 * @param t tree ADT to insert in to
 * @param str the string to insert
 */
static tree tree_insert_aux(tree t, char *str){
    if(t == NULL){
        /* printf("\twhere im at is currently null so writing \"%s\" right
           here\n", str); */
        t = emalloc(sizeof *t);
        t->left = NULL;
        t->right = NULL;
        t->key = emalloc((strlen(str) + 1) * sizeof t->key[0]);
        t->colour = RED;
        t->frequency = 1;
        strcpy(t->key, str);
        if(tree_type == RBT){
            t = tree_fix(t);
        }
        return t;
    }

    if(strcmp(t->key, str) == 0){
        /* whenever a duplicate is added to the tree, increment frequency */
        t->frequency = t->frequency + 1;
        return t;
    } else if(strcmp(t->key, str) > 0){
        /* printf("\tthe key \"%s\" is less than the key \"%s\" so we are
           sending \"%s\" to t->left\n", str, t->key, str); */
        t->left = tree_insert_aux(t->left, str);
        if(tree_type == RBT){
            t = tree_fix(t);
        }
        return t;
    } else {
        /* printf("\tthe key \"%s\" is greater than the key \"%s\" so we
           are sending \"%s\" to t->right\n", str, t->key, str); */
        t->right = tree_insert_aux(t->right, str);
        if(tree_type == RBT){
            t = tree_fix(t);
        }
        return t;
    }
}

/**
 * Sets the colour field of a given node to BLACK.
 *
 * @param t the node to make BLACK.
 */
static tree make_black(tree t){
    t->colour = BLACK;
    return t;
}

/**
 * Creates a new tree and allocates memory as required.
 *
 * @param type what type of tree ADT.
 *
 * @return the newly created tree table.
 */
tree tree_new(tree_t type){
    if(type == RBT){
        tree_type = RBT;
    }
    return NULL;
}

/**
 * Frees all memory that has been malloced associated with
 * the given tree ADT.
 *
 * @param t tree to free memory of.
 */
tree tree_free(tree t){
    if(t == NULL){
        return NULL;
    } else {
        tree_free(t->left);
        tree_free(t->right);
        free(t->key);
        free(t);
        return NULL;
    }
}

/**
 * Visible insert function. Calls tree_insert_aux to perform
 * the actual insertion. Then returns the root node, ensuring
 * it is black.
 *
 * @param t tree ADT to insert in to
 * @param str the string to insert
 */
tree tree_insert(tree t, char *str){
    t = tree_insert_aux(t, str);
    return make_black(t);
}

/**
 * Iterates through the tree ADT hitting
 * every key in ascending key order.
 *
 * @param t the tree ADT to print
 * @param f utility function to perform on each tree node
 */
void tree_inorder(tree t, void f(int freq, char *str)){
    if(t == NULL){
        return;
    }
    tree_inorder(t->left, f);
    f(t->frequency, t->key);
    tree_inorder(t->right, f);
}

/**
 * Iterates through the tree by visiting
 * every node in such a way that the "shape" of the tree
 * is exposed.
 *
 * @param t the tree ADT to print.
 * @param f utility function to perform on each tree node.
 */
void tree_preorder(tree t, void f(int freq, char *str)){
    /* must be empty so stop what you doing */
    if(t == NULL){
        return;
    }
    f(t->frequency, t->key);
    tree_preorder(t->left, f);
    tree_preorder(t->right, f);
}

/**
 * Rotating right moves branches from the left to
 * the right.
 *
 * @param t tree ADT to rotate around as the pivot.
 *
 * @return rotated ADT around pivot.
 */
tree tree_rotate_right(tree t){
    tree temp = t;
    t = t->left;
    temp->left = t->right;
    t->right = temp;
    return t;
}

/**
 * Rotating left moves branches from the right to
 * the left.
 *
 * @param t tree ADT to rotate around as the pivot.
 *
 * @return rotated ADT around pivot.
 */
tree tree_rotate_left(tree t){
    tree temp = t;
    t = t->right;
    temp->right = t->left;
    t->left = temp;
    return t;
}

/**
 * Returns the length of the longest path
 * between the root node and the furthest
 * leaf node.
 *
 * @param t tree ADT to measure depth on.
 *
 * @return integer representing the depth.
 */
int tree_depth(tree t){
    if (t == NULL){
        return -1;
    }else{
        int depthleft = tree_depth(t->left);
        int depthright = tree_depth(t->right);
        if (depthleft>depthright){
            return depthleft+1;
        }else{
            return depthright+1;
        }
    }
}

/**
 * Searches a given tree ADT for a given word. Used for
 * the dictionary functionality.
 *
 * @param t tree ADT to search.
 * @param str string variable to search.
 *
 * @return if the string is present in the ADT returns 1.
 */
int tree_search(tree t, char *str){
    if(t == NULL){
        return 0;
    }
    else if(strcmp(t->key, str) == 0){
        return 1;
    }
    else{
        if(strcmp(t->key, str) > 0){
            return tree_search(t->left, str);
        }else{
            return tree_search(t->right, str);
        }
    }
}

/**
 * Traverses the tree writing a DOT description about connections, and
 * possibly colours, to the given output stream.
 *
 * @param t the tree to output a DOT description of.
 * @param out the stream to write the DOT output to.
 */
static void tree_output_dot_aux(tree t, FILE *out) {
    if (t == NULL) {
        return;
    }
    if(t->key != NULL) {
        fprintf(out, "\"%s\"[label=\"{<f0>%s:%d|{<f1>|<f2>}}\"color=%s];\n",
                t->key, t->key, t->frequency,
                (RBT == tree_type && RED == t->colour) ? "red":"black");
    }
    if(t->left != NULL) {
        tree_output_dot_aux(t->left, out);
        fprintf(out, "\"%s\":f1 -> \"%s\":f0;\n", t->key, t->left->key);
    }
    if(t->right != NULL) {
        tree_output_dot_aux(t->right, out);
        fprintf(out, "\"%s\":f2 -> \"%s\":f0;\n", t->key, t->right->key);
    }
}

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
void tree_output_dot(tree t, FILE *out) {
    fprintf(out, "digraph tree {\nnode [shape = Mrecord, penwidth = 2];\n");
    tree_output_dot_aux(t, out);
    fprintf(out, "}\n");
}
