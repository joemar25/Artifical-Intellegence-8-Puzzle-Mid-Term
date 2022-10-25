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
    int p;  // -> priority
    int q;  // -> quantum
} process;

typedef struct Queue
{
    process p;
    queue *next;
} queue;

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

void FCS(queue *queue)
{
    /* we only need burst time and arrival time */
    for (i = 0; i < 3; i++)
    {
        // printf("%i ", p[i].bt);
        for (j = 0; j < p[i].bt; j++)
        {
        }
    }

    return;
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
    process p[3];

    // 3 process
    p[0].id = 1;
    p[0].bt = 3;
    p[0].at = 1;
    p[0].p = 0;
    p[0].q = 0;

    p[1].id = 2;
    p[1].bt = 5;
    p[1].at = 2;
    p[1].p = 0;
    p[1].q = 0;

    p[2].id = 3;
    p[2].bt = 2;
    p[2].at = 3;
    p[2].p = 0;
    p[2].q = 0;
    // end creation

    queue q;

    FCS(p);

    return 0;
}