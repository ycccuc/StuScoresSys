#pragma once
#include <vector>
#include <string>
#include <array>
#include <fstream>
#include "Student.h"
#include "MyConst.h"

class StudentManager
{
public:
    explicit StudentManager(const std::string &filename = DATA_FILE);

    // 增删改查
    ErrorCode add(const Student &s);
    ErrorCode remove(int id);
    ErrorCode modify(int id, const std::array<double, SUBJECT_COUNT> &scores);
    const Student *find(int id) const;
    const std::vector<Student> &getAll() const { return students_; }

    // 文件持久化
    ErrorCode load();
    ErrorCode save() const;

    // 统计（结果通过输出参数返回）
    struct StatResult
    {
        double avg[SUBJECT_COUNT];
        double max[SUBJECT_COUNT];
        double min[SUBJECT_COUNT];
        double totalAvg;
        const Student *topStudent;
        const Student *bottomStudent;
    };
    ErrorCode getStatistics(StatResult &out) const;

    // 排序：subjectIdx 0=语文,1=数学,2=英语,3=平均分
    void sortBy(int subjectIdx, bool ascending);

    bool empty() const { return students_.empty(); }
    size_t size() const { return students_.size(); }

private:
    std::vector<Student> students_;
    std::string filename_;

    static bool idValid(int id);
    static bool nameValid(const std::string &name);
    static bool scoreValid(double score);
};