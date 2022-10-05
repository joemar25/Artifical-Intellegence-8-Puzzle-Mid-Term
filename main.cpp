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
    // to initialize outside this class
    Puzzle(int, int);                             // default constructor
    bool IsGoal(const int puzzle[][ROW_COL]);     // will check if Current State is the Goal State
    void PrintBoard(const int puzzle[][ROW_COL]); // print the Current State

    // public functions - test
    int getX() const
    {
        return this->x;
    }

    int getY() const
    {
        return this->y;
    }

private:
    // private function, accesable only inside this class
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

    int other[ROW_COL][ROW_COL] = {
        {0, 2, 4},
        {8, 1, 7},
        {3, 6, 5}};

    Puzzle puzzle(25, 15);
    // std::cout << puzzle.getX() << std::endl;
    // std::cout << puzzle.getY() << std::endl;

    std::cout << puzzle.IsGoal(goal) << std::endl;
    std::cout << puzzle.IsGoal(other) << std::endl;

    return 0;
}

/* puzzle public functions */
Puzzle::Puzzle(int x, int y)
{
    setX(x);
    setY(y);
}

bool Puzzle::IsGoal(const int puzzle[ROW_COL][ROW_COL])
{
    int goal[ROW_COL][ROW_COL] = {
        {1, 2, 3},
        {8, 0, 4},
        {7, 6, 5}};

    for (ROW = 0; ROW < ROW_COL; ROW++)
    {
        for (COL = 0; COL < ROW_COL; COL++)
        {
            // if any two same positioned items not equal.
            if (puzzle[ROW][COL] != goal[ROW][COL])
                // this state is not the goal.
                return false;
        }
    }
    return true;
}

void Puzzle::PrintBoard(const int puzzle[ROW_COL][ROW_COL])
{
    for (ROW = 0; ROW < ROW_COL; ROW++)
    {
        for (COL = 0; COL < ROW_COL; COL++)
            std::cout << puzzle[ROW][COL] << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// other class functions