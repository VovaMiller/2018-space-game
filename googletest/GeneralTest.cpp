#include <gtest/gtest.h>
#include <DiggerOffline/utils_double.h>
#include <DiggerOffline/Point2DInt.h>
#include <DiggerOffline/Point2D.h>
#include <DiggerOffline/Box2DInt.h>
#include <DiggerOffline/Box2D.h>

TEST(Box2DIntTest, Has) {
    Box2DInt box(0, 0, 10, 5);
    EXPECT_TRUE(box.Has(0, 0)) << "Top Left corner";
    EXPECT_TRUE(box.Has(9, 4)) << "Bottom Right corner";
    EXPECT_TRUE(box.Has(9, 0)) << "Top Right corner";
    EXPECT_TRUE(box.Has(0, 4)) << "Bottom Left corner";
    EXPECT_TRUE(box.Has(4, 0)) << "Top side";
    EXPECT_TRUE(box.Has(4, 4)) << "Bottom side";
    EXPECT_TRUE(box.Has(0, 3)) << "Left side";
    EXPECT_TRUE(box.Has(9, 3)) << "Right side";
    EXPECT_TRUE(box.Has(4, 2)) << "Inside";
    EXPECT_FALSE(box.Has(-1, -1)) << "Outside (Top Left)";
    EXPECT_FALSE(box.Has(4, -1)) << "Outside (Top)";
    EXPECT_FALSE(box.Has(10, -1)) << "Outside (Top Right)";
    EXPECT_FALSE(box.Has(10, 3)) << "Outside (Right)";
    EXPECT_FALSE(box.Has(10, 5)) << "Outside (Bottom Right)";
    EXPECT_FALSE(box.Has(4, 5)) << "Outside (Bottom)";
    EXPECT_FALSE(box.Has(-1, 5)) << "Outside (Bottom Left)";
    EXPECT_FALSE(box.Has(-1, 3)) << "Outside (Left)";
}

TEST(Box2DIntTest, IntersectsWith) {
    Box2DInt box(0, 0, 10, 5);
    EXPECT_TRUE(box.IntersectsWith(Box2DInt(0, 0, 1, 1)));
    EXPECT_TRUE(box.IntersectsWith(Box2DInt(0, 0, 10, 5)));
    EXPECT_TRUE(box.IntersectsWith(Box2DInt(0, 0, 100, 100)));
    EXPECT_TRUE(box.IntersectsWith(Box2DInt(2, 2, 1, 1)));
    EXPECT_TRUE(box.IntersectsWith(Box2DInt(-1, -1, 2, 2)));
    EXPECT_TRUE(box.IntersectsWith(Box2DInt(9, 4, 1, 1)));
    EXPECT_TRUE(box.IntersectsWith(Box2DInt(5, -2, 2, 10)));
    EXPECT_TRUE(box.IntersectsWith(Box2DInt(-2, 2, 20, 2)));
    EXPECT_FALSE(box.IntersectsWith(Box2DInt(0, 0, 0, 0)));
    EXPECT_FALSE(box.IntersectsWith(Box2DInt(1, 1, 0, 0)));
    EXPECT_FALSE(box.IntersectsWith(Box2DInt(-1, -1, 1, 1)));
    EXPECT_FALSE(box.IntersectsWith(Box2DInt(10, 5, 1, 1)));
    EXPECT_FALSE(box.IntersectsWith(Box2DInt(-1, -1, 1, 10)));
    EXPECT_FALSE(box.IntersectsWith(Box2DInt(-1, -1, 10, 1)));
    EXPECT_FALSE(box.IntersectsWith(Box2DInt(10, -1, 1, 10)));
    EXPECT_FALSE(box.IntersectsWith(Box2DInt(-1, 5, 10, 1)));
    EXPECT_FALSE(box.IntersectsWith(Box2DInt(2, -5, 2, 2)));
    EXPECT_FALSE(box.IntersectsWith(Box2DInt(2, 10, 2, 2)));
    EXPECT_FALSE(box.IntersectsWith(Box2DInt(-5, 2, 2, 2)));
    EXPECT_FALSE(box.IntersectsWith(Box2DInt(15, 2, 2, 2)));
}

