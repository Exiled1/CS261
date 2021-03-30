/*
 * This file is where you should implement your stack.  It already contains
 * skeletons of the functions you need to implement (along with documentation
 * for each function).  Feel free to implement any additional functions you
 * might need.  Also, don't forget to include your name and @oregonstate.edu
 * email address below.
 *
 * Name:
 * Email:
 */

#include <stdlib.h>

#include "stack.h"
#include "list.h"


typedef struct stack Stack;
typedef struct list List;


/*
 * This is the structure that will be used to represent a stack.  This
 * structure specifically contains a single field representing a linked list
 * that should be used as the underlying data storage for the stack.
 *
 * You should not modify this structure.
 */
struct stack {
    List *list;
};


/*
 * This function should allocate and initialize a new, empty stack and return
 * a pointer to it.
 */
Stack *stack_create() {
    Stack *stack = (Stack *) malloc(sizeof(Stack)); // Make a new stack button.
    stack->list = list_create();
    return stack;
}

/*
 * This function should free the memory associated with a stack.  While this
 * function should up all memory used in the stack itself, it should not free
 * any memory allocated to the pointer values stored in the stack.  This is the
 * responsibility of the caller.
 *
 * Params:
 *   stack - the stack to be destroyed.  May not be NULL.
 */
void stack_free(Stack *stack) {
    list_free(stack->list);
    free(stack);
    return;
}

/*
 * This function should indicate whether a given stack is currently empty.
 * Specifically, it should return 1 if the specified stack is empty (i.e.
 * contains no elements) and 0 otherwise.
 *
 * Params:
 *   stack - the stack whose emptiness is being questioned.  May not be NULL.
 */
int stack_isempty(Stack *stack) {
    // Basically this is an if statement that checks if the list inside the stack is null or the stack inside the list is null, if it is, then set flag to 0, 1 otherwise.
    int flag;

    if(list_is_empty(stack->list) == 1){
        flag = 1;
    }else{
        flag = 0;
    }
    return flag;
}

/*
 * This function should push a new value onto a given stack.  The value to be
 * pushed is specified as a void pointer.  This function must have O(1)
 * average runtime complexity.
 *
 * Params:
 *   stack - the stack onto which a value is to be pushed.  May not be NULL.
 *   val - the value to be pushed.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void stack_push(Stack *stack, void *val) {
    list_insert(stack->list, val);
    return;
}

/*
 * This function should return the value stored at the top of a given stack
 * *without* removing that value.  This function must have O(1) average runtime
 * complexity.
 *
 * Params:
 *  stack - the stack from which to query the top value.  May not be NULL.
 * Return:
 *  Head value.
 */
void *stack_top(Stack *stack) {
    return list_get_top_val(stack->list);
}

/*
 * This function should pop a value from a given stack and return the popped
 * value.  This function must have O(1) average runtime complexity.
 *
 * Params:
 *   stack - the stack from which a value is to be popped.  May not be NULL.
 *
 * Return:
 *   This function should return the value that was popped.
 */
void* stack_pop(Stack *stack) {
    void* returnVal = list_remove_head(stack->list);
    return returnVal;
}
