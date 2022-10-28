#include <iostream>
#include <time.h>

using std::cin;
using std::cout;

void inputChoice(int &choice)
{
    cout << "enter choice := ";
    cin >> choice;
}

int main()
{
    int choice = 0;
    inputChoice(choice);
    cout << "choice is " << choice << "\n";
    return 0;
}
