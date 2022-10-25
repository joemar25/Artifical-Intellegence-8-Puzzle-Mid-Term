/**
 *
 * @file main.c
 *
 * @author Cardiño, Joemar J.
 *
 * @date 2022-10-19
 *
 * Title : CPU Scheduling  Implementation in C
 * Task  : Write a C Program to determine the average waiting time
 *         and average turnaround time given n processes and their
 *         burst times for the following CPU Scheduling algorithms:
 *          1. FCFS
 *          2. SJF (Non-preemptive)
 *          3. Priority (Non-preemptive)
 *          4. Round Robin
 */

#include <stdio.h>
#pragma pack(1) // We can avoid the wastage of memory by simply writing #pragma pack(1) : https://iq.opengenus.org/size-of-struct-in-c/

/**
 * @note my_standard::Global Variables => will be used for iteration(s)
 *
 * ---------------------------------------------------------------------
 * variable | uses
 * ---------------------------------------------------------------------
 *   i      | for row, basically used to compare the size of the Process
 * ---------------------------------------------------------------------
 *   j      | for column, used for other loop inside a loop
 * ---------------------------------------------------------------------
 * current  | current time, when a process arrived at 'some time'
 *          | and execute it's burst time, it will save the values
 *          | and later be used for computations
 */
unsigned int i, j, current;

typedef struct Process
{
    int id; // -> process id
    int bt; // -> burst time
    int at; // -> arrival time
    int pr; // -> priority
    int qt; // -> quantum
} process;

// typedef struct Queue
// {
//     process p;
//     struct Queue *next;
// } queue;

void DisplayResult()
{
    /**
     * expected output
     *
     * -------------------------------------
     * CPU SCHED := FCFS
     *
     * ------------------------------------
     * | Process | AT | BT | CT | TT | WT |
     * ------------------------------------
     * | 1       | 0  | 3  | 3  | 3  | 0  |
     * | 2       | 1  | 2  | 5  | 4  | 2  |
     * | 3       | 2  | 4  | 9  | 7  | 3  |
     * ------------------------------------
     *
     * ATT = 12.2 ms
     * AWT = 10.2 ms
     *
     * -------------------------------------
     */
    return;
}

void swap(process *px, process *py)
{
    process temp;
    temp = *px;
    *px = *py;
    *py = temp;
}

void sort(process *list, int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if ((list + j)->at > (list + j + 1)->at)
                swap((list + j), (list + j + 1));
        }
    }
}

void FCFS(process *queue, int size)
{
    /* we only need burst time and arrival time */
    printf("CPU SCHEDULING = FCFS");
    int total_bt = 0;

    for (i = 0; i < size; i++)
    {
        printf("Process ID = %d\n", (queue + i)->id);
        for (j = 0; j < (queue + i)->bt; j++)
        {
            total_bt += 1;
        }
    }

    printf("%d", total_bt);
}
void SJF()
{
    return;
}
void PRIO()
{
    return;
}
void RR()
{
    return;
}

int main()
{
    // define variables
    int size;

    process *list;
    int noOfRecords;
    printf("Enter the number of processes: ");
    scanf("%d", &size);

    // Memory allocation for process structures
    list = (process *)malloc(size * sizeof(process));

    for (i = 0; i < size; ++i)
    {
        printf("\nCount : %d\n", (i + 1));

        printf("enter process id  : ");
        scanf("%d", &(list + i)->id);

        printf("enter burst time  : ");
        scanf("%d", &(list + i)->bt);

        printf("enter arrival time : ");
        scanf("%d", &(list + i)->at);

        printf("enter priority     : ");
        scanf("%d", &(list + i)->pr);

        printf("enter quantum time : ");
        scanf("%d", &(list + i)->qt);
    }

    printf("\nDisplaying Information:\n");
    for (i = 0; i < size; ++i)
    {
        printf("Process ID = %d, \tProcess BT = %d\n", (list + i)->id, (list + i)->bt);
    }

    sort(list, size);

    printf("\nDisplaying Sorted Information:\n");
    for (i = 0; i < size; ++i)
    {
        printf("Process ID = %d, \tProcess BT = %d\n", (list + i)->id, (list + i)->bt);
    }

    FCFS(list, size);

    // free process
    free(list);
    return 0;
}