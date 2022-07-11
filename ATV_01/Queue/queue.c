#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define SIZE 5;

/*
A queue implements a data structure based on the FIFO principle (First In First Out)
*/

typedef struct Queue
{
    int capacity, size;
    int front, rear;
    int *array;
} Queue;

Queue* createQueue()
{
    Queue* queue = (Queue*)malloc(sizeof(Queue));

    queue->capacity = SIZE;
    queue->size = -1;
    queue->front = queue->size;
    queue->rear = queue->capacity - 1;

    queue->array = (int*)malloc(queue->capacity * sizeof(int));

    return queue;
}

int isEmpty(Queue* queue)
{
    return queue->size == -1;
}

int isFull(Queue* queue)
{
    return queue->size == queue->capacity - 1;
}

void enqueue (Queue* queue, int value)
{
    if (isFull(queue))
    {
        return;
    }
        
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = value;
    queue->size = queue->size + 1;

    printf("%d enqueued\n", value);
}

int dequeue(Queue* queue)
{
    if(isEmpty(queue))
    {
        return -1;
    }

    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;

    return item;
}


int main ()
{

    Queue* queue = createQueue();

    enqueue(queue, 1);
    enqueue(queue, 5);
    enqueue(queue, 2);
    enqueue(queue, 6);

    printf("Dequeued item: %d \n", dequeue(queue));
    printf("Dequeued item: %d \n", dequeue(queue));
    printf("Dequeued item: %d \n", dequeue(queue));
    printf("Dequeued item: %d \n", dequeue(queue));

    //Empty
    printf("Dequeued item: %d \n", dequeue(queue));

    return 0;
}