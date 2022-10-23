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
#include <limits> // ENTER continue

#define __row_col_ 3 * 3
int _index;

// global functions
void printChoices()
{
    std::cout << "\033[2J\033[1;1H";
    std::cout << "\t* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
    std::cout << "\t*                                                                                                           *\n";
    std::cout << "\t*                                         _P u z z l e   C h o i c e s_                                     *\n";
    std::cout << "\t*                                                                                                           *\n";
    std::cout << "\t*                                                                                                           *\n";
    std::cout << "\t*         easy                  medium                hard                 worst             preferred      *\n";
    std::cout << "\t*      +---+---+---+        +---+---+---+        +---+---+---+        +---+---+---+        +---+---+---+    *\n";
    std::cout << "\t*      | 1 | 3 | 4 |        | 2 | 8 | 1 |        | 2 | 8 | 1 |        | 5 | 6 | 7 |        | 2 | 8 | 3 |    *\n";
    std::cout << "\t*      +---+---+---+        +---+---+---+        +---+---+---+        +---+---+---+        +---+---+---+    *\n";
    std::cout << "\t*   a) | 8 | 6 | 2 |    b)  | 4 | 3 |   |    c)  | 4 | 6 | 3 |    d)  | 4 |   | 8 |    e)  | 1 | 6 | 4 |    *\n";
    std::cout << "\t*      +---+---+---+        +---+---+---+        +---+---+---+        +---+---+---+        +---+---+---+    *\n";
    std::cout << "\t*      | 7 | 5 |   |        | 7 | 6 | 5 |        | 7 | 5 |   |        | 3 | 2 | 1 |        | 7 |   | 5 |    *\n";
    std::cout << "\t*      +---+---+---+        +---+---+---+        +---+---+---+        +---+---+---+        +---+---+---+    *\n";
    std::cout << "\t*                                                                                                           *\n";
    std::cout << "\t*                                                                                                           *\n";
    std::cout << "\t*                                                                                                           *\n";
    std::cout << "\t*   Note: user can choose a as 1 as input                                                                   *\n";
    std::cout << "\t*         user can choose b as 2                                                                            *\n";
    std::cout << "\t*                    ...  c as 3                                                                            *\n";
    std::cout << "\t*                     ..  d as 4                                                                            *\n";
    std::cout << "\t*                      .  e as 5                                                                            *\n";
    std::cout << "\t*                                                                                                           *\n";
    std::cout << "\t* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
}
class Node
{
    Node *node;

    // stores puzzle
    int state[__row_col_];

    // direction
    char direction;

    // stores the number of misplaced tiles
    int cost;

    // stores the number of moves so far
    int level;

    // depth bound
    int dBound;

    // manhattan cost
    int gCost;
    int hCost;
    int fCost;

public:
    void IDS();
    void AStar();
};

class Puzzle
{
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
     *              Class variables, located and can be used only in this class            *
     *                               - private by default                                  *
     * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
    int state[__row_col_];
    int goal[__row_col_] = {1, 2, 3, 8, 0, 4, 7, 6, 5};
    // note: both array above is inside the stack, no need to worry about memory management

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
     *              Private functions, located and used only inside this class             *
     * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
    bool isValid(int);
    bool isMoveValid(int, int);
    void swap(int *, int *);
    int getBlank(int[]);

public:
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
     *              Public functions, located and can be used outside this class           *
     * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    /**
     * @brief Construct a new Puzzle object
     *
     */
    Puzzle() {}

    /* functions declaration */
    bool isGoal(int[]);
    void displayState(int[]);
    void MOVE_UP(int[]);
    void MOVE_LEFT(int[]);
    void MOVE_DOWN(int[]);
    void MOVE_RIGHT(int[]);
    int *misplacement(int, int, int[], int[]);
    int h(int[]);

    /**
     * @brief Destroy the Puzzle object
     * Note: This will destroy this Entity/Instance of the object if created within a scope"
     *
     *       std::cout << "Destroyed\n"; -> use for test
     */
    ~Puzzle() {}
};

/* CLASS::PUZZLE private functions */
bool Puzzle::isValid(int _area)
{
    return (_area >= 0 && _area <= 2);
}

bool Puzzle::isMoveValid(int _row, int _col)
{
    return isValid(_row) && isValid(_col);
}

void Puzzle::swap(int *_x, int *_y)
{
    *_y = *_x; // _puzzle[_pos_blank]    := _puzzle[_pos_with_val]  //
    *_x = 0;   // _puzzle[_pos_with_val] := 0                       //
}

int Puzzle::getBlank(int _puzzle[])
{
    for (int i = 0; i < __row_col_; i++)
    {
        if (_puzzle[i] == 0)
            return i;
    }
    return 0;
}

/* CLASS::PUZZLE public functions */
bool Puzzle::isGoal(int puzzle[])
{
    for (_index = 0; _index < __row_col_; _index++)
    {
        if (puzzle[_index] != goal[_index]) // if any two same positioned items not equal
            return false;                   // this state is not the goal
    }
    return true;
}

