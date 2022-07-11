#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 100

typedef struct Item
{
    int data;
    int key;
} Item;

Item *dummyItem;
Item *hashArray[SIZE];
Item *item;

int hashCode(int key)
{
    return key % SIZE;
}

Item *search(int key)
{

    int hashIndex = hashCode(key);

    while (hashArray[hashIndex] != NULL)
    {

        if (hashArray[hashIndex]->key == key)
        {
            return hashArray[hashIndex];
        }

        hashIndex++;

        // wrap around the table
        hashIndex %= SIZE;
    }
    return NULL;
}

void insert(int key, int data)
{

    Item *item = (Item *)malloc(sizeof(Item));
    item->data = data;
    item->key = key;

    int hashIndex = hashCode(key);

    // move in array until an empty or deleted cell
    while (hashArray[hashIndex] != NULL && hashArray[hashIndex]->key != -1)
    {
        hashIndex++;
        hashIndex %= SIZE;
    }
    hashArray[hashIndex] = item;
}

Item *delete(Item *item)
{
    int key = item->key;
    int hashIndex = hashCode(key);

    // move in array until an empty
    while (hashArray[hashIndex] != NULL)
    {

        if (hashArray[hashIndex]->key == key)
        {
            Item *temp = hashArray[hashIndex];

            // assign a dummy item at deleted position
            hashArray[hashIndex] = dummyItem;
            return temp;
        }
        hashIndex++;
        hashIndex %= SIZE;
    }
    return NULL;
}

void display()
{

    int i = 0;

    for (i = 0; i < SIZE; i++)
    {
        if (hashArray[i] != NULL)
        {
            printf(" (%d,%d)", hashArray[i]->key, hashArray[i]->data);
        }
    }

    printf("\n");
}

int main()
{

    dummyItem = (Item *)malloc(sizeof(Item));
    dummyItem->data = -1;
    dummyItem->key = -1;

    insert(1, 20);
    insert(2, 70);
    insert(42, 80);
    insert(42, 90);
    insert(4, 25);
    insert(37, 97);

    display();
    item = search(37);

    if (item != NULL)
    {
        printf("Element found: %d\n", item->data);
    }
    else
    {
        printf("Element not found\n");
    }

    delete (item);
    item = search(37);

    if (item != NULL)
    {
        printf("Element found: %d\n", item->data);
    }
    else
    {
        printf("Element not found\n");
    }
}