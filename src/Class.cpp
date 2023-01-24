#include "Class.h"
#include <fstream>
#include <sstream>

using namespace std;

std::string const Class::getClassCode(){return classCode_;}
std::string const Class::getUcCode() {return ucCode_;}
std::list<Slot> const Class::getClassSchedule() { return classSchedule_; }

Class::Class() : classCode_("null"), ucCode_("null"), classSchedule_({}) {;}
Class::Class(std::string classCode, std::string ucCode, list<Slot> classSchedule) : classCode_(classCode), ucCode_(ucCode), classSchedule_(classSchedule) {;}

std::vector<Class> Class::Read(const std::string &filename) {

    ifstream file(filename);
    string line;
    getline(file,line);
    line = "";
    vector<Class> result;
    while (getline(file, line)) {

        stringstream inputString(line);

        std::string classCode, ucCode, weekDay, startHour, duration, type;


        getline(inputString, classCode, ',');
        getline(inputString, ucCode, ',');
        getline(inputString, weekDay, ',');
        getline(inputString, startHour, ',');
        getline(inputString, duration, ',');
        getline(inputString, type, ',');
        list<Slot> classSchedule = Slot::readSlot(filename, classCode, ucCode);
        Class object(classCode, ucCode, classSchedule);
        result.push_back(object);
        line = "";
    }

    return result;
}

Slot Class::getTP() {
    Slot result = Slot("Monday", 0, 0, "TP");
    for (Slot s : classSchedule_) {
        if (s.getType() == "TP")
            return s;
    }
    return result;
}

void Class::print() {   
    std:: cout << classCode_ << ',' << ucCode_ << ',';
    cout << '\n';
    for (Slot s : classSchedule_){
        cout << '\t';
        s.print();}
}
