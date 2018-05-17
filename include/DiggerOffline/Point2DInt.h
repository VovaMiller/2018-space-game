#pragma once
#include <cmath>

class Point2DInt {
public:
	Point2DInt();
	Point2DInt(int x0, int y0);

	void operator=(const Point2DInt& other);
	Point2DInt operator+(const Point2DInt& other) const;
	Point2DInt operator+=(const Point2DInt& other);
	Point2DInt operator-(const Point2DInt& other) const;
	Point2DInt operator-=(const Point2DInt& other);
	Point2DInt operator*(int d) const;
	Point2DInt operator*=(int d);
	Point2DInt operator/(int d) const;
	Point2DInt operator/=(int d);
	int& operator[](int dim);
	int operator^(const Point2DInt& other) const;
    bool operator==(const Point2DInt& other) const;
    bool operator!=(const Point2DInt& other) const;
	int len2() const;
	double len() const;
	bool IsZero() const;

	int x, y;
};
