#include <DiggerOffline/utils_double.h>
#include <DiggerOffline/Point2D.h>

Point2D::Point2D() : x(0), y(0) {}
Point2D::Point2D(double x0, double y0) : x(x0), y(y0) {}
Point2D::Point2D(const Point2DInt& point) {
	x = static_cast<double>(point.x);
	y = static_cast<double>(point.y);
}

void Point2D::operator=(const Point2D& other) {
	x = other.x;
	y = other.y;
}

Point2D Point2D::operator+(const Point2D& other) const {
	return Point2D(x + other.x, y + other.y);
}

Point2D Point2D::operator+=(const Point2D& other) {
	x += other.x;
	y += other.y;
	return *this;
}

Point2D Point2D::operator-(const Point2D& other) const {
	return Point2D(x - other.x, y - other.y);
}

Point2D Point2D::operator-=(const Point2D& other) {
	x -= other.x;
	y -= other.y;
	return *this;
}

Point2D Point2D::operator*(double d) const {
	return Point2D(x * d, y * d);
}

Point2D Point2D::operator*=(double d) {
	x *= d;
	y *= d;
	return *this;
}

Point2D Point2D::operator/(double d) const {
	return Point2D(x / d, y / d);

}

Point2D Point2D::operator/=(double d) {
	x /= d;
	y /= d;
	return *this;
}

double& Point2D::operator[](int dim) {
	switch (dim) {
	case 0:
		return x;
	case 1:
		return y;
	default:
		return y;
	}
}

double Point2D::operator*(const Point2D& other) const {
	return x * other.y - y * other.x;

}

double Point2D::operator^(const Point2D& other) const {
	return x * other.x + y * other.y;
}

bool Point2D::operator==(const Point2D& other) const {
    return are_equal(x, other.x) && are_equal(y, other.y);
}

bool Point2D::operator!=(const Point2D& other) const {
    return !are_equal(x, other.x) || !are_equal(y, other.y);
}

double Point2D::len2() const {
	return (*this)^(*this);
}

double Point2D::len() const {
	return sqrt(len2());
}

double Point2D::get_angle(const Point2D& other) const {
	double length1 = len();
	double length2 = other.len();
	if (is_zero(length1) || is_zero(length2))
		return 0;
	return acos((*this ^ other) / (length1 * length2));
}

double Point2D::get_cos(const Point2D& other) const {
	double length1 = len();
	double length2 = other.len();
	if (is_zero(length1) || is_zero(length2))
		return 1.0;
	return (*this ^ other) / (length1 * length2);
}

bool Point2D::IsZero() const {
	return is_zero(x) && is_zero(y);
}
