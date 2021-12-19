#ifndef STUDENT_C
#define STUDENT_C

#include <Arduino.h>
#include <string>

class Student
{
public:
    Student();
    Student(String name, int age);
    ~Student();

private:
    String name;
    int age;

public:
    String getName();
    void setName(String name);
    int getAge();
    void setAge(int age);
};

#endif //STUDENT_C