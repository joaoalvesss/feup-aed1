#include "Slot.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

//Constructor
Slot::Slot(std::string weekDay, float startHour, float duration, std::string type) : weekDay_(weekDay), startHour_(startHour), duration_(duration), type_(type){}

//Getters
std::string const Slot::getWeekDay() { return weekDay_; }
float const Slot::getStartHour() { return startHour_; }
float const Slot::getDuration() { return duration_; }
std::string const Slot::getType() { return type_; }

//Methods
std::list<Slot> Slot::readSlot(const std::string& filename, std::string classCode, std::string ucCode){  //ver se passamos classes_per_uc em vez de classCode e UcCode
    std::ifstream file(filename);
    std::string line;
    line = "";
    std::list<Slot> result;

    getline(file,line);

    while (getline(file, line)) {

        std::istringstream inputString(line);
        std::string ucC, classC;
        getline(inputString, classC, ',');
        getline(inputString, ucC, ',');
        if (ucC == ucCode && classC == classCode) {
            std::string weekDay, startHour, duration, type;

            getline(inputString, weekDay, ',');
            getline(inputString, startHour, ',');
            getline(inputString, duration, ',');
            getline(inputString, type, ',');
            Slot object(weekDay, std::stof(startHour), std::stof(duration), type);
            result.push_back(object);
            line = "";
        }
    }
    return result;

}



void Slot::print(){
    std::cout << weekDay_ << "," << startHour_ << "," << duration_ << "," << type_ << std::endl;
}