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

// measure the running time
double cpuTimeUsed;
clock_t start, end;

// versatile global variable(puzzle)
unsigned int counter, x, y, i, cost;

/*** OBJECT tile, to keep track of a tile in PUZZLE ***/
class TILE
{
public:
    unsigned int X;
    unsigned int Y;

    TILE(){};
    ~TILE(){};

    void set(const unsigned int &_X, const unsigned int &_Y)
    {
        this->X = _X;
        this->Y = _Y;
    }
};

class DIRECTION
{
public:
    string move;

    void setDirection(const char &move)
    {
        if (move == 'U')
            this->move = "UP";
        if (move == 'L')
            this->move = "LEFT";
        if (move == 'D')
            this->move = "DOWN";
        if (move == 'R')
            this->move = "RIGHT";
        else
            this->move = "START";
    }

    DIRECTION(){};
    ~DIRECTION(){};
};

/*** OBJECT puzzle ***/
class PUZZLE
{
    // The Goal State
    const unsigned int goalState[ROW_COL][ROW_COL] = {{1, 2, 3}, {8, 0, 4}, {7, 6, 5}};

    int *getLoc(int &_row, int &_col, const unsigned int board[][ROW_COL])
    {
        static int location[2];
        for (x = 0; x < row; x++)
        {
            for (y = 0; y < col; y++)
            {
                if (board[x][y] == goalState[_row][_col])
                {
                    location[0] = x;
                    location[1] = y;
                }
            }
        }
        return location;
    }

public:
    PUZZLE *parent;                             // for backtracking the parent node of this current puzzle
    unsigned int board[ROW_COL][ROW_COL] = {0}; // puzzle object must have a board
    unsigned int depth;                         // depth attribute that will be used in IDS
    TILE blank;                                 // a puzzle must have a coordinate(puzzle) of where the blank tile is
    DIRECTION direction;                        // board move (UP, DOWN, LEFT, RIGHT)

    /**
     * @note - this is a Contructor that used to Construct a new PUZZLE object
     *       - this function will set a state and set the blank tile for that state
     *       - set heuristic to (-1) to determine if it is not yet calculated
     *
     * @param state
     * @return PUZZLE*
     */
    PUZZLE(){};

    PUZZLE(unsigned int puzzle[][ROW_COL])
    {
        for (x = 0; x < row; x++)
        {
            for (y = 0; y < col; y++)
            {
                if (puzzle[x][y] == 0)
                    this->blank.set(x, y);
                this->board[x][y] = puzzle[x][y];
            }
        }
    };

    /**
     * @note  - we also provided a deconstructor...
     *          Destructor - is an instance member function which is invoked
     *          automatically whenever an object is going to be destroyed.
     *          Meaning, a destructor is the last function that is going to
     *          be called before an object is destroyed.
     */
    ~PUZZLE()
    {
        free(parent);
    };

    // PUZZLE functions, when a puzzle object is created, it can use this functionalities (implemented in public)
    bool isGoal() const
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

    void display() const
    {
        for (x = 0; x < row; x++)
        {
            cout << "\t                                                  ";
            for (y = 0; y < col; y++)
                cout << "+---";
            cout << "+\n";

            cout << "\t                                                  ";
            for (y = 0; y < col; y++)
            {
                cout << "| ";
                if (this->board[x][y] == 0)
                    cout << " ";
                else
                    cout << this->board[x][y];
                cout << " ";
            }
            cout << "|\n";
        }

        cout << "\t                                                  ";
        for (y = 0; y < col; y++)
            cout << "+---";
        cout << "+\n";
        cout << "\t                                                  "
             << "   " << this->direction.move << "\n";
    }

