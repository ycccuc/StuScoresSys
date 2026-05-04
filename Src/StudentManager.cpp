#include "StudentManager.h"
#include <fstream>
#include <algorithm>

StudentManager::StudentManager()
{
}

ErrorCode StudentManager::addStudent(const Student &s)
{
    if (!isIdValid(s.getId()))
    {
        return ERROR_ID_INVALID;
    }
    if (!isNameValid(s.getName()))
    {
        return ERROR_NAME_INVALID;
    }

    if (findStudent(s.getId()) != -1)
    {
        return ERROR_ID_EXISTS;
    }

    students_.push_back(s);
    return SUCCESS;
}

ErrorCode StudentManager::deleteStudent(int id)
{
    int index = findStudent(id);
    if (index == -1)
    {
        return ERROR_ID_NOT_FOUND;
    }

    students_.erase(students_.begin() + index);
    return SUCCESS;
}

ErrorCode StudentManager::modifyStudent(int id, const double newScores[SUBJECT_COUNT])
{
    int index = findStudent(id);
    if (index == -1)
    {
        return ERROR_ID_NOT_FOUND;
    }

    for (int i = 0; i < SUBJECT_COUNT; i++)
    {
        if (!isScoreValid(newScores[i]))
        {
            return ERROR_SCORE_RANGE;
        }
    }

    students_[index].setScores(newScores);
    return SUCCESS;
}

int StudentManager::findStudent(int id) const
{
    auto it = std::find_if(students_.begin(), students_.end(),
        [id](const Student &s) { return s.getId() == id; });
    if (it == students_.end())
    {
        return -1;
    }
    return static_cast<int>(std::distance(students_.begin(), it));
}

Student StudentManager::getStudent(int index) const
{
    return students_[index];
}

const std::vector<Student> &StudentManager::getAllStudents() const
{
    return students_;
}

ErrorCode StudentManager::loadFromFile()
{
    std::ifstream in(DATA_FILE.c_str());
    if (!in.is_open())
    {
        return SUCCESS;
    }

    int count;
    in >> count;
    if (in.fail())
    {
        return ERROR_FILE_READ;
    }

    students_.clear();
    for (int i = 0; i < count; i++)
    {
        Student s;
        s.readFromFile(in);
        if (in.fail())
        {
            students_.clear();
            return ERROR_FILE_READ;
        }
        students_.push_back(s);
    }

    in.close();
    return SUCCESS;
}

ErrorCode StudentManager::saveToFile() const
{
    std::ofstream out(DATA_FILE.c_str());
    if (!out.is_open())
    {
        return ERROR_FILE_OPEN;
    }

    out << students_.size() << "\n";
    for (size_t i = 0; i < students_.size(); i++)
    {
        students_[i].printToFile(out);
        out << "\n";
    }

    out.close();
    return SUCCESS;
}

void StudentManager::calcStatistics(double avg[], double maxs[], double mins[],
                                    double &totalAvg, int &topIdx, int &bottomIdx) const
{
    int n = static_cast<int>(students_.size());

    for (int i = 0; i < SUBJECT_COUNT; i++)
    {
        double sum = 0.0;
        maxs[i] = MIN_SCORE;
        mins[i] = MAX_SCORE;

        for (int j = 0; j < n; j++)
        {
            double sc = students_[j].getScore(i);
            sum += sc;
            if (sc > maxs[i])
            {
                maxs[i] = sc;
            }
            if (sc < mins[i])
            {
                mins[i] = sc;
            }
        }
        avg[i] = sum / n;
    }

    totalAvg = 0.0;
    double maxAvg = -1.0;
    double minAvg = 999.0;
    topIdx = 0;
    bottomIdx = 0;

    for (int i = 0; i < n; i++)
    {
        double a = students_[i].getAverage();
        totalAvg += a;

        if (a > maxAvg)
        {
            maxAvg = a;
            topIdx = i;
        }
        if (a < minAvg)
        {
            minAvg = a;
            bottomIdx = i;
        }
    }
    totalAvg /= n;
}

void StudentManager::sortStudents(int sortBy, bool ascending)
{
    std::sort(students_.begin(), students_.end(),
        [sortBy, ascending](const Student &a, const Student &b) {
            double va, vb;
            if (sortBy == SORT_BY_AVERAGE)
            {
                va = a.getAverage();
                vb = b.getAverage();
            }
            else
            {
                int idx = sortBy - 1; // SORT_BY_CHINESE=1 → 语文下标=0
                va = a.getScore(idx);
                vb = b.getScore(idx);
            }
            return ascending ? (va < vb) : (va > vb);
        });
}

bool StudentManager::isEmpty() const
{
    return students_.empty();
}

int StudentManager::getCount() const
{
    return static_cast<int>(students_.size());
}

bool StudentManager::isIdValid(int id)
{
    return id >= MIN_ID && id <= MAX_ID;
}

bool StudentManager::isNameValid(const std::string &name)
{
    if (name.empty() || name.length() >= static_cast<size_t>(MAX_NAME_LEN))
    {
        return false;
    }
    // 拒绝纯空白（空格/制表符组成的"假"名字）
    if (name.find_first_not_of(" \t") == std::string::npos)
    {
        return false;
    }
    return true;
}

bool StudentManager::isScoreValid(double score)
{
    return score >= MIN_SCORE && score <= MAX_SCORE;
}