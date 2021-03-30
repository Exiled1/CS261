/*
 * This file is where you should implement your queue.  It already contains
 * skeletons of the functions you need to implement (along with documentation
 * for each function).  Feel free to implement any additional functions you
 * might need.  Also, don't forget to include your name and @oregonstate.edu
 * email address below.
 *
 * Name:
 * Email:
 */

#include <stdlib.h>

#include "queue.h"
#include "dynarray.h"

typedef struct queue Queue;

/*
 * This is the structure that will be used to represent a queue.  This
 * structure specifically contains a single field representing a dynamic array
 * that should be used as the underlying data storage for the queue.
 *
 * You should not modify this structure.
 */
struct queue {
    struct dynarray *array;
};

/*
 * This function should allocate and initialize a new, empty queue and return
 * a pointer to it.
 */
Queue *queue_create() {
    Queue* newQueue = malloc(sizeof(Queue));
    newQueue->array = dynarray_create();
    return newQueue;
}

/*
 * This function should free the memory associated with a queue.  While this
 * function should up all memory used in the queue itself, it should not free
 * any memory allocated to the pointer values stored in the queue.  This is the
 * responsibility of the caller.
 *
 * Params:
 *   queue - the queue to be destroyed.  May not be NULL.
 */
void queue_free(Queue *queue) {
    dynarray_free(queue->array);
    free(queue);
}

/*
 * This function should indicate whether a given queue is currently empty.
 * Specifically, it should return 1 if the specified queue is empty (i.e.
 * contains no elements) and 0 otherwise.
 *
 * Params:
 *   queue - the queue whose emptiness is being questioned.  May not be NULL.
 */
int queue_isempty(Queue *queue) {
    if(dynarray_is_empty(queue->array) == 1){
        return 1;
    }else{
        return 0;
    }
}

/*
 * This function should enqueue a new value into a given queue.  The value to
 * be enqueued is specified as a void pointer.  This function must have O(1)
 * average runtime complexity.
 *
 * Params:
 *   queue - the queue into which a value is to be enqueued.  May not be NULL.
 *   val - the value to be enqueued.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void queue_enqueue(Queue *queue, void *val) {
    // Enqueue adds a value to the end of the array.
    dynarray_insert(queue->array, val);
}

/*
 * This function should return the value stored at the front of a given queue
 * *without* removing that value.  This function must have O(1) average runtime
 * complexity.
 *
 * Params:
 *   queue - the queue from which to query the front value.  May not be NULL.
 */
void *queue_front(Queue *queue) {
    return dynarray_get(queue->array, 0);
}

/*
 * This function should dequeue a value from a given queue and return the
 * dequeued value.  This function must have O(1) average runtime complexity.
 *
 * Params:
 *   queue - the queue from which a value is to be dequeued.  May not be NULL.
 *
 * Return:
 *   This function should return the value that was dequeued.
 */
void *queue_dequeue(Queue *queue) {
    void* data = dynarray_get(queue->array, 0);
    dynarray_remove(queue->array, 0);
    return data;
}
