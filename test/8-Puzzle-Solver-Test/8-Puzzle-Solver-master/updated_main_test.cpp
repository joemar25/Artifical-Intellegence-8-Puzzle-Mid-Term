#include <iostream>
#include <ctime>

using std::cin;
using std::cout;

#define _ROWCOL_ 3

// this class is used for creating objects that keeps the position of the blank tile for each state
class BlankTile
{
public:
    int x = 0, y = 0;
    void setIndex(const int &_x, const int &_y)
    {
        this->x = _x;
        this->y = _y;
    }

    BlankTile() {}
    ~BlankTile() {}
};

// the main data structure for storing a state of a Puzzle like:
class Puzzle
{
public:
    int board[_ROWCOL_][_ROWCOL_]; // tile arrangements
    BlankTile blankTile;           // position (index) of the blank tile. BlankTile class is implemented above
    int level, manhattanDistance;  // (depth of a node (level) which is used in IDS algorithm, used in heuristicSearch)
    char move;                     // holds the previous tile movement which resulted into current state
    Puzzle *parent;                // pointer to parent node - used to backtrack previous states

    Puzzle(){};
    ~Puzzle(){};

    void printPuzzle()
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
                cout << board[i][j] << " ";
        }
        cout << "\n";
    }
};

// global variables
int goalState[][_ROWCOL_] = {{1, 2, 3}, {8, 0, 4}, {7, 6, 5}};
// function declarations - all of these are implemented at the bottom
Puzzle *newState(int state[][_ROWCOL_]);
Puzzle *newInitialState(int arr[][_ROWCOL_]);
Puzzle *move(Puzzle *state, char direction);
bool movable(Puzzle *state, char direction);
bool isEqual(Puzzle *state1, Puzzle *state2);
bool isGoal(Puzzle *state1);
void printState(Puzzle *state);
int printStates(Puzzle *state);
int getManhattanDistance(Puzzle *state);

void blindSearch(Puzzle *initialState);
void heuristicSearch(Puzzle *initialState);

// data structure needed for creating a linked-list of states
class State
{
public:
    Puzzle *state;
    State *next;

    State(){};
    ~State(){};
};

// making use of the data structure list, This is a class used for handling linked-list of states i.e:
// creating queue or stacks,
// manipulating values of a state
class List
{
public:
    // initializing an empty list of states
    State *node = NULL;
    // accessing a node (state) in the BEGINNING of the list & popping it afterwards
    Puzzle *front()
    {
        Puzzle *tmp = NULL;
        if (node != NULL)
        {
            tmp = node->state;
            State *temp = node;
            node = node->next;
            delete temp;
        }
        return tmp;
    }
    // accessing a node (state) in the END of the list & popping it afterwards
    Puzzle *end()
    {
        if (node->next == NULL)
        {
            front();
            return node->state;
        }
        Puzzle *tmp = NULL;
        if (node != NULL)
        {
            State *temp = node;
            while (temp->next != NULL)
                temp = temp->next;
            tmp = temp->state;
            delete temp;
            temp = NULL;
        }
        return tmp;
    }
    void insertToFront(Puzzle *s)
    {
        State *tmp = new (State);
        tmp->state = s;
        tmp->next = NULL;
        if (node != NULL)
            tmp->next = node;
        node = tmp;
    }
    void insertToEnd(Puzzle *s)
    {
        if (node == NULL)
        {
            insertToFront(s);
            return;
        }
        State *temp = node;
        State *tmp = new (State);
        tmp->state = s;
        tmp->next = NULL;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = tmp;
    }
    // this returns false or true if the given state is already in the list or not
    // this helps preventing insertion of the same node twice into the list
    bool notInList(Puzzle *state)
    {
        State *tmplist = node;
        while (tmplist != NULL)
        {
            if (isEqual(state, tmplist->state))
                return false;
            tmplist = tmplist->next;
        }
        return true;
    }

