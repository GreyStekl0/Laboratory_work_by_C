#include <stdio.h>
#include <stdlib.h>
#include "list.h"

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
    Item *newItem;

    while (1) {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            initList(&list);
            break;
        case 2:
            newItem = malloc(sizeof(Item));
            Add(&list, newItem);
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
            if (Remove(&list, index) != NULL) {
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
            newItem = malloc(sizeof(Item));
            Insert(&list, newItem, index);
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