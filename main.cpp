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

unsigned int ROW, COL, COUNTER, _index;

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
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
     *              Class variables, located and can be used only in this class            *
     *                               - private by default                                  *
     * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
    unsigned int state[ROW_COL * ROW_COL];
    unsigned int goal[ROW_COL * ROW_COL] = {1, 2, 3, 8, 0, 4, 7, 6, 5};

private:
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
     *              Private functions, located and used only inside this class             *
     * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
    bool IS_VALID(int);
    bool IS_MOVE_VALID(int, int);
    void SWAP(int *, int *);
    int GET_BLANK(int[]);

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
    bool IS_GOAL(int[]);
    void DISPLAY_STATE(int[]);

    // moves
    void MOVE_UP(int[]);
    void MOVE_LEFT(int[]);
    void MOVE_DOWN(int[]);
    void MOVE_RIGHT(int[]);

    /**
     * @brief Destroy the Puzzle object
     * Note: This will destroy this Entity/Instance of the object if created within a scope"
     */
    ~Puzzle()
    {
        std::cout << "Destroyed\n"; // uncomment after test
    }
};

/* puzzle private functions */
bool Puzzle::IS_VALID(int _area)
{
    return (_area >= 0 && _area <= 2);
}

bool Puzzle::IS_MOVE_VALID(int _row, int _col)
{
    return IS_VALID(_row) && IS_VALID(_col);
}

void Puzzle::SWAP(int *_x, int *_y)
{
    *_y = *_x; // _puzzle[_pos_blank]    := _puzzle[_pos_with_val]
    *_x = 0;   // _puzzle[_pos_with_val] := 0
}

int Puzzle::GET_BLANK(int _puzzle[])
{
    for (int i = 0; i < 9; i++)
    {
        if (_puzzle[i] == 0)
            return i;
    }
    return 0;
}

/* puzzle public functions */
bool Puzzle::IS_GOAL(int puzzle[])
{
    for (_index = 0; _index < ROW_COL * ROW_COL; _index++)
    {
        if (puzzle[_index] != goal[_index]) // if any two same positioned items not equal
            return false;                   // this state is not the goal
    }
    return true;
}

void Puzzle::DISPLAY_STATE(int puzzle[])
{
    for (unsigned int i = 0; i < 9; i++)
        std::cout << ((i % 3 == 0) ? "\n" : " ") << puzzle[i];
    std::cout << "\n";
}

void Puzzle::MOVE_UP(int _puzzle[])
{
    int _index = GET_BLANK(_puzzle);
    if (_index > 2)
        SWAP(&_puzzle[_index - 3], &_puzzle[_index]);
}

void Puzzle::MOVE_LEFT(int _puzzle[])
{
    int _index = GET_BLANK(_puzzle);
    if (_index % 3)
        SWAP(&_puzzle[_index - 1], &_puzzle[_index]);
}

void Puzzle::MOVE_DOWN(int _puzzle[])
{
    int _index = GET_BLANK(_puzzle);
    if (_index < 6)
        SWAP(&_puzzle[_index + 3], &_puzzle[_index]);
}

void Puzzle::MOVE_RIGHT(int _puzzle[])
{
    int _index = GET_BLANK(_puzzle);
    if (_index < 6)
        SWAP(&_puzzle[_index + 3], &_puzzle[_index]);
}

int main()
{
    // clock/time variables
    clock_t start, end;

    // intialized puzzle's
    int easy[ROW_COL * ROW_COL] = {1, 3, 4, 8, 6, 2, 7, 5, 0};
    // instance of object puzzle
    std::unique_ptr<Puzzle> puzzle = std::make_unique<Puzzle>();

    // puzzle test
    std::cout << "\nInitial State\n";
    puzzle->DISPLAY_STATE(easy);
    puzzle->MOVE_UP(easy);
    puzzle->DISPLAY_STATE(easy);

    std::cout << "\n";
    system("pause");
    std::cout << "\033[2J\033[1;1H";
    return 0;
}
