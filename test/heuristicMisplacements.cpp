#include <iostream>
#include <cmath>
#include <limits>

int f(int g, int h)
{
    return g + h;
}

int sum(int x, int y)
{
    return x + y;
}

int manhattanDistance(int arr[], int goal[])
{
    int cost = 0;
    for (int i = 0; i < 9; i++)
    {
        if (arr[i] != goal[i])
            cost += sum(abs(arr[i] / 3 - i / 3), abs(arr[i] % 3 - i % 3));
        /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
         * based on the condition, we will not check for position where 0 is located     *
         *                                                                               *
         *        [ARR]          [GOAL]     [RESULT]                                     *
         * pos 0 -> 1      !=     1          false                                       *
         * pos 1 -> 2      !=     2          false                                       *
         * pos 2 -> 3      !=     3          false                                       *
         * pos 3 -> 4      !=     8          *true                                       *
         * pos 4 -> 5      !=     0          *true                                       *
         * pos 5 -> 6      !=     4          *true                                       *
         * pos 6 -> 7      !=     7          false                                       *
         * pos 7 -> 8      !=     6          *true                                       *
         * pos 8 -> 0      !=     5          *true                                       *
         *                                                                               *
         * | 1 2 3 |           | 1 2 3 |                                                 *
         * | 4 5 6 |    =>     | 8 0 4 |                                                 *
         * | 7 8 0 |           | 7 6 5 |                                                 *
         *                                                                               *
         * value                 = [1 , 2 , 3 , 4 , 5 , 6 , 7 , 8, 0]                    *
         * manhattan distance is =  0 + 0 + 0 + 2 + 2 + 2 + 0 + 2 + 2                    *
         *                       =  10                                                   *
         *                                                                               *
         * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
    }
    return cost; // ????????????????? - check module 5 page 44
}

int distancesum(int x[], int y[], int n)
{
    int sum = 0;
    // for each point, finding distance to
    // rest of the point
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            sum += (abs(x[i] - x[j]) + abs(y[i] - y[j]));
    return sum;
}

int main()
{

    /**
     * uncomment only one arr[] and goal[]
     * - for testing
     */

    // int arr[9] = {1, 2, 3, 4, 5, 6, 7, 8, 0};
    // int arr[9] = {7, 2, 4, 5, 0, 6, 8, 3, 1};
    // int arr[9] = {2, 8, 1, 4, 3, 0, 7, 6, 5};
    // int arr[9] = {8, 2, 0,
    //               6, 1, 5,
    //               7, 4, 3};

    // int easy[9] = {1, 3, 4, 8, 6, 2, 7, 5, 0};
    // int medium[9] = {2, 8, 1, 4, 3, 0, 7, 6, 5};
    // int hard[9] = {2, 8, 1, 4, 6, 3, 7, 5, 0};
    // int worst[9] = {5, 6, 7, 4, 0, 8, 3, 2, 1};

    int test[9] = {3, 2, 4, 0, 5, 8, 7, 6, 1};

    // int goal[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    // int goal[9] = {1, 2, 3, 8, 0, 4, 7, 6, 5};
    int goal[9] = {2, 0, 4, 8, 1, 6, 3, 7, 5};

    int manhattan_cost = manhattanDistance(test, goal);
    std::cout << manhattan_cost << "\n";

    std::cout << "Press ENTER to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return 0;
}