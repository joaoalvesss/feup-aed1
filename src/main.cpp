#include "Class.h"
#include "Student.h"
#include "Slot.h"
#include "Classes_per_uc.h"
#include "Menu.h"

using namespace std;


int main() {
    ScheduleManager manager = ScheduleManager();
    Menu menu = Menu(manager);
    menu.mainMenu();
    return 0;
}

