#include "Menu.h"
#include <iostream>

Menu::Menu(ScheduleManager &schedule_manager) : schedule_manager(schedule_manager) {}

// Main menu

void Menu::mainMenu() {
    std::cout << endl;
    std::cout << "------- Main Menu -------" << endl;
    std::cout << "[1] Quit and Save" << endl;
    std::cout << "[2] Make a request" << endl;
    std::cout << "[3] Display information" << endl;
    int choice;
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    while (!std::cin.good()) {
        std::cin.clear();
        std::cin.ignore(123, '\n');
        std::cout << "[Warning!] Please enter a valid option!";
        mainMenu();
    }
    switch (choice) {
        case 1: schedule_manager.processRequests(); break;
        case 2: requestTypeMenu(); break;
        case 3: displayMenu(); break;
        default: std::cout << "### [Warning] Please choose from one of the listed numbers ###" << endl ; mainMenu() ;  break;
    }
}

void Menu::displayMenu() {
    std::cout << endl;
    std::cout << "--------  Display Menu  ---------" << endl;
    std::cout << "## What do you want to see? ##" << endl;
    std::cout << "[1] Go back to main menu" << endl;
    std::cout << "[2] Students in Class, Uc or Year" << endl;
    std::cout << "[3] Student's schedule" << endl;
    std::cout << "[4] Class schedule" << endl;
    std::cout << "[5] Occupation of Class, Uc or Year" << endl;
    int choice;
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    if(!std::cin.good()) {
        std::cin.clear();
        std::cin.ignore(123, '\n');
        std::cout << endl;
        std::cout << "[Warning] Please enter a valid option!" << endl;
        displayMenu();
    }
    switch (choice) {
        case 1: mainMenu(); break;
        case 2: studentDisplayMenu(); break;
        case 3: studentScheduleMenu(); break;
        case 4: classScheduleMenu(); break;
        case 5: occupationMenu(); break;
        default: std::cout << "### Please type a number from the list ###" << endl; displayMenu(); break;
    }
}

void Menu::requestTypeMenu() {

    std::cout << endl;
    std::cout << " ---------  Request Menu  ---------" << endl;
    std::cout << "[1] Go back to Main Menu" << endl;
    std::cout << "[2] Remove a student from a class" << endl;
    std::cout << "[3] Add a student to a new class" << endl;
    std::cout << "[4] Swap a student class(es)" << endl;

    int choice;
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    while(!std::cin.good()) {
        std::cin.clear();
        std::cin.ignore();
        std::cout << "[Warning] Please enter a valid option!" << endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
    }

    switch (choice) {
        case 1: mainMenu(); break;
        case 2: requestRMenu(); break;
        case 3: requestAMenu(); break;
        case 4: requestSMenu(); break;
        default: std::cout << "### Please type a number from the list ###" << endl; requestTypeMenu(); break;
    }
}

