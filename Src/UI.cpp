#include "UI.h"
#include "Logger.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <limits>

using namespace std;

void UI::clearScreen()
{
    system("cls");
}

void UI::pauseScreen()
{
    cout << "\n按回车键继续...";
    cin.get();
}

void UI::showError(int errorCode)
{
    if (errorCode == SUCCESS)
    {
        return;
    }

    string msg = Logger::getErrorMsg(errorCode);
    cout << "\n";
    cout << "╔════════════════════════════════════════════════╗\n";
    cout << "║  【错误】" << left << setw(38) << msg << "║\n";
    cout << "║  错误码: " << left << setw(4) << errorCode << "                                  ║\n";
    cout << "╚════════════════════════════════════════════════╝\n";
}

void UI::showWelcome()
{
    cout << "\n";
    cout << "╔════════════════════════════════════════════════╗\n";
    cout << "║                                                ║\n";
    cout << "║         欢 迎 使 用 学 生 成 绩 管 理 系 统    ║\n";
    cout << "║                                                ║\n";
    cout << "║              C++ 面向对象版本 8.0              ║\n";
    cout << "║                                                ║\n";
    cout << "╚════════════════════════════════════════════════╝\n";
}

void UI::showGoodbye()
{
    cout << "\n";
    cout << "╔════════════════════════════════════════════════╗\n";
    cout << "║                                                ║\n";
    cout << "║                  感谢使用，再见！              ║\n";
    cout << "║                                                ║\n";
    cout << "╚════════════════════════════════════════════════╝\n";
    cout << "\n";
}

void UI::showMenu()
{
    cout << "\n";
    cout << "╔════════════════════════════════════════════════╗\n";
    cout << "║                                                ║\n";
    cout << "║            学 生 成 绩 管 理 系 统             ║\n";
    cout << "║                                                ║\n";
    cout << "╠════════════════════════════════════════════════╣\n";
    cout << "║     1. 学生信息录入                            ║\n";
    cout << "║     2. 显示所有学生信息                        ║\n";
    cout << "║     3. 查询学生信息                            ║\n";
    cout << "║     4. 修改学生成绩                            ║\n";
    cout << "║     5. 删除学生信息                            ║\n";
    cout << "║     6. 成绩统计                                ║\n";
    cout << "║     7. 排序功能                                ║\n";
    cout << "║     0. 退出系统                                ║\n";
    cout << "║                                                ║\n";
    cout << "╚════════════════════════════════════════════════╝\n";
    cout << "\n请输入您的选择: ";
}

void UI::printHeader()
{
    cout << "┌────────┬────────────────────┬─────────┬─────────┬─────────┬─────────┐\n";
    cout << "│ 学号   │ 姓名               │";
    cout << " " << left << setw(7) << SUBJECT_NAMES[0] << " │";
    cout << " " << left << setw(7) << SUBJECT_NAMES[1] << " │";
    cout << " " << left << setw(7) << SUBJECT_NAMES[2] << " │";
    cout << " 平均分  │\n";
    cout << "├────────┼────────────────────┼─────────┼─────────┼─────────┼─────────┤\n";
}

void UI::printRow(const Student &s)
{
    cout << "│" << left << setw(6) << s.getId() << " │";
    cout << " " << left << setw(18) << s.getName() << " │";
    cout << " " << right << setw(7) << fixed << setprecision(2) << s.getScore(0) << " │";
    cout << " " << right << setw(7) << fixed << setprecision(2) << s.getScore(1) << " │";
    cout << " " << right << setw(7) << fixed << setprecision(2) << s.getScore(2) << " │";
    cout << " " << right << setw(7) << fixed << setprecision(2) << s.getAverage() << " │\n";
}

void UI::printFooter()
{
    cout << "└────────┴────────────────────┴─────────┴─────────┴─────────┴─────────┘\n";
}

void UI::printStatHeader()
{
    cout << "┌─────────┬─────────┬─────────┬─────────┐\n";
    cout << "│ 科目    │ 平均分  │ 最高分  │ 最低分  │\n";
    cout << "├─────────┼─────────┼─────────┼─────────┤\n";
}

void UI::printStatRow(const string &name, double avg, double max, double min)
{
    cout << "│ " << left << setw(7) << name << " │";
    cout << " " << right << setw(7) << fixed << setprecision(2) << avg << " │";
    cout << " " << right << setw(7) << fixed << setprecision(2) << max << " │";
    cout << " " << right << setw(7) << fixed << setprecision(2) << min << " │\n";
}

void UI::printStatFooter()
{
    cout << "└─────────┴─────────┴─────────┴─────────┘\n";
}

int UI::inputInt(const string &prompt)
{
    int value;
    while (true)
    {
        cout << prompt;
        cin >> value;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "【错误】请输入有效的整数！\n";
            continue;
        }

        char c = cin.peek();
        if (c != '\n' && c != EOF)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "【错误】输入包含非法字符，请只输入整数！\n";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return value;
    }
}

