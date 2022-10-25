#include <iostream>
#include <time.h>
using namespace std;
#define BSIZE 3

// this class is used for creating objects that keeps the position of the blank tile for each state
// OOP terminologies: class, methods, attributes
class Vector2
{
public:
    int i, j;
    void setIndex(int x, int y)
    {
        i = x;
        j = y;
    }
};

// the main data structure for storing a state of a puzzle like:
struct puzzle
{
    int board[BSIZE][BSIZE]; // tile arrangements
    Vector2 blankTile;       // position (index) of the blank tile. Vector2 class is implemented above
    int level;               // depth of a node (level) which is used in IDS algorithm
    char move;               // holds the previous tile movement which resulted into current state
    int manhattanDistance;   // used in heuristicSearch
    puzzle *parent;          // pointer to parent node - used to backtrack previous states
};

// data structure needed for creating a linked-list of states
struct list
{
    puzzle *state;
    list *next;
};

// global variables
int goalState[][BSIZE] = {{1, 2, 3}, {8, 0, 4}, {7, 6, 5}};

// function declarations - all of these are implemented at the bottom
puzzle *newState(int state[][BSIZE]);
puzzle *newInitialState(int arr[][BSIZE]);
puzzle *move(puzzle *state, char direction);
bool movable(puzzle *state, char direction);
bool isEqual(puzzle *state1, puzzle *state2);
bool isGoal(puzzle *state1);
void printState(puzzle *state);
int printStates(puzzle *state);
int getManhattanDistance(puzzle *state);

void blindSearch(puzzle *initialState);
void heuristicSearch(puzzle *initialState);

// making use of the data structure list, This is a class used for handling linked-list of states i.e:
// creating queue or stacks,
// manipulating values of a state
class List
{
public:
    // initializing an empty list of states
    list *lst = NULL;
    // accessing a node (state) in the BEGINNING of the list & popping it afterwards
    puzzle *front()
    {
        puzzle *tmp = NULL;
        if (lst != NULL)
        {
            tmp = lst->state;
            list *temp = lst;
            lst = lst->next;
            delete temp;
        }
        return tmp;
    }
    // accessing a node (state) in the END of the list & popping it afterwards
    puzzle *end()
    {
        if (lst->next == NULL)
        {
            front();
            return lst->state;
        }
        puzzle *tmp = NULL;
        if (lst != NULL)
        {
            list *temp = lst;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            tmp = temp->state;
            delete temp;
            temp = NULL;
        }
        return tmp;
    }
    void insertToFront(puzzle *s)
    {
        list *tmp = new (list);
        tmp->state = s;
        tmp->next = NULL;
        if (lst != NULL)
        {
            tmp->next = lst;
        }
        lst = tmp;
    }
    void insertToEnd(puzzle *s)
    {
        if (lst == NULL)
        {
            insertToFront(s);
            return;
        }
        list *temp = lst;
        list *tmp = new (list);
        tmp->state = s;
        tmp->next = NULL;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = tmp;
    }
    // this returns false or true if the given state is already in the list or not
    // this helps preventing insertion of the same node twice into the list
    bool notInList(puzzle *state)
    {
        list *tmplist = lst;
        while (tmplist != NULL)
        {
            if (isEqual(state, tmplist->state))
            {
                return false;
            }
            tmplist = tmplist->next;
        }
        return true;
    }

