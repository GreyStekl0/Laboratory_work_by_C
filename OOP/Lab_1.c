#include <stdio.h>
#include <stdlib.h>

typedef struct Item {
    struct Item *prev;
    struct Item *next;
} Item;

typedef struct {
    Item *head;
    Item *tail;
} List;

void initList(List *list) {
    list->head = NULL;
    list->tail = NULL;
    printf("List initialized.\n\n");
}

void Add(List *list) {
    Item *newItem = malloc(sizeof(Item));
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

Item* GetItem(const List *list, int index) {
    Item *current = list->head;
    int i = 0;

    while (current != NULL && i < index) {
        current = current->next;
        i++;
    }

    return current;
}

int Remove(List *list, int index) {
    Item *current = GetItem(list, index);

    if (current == NULL) {
        printf("Invalid index.\n\n");
        return -1;
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

    free(current);
    return 0;
}

void Delete(List *list, int index) {
    if (Remove(list, index) == 0) {
        printf("Item deleted at index %d.\n\n", index);
    }
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

void insert(List *list, int index) {
    if (index < 0) {
        printf("Invalid index.\n\n");
        return;
    }

    Item *newItem = malloc(sizeof(Item));
    if (newItem == NULL) {
        printf("Memory allocation failed.\n\n");
        return;
    }

    if (index == 0) {
        newItem->prev = NULL;
        newItem->next = list->head;
        if (list->head != NULL) {
            list->head->prev = newItem;
        }
        list->head = newItem;
        if (list->tail == NULL) {
            list->tail = newItem;
        }
        printf("Item inserted at index %d.\n\n", index);
        return;
    }

    Item *current = list->head;
    for (int i = 0; i < index - 1 && current != NULL; i++) {
        current = current->next;
    }

    if (current == NULL) {
        printf("Invalid index.\n\n");
        free(newItem);
        return;
    }

    newItem->next = current->next;
    newItem->prev = current;
    if (current->next != NULL) {
        current->next->prev = newItem;
    } else {
        list->tail = newItem;
    }
    current->next = newItem;
    printf("Item inserted at index %d.\n\n", index);
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

void displayMenu() {
    printf("Menu:\n");
    printf("1. Initialize List\n");
    printf("2. Add Item\n");
    printf("3. Delete Item by Index\n");
    printf("4. Print List\n");
    printf("5. Remove Item by Index\n");
    printf("6. Count Items\n");
    printf("7. Insert Item at Index\n");
    printf("8. Get Index of Item\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    List list;
    int choice, index;
    Item *item;

    while (1) {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            initList(&list);
            break;
        case 2:
            Add(&list);
            break;
        case 3:
            printf("Enter index to delete: ");
            scanf("%d", &index);
            Delete(&list, index);
            break;
        case 4:
            printList(&list);
            break;
        case 5:
            printf("Enter index to remove: ");
            scanf("%d", &index);
            if (Remove(&list, index) == 0) {
                printf("Item successfully removed at index %d.\n\n", index);
            } else {
                printf("Failed to remove item at index %d.\n\n", index);
            }
            break;
        case 6:
            count(&list);
            break;
        case 7:
            printf("Enter index to insert: ");
            scanf("%d", &index);
            insert(&list, index);
            break;
        case 8:
            printf("Enter item address to get index: ");
            scanf("%p", (void**)&item);
            GetIndex(&list, item);
            break;
        case 0:
            Clear(&list);
            printf("Exiting...\n\n");
            return 0;
        default:
            printf("Invalid choice. Please try again.\n\n");
        }
    }
}