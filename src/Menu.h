/**
 * @file Menu.h
 */

#include <iostream>
#include <algorithm>
#include "ScheduleManager.h"

#ifndef MENU
#define MENU

/**
 * @brief a class to create all the menus
 */
class Menu {
private:
    /// @brief schedule manager object so we can manage what we want in the menus
    ScheduleManager schedule_manager;
public:
    //constructors
    /// @brief constructor for the menu class
    Menu(ScheduleManager &schedule_manager);

    //menus
    /// @brief displays and manages the main menu of the application
    void mainMenu();
    /// @brief displays and manages the display menu of the application
    void displayMenu();
    /// @brief displays and manages the request menu of the application
    void requestTypeMenu();
    /// @brief displays and manages the request menu to remove a student from a class
    void requestRMenu();
    /// @brief displays and manages the request menu to add a student to a new class
    void requestAMenu();
    /// @brief displays and manages the request menu to swap student class(es)
    void requestSMenu();
    ///@brief displays and manages to show a student information
    void studentScheduleMenu();
    ///@brief displays the schedule of a class
    void classScheduleMenu();
    ///@brief displays the options to the occupation of classes, uc's or year
    void occupationMenu();
    ///@brief displays the options to show the occupation of classes
    void sortClassMenu();
    ///@brief displays the options to show the occupation of uc's
    void sortUcMenu();
    ///@brief displays the options to show the students on UC/Class/Year
    void studentDisplayMenu();
    ///@brief displays input options for classCode and UCCode to choose a Class's list of students to display
    void studentsClassMenu();
    ///@brief displays input options for classCode and UCCode to choose a Classes_per_uc list of students to display
    void studentsUcMenu();
    ///@brief displays input options for year to choose a year's list of students to display
    void studentsYearMenu();
};


#endif