/**
 * @file Request.h
 */

#include <string>
#include "Classes_per_uc.h"
#include "Student.h"
#include <list>

#ifndef PROJETO_REQUEST_H
#define PROJETO_REQUEST_H

/**
 * @brief a class to handle schedule changing requests
 */
class Request
        {
private:
    /**
     * @brief a list of classes that the student wants to go to
     * @brief |if type_ == 'S'| (switch)
     * @brief this list should be the same size as the actualClass_ list
     * @brief this will be checked in the menu
     * @brief the actual class for the corresponding pretended class is the one with the same index in the actualClass_ list
     * @brief |if type_ == 'R'| (remove)
     * @brief this list will be empty
     */
    list<Classes_per_uc> pretendedClass_; // turma pretendida para mudar

    /**
     * @brief a list of classes that the student pretends to leave from
     * @brief |if type_ == 'S'| (switch)
     * @brief this list should be the same size as the pretendedClass_ list
     * @brief this will be checked in the menu
     * @brief the pretended class for the corresponding actual class is the one with the same index in the pretendedClass_ list
     * @brief |if type_ == 'A'| (add)
     * @brief this list will be empty
     */
    list<Classes_per_uc> actualClass_; // turma atual

    /**
     * @brief type of request
     * 'A' -> add a student to a class
     * 'R' -> remove a student from a class
     * 'S' -> switch classes / groups of classes
     */
    char type_;
    /// @brief the code of the student that made the request
    int studentCode_;
public:
    /// @brief the constructor for the request class
    Request(list<Classes_per_uc> pretendedClass, list<Classes_per_uc> actualClass, int studentCode, char type);
    //Getters
    /// @return the list of classes that the student pretends to change to, complexity O(1)
    list<Classes_per_uc> getPretendedClass();
    /// @return the list of classes that the student pretends to leave from, complexity O(1)
    list<Classes_per_uc> getActualClass();
    /// @return the type of request, complexity O(1)
    char getType();
    /// @return the code of the student that made the request, complexity O(1)
    int getStudentCode();
};

#endif //PROJETO_REQUEST_H