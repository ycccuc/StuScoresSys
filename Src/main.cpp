#include <iostream>
#include "MyConst.h"
#include "StudentManager.h"
#include "UI.h"

int main()
{
    StudentManager manager;
    ErrorCode ret = manager.load();
    if (ret != ErrorCode::SUCCESS)
    {
        showError(ret);
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
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(1024, '\n');
            choice = -1;
        }

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
            showError(ErrorCode::ERROR_INPUT_INVALID);
            break;
        }

        UI::pauseScreen();
    }

    return 0;
}