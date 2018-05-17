#pragma once
#include <DiggerOffline/Point2DInt.h>

class Point2D {
public:
	Point2D();
	Point2D(double x0, double y0);
	Point2D(const Point2DInt& point);

	void operator=(const Point2D& other);
	Point2D operator+(const Point2D& other) const;
	Point2D operator+=(const Point2D& other);
	Point2D operator-(const Point2D& other) const;
	Point2D operator-=(const Point2D& other);
	Point2D operator*(double d) const;
	Point2D operator*=(double d);
	Point2D operator/(double d) const;
	Point2D operator/=(double d);
	double& operator[](int dim);
	double operator*(const Point2D& other) const;
	double operator^(const Point2D& other) const;
    bool operator==(const Point2D& other) const;
    bool operator!=(const Point2D& other) const;
	double len2() const;
	double len() const;
	double get_angle(const Point2D& other) const;
	double get_cos(const Point2D& other) const;
	bool IsZero() const;

	double x, y;
};
