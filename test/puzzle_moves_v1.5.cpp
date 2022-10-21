#include <iostream>

int main()
{
    // move validation
    int index;

    // up
    std::cout << "Move::UP\n";
    for (index = 0; index <= 8; index++)
    {
        if (index > 2)
            std::cout << index << "-->" << (index - 3) << "\n";
    }

    // left
    std::cout << "\n\nMove::Left\n";
    for (index = 0; index <= 8; index++)
    {
        if (index % 3 != 0)
            std::cout << index << "-->" << (index - 1) << "\n";
    }

    // down
    std::cout << "\n\nMove::Down\n";
    for (index = 0; index <= 8; index++)
    {
        if (index < 6)
            std::cout << index << "-->" << (index + 3) << "\n";
    }

    // right
    std::cout << "\n\nMove::Right\n";
    for (index = 0; index <= 8; index++)
    {
        if ((index != 2) && (index != 5) && (index != 8))
            std::cout << index << "-->" << (index + 1) << "\n";
    }

    return 0;
}
