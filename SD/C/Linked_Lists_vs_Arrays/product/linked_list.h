#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct List List;

List* ConstructList(int size);
int DestructList(List** list);

void *ListGetHead(List* list);
void *ListGetNext(List* list, void* element);
void *ListGetAtIndex(List* list, int index);

int ListAddTail(List* list, void* data);
int ListAddAfter(List* list, void* element, void* data);
int ListAddAtIndex(List* list, int index, void* data);

int ListRemoveTail(List* list);
int ListRemove(List* list, void* element);
int ListClear(List* list);

int ListCount(List* list);

#endif
