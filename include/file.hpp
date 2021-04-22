#pragma once

#include "myLib.hpp"
#include "student.hpp"
#include <sys/stat.h>
#include "utils.hpp"
#include "console.hpp"
#include "rng.hpp"
#include <sstream>

class FileNotFound{};

bool checkIfFileExists(const string&);

template <class Container>
void readFromFile(string, Container &);
void generateFile(string, int);