    int f()
    {
        int heur = 0, row_diff = 0, col_diff = 0;
        int *location = nullptr;

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (goalState[i][j] != 0)
                {
                    location = getLoc(i, j, this->board);
                    row_diff = (i > location[0]) ? i - location[0] : location[0] - i;
                    col_diff = (j > location[1]) ? j - location[1] : location[1] - j;
                    heur += col_diff + row_diff;
                }
            }
        }

        location = nullptr;
        delete location;
        location = nullptr;
        // g(x) + h(n)
        return this->depth + heur;
    }

    /**
     * @note this function is used for checking the state is already in the visited list
     *
     * @param a
     * @param b
     *
     *  compare each state and return if they were equally match or not
     *
     * @return true/false
     */
    bool compare(unsigned int _board[][ROW_COL]) const
    {
        for (x = 0; x < row; x++)
        {
            for (y = 0; y < col; y++)
            {
                if (this->board[x][y] != _board[x][y])
                    return false;
            }
        }
        return true;
    }

    // get total cost for expansion
    int getCost()
    {
        cost = 0;
        while (this->parent != nullptr)
        {
            cost++;
            this->parent = this->parent->parent;
        }
        return cost;
    }

    /**
     * @brief check if move is possible
     *
     * @param state
     * @param direction
     * @return true/false
     */
    bool canMoveUp() const
    {
        if (this->blank.X > 0)
            return true;
        return false;
    }

    bool canMoveLeft() const
    {
        if (this->blank.Y > 0)
            return true;
        return false;
    }

    bool canMoveDown() const
    {
        if (this->blank.X < ROW_COL - 1)
            return true;
        return false;
    }

    bool canMoveRight() const
    {
        if (this->blank.Y < ROW_COL - 1)
            return true;
        return false;
    }

    // puzzle actions
    PUZZLE *moveUp()
    {
        PUZZLE *temp = new PUZZLE(this->board);
        temp->parent = this;
        temp->depth = this->depth + 1;

        temp->direction.move = "Up";
        temp->board[temp->blank.X][temp->blank.Y] = temp->board[temp->blank.X - 1][temp->blank.Y];
        temp->blank.X--;
        temp->board[temp->blank.X][temp->blank.Y] = 0;
        return temp;
    }

    PUZZLE *moveLeft()
    {
        PUZZLE *temp = new PUZZLE(this->board);
        temp->parent = this;
        temp->depth = this->depth + 1;

        temp->direction.move = "Left";
        temp->board[temp->blank.X][temp->blank.Y] = temp->board[temp->blank.X][temp->blank.Y - 1];
        temp->blank.Y--;
        temp->board[temp->blank.X][temp->blank.Y] = 0;
        return temp;
    }

    PUZZLE *moveDown()
    {
        PUZZLE *temp = new PUZZLE(this->board);
        temp->parent = this;
        temp->depth = this->depth + 1;

        temp->direction.move = "Down";
        temp->board[temp->blank.X][temp->blank.Y] = temp->board[temp->blank.X + 1][temp->blank.Y];
        temp->blank.X++;
        temp->board[temp->blank.X][temp->blank.Y] = 0;
        return temp;
    }

    PUZZLE *moveRight()
    {
        PUZZLE *temp = new PUZZLE(this->board);
        temp->parent = this;
        temp->depth = this->depth + 1;

        temp->direction.move = "Right";
        temp->board[temp->blank.X][temp->blank.Y] = temp->board[temp->blank.X][temp->blank.Y + 1];
        temp->blank.Y++;
        temp->board[temp->blank.X][temp->blank.Y] = 0;
        return temp;
    }
};

/*** @note This contains the list of State of Puzzle ***/
class STATE
{
public:
    PUZZLE *state;
    STATE *next;

    STATE(){};
    ~STATE(){};
};

class NODE
{
public:
    STATE *node = nullptr; // an attribute for initializing an empty list of states

    PUZZLE *front()
    {
        PUZZLE *tempNode = nullptr;
        if (node != nullptr)
        {
            tempNode = node->state;
            STATE *temp = node;
            node = node->next;
            delete temp;
        }
        return tempNode;
    }

    /**
     * @brief - use to get the best state
     */
    PUZZLE *bestState()
    {
        int minimum = 0;
        STATE *temp = node;
        STATE *previous = nullptr;
        STATE *lowheur = nullptr;
        PUZZLE *best = nullptr;

        if (node->next == nullptr)
        {
            best = node->state;
            delete node;
            node = nullptr;
            return best;
        }

        minimum = temp->state->f();
        lowheur = temp;

        while (temp->next != nullptr)
        {
            int f = temp->next->state->f();
            if (f < minimum)
            {
                previous = temp;
                lowheur = temp->next;
                minimum = f;
            }
            temp = temp->next;
        }

        best = lowheur->state;

        if (node != nullptr)
        {
            if (lowheur == node)
                return front();
            if (lowheur->next == nullptr)
                previous->next = nullptr;
            else
                previous->next = lowheur->next;
        }

        delete lowheur;
        return best;
    }

