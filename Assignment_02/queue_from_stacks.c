/*
 * This file is where you should implement your queue-from-stacks.  It already
 * contains skeletons of the functions you need to implement (along with
 * documentation for each function).  Feel free to implement any additional
 * functions you might need.  Also, don't forget to include your name and
 * @oregonstate.edu email address below.
 *
 * Name:
 * Email:
 */

#include <stdlib.h>

#include "stack.h"
#include "queue_from_stacks.h"

#define TRUE 1
#define FALSE 0

/*
 * This is the structure that will be used to represent a queue using two
 * stacks.  It specifically contains two fields, each representing a stack.
 * These two stacks should be used together as the underlying data storage for
 * the queue.
 *
 * You should not modify this structure.
 */
struct queue_from_stacks {
    struct stack *s1;
    struct stack *s2;
};

typedef struct queue_from_stacks QueueStack;

/*
 * This function should allocate and initialize a new, empty queue-from-stacks
 * and return a pointer to it.
 */
QueueStack *queue_from_stacks_create() {
    QueueStack *queueStack = malloc(sizeof(QueueStack));
    queueStack->s1 = stack_create();
    queueStack->s2 = stack_create();
    return queueStack;
}

/*
 * This function should free the memory associated with a queue-from-stacks.
 * While this function should up all memory used in the queue-from-stacks
 * itself, it should not free any memory allocated to the pointer values stored
 * in the queue.  This is the responsibility of the caller.
 *
 * Params:
 *   qfs - the queue-from-stacks to be destroyed.  May not be NULL.
 */
void queue_from_stacks_free(QueueStack *qfs) {
    stack_free(qfs->s1);
    stack_free(qfs->s2);
    free(qfs);
}

/*
 * This function should indicate whether a given queue-from-stacks is currently
 * empty.  Specifically, it should return 1 if the specified queue-from-stacks
 * is empty (i.e. contains no elements) and 0 otherwise.
 *
 * Params:
 *   qfs - the queue-from-stacks whose emptiness is being questioned.  May not
 *     be NULL.
 */
int queue_from_stacks_isempty(QueueStack *qfs) {
    return (stack_isempty(qfs->s2) == TRUE && stack_isempty(qfs->s1))
           ? TRUE : FALSE;
}

/*
 * This function should enqueue a new value into a given queue-from-stacks.
 * The value to be enqueued is specified as a void pointer.
 *
 * Params:
 *   qfs - the queue-from-stacks into which a value is to be enqueued.  May not
 *     be NULL.
 *   val - the value to be enqueued.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void queue_from_stacks_enqueue(QueueStack *qfs, void *val) {
    stack_push(qfs->s1, val); // enqueue the value onto the stack.
}

/*
 * This function should return the value stored at the front of a given
 * queue-from-stacks *without* removing that value.
 *
 * Params:
 *   qfs - the queue-from-stacks from which to query the front value.  May not be NULL.
 */
void *queue_from_stacks_front(QueueStack *qfs) {
    void *val;

    if (stack_isempty(qfs->s2) == TRUE) {
        while (stack_isempty(qfs->s1) != TRUE) {
            // While stack 1 isn't empty, push every element into stack 2
            val = stack_pop(qfs->s1);
            stack_push(qfs->s2, val);
        }
    }
    return stack_top(qfs->s2);

}

/*
 * This function should dequeue a value from a given queue-from-stacks and
 * return the dequeued value.
 *
 * Params:
 *   qfs - the queue-from-stacks from which a value is to be dequeued.  May not
 *     be NULL.
 *
 * Return:
 *   This function should return the value that was dequeued.
 */
void *queue_from_stacks_dequeue(QueueStack *qfs) {
    void *val;

    if (stack_isempty(qfs->s2) == TRUE) {
        while (stack_isempty(qfs->s1) != TRUE) {
            // While stack 1 isn't empty, push every element into stack 2
            val = stack_pop(qfs->s1);
            stack_push(qfs->s2, val);
        }
    }
    val = stack_pop(qfs->s2);

    return val;
}
