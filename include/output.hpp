#pragma once

#include "myLib.hpp"
#include "student.hpp"
#include "console.hpp"
#include "utils.hpp"
#include <algorithm>
#include <sstream>

using std::fixed;

template <class Container>
void printResults(Container &,  OutputType, bool useFile=false, string filename="rezultatai.txt", bool log = true);