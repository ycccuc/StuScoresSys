#include "Student.h"
#include <iomanip>

Student::Student()
{
    id_ = 0;
    name_ = "";
    for (int i = 0; i < SUBJECT_COUNT; i++)
    {
        scores_[i] = 0.0;
    }
    average_ = 0.0;
}

Student::Student(int id, const std::string &name, const double scores[SUBJECT_COUNT])
{
    id_ = id;
    name_ = name;
    for (int i = 0; i < SUBJECT_COUNT; i++)
    {
        scores_[i] = scores[i];
    }
    calcAverage();
}

int Student::getId() const
{
    return id_;
}

std::string Student::getName() const
{
    return name_;
}

double Student::getScore(int index) const
{
    return scores_[index];
}

double Student::getAverage() const
{
    return average_;
}

void Student::setId(int id)
{
    id_ = id;
}

void Student::setName(const std::string &name)
{
    name_ = name;
}

void Student::setScores(const double scores[SUBJECT_COUNT])
{
    for (int i = 0; i < SUBJECT_COUNT; i++)
    {
        scores_[i] = scores[i];
    }
    calcAverage();
}

void Student::calcAverage()
{
    double sum = 0.0;
    for (int i = 0; i < SUBJECT_COUNT; i++)
    {
        sum += scores_[i];
    }
    average_ = sum / SUBJECT_COUNT;
}

void Student::printToFile(std::ostream &out) const
{
    out << id_ << " " << name_;
    for (int i = 0; i < SUBJECT_COUNT; i++)
    {
        out << " " << std::fixed << std::setprecision(2) << scores_[i];
    }
    out << " " << std::fixed << std::setprecision(2) << average_;
}

void Student::readFromFile(std::istream &in)
{
    in >> id_ >> name_;
    for (int i = 0; i < SUBJECT_COUNT; i++)
    {
        in >> scores_[i];
    }
    in >> average_;
}