#include "Student.h"
#include <numeric>
#include <iomanip>

Student::Student(int id, const std::string &name,
                 const std::array<double, SUBJECT_COUNT> &scores)
    : id_(id), name_(name), scores_(scores)
{
    calcAverage();
}

void Student::calcAverage()
{
    double sum = std::accumulate(scores_.begin(), scores_.end(), 0.0);
    average_ = sum / SUBJECT_COUNT;
}

void Student::setScores(const std::array<double, SUBJECT_COUNT> &scores)
{
    scores_ = scores;
    calcAverage();
}

std::ostream &operator<<(std::ostream &os, const Student &s)
{
    os << s.id_ << ' ' << s.name_;
    for (double sc : s.scores_)
    {
        os << ' ' << std::fixed << std::setprecision(2) << sc;
    }
    os << ' ' << std::fixed << std::setprecision(2) << s.average_;
    return os;
}

std::istream &operator>>(std::istream &is, Student &s)
{
    is >> s.id_ >> s.name_;
    for (int i = 0; i < SUBJECT_COUNT; ++i)
    {
        is >> s.scores_[i];
    }
    is >> s.average_;
    return is;
}