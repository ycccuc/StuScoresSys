#include "Logger.h"
#include "MyConst.h"
#include <fstream>
#include <ctime>

void Logger::logDebug(const std::string &func, int errorCode, const std::string &detail)
{
    std::ofstream fp(DEBUG_FILE, std::ios::app);
    if (!fp.is_open())
    {
        return;
    }

    time_t now = time(nullptr);
    char timeStr[64];
    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", localtime(&now));

    fp << "[" << timeStr << "] 函数: " << func << "\n";
    fp << "  错误码: " << errorCode << "\n";
    fp << "  错误信息: " << Logger::getErrorMsg(errorCode) << "\n";
    if (!detail.empty())
    {
        fp << "  详细信息: " << detail << "\n";
    }
    fp << "----------------------------------------\n";
}

std::string Logger::getErrorMsg(int errorCode)
{
    switch (errorCode)
    {
    case SUCCESS:
        return "操作成功";
    case ERROR_MEMORY:
        return "内存分配失败";
    case ERROR_FILE_OPEN:
        return "文件打开失败";
    case ERROR_FILE_READ:
        return "文件读取失败";
    case ERROR_FILE_WRITE:
        return "文件写入失败";
    case ERROR_EMPTY:
        return "数据为空";
    case ERROR_NOT_FOUND:
        return "数据未找到";
    case ERROR_DUPLICATE:
        return "数据重复";
    case ERROR_ID_INVALID:
        return "学号无效(应为" + std::to_string(MIN_ID) + "-" + std::to_string(MAX_ID) + ")";
    case ERROR_ID_EXISTS:
        return "学号已存在";
    case ERROR_ID_NOT_FOUND:
        return "学号不存在";
    case ERROR_NAME_INVALID:
        return "姓名无效(不能为空)";
    case ERROR_NAME_LONG:
        return "姓名过长(最多" + std::to_string(MAX_NAME_LEN) + "字符)";
    case ERROR_SCORE_RANGE:
        return "成绩超出范围(应为" + std::to_string(int(MIN_SCORE)) + "-" + std::to_string(int(MAX_SCORE)) + ")";
    case ERROR_INPUT_INVALID:
        return "输入无效";
    default:
        logDebug("getErrorMsg", errorCode, "未知错误码");
        return "未知错误";
    }
}
