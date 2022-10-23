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

private:
    Node *_node = new Node();

    void choices();
    void getInput();

    // functions
    ~Solver() {}

    void solution_path()
    {
        while (_node != NULL)
        {
            _node->displayState();
            _node = _node->next;
        }
    }

public:
    Solver(int _state[])
    {
        _node->setState(_state);
        _node->next = nullptr;
    }

    void displaySolutionPath()
    {
        solution_path();

        // total...
    }
};

int main()
{
    int state[9] = {1, 2, 3, 4, 5, 6, 7, 8};

    Solver *solve = new Solver(state);
    solve->displaySolutionPath();

    std::cout << "\n";
    return 0;
}