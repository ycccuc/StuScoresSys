#pragma once
#include <string>
#include <array>
#include <iostream>
#include "MyConst.h"

class Student
{
public:
    Student() = default;
    Student(int id, const std::string &name,
            const std::array<double, SUBJECT_COUNT> &scores);

    // Getters
    int getId() const { return id_; }
    const std::string &getName() const { return name_; }
    double getScore(int idx) const { return scores_[idx]; }
    const std::array<double, SUBJECT_COUNT> &getScores() const { return scores_; }
    double getAverage() const { return average_; }

    // Setters
    void setId(int id) { id_ = id; }
    void setName(const std::string &name) { name_ = name; }
    void setScores(const std::array<double, SUBJECT_COUNT> &scores);

    // 重新计算平均分
    void calcAverage();

    // 文件序列化（格式与原来完全一致，兼容旧数据）
    friend std::ostream &operator<<(std::ostream &os, const Student &s);
    friend std::istream &operator>>(std::istream &is, Student &s);

private:
    int id_ = 0;
    std::string name_;
    std::array<double, SUBJECT_COUNT> scores_{};
    double average_ = 0.0;
};