#include <iostream>
#include <list>

int main()
{
    std::list<int> open, closed;

    // open.push_front(1); // head
    open.push_back(2); // others
    open.push_back(3); // ...
    open.push_back(4); // ...
    open.push_back(5); // ...

    // iterator, is just as a pointer, that points at an object in the list -> node = node->next
    // std::list<int>::iterator it = open.begin();
    std::list<int>::iterator it;
    for (it = open.begin(); it != open.end(); it++)
        std::cout << *it << "\n";

    return 0;
}

// -- source of learnings, https://www.youtube.com/watch?v=fdwoXjIg94k&ab_channel=AlleyB