#include <iostream>
#include <ctime>

using std::cin;
using std::cout;

#define ROW_COL 3

// global variables
int goalState[][ROW_COL] = {{1, 2, 3}, {8, 0, 4}, {7, 6, 5}};

class BLANK
{
    // this class is used for creating objects that keeps the position of the blank tile for each state
public:
    int x = 0, y = 0;
    void setIndex(const int &_x, const int &_y)
    {
        this->x = _x;
        this->y = _y;
    }

    BLANK() {}
    ~BLANK() {}
};

// the main data structure for storing a state of a PUZZLE like:
class PUZZLE
{
public:
    int board[ROW_COL][ROW_COL];  // tile arrangements
    BLANK blankTile;              // position (index) of the blank tile. BLANK class is implemented above
    int level, manhattanDistance; // (depth of a node (level) which is used in IDS algorithm, used in heuristicSearch)
    char move;                    // holds the previous tile movement which resulted into current state
    PUZZLE *parent;               // pointer to parent node - used to backtrack previous states

    PUZZLE(){};
    ~PUZZLE(){};
    void printPuzzle();
};

// function declarations - all of these are implemented at the bottom
PUZZLE *newState(int state[][ROW_COL]);
PUZZLE *newInitialState(int arr[][ROW_COL]);
PUZZLE *move(PUZZLE *state, char direction);
bool movable(PUZZLE *state, char direction);
bool isEqual(PUZZLE *state1, PUZZLE *state2);
bool isGoal(PUZZLE *state1);
void printState(PUZZLE *state);
int printStates(PUZZLE *state);
int getManhattanDistance(PUZZLE *state);

void blindSearch(PUZZLE *initialState);
void heuristicSearch(PUZZLE *initialState);

// data structure needed for creating a linked-list of states
class STATE
{
public:
    PUZZLE *state;
    STATE *next;

    STATE(){};
    ~STATE(){};
};

// making use of the data structure list, This is a class used for handling linked-list of states i.e:
// creating queue or stacks,
// manipulating values of a state
class NODE
{
public:
    // initializing an empty list of states
    STATE *node = nullptr;
    // accessing a node (state) in the BEGINNING of the list & popping it afterwards
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
    // accessing a node (state) in the END of the list & popping it afterwards
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
            // getManhattanDistance(bestState);
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
    void view()
    {
        // view the entire list of states
        if (node != nullptr)
        {
            STATE *tmp = node;
            while (tmp != nullptr)
            {
                cout << getManhattanDistance(tmp->state) << " ";
                tmp = tmp->next;
            }
        }
        else
            cout << "empty list";
    }

    ~NODE() {}
};

