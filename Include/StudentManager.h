#ifndef STUDENT_MANAGER_H
#define STUDENT_MANAGER_H

#include <vector>
#include "MyConst.h"
#include "Student.h"

class StudentManager
{
public:
    StudentManager();

    ErrorCode addStudent(const Student &s);
    ErrorCode deleteStudent(int id);
    ErrorCode modifyStudent(int id, const double newScores[SUBJECT_COUNT]);
    int findStudent(int id) const;
    Student getStudent(int index) const;
    const std::vector<Student> &getAllStudents() const;

    ErrorCode loadFromFile();
    ErrorCode saveToFile() const;

    void calcStatistics(double avg[], double maxs[], double mins[],
                        double &totalAvg, int &topIdx, int &bottomIdx) const;

    void sortStudents(int sortBy, bool ascending);

    bool isEmpty() const;
    int getCount() const;

    static bool isIdValid(int id);
    static bool isNameValid(const std::string &name);
    static bool isScoreValid(double score);

private:
    std::vector<Student> students_;
};

#endif