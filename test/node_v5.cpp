#include <iostream>

// global variables
#define __row_col_ 9

int _index;
std::string move_list;
const int goal[9] = {1, 2, 3, 8, 0, 4, 7, 6, 5};

class Puzzle
{
    int *state = new int[9];

    ~Puzzle()
    {
        state = NULL;
        delete state;
        state = NULL;
    };

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
};

class Node
{ // store state
    Puzzle *puzzle;
    // store move
    std::string move;
    // depth
    int depth;
    // heuristic cost
    int hcost;
    // deconstructor, para di na kumanta ng please release me -Engelbert Humperdinck
    ~Node(){};

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

    // test display
    void displayState()
    {
        std::cout << "+---+---+---+\n";
        for (int index = 0, i = 0; i < 3; i++)
        {
            std::cout << "|";
            for (int j = 1; j < 4; j++)
            {
                std::cout << " " << this->puzzle->getState()[index] << " |";
                index++;
            }
            std::cout << "\n+---+---+---+\n";
        }

        if (this->getMove() != "")
            std::cout << "Move: " << this->getMove() << "\n\n";
    }
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
    int state[9] = {1, 2, 3, 4, 0, 5, 6, 7, 8};
    Puzzle *puzzle = new Puzzle(state);
    Node *initial = new Node(puzzle);
    solution_path(initial);
    std::cout << "\n";
    return 0;
}