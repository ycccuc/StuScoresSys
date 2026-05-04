#pragma once
#include <string>
#include <iostream>
#include <iomanip>

/*-----------------------------------错误码定义----------------------------------------*/

enum class ErrorCode
{
    SUCCESS = 0,
    ERROR_MEMORY = -1,
    ERROR_FILE_OPEN = -2,
    ERROR_FILE_READ = -3,
    ERROR_FILE_WRITE = -4,
    ERROR_EMPTY = -10,
    ERROR_NOT_FOUND = -11,
    ERROR_DUPLICATE = -12,
    ERROR_ID_INVALID = -20,
    ERROR_ID_EXISTS = -21,
    ERROR_ID_NOT_FOUND = -22,
    ERROR_NAME_INVALID = -23,
    ERROR_NAME_LONG = -24,
    ERROR_SCORE_RANGE = -25,
    ERROR_INPUT_INVALID = -30
};

/*-----------------------------------常量定义-------------------------------------------*/

constexpr int MAX_NAME_LEN = 50;
constexpr int SUBJECT_COUNT = 3;
constexpr int MIN_ID = 1;
constexpr int MAX_ID = 99999999;
constexpr double MIN_SCORE = 0.0;
constexpr double MAX_SCORE = 150.0;

constexpr int SORT_BY_CHINESE = 1;
constexpr int SORT_BY_MATH = 2;
constexpr int SORT_BY_ENGLISH = 3;
constexpr int SORT_BY_AVERAGE = 4;
constexpr int SORT_ORDER_ASC = 1;
constexpr int SORT_ORDER_DESC = 2;

const std::string DATA_FILE = "students.txt";
const std::string DEBUG_FILE = "debug.txt";

const std::string SUBJECT_NAMES[SUBJECT_COUNT] = {"语文", "数学", "英语"};

/*-----------------------------------错误处理工具--------------------------------------*/

inline std::string getErrorMsg(ErrorCode code)
{
    switch (code)
    {
    case ErrorCode::SUCCESS:
        return "操作成功";
    case ErrorCode::ERROR_MEMORY:
        return "内存分配失败";
    case ErrorCode::ERROR_FILE_OPEN:
        return "文件打开失败";
    case ErrorCode::ERROR_FILE_READ:
        return "文件读取失败";
    case ErrorCode::ERROR_FILE_WRITE:
        return "文件写入失败";
    case ErrorCode::ERROR_EMPTY:
        return "数据为空";
    case ErrorCode::ERROR_NOT_FOUND:
        return "数据未找到";
    case ErrorCode::ERROR_DUPLICATE:
        return "数据重复";
    case ErrorCode::ERROR_ID_INVALID:
        return "学号无效(应为" + std::to_string(MIN_ID) + "-" + std::to_string(MAX_ID) + ")";
    case ErrorCode::ERROR_ID_EXISTS:
        return "学号已存在";
    case ErrorCode::ERROR_ID_NOT_FOUND:
        return "学号不存在";
    case ErrorCode::ERROR_NAME_INVALID:
        return "姓名无效(不能为空)";
    case ErrorCode::ERROR_NAME_LONG:
        return "姓名过长(最多" + std::to_string(MAX_NAME_LEN) + "字符)";
    case ErrorCode::ERROR_SCORE_RANGE:
        return "成绩超出范围(应为" + std::to_string(int(MIN_SCORE)) + "-" + std::to_string(int(MAX_SCORE)) + ")";
    case ErrorCode::ERROR_INPUT_INVALID:
        return "输入无效";
    default:
        return "未知错误";
    }
}

inline void showError(ErrorCode code)
{
    if (code == ErrorCode::SUCCESS)
        return;
    std::string msg = getErrorMsg(code);
    std::cout << "\n";
    std::cout << "╔════════════════════════════════════════════════╗\n";
    std::cout << "║  【错误】" << std::left << std::setw(38) << msg << "║\n";
    std::cout << "║  错误码: " << std::left << std::setw(4) << static_cast<int>(code) << "                                  ║\n";
    std::cout << "╚════════════════════════════════════════════════╝\n";
}