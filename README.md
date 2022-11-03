# ⭐️⭐️⭐️ **AI Mid Term Project** ⭐️⭐️⭐️

This project is about showcasing how the two algorithms (IDS and A*) solve the 8 puzzle problem.

<br>

---

<br>

![Logo](https://static.vecteezy.com/system/resources/previews/000/371/208/original/vector-welcome-hand-drawn-text.jpg)

## Members

- [Arrlee Balagtas](https://www.facebook.com/100004747590876/ "Arrlee Balagtas") ✌🏻
- [Joemar Cardiño](https://github.com/joemar25 "Joemar's Github") 👋🏻
- [Olan Gomez](https://github.com/AdrianJones23 "Olan Gomez") 🤙🏻

## Tables of Contents

1. [Actual Test Run](#test-run)
2. [What are the Problems we encountered?](#problems-encuntered)
3. [Functions](#functions)
4. [Solving Algorithms](#solving-algorithms)
5. [Analysis](#analysis)
6. [References Used](#references)

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

> Worst is solvable but will take a while - about (2 - 4) min to solve.

<br>

---

<br>

## Problems Encuntered

<br>

---

<br>

## Functions

```md
MAIN()
    Terminologies...
        - unsigned int var_name; -> only takes unsigned integer values (1, 2, 5, etc...) and not (-1, -3, 25, etc...)
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

```md
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

> note: this function will use printChoices() that will return a print statements for user to see while the program is in execution

<br>

```md
 Terminologies...
        - var_type &var_name -> means no variable will be created. we will just only pass a reference of the original variable that will be passed in this function. 

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

```md
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

```md
from Puzzle class we have a function that will display the current state of the puzzle

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

---

<br>

## Solving Algorithms

<br>

---

<br>

## Analysis

<br>

---

<br>

## References
