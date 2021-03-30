/*
 * This file is where you should implement your linked list.  It already
 * contains skeletons of the functions you need to implement (along with
 * documentation for each function).  Feel free to implement any additional
 * functions you might need.  Also, don't forget to include your name and
 * @oregonstate.edu email address below.
 *
 * Name: Rudy Peralta
 * Email: peraltar@oregonstate.edu
 */

#include <stdlib.h>
#include <stdio.h>
#include "list.h"

typedef struct link Link;
typedef struct list List;

/*
 * This structure is used to represent a single link in a singly-linked list.
 * It is not defined in ll.h, so it is not visible to the user.  You should not
 * modify this structure.
 */
struct link {
    void *val;
    struct link *next;
};

/*
 * This structure is used to represent an entire singly-linked list.  Note that
 * we're keeping track of just the head of the list here, for simplicity.
 */
struct list {
    struct link *head;
};

/*
 * This function should allocate and initialize a new, empty linked list and
 * return a pointer to it.
 */
List *list_create() {
    List *head = (List *) calloc(1, sizeof(List));
    return head;
}

/*
 * This function should free the memory associated with a linked list.  In
 * particular, while this function should up all memory used in the list
 * itself (i.e. the space allocated for all of the individual links), it should
 * not free any memory allocated to the pointer values stored in the list.  In
 * other words, this function does not need to free the `val` fields of the
 * list's links.
 *
 * Params:
 *   list - the linked list to be destroyed.  May not be NULL.
 */
void list_free(List *list) { // list should probs be head.
    Link* tmp;
    while (list->head != NULL) {
        tmp = list->head;
        list->head = list->head->next;
        free(tmp);
    }
    return;
}

/*
 * This function should insert a new value into a given linked list.
 * Importantly, this function will need to allocate a new `struct link` in
 * which to store the new value and add that link at the head of the list.  For
 * simplicity, this function should only insert elements at the *beginning* of
 * the list.  In other words, it should always insert the new element as the
 * head of the list.
 *
 * Params:
 *   list - the linked list into which to insert an element.  May not be NULL.
 *   val - the value to be inserted.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void list_insert(struct list *list, void *val) {
    // Gods I want to rename list into node so bad... but it's not actually the node, just the container of the nodes.
    Link *newLink = (Link *) malloc(sizeof(Link)); // this creates a new link/node in te chain.
    // insert the data
    newLink->val = val;
    // make the next of the new node as the head ref.
    newLink->next = list->head;
    // move to head link to the beginning of the list now/make the beginning the head.
    list->head = newLink;
    return;
}

/*
 * This function should remove an element with a specified value from a given
 * linked list.  Importantly, if the specified value appears multiple times in
 * the list, the function should only remove the *first* instance of that
 * value (i.e. the one nearest to the head of the list).  For example, if a
 * list stores pointers to integers and contains two instances of the value 4,
 * only the first of those values should be removed, and the other one should
 * remain in the list.  Importantly, this function will also need to free the
 * memory held by the link being removed (it does not need to free the stored
 * value itself, just the link).
 *
 * This function will be passed a *function pointer* called `cmp` that you
 * should use to compare the value `val` to be removed with the values stored
 * in the list to determine which element (if any) to remove.  The cmp function
 * (which will be passed to list_remove() when it's called, so you don't have
 * to worry about writing it yourself) should be passed two void* values,
 * `val` and a value stored in the list against which to compare `val`.  If
 * the two values should be considered as equal, then the function will return
 * 0, and if the two values should be considered as not equal, then the
 * function will return a non-zero value.  For example, part of your code here
 * might look something like this (assuming you're comparing `val` to the `val`
 * field of a specific list link):
 *
 * if (cmp(val, link->val) == 0) {
 *   // Remove link from the list.
 * }
 *
 * For more on function pointers, refer to this tutorial:
 *   https://www.cprogramming.com/tutorial/function-pointers.html
 *
 * Params:
 *   list - the linked list from which to remove an element.  May not be NULL.
 *   val - the value to be removed.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 *   cmp - pointer to a function that can be passed two void* values from
 *     to compare them for equality, as described above.  If the two values
 *     passed are to be considered equal, this function should return 0.
 *     Otherwise, it should return a non-zero value.
 */
