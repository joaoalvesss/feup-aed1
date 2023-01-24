/**
 * @file ScheduleManager.h
 */

#include "Student.h"
#include "Request.h"
#include "Class.h"
#include "Classes_per_uc.h"
#include "Slot.h"
#include <set>
#include <queue>
#include <map>
#include <functional>
#include <iomanip>
#include <fstream>

#ifndef PROJETO_SCHEDULEMANAGER_H
#define PROJETO_SCHEDULEMANAGER_H

/**
 * @brief a class to manage schedules
 */
class ScheduleManager
{
private:
    /// @brief  a set of students
    std::set<Student> students_;
    /// @brief a vector of all the schedule
    std::vector<Class> schedule_ ;
    /// @brief a queue to process the requests for changing class
    std::queue<Request> requests_;
    /// @brief a vector with the refused request
    std::vector<Request> refusedRequests_;
    /// @brief a vector with all the classes of every uc
    std::list<Classes_per_uc> allClasses_;
public:
    //Getters
    /// @brief gets the set of students, complexity O(1)
    std::set<Student> getStudents();
    /// @brief gets the vector of classes, complexity O(1)
    std::vector<Class> getSchedule();
    /// @brief gets the queue of requests, complexity O(1)
    std::queue<Request> getRequests();
    /// @brief gets the vector of refused requests, complexity O(1)
    std::vector<Request> getRefusedRequests();
    /// @brief gets the list with all the classes per uc, complexity O(1)
    std::list<Classes_per_uc> getAllClasses();

    //Constructor
    /// @brief the constructor for the schedule manager class
    ScheduleManager();

    //Methods
    /// @brief method to call all the read methods to read all the files
    void const readAllFiles();

    /**
     * @brief get a class in the list of all classes per uc, complexity O(n)
     * @param cpu
     * @return the class for the corresponding class_per_uc
     */
    Class getClass(Classes_per_uc cpu);

    /**
     * @brief gets the corresponding object to a student code, complexity O(n)
     * @param studentCode
     * @return  Student object
     */
    Student getStudent(int studentCode);


    /**
    * @brief comparator function to use to sort, complexity O(1)
    * @param a
    * @param b
    * @return true if a.first is smaller than b.first
    */
    static bool sortPair(const pair<Slot, Classes_per_uc> &a, const pair<Slot, Classes_per_uc> &b);


    /**
     * @brief converts and prints a float into a time stamp, complexity O(1)
     * @param time
     */
    void printHour(float time);

    /**
     * @brief complexity max O(2*6+1=12) = O(1)
     * @param x
     * @return list with the the schedule of a student associated with each UC
     */
     list<pair<Slot, Classes_per_uc>> getStudentSchedule(int studentCode);

    /**
     * @brief prints a student schedule, complexity O(max number of classes that a student can have) = O(1)
     * @brief Weekday1  Type1  StartHour1 -> End  UcCode
     * @param studentCode
     */
    void printStudentSchedule(int studentCode);

    /**
     * @brief complexity O(2) = O(1)
     * @brief prints the schedule of a class in the format:
     * @brief Weekday1  Type1  StartHour1 -> End  UcCode
     */
    void printClassSchedule(Classes_per_uc cpu);



    /**
     * @brief complexity O(n + max number of classes of a student) = O(n)
     * @param cpu
     * @return list of Students in a class
     */
    std::list<Student> studentsPerClass(Classes_per_uc cpu);

    /**
     * @brief complexity O(2n) = O(n)
     * @brief prints the number of students of all classes by certain order defined by the user and passed by the parameter func
     * @param func
     */
    void printStudentsPerClassOccupation(const function<bool(pair <int,Classes_per_uc>, pair<int, Classes_per_uc>)> &func);

    /**
     * @brief complexity O(n + max number of classes of a student) = O(n)
     * @brief prints all student codes and name for any asked Uc
     * @param cpu
     */
    void printStudentsPerClass(Classes_per_uc cpu);



    /**
     * @brief complexity O(n + max number of classes of a student) = O(n)
     * @brief groups all students with at least one class of year_ in a list
     * @param year_
     * @return list of students enrolled on year_
     */
    list<Student> studentsPerYear(int year_);

    /**
     * @brief Complexity = O(n + max number of classes) = O(n)
     * @brief prints the number of students in each of the 3 years in LEIC
     */
    void printStudentsPerYearOccupation();

    /**
     * @brief Complexity = O(n + number of student's classes) = O(n)
     * @brief prints all students that have at least one class in year_
     * @param year_
     */
    void printStudentsPerYear(int year_);



    /**
     * @brief Complexity = O(n + number of classes per student) = O(n)
     * @brief Groups in a list all the students who have at least one class in an UC
     * @param Classes_per_uc whose students to display
     * @return list with all the students on a Class
     */
    list<Student> studentsPerUc(Classes_per_uc cpu);

    /**
     * @brief Complexity = O(n)
     * @param func -> a custom comparator function to sort a list of students
     * @brief prints in the terminal every UC and its number of students
     */
    void printStudentsPerUcOccupation(const function<bool(pair <int,Classes_per_uc>, pair<int, Classes_per_uc>)> &func);

