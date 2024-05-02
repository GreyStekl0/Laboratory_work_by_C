#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int id;
    int priority;
    struct {
        int hours;
        int minutes;
        int seconds;
    } creation_time;
    int available_memory;
    int occupied_memory;
    int open_resources;
} Process;

int compare_priority(const void *a, const void *b) {
    Process *processA = (Process *) a;
    Process *processB = (Process *) b;
    return processA->priority - processB->priority;
}

int compare_creation_time(const void *a, const void *b) {
    Process *processA = (Process *) a;
    Process *processB = (Process *) b;
    int timeA = processA->creation_time.hours * 3600 + processA->creation_time.minutes * 60 +
                processA->creation_time.seconds;
    int timeB = processB->creation_time.hours * 3600 + processB->creation_time.minutes * 60 +
                processB->creation_time.seconds;
    return timeA - timeB;
}

Process *find_by_id(Process *processes, int n, int id) {
    int i = 0;
    for (i; i < n; i++) {
        if (processes[i].id == id) {
            printf("Found process with id %d. Priority: %d, Creation time: %d:%d:%d, Available memory: %d, Occupied memory: %d, Open resources: %d\n",
                   processes[i].id, processes[i].priority, processes[i].creation_time.hours,
                   processes[i].creation_time.minutes, processes[i].creation_time.seconds,
                   processes[i].available_memory, processes[i].occupied_memory, processes[i].open_resources);
            return &processes[i];
        }
    }
    printf("Process with id %d not found.\n", id);
    return NULL;
}

int total_occupied_memory(Process *processes, int n) {
    int total = 0;
    int i = 0;
    for (i; i < n; i++) {
        total += processes[i].occupied_memory;
    }
    return total;
}

int input_number(const char *message, int min, int max) {
    int value;
    int result;
    do {
        printf("%s", message);
        result = scanf("%d", &value);
        while (getchar() != '\n');
    } while (result == 0 || value < min || value > max);
    return value;
}

void display_processes(Process *processes, int n) {
    printf("Current processes:\n");
    for (int i = 0; i < n; i++) {
        printf("Process id: %d, Priority: %d, Creation time: %d:%d:%d, Available memory: %d, Occupied memory: %d, Open resources: %d\n",
               processes[i].id, processes[i].priority, processes[i].creation_time.hours,
               processes[i].creation_time.minutes, processes[i].creation_time.seconds,
               processes[i].available_memory, processes[i].occupied_memory, processes[i].open_resources);
    }
}

bool is_unique_id(Process *processes, int current_size, int id) {
    for (int i = 0; i < current_size; i++) {
        if (processes[i].id == id) {
            return false;
        }
    }
    return true;
}

void input_process(Process *process, Process *processes, int current_size, bool is_new_process) {
    if (is_new_process) {
        int id;
        do {
            id = input_number("Enter process id: ", 0, INT_MAX);
            if (!is_unique_id(processes, current_size, id)) {
                printf("This id is already in use. Please enter a unique id.\n");
            }
        } while (!is_unique_id(processes, current_size, id));
        process->id = id;
    }
    process->priority = input_number("Enter process priority (1-10): ", 1, 10);
    process->creation_time.hours = input_number("Enter process creation time (hours): ", 0, 23);
    process->creation_time.minutes = input_number("Enter process creation time (minutes): ", 0, 59);
    process->creation_time.seconds = input_number("Enter process creation time (seconds): ", 0, 59);
    process->available_memory = input_number("Enter process available memory: ", 0, INT_MAX);
    process->occupied_memory = input_number("Enter process occupied memory: ", 0, INT_MAX);
    process->open_resources = input_number("Enter process open resources: ", 0, INT_MAX);
}

void initialize_process(Process *process, int id, int priority, int hours, int minutes, int seconds, int available_memory, int occupied_memory, int open_resources) {
    process->id = id;
    process->priority = priority;
    process->creation_time.hours = hours;
    process->creation_time.minutes = minutes;
    process->creation_time.seconds = seconds;
    process->available_memory = available_memory;
    process->occupied_memory = occupied_memory;
    process->open_resources = open_resources;
}

void delete_process(Process *processes, int *current_size, int id) {
    int i;
    for (i = 0; i < *current_size; i++) {
        if (processes[i].id == id) {
            break;
        }
    }
    if (i != *current_size) {
        for (int j = i; j < *current_size - 1; j++) {
            processes[j] = processes[j + 1];
        }
        (*current_size)--;
        printf("Process with id %d has been deleted.\n", id);
    } else {
        printf("Process with id %d not found.\n", id);
    }
}

void update_process(Process *processes, int current_size) {
    printf("Enter the id of the process you want to update: ");
    int id_to_update;
    scanf("%d", &id_to_update);
    for (int i = 0; i < current_size; i++) {
        if (processes[i].id == id_to_update) {
            printf("Process with id %d found. Enter new values.\n", id_to_update);
            input_process(&processes[i], processes, current_size, false);
            return;
        }
    }
    printf("Process with id %d not found.\n", id_to_update);
}

int main(void) {
    Process processes[10];

    initialize_process(&processes[0], 0, 4, 1, 15, 30, 1500, 750, 2);
    initialize_process(&processes[1], 1, 5, 2, 30, 15, 1000, 500, 3);
    initialize_process(&processes[2], 2, 3, 1, 20, 30, 2000, 1200, 5);
    initialize_process(&processes[3], 3, 7, 3, 45, 20, 1500, 700, 4);

    int current_size = 4;
    int max_size = sizeof(processes) / sizeof(Process);

    int choice;


    do {
        printf("\nMenu:\n");
        printf("1. Input process\n");
        printf("2. Delete process by id\n");
        printf("3. Update process by id\n");
        printf("4. Display processes\n");
        printf("5. Display total occupied memory\n");
        printf("6. Find process by id\n");
        printf("7. Sort processes by priority\n");
        printf("8. Sort processes by creation time\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (current_size < max_size) {
                    input_process(&processes[current_size], processes, current_size, true);
                    current_size++;
                    display_processes(processes, current_size);
                } else {
                    printf("No more space for new processes.\n");
                }
                break;
            case 2:
                printf("Enter the id of the process you want to delete: ");
                int id_to_delete;
                scanf("%d", &id_to_delete);
                delete_process(processes, &current_size, id_to_delete);
                display_processes(processes, current_size);
                break;
            case 3:
                update_process(processes, current_size);
                display_processes(processes, current_size);
                break;
            case 4:
                display_processes(processes, current_size);
                break;
            case 5:
                printf("Total occupied memory: %d\n", total_occupied_memory(processes, current_size));
                break;
            case 6:
                printf("Enter the id of the process you want to find: ");
                int id;
                scanf("%d", &id);
                find_by_id(processes, current_size, id);
                break;
            case 7:
                qsort(processes, current_size, sizeof(Process), compare_priority);
                printf("Processes sorted by priority:\n");
                display_processes(processes, current_size);
                break;
            case 8:
                qsort(processes, current_size, sizeof(Process), compare_creation_time);
                printf("Processes sorted by creation time:\n");
                display_processes(processes, current_size);
                break;
            case 0:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 0 and 5.\n");
        }
    } while (choice != 0);

    return 0;
}