#include <iostream>
#include <vector>
#include <list>

using std::cout;
using std::list;

#define __row_col_ 9

/**
 * @brief PUT const in get functions
 *
 */

int _index;
std::string move_list;
const int goal[9] = {1, 2, 3, 8, 0, 4, 7, 6, 5};

class Puzzle
{
    // default
    int state[9] = {1, 2, 3, 8, 0, 4, 7, 6, 5};

    int getBlank()
    {
        for (int i = 0; i < __row_col_; i++)
        {
            if (state[i] == 0)
                return i;
        }
        return 0;
    }

    void setState(int _state[])
    {
        for (int i = 0; i < 9; i++)
            this->state[i] = _state[i];
    }

    // check available moves
    bool canMoveUp()
    {
        return this->getBlank() > 2;
    }

    bool canMoveLeft()
    {
        return this->getBlank() % 3 != 0;
    }

    bool canMoveDown()
    {
        return this->getBlank() < 6;
    }

    bool canMoveRight()
    {
        return this->getBlank() != 2 && this->getBlank() != 5 && this->getBlank() != 8;
    }

    int *misplacement(int row, int col)
    {
        static int location[2];
        int state[3][3];
        int _goal[3][3];

        for (int index = 0, i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                state[i][j] = this->getState()[index];
                index++;
            }
        }

        for (int index = 0, i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                _goal[i][j] = goal[index];
                index++;
            }
        }

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (_goal[i][j] == state[row][col])
                {
                    location[0] = i;
                    location[1] = j;
                }
            }
        }
        return location;
    }

public:
    Puzzle(int _state[])
    {
        this->setState(_state);
    }

    // getters and setters

    int *getState()
    {
        return this->state;
    }

    int getStateIndex(int &index)
    {
        return this->state[index];
    }

    // manhattan distance
    int getManhattanDistance()
    {
        int total = 0, index = 0;
        int x = 0, y = 0;
        int *loc = new int;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (state[index] != 0)
                {
                    loc = misplacement(i, j);
                    x = (i > loc[0]) ? i - loc[0] : loc[0] - i;
                    y = (j > loc[1]) ? j - loc[1] : loc[1] - j;
                    total += x + y;
                }
                index++;
            }
        }

        // free memory
        loc = NULL;
        delete loc;
        loc = NULL;

        return total;
    }

    // test display
    void displayState()
    {
        for (int i = 0; i < 9; i++)
            cout << this->getStateIndex(i) << " ";
        cout << "\n";
    }

    ~Puzzle(){};
};

class Node
{
    Puzzle *puzzle;
    std::string move;
    int depth;
    int hcost;

public:
    Node *next;

    Node(Puzzle *_puzzle)
    {
        this->puzzle = _puzzle;
        next = nullptr;
    }

    void setMove(const std::string &_move)
    {
        this->move = _move;
    }

    std::string getMove() const
    {
        return this->move;
    }

    void setDepth(const int &_depth)
    {
        this->depth = _depth;
    }

    int getDepth() const
    {
        return this->depth;
    }

    std::vector<Puzzle *> open, closed;
    int f = 0;
    // test A*
    // void AAStar()
    // {
    //     open.push_back(this->puzzle);
    //     // open[0]->displayState();
    //     f = open.front()->getManhattanDistance();

    //     if (open.size() != 0)
    //     {
    //         int i = 0;

    //         for (auto i = open.begin(); i != open.end(); ++i)
    //         {
    //             // if (*i.operator++ % 2 == 0)
    //             // {
    //             //     open.erase(i);
    //             //     i--;
    //             // }
    //         }

    //         while (!open.empty())
    //         {
    //             closed.push_back(open.at(i));
    //             i++;
    //             // open.erase();
    //         }
    //     }
    //     else
    //         cout << "error occured\n";

    //     /**
    //      * 1. Put the start node s on a list called OPEN and compute f(s).
    //      * 2. If OPEN is empty, exit with failure; otherwise continue.
    //      * 3. Remove from OPEN that node whose f value is smallest and put it on a list called
    //      *    CLOSED. Call this node n. (Resolve ties for minimal f values arbitrarily, but always
    //      *    in favor of any goal node.)
    //      * 4. If n is a goal node, exit with the solution path obtained by tracing back the pointers;
    //      *    otherwise continue.
    //      * 5. Expand node n, generating all its successors. If there are no successors, go
    //      *    immediately to 2. For each successsor ni, compute f(ni).
    //      * 6. Associate with the successors not already on either OPEN or CLOSED the f values
    //      *    just computed. Put these nodes on OPEN and direct pointers from them back to n.
    //      * 7. Associate with those successors that were already on OPEN or CLOSED the smaller
    //      *    of the f values just computed and their previous f values. Put on OPEN those
    //      *    successors on CLOSED whose f values were thus lowered, and redirect to n the
    //      *    pointers from all nodes whose f values were lowered.
    //      * 8. Go to 2.
    //      */
    // }

    void AStar(Puzzle *initialState)
    {
        std::List openList;
        std::List closedList;
        openList.insertToFront(initialState);
        int counter = 0;
        while (openList.lst != NULL)
        {
            // get the best state which has the lowest heuristic value f(x) + g(x)
            eightPuzzle *bestState = openList.chooseBestState();
            closedList.insertToFront(bestState); // moves to closed list

            if (isGoal(bestState))
            {
                cout << "Solution Path: ";
                int cost = printStates(bestState);
                cout << endl;
                cout << "No. of Nodes Expanded: " << counter << endl;
                cout << "Solution Cost: " << cost - 1 << endl;
                return;
            }
            counter++;
            if (movable(bestState, "UP"))
            {
                eightPuzzle *tmp = move(bestState, "UP");
                if (closedList.notInList(tmp))
                {
                    openList.insertToFront(tmp);
                }
            }
            if (movable(bestState, "RIGHT"))
            {
                eightPuzzle *tmp = move(bestState, "RIGHT");
                if (closedList.notInList(tmp))
                {
                    openList.insertToFront(tmp);
                }
            }
            if (movable(bestState, "DOWN"))
            {
                eightPuzzle *tmp = move(bestState, "DOWN");
                if (closedList.notInList(tmp))
                {
                    openList.insertToFront(tmp);
                }
            }
            if (movable(bestState, "LEFT"))
            {
                eightPuzzle *tmp = move(bestState, "LEFT");
                if (closedList.notInList(tmp))
                {
                    openList.insertToFront(tmp);
                }
            }
        }
    }

    ~Node(){};
};

int main()
{
    int state[9] = {1, 2, 3, 4, 0, 5, 6, 7, 8};
    Puzzle puzzle(state);
    Node *node = new Node(&puzzle);
    node->AStar();
    // puzzle.displayState();
    // solution_path(initial);
    cout << "\n";
    return 0;
}