#pragma once

#define splitLimit 5

#include "myLib.hpp"
#include "student.hpp"
#include "file.hpp"
#include "output.hpp"
#include "timer.hpp"
#include <algorithm>
#include "utils.hpp"
#include "console.hpp"

void runBenchmarkWizard();

template <class Container>
void runBenchmark(int, string, int);