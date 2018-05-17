#pragma once
#include <DiggerOffline/Point2D.h>
#include <DiggerOffline/Box2DInt.h>

// Открытый прямоугольник.
class Box2D {
public:
	Box2D();
	Box2D(double pos_x, double pos_y, double size_x, double size_y);
	Box2D(const Point2D& pos, const Point2D& size);
	Box2D(const Box2DInt& box);

	Point2D pos_;
	Point2D size_;

    bool operator==(const Box2D& other) const;
    bool operator!=(const Box2D& other) const;
	bool Has(double x, double y) const;
	bool Has(const Point2D& point) const;
	bool IntersectsWith(const Box2D& other) const;
};