void list_remove(struct list *list, void *val, int (*cmp)(void *a, void *b)) {
    Link* temp = list->head;
    Link* prev;
    // get the head node stored.
    if(temp != NULL && cmp(val, temp->val) == 0){ // The key exists here.
        list->head = temp->next; // change head.
        free(temp); // free the currently selected head.
        return;
    }
    // Search for the val, and keep prev node in scope.
    while(temp != NULL && cmp(val, temp->val) != 0){
        prev = temp;
        temp = temp->next;
    }
    // the value to search for isn't there.
    if(temp == NULL){
        printf("Key value was not present in linked list.");
        return;
    }
    // unlink link from list.
    prev->next = temp->next;
    free(temp);
}

/*
 * This function should return the position (i.e. the 0-based "index") of the
 * first instance of a specified value within a given linked list.  For
 * example, if the list contains the specified in the 4th and 8th links
 * starting at the head, then this function should return 3 (the 0-based
 * "index" of the 4th link.).  If the value is contained in the head link,
 * then this function should return 0 (the 0-based index of the head link).
 * If the list does not contain the specified value, then this function should
 * return the special value -1.
 *
 * This function will be passed a *function pointer* called `cmp` that you
 * should use to compare the value `val` to be located with the values stored
 * in the list to determine which link (if any) contains `val`.  The cmp
 * function (which will be passed to list_remove() when it's called, so you
 * don't have to worry about writing it yourself) should be passed two void*
 * values, `val` and a value stored in the list against which to compare `val`.
 * If the two values should be considered as equal, then the cmp function will
 * return 0, and if the two values should be considered as not equal, then the
 * cmp function will return a non-zero value.  For example, part of your code
 * here might look something like this (assuming you're comparing `val` to the
 * `val` field of a specific list link):
 *
 * if (cmp(val, link->val) == 0) {
 *   // Return the position of link.
 * }
 *
 * For more on function pointers, refer to this tutorial:
 *   https://www.cprogramming.com/tutorial/function-pointers.html
 *
 * Params:
 *   list - the linked list from which to remove an element.  May not be NULL.
 *   val - the value to be located.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 *   cmp - pointer to a function that can be passed two void* values from
 *     to compare them for equality, as described above.  If the two values
 *     passed are to be considered equal, this function should return 0.
 *     Otherwise, it should return a non-zero value.
 *
 * Return:
 *   This function should return the 0-based position of the first instance of
 *   `val` within `list`, as determined by the function `cmp` (i.e. the closest
 *    such instance to the head of the list) or -1 if `list` does not contain
 *    the value `val`.
 */
int list_position(List* list, void* val, int (*cmp)(void *a, void *b)) {
    Link* head_ptr = list->head;
    int position = 0;
    while(head_ptr != NULL){
        if(cmp(head_ptr->val, val) == 0){
            // the key and the value of the head are the same.
            return position;
        }
        head_ptr = head_ptr->next;
        position++;
    }

    return -1; // Should only reach here if no position has been returned.
}

/*
 * This function should reverse the order of the links in a given linked list.
 * The reversal should be done *in place*, i.e. within the existing list, and
 * new memory should not be allocated to accomplish the reversal.  You should
 * be able to accomplish the reversal with a single pass through the list.
 *
 * Params:
 *   list - the linked list to be reversed.  May not be NULL.  When this
 *     function returns this should contain the reversed list.
 */
void list_reverse(struct list *list) {
    Link* prev = NULL;
    Link* current = list->head;
    Link* next = NULL;
    // I need to keep track of three things, the previous, current, and next.
    // This allows me to change the link of the current node to the previous node,
    // and to keep a pointer pointing to the next link in the chain.
    while(current != NULL){
        next = current->next; // store the next link.
        current->next = prev; // Reverse the current nodes link
        // move the pointers a position ahead. (Next 2 steps)
        prev = current;
        current = next;
    }
    list->head = prev; // obvious, but change the list head to the next traversal.
    return;
}
