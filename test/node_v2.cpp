#include <iostream>

class Node
{
public:
    int *state;
    Node *next;
    std::string move;
};

void solution_path(Node *_node)
{
    while (_node != NULL)
    {
        // printing nodes
        std::cout << "+---+---+---+\n";
        for (int index = 0, i = 0; i < 3; i++)
        {
            std::cout << "|";
            for (int j = 1; j < 4; j++)
            {
                std::cout << " " << _node->state[index] << " |";
                index++;
            }
            std::cout << "\n+---+---+---+\n";
        }
        std::cout << "Move: " << _node->move << "\n\n";
        // note: always set node pointing to the next node
        _node = _node->next;
    }
}

int main()
{
    Node *head = new Node();
    int state[9] = {1, 2, 3, 4, 5, 6, 7, 8};

    // initialize node
    head->state = state;
    head->next = nullptr;
    head->move = "initial";

    solution_path(head);

    return 0;
}