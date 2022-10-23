#include <iostream>
#include <list>

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
            std::cout << this->getStateIndex(i) << " ";
        std::cout << "\n";
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

    std::list<Puzzle *> open, closed;
    int f = 0;
    // test A*
    void AStar()
    {
        open.push_front(this->puzzle);
        f = open.front()->getManhattanDistance();
        for (std::list<Puzzle *>::iterator i = open.begin(); i != open.end(); i++)
        {
            *(i)->getManhattanDistance();
            // closed.push_back(i->getState());
        }
    }

    ~Node(){};
};

int main()
{
    int state[9] = {1, 2, 3, 4, 0, 5, 6, 7, 8};
    Puzzle puzzle(state);
    Node *node = new Node(&puzzle);

    // puzzle.displayState();
    // solution_path(initial);
    std::cout << "\n";
    return 0;
}