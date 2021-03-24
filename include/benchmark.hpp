#pragma once

#define splitLimit 5

#include "myLib.hpp"
#include "struct.hpp"
#include "file.hpp"
#include "output.hpp"
#include "timer.hpp"
#include <algorithm>
#include "utils.hpp"

template <class Container>
void runBenchmark(int, string);