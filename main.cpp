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
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
     *              Class variables, located and can be used only in this class            *
     *                               - private by default                                  *
     * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
    unsigned int x, y;
    unsigned int state[ROW_COL][ROW_COL];
    unsigned int goal[ROW_COL][ROW_COL] = {{1, 2, 3}, {8, 0, 4}, {7, 6, 5}};

public:
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
     *              Public functions, located and can be used outside this class           *
     * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    /**
     * @brief Construct a new Puzzle object
     *
     */
    Puzzle() {}
    Puzzle(int _state[ROW_COL][ROW_COL])
    {
        this->SET_PUZZLE(_state);
    }

    /* functions declaration */
    bool IS_GOAL(int[3][3]);
    void DISPLAY_STATE(int[3][3]);

    // get blank (x,y)
    int GET_ROW(int[3][3]);
    int GET_COL(int[3][3]);

    // moves
    void MOVE_UP(int[3][3]);
    void MOVE_LEFT(int[3][3]);
    void MOVE_DOWN(int[3][3]);
    void MOVE_RIGHT(int[3][3]);

    /**
     * @brief Destroy the Puzzle object
     * Note: This will destroy this Entity/Instance of the object if created within a scope"
     */
    ~Puzzle()
    {
        std::cout << "Destroyed\n";
    }

private:
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
     *              Private functions, located and used only inside this class             *
     * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
    bool IS_VALID(int);
    bool IS_MOVE_VALID(int, int);
    void SWAP(int *, int *);

    bool IS_VALID_PUZZLE_NUMBER(int num)
    {
        return !((num > 8) || (num < 0));
    }

    void SET_PUZZLE(int puzzle[ROW_COL][ROW_COL])
    {
        for (ROW = 0; ROW < ROW_COL; ROW++)
        {
            for (COL = 0; COL < ROW_COL; COL++)
            {
                if (IS_VALID_PUZZLE_NUMBER(puzzle[ROW][COL]))
                    this->state[ROW][COL] = puzzle[ROW][COL];
            }
        }
    }
};

int main()
{
    // instance of object puzzle
    std::unique_ptr<Puzzle> puzzle = std::make_unique<Puzzle>();

    // clock/time variables
    clock_t start, end;

    // intialized puzzle's
    int easy[ROW_COL][ROW_COL] = {{1, 3, 4}, {8, 6, 2}, {7, 5, 0}};

    // puzzle test
    std::cout << "\nInitial State\n";
    puzzle->DISPLAY_STATE(easy);
    puzzle->MOVE_UP(easy);
    puzzle->DISPLAY_STATE(easy);

    std::cout << "\n";
    system("pause");
    // std::cout << "\033[2J\033[1;1H"; // clear screen for both windows/linux
    return 0;
}

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
    *_y = *_x;
    *_x = 0;
}

/* puzzle public functions */
bool Puzzle::IS_GOAL(int puzzle[3][3])
{
    for (ROW = 0; ROW < ROW_COL; ROW++)
    {
        for (COL = 0; COL < ROW_COL; COL++)
        {
            if (puzzle[ROW][COL] != goal[ROW][COL]) // if any two same positioned items not equal
                return false;                       // this state is not the goal
        }
    }
    return true;
}

void Puzzle::DISPLAY_STATE(int puzzle[3][3])
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
            std::string result = (puzzle[ROW][COL] == 0) ? " " : std::to_string(puzzle[ROW][COL]);
            std::cout << "| " << result << " ";
            COUNTER++;
        }

        std::cout << "|\n";
    }

    for (COL = 0; COL < ROW_COL; COL++)
        std::cout << "+---";
    std::cout << "+\n";
}

int Puzzle::GET_ROW(int puzzle[3][3])
{
    int row = 0;
    for (unsigned int i = 0; i < 3; i++)
    {
        for (unsigned int j = 0; j < 3; j++)
        {
            if (puzzle[i][j] == 0)
                row = i;
        }
    }
    return row;
}

int Puzzle::GET_COL(int puzzle[3][3])
{
    int col = 0;
    for (unsigned int i = 0; i < 3; i++)
    {
        for (unsigned int j = 0; j < 3; j++)
        {
            if (puzzle[i][j] == 0)
                col = j;
        }
    }
    return col;
}

void Puzzle::MOVE_UP(int puzzle[3][3])
{
    int _row = GET_ROW(puzzle);
    int _col = GET_COL(puzzle);

    int _area = _row - 1;
    if (IS_MOVE_VALID(_area, _col))
        SWAP(&puzzle[_area][_col], &puzzle[_row][_col]);
}

void Puzzle::MOVE_LEFT(int puzzle[3][3])
{
    int _row = GET_ROW(puzzle);
    int _col = GET_COL(puzzle);

    int _area = _col - 1;
    if (IS_MOVE_VALID(_row, _area))
        SWAP(&puzzle[_row][_area], &puzzle[_row][_col]);
}

void Puzzle::MOVE_DOWN(int puzzle[3][3])
{
    int _row = GET_ROW(puzzle);
    int _col = GET_COL(puzzle);

    int _area = _row + 1;
    if (IS_MOVE_VALID(_area, _col))
        SWAP(&puzzle[_area][_col], &puzzle[_row][_col]);
}

void Puzzle::MOVE_RIGHT(int puzzle[3][3])
{
    int _row = GET_ROW(puzzle);
    int _col = GET_COL(puzzle);

    int _area = _col + 1;
    if (IS_MOVE_VALID(_row, _area))
        SWAP(&puzzle[_row][_area], &puzzle[_row][_col]);
}

// other class functions