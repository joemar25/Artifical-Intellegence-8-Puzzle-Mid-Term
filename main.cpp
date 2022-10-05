/**
 *
 * @file main.cpp
 * @authors  - Balagtas, Arrlee
 *           - Cardiño, Joemar
 *           - Gomez, Olan
 * @brief
 * @version 0.1
 * @date 2022-10-05
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>
#include <string>

#define ROW_COL 3
unsigned int ROW, COL;

class Puzzle
{
public:
    void set(int old_position, int new_position)
    {
    }

    void Display(int goal[ROW_COL][ROW_COL])
    {
        for (ROW = 0; ROW < ROW_COL; ROW++)
        {
            for (COL = 0; COL < ROW_COL; COL++)
                std::cout << ROW + COL << " ";
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
};

int main()
{

    int goal[ROW_COL][ROW_COL] = {
        {1, 2, 3},
        {8, 0, 4},
        {7, 6, 5}};

    Puzzle puzzle;
    puzzle.Display(goal);

    return 0;
}
