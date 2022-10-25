#include "Student.h"

Student::Student(string _name, char _grade)
{
    this->name = _name;
    this->grade = _grade;
}

string Student::getName() const
{
    return this->name;
}

char Student::getGrade() const
{
    return this->grade;
}

void Student::setName(string &_name)
{
    this->name = _name;
}

void Student::setGrade(char &_grade)
{
    this->grade = _grade;
}