    /**
     * @ brief Complexity = O(n)
     * @param cpu
     * @brief prints in the terminal a UC and a list of its students
     */
    void printStudentsPerUc(Classes_per_uc cpu);



    ///@brief custom comparator function to sort a list of pairs<int, Classes_per_uc> from the uc with less students to the one with more
    static bool UCAscendingNumberStudents(pair<int, Classes_per_uc> p1, pair<int, Classes_per_uc> p2);
    ///@brief custom comparator function to sort a list of pairs<int, Classes_per_uc> from the uc with more students to the one with less
    static bool UCDescendingNumberStudents(pair<int, Classes_per_uc> p1, pair<int, Classes_per_uc> p2);
    ///@brief custom comparator function to sort a list of pairs<int, Classes_per_uc> from the first UC to the last
    static bool UCAscending(pair<int, Classes_per_uc> p1, pair<int, Classes_per_uc> p2);
    ///@brief custom comparator function to sort a list of pairs<int, Classes_per_uc> from the last UC to the first
    static bool UCDescending(pair<int, Classes_per_uc> p1, pair<int, Classes_per_uc> p2);
    ///@brief custom comparator function to sort a list of pairs<int, Classes_per_uc> from the first to last Class
    static bool ClassAscending(pair<int, Classes_per_uc> p1, pair<int, Classes_per_uc> p2);

    //ESTAS 4 É PARA DAR SORT A UMA LISTA DE STUDENTS ->  FAZER SE HOUVER TEMPO
    static bool StudentAscendingStudentCode(Student s1, Student s2);
    static bool StudentDescendingStudentCode(Student s1, Student s2);
    static bool StudentAscendingStudentName(Student s1, Student s2);
    static bool StudentDescendingStudentName(Student s1, Student s2);

    /**
     * @brief Complextiy O(1)
     * @brief saves a single request into a queue
     * @param r
     */
    void const saveRequest(Request r);

    /**
     * @brief Complexity = O(n)
     * @brief a method that returns a list of pairs of the size of a class within a uc and its classes_per_uc,
     * @brief note: actual and pretended must have the same ucCode
     * @brief sets min to the minimum value of students that a class has within the uc,
     * @brief sets max to the maximum value of students that a class has within the uc,
     * @brief sets sizeOfActual to the number of students that the class corresponding to Acual's classCode has
     * @brief sets sizeOfPretended to the number of students that the class corresponding to Pretended's classCode has
     * @brief -> We did this so we don't have to iterate again in the createBalance method <-
     * @param actual
     * @param min
     * @param max
     * @param pretended
     * @param sizeOfActual
     * @param sizeOfPretended
     * @return a list of pairs of the size of a class within a uc and its classes_per_uc
     */
    list<pair<int, Classes_per_uc>> studentsPerClassOfUc(Classes_per_uc actual, int & min, int & max, Classes_per_uc pretended, int & sizeOfActual, int & sizeOfPretended);

    /**
     * @brief Complexity = O(1)
     * @param ucCode
     * @param pretendedClass
     * @return true if the change of the classes might lead the student's schedule to have overlapped classes
     * and false if not
     */
    bool classOverlap(Classes_per_uc c1, Classes_per_uc c2);

    /**
     * @brief Complexity = O(n)
     * @brief this function processes (or not) all the existing requests saved into saveRequest
     */
    void const processRequests();

    /**
     * @brief Complexity = O(n)
     * @brief returns the number of classes in an uc
     * @param cpu
     * @return number of classes in an uc
     */
    int classesOfUc(Classes_per_uc cpu);

    /**
     * @brief Complexity O(n)
     * @param r
     * @return TRUE if there is a class overlap in the student schedule and FALSE if not
     */
    bool analyseRequest(Request r);

    /**
     * @brief Complexity = O(n²)
     * @brief Check if a request creates balance between the classes of a Uc.
     * @brief This is our approach to balance:
     * @brief | diff < 4 | -> is balanced
     * @brief If the difference (diff = max - min) between the class that as more students and the class that has less
     * @brief is less then 4, then all request are allowed unless they involve edges (classes with max or min)
     * @brief this is what was required in the project statement.
     * @brief | diff >= 4| -> is not balanced
     * @brief If the difference (diff = max - min) between the class that as more students and the class that has less
     * @brief is more or equals than 4, then the request is only allowed if the number of students of the classes involved
     * @brief are closer to the ideal number of students (ideal = total number of uc's students / nº of classes of the uc)
     * @param r
     * @return TRUE if a request creates balance between the classes and FALSE if not
     */
    bool createsBalance(Request r);

    /**
     * @brief Complexity = O(n + log n)
     * @brief adds a class to a student
     * @param student
     * @param cpu
     */
    void addClassStudent(int student, const Classes_per_uc &cpu);

    /**
     * @brief Complexity = O(n + log n)
     * @brief removes a class from a student
     * @param student
     * @param cpu
     */
    void removeClassStudent(int student, const Classes_per_uc &cpu);

    /**
     * @brief Complexity = O(n)
     * @brief Writes on a csv file the students_ list
     */
    void writeStudentsFile();
};


#endif //PROJETO_SCHEDULEMANAGER_H
