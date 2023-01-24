#include "ScheduleManager.h"
#include "Student.h"

//Getters
std::set<Student> ScheduleManager::getStudents() { return students_;}
std::vector<Class> ScheduleManager::getSchedule() { return schedule_;}
std::queue<Request> ScheduleManager::getRequests() { return requests_;}
std::vector<Request> ScheduleManager::getRefusedRequests(){ return refusedRequests_;}
std::list<Classes_per_uc> ScheduleManager::getAllClasses() {return allClasses_;}

//Constructor
ScheduleManager::ScheduleManager() {
    readAllFiles();
}

//Methods
void const ScheduleManager::readAllFiles(){
    students_ = Student::read("../schedule/students_classes.csv");
    schedule_ = Class::Read("../schedule/classes.csv");
    allClasses_ = Classes_per_uc::Read("../schedule/classes_per_uc.csv");
    std::list<Classes_per_uc> allClasses_per_uc = Classes_per_uc::Read("../schedule/classes_per_uc.csv");
}

// -----------------------------------------------------------------------------------------------------
// -------------------------------------- GetClass / GetStudent ----------------------------------------
// -----------------------------------------------------------------------------------------------------


Class ScheduleManager::getClass(Classes_per_uc cpu) {
    for (Class c : schedule_) {
        if (c.getClassCode() == cpu.get_classCode() && c.getUcCode() == cpu.get_ucCode()) {
            return c;
        }
    }
    return Class();
}

Student ScheduleManager::getStudent(int studentCode)  {
    for (Student s : students_) {
        if (s.get_studentCode() == studentCode)
            return s;
    }
    return Student();
}

// -----------------------------------------------------------------------------------------------------
// ----------------------------------- Student & Class Schedule ----------------------------------------
// -----------------------------------------------------------------------------------------------------


bool ScheduleManager::sortPair(const pair<Slot, Classes_per_uc> &a, const pair<Slot, Classes_per_uc> &b){
    return (a.first < b.first);
}

void ScheduleManager::printHour(float time) {
    int hours = time / 1;
    time -= hours;
    int minutes = time * 60;
    std::cout << std::fixed << setw(2) << setfill('0') << hours << 'h'
              << setw(2) << setfill('0') << minutes;
}

list<pair<Slot, Classes_per_uc>> ScheduleManager::getStudentSchedule(int studentCode) {
    Student x = getStudent(studentCode);
    list<pair<Slot, Classes_per_uc>> result;
    list<Classes_per_uc> studentClasses_per_uc = x.get_classes();
    for (Classes_per_uc &cpu: studentClasses_per_uc){ // max 6 complexity
        Class c = getClass(cpu);
        for (Slot s: c.getClassSchedule()){ // max 2 complexity
            result.push_back({s,cpu});
        }
    }
    result.sort(sortPair);
    return result;
}

void ScheduleManager::printStudentSchedule(int studentCode) {
    Student s = getStudent(studentCode);
    list<pair<Slot,Classes_per_uc>> schedule = getStudentSchedule(studentCode);
    std::cout << "Schedule for " << s.get_studentName() << endl;
    std::cout << "Student Code: " << s.get_studentCode() << '\n' << endl;

    for ( pair<Slot, Classes_per_uc> slot: schedule) { // max number of classes of a student
        Slot sl = slot.first;
        float endHour = sl.getStartHour() + sl.getDuration();
        std::cout <<'\t';
        std:: cout << sl.getWeekDay() << ' ' << sl.getType() << ' ';
        printHour(sl.getStartHour());
        std::cout << " -> ";
        printHour(endHour);
        std::cout << "   \t" << slot.second.get_ucCode() << " | " << slot.second.get_classCode() << endl;
    }
}

void ScheduleManager::printClassSchedule(Classes_per_uc cpu) {
    Class c = getClass(cpu);
    list<Slot> help = c.getClassSchedule();
    help.sort();
    std::cout << "Uc Code: " << cpu.get_ucCode() << "  " << "Class Code: " << cpu.get_classCode() << endl << endl;
    for (Slot sl: help){
        float endHour = sl.getStartHour() + sl.getDuration();
        std::cout <<'\t';
        std:: cout << sl.getWeekDay() << ' ' << sl.getType() << ' ';
        printHour(sl.getStartHour());
        std::cout << " -> ";
        printHour(endHour);
        std::cout << endl;
    }
}



// -----------------------------------------------------------------------------------------------------
// -------------------------------------- Students Per Class -------------------------------------------
// -----------------------------------------------------------------------------------------------------



