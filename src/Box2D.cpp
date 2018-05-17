#include <DiggerOffline/Box2D.h>
#include <DiggerOffline/utils_double.h>

Box2D::Box2D() {}

Box2D::Box2D(double pos_x, double pos_y, double size_x, double size_y) {
	pos_.x = pos_x;
	pos_.y = pos_y;
	size_.x = size_x;
	size_.y = size_y;
}

Box2D::Box2D(const Point2D& pos, const Point2D& size) {
	pos_ = pos;
	size_ = size;
}

Box2D::Box2D(const Box2DInt& box) {
	pos_.x = static_cast<double>(box.pos_.x);
	pos_.y = static_cast<double>(box.pos_.y);
	size_.x = static_cast<double>(box.size_.x);
	size_.y = static_cast<double>(box.size_.y);
}

bool Box2D::operator==(const Box2D& other) const {
    return (pos_ == other.pos_) && (size_ == other.size_);
}

bool Box2D::operator!=(const Box2D& other) const {
    return (pos_ != other.pos_) || (size_ != other.size_);
}

bool Box2D::Has(double x, double y) const {
	return is_less_than(pos_.x, x) && is_less_than(x, pos_.x + size_.x)
		&& is_less_than(pos_.y, y) && is_less_than(y, pos_.y + size_.y);
}

bool Box2D::Has(const Point2D& point) const {
	return Has(point.x, point.y);
}

bool Box2D::IntersectsWith(const Box2D& other) const {
	if (is_zero(size_.x) || is_zero(size_.y) || is_zero(other.size_.x) || is_zero(other.size_.y))
		return false;
	return (is_less_than(pos_.x, other.pos_.x + other.size_.x) != is_less_or_equal(pos_.x + size_.x, other.pos_.x))
		&& (is_less_than(pos_.y, other.pos_.y + other.size_.y) != is_less_or_equal(pos_.y + size_.y, other.pos_.y));
}
