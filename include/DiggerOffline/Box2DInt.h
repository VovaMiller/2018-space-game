#pragma once
#include <DiggerOffline/Point2DInt.h>

class Box2DInt {
public:
	Box2DInt();
	Box2DInt(int pos_x, int pos_y, int size_x, int size_y);
	Box2DInt(const Point2DInt& pos, const Point2DInt& size);

	Point2DInt pos_;
	Point2DInt size_;

    bool operator==(const Box2DInt& other) const;
    bool operator!=(const Box2DInt& other) const;
	bool Has(int x, int y) const;
	bool Has(const Point2DInt& point) const;
	bool IntersectsWith(const Box2DInt& other) const;
};