std::list<Student> ScheduleManager::studentsPerClass(Classes_per_uc cpu) {
    list<Student> result;

    for (Student s : students_){
        for (Classes_per_uc c : s.get_classes()) {
            if(c == cpu){
                result.push_back(s);
            }
        }
    }
    return result;
}

void ScheduleManager::printStudentsPerClassOccupation(const function<bool(pair <int,Classes_per_uc>, pair<int, Classes_per_uc>)> &func) {
    list<pair<int, Classes_per_uc>> helper;
    for (Classes_per_uc c: allClasses_) {
        helper.push_back({studentsPerClass(c).size(), c});
    }
    helper.sort(func);
    std::cout << "  UC       Class     size"  << endl;
    for (pair<int, Classes_per_uc> c: helper) {
        std::cout << c.second.get_ucCode() << " | " << c.second.get_classCode() << " -> "<< c.first << endl;
    }
}

void ScheduleManager::printStudentsPerClass(Classes_per_uc cpu) {
    list<Student> help = studentsPerClass(cpu);
    cout << "Class: " << cpu.get_classCode() << ", Uc: " << cpu.get_ucCode() << endl;
    cout << "Total: " << help.size() << endl;
    for (Student s : help) {
        cout << '\t' << s.get_studentCode() << ' ' << s.get_studentName() << endl;
    }
}


// -----------------------------------------------------------------------------------------------------
// -------------------------------------- Students Per Year  -------------------------------------------
// -----------------------------------------------------------------------------------------------------


std::list<Student> ScheduleManager::studentsPerYear(int year_) {
    list<Student> result;
    for (Student s: students_) {
        list<Classes_per_uc> studentClasses = s.get_classes();
        for (Classes_per_uc cpu: studentClasses) {
            std::string year = cpu.get_classCode();
            std::string comparator = year.substr(0, 1);
            if (comparator == to_string(year_)) {
                result.push_back(s);
                break;
            }

        }
    }
    return result;
}

void ScheduleManager::printStudentsPerYearOccupation(){
    list<Student> year1 = studentsPerYear(1);
    list<Student> year2 = studentsPerYear(2);
    list<Student> year3 = studentsPerYear(3);
    std::cout << endl;
    cout << "First year has " << year1.size() << " students enrolled" << endl;
    cout << "Second year " << year2.size() << " students enrolled" << endl;
    cout << "Third year has " << year3.size() << " students enrolled" << endl;
    cout << endl;
}

void ScheduleManager::printStudentsPerYear(int year_) {
    list <Student> help = studentsPerYear(year_);
    cout << "List of students for year " << year_ << endl;
    cout << "Total: " << help.size() << endl;
    for (Student s : help) {
        cout << ' ' << s.get_studentCode() << ' ' << s.get_studentName() << endl;
    }
}


// -----------------------------------------------------------------------------------------------------
// -------------------------------------- Students Per UC ----------------------------------------------
// -----------------------------------------------------------------------------------------------------



list<Student> ScheduleManager::studentsPerUc(Classes_per_uc cpu) {
    list<Student> result;
    for (Student s : students_){
        for (Classes_per_uc c : s.get_classes()) {
            if(c.get_ucCode() == cpu.get_ucCode())
                result.push_back(s);
        }
    }
    return result;
}

void ScheduleManager::printStudentsPerUcOccupation (const function<bool(pair <int,Classes_per_uc>, pair<int, Classes_per_uc>)> &func) {
    string last;
    list<pair<int , Classes_per_uc>> helper; // pair <UCsize, UC>
    cout << "  UC       Size" << endl;
    for(Classes_per_uc cpu : allClasses_) {
        if (cpu.get_ucCode() != last) {
            list<Student> help = studentsPerUc(cpu);
            last = cpu.get_ucCode();
            helper.push_back({help.size(), cpu});
        }
    }
    helper.sort(func);
    for (pair<int, Classes_per_uc> pair : helper) {
        cout << pair.second.get_ucCode() << " -> " <<  pair.first << endl;
    }
}

void ScheduleManager::printStudentsPerUc(Classes_per_uc cpu) {
    list<Student> help = studentsPerUc(cpu);
    std::cout << "Uc: " << cpu.get_ucCode() << " has " << help.size() << " students" << endl;

    for (Student s : help) {
        std::cout << '\t' << s.get_studentCode() << ' ' << s.get_studentName() << endl;
    }
}

// -----------------------------------------------------------------------------------------------------
// ------------------------------------ Comparators ----------------------------------------------------
// -----------------------------------------------------------------------------------------------------

bool ScheduleManager::UCAscendingNumberStudents(pair<int, Classes_per_uc> p1, pair<int, Classes_per_uc> p2) {
    return p1.first < p2.first;
}

