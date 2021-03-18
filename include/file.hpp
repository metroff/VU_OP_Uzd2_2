#pragma once

#include "myLib.hpp"
#include "struct.hpp"
#include "student.hpp"
#include <sys/stat.h>
#include "utils.hpp"
#include "console.hpp"
#include "rng.hpp"
#include <sstream>

class GradeException{};
class FileNotFound{};

void readFromFile(string, vector<Student> &);
void generateFile(string, int);