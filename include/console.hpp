#pragma once

#include "myLib.hpp"
#include <limits>
#include "utils.hpp"

using std::numeric_limits;
using std::streamsize;

enum class OutputType {MEAN, MEDIAN, BOTH};

int readNumber();
int getNumOfGrades();
int getGrade(bool exit_state = false);
bool yesNoQuestion(string);
OutputType getOutputType();
int getInt(string, int, int);