#include <iostream>

class Puzzle
{
    // default
    int array[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};

public:
    Puzzle(int _array[])
    {
        this->setPuzzle(_array);
    };
    ~Puzzle(){};

    void setPuzzle(const int _array[])
    {
        for (int i = 0; i < 9; i++)
            this->array[i] = _array[i];
    }

    void displayPuzzle()
    {
        for (int i = 0; i < 9; i++)
            std::cout << array[i] << " ";
        std::cout << "\n";
    }
};

int main()
{
    int array[9] = {1, 2, 3, 8, 0, 4, 7, 6, 5};
    Puzzle puzz(array);
    puzz.displayPuzzle();

    return 0;
}