void Menu::requestRMenu() {

    std::cout << endl;
    std::cout << "------- Remove Class Request -------"  << endl;
    std::string ucCode;
    std::string classCode;
    list<Classes_per_uc> actual;
    int studentCode;
    char type = 'R';
    std::cout << "[1] Go back to Request Menu" << endl;

    std::cout << "Type student code:";
    std::cin >> studentCode;
    if (!std::cin.good()) {
        std::cin.clear();
        std::cin.ignore(123, '\n');
        std::cout << "### [Warning] Please type a valid studentCode. Ex: 202000000 ###" << endl;
        std::cout << "             ###      Aborting Request      ###" << endl;
        requestRMenu();
    }   // invalid input
    if (studentCode == 1) { // Exit code
        requestTypeMenu();
        return;
    }  // exit code
    if (schedule_manager.getStudent(studentCode).get_studentCode() == 0) { // Can't find student
        std::cout << "Student not in database!";
        requestRMenu();
    } // student not in database
    std::cout << "Starting a request for student " << schedule_manager.getStudent(studentCode).get_studentName()<< endl;
    std::cout << "Type [Done] to submit request." << endl;

    while (true) {
        std::cout << "Type ucCode to remove: ";
        std::cin >> ucCode;
        if (!std::cin.good()) {
            std::cin.clear();
            std::cin.ignore(123, '\n');
            std::cout << "### [Warning] Please type a valid input. Ex: ucCode -> L.EIC001 | classCode -> 1LEIC01 ###"
                      << endl;
            std::cout << "                  ###     Aborting Request    #### " << endl;
            requestRMenu();
            return;
        }
        if (ucCode == "Done") break;
        if (ucCode == std::to_string(1)) { // Exit code
            std::cout << endl;
            requestTypeMenu();
            return;
        }

        std::cout << "Type classCode to remove: ";
        std::cin >> classCode;
        if (!std::cin.good()) {
            std::cin.clear();
            std::cin.ignore(123, '\n');
            std::cout << "### [Warning] Please type a valid input. Ex: ucCode -> L.EIC001 classCode -> 1LEIC01 ###"
            << endl;
            std::cout << "###      Request Aborted       ###"   << endl;
            requestRMenu();
            return;
        }
        if (classCode == std::to_string(1)) { // Exit code
            std::cout << endl;
            requestTypeMenu();
            return;
        }
        Classes_per_uc cpu = Classes_per_uc(ucCode, classCode);
        if (schedule_manager.getClass(cpu).getUcCode() == "null" ||
            schedule_manager.getClass(cpu).getClassCode() == "null") {
            std::cout << "### Class not in database! ###" << endl;
            std::cout << "###     Request Aborted    ###" <<  endl;
            requestRMenu();
            return;
        }
        actual.push_back(cpu);
        std::cout << endl;
        std::cout << "Type [Done] to submit request." << endl;
    }
    if (actual.empty()) {
        std::cout << "###   Empty Request! Aborting...  ###" << endl;
        requestRMenu();
        return;
    }
    Request r = Request(actual, actual, studentCode, type);
    schedule_manager.saveRequest(r);
    std::cout << "Request submitted for approval" << endl;
    mainMenu();
}

void Menu::requestAMenu() {
    std::cout << endl;
    std::cout << "------- Add Class Request -------"  << endl;
    std::string ucCode;
    std::string classCode;
    list<Classes_per_uc> pretended;
    int studentCode;
    char type = 'A';
    std::cout << "[1] Go back to Request Menu" << endl;

    std::cout << "Type student code:";
    std::cin >> studentCode;
    if (!std::cin.good()) {
        std::cin.clear();
        std::cin.ignore(123, '\n');
        std::cout << "### [Warning] Please type a valid studentCode. Ex: 202000000 ###" << endl;
        std::cout << "             ###      Aborting Request      ###" << endl;
        requestAMenu();
    }   // invalid input
    if (studentCode == 1) { // Exit code
        requestTypeMenu();;
        return;
    }  // exit code
    if (schedule_manager.getStudent(studentCode).get_studentCode() == 0) { // Can't find student
        std::cout << "Student not in database!";
        std::cout << "### Aborting Request ###"<< endl;
        requestAMenu();
    } // student not in database
    std::cout << "Starting a request for student " << schedule_manager.getStudent(studentCode).get_studentName()
              << endl;
    std::cout << "Type [Done] to submit request." << endl;

    while (true) {
        std::cout << "Type ucCode to add: ";
        std::cin >> ucCode;
        if (!std::cin.good()) {
            std::cin.clear();
            std::cin.ignore(123, '\n');
            std::cout << "### [Warning] Please type a valid input. Ex: ucCode -> L.EIC001 classCode -> 1LEIC01 ###"
                      << endl;
            std::cout << "                 ###     Aborting Request    #### " << endl;
            requestAMenu();
            return;
        }
        if (ucCode == "Done") break;
        if (ucCode == std::to_string(1)) { // Exit code
            std::cout << endl;
            requestTypeMenu();
            return;
        }

        std::cout << "Type classCode to add: ";
        std::cin >> classCode;
        if (!std::cin.good()) {
            std::cin.clear();
            std::cin.ignore(123, '\n');
            std::cout << "### [Warning] Please type a valid input. Ex: ucCode -> L.EIC001 classCode -> 1LEIC01 ###"
                      << endl;
            std::cout << "###      Aborting Request       ###"   << endl;
            requestAMenu();
            return;
        }
        if (classCode == std::to_string(1)) { // Exit code
            std::cout << endl;
            requestTypeMenu();
            return;
        }
        Classes_per_uc cpu = Classes_per_uc(ucCode, classCode);
        if (schedule_manager.getClass(cpu).getUcCode() == "null" ||
            schedule_manager.getClass(cpu).getClassCode() == "null") {
            std::cout << "### Class not in database! ###" << endl;
            std::cout << "###    Aborting Request    ###" <<  endl;
            requestAMenu();
            return;
        }
        pretended.push_back(cpu);
        std::cout << endl;
        std::cout << "Type [Done] to submit request." << endl;
    }
    if (pretended.empty()) {
        std::cout << "###   Empty Request! Aborting...  ###" << endl;
        requestAMenu();
        return;
    }
    Request r = Request(pretended, pretended, studentCode, type);
    schedule_manager.saveRequest(r);
    std::cout << "Request submitted for approval" << endl;
    mainMenu();
}