    /**
     * @brief - this is a getter function that will use the Puzzle to insert on the Front of the List
     */
    void insert(PUZZLE *puzzle)
    {
        STATE *tempNode = new STATE;
        tempNode->state = puzzle;
        tempNode->next = nullptr;
        if (node != nullptr)
            tempNode->next = node;
        node = tempNode;
    }

    /**
     * @brief - this returns false or true if the given state is already in the list or not
     *
     * @param state
     * @return true/false - this helps preventing insertion of the same node twice into the list
     */
    bool isListed(PUZZLE *state)
    {
        STATE *list = node;
        while (list != nullptr)
        {
            if ((state->compare(list->state->board)))
                return false;
            list = list->next;
        }
        return true;
    }

    NODE(){};
    ~NODE(){};
};

/*** USERS BASE TERMINAL INPUT AND DISPLAY ***/
void printChoices()
{
    cout << "\n\t* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n"
         << "\t*                                                                                                           *\n"
         << "\t*                                         _P u z z l e   C h o i c e s_                                     *\n"
         << "\t*                                                                                                           *\n"
         << "\t*                                                                                                           *\n"
         << "\t*         easy                  medium                hard                 worst             preferred      *\n"
         << "\t*      +---+---+---+        +---+---+---+        +---+---+---+        +---+---+---+        +---+---+---+    *\n"
         << "\t*      | 1 | 3 | 4 |        | 2 | 8 | 1 |        | 2 | 8 | 1 |        | 5 | 6 | 7 |        | 0 | 0 | 0 |    *\n"
         << "\t*      +---+---+---+        +---+---+---+        +---+---+---+        +---+---+---+        +---+---+---+    *\n"
         << "\t*   1. | 8 | 6 | 2 |    2.  | 0 | 4 | 3 |    3.  | 4 | 6 | 3 |    4.  | 4 |   | 8 |    5.  | 0 | _ | 0 |    *\n"
         << "\t*      +---+---+---+        +---+---+---+        +---+---+---+        +---+---+---+        +---+---+---+    *\n"
         << "\t*      | 7 | 0 | 5 |        | 7 | 6 | 5 |        | 7 | 5 |   |        | 3 | 2 | 1 |        | 0 | 0 | 0 |    *\n"
         << "\t*      +---+---+---+        +---+---+---+        +---+---+---+        +---+---+---+        +---+---+---+    *\n"
         << "\t*                                                                                                           *\n"
         << "\t*                                                                                                           *\n"
         << "\t* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
}

/**
 * @note - validate number if valid on our option list
 *
 * @param num
 * @return true/false
 */
bool isOptionValid(const int &num)
{
    return num <= 0 || num >= 6;
}

/**
 * @brief loop until reaching the correct input
 *
 * @param input
 */
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

/**
 * @brief - state will create a new state that acceps array which contains tile arrangment
 *        - which also gets and set the state'puzzle blank tile
 *
 *        - set the depth limit
 *        - set move
 *        - and set parent of the state
 *
 * @param board := array from the main function that gets -> (easy, medium, hard, worst, preferred)
 * @return created state
 */
PUZZLE *initialState(unsigned int board[][ROW_COL])
{
    PUZZLE *state = new PUZZLE(board);
    state->depth = 0;
    state->direction.move = "Start";
    state->parent = nullptr;
    return state;
}

void solutionPath(PUZZLE *node)
{
    // If we hit the end of list, we return from there. End of recursion.
    if (node == nullptr)
        return;
    if (node->direction.move[0] != 'S')
    {
        // Move one node forward towards the end of list.
        solutionPath(node->parent);
        // While coming back from the end of list, start printing the node values. Last node will be first one in recursive open.
        std::cout << node->direction.move[0] << " ";
    }
}

/**
 * @note - this will display the path -> puzzle by puzzle
 *
 * @param node
 */
void displayPath(PUZZLE *node)
{
    if (node == nullptr)
        return;
    if (node->direction.move[0] != 'S')
    {
        displayPath(node->parent);
        node->display();
    }
}

