#include <iostream>
#include <list>

// global variables
#define __row_col_ 9

int _index;
std::string move_list;
const int goal[9] = {1, 2, 3, 8, 0, 4, 7, 6, 5};

class Puzzle
{
    int *state = new int[9];

    int getBlank()
    {
        for (int i = 0; i < __row_col_; i++)
        {
            if (state[i] == 0)
                return i;
        }
        return 0;
    }

public:
    Puzzle(int _state[])
    {
        this->state = _state;
    }

    // getters and setters
    void setState(int _state[])
    {
        this->state = _state;
    }

    int *getState()
    {
        return this->state;
    }

    int getStateIndex(int &index)
    {
        return this->state[index];
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

    // manhattan distance
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
            std::cout << this->getStateIndex(i) << " ";
        std::cout << "\n";
    }

    ~Puzzle()
    {
        state = NULL;
        delete state;
        state = NULL;
    };
};

class Node
{
    // store state
    Puzzle *puzzle;
    // store move
    std::string move;
    // depth
    int depth;
    // heuristic cost
    int hcost;
    // deconstructor, para di na kumanta ng please release me -Engelbert Humperdinck

public:
    // pointer next node to expand
    Node *next;

    Node(Puzzle *_puzzle)
    {
        this->puzzle = _puzzle;

        // --------------joemar temp
        next = nullptr;
    }

    void setMove(const std::string &_move)
    {
        this->move = _move;
    }

    std::string getMove()
    {
        return this->move;
    }

    void setDepth(const int &_depth)
    {
        this->depth = _depth;
    }

    int getDepth()
    {
        return this->depth;
    }

    std::list<Puzzle> open, closed;
    int f = 0;
    // test A*
    void AStar()
    {
        // add s to open list
        open.push_front(*this->puzzle);
        // get f(puzzle)
        f = open.begin()->getManhattanDistance();
        // If open is not empty - continue, else display error
        for (std::list<Puzzle>::iterator i = open.begin(); i != open.end(); i++)
        {
            i->displayState();
            // closed.push_back(i->getState());
            // open.erase();
        }
    }

    /**
     * 1. Put the start node s on a list called OPEN and compute f(s).
     * 2. If OPEN is empty, exit with failure; otherwise continue.
     * 3. Remove from OPEN that node whose f value is smallest and put it on a list called
     *    CLOSED. Call this node n. (Resolve ties for minimal f values arbitrarily, but always
     *    in favor of any goal node.)
     * 4. If n is a goal node, exit with the solution path obtained by tracing back the pointers;
     *    otherwise continue.
     * 5. Expand node n, generating all its successors. If there are no successors, go
     *    immediately to 2. For each successsor ni, compute f(ni).
     * 6. Associate with the successors not already on either OPEN or CLOSED the f values
     *    just computed. Put these nodes on OPEN and direct pointers from them back to n.
     * 7. Associate with those successors that were already on OPEN or CLOSED the smaller
     *    of the f values just computed and their previous f values. Put on OPEN those
     *    successors on CLOSED whose f values were thus lowered, and redirect to n the
     *    pointers from all nodes whose f values were lowered.
     * 8. Go to 2.
     */

    /**
     * @param A* - good source
     * The goal node is denoted by node_goal and the source node is denoted by node_start
     * We maintain two lists: OPEN and CLOSE:
     * OPEN consists on nodes that have been visited but not expanded (meaning that sucessors have not been
     * explored yet). This is the list of pending tasks.
     * CLOSE consists on nodes that have been visited and expanded (sucessors have been explored already and
     * included in the open list, if this was the case).
     * 1 Put node_start in the OPEN list with f(node_start) = h(node_start) (initialization)
     * 2 while the OPEN list is not empty {
     * 3 Take from the open list the node node_current with the lowest
     * 4 f(node_current) = g(node_current) + h(node_current)
     * 5 if node_current is node_goal we have found the solution; break
     * 6 Generate each state node_successor that come after node_current
     * 7 for each node_successor of node_current {
     * 8 Set successor_current_cost = g(node_current) + w(node_current, node_successor)
     * 9 if node_successor is in the OPEN list {
     * 10 if g(node_successor) ≤ successor_current_cost continue (to line 20)
     * 11 } else if node_successor is in the CLOSED list {
     * 12 if g(node_successor) ≤ successor_current_cost continue (to line 20)
     * 13 Move node_successor from the CLOSED list to the OPEN list
     * 14 } else {
     * 15 Add node_successor to the OPEN list
     * 16 Set h(node_successor) to be the heuristic distance to node_goal
     * 17 }
     * 18 Set g(node_successor) = successor_current_cost
     * 19 Set the parent of node_successor to node_current
     * 20 }
     * 21 Add node_current to the CLOSED list
     * 22 }
     * 23 if(node_current != node_goal) exit with error (the OPEN list is empty)
     */

    ~Node(){};
};

// void solution_path(Node *_node)
// {
//     while (_node != NULL)
//     {
//         _node->displayState();
//         _node = _node->next;
//     }
// }

int main()
{
    int state[9] = {1, 2, 3, 4, 0, 5, 6, 7, 8};
    Puzzle *puzzle = new Puzzle(state);
    Node *initial = new Node(puzzle);
    initial->AStar();
    // solution_path(initial);
    std::cout << "\n";
    return 0;
}