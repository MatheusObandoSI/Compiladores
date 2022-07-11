#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

/*
A stack implements a data structure based on the LIFO principle (Last in First Out)
*/

typedef struct Stack
{
    int size;
    int capacity;
    int* array;
} Stack;
  
Stack* createStack()
{
    Stack* stack = (Stack*)malloc(sizeof(Stack));

    stack->capacity = SIZE;
    stack->size = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    
    return stack;
}
  
int isFull(Stack* stack)
{
    return stack->size == stack->capacity - 1;
}
  
int isEmpty(Stack* stack)
{
    return stack->size == -1;
}
  
void push(Stack* stack, int item)
{
    if (isFull(stack))
    {
        return;
    }
    stack->array[++stack->size] = item;
    printf("%d pushed to the top of the stack\n", item);
}
  
int pop(Stack* stack)
{
    if (isEmpty(stack))
        return -1;
    return stack->array[stack->size--];
}
  
int main()
{
    Stack* stack = createStack();
  
    push(stack, 10);
    push(stack, 20);
    push(stack, 30);
  
    printf("%d popped from stack\n", pop(stack));
    printf("%d popped from stack\n", pop(stack));
    printf("%d popped from stack\n", pop(stack));

    //Empty
    printf("%d popped from stack\n", pop(stack));
  
    return 0;
}