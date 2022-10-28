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

/*** OBJECT tile, to keep track of a tile in PUZZLE ***/
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

/*** OBJECT puzzle***/
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

    // PUZZLE functions
    bool isGoal();

    void printBoard();
};

/*** LIST ***/
class STATE
{
public:
    PUZZLE *state;
    STATE *next;

    STATE(){};
    ~STATE(){};
};

/*** FUNCTIONS to get Heuristic ***/
int distBetween2Tiles(PUZZLE *state, BLANK correctTile)
{
    for (int row = 0; row < ROW_COL; row++)
    {
        for (int col = 0; col < ROW_COL; col++)
        {
            int i = correctTile.X, j = correctTile.Y;

            if (state->board[row][col] == goalState[i][j])
            {
                int localDist = abs(i - row) + abs(j - col);
                return localDist;
            }
        }
    }
    return 0;
}

int getManhattanDistance(PUZZLE *state)
{
    // if already calculated previously, just return that value
    if (state->heuristic != -1)
        return state->heuristic;

    int dist = 0;      // variable that will keep the total manhattan distance
    BLANK correctTile; // holds the index (i,j) of a tile in the given state

    for (int i = 0; i < ROW_COL; i++)
    {
        // loop through all the tiles of the given state
        for (int j = 0; j < ROW_COL; j++)
        {
            if (state->board[i][j] == goalState[i][j]) // skip if the tile is in the correct place
                continue;
            else
            {
                // else calculate the distance between 2 tiles (goalState's tile & misplaced tile)
                correctTile.set(i, j);
                dist += distBetween2Tiles(state, correctTile); // implemented as function to make use of return keyword to terminate nested loops completely when the distance is already calculated
            }
        }
    }
    // memorizing (recording) the value so next time getting the heuristic value for this state, just return the value recorded
    // this will skip bunch of loops next time
    // useful for getting the state with the lowest heuristic value in A* search algorithm
    state->heuristic = dist + state->depth;
    return dist + state->depth;
}

// used in checking if the state is already in the visited list - notInList()    function
bool isEqual(PUZZLE *state1, PUZZLE *state2)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (state1->board[i][j] != state2->board[i][j])
                return false;
        }
    }
    return true;
}

class NODE
{
public:
    NODE(){};
    ~NODE(){};

    // initializing an empty list of states
    STATE *node = nullptr;

    PUZZLE *front()
    {
        PUZZLE *tmp = nullptr;
        if (node != nullptr)
        {
            tmp = node->state;
            STATE *temp = node;
            node = node->next;
            delete temp;
        }
        return tmp;
    }

    PUZZLE *end()
    {
        if (node->next == nullptr)
        {
            front();
            return node->state;
        }
        PUZZLE *tmp = nullptr;
        if (node != nullptr)
        {
            STATE *temp = node;
            while (temp->next != nullptr)
                temp = temp->next;
            tmp = temp->state;
            delete temp;
            temp = nullptr;
        }
        return tmp;
    }

    PUZZLE *chooseBestState()
    {
        // chooses the state on the entire list with the lowest heuristic value
        STATE *tmplist = node;
        STATE *previous;
        STATE *lowestHeuristic; // holds the state with the lowest heuristic value
        PUZZLE *bestState = nullptr;
        int min;

        if (node->next == nullptr)
        {
            // CASE 1: has only 1 node in the list, just return that. that's already the bestState since there's no other state to compare with in the first place
            bestState = node->state;
            delete node;
            node = nullptr;
            return bestState;
        }
        // finding the state with lowest hueristic value by looping through the entire list
        min = getManhattanDistance(tmplist->state); // gets the heuristic value of the first state and sets that value as the minimum
        lowestHeuristic = tmplist;                  // initially, the best state is set to the first state in the list
        while (tmplist->next != nullptr)
        {
            int dist = getManhattanDistance(tmplist->next->state);
            if (dist < min)
            {
                previous = tmplist;
                lowestHeuristic = tmplist->next;
                min = dist;
            }
            tmplist = tmplist->next; // iterate
        }

        bestState = lowestHeuristic->state;
        if (node != nullptr)
        {
            // CASE 1: bestState is found at the start of the list
            if (lowestHeuristic == node)
                return front();
            // CASE 2: bestState is at the last
            else if (lowestHeuristic->next == nullptr)
                previous->next = nullptr; // link the previous state to nullptr means removing the last state out of the list
            // CASE 3: bestState is found in the middle so unlink the middle and reconnect the list
            else
                previous->next = lowestHeuristic->next; // link the previous node and the node next to bestState.
        }
        delete lowestHeuristic;
        return bestState;
    }

    void insertToFront(PUZZLE *s)
    {
        STATE *tmp = new (STATE);
        tmp->state = s;
        tmp->next = nullptr;
        if (node != nullptr)
            tmp->next = node;
        node = tmp;
    }

