#include "b_interface.h"
#include "b.hpp"

using namespace b;

extern "C" void add_b_int(int num) { add(num); }

extern "C" void add_b_float(float num) { add(num); }

extern "C" void add_b_double(double num) { add(num); }

extern "C" double get_b() { return b::get(); }