void Menu::requestSMenu() {
    std::cout << endl;
    std::cout << "------- Swap Class(es) Request -------"  << endl;
    std::string ucCode;
    std::string actualClassCode, pretendedClassCode;
    list<Classes_per_uc> pretended;
    list<Classes_per_uc> actual;
    int studentCode;
    char type = 'S';
    std::cout << "[1] Go back to Request Menu" << endl;

    std::cout << "Type student code:";
    std::cin >> studentCode;
    if (!std::cin.good()) {
        std::cin.clear();
        std::cin.ignore(123, '\n');
        std::cout << "### [Warning] Please type a valid studentCode. Ex: 202000000 ###" << endl;
        std::cout << "             ###      Aborting Request      ###" << endl;
        requestSMenu();
    }   // invalid input

    if (studentCode == 1) { // Exit code
        requestTypeMenu();
        return;
    }  // exit code

    if (schedule_manager.getStudent(studentCode).get_studentCode() == 0) { // Can't find student
        std::cout << "Student not in database!";
        std::cout << "### Aborting Request ###"<< endl;
        requestSMenu();
    } // student not in database
    std::cout << "Starting a request for student " << schedule_manager.getStudent(studentCode).get_studentName() << endl;
    std::cout << "Type [Done] to submit request." << endl;

    while (true) {
        std::cout << "Type ucCode to change: ";
        std::cin >> ucCode;
        if (!std::cin.good()) {
            std::cin.clear();
            std::cin.ignore(123, '\n');
            std::cout << "### [Warning] Please type a valid input. Ex: ucCode -> L.EIC001 classCode -> 1LEIC01 ###"
                      << endl;
            std::cout << "                 ###     Aborting Request    #### " << endl;
            requestSMenu();
            return;
        }
        if (ucCode == "Done") break;
        if (ucCode == std::to_string(1)) { // Exit code
            std::cout << endl;
            requestTypeMenu();
            return;
        }

        std::cout << "Type desired classCode: ";
        std::cin >> pretendedClassCode;
        if (!std::cin.good()) {
            std::cin.clear();
            std::cin.ignore(123, '\n');
            std::cout << "### [Warning] Please type a valid input. Ex: ucCode -> L.EIC001 classCode -> 1LEIC01 ###"
                      << endl;
            std::cout << "###      Aborting Request       ###"   << endl;
            requestSMenu();
            return;
        }
        if (pretendedClassCode == std::to_string(1)) { // Exit code
            std::cout << endl;
            requestTypeMenu();
            return;
        }

        Classes_per_uc cpu1 = Classes_per_uc(ucCode, pretendedClassCode); // ERRO AQUI
        if (schedule_manager.getClass(cpu1).getUcCode() == "null" ||
            schedule_manager.getClass(cpu1).getClassCode() == "null") {
            std::cout << "### Class not in database! ###" << endl;
            std::cout << "###    Aborting Request    ###" <<  endl;
            requestSMenu();
            return;
        }

        std::cout << "Type your current classCode: ";
        std::cin >> actualClassCode;
        if (!std::cin.good()) {
            std::cin.clear();
            std::cin.ignore(123, '\n');
            std::cout << "### [Warning] Please type a valid input. Ex: ucCode -> L.EIC001 classCode -> 1LEIC01 ###"
                      << endl;
            std::cout << "###      Aborting Request       ###"   << endl;
            requestSMenu();
            return;
        }
        if (pretendedClassCode == std::to_string(1)) { // Exit code
            std::cout << endl;
            requestTypeMenu();
            return;
        }

        Classes_per_uc cpu2 = Classes_per_uc(ucCode, actualClassCode); // ERRO AQUI
        if (schedule_manager.getClass(cpu2).getUcCode() == "null" ||
            schedule_manager.getClass(cpu2).getClassCode() == "null") {
            std::cout << "### Class not in database! ###" << endl;
            std::cout << "###    Aborting Request    ###" <<  endl;
            requestSMenu();
            return;
        }

        pretended.push_back(cpu1);
        actual.push_back(cpu2);
        std::cout << endl;
        std::cout << "Type [Done] to submit request." << endl;
    }
    if (pretended.empty() || actual.empty()) {
        std::cout << "###   Empty Request! Aborting...  ###" << endl;
        requestSMenu();
        return;
    }
    Request r = Request(pretended, actual, studentCode, type);
    schedule_manager.saveRequest(r);
    std::cout << "Request submitted for approval" << endl;
    mainMenu();
}

