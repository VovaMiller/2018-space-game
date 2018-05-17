#include <DiggerOffline/utils_double.h>

bool is_zero(double d) {
	return std::abs(d) < kEps;
}

int sign(double d) {
	if (is_zero(d)) return 0;
	return (d > 0) ? 1 : -1;
}

bool are_equal(double x, double y) {
	return sign(x - y) == 0;
}

bool is_less_than(double x, double y) {
	return sign(x - y) < 0;
}

bool is_more_than(double x, double y) {
	return sign(x - y) > 0;
}

bool is_less_or_equal(double x, double y) {
	return sign(x - y) <= 0;
}

bool is_more_or_equal(double x, double y) {
	return sign(x - y) >= 0;
}
