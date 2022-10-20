#include <iostream>

// using namespace std;

class Node //
{
public:
    int value;
    Node *next;
};

void print(Node *_node)
{
    while (_node != NULL)
    {
        std::cout << _node->value << " ";
        _node = _node->next;
    }
    std::cout << "\n";
}

int main()
{
    // standard naming convention of the first/head element is 'head' in a linked list
    // this declaration is just allocating memory for the first node
    // this will be the space where we put our first element of the link list
    Node *head = new Node();

    // extra nodes for testing
    Node *up = new Node();
    Node *left = new Node();
    Node *down = new Node();
    Node *right = new Node();

    head->value = 5;
    head->next = up;

    up->value = 1;
    up->next = left;

    left->value = 2;
    left->next = nullptr;

    print(head);

    return 0;
}