void Menu::studentScheduleMenu() {
    int studentCode;
    std::cout << endl;
    std::cout << "--- Display a student's schedule --- " << endl;
    std:: cout << "[1] Go back to Display Menu" << endl;
    std::cout << "Type student code:";
    std::cin >> studentCode;
    if(!std::cin.good()) {
        std::cin.clear();
        std::cin.ignore(123, '\n');
        std::cout << "### [Warning] Please type a valid studentCode. Ex: 202000000 ###" << endl;
    }
    if (studentCode == 1) { // Exit code
        displayMenu();
    }

    if (schedule_manager.getStudent(studentCode).get_studentCode() == 0) { // Can't find student
        std::cout << "Student not in database!";
        studentScheduleMenu();
    }
    schedule_manager.printStudentSchedule(studentCode);
    mainMenu();
}

void Menu::classScheduleMenu() {
    std::cout << endl;
    std::string ucCode;
    std::string classCode;
    std::cout << "--- Display a class' schedule ---" << endl;
    std::cout << "[1] Go back to Display Menu" << endl;
    std::cout << "Type ucCode: ";
    std::cin >> ucCode;
    if (ucCode == std::to_string(1)) { // Exit code
        std::cout << endl;
        displayMenu();
        return;
    }

    if (!std::cin.good()) {
        std::cin.clear();
        std::cin.ignore(123, '\n');
        std::cout << "### [Warning] Please type a valid input. Ex: ucCode -> L.EIC001 classCode -> 1LEIC01 ###" << endl;
    }

    std::cout << "Type classCode: ";
    std::cin >> classCode;
    if (classCode == std::to_string(1)) { // Exit code
        std::cout << endl;
        displayMenu();
        return;
    }

    if (!std::cin.good()) {
        std::cin.clear();
        std::cin.ignore(123, '\n');
        std::cout << "### [Warning] Please type a valid input. Ex: ucCode -> L.EIC001 classCode -> 1LEIC01 ###" << endl;
    }
    Classes_per_uc cpu = Classes_per_uc(ucCode, classCode);
    // Can't find class
    if (schedule_manager.getClass(cpu).getUcCode() == "null" || schedule_manager.getClass(cpu).getClassCode() == "null") {
        std::cout << "### Class not in database! ###" << '\n' << endl;
        classScheduleMenu();
        return;
    }
    std::cout << '\n';
    schedule_manager.printClassSchedule(cpu);
    std::cout << endl;
    std::cout << endl;
    mainMenu();
}