TEST(Box2DTest, Has) {
    Box2D box(0.0, 0.0, 10.0, 5.0);
    EXPECT_TRUE(box.Has(4.0, 2.0)) << "Inside";
    EXPECT_TRUE(box.Has(9.9, 4.9)) << "Inside";
    EXPECT_TRUE(box.Has(0.1, 0.1)) << "Inside";
    EXPECT_FALSE(box.Has(0.0, 0.0)) << "Top Left corner";
    EXPECT_FALSE(box.Has(10.0, 5.0)) << "Bottom Right corner";
    EXPECT_FALSE(box.Has(10.0, 0)) << "Top Right corner";
    EXPECT_FALSE(box.Has(0, 5.0)) << "Bottom Left corner";
    EXPECT_FALSE(box.Has(4.0, 0.0)) << "Top side";
    EXPECT_FALSE(box.Has(4.0, 5.0)) << "Bottom side";
    EXPECT_FALSE(box.Has(0.0, 3.0)) << "Left side";
    EXPECT_FALSE(box.Has(10.0, 3.0)) << "Right side";
    EXPECT_FALSE(box.Has(-1.0, -1.0)) << "Outside (Top Left)";
    EXPECT_FALSE(box.Has(4.0, -1.0)) << "Outside (Top)";
    EXPECT_FALSE(box.Has(11.0, -1.0)) << "Outside (Top Right)";
    EXPECT_FALSE(box.Has(11.0, 3.0)) << "Outside (Right)";
    EXPECT_FALSE(box.Has(11.0, 6.0)) << "Outside (Bottom Right)";
    EXPECT_FALSE(box.Has(4.0, 6.0)) << "Outside (Bottom)";
    EXPECT_FALSE(box.Has(-1.0, 6.0)) << "Outside (Bottom Left)";
    EXPECT_FALSE(box.Has(-1.0, 3.0)) << "Outside (Left)";
}

TEST(Box2DTest, IntersectsWith) {
    Box2D box(0.0, 0.0, 10.0, 5.0);
    EXPECT_TRUE(box.IntersectsWith(Box2D(0.0, 0.0, 1.0, 1.0)));
    EXPECT_TRUE(box.IntersectsWith(Box2D(0.0, 0.0, 10.0, 5.0)));
    EXPECT_TRUE(box.IntersectsWith(Box2D(0.0, 0.0, 100.0, 100.0)));
    EXPECT_TRUE(box.IntersectsWith(Box2D(2.0, 2.0, 1.0, 1.0)));
    EXPECT_TRUE(box.IntersectsWith(Box2D(-1.0, -1.0, 2.0, 2.0)));
    EXPECT_TRUE(box.IntersectsWith(Box2D(9.9, 4.9, 0.1, 0.1)));
    EXPECT_TRUE(box.IntersectsWith(Box2D(5.0, -2.0, 2.0, 10.0)));
    EXPECT_TRUE(box.IntersectsWith(Box2D(-2.0, 2.0, 20.0, 2.0)));
    EXPECT_FALSE(box.IntersectsWith(Box2D(0.0, 0.0, 0.0, 0.0)));
    EXPECT_FALSE(box.IntersectsWith(Box2D(1.0, 1.0, 0.0, 0.0)));
    EXPECT_FALSE(box.IntersectsWith(Box2D(-1.0, -1.0, 1.0, 1.0)));
    EXPECT_FALSE(box.IntersectsWith(Box2D(10.0, 5.0, 1.0, 1.0)));
    EXPECT_FALSE(box.IntersectsWith(Box2D(-1.0, -1.0, 1.0, 10.0)));
    EXPECT_FALSE(box.IntersectsWith(Box2D(-1.0, -1.0, 10.0, 1.0)));
    EXPECT_FALSE(box.IntersectsWith(Box2D(10.0, -1.0, 1.0, 10.0)));
    EXPECT_FALSE(box.IntersectsWith(Box2D(-1.0, 5.0, 10.0, 1.0)));
    EXPECT_FALSE(box.IntersectsWith(Box2D(2.0, -5.0, 2.0, 2.0)));
    EXPECT_FALSE(box.IntersectsWith(Box2D(2.0, 10.0, 2.0, 2.0)));
    EXPECT_FALSE(box.IntersectsWith(Box2D(-5.0, 2.0, 2.0, 2.0)));
    EXPECT_FALSE(box.IntersectsWith(Box2D(15.0, 2.0, 2.0, 2.0)));
}

TEST(Point2DIntTest, ScalarProduct) {
    Point2DInt point(1, 1);
    EXPECT_EQ(point.len2(), point^point) << "(point, point) != |point|^2";
    EXPECT_EQ(0, point^Point2DInt(0, 0)) << "(point, 0) != 0";
    EXPECT_EQ(-point.len2(), point^(point * (-1))) << "(point, -point) != -|point|^2";
    EXPECT_EQ(0, point^Point2DInt(point.y, -point.x)) << "(v1, v2) != 0, when v1 _|_ v2";
    EXPECT_EQ(1, point^Point2DInt(1, 0));
    EXPECT_EQ(1, point^Point2DInt(0, 1));
    EXPECT_EQ(point^Point2DInt(-3, 2), Point2DInt(-3, 2)^point) << "(v1, v2) != (v2, v1)";
}

