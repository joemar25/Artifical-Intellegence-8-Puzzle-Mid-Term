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
    }
    return cost;
}

int main()
{
    int test[9] = {1, 2, 3, 4, 5, 6, 7, 8, 0};
    int goal[9] = {1, 2, 3, 8, 0, 4, 7, 6, 5};

    int manhattan_cost = manhattanDistance(test, goal);
    std::cout << manhattan_cost << "\n";

    std::cout << "Press ENTER to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return 0;
}