/**
 * @file Slot.h
 */

#include <string>
#include <list>
#include <map>

#ifndef PROJETO_SLOT_H
#define PROJETO_SLOT_H

/**
 * @brief a class to represent when a class happens and its type
 */
class Slot
{
private:
    /// @brief a string that represents the weekday of a class
    std::string weekDay_;
    /// @brief a float that represents the start hour of a class
    float startHour_;
    /// @brief a float that represents the duration of a class
    float duration_;
    /// @brief a string that represents the type of a class
    std::string type_;

public:
    //Constructor
    ///@brief the constructor for the slot class
    Slot(std::string weekDay, float startHour, float duration, std::string type);

    //Getters
    /// @brief gets the weekday of a class, complexity O(1)
    std::string const getWeekDay();
    /// @brief gets the start hour of a class, complexity O(1)
    float const getStartHour();
    /// @brief gets the duration of a class, complexity O(1)
    float const getDuration();
    /// @brief gets the type of a class, complexity O(1)
    std::string const getType();

    //Methods
    /**
     * @brief read helper of the method Read presented in Class, complexity O(2) = O(1)
     * @param filename
     * @param classCode
     * @param ucCode
     * @return a list of Slot that has all the schedule and type of all the class that an Uc has
     */
    static std::list<Slot> readSlot(const std::string& filename, std::string classCode, std::string ucCode);

    /**
     * @brief print the content of a Slot, complexity O(1)
     */
    void print();

    /**
     * @brief operator< overload to compare Slots by when a slot happens first than another, complexity O(1)
     * @param s
     * @return true if the slot that we want to compare happens first than the other
     */
    bool operator< (const Slot s) const {
        std::map<std::string,int> days = {{"Monday" , 2}, {"Tuesday", 3}, {"Wednesday", 4}, {"Thursday", 5}, {"Friday",6}};
        return days[weekDay_] < days[s.weekDay_] ||
                (weekDay_ == s.weekDay_ && startHour_ < s.startHour_);
    }
};

#endif //PROJETO_SLOT_H
