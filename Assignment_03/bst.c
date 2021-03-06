/*
 * This file is where you should implement your binary search tree.  It already
 * contains skeletons of the functions you need to implement (along with
 * documentation for each function).  Feel free to implement any additional
 * functions you might need.  Also, don't forget to include your name and
 * @oregonstate.edu email address below.
 *
 * Name: Rudy Peralta
 * Email: peraltar@oregonstate.edu
 */

#include <stdlib.h>

#include "bst.h"
#include "stack.h"

typedef struct bst_node bstNode;
typedef struct bst BST;

/*
 * This structure represents a single node in a BST.  In addition to containing
 * pointers to its two child nodes (i.e. `left` and `right`), it contains two
 * fields representing the data stored at this node.  The `key` field is an
 * integer value that should be used as an identifier for the data in this
 * node.  Nodes in the BST should be ordered based on this `key` field.  The
 * `value` field stores data associated with the key.
 *
 * You should not modify this structure.
 */
struct bst_node {
    int key;
    void *value;
    struct bst_node *left;
    struct bst_node *right;
};


/*
 * This structure represents an entire BST.  It specifically contains a
 * reference to the root node of the tree.
 *
 * You should not modify this structure.
 */
struct bst {
    struct bst_node *root;
};

/*
 * This function should allocate and initialize a new, empty, BST and return
 * a pointer to it.
 */
struct bst *bst_create() {
    BST *new_bst_root = (BST *) malloc(sizeof(BST));
    new_bst_root->root = NULL;
    return new_bst_root;
}


/**
 * Params:
 *  Given a bst_node from a root BST. it'll go and recursively delete what's currently in the tree. This wont free the main node, I don't think, so be careful with that chief.
 *  @param bst_node
 */
void bst_node_free(bstNode *bst_node) {

    if (bst_node == NULL) {
        return;
    }
    bst_node_free(bst_node->right);
    bst_node_free(bst_node->left);

    free(bst_node);
}

/*
 * This function should free the memory associated with a BST.  While this
 * function should up all memory used in the BST itself, it should not free
 * any memory allocated to the pointer values stored in the BST.  This is the
 * responsibility of the caller.
 *
 * Params:
 *   bst - the BST to be destroyed.  May not be NULL.
 */
void bst_free(struct bst *bst) {
    // if it's not an empty tree, delete the left and the right subtree recursively til it reaches the end.
    bst_node_free(bst->root->right);
    bst_node_free(bst->root->left);

    free(bst->root);
    free(bst);
}

int _bst_node_size(bstNode *bst_node) {
    if (bst_node == NULL) {
        return 0;
    }
    return 1 + _bst_node_size(bst_node->left) + _bst_node_size(bst_node->right);
}

/*
 * This function should return the total number of elements stored in a given
 * BST.
 *
 * Params:
 *   bst - the BST whose elements are to be counted.  May not be NULL.
 */
int bst_size(struct bst *bst) {
    if (bst->root == NULL) {
        return 0;
    }
    return 1 + _bst_node_size(bst->root->left) + _bst_node_size(bst->root->right);
}

