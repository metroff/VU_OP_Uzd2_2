#pragma once

#include "myLib.hpp"
#include "struct.hpp"
#include "console.hpp"
#include "student.hpp"
#include <sstream>

using std::fixed;

void printResults(vector<Student> &,  OutputType, bool useFile=false);