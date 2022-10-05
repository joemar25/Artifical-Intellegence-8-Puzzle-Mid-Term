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

class Node
{
    // heuristic counter
    // manahattan distance counter
};

class Puzzle
{
    // class variables - hidden by default
    unsigned int x, y;

public:
    bool IsGoal();
    void PrintBoard(int puzzle[ROW_COL][ROW_COL]);

    // constructor
    Puzzle(int x, int y)
    {
        setX(x);
        setY(y);
    }

    // public functions
    int getX() const
    {
        return this->x;
    }

    int getY() const
    {
        return this->y;
    }

    void PrintBoard(int puzzle[ROW_COL][ROW_COL])
    {
        for (ROW = 0; ROW < ROW_COL; ROW++)
        {
            for (COL = 0; COL < ROW_COL; COL++)
                std::cout << ROW + COL << " ";
            /*CHANGE THIS AREA */
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

private:
    void setX(const int &x)
    {
        this->x = x;
    }

    void setY(const int &y)
    {
        this->y = y;
    }
};

int main()
{

    int goal[ROW_COL][ROW_COL] = {
        {1, 2, 3},
        {8, 0, 4},
        {7, 6, 5}};

    Puzzle puzzle(25, 15);
    std::cout << puzzle.getX() << std::endl;
    std::cout << puzzle.getY() << std::endl;
    // puzzle.Display(goal);

    return 0;
}

/* puzzle public functions */
bool Puzzle::IsGoal()
{
    for (ROW = 0; ROW < ROW_COL; ROW++)
    {
        for (COL = 0; COL < ROW_COL; COL++)
        {
            // if any two same positioned items not equal.
            // if (A[ROW][COL] != Goal[ROW][COL])
            // this state is not the goal.
            // return false;
        }
    }
    return true;
}

void Puzzle::PrintBoard(int puzzle[ROW_COL][ROW_COL])
{
    for (ROW = 0; ROW < ROW_COL; ROW++)
    {
        for (COL = 0; COL < ROW_COL; COL++)
            std::cout << ROW + COL << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}