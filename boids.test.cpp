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

  SUBCASE("Testing operator /")
  {
    auto u  = 2.1;
    auto p1 = point1 / u;
    CHECK(p1.x == doctest::Approx(0.6190476));
    CHECK(p1.y == doctest::Approx(5.9047619));
  }
}

TEST_CASE("Testing rules of flight")
{
  std::vector<pf::Boid> prova;
  REQUIRE(prova.size() == 0);

  SUBCASE("Calling separazione() with 2 boids")
  {
    pf::Point2D p1{2, 3};
    pf::Point2D v1{0, 0};
    pf::Point2D p2{4.5, 7.8};
    pf::Point2D v2{0, 0};
    pf::Boid b1{p1, v1};
    pf::Boid b2{p2, v2};
    prova.push_back(b1);
    prova.push_back(b2);
    pf::Point2D v3 = separazione(prova, p1, 0.5);
    CHECK(v3.x == doctest::Approx(-1.25));
    CHECK(v3.y == doctest::Approx(-2.4));
  }

  SUBCASE("Calling separazione() with 0 boids")
  {
    pf::Point2D p1{2, 3};
    CHECK_THROWS(separazione(prova, p1, 0.5));
  }

  SUBCASE("Calling separazione() with 1 boid")
  {
    pf::Point2D p1{2, 3};
    pf::Point2D p2{4.5, 7.8};
    pf::Point2D v2{0, 0};
    pf::Boid b2{p2, v2};
    prova.push_back(b2);
    CHECK_THROWS(separazione(prova, p1, 0.5));
  }

  SUBCASE("Calling allineamento() with 3 boids")
  {
    pf::Point2D v1{2, 3};
    pf::Point2D p1{0, 0};
    pf::Point2D v2{0.5, 6.2};
    pf::Point2D p2{0, 0};
    pf::Point2D v3{4.5, 7.8};
    pf::Point2D p3{0, 0};
    pf::Boid b1{p1, v1};
    pf::Boid b2{p2, v2};
    pf::Boid b3{p3, v3};
    prova.push_back(b1);
    prova.push_back(b2);
    prova.push_back(b3);
    pf::Point2D v4 = allineamento(prova, 1, 3);
    CHECK(v4.x == doctest::Approx(8.25));
    CHECK(v4.y == doctest::Approx(-2.4));
  }

  SUBCASE("Calling allineamento() with 0 boids")
  {
    CHECK_THROWS(allineamento(prova, 0, 2));
  }

  SUBCASE("Calling allineamento() with 1 boid")
  {
    pf::Point2D v1{4.5, 7.8};
    pf::Point2D p1{0, 0};
    pf::Boid b1{p1, v1};
    prova.push_back(b1);
    CHECK_THROWS(allineamento(prova, 0, 2));
  }

  SUBCASE("Calling coesione() with 3 boids")
  {
    pf::Point2D p1{2, 3};
    pf::Point2D v1{0, 0};
    pf::Point2D p2{0.5, 6.2};
    pf::Point2D v2{0, 0};
    pf::Point2D p3{4.5, 7.8};
    pf::Point2D v3{0, 0};
    pf::Boid b1{p1, v1};
    pf::Boid b2{p2, v2};
    pf::Boid b3{p3, v3};
    prova.push_back(b1);
    prova.push_back(b2);
    prova.push_back(b3);
    pf::Point2D v4 = coesione(prova, 0, 0.6);
    CHECK(v4.x == doctest::Approx(0.3));
    CHECK(v4.y == doctest::Approx(2.4));
  }

  SUBCASE("Calling coesione() with 0 boids")
  {
    CHECK_THROWS(coesione(prova, 0, 0.2));
  }

  SUBCASE("Calling coesione() with 1 boid")
  {
    pf::Point2D p1{4.5, 7};
    pf::Point2D v1{0, 0};
    pf::Boid b1{p1, v1};
    prova.push_back(b1);
    CHECK_THROWS(allineamento(prova, 0, 2));
  }
}
