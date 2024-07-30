#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "boids.hpp"

#include "doctest.h"

TEST_CASE("Testing the operators of the struct Point2D")
{
  pf::Point2D point1{1.3, 12.4};
  pf::Point2D point2{4.32, 2};
  pf::Point2D point3{0, -1.7};

  SUBCASE("Testing operator +")
  {
    auto p1 = point1 + point2;
    auto p2 = point2 + point3;
    CHECK(p1.x == doctest::Approx(5.62));
    CHECK(p2.x == doctest::Approx(4.32));
    CHECK(p1.y == doctest::Approx(14.4));
    CHECK(p2.y == doctest::Approx(0.3));
  }

  SUBCASE("Testing operator -")
  {
    auto p1 = point1 - point2;
    auto p2 = point2 - point3;
    CHECK(p1.x == doctest::Approx(-3.02));
    CHECK(p2.x == doctest::Approx(4.32));
    CHECK(p1.y == doctest::Approx(10.4));
    CHECK(p2.y == doctest::Approx(3.7));
  }

  SUBCASE("Testing operator * with a positive double")
  {
    auto u  = 2.3;
    auto p1 = u * point1;
    CHECK(p1.x == doctest::Approx(2.99));
    CHECK(p1.y == doctest::Approx(28.52));
  }

  SUBCASE("Testing operator * with a negative double")
  {
    auto u  = -0.2;
    auto p1 = u * point2;
    CHECK(p1.x == doctest::Approx(-0.864));
    CHECK(p1.y == doctest::Approx(-0.4));
  }

  SUBCASE("Testing operator * with 0")
  {
    auto u  = 0.;
    auto p1 = u * point1;
    CHECK(p1.x == doctest::Approx(0));
    CHECK(p1.y == doctest::Approx(0));
  }
}