    void insertToEnd(PUZZLE *s)
    {
        if (node == nullptr)
        {
            insertToFront(s);
            return;
        }
        STATE *temp = node;
        STATE *tmp = new (STATE);
        tmp->state = s;
        tmp->next = nullptr;
        while (temp->next != nullptr)
            temp = temp->next;
        temp->next = tmp;
    }

    // this returns false or true if the given state is already in the list or not
    // this helps preventing insertion of the same node twice into the list
    bool notInList(PUZZLE *state)
    {
        STATE *tmplist = node;
        while (tmplist != nullptr)
        {
            if (isEqual(state, tmplist->state))
                return false;
            tmplist = tmplist->next;
        }
        return true;
    }
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
    // cout << "                                                        PUZZLE Configuration\n";
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
    cout << blankspace << "   " << this->move_indicator << "\n";
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
PUZZLE *newState(unsigned int state[][ROW_COL])
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
PUZZLE *newInitialState(unsigned int arr[][ROW_COL])
{
    PUZZLE *state = newState(arr);
    state->depth = 0;
    state->move = 'S';
    state->move_indicator = "Initial";
    state->parent = nullptr;
    return state;
}

// moves the blank tile in a certain direction
PUZZLE *move(PUZZLE *state, char direction)
{
    PUZZLE *tmp = newState(state->board);
    tmp->parent = state;
    tmp->depth = state->depth + 1;

    // actions i.e move left, right, up and down
    if (direction == 'U')
    {
        tmp->move = 'U';
        tmp->move_indicator = "Up";
        tmp->board[tmp->blank_tile.X][tmp->blank_tile.Y] = tmp->board[tmp->blank_tile.X - 1][tmp->blank_tile.Y];
        tmp->blank_tile.X--;
        tmp->board[tmp->blank_tile.X][tmp->blank_tile.Y] = 0;
    }
    else if (direction == 'R')
    {
        tmp->move = 'R';
        tmp->move_indicator = "Right";
        tmp->board[tmp->blank_tile.X][tmp->blank_tile.Y] = tmp->board[tmp->blank_tile.X][tmp->blank_tile.Y + 1];
        tmp->blank_tile.Y++;
        tmp->board[tmp->blank_tile.X][tmp->blank_tile.Y] = 0;
    }
    else if (direction == 'D')
    {
        tmp->move = 'D';
        tmp->move_indicator = "Down";
        tmp->board[tmp->blank_tile.X][tmp->blank_tile.Y] = tmp->board[tmp->blank_tile.X + 1][tmp->blank_tile.Y];
        tmp->blank_tile.X++;
        tmp->board[tmp->blank_tile.X][tmp->blank_tile.Y] = 0;
    }
    else if (direction == 'L')
    {
        tmp->move = 'L';
        tmp->move_indicator = "Left";
        tmp->board[tmp->blank_tile.X][tmp->blank_tile.Y] = tmp->board[tmp->blank_tile.X][tmp->blank_tile.Y - 1];
        tmp->blank_tile.Y--;
        tmp->board[tmp->blank_tile.X][tmp->blank_tile.Y] = 0;
    }
    else
        return nullptr;
    return tmp;
}

// checks if it is a valid move for the blank tile
bool movable(PUZZLE *state, char direction)
{
    if (direction == 'U')
    {
        if (state->blank_tile.X > 0)
            return true;
    }
    else if (direction == 'R')
    {
        if (state->blank_tile.Y < ROW_COL - 1)
            return true;
    }
    else if (direction == 'D')
    {
        if (state->blank_tile.X < ROW_COL - 1)
            return true;
    }
    else if (direction == 'L')
    {
        if (state->blank_tile.Y > 0)
            return true;
    }
    return false;
}

int printStates(PUZZLE *state)
{
    if (state == nullptr)
        return 0;

    int i;
    i = printStates(state->parent) + 1;
    if (state->move == 'S')
        return i;
    cout << " " << state->move;
    return i;
}

int printMoves(PUZZLE *state)
{
    if (state == nullptr)
        return 0;

    int i;
    if (state->move == 'S')
        return i;
    i = printMoves(state->parent) + 1;
    state->printBoard();
    return i;
}

/*** Algorithms ***/
void heuristicSearch(PUZZLE *state)
{
    int counter = 0;
    NODE openList;
    NODE closedList;
    openList.insertToFront(state);

    while (openList.node != nullptr)
    {
        PUZZLE *bestState = openList.chooseBestState();
        closedList.insertToFront(bestState);

        if (bestState->isGoal())
        {
            printMoves(bestState);
            cout << "\n\t Agent found the solution!";
            cout << "\n\t Agent says.. this is the solution Path: ";
            int cost = printStates(bestState);
            cout << "\n\n\t Expanded Nodes = " << counter;
            cout << "\n\t Solution Cost  = " << cost - 1;
            return;
        }
        counter++;
        if (movable(bestState, 'U'))
        {
            PUZZLE *tmp = move(bestState, 'U');
            if (closedList.notInList(tmp))
            {
                openList.insertToFront(tmp);
            }
        }
        if (movable(bestState, 'R'))
        {
            PUZZLE *tmp = move(bestState, 'R');
            if (closedList.notInList(tmp))
            {
                openList.insertToFront(tmp);
            }
        }
        if (movable(bestState, 'D'))
        {
            PUZZLE *tmp = move(bestState, 'D');
            if (closedList.notInList(tmp))
            {
                openList.insertToFront(tmp);
            }
        }
        if (movable(bestState, 'L'))
        {
            PUZZLE *tmp = move(bestState, 'L');
            if (closedList.notInList(tmp))
            {
                openList.insertToFront(tmp);
            }
        }
    }
}

void blindSearch(PUZZLE *initialState)
{
    int i = 0, counter = 0;

    while (true)
    {
        NODE closed, stack;
        stack.insertToFront(initialState);
        while (stack.node != nullptr)
        {
            PUZZLE *first = stack.front();

            if (first->depth > i)
                continue;

            closed.insertToFront(first);

            if (first->isGoal())
            {
                cout << "\n\t Agent found the solution!";
                cout << "\n\t Agent says.. this is the solution Path: ";
                int cost = printStates(first);
                cout << "\n\n\t Expanded Nodes = " << counter;
                cout << "\n\t Solution Cost  = " << cost - 1;
                return;
            }
            counter++;
            if (movable(first, 'U'))
            {
                PUZZLE *tmp = move(first, 'U');
                if (closed.notInList(tmp))
                {
                    stack.insertToFront(tmp);
                }
            }
            if (movable(first, 'R'))
            {
                PUZZLE *tmp = move(first, 'R');
                if (closed.notInList(tmp))
                {
                    stack.insertToFront(tmp);
                }
            }
            if (movable(first, 'D'))
            {
                PUZZLE *tmp = move(first, 'D');
                if (closed.notInList(tmp))
                {
                    stack.insertToFront(tmp);
                }
            }
            if (movable(first, 'L'))
            {
                PUZZLE *tmp = move(first, 'L');
                if (closed.notInList(tmp))
                {
                    stack.insertToFront(tmp);
                }
            }
        }
        i++;
    }
}
int main(int argc, char **argv)
{
    unsigned int user_input = 0, end = 0;
    PUZZLE *init = nullptr;

    // PUZZLE default config
    unsigned int easy[][ROW_COL] = {{1, 3, 4}, {8, 6, 2}, {7, 0, 5}};
    unsigned int medium[][ROW_COL] = {{2, 8, 1}, {0, 4, 3}, {7, 6, 5}};
    unsigned int hard[][ROW_COL] = {{2, 8, 1}, {4, 6, 3}, {7, 5, 0}};
    unsigned int worst[][ROW_COL] = {{5, 6, 7}, {4, 0, 8}, {3, 2, 1}};
    unsigned int preferred[][ROW_COL] = {{2, 0, 1}, {4, 8, 3}, {7, 6, 5}};
    unsigned int input[][ROW_COL] = {0};

    do
    {
        selectOption(user_input);

        cout << user_input;

        if (user_input == 5)
        {
            cout << "\n\t Board Configuration Input";
            cout << "\n\t Please Input the tile arrangement for each row separated with spaces\n";
            for (x = 0; x < row; x++)
            {
                cout << "Row: " << x + 1 << "\n";
                for (y = 0; y < col; y++)
                    cin >> input[x][y];

                for (y = 0; y < col; y++)
                    cout << input[x][y];
            }
            init = newInitialState(input);
        }

        if (user_input == 1)
            init = newInitialState(easy);
        if (user_input == 2)
            init = newInitialState(medium);
        if (user_input == 3)
            init = newInitialState(hard);
        if (user_input == 4)
            init = newInitialState(worst);

        init->printBoard();
        cout << "\033[2J\033[1;1H";

        // A*
        cout << "\n\t Agent is using A*\n\t Agent is now searching for solution path...\n";
        start = clock();
        heuristicSearch(init);
        end = clock();
        cpuTimeUsed = ((double)(end - start)) / CLOCKS_PER_SEC;
        cout << "\n\t Running Time   = " << cpuTimeUsed << "\n";

        cout << "\n\t=================================================================================\n";

        // IDS
        cout << "\n\t Agent is using IDS\n\t Agent is now searching for solution path...";
        start = clock();
        blindSearch(init);
        end = clock();
        cpuTimeUsed = ((double)(end - start)) / CLOCKS_PER_SEC;
        cout << "\n\t Running Time   = " << cpuTimeUsed << "\n";

        cout << "\n\n\t press and enter (0 to continue and 1 to end program): ";
        scanf("%d", &end);
    } while (!(end >= 1 && end <= 1));

    cout << "\033[2J\033[1;1H";
    delete init;
    init = nullptr;
    return 0;
}