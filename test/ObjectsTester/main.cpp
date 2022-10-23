/**
 * @file main.cpp
 * @author Cardño, Joemar
 * @brief
 * @version 0.1
 * @date 2022-10-23
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>
#include <string>
#include <vector>
#include "Student.h"

using namespace std;

/**
 * @brief fill student(s) information
 * @param vector<Student> &list
 * @return none, fillable
 */
void fillStudents(vector<Student> &);

/**
 * @brief display student(s) information
 * @param vector<Student> &list
 * @return none, printing
 */
void displayStudents(const vector<Student> &);

int main()
{
    vector<Student> studentList;
    fillStudents(studentList);
    displayStudents(studentList);

    return 0;
}

void fillStudents(vector<Student> &list)
{
    unsigned i, size = 0;
    char grade;
    string name;

    cout << "number of student's in class? ";
    cin >> size;

    for (i = 0; i < size; i++)
    {
        cout << "\nenter student name := ";
        cin >> name;
        cout << "enter grade := ";
        cin >> grade;

        Student student(name, grade);
        list.push_back(student);
    }
}

void displayStudents(const vector<Student> &list)
{
    for (unsigned i = 0; i < list.size(); i++)
    {
        cout << "Student Name  : " << list[i].getName() << "\n";
        cout << "Student Grade : " << list[i].getGrade() << "\n\n";
    }
}