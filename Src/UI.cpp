#include "UI.h"
#include <cstdlib>
#include <limits>

void UI::clearScreen()
{
    system("cls");
}

void UI::pauseScreen()
{
    std::cout << "\n按回车键继续...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void UI::showWelcome()
{
    std::cout << "\n";
    std::cout << "╔════════════════════════════════════════════════╗\n";
    std::cout << "║                                                ║\n";
    std::cout << "║         欢 迎 使 用 学 生 成 绩 管 理 系 统    ║\n";
    std::cout << "║                                                ║\n";
    std::cout << "║              C++ 面向对象版本 8.0              ║\n";
    std::cout << "║                                                ║\n";
    std::cout << "╚════════════════════════════════════════════════╝\n";
}

void UI::showGoodbye()
{
    std::cout << "\n";
    std::cout << "╔════════════════════════════════════════════════╗\n";
    std::cout << "║                                                ║\n";
    std::cout << "║                  感谢使用，再见！              ║\n";
    std::cout << "║                                                ║\n";
    std::cout << "╚════════════════════════════════════════════════╝\n";
    std::cout << "\n";
}

void UI::showMenu()
{
    std::cout << "\n";
    std::cout << "╔════════════════════════════════════════════════╗\n";
    std::cout << "║                                                ║\n";
    std::cout << "║           学 生 成 绩 管 理 系 统              ║\n";
    std::cout << "║                                                ║\n";
    std::cout << "╠════════════════════════════════════════════════╣\n";
    std::cout << "║     1. 学生信息录入                            ║\n";
    std::cout << "║     2. 显示所有学生信息                        ║\n";
    std::cout << "║     3. 查询学生信息                            ║\n";
    std::cout << "║     4. 修改学生成绩                            ║\n";
    std::cout << "║     5. 删除学生信息                            ║\n";
    std::cout << "║     6. 成绩统计                                ║\n";
    std::cout << "║     7. 排序功能                                ║\n";
    std::cout << "║     0. 退出系统                                ║\n";
    std::cout << "║                                                ║\n";
    std::cout << "╚════════════════════════════════════════════════╝\n";
    std::cout << "\n请输入您的选择: ";
}

void UI::printHeader()
{
    std::cout << "┌────────┬────────────────────┬─────────┬─────────┬─────────┬─────────┐\n";
    std::cout << "│ " << std::left << std::setw(6) << "学号" << " │ "
              << std::setw(18) << "姓名" << " │ "
              << std::setw(7) << SUBJECT_NAMES[0] << " │ "
              << std::setw(7) << SUBJECT_NAMES[1] << " │ "
              << std::setw(7) << SUBJECT_NAMES[2] << " │ "
              << std::setw(7) << "平均分" << " │\n";
    std::cout << "├────────┼────────────────────┼─────────┼─────────┼─────────┼─────────┤\n";
}

void UI::printRow(const Student &s)
{
    std::cout << "│" << std::left << std::setw(6) << s.getId() << "│ "
              << std::left << std::setw(18) << s.getName() << " │"
              << std::right << std::fixed << std::setprecision(2)
              << std::setw(8) << s.getScore(0) << " │"
              << std::setw(8) << s.getScore(1) << " │"
              << std::setw(8) << s.getScore(2) << " │"
              << std::setw(8) << s.getAverage() << " │\n";
}

void UI::printFooter()
{
    std::cout << "└────────┴────────────────────┴─────────┴─────────┴─────────┴─────────┘\n";
}

void UI::printStatHeader()
{
    std::cout << "┌─────────┬─────────┬─────────┬─────────┐\n";
    std::cout << "│ " << std::left << std::setw(7) << "科目" << " │ "
              << std::setw(7) << "平均分" << " │ "
              << std::setw(7) << "最高分" << " │ "
              << std::setw(7) << "最低分" << " │\n";
    std::cout << "├─────────┼─────────┼─────────┼─────────┤\n";
}

void UI::printStatRow(const std::string &name, double avg, double max, double min)
{
    std::cout << "│ " << std::left << std::setw(7) << name << " │"
              << std::right << std::fixed << std::setprecision(2)
              << std::setw(8) << avg << " │"
              << std::setw(8) << max << " │"
              << std::setw(8) << min << " │\n";
}

void UI::printStatFooter()
{
    std::cout << "└─────────┴─────────┴─────────┴─────────┘\n";
}

int UI::inputInt(const std::string &prompt)
{
    std::cout << prompt;
    int val;
    std::cin >> val;
    return val;
}

double UI::inputDouble(const std::string &prompt)
{
    std::cout << prompt;
    double val;
    std::cin >> val;
    return val;
}

std::string UI::inputLine(const std::string &prompt)
{
    std::cout << prompt;
    std::string val;
    std::getline(std::cin, val);
    return val;
}

void UI::funcAdd(StudentManager &mgr)
{
    std::cout << "\n================== 学生信息录入 ==================\n\n";

    int id = inputInt("请输入学号 (1-99999999): ");
    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(1024, '\n');
        showError(ErrorCode::ERROR_INPUT_INVALID);
        return;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string name = inputLine("请输入姓名: ");

    std::cout << "\n请输入" << SUBJECT_COUNT << "门课程成绩 (0-150):\n\n";
    std::array<double, SUBJECT_COUNT> scores{};
    for (int i = 0; i < SUBJECT_COUNT; ++i)
    {
        scores[i] = inputDouble("  " + SUBJECT_NAMES[i] + ": ");
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(1024, '\n');
            showError(ErrorCode::ERROR_INPUT_INVALID);
            return;
        }
    }

    Student s(id, name, scores);
    ErrorCode ret = mgr.add(s);
    if (ret != ErrorCode::SUCCESS)
    {
        showError(ret);
        return;
    }

    ret = mgr.save();
    if (ret != ErrorCode::SUCCESS)
    {
        showError(ret);
        return;
    }

    std::cout << "\n学生信息录入成功！\n";
    std::cout << "  学号: " << id << ", 姓名: " << name
              << ", 平均分: " << std::fixed << std::setprecision(2)
              << s.getAverage() << "\n";
}