double UI::inputDouble(const string &prompt)
{
    double value;
    while (true)
    {
        cout << prompt;
        cin >> value;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "【错误】请输入有效的数字！\n";
            continue;
        }

        char c = cin.peek();
        if (c != '\n' && c != EOF)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "【错误】输入包含非法字符，请只输入数字！\n";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return value;
    }
}

string UI::inputLine(const string &prompt)
{
    cout << prompt;
    string line;
    getline(cin, line);
    return line;
}

void UI::funcAdd(StudentManager &mgr)
{
    cout << "\n================== 学生信息录入 ==================\n\n";

    int id = inputInt("请输入学号 (1-99999999): ");
    if (!StudentManager::isIdValid(id))
    {
        cout << "【错误】学号无效！\n";
        return;
    }

    if (mgr.findStudent(id) != -1)
    {
        cout << "【错误】学号已存在！\n";
        return;
    }

    string name = inputLine("请输入姓名: ");
    if (!StudentManager::isNameValid(name))
    {
        cout << "【错误】姓名无效（不能为空或超过50字符）！\n";
        return;
    }

    cout << "\n请输入" << SUBJECT_COUNT << "门课程成绩 (0-150):\n\n";
    double scores[SUBJECT_COUNT];

    for (int i = 0; i < SUBJECT_COUNT; i++)
    {
        scores[i] = inputDouble("  " + SUBJECT_NAMES[i] + ": ");

        if (!StudentManager::isScoreValid(scores[i]))
        {
            cout << "【错误】成绩超出范围（应为0-150）！\n";
            return;
        }
    }

    Student s(id, name, scores);
    ErrorCode ret = mgr.addStudent(s);
    if (ret != SUCCESS)
    {
        cout << "【错误】添加失败！\n";
        return;
    }

    ret = mgr.saveToFile();
    if (ret != SUCCESS)
    {
        cout << "【错误】保存文件失败！\n";
        return;
    }

    cout << "\n学生信息录入成功！\n";
    cout << "  学号: " << id << ", 姓名: " << name;
    cout << ", 平均分: " << fixed << setprecision(2) << s.getAverage() << "\n";
}

void UI::funcDisplay(const StudentManager &mgr)
{
    cout << "\n================== 所有学生信息 ==================\n\n";

    if (mgr.isEmpty())
    {
        cout << "【提示】暂无学生记录！\n";
        return;
    }

    cout << "共有 " << mgr.getCount() << " 名学生\n\n";

    printHeader();
    const vector<Student> &all = mgr.getAllStudents();
    for (size_t i = 0; i < all.size(); i++)
    {
        printRow(all[i]);
    }
    printFooter();
}

void UI::funcQuery(const StudentManager &mgr)
{
    cout << "\n================== 查询学生信息 ==================\n\n";

    if (mgr.isEmpty())
    {
        cout << "【提示】暂无学生记录！\n";
        return;
    }

    int id = inputInt("请输入要查询的学号: ");
    int index = mgr.findStudent(id);

    if (index == -1)
    {
        cout << "【错误】学号不存在！\n";
        return;
    }

    cout << "\n找到学生信息:\n\n";
    printHeader();
    printRow(mgr.getStudent(index));
    printFooter();
}

void UI::funcModify(StudentManager &mgr)
{
    cout << "\n================== 修改学生成绩 ==================\n\n";

    if (mgr.isEmpty())
    {
        cout << "【提示】暂无学生记录！\n";
        return;
    }

    int id = inputInt("请输入要修改的学号: ");
    int index = mgr.findStudent(id);

    if (index == -1)
    {
        cout << "【错误】学号不存在！\n";
        return;
    }

    Student s = mgr.getStudent(index);
    cout << "\n找到学生: " << s.getName() << " (学号: " << s.getId() << ")\n\n";
    cout << "当前成绩：\n";
    for (int i = 0; i < SUBJECT_COUNT; i++)
    {
        cout << "  " << SUBJECT_NAMES[i] << ": "
             << fixed << setprecision(2) << s.getScore(i) << "\n";
    }

    cout << "\n请输入新的成绩:\n\n";
    double newScores[SUBJECT_COUNT];

    for (int i = 0; i < SUBJECT_COUNT; i++)
    {
        newScores[i] = inputDouble("  " + SUBJECT_NAMES[i] + ": ");

        if (!StudentManager::isScoreValid(newScores[i]))
        {
            cout << "【错误】成绩超出范围（应为0-150）！\n";
            return;
        }
    }

    ErrorCode ret = mgr.modifyStudent(id, newScores);
    if (ret != SUCCESS)
    {
        cout << "【错误】修改失败！\n";
        return;
    }

    ret = mgr.saveToFile();
    if (ret != SUCCESS)
    {
        cout << "【错误】保存文件失败！\n";
        return;
    }

    s = mgr.getStudent(index);
    cout << "\n成绩修改成功! 新平均分: "
         << fixed << setprecision(2) << s.getAverage() << "\n";
}

