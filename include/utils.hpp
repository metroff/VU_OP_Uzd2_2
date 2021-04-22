#pragma once

#include "myLib.hpp"
#include "student.hpp"
#include <algorithm>

bool isValidGrade(int);

void sortContainer(list<Student> &);
void sortContainer(vector<Student> &);
void sortContainer(deque<Student> &);

void sortContainerByName(list<Student> &);
void sortContainerByName(vector<Student> &);
void sortContainerByName(deque<Student> &);