bstNode *_bst_create_node(void *data, int key) {
    bstNode *new_node = (bstNode *) malloc(sizeof(bstNode));
    new_node->value = data;
    new_node->key = key;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

/*
 * This function should insert a new key/value pair into the BST.  The key
 * should be used to order the key/value pair with respect to the other data
 * stored in the BST.  The value should be stored along with the key, once the
 * right location in the tree is found.
 *
 * Params:
 *   bst - the BST into which a new key/value pair is to be inserted.  May not
 *     be NULL.
 *   key - an integer value that should be used to order the key/value pair
 *     being inserted with respect to the other data in the BST.
 *   value - the value being inserted into the BST.  This should be stored in
 *     the BST alongside the key.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void bst_insert(struct bst *bst, int key, void *value) {

    if (bst->root == NULL) {
        bst->root = _bst_create_node(value, key); // should only
        return;
    }
    bstNode *previous = NULL;     // Holds previous node.
    bstNode *parent = NULL;       // P
    bstNode *current = bst->root; // N
    while (current != NULL) {
        parent = current;
        if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }

    }
    if (key < parent->key) {
        parent->left = _bst_create_node(value, key);
    } else {
        parent->right = _bst_create_node(value, key);
    }
}

/**
 * Finds the node with the smallest key in the tree. Starts from the p_node.
 * @param p_node
 * @return
 */
bstNode *_bst_smallest(bstNode *p_node) { // If the tree was made well, the smallest value is on the leftmost leaf.
    bstNode *current = p_node;

    // Find the leftmost node in the tree.
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

bstNode *_bst_delete_node(bstNode *root, int key) {
    // base case is that the tree is empty.
    if (root == NULL) {
        return root;
    }

    // Basically just a way to find the item that needs to be deleted recursively.
    if (key < root->key) { // This checks if the key is to the left.
        root->left = _bst_delete_node(root->left, key);
    } else if (key > root->key) { // Checks for the opposite.
        root->right = _bst_delete_node(root->right, key);
    } else { // Key is the same as root key. Which means we found the correct item. So start safely deleting stuff.
        if (root->left == NULL) {
            bstNode *p_temp = root->right;
            free(root);
            return p_temp;
        } else if (root->right == NULL) {
            bstNode *p_temp = root->right;
            free(root);
            return p_temp;
        }

        // If a node has two children:
        //  - Get the smallest value in the right Sub tree, which will be in the leftmost node.
        bstNode *smallest_node = _bst_smallest(root->right);

        // Copy from successor to current node.
        root->key = smallest_node->key;

        // Delete the correct node.
        root->right = _bst_delete_node(root->right, smallest_node->key);
    }
    return root;
}


/*
 * This function should remove a key/value pair with a specified key from a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function should remove the first one it encounters (i.e. the one closest to
 * the root of the tree).
 *
 * Params:
 *   bst - the BST from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair to be removed from the BST.
 */
void bst_remove(struct bst *bst, int key) {
    // send the whole tree into the thing.
    _bst_delete_node(bst->root, key);
}

/*
 * This function should return the value associated with a specified key in a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function should return the first one it encounters (i.e. the one closest to
 * the root of the tree).  If the BST does not contain the specified key, this
 * function should return NULL.
 *
 * Params:
 *   bst - the BST from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair whose value is to be returned.
 *
 * Return:
 *   Should return the value associated with the key `key` in `bst` or NULL,
 *   if the key `key` was not found in `bst`.
 */
void *bst_get(struct bst *bst, int key) {
    bstNode *current = bst->root; // N
    while (current != NULL) {
        if (current->key == key) {
            return current->value;
        } else if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return NULL;
}

/*****************************************************************************
 **
 ** BST iterator definition (extra credit only)
 **
 *****************************************************************************/

/*
 * Structure used to represent a binary search tree iterator.  It contains
 * only a reference to a stack to be used to implement the iterator.
 *
 * You should not modify this structure.
 */
struct bst_iterator {
    struct stack *stack;
};

/*
 * This function should allocate and initialize an iterator over a specified
 * BST and return a pointer to that iterator.
 *
 * Params:
 *   bst - the BST for over which to create an iterator.  May not be NULL.
 */
struct bst_iterator *bst_iterator_create(struct bst *bst) {
    return NULL;
}

/*
 * This function should free all memory allocated to a given BST iterator.
 * It should NOT free any memory associated with the BST itself.  This is the
 * responsibility of the caller.
 *
 * Params:
 *   iter - the BST iterator to be destroyed.  May not be NULL.
 */
void bst_iterator_free(struct bst_iterator *iter) {
    return;
}

/*
 * This function should indicate whether a given BST iterator has more nodes
 * to visit.  It should specifically return 1 (true) if the iterator has at
 * least one more node to visit or 0 (false) if it does not have any more
 * nodes to visit.
 *
 * Param:
 *   iter - the BST iterator to be checked for remaining nodes to visit.  May
 *     not be NULL.
 */
int bst_iterator_has_next(struct bst_iterator *iter) {
    return 0;
}

/*
 * This function should return both the value and key associated with the
 * current node pointed to by the specified BST iterator and advnce the
 * iterator to point to the next node in the BST (in in-order order).
 *
 * Because a function can't return two things, the key associated with the
 * current node should be returned the normal way, while its value should be
 * returned via the argument `value`.  Specifically, the argument `value`
 * is a pointer to a void pointer.  The current BST node's value (a void
 * pointer) should be stored at the address represented by `value` (i.e. by
 * dereferencing `value`).  This will look something like this:
 *
 *   *value = current_node->value;
 *
 * Parameters:
 *   iter - BST iterator.  The key and value associated with this iterator's
 *     current node should be returned, and the iterator should be updated to
 *     point to the next node in the BST (in in-order order).  May not be NULL.
 *   value - pointer at which the current BST node's value should be stored
 *     before this function returns.
 *
 * Return:
 *   This function should return the key associated with the current BST node
 *   pointed to by `iter`.
 */
int bst_iterator_next(struct bst_iterator *iter, void **value) {
    if (value) {
        *value = NULL;
    }
    return 0;
}
