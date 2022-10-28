#include <iostream>
#include <ctime>

using std::cin;
using std::cout;
using std::string;

// global final variable
#define ROW_COL 3
const unsigned int row = 3, col = 3;
const string blankspace = "\t                                                  ";

// measure the running time
double cpuTimeUsed;
clock_t start, end;

// versatile global variable(s)
unsigned int counter, x, y;
const unsigned int goalState[][ROW_COL] = {{1, 2, 3}, {8, 0, 4}, {7, 6, 5}};

class BLANK
{
public:
    unsigned int X;
    unsigned int Y;

    BLANK(){};
    ~BLANK(){};

    void set(const unsigned int &_X, const unsigned int &_Y)
    {
        this->X = _X;
        this->Y = _Y;
    }
};

class PUZZLE
{
public:
    unsigned int board[ROW_COL][ROW_COL] = {0};
    unsigned int depth;
    unsigned int heuristic;
    char move;
    string move_indicator;
    BLANK blank_tile;
    PUZZLE *parent;

    // constructors
    PUZZLE(){};
    ~PUZZLE(){};

    // puzzle functions
    bool isGoal();

    void printBoard();
};

class NODE
{
public:
    NODE(){};
    ~NODE(){};
};

/*** PUZZLE actual function(s) ***/
bool PUZZLE::isGoal()
{
    for (x = 0; x < row; x++)
    {
        for (y = 0; y < col; y++)
        {
            if (board[x][y] != goalState[x][y])
                return false;
        }
    }
    return true;
}

void PUZZLE::printBoard()
{
    cout << "\033[2J\033[1;1H";
    cout << "                                                        Puzzle Configuration\n";
    for (x = 0; x < row; x++)
    {
        cout << blankspace;
        for (y = 0; y < col; y++)
            cout
                << "+---";
        cout << "+\n";

        cout << blankspace;
        for (y = 0; y < col; y++)
        {
            string result = (this->board[x][y] == 0) ? " " : std::to_string(this->board[x][y]);
            cout << "| " << result << " ";
        }
        cout << "|\n";
    }

    cout << blankspace;
    for (y = 0; y < col; y++)
        cout << "+---";
    cout << "+\n";
}

/*** USERS BASE TERMINAL GUI AND INPUT DESIGN ***/
void printChoices()
{
    cout << "\033[2J\033[1;1H"
         << "\t* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n"
         << "\t*                                                                                                           *\n"
         << "\t*                                         _P u z z l e   C h o i c e s_                                     *\n"
         << "\t*                                                                                                           *\n"
         << "\t*                                                                                                           *\n"
         << "\t*         easy                  medium                hard                 worst             preferred      *\n"
         << "\t*      +---+---+---+        +---+---+---+        +---+---+---+        +---+---+---+        +---+---+---+    *\n"
         << "\t*      | 1 | 3 | 4 |        | 2 | 8 | 1 |        | 2 | 8 | 1 |        | 5 | 6 | 7 |        | 0 | 0 | 0 |    *\n"
         << "\t*      +---+---+---+        +---+---+---+        +---+---+---+        +---+---+---+        +---+---+---+    *\n"
         << "\t*   1. | 8 | 6 | 2 |    2.  | 4 | 3 |   |    3.  | 4 | 6 | 3 |    4.  | 4 |   | 8 |    5.  | 0 | _ | 0 |    *\n"
         << "\t*      +---+---+---+        +---+---+---+        +---+---+---+        +---+---+---+        +---+---+---+    *\n"
         << "\t*      | 7 | 5 |   |        | 7 | 6 | 5 |        | 7 | 5 |   |        | 3 | 2 | 1 |        | 0 | 0 | 0 |    *\n"
         << "\t*      +---+---+---+        +---+---+---+        +---+---+---+        +---+---+---+        +---+---+---+    *\n"
         << "\t*                                                                                                           *\n"
         << "\t*                                                                                                           *\n"
         << "\t* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
}

bool isOptionValid(const int &num)
{
    return num <= 0 || num >= 5;
}

void selectOption(unsigned int &input)
{
    printChoices();
    {
    ASK:
        do
        {
            cout << "\t  enter choice := ";
        } while (scanf("%d", &input) != 1);

        if (isOptionValid(input))
        {
            cout << "\t  invalid input. try again...\n\t\n";
            goto ASK;
        }
    }
}

/*** USEFULL actutal function(s) ***/

/**
 * @note - this function will set a state and set the blank tile for that state
 *       - set heuristic to (-1) to determine if it is not yet calculated
 *
 * @param state
 * @return PUZZLE*
 */
PUZZLE *newState(int state[][ROW_COL])
{
    PUZZLE *tmp = new (PUZZLE);
    for (x = 0; x < row; x++)
    {
        for (y = 0; y < col; y++)
        {
            // finds the blank tile
            if (state[x][y] == 0)
                tmp->blank_tile.set(x, y);
            tmp->board[x][y] = state[x][y];
            tmp->heuristic = -1;
        }
    }
    return tmp;
}

/**
 * @brief - state will create a new state that acceps array which contains tile arrangment
 *        - which also gets and set the state's blank tile
 *
 *        - set the depth limit
 *        - set move
 *        - and set parent of the state
 *
 * @param arr := array from the main function (easy, medium, hard, worst, preferred)
 * @return created state
 */
PUZZLE *newInitialState(int arr[][ROW_COL])
{
    PUZZLE *state = newState(arr);
    state->depth = 0;
    state->move = 'S';
    state->move_indicator = "Initial";
    state->parent = NULL;
    return state;
}

int main(int argc, char **argv)
{
    unsigned int user_input = 0, end = 0;
    PUZZLE *init = NULL; // change to nullptr

    // puzzle default config
    int easy[][ROW_COL] = {{1, 3, 4}, {8, 6, 2}, {7, 0, 5}};
    int medium[][ROW_COL] = {{2, 8, 1}, {0, 4, 3}, {7, 6, 5}};
    int hard[][ROW_COL] = {{2, 8, 1}, {4, 6, 3}, {7, 5, 0}};
    int worst[][ROW_COL] = {{5, 6, 7}, {4, 0, 8}, {3, 2, 1}};
    int preferred[][ROW_COL] = {{2, 0, 1}, {4, 8, 3}, {7, 6, 5}};
    int input[][ROW_COL] = {0};

    do
    {
        selectOption(user_input);
        init = newInitialState(easy);
        init->printBoard();

        // A*
        cout << "\n\t Agent is using A*\n\t Agent is now searching for solution path...";
        start = clock();
        // heuristicSearch(init);
        end = clock();
        cpuTimeUsed = ((double)(end - start)) / CLOCKS_PER_SEC;
        cout << "Running Time: " << cpuTimeUsed << "\n";

        // IDS
        cout << "\n\t Agent is using IDS\n\t Agent is now searching for solution path...";
        start = clock();
        // blindSearch(init);
        end = clock();
        cpuTimeUsed = ((double)(end - start)) / CLOCKS_PER_SEC;
        cout << "Running time: " << cpuTimeUsed << "\n\n\n";

        cout << "\t press and enter (0 to continue and 1 to end program): ";
        scanf("%d", &end);

    } while (!(end >= 1 && end <= 1));

    cout << "\033[2J\033[1;1H";
    delete init;
    init = nullptr;
    return 0;
}