void Menu::occupationMenu() {
    std::cout << endl;
    std::cout << "---- Occupation Display Menu ----" << endl;
    std::cout << "[1] Go back Display Menu" << endl;
    std::cout << "[2] Class" << endl;
    std::cout << "[3] UC" << endl;
    std::cout << "[4] Year" << endl;
    int choice;
    std::cout << "Enter your choice:";
    std::cin >> choice;
    if (!std::cin.good()) {
        std::cin.clear();
        std::cin.ignore(123, '\n');
        std::cout << "### [Warning] Please enter a valid option! ###";
        occupationMenu();
    }

    switch(choice) {
        case 1: displayMenu(); break;
        case 2: sortClassMenu(); break;
        case 3: sortUcMenu(); break;
        case 4:
                schedule_manager.printStudentsPerYearOccupation();
                mainMenu();
                break;
        default: std::cout << "### Please type a number from the list ###";
    }
}

void Menu::sortClassMenu() {
    std::cout << endl;
    std::cout << "---  Choose a sorting method ---" << endl;
    std::cout << "[1] Go back Occupation Menu" << endl;
    std::cout << "[2] Sort by UC" << endl;
    std::cout << "[3] Sort in ascending order" << endl;
    std::cout << "[4] Sort in descending order" << endl;
    int choice;
    std::cout << "Enter your choice:";
    std::cin >> choice;
    if (!std::cin.good()) {
        std::cin.clear();
        std::cin.ignore(123, '\n');
        std::cout << "### [Warning] Please enter a valid option! ###";
        mainMenu();
    }

    switch(choice){
        case 1: occupationMenu(); break;
        case 2: schedule_manager.printStudentsPerClassOccupation(ScheduleManager::UCAscending); mainMenu(); break;
        case 3: schedule_manager.printStudentsPerClassOccupation(ScheduleManager::UCAscendingNumberStudents); mainMenu(); break;
        case 4: schedule_manager.printStudentsPerClassOccupation(ScheduleManager::UCDescendingNumberStudents); mainMenu(); break;
    }
}

void Menu::sortUcMenu() {
    std::cout << endl;
    std::cout << " ------   Choose a Sorting Method   ------" << endl;
    std::cout << "[1] Go back Occupation Menu" << endl;
    std::cout << "[2] Sort by occupation ascending order" << endl;
    std::cout << "[3] Sort by occupation descending order" << endl;
    std::cout << "[4] Sort Uc's by ascending order" << endl;
    std::cout << "[5] Sort Uc's descending order" << endl;
    int choice;
    std::cout << "Enter your choice:";
    std::cin >> choice;
    if (!std::cin.good()) {
        std::cin.clear();
        std::cin.ignore(123, '\n');
        std::cout << "### [Warning] Please enter a valid option! ###";
        sortUcMenu();
    }

    switch (choice) {
        case 1:
            occupationMenu();
            break;
        case 2:
            schedule_manager.printStudentsPerUcOccupation(ScheduleManager::UCAscendingNumberStudents);
            mainMenu();
            break;
        case 3:
            schedule_manager.printStudentsPerUcOccupation(ScheduleManager::UCDescendingNumberStudents);
            mainMenu();
            break;
        case 4:
            schedule_manager.printStudentsPerUcOccupation(ScheduleManager::UCAscending);
            mainMenu();
            break;
        case 5:
            schedule_manager.printStudentsPerUcOccupation(ScheduleManager::UCDescending);
            mainMenu();
            break;
        default:
            sortUcMenu();
            break;
    }
}

void Menu::studentDisplayMenu() {
    std::cout << endl;
    std::cout << "### Choose the group of students to display ###" << endl;
    std::cout << "[1] Go back Display Menu" << endl;
    std::cout << "[2] Class" << endl;
    std::cout << "[3] UC" << endl;
    std::cout << "[4] Year" << endl;
    int choice;
    std::cout << "Enter your choice:";
    std::cin >> choice;
    if (!std::cin.good()) {
        std::cin.clear();
        std::cin.ignore(123, '\n');
        std::cout << "### [Warning] Please enter a valid option! ###";
        studentDisplayMenu();
    }
    switch(choice) {
        case 1: displayMenu();
                break;
        case 2: studentsClassMenu();
                break;
        case 3: studentsUcMenu();
                break;
        case 4: studentsYearMenu();
                break;
        default:std::cout <<  "### [Warning] Please enter a valid option! ###";
                studentDisplayMenu();
                break;
    }
}

