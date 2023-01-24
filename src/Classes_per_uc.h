/**
 * @file Classes_per_uc.h
 */
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
using namespace std;

#ifndef PROJETO_CLASSES_PER_UC_H
#define PROJETO_CLASSES_PER_UC_H

/**
 * @brief a class to create a new type of variable that olds UcCodes and ClassCodes
 */
class Classes_per_uc{
private:
    /// @brief a string that represents the Uc Code
    std::string ucCode_;
    /// @brief a string that represents the Class Code
    std::string classCode_;

public:
    //Getters
    /// @brief gets the Uc Code, complexity O(1)
    std::string const get_ucCode();
    /// @brief gets the Class Code, complexity O(1)
    std::string const get_classCode();

    //Constructor
    ///@brief constructor for the classes per uc class
    Classes_per_uc(std::string ucCode, std::string classCode);

    //Methods
    /**
     * @brief operator== overload to see when a class is equal to another, complexity O(1)
     * @param s
     * @return true if the class that we are comparing is equal to s
     */
    bool operator== (const Classes_per_uc& s) const {return (s.ucCode_ == ucCode_ && s.classCode_ == classCode_);}

    /**
     * @brief read the file classes_per_uc.csv, complexity O(n)
     * @param filename
     * @return a list with all the Classes_per_uc that exist in classes_per_uc.csv
     */
    static list<Classes_per_uc> Read(const std::string& filename);

    /**
     * @brief print a class per uc type object (used only for tests), complexity O(1)
     */
    void print();

};
#endif
