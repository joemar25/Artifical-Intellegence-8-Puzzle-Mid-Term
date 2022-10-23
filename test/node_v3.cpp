#include <iostream>

// global variables
#define __row_col_ 9
int _index;

class Node
{
    // store state
    int *state = new int[9];
    // store move
    std::string move;
    // depth
    int depth;
    // heuristic cost
    int hcost;
    // deconstructor, para di na kumanta ng please release me -Engelbert Humperdinck
    ~Node()
    {
        state = NULL;
        delete state;
        state = NULL;
    };

public:
    // next node to expand
    Node *next;

    Node() {}

    // getters and  setters
    void setState(int _state[])
    {
        this->state = _state;
    }

    int *getState()
    {
        return this->state;
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

    // other functions
    void displayState()
    {
        std::cout << "+---+---+---+\n";
        for (int index = 0, i = 0; i < 3; i++)
        {
            std::cout << "|";
            for (int j = 1; j < 4; j++)
            {
                std::cout << " " << this->getState()[index] << " |";
                index++;
            }
            std::cout << "\n+---+---+---+\n";
        }
        std::cout << "Move: " << this->getMove() << "\n\n";
    }
};

class Puzzle
{
    int goal_state[9] = {1, 2, 3, 8, 0, 4, 7, 6, 5};
    ~Puzzle(){};

public:
    Puzzle(){};

    bool isGoal(int _current_state[])
    {
        for (_index = 0; _index < __row_col_; _index++)
        {
            if (_current_state[_index] != goal_state[_index])
                return false;
        }
        return true;
    }
};

class Solver
{

    void choices();
    void getInput();
    void displaySolutionPath()
    {
        /** print path
         *  std::cout << "solution path => Up-UP-Left-Down-Right\n";
         *  std::cout << "solution cost => 5\n";
         *  std::cout << "solution path => 27\n";
         *  std::cout << "running time  => 0.69\n";
         */
    }

    /**
     * @brief Note
     *
     * Although there maybe available codes on the internet for the 8-puzzle, make
     * sure that for the A* Search, your codes follow the pseudocode given in the
     * lecture. As much as possible, write your code from scratch given the
     * pseudocode described.
     */

    /**
     * The following implementation of A* does not
     * build an actual tree-like structure. It uses a
     * list called OPEN (fringe), which contains
     * nodes ready for expansion, and another list
     * called CLOSED which contains expanded
     * nodes.
     *
     * A* Algorithm - Module
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
};

void solution_path(Node *_node)
{
    while (_node != NULL)
    {
        _node->displayState();
        _node = _node->next;
    }
}

int main()
{
    Node *initial = new Node();
    int state[9] = {1, 2, 3, 4, 5, 6, 7, 8};

    initial->setState(state);
    initial->next = nullptr;

    // display solution path
    solution_path(initial);
    std::cout << "\n";
    return 0;
}