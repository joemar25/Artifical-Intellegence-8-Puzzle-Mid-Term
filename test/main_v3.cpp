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
#include <memory>
#define ROW_COL 3

unsigned int ROW, COL, COUNTER;

class Node
{
    int initial;
    int parent;

    int MOVE_RIGHT;
    int MOVE_LEFT;
    int MOVE_UP;
    int MOVE_DOWN;

    int dBound;
    int gCost;
    int hCost; // manhattan cost
    int fCost;
};

class Puzzle
{
    // class variables - hidden by default
    unsigned int x, y;
    unsigned int PUZZLE_VALUE[ROW_COL][ROW_COL];
    unsigned int goal[ROW_COL][ROW_COL] = {{1, 2, 3}, {8, 0, 4}, {7, 6, 5}};

    // to initialize outside this class
public:
    // default constructor
    Puzzle(int[][ROW_COL]);
    // get Puzzle's Current state
    int PUZZLE_VALUE(int, int) const;
    // check if Current State is the Goal State
    bool IS_GOAL();
    // print the Current State
    void PRINT_BOARD();
    // get Puzzle current State
    void GET_PUZZLE();
    // "Deconstructor, This will destroy this Entity/Instance of the object if created within a scope"
    ~Puzzle() {}

private:
    // private function(s) is accesable only inside this class
    bool IS_VALID(int num)
    {
        return !((num > 8) || (num < 0));
    }

    void SET_PUZZLE(int puzzle[ROW_COL][ROW_COL])
    {
        for (ROW = 0; ROW < ROW_COL; ROW++)
        {
            for (COL = 0; COL < ROW_COL; COL++)
            {
                if (IS_VALID(puzzle[ROW][COL]))
                    this->PUZZLE_VALUE[ROW][COL] = puzzle[ROW][COL];
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
    std::unique_ptr<Puzzle> puzzle1 = std::make_unique<Puzzle>(easy);

    // if choice is easy then put easy to Puzzle Entity
    // Puzzle puzzle2(medium);
    // Puzzle puzzle3(hard);
    // Puzzle puzzle4(worst);
    // Puzzle puzzle5(prefered);

    // welcome
    std::cout << "+=================================+\n";
    std::cout << "|         8-Puzzle Solver         |\n";
    std::cout << "|     Balagtas, Cardiño, Gomez    |\n";
    std::cout << "+=================================+\n";

    // puzzle 1 test
    {
        std::cout << "\nInitial State\n";
        start = clock();
        puzzle1->PRINT_BOARD();
        end = clock();

        std::cout << "T(N) = " << ((double)(end - start)) / CLOCKS_PER_SEC << "\n";
        std::cout << "Is Goal? " << puzzle1->IS_GOAL() << "\n\n";
    }

    std::cout << "\n";
    system("pause");
    return 0;
}

/* puzzle public functions */
Puzzle::Puzzle(int puzzle[ROW_COL][ROW_COL])
{
    this->SET_PUZZLE(puzzle);
}

bool Puzzle::IS_GOAL()
{
    for (ROW = 0; ROW < ROW_COL; ROW++)
    {
        for (COL = 0; COL < ROW_COL; COL++)
        {
            if (this->PUZZLE_VALUE(ROW, COL) != goal[ROW][COL]) // if any two same positioned items not equal
                return false;                                   // this state is not the goal
        }
    }
    return true;
}

int Puzzle::PUZZLE_VALUE(int _row, int _col) const
{
    return this->PUZZLE_VALUE[_row][_col];
}

void Puzzle::PRINT_BOARD()
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
            std::string result = (this->PUZZLE_VALUE(ROW, COL) == 0) ? " " : std::to_string(this->PUZZLE_VALUE(ROW, COL));
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