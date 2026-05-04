#pragma once
#include "StudentManager.h"

class UI
{
public:
    static void clearScreen();
    static void pauseScreen();

    static void showWelcome();
    static void showGoodbye();
    static void showMenu();

    static void printHeader();
    static void printRow(const Student &s);
    static void printFooter();
    static void printStatHeader();
    static void printStatRow(const std::string &name, double avg, double max, double min);
    static void printStatFooter();

    // 功能界面（直接操作 Manager）
    static void funcAdd(StudentManager &mgr);
    static void funcDisplay(const StudentManager &mgr);
    static void funcQuery(const StudentManager &mgr);
    static void funcModify(StudentManager &mgr);
    static void funcDelete(StudentManager &mgr);
    static void funcStat(const StudentManager &mgr);
    static void funcSort(StudentManager &mgr);

    // 基础输入
    static int inputInt(const std::string &prompt);
    static double inputDouble(const std::string &prompt);
    static std::string inputLine(const std::string &prompt);
};