//####################################     M A I N   F U N C T I O N     ####################################
int main()
{
    int choice = 0;

    int easy[][ROW_COL] = {{1, 3, 4}, {8, 6, 2}, {7, 0, 5}};
    int medium[][ROW_COL] = {{2, 8, 1}, {0, 4, 3}, {7, 6, 5}};
    int hard[][ROW_COL] = {{2, 8, 1}, {4, 6, 3}, {7, 5, 0}};
    int worst[][ROW_COL] = {{5, 6, 7}, {4, 0, 8}, {3, 2, 1}};
    int preferred[][ROW_COL] = {{2, 0, 1}, {4, 8, 3}, {7, 6, 5}};
    int input[][ROW_COL] = {0};

    cout << "\tChoose Initial Configuration:\n"
         << "1 - Easy\n"
         << "2 - Medium\n"
         << "3 - Hard\n"
         << "4 - Worst\n"
         << "5 - Preferred Configuration\n\n"
         << "Input := ";
    cin >> choice;

    PUZZLE *init = nullptr;
    switch (choice)
    {
    case 1:
        init = newInitialState(easy);
        break;
    case 2:
        init = newInitialState(medium);
        break;
    case 3:
        init = newInitialState(hard);
        break;
    case 4:
        init = newInitialState(worst);
        break;
    case 5:
        cout << "Board Configuration Input\n";
        cout << "Please Input the tile arrangement for each row separated with spaces\n";
        for (int i = 0; i < ROW_COL; i++)
        {
            cout << "Row: " << i + 1 << "\n";
            for (int j = 0; j < ROW_COL; j++)
                cin >> input[i][j];

            for (int j = 0; j < ROW_COL; j++)
                cout << input[i][j];
        }
        init = newInitialState(input);
        break;
    default:
        cout << "Invalid input";
        return 0;
    }
    cout << "\n\n";

    if (isEqual(init, newState(easy)))
        cout << "EASY\n";
    else if (isEqual(init, newState(medium)))
        cout << "MEDIUM\n";
    else if (isEqual(init, newState(hard)))
        cout << "HARD\n";
    else if (isEqual(init, newState(worst)))
        cout << "WORST\n";
    else if (isEqual(init, newState(preferred)))
        cout << "PREFERRED\n";

    printState(init);

    double cpuTimeUsed;
    // variables for measuring the running time
    clock_t start, end;
    cout << "\n---------A* Algorithm---------\nstatus: searching...";
    start = clock();
    heuristicSearch(init);
    end = clock();
    cpuTimeUsed = ((double)(end - start)) / CLOCKS_PER_SEC;
    cout << "Running Time: " << cpuTimeUsed << "\n";

    // IDS algorithm
    cout << "\n\n\n--------IDS Algorithm---------\nstatus: searching...";
    start = clock();
    blindSearch(init);
    end = clock();
    cpuTimeUsed = ((double)(end - start)) / CLOCKS_PER_SEC;
    cout << "Running time: " << cpuTimeUsed << "\n\n\n";
}

//################     S E A R C H    A L G O R I T H M     I M P L E M E N T A T I O N S    ################
// A* SEARCH ALGORITHM

// mar
void solution_path(NODE node)
{
    while (node.front() != nullptr)
    {
        /*joemar not working*/

        node.node->state->printPuzzle();
        node.node = node.node->next;
    }
}

