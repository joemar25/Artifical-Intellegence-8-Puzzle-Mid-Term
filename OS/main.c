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
#include <stdlib.h> // use malloc, free
#pragma pack(1)     // We can avoid the wastage of memory by simply writing #pragma pack(1) : https://iq.opengenus.org/size-of-struct-in-c/

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
unsigned int tt, wt, tbt, ct;
float att, awt;

typedef struct Process
{
    int id; // -> process id
    int bt; // -> burst time
    int at; // -> arrival time
    int pr; // -> priority
    int qt; // -> quantum
} process;

void swap(process *a, process *b)
{
    process temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

int compareAT(const void *a, const void *b)
{
    return ((process *)a)->at > ((process *)b)->at;
}

int compareBT(const void *a, const void *b)
{
    return ((process *)a)->bt > ((process *)b)->bt;
}

int getTBT(process *p, int size)
{
    // - return total burst time, function::checking the correct burst time per process
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < (p + i)->bt; j++)
            tbt += 1;
    }
    return tbt;
}

/**
 * @note
 *  - We need to add (bt) per process and get its tunaround time and waiting time
 *  - Get Average tunaround time and Average Waiting time
 */
void FCFS(process *queue, int size)
{
    qsort(queue, size, sizeof(process), compareAT);

    printf("\n\n=========================================\n\n");
    printf("CPU SCHED := FCFS\n\n");
    printf("-----------------------------------------\n");
    printf("| Process | AT  | BT  | CT  | TT  | WT  |\n");
    printf("-----------------------------------------\n");

    for (i = 0; i < size; i++)
    {
        ct += (queue + i)->bt;
        tt = ct - (queue + i)->at;
        wt = tt - (queue + i)->bt;
        att += tt;
        awt += wt;
        // print cases
        printf("| %d       |%3d  |%3d  |%3d  |%3d  |%3d  |\n", (queue + i)->id, (queue + i)->at, (queue + i)->bt, ct, tt, wt);
    }
    att /= size;
    awt /= size;
    printf("-----------------------------------------\n");

    printf("ATT = %.1f ms\n", att);
    printf("AWT = %.1f ms\n", awt);
}

void SJF(process *queue, int n)
{
    qsort(queue, n, sizeof(process), compareAT);
    tt = 0, wt = 0, tbt = 0, ct = 0;
    att = 0, awt = 0;

    int ttime = 0;
    for (i = 0; i < n; i++)
    {
        j = i;
        while ((queue + j)->at <= ttime && j != n)
            j++;
        qsort((queue + j), n - j, sizeof(process), compareBT);
        ttime += (queue + i)->at;
    }

    printf("\n\n=========================================\n\n");
    printf("CPU SCHED := FCFS\n\n");
    printf("-----------------------------------------\n");
    printf("| Process | AT  | BT  | CT  | TT  | WT  |\n");
    printf("-----------------------------------------\n");

    for (i = 0; i < n; i++)
    {
        ct += (queue + i)->bt;
        tt = ct - (queue + i)->at;
        wt = tt - (queue + i)->bt;
        att += tt;
        awt += wt;
        // print cases
        printf("| %d       |%3d  |%3d  |%3d  |%3d  |%3d  |\n", (queue + i)->id, (queue + i)->at, (queue + i)->bt, ct, tt, wt);
    }
    att /= n;
    awt /= n;
    printf("-----------------------------------------\n");

    printf("ATT = %.1f ms\n", att);
    printf("AWT = %.1f ms\n", awt);
}

void PRIO()
{
    return;
}

void RR()
{
    return;
}

void CPU_SCHED_ALGO(process *queue, int size)
{
    FCFS(queue, size);
    SJF(queue, size);
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

        printf("enter arrival time : ");
        scanf("%d", &(list + i)->at);

        printf("enter burst time  : ");
        scanf("%d", &(list + i)->bt);

        // printf("enter priority     : ");
        // scanf("%d", &(list + i)->pr);

        // printf("enter quantum time : ");
        // scanf("%d", &(list + i)->qt);
    }

    // sort by arrival time
    CPU_SCHED_ALGO(list, size);

    // free process
    free(list);
    return 0;
}

/*

5
0 0 2
1 1 6
2 2 4
3 3 9
4 6 12

5
2 2 2
5 4 7
3 1 4
4 0 1
1 3 5

5
1 0 5
2 1 2
3 2 4
4 3 1
5 4 7


*/