#ifndef MYCONST_H
#define MYCONST_H

#include <string>

/*------------------------------- 错误码 -------------------------------*/

enum ErrorCode
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

/*------------------------------- 常量 -------------------------------*/

const int MAX_NAME_LEN = 50;
const int SUBJECT_COUNT = 3;

const int MIN_ID = 1;
const int MAX_ID = 99999999;

const double MIN_SCORE = 0.0;
const double MAX_SCORE = 150.0;

const int SORT_BY_CHINESE = 1;
const int SORT_BY_MATH = 2;
const int SORT_BY_ENGLISH = 3;
const int SORT_BY_AVERAGE = 4;

const int SORT_ORDER_ASC = 1;
const int SORT_ORDER_DESC = 2;

const std::string DATA_FILE = "students.txt";
const std::string DEBUG_FILE = "debug.txt";

const std::string SUBJECT_NAMES[SUBJECT_COUNT] = {"语文", "数学", "英语"};

#endif