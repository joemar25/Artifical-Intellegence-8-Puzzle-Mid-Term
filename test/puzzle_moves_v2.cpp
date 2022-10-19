#include <iostream>

bool IS_VALID(int _pos)
{
    return (_pos >= 0 && _pos <= 8);
}

void SWAP(int *_x, int *_y)
{
    *_y = *_x;
    *_x = 0;
}

int GET_BLANK(int _puzzle[])
{
    for (int i = 0; i < 9; i++)
    {
        if (_puzzle[i] == 0)
            return i;
    }
    return 0;
}

void MOVE_UP(int _puzzle[])
{
    int _index = GET_BLANK(_puzzle);
    if (_index > 2)
        SWAP(&_puzzle[_index - 3], &_puzzle[_index]);
    // _puzzle[_index] = _puzzle[_index - 3];
    // _puzzle[_index - 3] = 0;
}

void MOVE_LEFT(int _puzzle[])
{
    int _index = GET_BLANK(_puzzle);
    if (_index % 3)
        SWAP(&_puzzle[_index - 1], &_puzzle[_index]);
}

void MOVE_DOWN(int _puzzle[])
{
    int _index = GET_BLANK(_puzzle);
    if (_index < 6)
        SWAP(&_puzzle[_index + 3], &_puzzle[_index]);
}

void MOVE_RIGHT(int _puzzle[])
{
    int _index = GET_BLANK(_puzzle);
    if (_index < 6)
        SWAP(&_puzzle[_index + 3], &_puzzle[_index]);
}

void DISPLAY_STATE(int _puzzle[3])
{
    for (unsigned int i = 0; i < 9; i++)
        std::cout << ((i % 3 == 0) ? "\n" : " ") << _puzzle[i];
    std::cout << "\n";
}

int main()
{
    int state[9] = {1, 2, 3, 8, 0, 4, 6, 7, 5};

    // print initial state
    std::cout << "initial state" << std::endl;
    DISPLAY_STATE(state);

    // uncomment 1 at a time for testing
    // move up
    std::cout << "\nMove Up\n";
    MOVE_DOWN(state);
    DISPLAY_STATE(state);

    // std::cout << "\nMove Left\n";
    // MOVE_LEFT(state, row, col);
    // DISPLAY_STATE(state);

    // std::cout << "\nMove Down\n";
    // MOVE_DOWN(state, row, col);
    // DISPLAY_STATE(state);

    // std::cout << "\nMove Right\n";
    // MOVE_RIGHT(state, row, col);
    // DISPLAY_STATE(state);

    std::cout << "\n";
    std::system("PAUSE");
    return 0;
}