TEST(Point2DTest, ScalarProduct) {
    Point2D point(1.0, 1.0);
    EXPECT_NEAR(point.len2(), point^point, kEps) << "(point, point) != |point|^2";
    EXPECT_NEAR(0.0, point^Point2D(0.0, 0.0), kEps) << "(point, 0) != 0";
    EXPECT_NEAR(-point.len2(), point^(point * (-1.0)), kEps) << "(point, -point) != -|point|^2";
    EXPECT_NEAR(0.0, point^Point2D(point.y, -point.x), kEps) << "(v1, v2) != 0, when v1 _|_ v2";
    EXPECT_NEAR(1.0, point^Point2D(1.0, 0.0), kEps);
    EXPECT_NEAR(1.0, point^Point2D(0.0, 1.0), kEps);
    EXPECT_NEAR(point^Point2D(-3.0, 2.0), Point2D(-3.0, 2.0)^point, kEps) << "(v1, v2) != (v2, v1)";
}

TEST(Point2DTest, VectorProduct) {
    Point2D point(1.0, 1.0);
    EXPECT_NEAR(0.0, point*point, kEps) << "|[point, point]| != 0";
    EXPECT_NEAR(0.0, point*Point2D(0.0, 0.0), kEps) << "|[point, 0]| != 0";
    EXPECT_NEAR(0.0, point*(point * (-1.0)), kEps) << "|[point, -point]| != 0";
    EXPECT_NEAR(-2.0, point*Point2D(1.0, -1.0), kEps);
    EXPECT_NEAR(2.0, point*Point2D(-1.0, 1.0), kEps);
    EXPECT_NEAR(-1.0, point*Point2D(1.0, 0.0), kEps);
    EXPECT_NEAR(1.0, point*Point2D(0.0, 1.0), kEps);
    EXPECT_NEAR(point*Point2D(-3.0, 2.0), -(Point2D(-3.0, 2.0)*point), kEps) << "[v1, v2].z != -[v2, v1].z";
}

TEST(Point2DTest, GetAngle) {
    Point2D point(1.0, 1.0);
    double pi = 4 * std::atan(1);
    EXPECT_NEAR(0.0, point.get_angle(point), kEps) << "angle(v, v) != 0";
    EXPECT_NEAR(pi, std::abs(point.get_angle(point * (-1))), kEps) << "|angle(v, -v)| != pi";
    EXPECT_NEAR(0.0, point.get_angle(Point2D(0.0, 0.0)), kEps) << "angle(v, 0) != 0";
    EXPECT_NEAR(pi / 2.0, point.get_angle(Point2D(point.y, -point.x)), kEps);
    EXPECT_NEAR(point.get_angle(Point2D(-3.0, 2.0)), Point2D(-3.0, 2.0).get_angle(point), kEps) << "angle(v1, v2) != angle(v2, v1)";
    EXPECT_NEAR(pi / 4.0, Point2D(1.0, 1.0).get_angle(Point2D(1.0, 0)), kEps);
    EXPECT_NEAR(3.0 * pi / 4.0, Point2D(1.0, 1.0).get_angle(Point2D(-1.0, 0)), kEps);
    EXPECT_NEAR(3.0 * pi / 4.0, Point2D(1.0, 1.0).get_angle(Point2D(0.0, -1.0)), kEps);
}

TEST(Point2DTest, GetCos) {
    Point2D point(1.0, 1.0);
    double pi = 4 * std::atan(1);
    EXPECT_NEAR(1.0, point.get_cos(point), kEps) << "cos(v, v) != 1";
    EXPECT_NEAR(-1.0, point.get_cos(point * (-1)), kEps) << "cos(v, -v) != -1";
    EXPECT_NEAR(1.0, point.get_cos(Point2D(0.0, 0.0)), kEps) << "cos(v, 0) != 1";
    EXPECT_NEAR(0.0, point.get_cos(Point2D(point.y, -point.x)), kEps);
    EXPECT_NEAR(point.get_cos(Point2D(-3.0, 2.0)), Point2D(-3.0, 2.0).get_cos(point), kEps) << "cos(v1, v2) != cos(v2, v1)";
    EXPECT_NEAR(std::cos(pi / 4.0), Point2D(1.0, 1.0).get_cos(Point2D(1.0, 0)), kEps);
    EXPECT_NEAR(std::cos(3.0 * pi / 4.0), Point2D(1.0, 1.0).get_cos(Point2D(-1.0, 0)), kEps);
    EXPECT_NEAR(std::cos(3.0 * pi / 4.0), Point2D(1.0, 1.0).get_cos(Point2D(0.0, -1.0)), kEps);
}
