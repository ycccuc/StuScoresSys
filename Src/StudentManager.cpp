#include "StudentManager.h"
#include <algorithm>
#include <numeric>
#include <ctime>

namespace
{
    void logDebug(const std::string &func, ErrorCode code, const std::string &detail)
    {
        std::ofstream fp(DEBUG_FILE, std::ios::app);
        if (!fp)
            return;

        time_t now = time(nullptr);
        char timeStr[64];
        strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", localtime(&now));

        fp << "[" << timeStr << "] 函数: " << func << "\n";
        fp << "  错误码: " << static_cast<int>(code) << "\n";
        fp << "  详细信息: " << detail << "\n";
        fp << "----------------------------------------\n";
    }
}

StudentManager::StudentManager(const std::string &filename)
    : filename_(filename) {}

ErrorCode StudentManager::add(const Student &s)
{
    if (!idValid(s.getId()))
    {
        logDebug("add", ErrorCode::ERROR_ID_INVALID, "学号验证失败");
        return ErrorCode::ERROR_ID_INVALID;
    }
    if (!nameValid(s.getName()))
    {
        logDebug("add", ErrorCode::ERROR_NAME_INVALID, "姓名验证失败");
        return ErrorCode::ERROR_NAME_INVALID;
    }

    // STL: find_if
    auto it = std::find_if(students_.begin(), students_.end(),
                           [&s](const Student &stu)
                           { return stu.getId() == s.getId(); });
    if (it != students_.end())
    {
        logDebug("add", ErrorCode::ERROR_ID_EXISTS, "学号重复");
        return ErrorCode::ERROR_ID_EXISTS;
    }

    students_.push_back(s);
    return ErrorCode::SUCCESS;
}

ErrorCode StudentManager::remove(int id)
{
    auto it = std::find_if(students_.begin(), students_.end(),
                           [id](const Student &s)
                           { return s.getId() == id; });
    if (it == students_.end())
    {
        logDebug("remove", ErrorCode::ERROR_ID_NOT_FOUND, "学号不存在");
        return ErrorCode::ERROR_ID_NOT_FOUND;
    }

    students_.erase(it);
    return ErrorCode::SUCCESS;
}

ErrorCode StudentManager::modify(int id, const std::array<double, SUBJECT_COUNT> &scores)
{
    auto it = std::find_if(students_.begin(), students_.end(),
                           [id](const Student &s)
                           { return s.getId() == id; });
    if (it == students_.end())
    {
        logDebug("modify", ErrorCode::ERROR_ID_NOT_FOUND, "学号不存在");
        return ErrorCode::ERROR_ID_NOT_FOUND;
    }

    for (double sc : scores)
    {
        if (!scoreValid(sc))
        {
            logDebug("modify", ErrorCode::ERROR_SCORE_RANGE, "成绩验证失败");
            return ErrorCode::ERROR_SCORE_RANGE;
        }
    }

    it->setScores(scores);
    return ErrorCode::SUCCESS;
}

const Student *StudentManager::find(int id) const
{
    auto it = std::find_if(students_.begin(), students_.end(),
                           [id](const Student &s)
                           { return s.getId() == id; });
    if (it != students_.end())
        return &(*it);
    return nullptr;
}

ErrorCode StudentManager::load()
{
    std::ifstream fp(filename_);
    if (!fp)
        return ErrorCode::SUCCESS; // 文件不存在，空数据启动

    int count;
    fp >> count;
    if (fp.fail())
    {
        logDebug("load", ErrorCode::ERROR_FILE_READ, "读取数量失败");
        return ErrorCode::ERROR_FILE_READ;
    }

    students_.clear();
    for (int i = 0; i < count; ++i)
    {
        Student s;
        fp >> s;
        if (fp.fail())
        {
            students_.clear();
            logDebug("load", ErrorCode::ERROR_FILE_READ, "读取学生数据失败");
            return ErrorCode::ERROR_FILE_READ;
        }
        students_.push_back(s);
    }
    return ErrorCode::SUCCESS;
}

ErrorCode StudentManager::save() const
{
    std::ofstream fp(filename_);
    if (!fp)
    {
        logDebug("save", ErrorCode::ERROR_FILE_OPEN, filename_);
        return ErrorCode::ERROR_FILE_OPEN;
    }

    fp << students_.size() << "\n";
    for (const auto &s : students_)
    {
        fp << s << "\n";
    }
    return ErrorCode::SUCCESS;
}

ErrorCode StudentManager::getStatistics(StatResult &out) const
{
    if (students_.empty())
    {
        logDebug("getStatistics", ErrorCode::ERROR_EMPTY, "无学生记录");
        return ErrorCode::ERROR_EMPTY;
    }

    for (int i = 0; i < SUBJECT_COUNT; ++i)
    {
        // STL: accumulate
        double sum = std::accumulate(students_.begin(), students_.end(), 0.0,
                                     [i](double acc, const Student &s)
                                     { return acc + s.getScore(i); });
        out.avg[i] = sum / students_.size();

        // STL: minmax_element
        auto pr = std::minmax_element(students_.begin(), students_.end(),
                                      [i](const Student &a, const Student &b)
                                      {
                                          return a.getScore(i) < b.getScore(i);
                                      });
        out.min[i] = pr.first->getScore(i);
        out.max[i] = pr.second->getScore(i);
    }

    // 总体平均分的平均
    double totalSum = std::accumulate(students_.begin(), students_.end(), 0.0,
                                      [](double acc, const Student &s)
                                      { return acc + s.getAverage(); });
    out.totalAvg = totalSum / students_.size();

    // 最高/最低平均分的学生
    auto pr = std::minmax_element(students_.begin(), students_.end(),
                                  [](const Student &a, const Student &b)
                                  {
                                      return a.getAverage() < b.getAverage();
                                  });
    out.bottomStudent = &(*pr.first);
    out.topStudent = &(*pr.second);

    return ErrorCode::SUCCESS;
}

void StudentManager::sortBy(int subjectIdx, bool ascending)
{
    // Lambda 比较器
    auto cmp = [subjectIdx](const Student &a, const Student &b)
    {
        if (subjectIdx == SORT_BY_AVERAGE - 1)
        {
            return a.getAverage() < b.getAverage();
        }
        return a.getScore(subjectIdx) < b.getScore(subjectIdx);
    };

    // STL: sort
    if (ascending)
    {
        std::sort(students_.begin(), students_.end(), cmp);
    }
    else
    {
        std::sort(students_.begin(), students_.end(),
                  [&cmp](const Student &a, const Student &b)
                  { return cmp(b, a); });
    }
}

bool StudentManager::idValid(int id)
{
    return id >= MIN_ID && id <= MAX_ID;
}
bool StudentManager::nameValid(const std::string &name)
{
    return !name.empty() && name.length() < MAX_NAME_LEN;
}
bool StudentManager::scoreValid(double score)
{
    return score >= MIN_SCORE && score <= MAX_SCORE;
}