    Puzzle *chooseBestState()
    {
        // chooses the state on the entire list with the lowest heuristic value
        State *tmplist = node;
        State *previous;
        State *lowestHeuristic; // holds the state with the lowest heuristic value
        Puzzle *bestState = NULL;
        int min;

        if (node->next == NULL)
        {
            // CASE 1: has only 1 node in the list, just return that. that's already the bestState since there's no other state to compare with in the first place
            bestState = node->state;
            getManhattanDistance(bestState);
            delete node;
            node = NULL;
            return bestState;
        }
        // finding the state with lowest hueristic value by looping through the entire list
        min = getManhattanDistance(tmplist->state); // gets the heuristic value of the first state and sets that value as the minimum
        lowestHeuristic = tmplist;                  // initially, the best state is set to the first state in the list
        while (tmplist->next != NULL)
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
        if (node != NULL)
        {
            // CASE 1: bestState is found at the start of the list
            if (lowestHeuristic == node)
                return front();
            // CASE 2: bestState is at the last
            else if (lowestHeuristic->next == NULL)
                previous->next = NULL; // link the previous state to NULL means removing the last state out of the list
            // CASE 3: bestState is found in the middle so unlink the middle and reconnect the list
            else
                previous->next = lowestHeuristic->next; // link the previous node and the node next to bestState.
        }
        delete lowestHeuristic;
        return bestState;
    }
    void view()
    { // view the entire list of states
        if (node != NULL)
        {
            State *tmp = node;
            while (tmp != NULL)
            {
                cout << getManhattanDistance(tmp->state) << " ";
                tmp = tmp->next;
            }
        }
        else
            cout << "empty list";
    }

    ~List() {}
};

