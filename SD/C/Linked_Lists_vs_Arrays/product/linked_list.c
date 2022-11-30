#include "linked_list.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct Element{
    void* data;
    Element* next;
}Element;

struct List {
    int size;
    int count;
    Element* head;
    Element* tail;
};

List* ConstructList(int size)
{
    List* list = malloc(sizeof(List));
    if (list == NULL)
    {
        return NULL;
    }
    list->size = size;
    list->count = 0;
    list->head = NULL;
    list->tail = NULL;
    return list;
}

int DestructList(List** list)
{
    if (list == NULL || *list == NULL)
    {
        return -1;
    }
    ListClear(*list);
    free(*list);
    *list = NULL;
    return 0;
}

void *ListGetHead(List* list)
{
    if (list == NULL)
    {
        return NULL;
    }
    return list->head;
}


void *ListGetNext(List* list, Element* element)
{
    if (list == NULL || element == NULL)
    {
        return NULL;
    }
    return (element->next);
}

void *ListGetAtIndex(List* list, int index)
{
    if (list == NULL || index < 0 || index >= list->count)
    {
        return NULL;
    }
    Element* element = list->head;
    for (int i = 0; i < index; i++)
    {
        element = element->next;
    }
    return element;
}

// Add element to the tail of the list
// return 0 if successful, -1 if not successful
int ListAddTail(List* list, void* data)
{
    if (list == NULL || data == NULL)
    {
        return -1;
    }
    Element* element = malloc(sizeof(Element));
    if (element == NULL)
    {
        return -1;
    }
    element->data = data;
    element->next = NULL;
    if (list->count == 0)
    {
        list->head = element;
        list->tail = element;
    }
    else
    {
        list->tail->next = element;
        list->tail = element;
    }
    list->count++;
    return 0;
}

// Add element after the given element
// return 0 if successful, -1 if not successful
int ListAddAfter(List* list, Element* element, void* data)
{
    if (list == NULL || element == NULL || data == NULL)
    {
        return -1;
    }
    Element* newElement = malloc(sizeof(Element));
    if (newElement == NULL)
    {
        return -1;
    }
    newElement->data = data;
    newElement->next = element->next;
    element->next = newElement;
    if (element == list->tail)
    {
        list->tail = newElement;
    }
    list->count++;
    return 0;
}

// Add element at the given index
// return 0 if successful, -1 if not successful
int ListAddAtIndex(List* list, int index, void* data)
{
    if (list == NULL || index < 0 || index > list->count || data == NULL)
    {
        return -1;
    }
    if (index == 0)
    {
        Element* element = malloc(sizeof(Element));
        if (element == NULL)
        {
            return -1;
        }
        element->data = data;
        element->next = list->head;
        list->head = element;
        if (list->count == 0)
        {
            list->tail = element;
        }
        list->count++;
        return 0;
    }
    Element* element = list->head;
    for (int i = 0; i < index - 1; i++)
    {
        element = element->next;
    }
    return ListAddAfter(list, element, data);
}

// Remove the tail element
// return 0 if successful, -1 if not successful
int ListRemoveTail(List* list)
{
    if (list == NULL || list->count == 0)
    {
        return -1;
    }
    Element* element = list->head;
    if (list->count == 1)
    {
        list->head = NULL;
        list->tail = NULL;
    }
    else
    {
        for (int i = 0; i < list->count - 2; i++)
        {
            element = element->next;
        }
        list->tail = element;
        element->next = NULL;
    }
    free(element);
    element = NULL;
    list->count--;
    return 0;
}

// Remove the given element
// return 0 if successful, -1 if not successful
int ListRemove(List* list, Element* element)
{
    if (list == NULL || element == NULL)
    {
        return -1;
    }
    if (element == list->head)
    {
        list->head = element->next;
        if (list->count == 1)
        {
            list->tail = NULL;
        }
        free(element);
        element = NULL;
        list->count--;
        return 0;
    }
    Element* prevElement = list->head;
    for (int i = 0; i < list->count - 1; i++)
    {
        if (prevElement->next == element)
        {
            break;
        }
        prevElement = prevElement->next;
    }
    if (prevElement->next != element)
    {
        return -1;
    }
    prevElement->next = element->next;
    if (element == list->tail)
    {
        list->tail = prevElement;
    }
    free(element);
    element = NULL;
    list->count--;
    return 0;
}

// Remove the element at the given index
// return 0 if successful, -1 if not successful
int ListRemoveAtIndex(List* list, int index)
{
    if (list == NULL || index < 0 || index >= list->count)
    {
        return -1;
    }
    if (index == 0)
    {
        Element* element = list->head;
        list->head = element->next;
        if (list->count == 1)
        {
            list->tail = NULL;
        }
        free(element);
        element = NULL;
        list->count--;
        return 0;
    }
    Element* element = list->head;
    for (int i = 0; i < index - 1; i++)
    {
        element = element->next;
    }
    return ListRemove(list, element->next);
}

// Remove all elements from the list
// return 0 if successful, -1 if not successful
int ListClear(List* list)
{
    if (list == NULL)
    {
        return -1;
    }
    while (list->count > 0)
    {
        ListRemoveTail(list);
    }
    return 0;
}

// Return the number of elements in the list
int ListCount(List* list)
{
    if (list == NULL)
    {
        return -1;
    }
    return list->count;
}
