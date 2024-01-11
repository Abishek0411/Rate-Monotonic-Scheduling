#include <stdio.h>
#include <stdlib.h>

// Define a structure to represent a process
typedef struct {
    int id;
    int period;
    int processing_time;
    int deadline;
} Process;

// Function to compare processes based on their periods
int compareProcesses(const void *a, const void *b) {
    return ((Process *)a)->period - ((Process *)b)->period;
}

// Function to perform Rate Monotonic Scheduling
void rateMonotonicScheduling(int num_processes, Process processes[]) {
    // Sort the processes based on their periods
    qsort(processes, num_processes, sizeof(Process), compareProcesses);

    // Initialize the Gantt chart
    int ganttChart[num_processes][2];
    int current_time = 0;
    int all_deadlines_met = 1; // Flag to track if all deadlines are met

    // Calculate the completion time for each process and check deadlines
    for (int i = 0; i < num_processes; i++) {
        ganttChart[i][0] = processes[i].id;
        ganttChart[i][1] = current_time;
        current_time += processes[i].processing_time;

        // Check if the completion time exceeds the deadline
        if (current_time > processes[i].deadline) {
            all_deadlines_met = 0;
            break; // No need to check further, one missed deadline is enough to set the flag
        }
    }

    // Print the result
    if (all_deadlines_met) {
        printf("\nAll processes met their deadlines.\n");
    } else {
        printf("\nAt least one process missed its deadline.\n");
    }

    // Print the Gantt chart
    printf("\nGantt Chart:\n");
    printf("--------------------------------------------------------\n");
    printf("| Process   | Cumulative Time \t| Completion Time  |\n");
    printf("--------------------------------------------------------\n");
    for (int i = 0; i < num_processes; i++) {
        printf("|    P%d    |         %2d         |         %2d         |\n",
               ganttChart[i][0], ganttChart[i][1], ganttChart[i][1] + processes[i].processing_time);
    }
    printf("--------------------------------------------------------\n");
}

int main() {
    int num_processes;

    // Get the number of processes
    printf("Enter the number of processes (min 3): ");
    scanf("%d", &num_processes);

    // Check if the number of processes is at least 3
    if (num_processes < 3) {
        printf("Number of processes must be at least 3.\n");
        return 1;
    }

    // Initialize an array to store the processes
    Process processes[num_processes];

    // Get information for each process
    for (int i = 0; i < num_processes; i++) {
        processes[i].id = i + 1;
        printf("\nEnter details for Process P%d:\n", processes[i].id);
        printf("Period: ");
        scanf("%d", &processes[i].period);
        printf("Processing Time: ");
        scanf("%d", &processes[i].processing_time);
        processes[i].deadline = processes[i].period; // Deadline is assumed to be equal to the period
    }

    // Perform Rate Monotonic Scheduling
    rateMonotonicScheduling(num_processes, processes);

    return 0;
} 
