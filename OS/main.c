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
 *
 * @note
 *  - This program is made from scratch. I did my best to implement all algorithms for cpu scheduling.
 *    I hope that this works well...and user will enjoy this program... '_^
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
float att, awt;

typedef struct Process
{
    int id; // process id
    int pr; // priority
    int at; // arrival time
    int bt; // burst time
} process;

typedef struct Queue
{
    process process;
    int ct;             // completion time
    int wt;             // waiting time
    int tt;             // turnaround time
    struct Queue *next; // next in the queue
} queue;

void swap(queue *q1, queue *q2)
{
    /**
     * @note this function swap a queue process
     */
    queue temp = *q1;
    *q1 = *q2;
    *q2 = temp;
}

int compareID(const void *a, const void *b)
{
    return ((queue *)a)->process.id > ((queue *)b)->process.id;
}

int compareAT(const void *a, const void *b)
{
    return ((queue *)a)->process.at > ((queue *)b)->process.at;
}

int compareBT(const void *a, const void *b)
{
    return ((queue *)a)->process.bt > ((queue *)b)->process.bt;
}

int comparePR(const void *a, const void *b)
{
    return ((queue *)a)->process.pr > ((queue *)b)->process.pr;
}

/**
 * @brief test display
 *
 * @param q
 * @param n
 */
void testDisplayQ(queue *q, int n)
{
    printf("\n\n");
    printf("-----------------------------------------------\n");
    printf("| Process | PR  | AT  | BT  | CT  | TT  | WT  |\n");
    printf("-----------------------------------------------\n");
    for (i = 0; i < n; i++)
        printf("| %d       |%3d  |%3d  |%3d  |%3d  |%3d  |%3d  |\n", (q + i)->process.id, (q + i)->process.pr, (q + i)->process.at, (q + i)->process.bt, 0, 0, 0);
}

int isSync(queue *q, int n)
{
    int result = 0;
    for (i = 0; i < n - 1; i++)
    {
        if ((q + i)->process.at != (q + i + 1)->process.at)
        {
            result = 1;
            break;
        }
    }
    return result;
}

int isPRSync(queue *q, int n)
{
    int result = 0;
    for (i = 0; i < n - 1; i++)
    {
        if ((q + i)->process.pr != (q + i + 1)->process.pr)
        {
            result = 1;
            break;
        }
    }
    return result;
}

/**
 * @note
 *  - We need to add (bt) per process and get its tunaround time and waiting time
 *  - Get Average tunaround time and Average Waiting time
 */
void FCFS(queue *q, int n)
{
    // temp
    int tempCT = 0;
    att = 0, awt = 0;

    // default by id, if arrival time is not sync (a.k.a the same)
    qsort(q, n, sizeof(queue), compareID);
    if (isSync(q, n) == 1)
        qsort(q, n, sizeof(queue), compareAT);

    printf("\n\n=====================================\n\n");
    printf("CPU SCHED := FCFS\n\n");
    printf("-----------------------------------------\n");
    printf("| Process | AT  | BT  | CT  | TT  | WT  |\n");
    printf("-----------------------------------------\n");

    // set values to 0 for incrementation
    (q + i)->tt = 0;
    (q + i)->wt = 0;

    for (i = 0; i < n; i++)
    {
        // if ((q + i)->process.at != 0)
        //     tempCT += (q + i)->process.at;
        tempCT += (q + i)->process.bt;
        (q + i)->ct = tempCT;
        (q + i)->tt = (q + i)->ct - (q + i)->process.at;
        (q + i)->wt = (q + i)->tt - (q + i)->process.bt;
        att += (q + i)->tt;
        awt += (q + i)->wt;

        printf("| %d       |%3d  |%3d  |%3d  |%3d  |%3d  |\n", (q + i)->process.id, (q + i)->process.at, (q + i)->process.bt, (q + i)->ct, (q + i)->tt, (q + i)->wt);
    }

    att /= n;
    awt /= n;
    printf("-----------------------------------------\n");

    printf("ATT = %.1f ms\n", att);
    printf("AWT = %.1f ms\n", awt);
}

/**
 * @note
 *  - if arrival time 0, sort by burst time
 *  - must base on the arrival time if arrival time != 0, before sorting the their burst time
 */
