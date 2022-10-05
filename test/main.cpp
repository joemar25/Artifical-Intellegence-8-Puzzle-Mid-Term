/**
 *
 * @file main.cpp
 * @authors  - Balagtas, Arrlee
 *           - Cardiñom Joemar
 *           - Gomez, Olan
 * @brief
 * @version 0.1
 * @date 2022-10-05
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>
#include <string>
#include <ctime>

#define ROW_COL 3

bool validate(char input)
{
    if (input == 'a' || input == 'b' || input == 'c' || input == 'd')
        return true;
    return false;
}

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

    std::cout << validate(input) << std::endl;
    // std::cout << <<std::endl;

    return 0;
}

/*

         ********NOTES********

        f(n) = g(n) + h(n)

        g(n) is the cost (number of steps taken to current state)
        f(n) is the estimated distance to goal (estimated number of steps taken from current state to goal state)
             - manhattan distance

        a* lecture source : https://www.youtube.com/watch?v=GuCzYxHa7iA&ab_channel=JinyueHan


*/