#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define SIZE 100

typedef struct Stack
{
    int top;
    int capacity;
    char* array;
} Stack;

typedef struct IntStack
{
    int top;
    int capacity;
    int* array;
} IntStack;

IntStack* icreateStack()
{
    IntStack* stack = (IntStack*)malloc(sizeof(IntStack));

    stack->capacity = SIZE;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    
    return stack;
}

Stack* createStack()
{
    Stack* stack = (Stack*)malloc(sizeof(Stack));

    stack->capacity = SIZE;
    stack->top = -1;
    stack->array = (char*)malloc(stack->capacity * sizeof(char));
    
    return stack;
}

int iisFull(IntStack* stack)
{
    return stack->top == stack->capacity - 1;
}
  
int iisEmpty(IntStack* stack)
{
    return stack->top == -1;
}

int isFull(Stack* stack)
{
    return stack->top == stack->capacity - 1;
}
  
int isEmpty(Stack* stack)
{
    return stack->top == -1;
}


void ipush(IntStack* stack, int item)
{
    if (iisFull(stack))
    {
        return;
    }

    stack->array[++stack->top] = item;
}
  
int ipop(IntStack* stack)
{
    if (iisEmpty(stack))
        return -1;

    int top = stack->array[stack->top];
    stack->top = --stack->top;
    return top;
}

int itop(IntStack* stack)
{
    return stack->array[stack->top];
}

void push(Stack* stack, char item)
{
    if (isFull(stack))
    {
        return;
    }
    stack->array[++stack->top] = item;
}
  
char pop(Stack* stack)
{
    if (isEmpty(stack))
        return '\n';

    char top = stack->array[stack->top];
    stack->top = --stack->top;
    return top;
}

char top(Stack* stack)
{
    return stack->array[stack->top];
}


int precedence(char ch) 
{
    if (ch == '+' || ch == '-')
    {
        return 1;
    } 
    else if (ch == '*' || ch == '/')
    {
        return 1;
    } 
    else
    {
        return -1; 
    }
} 



int isOperator(char c)
{
    if(c=='/' || c=='*' || c=='+' || c=='-' || c=='(' || c==')')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

float doOperation(char operator, float x, float y)
{
    if (operator == '+')
    {
        return x+y;
    }
    else if (operator == '-')
    {
        return x-y;
    }
    else if (operator == '/')
    {
        return x/y;
    }
    else if (operator == '*')
    {
        return x*y;
    }
}

int convertInfixToPostfix(char* expression) 
{ 

    Stack* postfixStack = createStack();
    
    int i, j;

    for (i = 0, j = -1; expression[i]; ++i) 
    { 
        //Check if it's a value
        if (!isOperator(expression[i]))
        {
            expression[++j] = expression[i]; 
        } 

        // Here, if we scan character ‘(‘, we need push it to the stack. 
        else if (expression[i] == '(')
        {
            push(postfixStack, expression[i]); 
        }

        // Here, if we scan character is an ‘)’, we need to pop and print from the stack  
        // do this until an ‘(‘ is encountered in the stack. 
        else if (expression[i] == ')') 
        { 
            while (!isEmpty(postfixStack) && top(postfixStack) != '(') 
                expression[++j] = pop(postfixStack); 
            if (!isEmpty(postfixStack) && top(postfixStack) != '(') 
                return -1; // invalid expression              
            else
                pop(postfixStack); 
        }
        else // if an operator
        { 
            while (!isEmpty(postfixStack) && precedence(expression[i]) <= precedence(top(postfixStack))) 
                expression[++j] = pop(postfixStack); 
            push(postfixStack, expression[i]); 
        } 

    } 

    // Once all inital expression characters are traversed
    // adding all left elements from stack to exp
    while (!isEmpty(postfixStack)) 
        expression[++j] = pop(postfixStack); 

    expression[++j] = '\0'; 
    printf("Postfix expression: %s", expression); 
} 

int evaluatePostfix(char* exp)
{
    // Create a stack of capacity equal to expression size
    IntStack* stack = icreateStack();
    int i;
  
    // See if stack was created successfully
    if (!stack) return -1;
  
    // Scan all characters one by one
    for (i = 0; exp[i]; ++i)
    {
        // If the scanned character is an operand (number here),
        // push it to the stack.
        if (!isOperator(exp[i]))
            ipush(stack, exp[i] - '0');
  
        // If the scanned character is an operator, pop two
        // elements from stack apply the operator
        else
        {
            int val1 = ipop(stack);
            int val2 = ipop(stack);
            switch (exp[i])
            {
                case '+': ipush(stack, val2+val1); break;
                case '-': ipush(stack, val2-val1); break;
                case '*': ipush(stack, val2*val1); break;
                case '/': ipush(stack, val2/val1); break;
            }
        }
    }
    return ipop(stack);
}


  
int main()
{
    Stack* stack = createStack();

    /*String split example*/
    char str[] = "5 + 4 + 3 * 7";
    char *pch;
    printf ("Splitting string \"%s\" into tokens:\n",str);
    pch = strtok (str," ");
    char expression[] = "((1+(2*3))-4)"; 
    convertInfixToPostfix(expression);
    int result = evaluatePostfix(expression);
    printf("\nRESULT: %d\n", result);

    //Token formats are ""
    // while (pch != NULL)
    // {
    //     printf ("%s ",pch);
    //     pch = strtok (NULL, " ,.-");
    // }
  
    // push(stack, '1');
    // push(stack, '2');
    // push(stack, '3');

    // printf("%c TOP from stack\n", top(stack));
    // printf("%c popped from stack\n", pop(stack));
    // printf("%c popped from stack\n", pop(stack));
    // printf("%c popped from stack\n", pop(stack));

    // printf("%c popped from stack\n", pop(stack));

    return 0;
}