/*** Algorithms ***/
void AStar_Search(PUZZLE *state)
{
    NODE openList, closedList;

    openList.insert(state);

    counter = 0;

    while (openList.node != nullptr)
    {
        PUZZLE *puzzle = openList.bestState();
        closedList.insert(puzzle);

        cout << counter << "\n";

        if (puzzle->isGoal())
        {
            cout << "\tGenerating A* Path...\n\n";
            displayPath(puzzle);
            cout << "\n\t Agent is using A*...";
            cout << "\n\t Solution Path: ";
            solutionPath(puzzle);
            cout << "\n\t Solution Cost  = " << puzzle->getCost();
            cout << "\n\t Expanded Nodes = " << counter;
            return;
        }

        if (puzzle->canMoveUp())
        {
            if (closedList.isListed(puzzle->moveUp()))
                openList.insert(puzzle->moveUp());
        }

        if (puzzle->canMoveLeft())
        {
            if (closedList.isListed(puzzle->moveLeft()))
                openList.insert(puzzle->moveLeft());
        }

        if (puzzle->canMoveDown())
        {
            if (closedList.isListed(puzzle->moveDown()))
                openList.insert(puzzle->moveDown());
        }

        if (puzzle->canMoveRight())
        {
            if (closedList.isListed(puzzle->moveRight()))
                openList.insert(puzzle->moveRight());
        }

        counter++;
    }
}

void IDS_Search(PUZZLE *initialState)
{
    cout << "\n\t Agent is using IDS...";
    i = 0, counter = 0;

    while (true)
    {
        NODE closed, open;

        open.insert(initialState);
        while (open.node != nullptr)
        {
            PUZZLE *puzzle = open.front();

            if (puzzle->depth > i)
                continue;

            closed.insert(puzzle);

            if (puzzle->isGoal())
            {
                cout << "\n\t Solution Path: ";
                solutionPath(puzzle);
                cout << "\n\t Solution Cost  = " << puzzle->getCost();
                cout << "\n\t Expanded Nodes = " << counter;
                return;
            }

            counter++;

            if (puzzle->canMoveUp())
            {
                if (closed.isListed(puzzle->moveUp()))
                    open.insert(puzzle->moveUp());
            }

            if (puzzle->canMoveLeft())
            {
                if (closed.isListed(puzzle->moveLeft()))
                    open.insert(puzzle->moveLeft());
            }

            if (puzzle->canMoveDown())
            {
                if (closed.isListed(puzzle->moveDown()))
                    open.insert(puzzle->moveDown());
            }

            if (puzzle->canMoveRight())
            {
                if (closed.isListed(puzzle->moveRight()))
                    open.insert(puzzle->moveRight());
            }
        }

        i++;
    }
}

int main(int argc, char **argv)
{
    unsigned int user_input = 0, end = 0;
    PUZZLE *init = new PUZZLE();

    // PUZZLE default config
    unsigned int easy[][ROW_COL] = {{1, 3, 4}, {8, 6, 2}, {7, 0, 5}};
    unsigned int medium[][ROW_COL] = {{2, 8, 1}, {0, 4, 3}, {7, 6, 5}};
    unsigned int hard[][ROW_COL] = {{2, 8, 1}, {4, 6, 3}, {7, 5, 0}};
    unsigned int worst[][ROW_COL] = {{5, 6, 7}, {4, 0, 8}, {3, 2, 1}};
    unsigned int input[][ROW_COL] = {0};

    do
    {
        // select options and select board to initialize
        selectOption(user_input);

        if (user_input == 5)
        {
            cout << "\n\t Board Configuration Input";
            cout << "\n\t Separated with spaces, upon filling each tile...\n";
            for (x = 0; x < row; x++)
            {
                cout << "\n\t Row: " << x + 1 << "\n\t ";
                for (y = 0; y < col; y++)
                    cin >> input[x][y];
            }
            init = initialState(input);
        }

        if (user_input == 1)
            init = initialState(easy);
        if (user_input == 2)
            init = initialState(medium);
        if (user_input == 3)
            init = initialState(hard);
        if (user_input == 4)
            init = initialState(worst);

        AStar_Search(init);

        cout << "\n\t=================================================================================\n";
    } while (!(end >= 1 && end <= 1));

    delete init;
    init = nullptr;
    return 0;
}