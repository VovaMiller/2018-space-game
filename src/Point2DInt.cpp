#include <DiggerOffline/Point2DInt.h>

Point2DInt::Point2DInt() : x(0), y(0) {}
Point2DInt::Point2DInt(int x0, int y0) : x(x0), y(y0) {}

void Point2DInt::operator=(const Point2DInt& other) {
	x = other.x;
	y = other.y;
}

Point2DInt Point2DInt::operator+(const Point2DInt& other) const {
	return Point2DInt(x + other.x, y + other.y);
}

Point2DInt Point2DInt::operator+=(const Point2DInt& other) {
	x += other.x;
	y += other.y;
	return *this;
}

Point2DInt Point2DInt::operator-(const Point2DInt& other) const {
	return Point2DInt(x - other.x, y - other.y);
}

Point2DInt Point2DInt::operator-=(const Point2DInt& other) {
	x -= other.x;
	y -= other.y;
	return *this;
}

Point2DInt Point2DInt::operator*(int d) const {
	return Point2DInt(x * d, y * d);
}

Point2DInt Point2DInt::operator*=(int d) {
	x *= d;
	y *= d;
	return *this;
}

Point2DInt Point2DInt::operator/(int d) const {
	return Point2DInt(x / d, y / d);
}

Point2DInt Point2DInt::operator/=(int d) {
	x /= d;
	y /= d;
	return *this;
}

int& Point2DInt::operator[](int dim) {
	switch (dim) {
	case 0:
		return x;
	case 1:
		return y;
	default:
		return y;
	}
}

int Point2DInt::operator^(const Point2DInt& other) const {
	return x * other.x + y * other.y;
}

bool Point2DInt::operator==(const Point2DInt& other) const {
    return (x == other.x) && (y == other.y);
}

bool Point2DInt::operator!=(const Point2DInt& other) const {
    return (x != other.x) || (y != other.y);
}

int Point2DInt::len2() const {
	return (*this)^(*this);
}

double Point2DInt::len() const {
	return sqrt(len2());
}

bool Point2DInt::IsZero() const {
	return (x == 0) && (y == 0);
}
