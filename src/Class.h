/**
 * @file Class.h
 */

#include <string>
#include <iostream>
#include <vector>
#include <list>
#include "Slot.h"

#ifndef CLASSE
#define CLASSE

/** @brief a class to store a class and its information */
class Class {
private:
    /// @brief a string that represents the Class Code
    std::string classCode_;
    /// @brief a string that represents the Uc Code
    std::string ucCode_;
    /// @brief a list of Slots
    std::list<Slot> classSchedule_;

public:
    /// @brief gets the Class Code, complexity O(1)
    std::string const getClassCode();
    /// @brief gets the Uc Code, complexity O(1)
    std::string const getUcCode();
    /// @brief gets a list of the Class Schedule, complexity O(1)
    std::list<Slot> const getClassSchedule();

    /**
     * @brief default constructor for Class,
     * classCode = "null", ucCode = "null", classSchedule = {}
     */
    Class();
    /// @brief constructor for Class
    Class(std::string classCode, std::string ucCode, std::list<Slot> classSchedule);

    //Methods
    /**
     * @brief prints the content of a Class (used only for testing), complexity O(n)
     */
    void print();

    /**
     * @brief a Class only has one TP class per week, and this function gets it, complexity O(2) = O(1)
     * @return the Slot of a Class that has type TP (Theoretical Practical)
     */
    Slot getTP();

    /**
     * @brief reads the file classes.csv with help of the method Slot::readSlot, complexity O(n+2) = O(n)
     * @param filename
     * @return a vector with all the information in the file classes.csv
     */
    static std::vector<Class> Read(const std::string& filename);
};

#endif
