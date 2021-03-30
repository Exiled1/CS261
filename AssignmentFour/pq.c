/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name:
 * Email:
 */

#include <stdlib.h>
#include <stdio.h>

#include "pq.h"
#include "dynarray.h"

typedef struct pq PQueue;
typedef struct pq_node Node;

int pq_getLeft(int index);

int pq_getRight(int index);

int pq_getSmallestChildPrioIndex(int currentIndex, PQueue *pQueue);

int pq_getSmallestChildPrio(int smallestIndex, PQueue *pQueue);

struct pq_node {
    int priority;
    void *value;
};

/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 */
struct pq {
    struct dynarray *pq_node;
};


/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq *pq_create() {
    PQueue *pQueue = (PQueue *) malloc(sizeof(PQueue));
    pQueue->pq_node = dynarray_create();
    return pQueue;
}


/*
 * This function should free the memory allocated to a given priority queue.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the priority queue.  That is the responsibility of the caller.
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 */
void pq_free(PQueue *pq) {
    dynarray_free(pq->pq_node); // Free the interior array.
    free(pq); // free the pq.

}


/*
 * This function should return 1 if the specified priority queue is empty and
 * 0 otherwise.
 *
 * Params:
 *   pq - the priority queue whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if pq is empty and 0 otherwise.
 */
