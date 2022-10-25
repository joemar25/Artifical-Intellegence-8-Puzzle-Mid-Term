#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
using namespace std;

class Student
{
    // member variables
    string name;
    char grade;

public:
    //  default constructor
    Student() {}
    //  overload constructor
    Student(string, char);
    //  deconstructor
    ~Student() {}

    /**
     * @brief getName function - getters/accessor functions
     * @param none
     * @return string - name of student
     */
    string getName() const;

    /**
     * @brief getGrade function
     * @param none
     * @return char - grade of student
     */
    char getGrade() const;

    /**
     * @brief setName function - setters/mutator functions
     * @param string - name of student
     * @return none
     */
    void setName(string &);

    /**
     * @brief setGrade function
     * @param grade - of student
     * @return none
     */
    void setGrade(char &);
};

#endif