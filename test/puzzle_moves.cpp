#include <iostream>

bool IS_VALID(int _area)
{
    return (_area >= 0 && _area <= 2);
}

bool IS_MOVE_VALID(int _row, int _col)
{
    return IS_VALID(_row) && IS_VALID(_col);
}

void SWAP(int *_x, int *_y)
{
    *_y = *_x;
    *_x = 0;
}

void MOVE_UP(int puzzle[3][3], int _row, int _col)
{
    int _area = _row - 1;
    if (IS_MOVE_VALID(_area, _col))
        SWAP(&puzzle[_area][_col], &puzzle[_row][_col]);
}

void MOVE_LEFT(int puzzle[3][3], int _row, int _col)
{
    int _area = _col - 1;
    if (IS_MOVE_VALID(_row, _area))
        SWAP(&puzzle[_row][_area], &puzzle[_row][_col]);
}

void MOVE_DOWN(int puzzle[3][3], int _row, int _col)
{
    int _area = _row + 1;
    if (IS_MOVE_VALID(_area, _col))
        SWAP(&puzzle[_area][_col], &puzzle[_row][_col]);
}

void MOVE_RIGHT(int puzzle[3][3], int _row, int _col)
{
    int _area = _col + 1;
    if (IS_MOVE_VALID(_row, _area))
        SWAP(&puzzle[_row][_area], &puzzle[_row][_col]);
}

void DISPLAY_STATE(int puzzle[3][3])
{
    for (unsigned int i = 0; i < 3; i++)
    {
        for (unsigned int j = 0; j < 3; j++)
            std::cout << puzzle[i][j] << " ";
        std::cout << std::endl;
    }
}

int GET_ROW(int puzzle[3][3])
{
    int row = 0;
    for (unsigned int i = 0; i < 3; i++)
    {
        for (unsigned int j = 0; j < 3; j++)
        {
            if (puzzle[i][j] == 0)
                row = i;
        }
    }
    return row;
}

int GET_COL(int puzzle[3][3])
{
    int col = 0;
    for (unsigned int i = 0; i < 3; i++)
    {
        for (unsigned int j = 0; j < 3; j++)
        {
            if (puzzle[i][j] == 0)
                col = j;
        }
    }
    return col;
}

int main()
{
    int row = 0, col = 0;
    int state[3][3] = {
        {1, 3, 0},
        {8, 2, 4},
        {6, 7, 5},
    };

    // print initial state
    std::cout << "initial state" << std::endl;
    for (unsigned int i = 0; i < 3; i++)
    {
        for (unsigned int j = 0; j < 3; j++)
        {
            std::cout << state[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // get row and column
    row = GET_ROW(state);
    col = GET_COL(state);

    // uncomment 1 at a time for testing
    // move up
    std::cout << "\nMove Up\n";
    MOVE_UP(state, row, col);
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