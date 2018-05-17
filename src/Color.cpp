#include <DiggerOffline/Color.h>

Color::Color() : r_(0), g_(0), b_(0), a_(255) {}

Color::Color(int r, int g, int b) : r_(0), g_(0), b_(0), a_(255) {
	set_rgb(r, g, b);
}

Color::Color(int r, int g, int b, int a) : r_(0), g_(0), b_(0), a_(255) {
	set_rgba(r, g, b, a);
}

void Color::set_rgb(int r, int g, int b) {
	set_r(r);
	set_g(g);
	set_b(b);
}

void Color::set_rgba(int r, int g, int b, int a) {
	set_r(r);
	set_g(g);
	set_b(b);
	set_a(a);
}

void Color::set_r(int r) {
	r_ = CheckFormat(r, r_);
}

void Color::set_g(int g) {
	g_ = CheckFormat(g, g_);
}

void Color::set_b(int b) {
	b_ = CheckFormat(b, b_);
}

void Color::set_a(int a) {
	a_ = CheckFormat(a, a_);
}

int Color::get_r() const {
	return r_;
}

int Color::get_g() const {
	return g_;
}

int Color::get_b() const {
	return b_;
}

int Color::get_a() const {
	return a_;
}

int Color::CheckFormat(int c, int c0) {
	if ((c >= 0) && (c <= 255))
		return c;
	return c0;
}