    puzzle *chooseBestState()
    { // chooses the state on the entire list with the lowest heuristic value
        list *tmplist = lst;
        list *previous;
        list *survivor; // holds the state with the lowest heuristic value
        puzzle *bestState = NULL;
        int min;

        if (lst->next == NULL)
        { // CASE 1: has only 1 node in the list, just return that. that's already the bestState since there's no other state to compare with in the first place
            bestState = lst->state;
            getManhattanDistance(bestState);
            delete lst;
            lst = NULL;
            return bestState;
        }
        // finding the state with lowest hueristic value by looping through the entire list
        min = getManhattanDistance(tmplist->state); // gets the heuristic value of the first state and sets that value as the minimum
        survivor = tmplist;                         // initially, the best state is set to the first state in the list
        while (tmplist->next != NULL)
        {
            int dist = getManhattanDistance(tmplist->next->state);
            if (dist < min)
            {
                previous = tmplist;
                survivor = tmplist->next;
                min = dist;
            }
            tmplist = tmplist->next; // iterate
        }
        bestState = survivor->state;
        if (lst != NULL)
        {
            if (survivor == lst)
            { // CASE 1: bestState is found at the start of the list
                return front();
            }
            else if (survivor->next == NULL)
            {                          // CASE 2: bestState is at the last
                previous->next = NULL; // link the previous state to NULL means removing the last state out of the list
            }
            else
            {                                    // CASE 3: bestState is found in the middle so unlink the middle and reconnect the list
                previous->next = survivor->next; // link the previous node and the node next to bestState.
            }
        }
        delete survivor;
        return bestState;
    }
    void view()
    { // view the entire list of states
        if (lst != NULL)
        {
            list *tmp = lst;
            while (tmp != NULL)
            {
                cout << getManhattanDistance(tmp->state) << " ";
                tmp = tmp->next;
            }
        }
        else
            cout << "empty list";
    }
};