void SJF(queue *q, int n)
{
    int tempCT = 0;
    int ttime = 0;
    att = 0, awt = 0;

    qsort(q, n, sizeof(queue), compareAT);
    for (i = 0; i < n; i++)
    {
        j = i;
        while ((q + j)->process.at <= ttime && j != n)
            j++;
        qsort((q + j), n - j, sizeof(queue), compareBT);
        ttime += (q + i + 1)->process.at;
    }

    printf("\n\n=====================================\n\n");
    printf("CPU SCHED := SJF\n\n");
    printf("-----------------------------------------\n");
    printf("| Process | AT  | BT  | CT  | TT  | WT  |\n");
    printf("-----------------------------------------\n");

    for (i = 1; i < n - 1; i++)
    {
        if ((q + i)->process.bt > (q + i + 1)->process.at)
            qsort((q + j), n - j, sizeof(queue), compareBT);
    }

    if (isSync(q, n) != 1)
        qsort(q, n, sizeof(queue), compareBT);

    // set values to 0 for incrementation
    (q + i)->tt = 0;
    (q + i)->wt = 0;

    for (i = 0; i < n; i++)
    {
        // if ((q + i)->process.at != 0)
        //     tempCT += (q + i)->process.at;
        tempCT += (q + i)->process.bt;
        (q + i)->ct = tempCT;
        (q + i)->tt = (q + i)->ct - (q + i)->process.at;
        (q + i)->wt = (q + i)->tt - (q + i)->process.bt;
        att += (q + i)->tt;
        awt += (q + i)->wt;

        printf("| %d       |%3d  |%3d  |%3d  |%3d  |%3d  |\n", (q + i)->process.id, (q + i)->process.at, (q + i)->process.bt, (q + i)->ct, (q + i)->tt, (q + i)->wt);
    }

    att /= n;
    awt /= n;
    printf("-----------------------------------------\n");

    printf("ATT = %.1f ms\n", att);
    printf("AWT = %.1f ms\n", awt);
}

void PRIO(queue *q, int n)
{
    int tempCT = 0;
    int ttime = 0;
    att = 0, awt = 0;

    if (isPRSync(q, n) != 1)
    {
        qsort(q, n, sizeof(queue), compareAT);
    }
    if (isSync(q, n) != 1)
    {
        qsort(q, n, sizeof(queue), compareID);
    }
    else
    {
        for (i = 0; i < n; i++)
        {
            j = i;
            while ((q + j)->process.at <= ttime && j != n)
                j++;
            qsort((q + j), n - j, sizeof(queue), comparePR);
            ttime += (q + i + 1)->process.at;
        }
    }

    printf("\n\n===========================================\n\n");
    printf("CPU SCHED := PRIORITY\n\n");
    printf("-----------------------------------------------\n");
    printf("| Process | PR  | AT  | BT  | CT  | TT  | WT  |\n");
    printf("-----------------------------------------------\n");

    // set values to 0 for incrementation
    (q + i)->tt = 0;
    (q + i)->wt = 0;

    for (i = 0; i < n; i++)
    {
        // if ((q + i)->process.at != 0)
        //     tempCT += (q + i)->process.at;
        tempCT += (q + i)->process.bt;
        (q + i)->ct = tempCT;
        (q + i)->tt = (q + i)->ct - (q + i)->process.at;
        (q + i)->wt = (q + i)->tt - (q + i)->process.bt;
        att += (q + i)->tt;
        awt += (q + i)->wt;

        printf("| %d       |%3d  |%3d  |%3d  |%3d  |%3d  |%3d  |\n", (q + i)->process.id, (q + i)->process.pr, (q + i)->process.at, (q + i)->process.bt, (q + i)->ct, (q + i)->tt, (q + i)->wt);
    }

    att /= n;
    awt /= n;
    printf("-----------------------------------------------\n");

    printf("ATT = %.1f ms\n", att);
    printf("AWT = %.1f ms\n", awt);
}

