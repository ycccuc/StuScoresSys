#include <iostream>
#include "MyConst.h"
#include "StudentManager.h"
#include "UI.h"
#include "Logger.h"

using namespace std;

int main()
{
    StudentManager manager;
    ErrorCode ret = manager.loadFromFile();

    if (ret != SUCCESS)
    {
        Logger::logDebug("main", ret, "加载数据失败");
        UI::showError(ret);
        return 1;
    }

    UI::clearScreen();
    UI::showWelcome();
    UI::pauseScreen();

    while (true)
    {
        UI::clearScreen();
        UI::showMenu();

        int choice = UI::inputInt("");

        switch (choice)
        {
        case 1:
            UI::funcAdd(manager);
            break;
        case 2:
            UI::funcDisplay(manager);
            break;
        case 3:
            UI::funcQuery(manager);
            break;
        case 4:
            UI::funcModify(manager);
            break;
        case 5:
            UI::funcDelete(manager);
            break;
        case 6:
            UI::funcStat(manager);
            break;
        case 7:
            UI::funcSort(manager);
            break;
        case 0:
            UI::clearScreen();
            UI::showGoodbye();
            return 0;
        default:
            Logger::logDebug("main", ERROR_INPUT_INVALID, "菜单选择错误");
            UI::showError(ERROR_INPUT_INVALID);
            break;
        }

        UI::pauseScreen();
    }

    return 0;
}