void UI::funcDisplay(const StudentManager &mgr)
{
    std::cout << "\n================== 所有学生信息 ==================\n\n";
    if (mgr.empty())
    {
        showError(ErrorCode::ERROR_EMPTY);
        return;
    }

    std::cout << "共有 " << mgr.size() << " 名学生\n\n";
    printHeader();
    for (const auto &s : mgr.getAll())
    {
        printRow(s);
    }
    printFooter();
}

void UI::funcQuery(const StudentManager &mgr)
{
    std::cout << "\n================== 查询学生信息 ==================\n\n";
    if (mgr.empty())
    {
        showError(ErrorCode::ERROR_EMPTY);
        return;
    }

    int id = inputInt("请输入要查询的学号: ");
    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(1024, '\n');
        showError(ErrorCode::ERROR_INPUT_INVALID);
        return;
    }

    const Student *s = mgr.find(id);
    if (!s)
    {
        showError(ErrorCode::ERROR_ID_NOT_FOUND);
        return;
    }

    std::cout << "\n找到学生信息:\n\n";
    printHeader();
    printRow(*s);
    printFooter();
}

void UI::funcModify(StudentManager &mgr)
{
    std::cout << "\n================== 修改学生成绩 ==================\n\n";
    if (mgr.empty())
    {
        showError(ErrorCode::ERROR_EMPTY);
        return;
    }

    int id = inputInt("请输入要修改的学号: ");
    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(1024, '\n');
        showError(ErrorCode::ERROR_INPUT_INVALID);
        return;
    }

    const Student *s = mgr.find(id);
    if (!s)
    {
        showError(ErrorCode::ERROR_ID_NOT_FOUND);
        return;
    }

    std::cout << "\n找到学生: " << s->getName() << " (学号: " << s->getId() << ")\n\n";
    std::cout << "当前成绩：\n";
    for (int i = 0; i < SUBJECT_COUNT; ++i)
    {
        std::cout << "  " << SUBJECT_NAMES[i] << ": "
                  << std::fixed << std::setprecision(2) << s->getScore(i) << "\n";
    }

    std::cout << "\n请输入新的成绩:\n\n";
    std::array<double, SUBJECT_COUNT> scores{};
    for (int i = 0; i < SUBJECT_COUNT; ++i)
    {
        scores[i] = inputDouble("  " + SUBJECT_NAMES[i] + ": ");
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(1024, '\n');
            showError(ErrorCode::ERROR_INPUT_INVALID);
            return;
        }
    }

    ErrorCode ret = mgr.modify(id, scores);
    if (ret != ErrorCode::SUCCESS)
    {
        showError(ret);
        return;
    }

    ret = mgr.save();
    if (ret != ErrorCode::SUCCESS)
    {
        showError(ret);
        return;
    }

    s = mgr.find(id);
    std::cout << "\n成绩修改成功! 新平均分: "
              << std::fixed << std::setprecision(2) << s->getAverage() << "\n";
}

