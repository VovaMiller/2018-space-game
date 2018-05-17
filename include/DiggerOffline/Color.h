#pragma once

class Color {
public:
	Color();
	Color(int r, int g, int b);
	Color(int r, int g, int b, int a);

	void set_rgb(int r, int g, int b);
	void set_rgba(int r, int g, int b, int a);
	void set_r(int r);
	void set_g(int g);
	void set_b(int b);
	void set_a(int a);
	int get_r() const;
	int get_g() const;
	int get_b() const;
	int get_a() const;

private:
	int r_, g_, b_, a_;

	int CheckFormat(int c, int c0);
};
