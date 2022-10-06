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
    unsigned int puzzleValue[ROW_COL][ROW_COL];

public:
    // to initialize outside this class
    Puzzle(int[][ROW_COL]);                // default constructor
    bool IsGoal();                         // check if Current State is the Goal State
    bool IsValid(const int[][ROW_COL]);    // validate array if is in standard
    void PrintBoard(const int[][ROW_COL]); // print the Current State

    int getPuzzleValue(int _r, int _c) const
    {
        return puzzleValue[_r][_c];
    }

private:
    // private function, accesable only inside this class
    void setPuzzle(int puzzle[ROW_COL][ROW_COL])
    {
        for (ROW = 0; ROW < ROW_COL; ROW++)
        {
            for (COL = 0; COL < ROW_COL; COL++)
                this->puzzleValue[ROW][COL] = puzzle[ROW][COL];
        }
    }
};

// driver method
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

    Puzzle puzzle1(goal);
    Puzzle puzzle2(other);
    // puzzle.PrintBoard(goal);
    std::cout << puzzle1.IsGoal() << std::endl;
    std::cout << puzzle2.IsGoal() << std::endl;

    return 0;
}

/* puzzle public functions */
Puzzle::Puzzle(int puzzle[ROW_COL][ROW_COL])
{
    this->setPuzzle(puzzle);
}

bool Puzzle::IsGoal()
{
    int goal[ROW_COL][ROW_COL] = {
        {1, 2, 3},
        {8, 0, 4},
        {7, 6, 5}};

    for (ROW = 0; ROW < ROW_COL; ROW++)
    {
        for (COL = 0; COL < ROW_COL; COL++)
        {
            if (getPuzzleValue(ROW, COL) != goal[ROW][COL]) // if any two same positioned items not equal
                return false;                               // this state is not the goal
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