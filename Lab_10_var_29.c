#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>

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

void display_process(Process *process){
    printf("Process id: %d, Priority: %d, Creation time: %d:%d:%d, Available memory: %d, Occupied memory: %d, Open resources: %d\n",
           process->id, process->priority, process->creation_time.hours,
           process->creation_time.minutes, process->creation_time.seconds,
           process->available_memory, process->occupied_memory, process->open_resources);
}

Process *find_by_id(Process *processes, int n, int id) {
    int i = 0;
    for (i; i < n; i++) {
        if (processes[i].id == id) {
            display_process(&processes[i]);
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
    int i;
    for (i = 0; i < n; i++) {
        display_process(&processes[i]);
    }
}

bool is_unique_id(Process *processes, int current_size, int id) {
    int i;
    for (i = 0; i < current_size; i++) {
        if (processes[i].id == id) {
            return false;
        }
    }
    return true;
}

void save_processes_to_file(const char *filename, Process *processes, int current_size) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Failed to open file %s\n", filename);
        return;
    }
    int i;
    for (i = 0; i < current_size; i++) {
        fprintf(file, "%d %d %d %d %d %d %d %d\n", processes[i].id, processes[i].priority,
                processes[i].creation_time.hours, processes[i].creation_time.minutes,
                processes[i].creation_time.seconds,
                processes[i].available_memory, processes[i].occupied_memory, processes[i].open_resources);
    }

    fclose(file);
    printf("Processes have been successfully saved to file %s.\n", filename);
}

bool realloc_processes(Process **processes, int *current_size, int *max_size) {
    if (*current_size == *max_size) {
        *max_size += 10;
        Process *temp = realloc(*processes, *max_size * sizeof(Process));
        if (temp == NULL) {
            printf("Memory allocation failed. No changes were made.\n");
            return false;
        }
        *processes = temp;
    }
    return true;
}

void input_process(Process *process, Process **processes, int current_size) {
    int id;
    do {
        id = input_number("Enter process id: ", 0, INT_MAX);
        if (!is_unique_id(*processes, current_size, id)) {
            printf("This id is already in use. Please enter a unique id.\n");
        }
    } while (!is_unique_id(*processes, current_size, id));
    process->id = id;
    process->priority = input_number("Enter process priority (1-10): ", 1, 10);
    process->creation_time.hours = input_number("Enter process creation time (hours): ", 0, 23);
    process->creation_time.minutes = input_number("Enter process creation time (minutes): ", 0, 59);
    process->creation_time.seconds = input_number("Enter process creation time (seconds): ", 0, 59);
    process->available_memory = input_number("Enter process available memory: ", 0, INT_MAX);
    process->occupied_memory = input_number("Enter process occupied memory: ", 0, INT_MAX);
    process->open_resources = input_number("Enter process open resources: ", 0, INT_MAX);
}

void add_process(Process **processes, int *current_size, int *max_size) {
    if (!realloc_processes(processes, current_size, max_size)) {
        printf("Failed to add process due to memory allocation error.\n");
        return;
    }
    input_process(processes, current_size, *max_size);
}

void delete_process(Process **processes, int *current_size, int *max_size, int id) {
    int i;
    for (i = 0; i < *current_size; i++) {
        if ((*processes)[i].id == id) {
            break;
        }
    }
    if (i != *current_size) {
        int j;
        for (j = i; j < *current_size - 1; j++) {
            (*processes)[j] = (*processes)[j + 1];
        }
        (*current_size)--;
        printf("Process with id %d has been deleted.\n", id);

        if (*current_size < *max_size / 2) {
            *max_size /= 2;
            Process *temp = realloc(*processes, *max_size * sizeof(Process));
            if (temp == NULL) {
                printf("Memory allocation failed. No changes were made.\n");
                return;
            }
            *processes = temp;
        }
    } else {
        printf("Process with id %d not found.\n", id);
    }
}

