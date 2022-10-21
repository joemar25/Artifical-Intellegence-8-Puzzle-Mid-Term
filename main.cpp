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
unsigned int _index;

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
    std::cout << "\t*      | 1 | 3 | 4 |        | 2 | 8 | 1 |        | 2 | 8 | 1 |        | 5 | 6 | 7 |        | 1 | 2 | 3 |    *\n";
    std::cout << "\t*      +---+---+---+        +---+---+---+        +---+---+---+        +---+---+---+        +---+---+---+    *\n";
    std::cout << "\t*   a) | 8 | 6 | 2 |    b)  | 4 | 3 |   |    c)  | 4 | 6 | 3 |    d)  | 4 |   | 8 |    e)  | 4 | 5 | 6 |    *\n";
    std::cout << "\t*      +---+---+---+        +---+---+---+        +---+---+---+        +---+---+---+        +---+---+---+    *\n";
    std::cout << "\t*      | 7 | 5 |   |        | 7 | 6 | 5 |        | 7 | 5 |   |        | 3 | 2 | 1 |        | 8 | 7 |   |    *\n";
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
    Node *parent;

    // stores puzzle
    int state[__row_col_];

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
};

class Puzzle
{
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
     *              Class variables, located and can be used only in this class            *
     *                               - private by default                                  *
     * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
    unsigned int state[__row_col_];
    unsigned int goal[__row_col_] = {1, 2, 3, 8, 0, 4, 7, 6, 5};
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
    for (unsigned int i = 0; i < 3; i++)
    {
        std::cout << "|";
        for (unsigned int j = 1; j < 4; j++)
        {
            std::cout << " " << puzzle[i + j] << " |";
        }
        // std::cout << ((i % 3 == 0) ? "+---+---+---+\n" : " ") << puzzle[i];
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

int main()
{
    printChoices();

    // clock/time variables
    clock_t start, end;

    // intialized puzzle's
    int easy[__row_col_] = {
        1, 3, 4,
        8, 0, 2,
        6, 5, 7};

    // instance of object puzzle
    std::unique_ptr<Puzzle> puzzle = std::make_unique<Puzzle>();

    // puzzle test
    std::cout << "\nInitial State\n";
    puzzle->displayState(easy);
    puzzle->MOVE_RIGHT(easy);
    puzzle->displayState(easy);

    // Solve(state, goal);

    std::cout << "\n";
    std::cout << "Press ENTER to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return 0;
}
