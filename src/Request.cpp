#include "Request.h"

Request::Request(list<Classes_per_uc> pretendedClass, list<Classes_per_uc> actualClass, int studentCode, char type) : pretendedClass_(pretendedClass), actualClass_(actualClass), studentCode_(studentCode), type_(type){}
list<Classes_per_uc> Request::getPretendedClass() { return pretendedClass_;}
list<Classes_per_uc> Request::getActualClass(){ return actualClass_; }
int Request::getStudentCode(){ return studentCode_; }
char Request::getType() {return type_;}