void Menu::studentsClassMenu() {
    std::cout << endl;
    std::cout << " --- Choose class to display --- " << endl;
    std::string ucCode;
    std::string classCode;
    std::cout << "[1] Go back to Display Menu" << endl;
    std::cout << "Type ucCode: ";
    std::cin >> ucCode;

    if (!std::cin.good()) {
        std::cin.clear();
        std::cin.ignore(123, '\n');
        std::cout << "### [Warning] Please type a valid input. Ex: ucCode -> L.EIC001 classCode -> 1LEIC01 ###" << endl;
        studentsClassMenu();
        return;
    }

    if (ucCode == std::to_string(1)) { // Exit code
        std::cout << endl;
        displayMenu();
        return;
    }
    std::cout << "Type classCode: ";
    std::cin >> classCode;
    if (classCode == std::to_string(1)) { // Exit code
        std::cout << endl;
        displayMenu();
        return;
    }

    Classes_per_uc cpu = Classes_per_uc(ucCode, classCode);
    // Can't find class
    if (schedule_manager.getClass(cpu).getUcCode() == "null" || schedule_manager.getClass(cpu).getClassCode() == "null") {
        std::cout << "### Class not in database! ###" << '\n' << endl;
        studentsClassMenu();
        return;
    }
    schedule_manager.printStudentsPerClass(cpu);
    mainMenu();
}

void Menu::studentsUcMenu() {
    std::cout << endl;
    std::cout << " ----  Choose UC to display ----" << endl;
    std::string ucCode;
    std::string classCode;
    std::cout << "[1] Go back to Display Menu" << endl;
    std::cout << "Type ucCode: ";
    std::cin >> ucCode;
    if (ucCode == std::to_string(1)) { // Exit code
        std::cout << endl;
        displayMenu();
        return;
    }
    std::cout << "Type classCode: ";
    std::cin >> classCode;
    if (classCode == std::to_string(1)) { // Exit code
        std::cout << endl;
        displayMenu();
        return;
    }

    if (!std::cin.good()) {
        std::cin.clear();
        std::cin.ignore(123, '\n');
        std::cout << "### [Warning] Please type a valid input. Ex: ucCode -> L.EIC001 classCode -> 1LEIC01 ###" << endl;
        studentsUcMenu();
        return;
    }
    Classes_per_uc cpu = Classes_per_uc(ucCode, classCode);
    // Can't find class
    if (schedule_manager.getClass(cpu).getUcCode() == "null" || schedule_manager.getClass(cpu).getClassCode() == "null") {
        std::cout << "### Class not in database! ###" << '\n' << endl;
        studentsUcMenu();
        return;
    }
    schedule_manager.printStudentsPerUc(cpu);
    mainMenu();
}

void Menu::studentsYearMenu() {
    int choice;
    std::cout << " ---- Year's Student Display Menu ----" << endl;
    std::cout << "[1] Go back to Display Menu" << endl;
    std::cout << "[2] Year 1 students" << endl;
    std::cout << "[3] Year 2 students" << endl;
    std::cout << "[4] Year 3 students" << endl;
    std::cin >> choice;
    if (!std::cin.good()) {
        std::cin.clear();
        std::cin.ignore(123, '\n');
        std::cout << "### [Warning] Please choose from on of the options ###" << endl;
        studentsYearMenu();
        return;
    }
    switch (choice) {
        case 1 : displayMenu();
                 break;
        case 2 : schedule_manager.printStudentsPerYear(1); mainMenu(); break;
        case 3 : schedule_manager.printStudentsPerYear(2); mainMenu(); break;
        case 4 : schedule_manager.printStudentsPerYear(3); mainMenu(); break;
        default: std::cout << "### [Warning] Please choose from on of the options ###" << endl; studentsYearMenu(); break;
    }
}