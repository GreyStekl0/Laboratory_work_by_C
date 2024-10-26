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
}

void Delete(List *list, int index) {
    Item *current = list->head;
    int i = 0;

    while (current != NULL && i < index) {
        current = current->next;
        i++;
    }

    if (current == NULL) {
        return;
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
}

void printList(const List *list) {
    Item *current = list->head;
    while (current != NULL) {
        printf("%p ", (void*)current);
        current = current->next;
    }
    printf("\n");
}

int Remove(List *list, int index) {
    Item *current = list->head;
    int i = 0;

    while (current != NULL && i < index) {
        current = current->next;
        i++;
    }

    if (current == NULL) {
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

void insert(List *list, int index) {
    Item *newItem = malloc(sizeof(Item));

    if (index == 0) {
        newItem->next = list->head;
        newItem->prev = NULL;
        if (list->head != NULL) {
            list->head->prev = newItem;
        }
        list->head = newItem;
        if (list->tail == NULL) {
            list->tail = newItem;
        }
        return;
    }

    Item *current = list->head;
    int i = 0;

    while (current != NULL && i < index - 1) {
        current = current->next;
        i++;
    }

    if (current == NULL) {
        newItem->next = NULL;
        newItem->prev = list->tail;
        if (list->tail != NULL) {
            list->tail->next = newItem;
        }
        list->tail = newItem;
        if (list->head == NULL) {
            list->head = newItem;
        }
        return;
    }

    newItem->next = current->next;
    newItem->prev = current;
    if (current->next != NULL) {
        current->next->prev = newItem;
    }
    current->next = newItem;
    if (newItem->next == NULL) {
        list->tail = newItem;
    }
}

int count(const List *list) {
    int count = 0;
    const Item *current = list->head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
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
}

int GetIndex(const List *list, const Item *item) {
    int index = 0;
    const Item *current = list->head;

    while (current != NULL) {
        if (current == item) {
            return index;
        }
        current = current->next;
        index++;
    }

    return -1;
}

int main() {
    List list;
    initList(&list);
    Add(&list);
    printf("стартовый список\n");
    printList(&list);
    printf("список с добавлением в него элементов\n");
    Add(&list);
    Add(&list);
    Add(&list);
    Add(&list);
    printList(&list);

    printf("удаление первого элемента\n");
    Delete(&list, 0);
    printList(&list);
    printf("удаление элемента под индексом 1\n");
    printf("%d\n", Remove(&list, 1));
    printList(&list);

    printf("вставка элемента на индекс 1\n");
    insert(&list, 1);
    printList(&list);
    printf("вывод количества элементов в списке\n");
    printf("%d\n", count(&list));

    const Item *item = list.head->next;
    printf("Индекс второго элемента: %d\n", GetIndex(&list, item));

    Clear(&list);
    printList(&list);

    return 0;
}