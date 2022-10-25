#include <stdio.h>

int main()
{
    printf("Gantt Chart:\n");

    int i, j;
    int size = 5;
    int id[5] = {0, 1, 2, 3, 4};
    int bt[5] = {2, 6, 4, 9, 12};
    // int bt[3] = {1, 1, 1};
    int counter = 0;

    int tbt = 0;
    for (i = 0; i < size; i++)
    {
        tbt += bt[i];
    }

    printf("time   : ");
    for (i = 0; i < tbt; i++)
    {
        if (i > 9)
            printf("|---");
        else
            printf("|-");
    }
    printf("|\n\t ");
    for (i = 0; i <= tbt; i++)
    {
        if (i > 9)
            printf("%d  ", i);
        else
            printf("%d ", i);
    }

    printf("\np_id   : %d%*s", id[0], bt[0]);
    for (i = 1; i < size; i++)
    {
        if (bt[i] == 1)
        {
            printf("%d ", id[i]);
        }
        if (bt[i] < 9)
        {
            printf("%2d", id[i]);
        }
        else
        {
            printf("%*s%d", bt[i], "", id[i]);
        }
        /*
            |-|-|-|-|-|-|
            0 1 2 3 4 5 6
         */
        for (j = 0; j < bt[i] - 1; j++)
        {
            printf("  ");
        }
    }

    printf("\n");

    return 0;
}

// https://www.javatpoint.com/os-fcfs-scheduling
// spacing https://stackoverflow.com/questions/66189160/formatting-spacing-with-the-printf-function-c