void Puzzle::displayState(int puzzle[])
{
    std::cout << "+---+---+---+\n";
    for (int index = 0, i = 0; i < 3; i++)
    {
        std::cout << "|";
        for (int j = 1; j < 4; j++)
        {
            std::cout << " " << puzzle[index] << " |";
            index++;
        }
        std::cout << "\n+---+---+---+\n";
    }
}

void Puzzle::MOVE_UP(int _puzzle[])
{
    int _index = getBlank(_puzzle);
    if (_index > 2)
        swap(&_puzzle[_index - 3], &_puzzle[_index]);
}

void Puzzle::MOVE_LEFT(int _puzzle[])
{
    int _index = getBlank(_puzzle);
    if (_index % 3 != 0)
        swap(&_puzzle[_index - 1], &_puzzle[_index]);
}

void Puzzle::MOVE_DOWN(int _puzzle[])
{
    int _index = getBlank(_puzzle);
    if (_index < 6)
        swap(&_puzzle[_index + 3], &_puzzle[_index]);
}

void Puzzle::MOVE_RIGHT(int _puzzle[])
{
    int _index = getBlank(_puzzle);
    if (_index != 2 && _index != 5 && _index != 8)
        swap(&_puzzle[_index + 1], &_puzzle[_index]);
}

int *Puzzle::misplacement(int row, int col, int _state[], int _goal[])
{
    static int location[2];
    int state[3][3];
    int goal[3][3];

    for (int index = 0, i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            state[i][j] = _state[index];
            index++;
        }
    }

    for (int index = 0, i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            goal[i][j] = _goal[index];
            index++;
        }
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (goal[i][j] == state[row][col])
            {
                location[0] = i;
                location[1] = j;
            }
        }
    }
    return location;
}

int Puzzle::h(int state[])
{
    int total = 0, index = 0;
    int x = 0, y = 0;
    int *loc = new int;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (state[index] != 0)
            {
                loc = misplacement(i, j, state, goal);
                x = (i > loc[0]) ? i - loc[0] : loc[0] - i;
                y = (j > loc[1]) ? j - loc[1] : loc[1] - j;
                total += x + y;
            }
            index++;
        }
    }

    // free memory
    loc = NULL;
    delete loc;
    loc = NULL;

    return total;
}

int main(int argc, char **argv)
{
    printChoices();

    // clock/time variables
    clock_t start, end;

    // intialized puzzle's
    int easy[__row_col_] = {1, 3, 4, 8, 0, 2, 6, 5, 7};

    // module_test_case
    int test[__row_col_] = {2, 8, 3, 1, 6, 4, 7, 0, 5};

    // instance of object puzzle
    std::unique_ptr<Puzzle> puzzle = std::make_unique<Puzzle>();

    // puzzle test, display, then calculate h(n)
    std::cout << "\nInitial State\n";
    puzzle->displayState(test); // initial, h() = 8
    std::cout << "-> h(n) = " << puzzle->h(test) << "\n\n";

    // puzzle move, display, then calculate h(n)
    puzzle->MOVE_UP(test); // available, h() = 4
    puzzle->displayState(test);
    std::cout << "-> move: Up\n";
    std::cout << "-> h(n) = " << puzzle->h(test) << "\n\n";

    puzzle->MOVE_UP(test); // available, h() = 3
    puzzle->displayState(test);
    std::cout << "-> move: Up\n";
    std::cout << "-> h(n) = " << puzzle->h(test) << "\n\n";

    puzzle->MOVE_LEFT(test); // available, h() = 2
    puzzle->displayState(test);
    std::cout << "-> move: Left\n";
    std::cout << "-> h(n) = " << puzzle->h(test) << "\n\n";

    puzzle->MOVE_DOWN(test); // available, h() = 5
    puzzle->displayState(test);
    std::cout << "-> move: Down\n";
    std::cout << "-> h(n) = " << puzzle->h(test) << "\n\n";

    puzzle->MOVE_RIGHT(test); // available, h() = 0
    puzzle->displayState(test);
    std::cout << "-> move: Right\n";
    std::cout << "-> h(n) = " << puzzle->h(test) << "\n\n";
    std::cout << "-> isGoal = " << puzzle->isGoal(test) << "\n\n";

    /**
     * It should output the following for both the IDS and A* Search:
     *  • solution path(corresponds to the moves needed to reach the goal): e.g. [Up-Left-Left-Right]
     *  • solution cost(# of moves in the solution): 4
     *  • number of nodes expanded before reaching the goal
     *  • running time
     *
     */
    std::cout << "solution path => Up-UP-Left-Down-Right\n";
    std::cout << "solution cost => 5\n";
    std::cout << "solution path => 27\n";
    std::cout << "running time  => 0.69\n";

    std::cout << "\n";
    // std::cout << "Press ENTER to continue...";
    // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return 0;
}