void RR(queue *q, int n)
{
    int tempCT = 0, quantum = 0;
    att = 0, awt = 0;

    printf("\n\n=========================================\n\n");

    printf("quantum time : ");
    scanf("%d", &quantum);

    printf("\n=========================================\n\n");
    printf("CPU SCHED := RR\n");
    printf("Quantum   := %d\n\n", quantum);
    printf("-----------------------------------------\n");
    printf("| Process | AT  | BT  | CT  | TT  | WT  |\n");
    printf("-----------------------------------------\n");

    int y = 0, z = 0, x = n;
    int AT[n];
    int TAT[n];
    int TBT[n];
    int BT[n];

    for (i = 0; i < n; i++)
    {
        BT[i] = (q + i)->process.bt;
        TBT[i] = BT[i];
    }

    for (y = 0, i = 0; x != 0;)
    {
        if (TBT[i] <= quantum && TBT[i] > 0)
        {
            y = y + TBT[i];
            TBT[i] = 0;
            z = 1;
        }
        else if (TBT[i] > 0)
        {
            TBT[i] = TBT[i] - quantum;
            y += quantum;
        }
        if (TBT[i] == 0 && z == 1)
        {
            x--;
            printf("\nP%d\t\t\t%d\t\t\t%d\t\t\t%d", i + 1, BT[i],
                   y - AT[i], y - AT[i] - BT[i]);
            // printf("| %d       |%3d  |%3d  |%3d  |%3d  |%3d  |%3d  |\n", (q + i)->process.id, (q + i)->process.pr, (q + i)->process.at, (q + i)->process.bt, (q + i)->ct, (q + i)->tt, (q + i)->wt);
            awt += y - AT[i] - BT[i];
            att += y - AT[i];
            z = 0;
        }
        if (i == n - 1)
        {
            i = 0;
        }
        else if (AT[i + 1] <= y)
        {
            i++;
        }
        else
        {
            i = 0;
        }
    }

    // --------------------
    testDisplayQ(q, n);

    return;
}

void input(queue *q, int n)
{
    for (i = 0; i < n; ++i)
    {
        printf("\nCount : %d\n", (i + 1));

        printf("enter process id  : ");
        scanf("%d", &(q + i)->process.id);

        printf("enter priority     : ");
        scanf("%d", &(q + i)->process.pr);

        printf("enter arrival time : ");
        scanf("%d", &(q + i)->process.at);

        printf("enter burst time  : ");
        scanf("%d", &(q + i)->process.bt);

        q->next = q;
    }
    q->next = NULL;

    /*
    3
    1 0 0 4
    2 0 0 3
    3 0 0 5

    */
}

void CPU_SCHED_ALGO(queue *q, int n)
{
    /*
    5
    1 5 0 8
    2 1 5 2
    3 2 1 7
    4 3 6 3
    5 4 8 5

    3

    1 1 0 0 8 3
    1 0 0 8 22 22 14

    3
    1 0 0 4
    2 0 0 3
    3 0 0 5

    2

    */

    // input the processes inside queue
    input(q, n);

    // use cpu scheduling algorithms
    FCFS(q, n);
    SJF(q, n);
    PRIO(q, n);
    // RR(q, n);
}

int main()
{
    int size;
    queue *q;

    printf("Enter the number of processes: ");
    scanf("%d", &size);

    // Memory allocation for process structures
    q = (queue *)malloc(size * sizeof(queue));

    CPU_SCHED_ALGO(q, size);

    free(q);
    return 0;
}
/*
---------------
Priority Test

p, pr, at, bt

7
1 2	0 3
2 6	2 5
3 3	1 4
4 5	4 2
5 7	6 9
6 4	5 4
7 10 7 10

3

outcome
Process Id	Priority	Arrival Time	Burst Time	Completion Time	Turnaround Time	Waiting Time	Response Time
1	2	0	3	3	3	0	0
2	6	2	5	18	16	11	13
3	3	1	4	7	6	2	3
4	5	4	2	13	9	7	11
5	7	6	9	27	21	12	18
6	4	5	4	11	6	2	7
7	10	7	10	37	30	18	27

-simplified
1	2	0	3	3	3	0
3	3	1	4	7	6	2
6	4	5	4	11	6	2
4	5	4	2	13	9	7
2	6	2	5	18	16	11
5	7	6	9	27	21	12
7	10	7	10	37	30	18

Avg Waiting Time = (0+11+2+7+12+2+18)/7 = 52/7 units => 7.4 or 7.7
or 54/7 = 7.7 ms



p, pr, at, bt

3
1 0 0 4
2 0 0 3
3 0 0 5
2

*/