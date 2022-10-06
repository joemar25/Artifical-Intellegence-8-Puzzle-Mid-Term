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
#include <stack> // for IDS, since DFS is a LIFO based algo and uses Stack
#define ROW_COL 3

unsigned int ROW, COL, COUNTER;

class Node
{
    int y;
    int x;
    int parentX;
    int parentY;
    float gCost;
    float hCost;
    float fCost;

    // heuristic counter
    // manahattan distance counter
};

class Puzzle
{
    // class variables - hidden by default
    unsigned int x, y;
    unsigned int puzzleValue[ROW_COL][ROW_COL];
    unsigned int goal[ROW_COL][ROW_COL] = {
        {1, 2, 3},
        {8, 0, 4},
        {7, 6, 5}};

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
    // clock/time variables
    clock_t start, end;

    // intialized puzzle's
    int easy[ROW_COL][ROW_COL] = {{1, 3, 4}, {8, 6, 2}, {7, 5, 0}};
    int medium[ROW_COL][ROW_COL] = {{2, 8, 1}, {4, 3, 0}, {7, 6, 5}};
    int hard[ROW_COL][ROW_COL] = {{2, 8, 1}, {4, 6, 3}, {7, 5, 0}};
    int worst[ROW_COL][ROW_COL] = {{5, 6, 7}, {4, 0, 8}, {3, 2, 1}};
    int prefered[ROW_COL][ROW_COL] = {{1, 2, 3}, {4, 5, 6}, {8, 7, 0}};

    // instance of object puzzle
    Puzzle puzzle1(easy);
    Puzzle puzzle2(medium);
    Puzzle puzzle3(hard);
    Puzzle puzzle4(worst);
    Puzzle puzzle5(prefered);

    // welcome
    std::cout << "+=================================+\n";
    std::cout << "|         8-Puzzel Solver         |\n";
    std::cout << "|     Balagtas, Cardiño, Gomez    |\n";
    std::cout << "+=================================+\n";

    // puzzle 1 test
    {
        std::cout << "\nInitial State\n";
        start = clock();
        puzzle1.PrintBoard();
        end = clock();

        std::cout << "T(N) = " << ((double)(end - start)) / CLOCKS_PER_SEC << "\n";
        std::cout << "Is Goal? " << puzzle1.IsGoal() << "\n\n";
    }

    std::cout << std::endl;
    system("pause");
    return 0;
}

/* puzzle public functions */
Puzzle::Puzzle(int puzzle[ROW_COL][ROW_COL])
{
    this->setPuzzle(puzzle);
}

bool Puzzle::IsGoal()
{
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
    COUNTER = 0;
    for (ROW = 0; ROW < ROW_COL; ROW++)
    {
        for (COL = 0; COL < ROW_COL; COL++)
            std::cout << "+---";
        std::cout << "+\n";

        for (COL = 0; COL < ROW_COL; COL++)
        {
            // to string is just temporary
            std::string result = (this->PuzzleValue(ROW, COL) == 0) ? " " : std::to_string(this->PuzzleValue(ROW, COL));
            std::cout << "| " << result << " ";
            COUNTER++;
        }

        std::cout << "|\n";
    }

    for (COL = 0; COL < ROW_COL; COL++)
        std::cout << "+---";
    std::cout << "+\n";
}

// other class functions