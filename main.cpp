#include <iostream>
#include <string>
#include <ctime>

void configPrint(int puzzle[3][3], std::string difficulty)
{
    std::cout << difficulty << std::endl;
    for (int r = 0; r < 3; r++)
    {
        for (int c = 0; c < 3; c++)
            std::cout << puzzle[r][c] << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main()
{

    // default variables
    char input;

    // goal state
    int goal[3][3] = {
        {1, 2, 3},
        {8, 0, 4},
        {7, 6, 5}};

    // easy
    int easyP[3][3] = {
        {1, 3, 4},
        {5, 6, 2},
        {7, 0, 5}};

    // medium
    int mediumP[3][3] = {
        {1, 3, 4},
        {5, 6, 2},
        {7, 0, 5}};

    // hard
    int hardP[3][3] = {
        {1, 3, 4},
        {5, 6, 2},
        {7, 0, 5}};

    // worst
    int worstP[3][3] = {
        {1, 3, 4},
        {5, 6, 2},
        {7, 0, 5}};

    // default
    int defaultP[3][3] = {
        {1, 3, 4},
        {5, 6, 2},
        {7, 0, 5}};

    configPrint(easyP, "a. easy");
    configPrint(mediumP, "b. medium");
    configPrint(hardP, "c. hard");
    configPrint(worstP, "d. worst");
    configPrint(defaultP, "e. default");

    // promting
    std::cout << "choose a puzzle to solve...\n -select a letter and press enter: ";
    std::cin >> input;
    std::cout << std::endl;

    if (input == 'a')
    {
        std::cout << "hello " << input << std::endl;
    }
    if (input == 'b')
    {
        std::cout << "hello " << input << std::endl;
    }
    if (input == 'c')
    {
        std::cout << "hello " << input << std::endl;
    }
    if (input == 'd')
    {
        std::cout << "hello " << input << std::endl;
    }

    // std::cout << <<std::endl;

    return 0;
}