//####################################     M A I N   F U N C T I O N     ####################################
int main()
{

    int easy[][BSIZE] = {{1, 3, 4}, {8, 6, 2}, {7, 0, 5}};
    int medium[][BSIZE] = {{2, 8, 1}, {0, 4, 3}, {7, 6, 5}};
    int hard[][BSIZE] = {{2, 8, 1}, {4, 6, 3}, {7, 5, 0}};
    int worst[][BSIZE] = {{5, 6, 7}, {4, 0, 8}, {3, 2, 1}};
    int preferred[][BSIZE] = {{2, 0, 1}, {4, 8, 3}, {7, 6, 5}};
    int input[BSIZE][BSIZE] = {0};
    int choice = 0;
    cout << "Choose initial configuration:\n";
    cout << "[1] Easy\n[2] Medium\n[3] Hard\n[4] Worst\n[5] Keyboard input\n";
    cin >> choice;

    puzzle *init = NULL;
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
        cout << "*******Initial Board Configuration Input*******" << endl;
        cout << "Please Input the tile arrangement for each row separated with spaces" << endl
             << endl;
        for (int i = 0; i < BSIZE; i++)
        {
            cout << "ROW" << i + 1 << "\n";
            for (int j = 0; j < BSIZE; j++)
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
    cout << "Running Time: " << cpuTimeUsed << endl;

    cout << "\n\n\n--------IDS Algorithm---------\nstatus: searching...";
    start = clock();
    blindSearch(init); // IDS algorithm
    end = clock();
    cpuTimeUsed = ((double)(end - start)) / CLOCKS_PER_SEC;
    cout << "Running time: " << cpuTimeUsed << endl;
    cout << "\n\n\n\n\n\n\n\n\n";
}

//################     S E A R C H    A L G O R I T H M     I M P L E M E N T A T I O N S    ################
// A* SEARCH ALGORITHM
void heuristicSearch(puzzle *initialState)
{

    List openList;
    List closedList;
    openList.insertToFront(initialState);
    int counter = 0;
    while (openList.lst != NULL)
    {
        // get the best state which has the lowest heuristic value f(x) + g(x)
        puzzle *bestState = openList.chooseBestState();
        closedList.insertToFront(bestState); // moves to closed list

        if (isGoal(bestState))
        {
            cout << endl
                 << "status: solution found";
            cout << endl
                 << endl
                 << "Solution Path: ";
            int cost = printStates(bestState);
            cout << "\nNodes expanded: " << counter;
            cout << "\nSolution Cost: " << cost - 1 << endl;
            return;
        }
        counter++;
        if (movable(bestState, 'U'))
        {
            puzzle *tmp = move(bestState, 'U');
            if (closedList.notInList(tmp))
            {
                openList.insertToFront(tmp);
            }
        }
        if (movable(bestState, 'R'))
        {
            puzzle *tmp = move(bestState, 'R');
            if (closedList.notInList(tmp))
            {
                openList.insertToFront(tmp);
            }
        }
        if (movable(bestState, 'D'))
        {
            puzzle *tmp = move(bestState, 'D');
            if (closedList.notInList(tmp))
            {
                openList.insertToFront(tmp);
            }
        }
        if (movable(bestState, 'L'))
        {
            puzzle *tmp = move(bestState, 'L');
            if (closedList.notInList(tmp))
            {
                openList.insertToFront(tmp);
            }
        }
    }
}

// IDS algorithm
void blindSearch(puzzle *initialState)
{
    int i = 0, counter = 0;
    while (true)
    {
        List closed;
        List stack;
        stack.insertToFront(initialState);
        while (stack.lst != NULL)
        {
            puzzle *first = stack.front();

            if (first->level > i)
                continue;

            closed.insertToFront(first);

            if (isGoal(first))
            {
                cout << endl
                     << "status: solution found";
                cout << endl
                     << endl
                     << "Solution Path: ";
                int cost = printStates(first);
                cout << "\nNodes expanded: " << counter;
                cout << "\nSolution Cost: " << cost - 1 << endl;
                return;
            }
            counter++;
            if (movable(first, 'U'))
            {
                puzzle *tmp = move(first, 'U');
                if (closed.notInList(tmp))
                {
                    stack.insertToFront(tmp);
                }
            }
            if (movable(first, 'R'))
            {
                puzzle *tmp = move(first, 'R');
                if (closed.notInList(tmp))
                {
                    stack.insertToFront(tmp);
                }
            }
            if (movable(first, 'D'))
            {
                puzzle *tmp = move(first, 'D');
                if (closed.notInList(tmp))
                {
                    stack.insertToFront(tmp);
                }
            }
            if (movable(first, 'L'))
            {
                puzzle *tmp = move(first, 'L');
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
puzzle *newState(int state[][BSIZE])
{
    puzzle *tmp = new (puzzle);
    for (int i = 0; i < BSIZE; i++)
    {
        for (int j = 0; j < BSIZE; j++)
        {
            if (state[i][j] == 0) // finds the blank tile
                tmp->blankTile.setIndex(i, j);
            tmp->board[i][j] = state[i][j];
            tmp->manhattanDistance = -1; // by default sets to -1 to determine if it is not yet calculated
        }
    }
    return tmp;
}
// creating a initial state
puzzle *newInitialState(int arr[][BSIZE])
{
    puzzle *state = newState(arr); // creating a new state that acceps array which contains tile arrangment
    state->level = 0;              // initial state has g(x) = 0
    state->move = 'S';             // S indicates starting move
    state->parent = NULL;
    return state; // return the created state
}
// checks if tile arrangements between 2 states are equal
// used in checking if the state is already in the visited list - notInList()    function
bool isEqual(puzzle *state1, puzzle *state2)
{
    for (int i = 0; i < BSIZE; i++)
    {
        for (int j = 0; j < BSIZE; j++)
        {
            if (state1->board[i][j] != state2->board[i][j])
                return false;
        }
    }
    return true;
}
// checks if the goal is found by comparing each tiles
bool isGoal(puzzle *state1)
{
    for (int i = 0; i < BSIZE; i++)
    {
        for (int j = 0; j < BSIZE; j++)
        {
            if (state1->board[i][j] != goalState[i][j])
                return false;
        }
    }
    return true;
}
void printState(puzzle *state)
{
    for (int i = 0; i < BSIZE; i++)
    {
        for (int j = 0; j < BSIZE; j++)
        {
            cout << state->board[i][j] << " | ";
        }
        cout << endl;
    }
}
int printStates(puzzle *state)
{
    if (state != NULL)
    {
        int i;
        i = printStates(state->parent) + 1;
        if (state->move == 'S')
            return i;
        cout << " " << state->move;
        return i;
    }
    else
    {
        return 0;
    }
}
// moves the blank tile in a certain direction
puzzle *move(puzzle *state, char direction)
{
    puzzle *tmp = newState(state->board);
    tmp->parent = state;
    tmp->level = state->level + 1;

    // actions i.e move left, right, up and down
    if (direction == 'U')
    {
        tmp->move = 'U';
        tmp->board[tmp->blankTile.i][tmp->blankTile.j] = tmp->board[tmp->blankTile.i - 1][tmp->blankTile.j];
        tmp->blankTile.i--;
        tmp->board[tmp->blankTile.i][tmp->blankTile.j] = 0;
    }
    else if (direction == 'R')
    {
        tmp->move = 'R';
        tmp->board[tmp->blankTile.i][tmp->blankTile.j] = tmp->board[tmp->blankTile.i][tmp->blankTile.j + 1];
        tmp->blankTile.j++;
        tmp->board[tmp->blankTile.i][tmp->blankTile.j] = 0;
    }
    else if (direction == 'D')
    {
        tmp->move = 'D';
        tmp->board[tmp->blankTile.i][tmp->blankTile.j] = tmp->board[tmp->blankTile.i + 1][tmp->blankTile.j];
        tmp->blankTile.i++;
        tmp->board[tmp->blankTile.i][tmp->blankTile.j] = 0;
    }
    else if (direction == 'L')
    {
        tmp->move = 'L';
        tmp->board[tmp->blankTile.i][tmp->blankTile.j] = tmp->board[tmp->blankTile.i][tmp->blankTile.j - 1];
        tmp->blankTile.j--;
        tmp->board[tmp->blankTile.i][tmp->blankTile.j] = 0;
    }
    else
        return NULL;
    return tmp;
}
// checks if it is a valid move for the blank tile
bool movable(puzzle *state, char direction)
{
    if (direction == 'U')
    {
        if (state->blankTile.i > 0)
            return true;
    }
    else if (direction == 'R')
    {
        if (state->blankTile.j < BSIZE - 1)
            return true;
    }
    else if (direction == 'D')
    {
        if (state->blankTile.i < BSIZE - 1)
            return true;
    }
    else if (direction == 'L')
    {
        if (state->blankTile.j > 0)
            return true;
    }
    return false;
}
// return the absolute value of an integer
int abs(int x)
{
    if (x < 0)
    {
        x -= (x * 2);
    }
    return x;
}

// returns the distance between 2 tiles
// used in getManhattanDistance function
int distBetween2Tiles(puzzle *state, Vector2 correctTile)
{
    for (int y = 0; y < BSIZE; y++)
    {
        for (int x = 0; x < BSIZE; x++)
        {
            int i = correctTile.i;
            int j = correctTile.j;
            if (state->board[y][x] == goalState[i][j])
            {
                int localDist = abs(i - y) + abs(j - x);
                return localDist;
            }
        }
    }
    return 0;
}

int getManhattanDistance(puzzle *state)
{
    if (state->manhattanDistance != -1)
    { // if already calculated previously, just return that value
        return state->manhattanDistance;
    }
    int dist = 0;        // variable that will keep the total manhattan distance
    Vector2 correctTile; // holds the index (i,j) of a tile in the given state
    for (int i = 0; i < BSIZE; i++)
    { // loop through all the tiles of the given state
        for (int j = 0; j < BSIZE; j++)
        {
            if (state->board[i][j] == goalState[i][j]) // skip if the tile is in the correct place
                continue;
            else
            { // else calculate the distance between 2 tiles (goalState's tile & misplaced tile)
                correctTile.setIndex(i, j);
                dist += distBetween2Tiles(state, correctTile); // implemented as function to make use of return keyword to terminate nested loops completely when the distance is already calculated
            }
        }
    }
    // memoizing (recording) the value so next time getting the heuristic value for this state, just return the value recorded
    // this will skip bunch of loops next time
    // useful for getting the state with the lowest heuristic value in A* search algorithm
    state->manhattanDistance = dist + state->level;
    return dist + state->level;
}