void insert_process(Process **processes, int *current_size, int *max_size) {
    int position;
    do {
        position = input_number("Enter the position where you want to insert the new process (0 to n): ", 0, *current_size);
    } while (position < 0 || position > *current_size);

    if (!realloc_processes(processes, current_size, max_size)) {
        printf("Failed to input process due to memory allocation error.\n");
        return;
    }

    for (int i = *current_size; i > position; i--) {
        (*processes)[i] = (*processes)[i - 1];
    }

    input_process(processes, current_size, *max_size);
}

void load_processes_from_file(const char *filename, Process **processes, int *current_size, int *max_size) {
    const char *extension = strrchr(filename, '.');
    if (!extension || strcmp(extension, ".txt") != 0) {
        printf("Invalid file type. Please provide a .txt file.\n");
        return;
    }

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open file %s\n", filename);
        return;
    }
    *current_size = 0;

    Process process;
    while (fscanf(file, "%d %d %d %d %d %d %d %d", &process.id, &process.priority,
                  &process.creation_time.hours, &process.creation_time.minutes, &process.creation_time.seconds,
                  &process.available_memory, &process.occupied_memory, &process.open_resources) == 8) {
        if (!realloc_processes(processes, current_size, max_size)) {
            printf("Failed to load processes from file due to memory allocation error.\n");
            return;
        }
        (*processes)[(*current_size)++] = process;
    }

    fclose(file);
    printf("File %s has been successfully read.\n", filename);
}

void reset_processes(Process **processes, int *current_size, int *max_size) {
    *current_size = 0;
    *max_size = 0;
    free(*processes);
    *processes = NULL;
    printf("All processes have been reset.\n");
}

int main(void) {
    Process *processes = NULL;

    int current_size = 0;
    int max_size = 0;

    int choice;


    do {
        printf("\nMenu:\n");
        printf("1. Load processes from file\n");
        printf("2. Input process\n");
        printf("3. Delete process by id\n");
        printf("4. Process insertion\n");
        printf("5. Display processes\n");
        printf("6. Display total occupied memory\n");
        printf("7. Find process by id\n");
        printf("8. Sort processes by priority\n");
        printf("9. Sort processes by creation time\n");
        printf("10. Reset all processes\n");
        printf("11. Save processes to file\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the name of the file you want to load processes from: ");
                char filename[256];
                scanf("%255s", filename);
                load_processes_from_file(filename, &processes, &current_size, &max_size);
                break;
            case 2:
                add_process(&processes, &current_size, &max_size);
                display_processes(processes, current_size);
                break;
            case 3:
                printf("Enter the id of the process you want to delete: ");
                int id_to_delete;
                scanf("%d", &id_to_delete);
                delete_process(&processes, &current_size, &max_size, id_to_delete);
                display_processes(processes, current_size);
                break;
            case 4:
                insert_process(processes, &current_size, &max_size);
                display_processes(processes, current_size);
                break;
            case 5:
                display_processes(processes, current_size);
                break;
            case 6:
                printf("Total occupied memory: %d\n", total_occupied_memory(processes, current_size));
                break;
            case 7:
                printf("Enter the id of the process you want to find: ");
                int id;
                scanf("%d", &id);
                find_by_id(processes, current_size, id);
                break;
            case 8:
                qsort(processes, current_size, sizeof(Process), compare_priority);
                printf("Processes sorted by priority:\n");
                display_processes(processes, current_size);
                break;
            case 9:
                qsort(processes, current_size, sizeof(Process), compare_creation_time);
                printf("Processes sorted by creation time:\n");
                display_processes(processes, current_size);
                break;
            case 10:
                reset_processes(&processes, &current_size, &max_size);
                break;
            case 11:
                printf("Enter the name of the file you want to save processes to: ");
                char filename1[256];
                scanf("%255s", filename1);
                save_processes_to_file(filename1, processes, current_size);
                break;
            case 0:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 0 and 11.\n");
        }
    } while (choice != 0);
    free(processes);
    return 0;
}