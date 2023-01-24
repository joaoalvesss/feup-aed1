/**
 * @file Student.h
 */
#include <iostream>
#include "Class.h"
#include "Classes_per_uc.h"
#include <string>
#include <list>
#include <set>

#ifndef STUDENT
#define STUDENT

/**
 * @brief a class to represent a student and the class that (s)he has
 */
class Student {
private:
    /// @brief a unique number that represents a student
    int studentCode_;
    /// @brief a string that represents the student name
    std::string studentName_;
    /// @breif a list has all the classes that a student has
    std::list<Classes_per_uc> classes_;
public:
    /// @brief gets the student code, complexity O(1)
    int const get_studentCode();
    /// @brief gets the student name, complexity O(1)
    std::string const get_studentName();
    /// @brief gets the student classes, complexity O(1)
    std::list<Classes_per_uc> const get_classes();

    //Constructors
    /** @brief default constructor with no parameters, creates a student with studentCode = 0, studentName = "null"
     * classes = empty list
     */
    Student();
    /// @brief constructor for student
    Student(int studentCode, std::string studentName, std::list<Classes_per_uc> classes);

    //Methods
    /**
     * @brief operator overload to sort students, complexity O(1)
     * @param s
     * @return true if the student that we are comparing has a lower student code than s
     */
    bool operator< (const Student& s) const {return studentCode_ < s.studentCode_;}

    /**
     * @brief reads students_classes.csv, complexity O(n)
     * @param filename
     * @return a set with all the information about the students in the file passed as parameter
     */
    static std::set<Student> read(const std::string &filename);

    /**
     * @brief print all the information presented in the private parameters of the student (used only for testing), complexity O(n)
     */
    void print();

    /**
     * @brief print all the classes of the student (used only for testing), complexity O(1)
     */
    void studentsPerClassPrint();
};


#endif