//####################################     M A I N   F U N C T I O N     ####################################
int main()
{
    int choice = 0;

    int easy[][_ROWCOL_] = {{1, 3, 4}, {8, 6, 2}, {7, 0, 5}};
    int medium[][_ROWCOL_] = {{2, 8, 1}, {0, 4, 3}, {7, 6, 5}};
    int hard[][_ROWCOL_] = {{2, 8, 1}, {4, 6, 3}, {7, 5, 0}};
    int worst[][_ROWCOL_] = {{5, 6, 7}, {4, 0, 8}, {3, 2, 1}};
    int preferred[][_ROWCOL_] = {{2, 0, 1}, {4, 8, 3}, {7, 6, 5}};
    int input[_ROWCOL_][_ROWCOL_] = {0};

    cout << "Choose initial configuration:\n";
    cout << "[1] Easy\n[2] Medium\n[3] Hard\n[4] Worst\n[5] Keyboard input\n";
    cin >> choice;

    Puzzle *init = NULL;
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
        cout << "*******Initial Board Configuration Input*******\n";
        cout << "Please Input the tile arrangement for each row separated with spaces\n";
        for (int i = 0; i < _ROWCOL_; i++)
        {
            cout << "ROW" << i + 1 << "\n";
            for (int j = 0; j < _ROWCOL_; j++)
            {
                cin >> input[i][j];
            }
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
void solution_path(List node)
{
    while (node.front() != NULL)
    {
        /*joemar not working*/

        node.node->state->printPuzzle();
        node.node = node.node->next;
    }
}

void heuristicSearch(Puzzle *initialState)
{
    int counter = 0;
    List openList;
    List closedList;
    openList.insertToFront(initialState);

    while (openList.node != NULL)
    {
        // get the best state which has the lowest heuristic value f(x) + g(x)
        Puzzle *bestState = openList.chooseBestState();
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
            Puzzle *tmp = move(bestState, 'U');
            if (closedList.notInList(tmp))
            {
                openList.insertToFront(tmp);
            }
        }
        if (movable(bestState, 'R'))
        {
            Puzzle *tmp = move(bestState, 'R');
            if (closedList.notInList(tmp))
            {
                openList.insertToFront(tmp);
            }
        }
        if (movable(bestState, 'D'))
        {
            Puzzle *tmp = move(bestState, 'D');
            if (closedList.notInList(tmp))
            {
                openList.insertToFront(tmp);
            }
        }
        if (movable(bestState, 'L'))
        {
            Puzzle *tmp = move(bestState, 'L');
            if (closedList.notInList(tmp))
            {
                openList.insertToFront(tmp);
            }
        }
    }
    solution_path(closedList);
}

// IDS algorithm
void blindSearch(Puzzle *initialState)
{
    int i = 0, counter = 0;
    while (true)
    {
        List closed, stack;
        stack.insertToFront(initialState);
        while (stack.node != NULL)
        {
            Puzzle *first = stack.front();

            if (first->level > i)
                continue;

            closed.insertToFront(first);

            if (isGoal(first))
            {
                cout << "\n"
                     << "status: solution found";
                cout << "\n"
                     << "\n"
                     << "Solution Path: ";
                int cost = printStates(first);
                cout << "\nNodes expanded: " << counter;
                cout << "\nSolution Cost: " << cost - 1 << "\n";
                return;
            }
            counter++;
            if (movable(first, 'U'))
            {
                Puzzle *tmp = move(first, 'U');
                if (closed.notInList(tmp))
                {
                    stack.insertToFront(tmp);
                }
            }
            if (movable(first, 'R'))
            {
                Puzzle *tmp = move(first, 'R');
                if (closed.notInList(tmp))
                {
                    stack.insertToFront(tmp);
                }
            }
            if (movable(first, 'D'))
            {
                Puzzle *tmp = move(first, 'D');
                if (closed.notInList(tmp))
                {
                    stack.insertToFront(tmp);
                }
            }
            if (movable(first, 'L'))
            {
                Puzzle *tmp = move(first, 'L');
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
Puzzle *newState(int state[][_ROWCOL_])
{
    Puzzle *tmp = new (Puzzle);
    for (int i = 0; i < _ROWCOL_; i++)
    {
        for (int j = 0; j < _ROWCOL_; j++)
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
Puzzle *newInitialState(int arr[][_ROWCOL_])
{
    Puzzle *state = newState(arr); // creating a new state that acceps array which contains tile arrangment
    state->level = 0;              // initial state has g(x) = 0
    state->move = 'S';             // S indicates starting move
    state->parent = NULL;
    return state; // return the created state
}
// checks if tile arrangements between 2 states are equal
// used in checking if the state is already in the visited list - notInList()    function
bool isEqual(Puzzle *state1, Puzzle *state2)
{
    for (int i = 0; i < _ROWCOL_; i++)
    {
        for (int j = 0; j < _ROWCOL_; j++)
        {
            if (state1->board[i][j] != state2->board[i][j])
                return false;
        }
    }
    return true;
}
// checks if the goal is found by comparing each tiles
bool isGoal(Puzzle *state1)
{
    for (int i = 0; i < _ROWCOL_; i++)
    {
        for (int j = 0; j < _ROWCOL_; j++)
        {
            if (state1->board[i][j] != goalState[i][j])
                return false;
        }
    }
    return true;
}
void printState(Puzzle *state)
{
    for (int i = 0; i < _ROWCOL_; i++)
    {
        for (int j = 0; j < _ROWCOL_; j++)
            cout << state->board[i][j] << " | ";
        cout << "\n";
    }
}

int printStates(Puzzle *state)
{
    if (state == NULL)
        return 0;

    int i;
    i = printStates(state->parent) + 1;
    if (state->move == 'S')
        return i;
    cout << " " << state->move;
    return i;
}
// moves the blank tile in a certain direction
Puzzle *move(Puzzle *state, char direction)
{
    Puzzle *tmp = newState(state->board);
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
        return NULL;
    return tmp;
}
// checks if it is a valid move for the blank tile
bool movable(Puzzle *state, char direction)
{
    if (direction == 'U')
    {
        if (state->blankTile.x > 0)
            return true;
    }
    else if (direction == 'R')
    {
        if (state->blankTile.y < _ROWCOL_ - 1)
            return true;
    }
    else if (direction == 'D')
    {
        if (state->blankTile.x < _ROWCOL_ - 1)
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
int distBetween2Tiles(Puzzle *state, BlankTile correctTile)
{
    for (int row = 0; row < _ROWCOL_; row++)
    {
        for (int col = 0; col < _ROWCOL_; col++)
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

int getManhattanDistance(Puzzle *state)
{
    // if already calculated previously, just return that value
    if (state->manhattanDistance != -1)
        return state->manhattanDistance;

    int dist = 0;          // variable that will keep the total manhattan distance
    BlankTile correctTile; // holds the index (i,j) of a tile in the given state

    for (int i = 0; i < _ROWCOL_; i++)
    {
        // loop through all the tiles of the given state
        for (int j = 0; j < _ROWCOL_; j++)
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