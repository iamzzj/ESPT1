#include "Student.h"
#include <Arduino.h>

Student::Student()
{
    Serial.println("Student()");
}

Student::Student(String name, int age)
{
    this->name = name;
    this->age = age;
}

Student::~Student()
{
    Serial.println("~Student()");
}

String Student::getName()
{
    return this->name;
}

void Student::setName(String name)
{
    this->name = name;
}

int Student::getAge()
{
    return this->age;
}

void Student::setAge(int age)
{
    this->age = age;
}