bool ScheduleManager::UCDescendingNumberStudents(pair<int, Classes_per_uc> p1, pair<int, Classes_per_uc> p2) {
    return p1.first > p2.first;
}

bool ScheduleManager::UCAscending(pair<int, Classes_per_uc> p1, pair<int, Classes_per_uc> p2) {
    return p1.second.get_ucCode() < p2.second.get_ucCode();
}

bool ScheduleManager::UCDescending(pair<int, Classes_per_uc> p1, pair<int, Classes_per_uc> p2) {
    return p1.second.get_ucCode() > p2.second.get_ucCode();
}

bool ScheduleManager::ClassAscending(pair<int, Classes_per_uc> p1, pair<int, Classes_per_uc> p2) {
    return p1.second.get_ucCode() < p2.second.get_ucCode() ||
            (p1.second.get_ucCode() == p2.second.get_ucCode() && p1.second.get_classCode() < p2.second.get_classCode());
}


// -----------------------------------------------------------------------------------------------------
// -------------------------------------- Requests -----------------------------------------------------
// -----------------------------------------------------------------------------------------------------



void const ScheduleManager::saveRequest(Request r){
     requests_.push(r);
 }

list<pair<int, Classes_per_uc>> ScheduleManager::studentsPerClassOfUc(Classes_per_uc actual, int & min, int & max, Classes_per_uc pretended, int & sizeOfActual, int & sizeOfPretended) {
    list<pair<int, Classes_per_uc>> result;
    for (Classes_per_uc c: allClasses_) {
        if (c.get_ucCode() == actual.get_ucCode()) {
            int stud = studentsPerClass(c).size();
            if (stud > max) max = stud;
            else if (stud <= min) min = stud;
            result.push_back({stud, c});
            if (c.get_classCode() == actual.get_classCode()) sizeOfActual = stud;
            if (c.get_classCode() == pretended.get_classCode()) sizeOfPretended = stud;
        }
    }
    return result;
}

bool ScheduleManager::classOverlap(Classes_per_uc c1, Classes_per_uc c2) {
    Class C1 = getClass(c1);
    Class C2 = getClass(c2);
    Slot C1TP = C1.getTP();
    Slot C2TP = C2.getTP();
    float endHourC1 = C1TP.getStartHour() + C1TP.getDuration();
    float endHourC2 = C2TP.getStartHour() + C2TP.getDuration();
    return (C1TP.getWeekDay() == C2TP.getWeekDay() &&
            (C1TP.getStartHour() < endHourC2 &&  C2TP.getStartHour() < endHourC1));
}

void const ScheduleManager::processRequests() {
    while(!(requests_.empty())){
        Request cur = requests_.front();
        if (cur.getType() == 'R') {
            for (Classes_per_uc actual : cur.getActualClass())
            removeClassStudent(cur.getStudentCode(), actual);
        }

        else if (cur.getType() == 'A') {
            if(createsBalance(cur) && analyseRequest(cur)) {
                for (Classes_per_uc pretended: cur.getPretendedClass())
                    addClassStudent(cur.getStudentCode(), pretended);
            }
            else
                refusedRequests_.push_back(cur);
        }

        else if (cur.getType() == 'S') {
            if(createsBalance(cur) && analyseRequest(cur)) {

                auto it1 = cur.getActualClass().begin();
                auto it2 = cur.getPretendedClass().begin();
                for (int i = 0; i < cur.getActualClass().size(); i++) {
                    Classes_per_uc actual = *it1;
                    Classes_per_uc pretended = *it2;
                    addClassStudent(cur.getStudentCode(), pretended);
                    removeClassStudent(cur.getStudentCode(), actual);
                }
            }
            else
                refusedRequests_.push_back(cur);
        }
        requests_.pop();
    }
    writeStudentsFile();
}

int ScheduleManager::classesOfUc(Classes_per_uc cpu) {
    int count = 0;
    for (Classes_per_uc c : allClasses_) {
        if (c.get_ucCode() == cpu.get_ucCode())
            count++;
    }
    return count;
}

