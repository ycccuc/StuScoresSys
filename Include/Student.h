#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <iostream>
#include "MyConst.h"

class Student
{
public:
    Student();
    Student(int id, const std::string &name, const double scores[SUBJECT_COUNT]);

    int getId() const;
    std::string getName() const;
    double getScore(int index) const;
    double getAverage() const;

    void setId(int id);
    void setName(const std::string &name);
    void setScores(const double scores[SUBJECT_COUNT]);
    void calcAverage();

    void printToFile(std::ostream &out) const;
    void readFromFile(std::istream &in);

private:
    int id_;
    std::string name_;
    double scores_[SUBJECT_COUNT];
    double average_;
};

#endif