int pq_isempty(PQueue *pq) {
    if (dynarray_size(pq->pq_node) == 0) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * Returns the left node index.
 * @param index
 * @return
 */
int pq_getLeft(int index) {
    return (2 * index) + 1;
}

/**
 * returns right node index.
 * @param index
 * @return
 */
int pq_getRight(int index) {
    return (2 * index) + 2;
}

/**
 * returns parent index.
 * @param index
 * @return
 */
int pq_getParent(int index) {
    return (index - 1) / 2;
}

/**
 * returns index of the first open node.
 * @param pQueue
 * @return
 */
int pq_getFirstOpen(PQueue *pQueue) {
    return dynarray_size(pQueue->pq_node); // returns the index of the last pq node.
}


/**
 * Swaps both the arrays at once given an a_index and b_index. (hopefully)
 * @param pQueue
 * @param aIndex
 * @param bIndex
 */
void pq_swap(PQueue *pQueue, int aIndex, int bIndex) {
    /**
     * OKAY, this hurt my brain.
     * Basically, given a pq (which is a dynarray full of void*'s)
     * Swap the void* values at index a and index b.
     * [val1, val2, val3]
     *  ^             ^
     *  |____________|
     * Using dynarray set, which overwrites a value with another value given an index and a value.
     * it should just save the val1 in a temp variable (which is a void*), and then do swap stuff.
     * HOWEVER, I'm wondering that if my void* gets overwritten, is the value still the same, or is
     * it now the overwritten value.
     */
    void *temp = dynarray_get(pQueue->pq_node, aIndex);
    dynarray_set(pQueue->pq_node, aIndex, dynarray_get(pQueue->pq_node, bIndex));
    dynarray_set(pQueue->pq_node, bIndex, temp);
}

/*
 * This function should insert a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, LOWER priority
 * values are assigned to elements with HIGHER priority.  In other words, the
 * element in the priority queue with the LOWEST priority value should be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   value - the value to be inserted into pq.
 *   priority - the priority value to be assigned to the newly-inserted
 *     element.  Note that in this implementation, LOWER priority values
 *     should correspond to elements with HIGHER priority.  In other words,
 *     the element in the priority queue with the LOWEST priority value should
 *     be the FIRST one returned.
 */
void pq_insert(PQueue *pq, void *value, int priority) {
    int currNodeIndex = pq_getFirstOpen(pq); // index of the end of the array = size.
    int parentNodeIndex = pq_getParent(currNodeIndex);

    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->priority = priority;
    newNode->value = value;
    // get's the index of where the new node is going.
    dynarray_insert(pq->pq_node, newNode); // inserts at the first open location.
    // If broken, fix this? but, for now, inserts at same place as the value.
    // Insert @ first open [check]

    Node *parentNode = dynarray_get(pq->pq_node, parentNodeIndex);

    while (newNode->priority < parentNode->priority) {
        // Implements
        pq_swap(pq, currNodeIndex, parentNodeIndex);
        currNodeIndex = parentNodeIndex;
        parentNodeIndex = pq_getParent(currNodeIndex);
        newNode = dynarray_get(pq->pq_node, currNodeIndex);
        parentNode = dynarray_get(pq->pq_node, parentNodeIndex);
    }

}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void *pq_first(PQueue *pq) {
    Node *ret_node = dynarray_get(pq->pq_node, 0);
    return ret_node->value;
    // gets the 0th index of the pq_node which is the values of the dynarray.
}


/*
 * This function should return the priority value of the first item in a
 * priority queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   Should return the priority value of the first item in pq, i.e. the item
 *   with LOWEST priority value.
 */
int pq_first_priority(PQueue *pq) {
    Node *returned_node = dynarray_get(pq->pq_node, 0);
    return returned_node->priority;
}

int pq_getSmallestChildPrioIndex(int currentIndex, PQueue *pQueue) {
    int rightNodeIndex = pq_getRight(currentIndex);
    int leftNodeIndex = pq_getLeft(currentIndex);
    Node *leftNode;
    Node *rightNode;
    int smallestPrioIndex;

    if ((rightNodeIndex >= dynarray_size(pQueue->pq_node)) || leftNodeIndex > dynarray_size(pQueue->pq_node)) { // if it's bigger than the array. return -1.
        return -1;
    } else {
        leftNode = dynarray_get(pQueue->pq_node, leftNodeIndex);
        rightNode = dynarray_get(pQueue->pq_node, rightNodeIndex);
    }

    if (leftNode->priority < rightNode->priority) {
        smallestPrioIndex = leftNodeIndex;
    } else {
        smallestPrioIndex = rightNodeIndex;
    }

    // Compares their priorities, if the left prio is smaller it gives the left index, and vice versa.
    return smallestPrioIndex;
}

int pq_getSmallestChildPrio(int smallestIndex, PQueue *pQueue) {
    Node *smallestNode;
    //printf("Smallest Index: %d\n", smallestIndex);
    smallestNode = dynarray_get(pQueue->pq_node, smallestIndex);
    return smallestNode->priority;
}

/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value, and then remove that item
 * from the queue.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void *pq_remove_first(PQueue *pq) {

    int size = dynarray_size(pq->pq_node); // get how many elements exist.
    Node *currNode = dynarray_get(pq->pq_node, 0); // get root.
    void *value = currNode->value; // point to root value.
    pq_swap(pq, 0, size - 1); // swap root with last element.
    dynarray_remove(pq->pq_node, size - 1); // remove last element. [memory leak, fuck it.]
    if(dynarray_size(pq->pq_node) == 0){
        return value;
    }

    currNode = dynarray_get(pq->pq_node, 0); // gets the new current node after the swap/remove.

    int currNodePrio = currNode->priority;
    //pq_print(pq);
    int currNodeIndex = 0;
    int leftIndex = 1;
    int rightIndex = 2;
    int currChildPrioIndex = 0;
    // ^^ ALways done at the root node.
    int currChildPrioVal = 1; // should give 1:

    // while the left and right indexes aren't bigger than
    // the dynarray size, and the current prio value is > smallest child prio value:
    while ((leftIndex < dynarray_size(pq->pq_node)) && (rightIndex < dynarray_size(pq->pq_node)) && currNodePrio > currChildPrioVal) {
        pq_swap(pq, currChildPrioIndex, currNodeIndex); // swap smallest child with current node.

        currNodeIndex = currChildPrioIndex; // Updates current node's index to be the child's index.

        currNode = dynarray_get(pq->pq_node, currNodeIndex); // Update the current node to be the child.
        currNodePrio = currNode->priority; // Update the current node's priority.

        currChildPrioIndex = pq_getSmallestChildPrioIndex(currNodeIndex, pq); // get the next child's prio index.
        if (currChildPrioIndex == -1) {
            return value;
        }
        currChildPrioVal = pq_getSmallestChildPrio(currChildPrioIndex, pq);
        leftIndex = pq_getLeft(currNodeIndex);
        rightIndex = pq_getRight(currNodeIndex);
    }

    return value;
}

void pq_print(PQueue *pq) {
    int pqSize = dynarray_size(pq->pq_node);
    Node *currentNode;
    printf("PQ Priority: \n");
    for (int i = 0; i < pqSize; ++i) {
        currentNode = dynarray_get(pq->pq_node, i);
        printf("%d ", currentNode->priority);
    }
    printf("\n");
}