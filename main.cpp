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
#define ROW 3
#define COL 3

unsigned int COUNTER, _j, _i;

class Node
{
    // heuristic counter
    // manahattan distance counter
};

class Puzzle
{
    // class variables - hidden by default
    unsigned int puzzleValue[ROW * COL];

public:
    // to initialize outside this class
    Puzzle(int[]);              // default constructor
    int PuzzleValue(int) const; // get Puzzle's Current state
    bool IsGoal();              // check if Current State is the Goal State
    void PrintBoard();          // print the Current State

private:
    // private function, accesable only inside this class
    bool isValid(int num)
    {
        return !((num > 8) || (num < 0));
    }

    void setPuzzle(int puzzle[])
    {
        for (COUNTER = 0; COUNTER < (ROW * COL); COUNTER++)
        {
            if (isValid(puzzle[COUNTER]))
                this->puzzleValue[COUNTER] = puzzle[COUNTER];
        }
    }
};

// driver method
int main()
{
    clock_t start, end;

    int _puzzl1[ROW * COL] = {1, 2, 3, 8, 0, 4, 7, 6, 5};
    int _puzzl2[ROW * COL] = {0, 2, 4, 8, 1, 7, 3, 6, 5};

    Puzzle puzzle1(_puzzl1);
    Puzzle puzzle2(_puzzl2);

    {
        start = clock();
        puzzle1.PrintBoard();
        end = clock();

        std::cout << "T(N) = " << ((double)(end - start)) / CLOCKS_PER_SEC << std::endl;
        std::cout << "Is Goal? " << puzzle1.IsGoal() << "";
    }

    return 0;
}

/* puzzle public functions */
Puzzle::Puzzle(int puzzle[])
{
    this->setPuzzle(puzzle);
}

bool Puzzle::IsGoal()
{
    int goal[ROW * COL] = {1, 2, 3, 8, 0, 4, 7, 6, 5};

    for (COUNTER = 0; COUNTER < (ROW * COL); COUNTER++)
    {
        if (this->PuzzleValue(COUNTER) != goal[COUNTER]) // if any two same positioned items not equal
            return false;                                // this state is not the goal
    }
    return true;
}

int Puzzle::PuzzleValue(int _pos) const
{
    return this->puzzleValue[_pos];
}

void Puzzle::PrintBoard()
{
    COUNTER = 0;
    // std::cout << " " << this->PuzzleValue(COUNTER) << " *";
    for (_i = 0; _i < (ROW); _i++)
    {
        for (_j = 0; _j < COL; _j++)
            std::cout << "+---";
        std::cout << "+" << std::endl;

        for (_j = 0; _j < COL; _j++)
        {
            // to string is just temporary
            std::string result = (this->PuzzleValue(COUNTER) == 0) ? " " : std::to_string(this->PuzzleValue(COUNTER));
            std::cout << "| " << result << " ";
            COUNTER++;
        }

        std::cout << "|" << std::endl;
    }

    for (_j = 0; _j < COL; _j++)
        std::cout << "+---";
    std::cout << "+" << std::endl;
}

// other class functions
