#include "linked_list.h"

#include <stdlib.h>

static Element* head = NULL;

/* function: ListAddTail
 * pre: -
 * post: an element is added to the end of the linked list
 * returns: 0 on success, -1 on fail
 */
int ListAddTail(int address, int size)
{
    Element* newElement = (Element*)malloc(sizeof(Element));
    if(newElement == NULL)
    {
        return -1;
    }
    newElement->address = address;
    newElement->size = size;
    newElement->next = NULL;
    if(head == NULL){
        head = newElement;
    }else{
        Element* temp = head;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = newElement;
    }
    return 0;
}

/* function: ListAddAfter
 * pre: -
 * post: a new element with given data is added after element
 *       in the linked list. If element is NULL, the new element
 *       is added to the front of the list.
 * returns: 0 on success, -1 on fail
 */
int ListAddAfter(int address, int size, Element* element)
{
    if(element == NULL)
    {
        Element* newElement = (Element*)malloc(sizeof(Element));
        if(newElement == NULL)
        {
            return -1;
        }
        newElement->address = address;
        newElement->size = size;
        newElement->next = head;
        head = newElement;
        return 0;
    }
    else
    {
        Element* newElement = (Element*)malloc(sizeof(Element));
        newElement->address = address;
        newElement->size = size;
        newElement->next = element->next;
        element->next = newElement;
        return 0;
    }
    return -1;
}


/* function: ListGetHead
 * pre: -
 * post: first element in linked list is returned
 * returns: first element on success, NULL if list is empty
 */
Element* ListGetHead()
{
    return head;
}


/* function: ListRemoveTail
 * pre: -
 * post: last element is removed from list
 * returns: 0 on success, -1 on fail
 */
int ListRemoveTail()
{
    if(head == NULL)
    {
        return -1;
    }
    else
    {
        Element* element = head;
        Element* prev = NULL;
        while(element->next != NULL)
        {
            prev = element;
            element = element->next; 
        }
        free(element);
        prev->next = NULL;

        return 0;
    }
    return -1;
}

/* function: ListRemove
 * pre: -
 * post: element is removed from list, pointer from callee is made NULL
 * returns: 0 on success, -1 on fail
 */
int ListRemove(Element** element)
{
    if(*element == NULL)
    {
        return -1;
    }
    else
    {
        Element* temp = head;
        Element* prev = NULL;
        while(temp != *element)
        {
            prev = temp;
            temp = temp->next;
        }
        prev->next = temp->next;
        free(temp);
        *element = NULL;
        return 0;
    }
    return -1;
}

/* function: ListRemoveAll
 * pre: -
 * post: all existing elements from list are removed
 */
void ListRemoveAll()
{
    Element* element = head;
    while(element != NULL)
    {
        Element* temp = element;
        element = element->next;
        free(temp);
    }
    head = NULL;
}
