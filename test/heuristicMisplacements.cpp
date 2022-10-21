#include <iostream>
#include <cmath>
#include <limits>

int sum(int x, int y)
{
    return x + y;
}

int manhattanDistance(int arr[], int goal[])
{
    int cost = 0;
    for (int counter = 0, i = 0; i < 9; i++)
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

int main()
{

    /**
     * uncomment only one arr[] and goal[]
     * - for testing
     */

    // int arr[9] = {1, 2, 3, 4, 5, 6, 7, 8, 0};
    // int arr[9] = {7, 2, 4, 5, 0, 6, 8, 3, 1};
    int arr[9] = {2, 8, 1, 4, 3, 0, 7, 6, 5};

    // int goal[9] = {1, 2, 3, 8, 0, 4, 7, 6, 5};
    int goal[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};

    int manhattan_cost = manhattanDistance(arr, goal);
    std::cout << manhattan_cost << "\n";

    std::cout << "Press ENTER to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return 0;
}