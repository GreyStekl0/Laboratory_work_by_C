#include <stdio.h>
#include <stdlib.h>

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

void input_process(Process *process) {
    process->id = input_number("Enter process id: ", 0, INT_MAX);
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

void print_processes(Process *processes, int current_size) {
    for (int i = 0; i < current_size; i++) {
        printf("Process id: %d, Priority: %d, Creation time: %d:%d:%d, Available memory: %d, Occupied memory: %d, Open resources: %d\n",
               processes[i].id, processes[i].priority, processes[i].creation_time.hours,
               processes[i].creation_time.minutes, processes[i].creation_time.seconds,
               processes[i].available_memory, processes[i].occupied_memory, processes[i].open_resources);
    }
}

int main(void) {
    Process processes[4];

    input_process(&processes[0]);

    initialize_process(&processes[1], 1, 5, 2, 30, 15, 1000, 500, 3);
    initialize_process(&processes[2], 2, 3, 1, 20, 30, 2000, 1200, 5);
    initialize_process(&processes[3], 3, 7, 3, 45, 20, 1500, 700, 4);

    int current_size = sizeof(processes) / sizeof(Process);

    printf("Total occupied memory: %d\n", total_occupied_memory(processes, current_size));

    int id;
    int result;
    do {
        printf("Enter the id of the process you want to find: ");
        result = scanf("%d", &id);
        while (getchar() != '\n');
    } while (result == 0);

    find_by_id(processes, current_size, id);

    qsort(processes, current_size, sizeof(Process), compare_priority);
    printf("Processes sorted by priority:\n");
    print_processes(processes, current_size);

    qsort(processes, current_size, sizeof(Process), compare_creation_time);
    printf("Processes sorted by creation time:\n");
    print_processes(processes, current_size);

    return 0;
}