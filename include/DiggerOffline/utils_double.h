#pragma once
#include <cmath>

const double kEps = 1e-5;
const double kPi = 3.14159;

bool is_zero(double d);
int sign(double d);
bool are_equal(double x, double y);
bool is_less_than(double x, double y);
bool is_more_than(double x, double y);
bool is_less_or_equal(double x, double y);
bool is_more_or_equal(double x, double y);
