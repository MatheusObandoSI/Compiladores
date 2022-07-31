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
    char* characters;
    int* integers;
} Stack;


Stack* createIntStack()
{
    Stack* stack = (Stack*)malloc(sizeof(Stack));

    stack->capacity = SIZE;
    stack->top = -1;
    stack->integers = (int*)malloc(stack->capacity * sizeof(int));
    
    return stack;
}

Stack* createCharStack()
{
    Stack* stack = (Stack*)malloc(sizeof(Stack));

    stack->capacity = SIZE;
    stack->top = -1;
    stack->characters = (char*)malloc(stack->capacity * sizeof(char));
    
    return stack;
}

int isFull(Stack* stack)
{
    return stack->top == stack->capacity - 1;
}
  
int isEmpty(Stack* stack)
{
    return stack->top == -1;
}


void ipush(Stack* stack, int item)
{
    if (isFull(stack))
    {
        return;
    }

    stack->integers[++stack->top] = item;
}
  
int ipop(Stack* stack)
{
    if (isEmpty(stack))
        return -1;

    int top = stack->integers[stack->top];
    stack->top = --stack->top;
    return top;
}

int itop(Stack* stack)
{
    return stack->integers[stack->top];
}

void push(Stack* stack, char item)
{
    if (isFull(stack))
    {
        return;
    }
    stack->characters[++stack->top] = item;
}
  
char pop(Stack* stack)
{
    if (isEmpty(stack))
        return '\n';

    char top = stack->characters[stack->top];
    stack->top = --stack->top;
    return top;
}

char top(Stack* stack)
{
    return stack->characters[stack->top];
}


int opPrecedence(char ch) 
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

    Stack* postfixStack = createCharStack();

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
            while (!isEmpty(postfixStack) && opPrecedence(expression[i]) <= opPrecedence(top(postfixStack))) 
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
    Stack* stack = createIntStack();
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
    Stack* stack = createCharStack();

    /*String split example*/
    char str[] = "5 + 4 + 3 * 7";
    char *pch;
    printf ("Splitting string \"%s\" into tokens:\n",str);
    pch = strtok (str," ");
    char expression[] = "((1+(2*3))-4)"; 
    convertInfixToPostfix(expression);
    int result = evaluatePostfix(expression);
    printf("\nRESULT: %d\n", result);

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