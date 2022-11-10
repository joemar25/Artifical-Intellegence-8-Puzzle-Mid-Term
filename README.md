<h1 align="center"> ⭐️⭐️⭐️ AI Midterm Project** ⭐️⭐️⭐️<h1>

This project is about showcasing how the IDS and A* Algorithms solve the 8-puzzle problem.

<br>

---

<br>

<p align="center"> <img align="center" src="https://sandipanweb.files.wordpress.com/2017/03/sol_a4.gif?w=676"> </p>

## Members

- [Arrlee Balagtas](https://github.com/M0isT12 "Arrlee's Github") ✌🏻
- [Joemar Cardiño](https://github.com/joemar25 "Joemar's Github") 👋🏻
- [Olan Gomez](https://github.com/Olan-G "Olan's Github") 🤙🏻

## Tables of Contents

1. [Actual Test Run](#test-run)
2. [What are the Problems we encountered?](#problems-encountered)
3. [Functions](#functions)
4. [Analysis](#analysis)
5. [References Used](#references)

<br>

---

## Test Run

<p align="center"> Input <br> <img align="center" src="https://github.com/joemar25/Files/blob/main/easy-in.PNG?raw=true"> </p>

> Note: Any Numbers from 1-5 can be put in this input statement to choose which puzzle configuration to Solve.

<p align="center"> Generated Path for A* Search <br> <img align="center" src="https://github.com/joemar25/Files/blob/main/ai-mid-term-out.PNG?raw=true" > </p>

> Only A* Search can output this, since it has less generated nodes than IDS.

### Easy

<p align="center"> Output <br> <img align="center" src="https://github.com/joemar25/Files/blob/main/easy-out.PNG?raw=true" > </p>

### Medium

<p align="center"> Output <br> <img align="center" src="https://github.com/joemar25/Files/blob/main/medium-out.PNG?raw=true" > </p>

### Hard

<p align="center"> Output <br> <img align="center" src="https://github.com/joemar25/Files/blob/main/hard-out.PNG?raw=true" > </p>

### Worst

<p align="center"> Output <br> <img align="center" src="https://github.com/joemar25/Files/blob/main/worst-out.PNG?raw=true" > </p>

> Worst is solvable but it will take about 2 to 4 minutes to solve.

<br>

---

<br>

## Problems Encountered

```txt
The developers first tried to develop the 8-puzzle using a 1-dimensional array, but they decided
to make it using a 2-dimensional array instead because it uses a less complicated algorithm. 

The developers also encountered a problem in solving more complicated problems. The more complicated
problems took a longer time to solve and the developer would not know if the program is still running
or still solving the problem. But the worst maximum time the developers encountered while running
the program was around 10 minutes. 
```

<br>

---

<br>

## Functions

```txt
This is the head area of the program.
We only use iostream (input output stream)
And use ctime which is equivalent to time.h in C, for calculating
runtime of algorithm.

We have ROW_COL 3 for (3x3) puzzle
and row 3 and col 3 for the loop

We also declare here other important variables that will be used thoughout
the program.
```

```c++

#include <iostream>
#include <ctime>

using std::cin;
using std::cout;
using std::string;

#define ROW_COL 3

const unsigned int row = 3, col = 3;

double cpuTimeUsed;
clock_t start, end;

unsigned int counter, x, y, i, cost;

```

> Note: Variable here are used in most of the functions in this program.

```txt
MAIN()
    Terminologies...
        - unsigned int var_name; -> only takes unsigned integer values (1, 2, 5, etc...)
          and not (-1, -3, 25, etc...)
        - delete pointer; -> Delete operator deallocates memory from heap

    Algo.
        1. Start
        2. Initialize user input and end with 0
        3. Initialize Puzzle as init as null (*)
        4. Initialize 2D boards (easy, medium, hard, worst) and input values as 0
        5. loop while !( end >= 1 && end <= 1 )
           A. Get user option (*)
           B. if user select's 5
              a. fill input array
              b. put input array as board for the puzzle initial state (*)
           C. if user select's 1
              a. put easy as board for the puzzle initial state
           D. if user select's 2
              a. put medium as board for the puzzle initial state
           E. if user select's 3
              a. put hard as board for the puzzle initial state
           F. if user select's 4
              a. put worst as board for the puzzle initial state
           G. display selected initial state
           H. start clock
           I. perform A* to the initialized selected Board (*)
           J. end clock
           K. calculate cpu time used for A*
           L. start clock
           M. perform IDS* to the initialized selected Board (*)
           N. end clock
           M. calculate cpu time used for IDS*
           O. end clock
        6. Dealocate Puzzle Pointer from memory
        7. End
```

```c++
int main(int argc, char **argv)
{
    unsigned int user_input = 0, end = 0;
    PUZZLE *init = nullptr;

    unsigned int easy[][ROW_COL] = {{1, 3, 4}, {8, 6, 2}, {7, 0, 5}};
    unsigned int medium[][ROW_COL] = {{2, 8, 1}, {0, 4, 3}, {7, 6, 5}};
    unsigned int hard[][ROW_COL] = {{2, 8, 1}, {4, 6, 3}, {7, 5, 0}};
    unsigned int worst[][ROW_COL] = {{5, 6, 7}, {4, 0, 8}, {3, 2, 1}};
    unsigned int input[][ROW_COL] = {0};

    do
    {
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

        init->display();

        start = clock();
        AStar_Search(init);
        end = clock();
        cpuTimeUsed = ((double)(end - start)) / CLOCKS_PER_SEC;
        cout << "\n\t Running Time   = " << cpuTimeUsed << "\n";

        cout << "\n\t=================================================================================\n";

        start = clock();
        IDS_Search(init);
        end = clock();
        cpuTimeUsed = ((double)(end - start)) / CLOCKS_PER_SEC;
        cout << "\n\t Running Time   = " << cpuTimeUsed << "\n";

        cout << "\n\n\t press and enter (0 to continue and 1 to end program): ";
        scanf("%d", &end);

    } while (!(end >= 1 && end <= 1));

    delete init;
    init = nullptr;
    return 0;
}
```

> Note: This main function will call other functions that will solve the 8 puzzle problem. Those board that had been configured will be used for determining which will be used as initial state of the puzzle.

<br>

```txt
SELECT OPTION (input)
    1. Print Choices (*)
    2. Create Label ASK
    3. Loop while input is like +, -
    4. End Loop
    5. If input option is not valid
       A. Goto 2
    6. Else end
```

```c++
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
```

> note: This function will use printChoices() that will return a print statements for user to see while the program is in execution.

<br>

```txt
 Terminologies...
        - var_type &var_name -> means no variable will be created. we will just only pass a reference of
        the original variable that will be passed in this function. 

Is Option Valid(num)
    1. If num less than or equal to 0 or num greater than or equal 6, then return true else false
```

```c++
bool isOptionValid(const int &num)
{
    return num <= 0 || num >= 6;
}
```

> Note: This is use for determining if user input number is correct.

<br>

```txt
state will create a new state that acceps array which contains tile arrangment
    - which also gets and set the state'puzzle blank tile
    - set the depth limit
    - set move
    - and set parent of the state

parameter is board which is an array from the main function that gets -> (easy, medium, hard, worst, preferred)
that will return created puzzle state


intial state (board) - return initialized Puzzle
    1. Set new Puzzle by giving it a board
    2. Set initial Depth Level 0
    3. Set initial move to Start
    4. Set parent of this Puzzle to none
    5. return this initialized puzzle state
```

```c++
PUZZLE *initialState(unsigned int board[][ROW_COL])
{
    PUZZLE *state = new PUZZLE(board);
    state->depth = 0;
    state->direction.move = "Start";
    state->parent = nullptr;
    return state;
}
```

> Note: This initial state function will return a (puzzle state) in which will be used for the algorithms (IDS and A*). See [Main()](#functions). As you will notice it will be currently be hold by (object pointer) Puzzle, that pointer will be passed to the algorithms.

<p align="center"> <img align="center" src="https://github.com/joemar25/Files/blob/main/ai-puzzle-drawing-main-logic-blue.png?raw=true" > </p>

<br>

```txt
From Puzzle class we have a function that will display the current state of the puzzle

display() - is a constant, no values here can be modified

this function is just for visualization of the puzzle state
```

```c++
PUZZLE () {
    public:
        void display() const
        {
            for (x = 0; x < row; x++)
            {
                cout << "\t                                                  ";
                for (y = 0; y < col; y++)
                    cout
                        << "+---";
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
}
```

> note: This function will output states like this:  

<p align="center"> <img align="center" src="https://github.com/joemar25/Files/blob/main/ai-8-puzzle-out-pattern.png?raw=true" > </p>

<br>

```txt
Module (Lecture 5, Page 32) A* Algorithm
    1. Put the start node s on a list called OPEN and compute f(s).
    2. If OPEN is empty, exit with failure; otherwise continue.
    3. Remove from OPEN that node whose f value is smallest and put it on a list called 
    CLOSED. Call this node n. (Resolve ties for minimal f values arbitrarily, but always 
    in favor of any goal node.)
    4. If n is a goal node, exit with the solution path obtained by tracing back the pointers; 
    otherwise continue.
    5. Expand node n, generating all its successors. If there are no successors, go 
    immediately to 2. For each successsor ni, compute f(ni).
    6. Associate with the successors not already on either OPEN or CLOSED the f values 
    just computed. Put these nodes on OPEN and direct pointers from them back to n.
    7. Associate with those successors that were already on OPEN or CLOSED the smaller 
    of the f values just computed and their previous f values. Put on OPEN those 
    successors on CLOSED whose f values were thus lowered, and redirect to n the 
    pointers from all nodes whose f values were lowered.
    8. Go to 2.

nuestra propia versión (program's version)

AStar Search(initial state)
    1. Start
    2. Set counter to 0, for number of expanded node
    3. Insert the initial state to open list
    4. if open list is not empty
        A. get best state from open list and remove state from open list (*)
        B. insert the best state to the closed list
        C. if best state is goal
            a. Display result with expanded node
            b. Go to 5
        E. if best state can move up, check if it is already existing on closed list (*)
            a. if true, then insert move up (*) to open list, else continue
        F. if best state can move left, check if it is already existing on closed list (*)
            a. if true, then insert move left (*) to open list, else continue
        G. if best state can move down, check if it is already existing on closed list (*)
            a. if true, then insert move down (*) to open list, else continue
        H. if best state can move right, check if it is already existing on closed list (*)
            a. if true, then insert move right (*) to open list, else continue
        I. increment counter by 1
        J. Go to 4
    5. End
```

```c++
void AStar_Search(PUZZLE *state)
{
    counter = 0;

    NODE openList, closedList;

    openList.insert(state);

    while (openList.node != nullptr)
    {
        PUZZLE *puzzle = openList.bestState();
        closedList.insert(puzzle);

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
```

> Note: This function is composed of helper functions that will help to solve 8 puzzle problem using A*.

<br>

```txt
node = null -> this is an attribute for initializing an empty list of states

Insert (puzzle)
    1. Create an empty State as tempNode
    2. Set tempNode state to puzzle (*)
    3. Set tempNode next to none (null)
    4. If node is not null
        A. set node -> temp node next
    5. Set temp node -> node
```

```c++
class NODE {
    public: 
        STATE *node = nullptr;

        void insert(PUZZLE *puzzle)
        {
            STATE *tempNode = new STATE;
            tempNode->state = puzzle;
            tempNode->next = nullptr;
            if (node != nullptr)
                tempNode->next = node;
            node = tempNode;
        }
};
```

> Note: This will use other class called State, that will use as a note list for checking later.

<br>

```txt
This is a blueprint of STATE, used in void insert(PUZZLE *puzzle){}

This Object blueprint is also composed of a constructor and a deconstructor. 
```

```c++
class STATE
{
    public:
        PUZZLE *state;
        STATE *next;

        STATE(){};
        ~STATE(){};
};
```

> Note: This class is all about helping us create a linked-list of states.

<br>

```txt

node = null

Best State() {
    1. initialize minimum value to 0
    2. set State templist to node / supposed temp node 
    3. set previous, lowheur to none
    4. set best Puzzle to none
    5. if node next value is none
        A. set next state to best
        B. delete node values
        C. set node to none
        D. return best puzzle state
    6. get f() of current temp state and set is to minimum - based in module 5, page 44
    7. set temp list to lowheur
    8. if temp list next value is not null
       A. set temp list next state f() to dist
       B. check if dist less than minimum - dist (misplaced distance or f() of the next node) 
          - compare with current minimum f()
            a. let previous hold templist
            b. lowheur set to temp list next
            c. set dist to minimum
        C. temp list is set to temp list next
       Goto 8
    9. set lowheur state to best
    10. if node is not equal to none
        A. check if lowheur is equal to node, then return front
        B. check if lowheur next is null, then set previous next to null, else previous next 
           set to lowheur next 
    11. free lowheur
    12. return best state from the list
}
```

```c++
class NODE {
    public:
        STATE *node = nullptr;

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
};
```

> Note: This function is used to get the best state, used in A* Search Algorithm.

<br>

```txt
h gives how far the goal node is and g the number of nodes traversed from the  
  start node to the current node.
For h, we will use the Manhattan distance, and for g, we will use the depth
  of the current node.

f() - get the total cost, that will be used to select which move to pick as best state in bestState()
    1. Initialize 0, row difference = 0, column difference 0
    2. Set a pointer to null, this will hold an array value
    3. initialize i = 0
    4. If i < row
        A. initialize j = 0
        B. if j < col
            a. if board index [i][j] is equal to 0
               a.1. set location array to get location of current board
               a.2. calculate row difference
               a.3. calculate col difference
               a.4. add total (row diff + col diff) as heur
               a.5. goto 4.B.
    5. free pointer
    6. return depth level + manhattan distance -> g(x) + h(x)
```

```c++
class PUZZLE {

    private:
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
}
```

> Note: This function return an integer which is used in bestState() function, mainly in condition
        on determining which is the best state on open list

<br>

```txt
front()
    1. create a tempnode Puzzle
    2. if node != null
        A. set node state to the tempnode
        B. create temp State and set to the node
        .
        .
        .
        .
        .
        
```

```c++
class NODE {
    public:
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
}
```

> Note: This function gives use access to the node (state) in the beginning of the list.

<br>

```txt
Is Goal ()
    1. Start 
    2. initialize x as 0
    3. if x is less than row, if false Goto 6
       A. initialize y as 0
       B. if y is less than col
          B.1. if board index is not equal to goal state index, return false
       C. increment y
       D. Goto 3.A.
    4. incremrnt x
    5. Goto 3
    6. Return true
    7. End.
```

```c++
class PUZZLE {
    public:
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
}
```

> Note: This function is used for determining if the current Puzzle state is the Goal state. Used in both Algorithm (IDS and A*)

<br>

```txt
Get Cost()
    1. Start
    2. Set Cost to 0
    3. If puzzle parent is not Null
        A. iterate cost by 1
        B. set puzzle parent to the other puzzle parent
        C. Goto 2 else Goto 3
    4. return cost
    5. End.
```

```c++
class PUZZLE {
    public:
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
}
```

> Note: This function will be used to get total cost for expansion.

<br>

```txt
This functions is for checking if the Puzzle (blank tile) possilble moves.

This is a constant function, since we are not going to modify anything
but rather return true/false depending on the result.

Can Move Up()
    1. Start
    2. check puzzle blank x if greater than 0
        A. Return true
    3. Return false
    4. End.

    explanation...
        [0,0], [0,1], [0,2]
        [1,0], [1,1], [1,2]
        [2,0], [2,1], [2,2]

    -----------------------------------------------------------
    
    for example: blank x is 1
        
        blank.x > 0 returns true

        old -> [1,0], [1,1], [1,2]
        old -> [2,0], [2,1], [2,2]
        .        .      .      .
        .        .      .      .

        since x will be decrement by 1 if blank will go up

        .        .      .      .
        .        .      .      .
        new -> [0,0], [0,1], [0,2]
        new -> [1,0], [1,1], [1,2]

        this indexes can go upwards
        
    -----------------------------------------------------------

        for example: blank x is 0
        - blank.x > 0 returns False
        - since blank x is 0 it cannot be decrement by 1,
          which will result to a negative value

    -----------------------------------------------------------

Can Move Left()
    1. Start
    2. check puzzle blank y if greater than 0
        A. Return true
    3. Return false
    4. End.

    explanation...
        [0,0], [0,1], [0,2]
        [1,0], [1,1], [1,2]
        [2,0], [2,1], [2,2]

    -----------------------------------------------------------
    
    for example: blank y is 1
        
        blank.y > 0 returns true

        old -> [0,1], [0,2]
        old -> [1,1], [1,2]
        old -> [2,1], [2,2]
        .        .      .
        .        .      .

        since x will be decrement by 1 if blank will go up

        .        .      .
        .        .      .
        new -> [0,0], [0,1]
        new -> [1,0], [1,1]
        new -> [2,0], [2,1]

        this indexes can go left

    -----------------------------------------------------------
    
    for example: blank y is 0
        - blank.y > 0 returns False
        - since blank y is 0 it cannot be decrement by 1,
          which will result to a negative value

    -----------------------------------------------------------

Can Move Down()
    1. Start
    2. check puzzle blank x if less than 2
        A. Return true
    3. Return false
    4. End.

    explanation...
        [0,0], [0,1], [0,2]
        [1,0], [1,1], [1,2]
        [2,0], [2,1], [2,2]

    -----------------------------------------------------------
    
    for example: blank x is 1
        
        blank.x < 2 returns true

        old -> [0,0], [0,1], [0,2]
        old -> [1,0], [1,1], [1,2]
        .        .      .      .
        .        .      .      .

        since x will be increment by 1 if blank will go down

        .        .      .      .
        .        .      .      .
        new -> [1,0], [1,1], [1,2]
        new -> [2,0], [2,1], [2,2]

        this indexes can go downwards
        
    -----------------------------------------------------------

        for example: blank x is 2
        - blank.x < 2 returns False
        - since blank x is 2 it cannot be increment by 1,
          which will result to a out of bounce

    -----------------------------------------------------------

Can Move Right()
    1. Start
    2. check puzzle blank y if less than 2
        A. Return true
    3. Return false
    4. End.

    explanation...
        [0,0], [0,1], [0,2]
        [1,0], [1,1], [1,2]
        [2,0], [2,1], [2,2]

    -----------------------------------------------------------
    
    for example: blank y is 1
        
        blank.y < 2 returns true

        old -> [0,0], [0,1]
        old -> [1,0], [1,1]
        old -> [2,0], [2,1]
        .        .      .
        .        .      .

        since x will be increment by 1 if blank will go up

        .        .      .
        .        .      .
        new -> [0,1], [0,2]
        new -> [1,1], [1,2]
        new -> [2,1], [2,2]

        this indexes can go right

    -----------------------------------------------------------
    
    for example: blank y is 2
        - blank.y < 2 returns False
        - since blank y is 2 it cannot be increment by 1,
          which will result to a out of bounce

    -----------------------------------------------------------

```

<p align="center"> <img align="center" src="https://github.com/joemar25/Files/blob/main/ai-puzzle-can-move-function.png?raw=true" > </p>

```c++
class PUZZLE {
    public:
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
}
```

> Note: Used in both algorithms.

<br>

```txt

Move the Puzzle (blank tile). Depending on the statement in (A* and IDS), the function
here will return a state in which the puzzle tile is moved on a specific area of the board.

```

```c++
class PUZZLE {
    public: 
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
}
```

<p align="center"> <img align="center" src="https://github.com/joemar25/Files/blob/main/ai-puzzle-can-move-u.png?raw=true" > </p>

<p align="center"> <img align="center" src="https://github.com/joemar25/Files/blob/main/ai-puzzle-can-move-l.png?raw=true" > </p>

<p align="center"> <img align="center" src="https://github.com/joemar25/Files/blob/main/ai-puzzle-can-move-d.png?raw=true" > </p>

<p align="center"> <img align="center" src="https://github.com/joemar25/Files/blob/main/ai-puzzle-can-move-r.png?raw=true" > </p>

> Note: This is used after checking if the Puzzle (tile) can move on a specific area which is used in two Algorithms.

<br>

```txt
display
```

```c++
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
```

> Note:

<br>

```txt
```

```c++
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
```

> Note:

<br>

```txt
```

```c++
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
```

> Note:

<br>

---

<br>

## Analysis

<br>

---

<br>

## Credits

Creator of all illustrations  : [Joemar](https://github.com/joemar25 "Joemar's Github")

## References

- <https://faramira.com/solving-8-puzzle-problem-using-a-star-search/>
