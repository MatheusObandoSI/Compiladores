#include <stdio.h>
#include <stdlib.h>

/*Implementation of a binay tree data structure*/

typedef struct Node
{
    unsigned int data;
    struct Node* left_child;
    struct Node* right_child;
} Node;

Node* createNode(int data)
{
    Node *node = (Node*)malloc(sizeof(Node));

    node->data = data;
    node->left_child = NULL;
    node->right_child = NULL;

    return node;
}

void insert(Node **root, int data)
{
    if (*root == NULL)
    {
        *root = createNode(data);
    }

    else
    {
        if (data < ((*root)->data))
        {
            insert(&((*root)->left_child), data);
        }
        else
        {
            insert(&((*root)->right_child), data);
        }
    }
}

void displayInOrder(Node *root)
{
    if(root != NULL){
        displayInOrder(root->left_child);
        printf("%d\n", root->data);
        displayInOrder(root->right_child);
    }
}

int countNodes(Node *root)
{
   if(root == NULL)
        return 0;
   else
        return 1 + countNodes(root->left_child) + countNodes(root->right_child);
}

int main()
{
    Node *tree = NULL;

    insert(&tree, 1);
    insert(&tree, 3);
    insert(&tree, 2);

    displayInOrder(tree);

    int count = countNodes(tree);

    printf("Number of nodes: %d\n", count);

    return 0;
}