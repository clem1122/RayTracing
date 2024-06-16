#pragma once
#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <vector>


// C++ Std Usings

using std::make_shared;
using std::shared_ptr;
using std::sqrt;

// Common Headers

#include "ray.h"
#include "vec3.h"

int random_int(int a, int b) {
	int range = b - a;
    if (range <= 0) return a;
    int result;
    do {
        result = a + std::floor(drand48() * range);
    } while (result == b); 

    return result;
}