void UI::funcDelete(StudentManager &mgr)
{
    std::cout << "\n================== 删除学生信息 ==================\n\n";
    if (mgr.empty())
    {
        showError(ErrorCode::ERROR_EMPTY);
        return;
    }

    int id = inputInt("请输入要删除的学号: ");
    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(1024, '\n');
        showError(ErrorCode::ERROR_INPUT_INVALID);
        return;
    }

    const Student *s = mgr.find(id);
    if (!s)
    {
        showError(ErrorCode::ERROR_ID_NOT_FOUND);
        return;
    }

    std::cout << "\n找到学生: " << s->getName() << " (学号: " << s->getId() << ")\n";
    int confirm = inputInt("\n确定要删除吗? (1-是, 0-否): ");
    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(1024, '\n');
        showError(ErrorCode::ERROR_INPUT_INVALID);
        return;
    }

    if (confirm != 1)
    {
        std::cout << "\n已取消删除。\n";
        return;
    }

    ErrorCode ret = mgr.remove(id);
    if (ret != ErrorCode::SUCCESS)
    {
        showError(ret);
        return;
    }

    ret = mgr.save();
    if (ret != ErrorCode::SUCCESS)
    {
        showError(ret);
        return;
    }

    std::cout << "\n学生信息已删除!\n";
}

void UI::funcStat(const StudentManager &mgr)
{
    std::cout << "\n================== 成绩统计 ==================\n";

    StudentManager::StatResult stat{};
    ErrorCode ret = mgr.getStatistics(stat);
    if (ret != ErrorCode::SUCCESS)
    {
        showError(ret);
        return;
    }

    std::cout << "\n【各科目统计】\n\n";
    printStatHeader();
    for (int i = 0; i < SUBJECT_COUNT; ++i)
    {
        printStatRow(SUBJECT_NAMES[i], stat.avg[i], stat.max[i], stat.min[i]);
    }
    printStatFooter();

    std::cout << "\n【总体统计】\n\n";
    std::cout << "  学生总数:   " << mgr.size() << "\n";
    std::cout << "  总平均分:   " << std::fixed << std::setprecision(2) << stat.totalAvg << "\n";
    if (stat.topStudent)
    {
        std::cout << "  最高平均分: " << stat.topStudent->getAverage()
                  << " (" << stat.topStudent->getName() << ", 学号" << stat.topStudent->getId() << ")\n";
    }
    if (stat.bottomStudent)
    {
        std::cout << "  最低平均分: " << stat.bottomStudent->getAverage()
                  << " (" << stat.bottomStudent->getName() << ", 学号" << stat.bottomStudent->getId() << ")\n";
    }
}

void UI::funcSort(StudentManager &mgr)
{
    std::cout << "\n================== 排序功能 ==================\n\n";
    if (mgr.empty())
    {
        showError(ErrorCode::ERROR_EMPTY);
        return;
    }
    if (mgr.size() == 1)
    {
        std::cout << "只有一名学生，无需排序！\n";
        return;
    }

    std::cout << "请选择排序依据:\n\n";
    std::cout << "  1. 按" << SUBJECT_NAMES[0] << "成绩排序\n";
    std::cout << "  2. 按" << SUBJECT_NAMES[1] << "成绩排序\n";
    std::cout << "  3. 按" << SUBJECT_NAMES[2] << "成绩排序\n";
    std::cout << "  4. 按平均分排序\n";
    int subject = inputInt("\n请输入选择 (1-4): ");
    if (std::cin.fail() || subject < 1 || subject > 4)
    {
        std::cin.clear();
        std::cin.ignore(1024, '\n');
        showError(ErrorCode::ERROR_INPUT_INVALID);
        return;
    }

    std::cout << "\n请选择排序方式:\n\n";
    std::cout << "  1. 升序（从低到高）\n";
    std::cout << "  2. 降序（从高到低）\n";
    int order = inputInt("\n请输入选择 (1-2): ");
    if (std::cin.fail() || (order != 1 && order != 2))
    {
        std::cin.clear();
        std::cin.ignore(1024, '\n');
        showError(ErrorCode::ERROR_INPUT_INVALID);
        return;
    }

    mgr.sortBy(subject - 1, order == SORT_ORDER_ASC);

    ErrorCode ret = mgr.save();
    if (ret != ErrorCode::SUCCESS)
    {
        showError(ret);
        return;
    }

    const char *sortNames[] = {"语文", "数学", "英语", "平均分"};
    std::cout << "\n已按 " << sortNames[subject - 1] << " "
              << (order == SORT_ORDER_ASC ? "升序" : "降序") << " 排序:\n\n";

    printHeader();
    for (const auto &s : mgr.getAll())
    {
        printRow(s);
    }
    printFooter();
}