bool ScheduleManager::analyseRequest(Request r) {
    Student student = getStudent(r.getStudentCode());
    list<Classes_per_uc> actualClassList = r.getActualClass();
    list<Classes_per_uc> pretendedClassList = r.getPretendedClass();

    if (r.getType() == 'S') {
        list<Classes_per_uc> studentClassesMinusActualStudentList;
        // studentClassesMinusActualStudentList = studentClasses - actualClasses
        for (Classes_per_uc actualCpu: actualClassList) {
            for (Classes_per_uc studentCpu: student.get_classes()) {
                if (!(actualCpu == studentCpu)) studentClassesMinusActualStudentList.push_back(studentCpu);
            }
        }
        // index serve para correr as listas pelos pares
        for (Classes_per_uc pretendedCpu : pretendedClassList) {
            for (Classes_per_uc studentCpu : studentClassesMinusActualStudentList) {
                if (classOverlap(pretendedCpu, studentCpu)) return false;
            }
        }
        return true;
    }

    if (r.getType() == 'A') {
        for (Classes_per_uc pretendedCpu : pretendedClassList) {
            for (Classes_per_uc studentCpu : student.get_classes()) {
                if (classOverlap(pretendedCpu, studentCpu))
                    return false;
            }
        }
        return true;
    }
    if (r.getType() == 'R') return true;
    return false;
}

bool ScheduleManager::createsBalance(Request r) {
    // diff = max - min
    // se diff < 4 (em equilibrio)
    // todas as adições são permitidas que não envolvam pontas
    // se diff >= 4 (em desiquilibrio)
    // ideal = Alunos Uc / nTurmas
    // só permite se a turma na qual o aluno entra se aproxima desse número
    list<Classes_per_uc> actualClassList = r.getActualClass();
    list<Classes_per_uc> pretendedClassList = r.getPretendedClass();

    if (r.getType() == 'S') {
        int diff, total, ideal;
        int actualSize, pretendedSize;
        auto itActualCpu = actualClassList.begin();
        auto itPretendedCpu = pretendedClassList.begin();
        for (int i = 0; i < actualClassList.size(); i++) {
            int min = INT32_MAX, max = INT32_MIN;
            Classes_per_uc actualCpu = *itActualCpu;
            Classes_per_uc pretendedCpu = *itPretendedCpu;
            list<pair<int, Classes_per_uc>> helper = studentsPerClassOfUc(actualCpu, min, max, pretendedCpu, actualSize,
                                                                          pretendedSize);
            diff = max - min;
            total = studentsPerUc(actualCpu).size();
            ideal = total / classesOfUc(actualCpu);
            if (diff < 4) {
                if (actualSize == min || pretendedSize == max)
                    return false;
            } else {
                if (actualSize <= ideal || pretendedSize >= ideal) // mudei para e igual (rama)
                    return false;
            }
            itActualCpu++;
            itPretendedCpu++;
        }
        return true;
    }

    if (r.getType() == 'A') {
        int diff, total, ideal;
        int pretendedSize;
        auto itPretendedCpu = pretendedClassList.begin();
        for (int i = 0; i < actualClassList.size(); i++) {
            int min = INT32_MAX, max = INT32_MIN;
            Classes_per_uc pretendedCpu = *itPretendedCpu;
            list<pair<int, Classes_per_uc>> helper = studentsPerClassOfUc(pretendedCpu, min, max, pretendedCpu, pretendedSize,
                                                                          pretendedSize);
            diff = max - min;
            total = studentsPerUc(pretendedCpu).size();
            ideal = total / classesOfUc(pretendedCpu);
            if (diff == 3) {
                if (pretendedSize == max)
                    return false;
            }
            else if (diff >= 4) {
                if (pretendedSize > ideal)
                    return false;
            }
            itPretendedCpu++;
        }
        return true;
    }
    return true;
}



void ScheduleManager::addClassStudent(int student, const Classes_per_uc &cpu) {
    Student s1 = getStudent(student);
    std::string name = s1.get_studentName();
    list<Classes_per_uc> studentClasses = s1.get_classes();
    studentClasses.push_back(cpu);
    students_.erase(s1);
    students_.insert(Student(student, name, studentClasses));
}

void ScheduleManager::removeClassStudent(int student, const Classes_per_uc &cpu){
    Student s1 = getStudent(student);
    std::string name = s1.get_studentName();
    list<Classes_per_uc> studentClasses = s1.get_classes();
    studentClasses.remove(cpu);
    students_.erase(s1);
    students_.insert(Student(student, name, studentClasses));
}

void ScheduleManager::writeStudentsFile() {
    ofstream h("../out/students_classes.csv"); // clears the file
    ofstream write;
    write.open("../out/students_classes.csv", std::ios_base::app);
    write << "StudentCode,StudentName,UcCode,ClassCode\n";
    for (Student s : students_) {
        for (Classes_per_uc cpu : s.get_classes()) {
            write << to_string(s.get_studentCode()) << ',' << s.get_studentName() << ',' << cpu.get_ucCode() << ',' << cpu.get_classCode() <<'\n';
        }
    }
}