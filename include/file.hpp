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

template <class Container>
void readFromFile(string, Container &);
void generateFile(string, int);