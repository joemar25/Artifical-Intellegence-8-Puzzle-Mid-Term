#include <iostream>
using namespace std;

int main()
{
    int row, col;
    cout << "How many rows are there?" << endl;
    cin >> row;
    cout << "How many columns are there?" << endl;
    cin >> col;
    cout << "Enter values for the matrix: " << endl;

    // check if row and col > 0
    int *val = new int[row * col];

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cin >> val[i * col + j];
        }
    }

    // print val
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cout << val[i * col + j];
        }
        cout << endl;
    }

    delete[] val;
    return 0;
}
