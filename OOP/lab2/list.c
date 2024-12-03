#include "list.h"
#include <stdio.h>
#include <stdlib.h>

void Add(List *list, Item *newItem) {
    newItem->next = NULL;
    newItem->prev = list->tail;

    if (list->tail != NULL) {
        list->tail->next = newItem;
    } else {
        list->head = newItem;
    }

    list->tail = newItem;
    printf("Item added.\n\n");
}

void Delete(List *list, int index) {
    Item *removedItem = Remove(list, index);
    if (removedItem != NULL) {
        free(removedItem);
        printf("Item deleted at index %d.\n\n", index);
    } else {
        printf("Invalid index. No item deleted.\n\n");
    }
}

Item* GetItem(const List *list, int index) {
    if (index < 0) {
        return NULL;
    }

    Item *current = list->head;
    int i = 0;

    while (current != NULL && i < index) {
        current = current->next;
        i++;
    }

    return current;
}

Item* Remove(List *list, int index) {
    if (index < 0) {
        return NULL;
    }

    Item *current = GetItem(list, index);

    if (current == NULL) {
        return NULL;
    }

    if (current->prev != NULL) {
        current->prev->next = current->next;
    } else {
        list->head = current->next;
    }

    if (current->next != NULL) {
        current->next->prev = current->prev;
    } else {
        list->tail = current->prev;
    }

    return current;
}

void Insert(List *list, Item *newItem, int index) {
    if (index < 0) {
        printf("Invalid index.\n\n");
        return;
    }

    Item *current = GetItem(list, index);

    if (current == NULL) {
        Add(list, newItem);
        printf("Item added at the end as index %d was invalid.\n\n", index);
        return;
    }

    newItem->next = current;
    newItem->prev = current->prev;

    if (current->prev != NULL) {
        current->prev->next = newItem;
    } else {
        list->head = newItem;
    }

    current->prev = newItem;
    printf("Item inserted at index %d.\n\n", index);
}

int count(const List *list) {
    int count = 0;
    const Item *current = list->head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    printf("Number of items: %d\n\n", count);
    return count;
}

void Clear(List *list) {
    Item *current = list->head;
    Item *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    list->head = NULL;
    list->tail = NULL;
    printf("List cleared.\n\n");
}

int GetIndex(const List *list, const Item *item) {
    const Item *current = list->head;
    int index = 0;

    while (current != NULL) {
        if (current == item) {
            printf("Item index: %d\n\n", index);
            return index;
        }
        current = current->next;
        index++;
    }

    printf("Item not found.\n\n");
    return -1;
}

void initList(List *list) {
    list->head = NULL;
    list->tail = NULL;
    printf("List initialized.\n\n");
}

void printList(const List *list) {
    Item *current = list->head;
    int i = 0;
    printf("List: %p  Head: %p  Tail: %p\n", (void*)list, (void*)list->head, (void*)list->tail);
    printf("#       p       prev    next\n");
    while (current != NULL) {
        printf("%d       %p    %p    %p\n", i, (void*)current, (void*)current->prev, (void*)current->next);
        current = current->next;
        i++;
    }
    printf("\n");
}