void UI::funcDelete(StudentManager &mgr)
{
    cout << "\n================== 删除学生信息 ==================\n\n";

    if (mgr.isEmpty())
    {
        cout << "【提示】暂无学生记录！\n";
        return;
    }

    int id = inputInt("请输入要删除的学号: ");
    int index = mgr.findStudent(id);

    if (index == -1)
    {
        cout << "【错误】学号不存在！\n";
        return;
    }

    Student s = mgr.getStudent(index);
    cout << "\n找到学生: " << s.getName() << " (学号: " << s.getId() << ")\n";

    int confirm = inputInt("\n确定要删除吗? (1-是, 0-否): ");
    if (confirm != 1)
    {
        cout << "\n已取消删除。\n";
        return;
    }

    ErrorCode ret = mgr.deleteStudent(id);
    if (ret != SUCCESS)
    {
        cout << "【错误】删除失败！\n";
        return;
    }

    ret = mgr.saveToFile();
    if (ret != SUCCESS)
    {
        cout << "【错误】保存文件失败！\n";
        return;
    }

    cout << "\n学生信息已删除!\n";
}

void UI::funcStat(const StudentManager &mgr)
{
    cout << "\n================== 成绩统计 ==================\n";

    if (mgr.isEmpty())
    {
        cout << "【提示】暂无学生记录！\n";
        return;
    }

    double avg[SUBJECT_COUNT];
    double maxs[SUBJECT_COUNT];
    double mins[SUBJECT_COUNT];
    double totalAvg;
    int topIdx, bottomIdx;

    mgr.calcStatistics(avg, maxs, mins, totalAvg, topIdx, bottomIdx);

    cout << "\n【各科目统计】\n\n";
    printStatHeader();
    for (int i = 0; i < SUBJECT_COUNT; i++)
    {
        printStatRow(SUBJECT_NAMES[i], avg[i], maxs[i], mins[i]);
    }
    printStatFooter();

    Student top = mgr.getStudent(topIdx);
    Student bottom = mgr.getStudent(bottomIdx);

    cout << "\n【总体统计】\n\n";
    cout << "  学生总数:   " << mgr.getCount() << "\n";
    cout << "  总平均分:   " << fixed << setprecision(2) << totalAvg << "\n";
    cout << "  最高平均分: " << top.getAverage()
         << " (" << top.getName() << ", 学号" << top.getId() << ")\n";
    cout << "  最低平均分: " << bottom.getAverage()
         << " (" << bottom.getName() << ", 学号" << bottom.getId() << ")\n";
}

void UI::funcSort(StudentManager &mgr)
{
    cout << "\n================== 排序功能 ==================\n\n";

    if (mgr.isEmpty())
    {
        cout << "【提示】暂无学生记录！\n";
        return;
    }

    if (mgr.getCount() == 1)
    {
        cout << "只有一名学生，无需排序！\n";
        return;
    }

    cout << "请选择排序依据:\n\n";
    cout << "  1. 按" << SUBJECT_NAMES[0] << "成绩排序\n";
    cout << "  2. 按" << SUBJECT_NAMES[1] << "成绩排序\n";
    cout << "  3. 按" << SUBJECT_NAMES[2] << "成绩排序\n";
    cout << "  4. 按平均分排序\n";

    int sortBy = inputInt("\n请输入选择 (1-4): ");
    if (sortBy < 1 || sortBy > 4)
    {
        cout << "【错误】选择无效！\n";
        return;
    }

    cout << "\n请选择排序方式:\n\n";
    cout << "  1. 升序（从低到高）\n";
    cout << "  2. 降序（从高到低）\n";

    int order = inputInt("\n请输入选择 (1-2): ");
    if (order != 1 && order != 2)
    {
        cout << "【错误】选择无效！\n";
        return;
    }

    mgr.sortStudents(sortBy, order == SORT_ORDER_ASC);

    ErrorCode ret = mgr.saveToFile();
    if (ret != SUCCESS)
    {
        cout << "【错误】保存文件失败！\n";
        return;
    }

    const char *sortNames[] = {"语文", "数学", "英语", "平均分"};
    cout << "\n已按 " << sortNames[sortBy - 1] << " "
         << (order == 1 ? "升序" : "降序") << " 排序:\n\n";

    printHeader();
    const vector<Student> &all = mgr.getAllStudents();
    for (size_t i = 0; i < all.size(); i++)
    {
        printRow(all[i]);
    }
    printFooter();
}