void heuristicSearch(PUZZLE *initialState)
{
    int counter = 0;
    NODE openList;
    NODE closedList;
    openList.insertToFront(initialState);

    while (openList.node != nullptr)
    {
        // get the best state which has the lowest heuristic value f(x) + g(x)
        PUZZLE *bestState = openList.chooseBestState();
        closedList.insertToFront(bestState); // moves to closed list

        if (isGoal(bestState))
        {
            cout << "\nstatus: solution found\n";
            cout << "\nSolution Path: ";
            int cost = printStates(bestState);
            cout << "\nNodes expanded: " << counter;
            cout << "\nSolution Cost: " << cost - 1 << "\n";
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
    solution_path(closedList);
}

// IDS algorithm
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

            if (first->level > i)
                continue;

            closed.insertToFront(first);

            if (isGoal(first))
            {
                cout << "\nstatus: solution found";
                cout << "\n\nSolution Path: ";
                int cost = printStates(first);
                cout << "\nNodes expanded: " << counter;
                cout << "\nSolution Cost: " << cost - 1 << "\n";
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

//####################################     O T H E R      F U N C T I O N S     ####################################

// function implementations
// creating a new state that acceps array which contains tile arrangment
PUZZLE *newState(int state[][ROW_COL])
{
    PUZZLE *tmp = new (PUZZLE);
    for (int i = 0; i < ROW_COL; i++)
    {
        for (int j = 0; j < ROW_COL; j++)
        {
            // finds the blank tile
            if (state[i][j] == 0)
                tmp->blankTile.setIndex(i, j);
            tmp->board[i][j] = state[i][j];
            tmp->manhattanDistance = -1; // by default sets to -1 to determine if it is not yet calculated
        }
    }
    return tmp;
}
// creating a initial state
PUZZLE *newInitialState(int arr[][ROW_COL])
{
    PUZZLE *state = newState(arr); // creating a new state that acceps array which contains tile arrangment
    state->level = 0;              // initial state has g(x) = 0
    state->move = 'S';             // S indicates starting move
    state->parent = nullptr;
    return state; // return the created state
}
// checks if tile arrangements between 2 states are equal
// used in checking if the state is already in the visited list - notInList()    function
bool isEqual(PUZZLE *state1, PUZZLE *state2)
{
    for (int i = 0; i < ROW_COL; i++)
    {
        for (int j = 0; j < ROW_COL; j++)
        {
            if (state1->board[i][j] != state2->board[i][j])
                return false;
        }
    }
    return true;
}
// checks if the goal is found by comparing each tiles
bool isGoal(PUZZLE *state1)
{
    for (int i = 0; i < ROW_COL; i++)
    {
        for (int j = 0; j < ROW_COL; j++)
        {
            if (state1->board[i][j] != goalState[i][j])
                return false;
        }
    }
    return true;
}
void printState(PUZZLE *state)
{
    for (int i = 0; i < ROW_COL; i++)
    {
        for (int j = 0; j < ROW_COL; j++)
            cout << state->board[i][j] << " | ";
        cout << "\n";
    }
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
// moves the blank tile in a certain direction
PUZZLE *move(PUZZLE *state, char direction)
{
    PUZZLE *tmp = newState(state->board);
    tmp->parent = state;
    tmp->level = state->level + 1;

    // actions i.e move left, right, up and down
    if (direction == 'U')
    {
        tmp->move = 'U';
        tmp->board[tmp->blankTile.x][tmp->blankTile.y] = tmp->board[tmp->blankTile.x - 1][tmp->blankTile.y];
        tmp->blankTile.x--;
        tmp->board[tmp->blankTile.x][tmp->blankTile.y] = 0;
    }
    else if (direction == 'R')
    {
        tmp->move = 'R';
        tmp->board[tmp->blankTile.x][tmp->blankTile.y] = tmp->board[tmp->blankTile.x][tmp->blankTile.y + 1];
        tmp->blankTile.y++;
        tmp->board[tmp->blankTile.x][tmp->blankTile.y] = 0;
    }
    else if (direction == 'D')
    {
        tmp->move = 'D';
        tmp->board[tmp->blankTile.x][tmp->blankTile.y] = tmp->board[tmp->blankTile.x + 1][tmp->blankTile.y];
        tmp->blankTile.x++;
        tmp->board[tmp->blankTile.x][tmp->blankTile.y] = 0;
    }
    else if (direction == 'L')
    {
        tmp->move = 'L';
        tmp->board[tmp->blankTile.x][tmp->blankTile.y] = tmp->board[tmp->blankTile.x][tmp->blankTile.y - 1];
        tmp->blankTile.y--;
        tmp->board[tmp->blankTile.x][tmp->blankTile.y] = 0;
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
        if (state->blankTile.x > 0)
            return true;
    }
    else if (direction == 'R')
    {
        if (state->blankTile.y < ROW_COL - 1)
            return true;
    }
    else if (direction == 'D')
    {
        if (state->blankTile.x < ROW_COL - 1)
            return true;
    }
    else if (direction == 'L')
    {
        if (state->blankTile.y > 0)
            return true;
    }
    return false;
}
// return the absolute value of an integer
int abs(int x)
{
    if (x < 0)
        x -= (x * 2);
    return x;
}

// returns the distance between 2 tiles
// used in getManhattanDistance function
int distBetween2Tiles(PUZZLE *state, BLANK correctTile)
{
    for (int row = 0; row < ROW_COL; row++)
    {
        for (int col = 0; col < ROW_COL; col++)
        {
            int i = correctTile.x, j = correctTile.y;

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
    if (state->manhattanDistance != -1)
        return state->manhattanDistance;

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
                correctTile.setIndex(i, j);
                dist += distBetween2Tiles(state, correctTile); // implemented as function to make use of return keyword to terminate nested loops completely when the distance is already calculated
            }
        }
    }
    // memorizing (recording) the value so next time getting the heuristic value for this state, just return the value recorded
    // this will skip bunch of loops next time
    // useful for getting the state with the lowest heuristic value in A* search algorithm
    state->manhattanDistance = dist + state->level;
    return dist + state->level;
}

void PUZZLE::printPuzzle()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            cout << board[i][j] << " ";
    }
    cout << "\n";
}
