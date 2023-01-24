#include "Student.h"

//Getters
int const Student::get_studentCode(){ return studentCode_;}
std::string const Student::get_studentName() {return studentName_;}
std::list<Classes_per_uc> const Student::get_classes() {return classes_;}

//Constructor
Student::Student() : studentCode_(0), studentName_("null"), classes_({}) {}
Student::Student( int studentCode, std::string studentName, std::list<Classes_per_uc> classes) : studentCode_(studentCode), studentName_(studentName), classes_(classes){;}

//Methods

/**
 *
 * @param filename
 * @return returns a binary search tree with all the students from the file
 */
std::set<Student> Student::read(const std::string &filename){

    ifstream file(filename);
    string line;
    getline(file,line);
    line = "";
    std::set<Student> result;
    list<Classes_per_uc> classes_;
    std::string studentCode,studentName, ucCode, classCode;
    std::string nextStudentCode, nextStudentName, nextUcCode, nextClassCode;

    getline(file, line);
    istringstream input(line);
    getline(input, nextStudentCode, ',');
    getline(input, nextStudentName, ',');
    getline(input, nextUcCode, ',');
    getline(input, nextClassCode, ',');

    while (getline(file, line)) {

        stringstream inputString(line);

        studentCode = nextStudentCode, studentName = nextStudentName, ucCode = nextUcCode, classCode = nextClassCode;


        getline(inputString, nextStudentCode, ',');
        getline(inputString, nextStudentName, ',');
        getline(inputString, nextUcCode, ',');
        getline(inputString, nextClassCode, ',');

        if(studentCode != nextStudentCode) {
            Classes_per_uc cpu = Classes_per_uc(ucCode, classCode);
            classes_.push_back(cpu);
            Student object(stoi(studentCode), studentName, classes_);
            result.insert(object);
            classes_.clear();
        }

        else {
            Classes_per_uc cpu = Classes_per_uc(ucCode, classCode);
            classes_.push_back(cpu);
        }

        line = "";
    }
    Classes_per_uc cpu = Classes_per_uc(nextUcCode, nextClassCode);
    classes_.push_back(cpu);
    Student object(stoi(studentCode), studentName, classes_);
    result.insert(object);

    return result;
}

void Student::print() {
    std::cout << studentCode_ << ',' << studentName_ << '\n';
    for (Classes_per_uc s : classes_){
        cout << '\t';
        cout << s.get_ucCode() << ' ' << s.get_classCode() << endl;}
}

void Student::studentsPerClassPrint() {
    cout << '\t' << studentCode_ << ' ' << studentName_ << '\n';
}