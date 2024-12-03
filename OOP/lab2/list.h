#ifndef LIST_H
#define LIST_H

typedef struct Item {
    struct Item *prev;
    struct Item *next;
} Item;

typedef struct {
    Item *head;
    Item *tail;
} List;

void Add(List *list, Item *newItem);
void Delete(List *list, int index);
Item* GetItem(const List *list, int index);
Item* Remove(List *list, int index);
void Insert(List *list, Item *newItem, int index);
int count(const List *list);
void Clear(List *list);
int GetIndex(const List *list, const Item *item);
void initList(List *list);
void printList(const List *list);

#endif //LIST_H
