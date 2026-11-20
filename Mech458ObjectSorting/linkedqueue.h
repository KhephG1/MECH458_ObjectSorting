/*
 * linkedqueue.h
 * FIFO queue of classified objects for the ATmega2560 sorting project
 * - Singly linked list with head and tail pointers, each node holding an
 *   element (an ObjectType plus a stage field)
 * - An object is enqueued when the reflective sensor classifies it and
 *   dequeued when the exit sensor sees it, so the queue order matches the
 * order of objects on the belt
 * - Nodes are heap allocated with malloc in initLink() and freed by the
 * caller after dequeue(), or by clearQueue()
 *
 * MECH 458, Fall 2026, Khephren Gould & Clifton Tollefson
 */

#ifndef LINKEDQUEUE_H
#define LINKEDQUEUE_H

#include "myutils.h"

/* element
 * The data stored in one queue node.
 *
 * itemCode: The object type (BLACK, ALUMINIUM, WHITE or STEEL)
 * stage: Additional object state; not currently used by the sorter.
 */
typedef struct
{
    ObjectType itemCode;
    char stage;
} element;

/* link
 * One queue node containing an element and a pointer to the next node toward
 * the tail. The next pointer is NULL for the final node.
 */
typedef struct link
{
    element e;
    struct link *next;
} link;

/* initLink
 * Allocates a new queue node using malloc and points *newLink at it.
 * The next pointer is initialized to NULL, but the element fields are not.
 *
 * newLink: Address of the pointer that receives the allocated node.
 *
 * The caller owns the allocated node and must eventually free it or pass it
 * to enqueue(). The caller should check for NULL in case malloc fails.
 */
void initLink(link **newLink);

/* setup
 * Initializes an empty queue by setting both the head and tail pointers to
 * NULL. Should be called once before using the queue.
 *
 * h: Address of the queue head pointer.
 * t: Address of the queue tail pointer.
 */
void setup(link **h, link **t);

/* clearQueue
 * Removes all nodes from the queue and frees their allocated memory.
 * Both the head and tail pointers are set to NULL after clearing.
 *
 * h: Address of the queue head pointer.
 * t: Address of the queue tail pointer.
 *
 * All nodes previously belonging to the queue are freed.
 */
void clearQueue(link **h, link **t);

/* enqueue
 * Adds a node to the end of the FIFO queue by updating the tail pointer.
 * If the queue is empty, the new node becomes both the head and tail.
 *
 * h: Address of the queue head pointer.
 * t: Address of the queue tail pointer.
 * nL: Address of the pointer to the node being added.
 *
 * The node is transferred to the queue. The caller should not independently
 * free or reuse it while it remains in the queue.
 */
void enqueue(link **h, link **t, link **nL);

/* dequeue
 * Removes the node at the front of the FIFO queue and returns it through
 * deQueuedLink. The node is detached from the queue but is not freed.
 *
 * h: Address of the queue head pointer.
 * deQueuedLink: Address of the pointer that receives the removed node.
 *
 * The caller is responsible for freeing the returned node when finished.
 * If the queue becomes empty, the head pointer is set to NULL.
 */
void dequeue(link **h, link **deQueuedLink);

/* firstValue
 * Returns the element stored in the node at the front of the queue without
 * removing the node.
 *
 * h: Address of the queue head pointer.
 *
 * Returns the element at the head of the queue.
 * The queue must not be empty when this function is called.
 */
element firstValue(link **h);

/* isEmpty
 * Checks whether the queue contains any nodes.
 *
 * h: Address of the queue head pointer.
 *
 * Returns a nonzero value if the queue is empty, or 0 otherwise.
 */
char isEmpty(link **h);

/* size
 * Counts the number of nodes currently stored in the queue.
 *
 * h: Address of the queue head pointer.
 * t: Address of the queue tail pointer.
 *
 * Returns the number of nodes in the queue as an integer.
 */
int size(link **h, link **t);

#endif