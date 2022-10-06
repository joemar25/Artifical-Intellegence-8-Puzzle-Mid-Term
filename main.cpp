/**
 *
 * @file main.cpp
 *
 * @authors  - Balagtas, Arrlee
 *           - Cardiño, Joemar
 *           - Gomez, Olan
 *
 * @date 2022-10-05
 *
 */

#include <iostream>
#include <string>
#include <ctime>
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
    Puzzle(int[][ROW_COL]);          // default constructor
    int PuzzleValue(int, int) const; // get Puzzle's Current state
    bool IsGoal();                   // check if Current State is the Goal State
    void PrintBoard();               // print the Current State

private:
    // private function, accesable only inside this class

    bool isValid(int num)
    {
        return !((num > 8) || (num < 0));
    }

    void setPuzzle(int puzzle[ROW_COL][ROW_COL])
    {
        for (ROW = 0; ROW < ROW_COL; ROW++)
        {
            for (COL = 0; COL < ROW_COL; COL++)
            {
                if (isValid(puzzle[ROW][COL]))
                    this->puzzleValue[ROW][COL] = puzzle[ROW][COL];
            }
        }
    }
};

// driver method
int main()
{
    clock_t start, end;

    int _puzzl1[ROW_COL][ROW_COL] = {
        {1, 2, 3},
        {8, 0, 4},
        {7, 6, 5}};

    int _puzzl2[ROW_COL][ROW_COL] = {
        {0, 2, 4},
        {8, 1, 7},
        {3, 6, 5}};

    Puzzle puzzle1(_puzzl1);
    Puzzle puzzle2(_puzzl2);

    // puzzle 1 test
    {
        start = clock();
        puzzle1.PrintBoard();
        end = clock();

        std::cout << "T(N) = " << ((double)(end - start)) / CLOCKS_PER_SEC << std::endl;
        std::cout << "Is Goal? " << puzzle1.IsGoal() << "\n\n";
    }

    // puzzle 2 test
    {
        start = clock();
        puzzle2.PrintBoard();
        end = clock();

        std::cout << "T(N) = " << ((double)(end - start)) / CLOCKS_PER_SEC << std::endl;
        std::cout << "Is Goal? " << puzzle2.IsGoal() << std::endl;
    }

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
            if (this->PuzzleValue(ROW, COL) != goal[ROW][COL]) // if any two same positioned items not equal
                return false;                                  // this state is not the goal
        }
    }
    return true;
}

int Puzzle::PuzzleValue(int _row, int _col) const
{
    return this->puzzleValue[_row][_col];
}

void Puzzle::PrintBoard()
{
    for (ROW = 0; ROW < ROW_COL; ROW++)
    {
        for (COL = 0; COL < ROW_COL; COL++)
            std::cout << this->PuzzleValue(ROW, COL) << " ";
        std::cout << std::endl;
    }
}

// other class functions