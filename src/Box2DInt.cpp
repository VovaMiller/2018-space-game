#include <DiggerOffline/Box2DInt.h>

Box2DInt::Box2DInt() {}

Box2DInt::Box2DInt(int pos_x, int pos_y, int size_x, int size_y) {
	pos_.x = pos_x;
	pos_.y = pos_y;
	size_.x = size_x;
	size_.y = size_y;
}

Box2DInt::Box2DInt(const Point2DInt& pos, const Point2DInt& size) {
	pos_ = pos;
	size_ = size;
}

bool Box2DInt::operator==(const Box2DInt& other) const {
    return (pos_ == other.pos_) && (size_ == other.size_);
}

bool Box2DInt::operator!=(const Box2DInt& other) const {
    return (pos_ != other.pos_) || (size_ != other.size_);
}

bool Box2DInt::Has(int x, int y) const {
	return (pos_.x <= x) && (x < (pos_.x + size_.x))
		&& (pos_.y <= y) && (y < (pos_.y + size_.y));
}

bool Box2DInt::Has(const Point2DInt& point) const {
	return Has(point.x, point.y);
}

bool Box2DInt::IntersectsWith(const Box2DInt& other) const {
	if ((size_.x == 0) || (size_.y == 0) || (other.size_.x == 0) || (other.size_.y == 0))
		return false;
	return (pos_.x < (other.pos_.x + other.size_.x)) != ((pos_.x + size_.x) <= other.pos_.x)
		&& (pos_.y < (other.pos_.y + other.size_.y)) != ((pos_.y + size_.y) <= other.pos_.y);
}
