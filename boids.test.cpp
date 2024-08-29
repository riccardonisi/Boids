#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "simulation.hpp"

#include "doctest.h"

TEST_CASE("Testing operators and functions of the struct Point2D")
{
  SUBCASE("Testing operator +")
  {
    pf::Point2D point1{1.3f, 12.4f};
    pf::Point2D point2{4.32f, 2};
    pf::Point2D point3{0, -1.7f};
    auto p1 = point1 + point2;
    auto p2 = point2 + point3;
    CHECK(p1.x == doctest::Approx(5.62f));
    CHECK(p2.x == doctest::Approx(4.32f));
    CHECK(p1.y == doctest::Approx(14.4f));
    CHECK(p2.y == doctest::Approx(0.3f));
  }

  SUBCASE("Testing operator -")
  {
    pf::Point2D point1{1.3f, 12.4f};
    pf::Point2D point2{4.32f, 2};
    pf::Point2D point3{0, -1.7f};
    auto p1 = point1 - point2;
    auto p2 = point2 - point3;
    CHECK(p1.x == doctest::Approx(-3.02f));
    CHECK(p2.x == doctest::Approx(4.32f));
    CHECK(p1.y == doctest::Approx(10.4f));
    CHECK(p2.y == doctest::Approx(3.7f));
  }

  SUBCASE("Testing operator * with a positive float")
  {
    pf::Point2D point1{1.3f, 12.4f};
    auto u  = 2.3f;
    auto p1 = u * point1;
    CHECK(p1.x == doctest::Approx(2.99f));
    CHECK(p1.y == doctest::Approx(28.52f));
  }

  SUBCASE("Testing operator * with a negative float")
  {
    pf::Point2D point2{4.32f, 2};
    auto u  = -0.2f;
    auto p1 = u * point2;
    CHECK(p1.x == doctest::Approx(-0.864f));
    CHECK(p1.y == doctest::Approx(-0.4f));
  }

  SUBCASE("Testing operator * with 0")
  {
    pf::Point2D point1{1.3f, 12.4f};
    auto u  = 0.f;
    auto p1 = u * point1;
    CHECK(p1.x == doctest::Approx(0.f));
    CHECK(p1.y == doctest::Approx(0.f));
  }

  SUBCASE("Testing operator /")
  {
    pf::Point2D point1{1.3f, 12.4f};
    auto u  = 2.1f;
    auto p1 = point1 / u;
    CHECK(p1.x == doctest::Approx(0.6190476f));
    CHECK(p1.y == doctest::Approx(5.9047619f));
  }

  SUBCASE("Testing operator / with 0")
  {
    pf::Point2D point1{1.3f, 12.4f};
    auto u = 0.f;
    CHECK_THROWS(point1 / u);
  }

  SUBCASE("Testing dot() function")
  {
    pf::Point2D a1{2, 3};
    pf::Point2D b1{-1, 0};
    pf::dot(a1, b1);
    CHECK(pf::dot(a1, b1) == doctest::Approx(-2.f));
    pf::Point2D a2{0, 3};
    pf::Point2D b2{-1, 0};
    pf::dot(a2, b2);
    CHECK(pf::dot(a2, b2) == doctest::Approx(0.f));
    pf::Point2D a3{-1, -3};
    pf::Point2D b3{-1, -2};
    pf::dot(a3, b3);
    CHECK(pf::dot(a3, b3) == doctest::Approx(7.f));
    a3 = pf::Point2D{1, 1};
    CHECK(pf::dot(a3, a3) == doctest::Approx(2.f));
    a3 = pf::Point2D{std::sqrt(2.F) / 2, std::sqrt(2.F) / 2};
    CHECK(pf::dot(a3, a3) == doctest::Approx(1.f));
    a3 = pf::Point2D{0, 0};
    CHECK(pf::dot(a3, b3) == doctest::Approx(0.f));
  }

  SUBCASE("Testing magnitude() function")
  {
    pf::Point2D a{1, 2};
    pf::magnitude(a);
    CHECK(pf::magnitude(a) == doctest::Approx(2.23607f));
    pf::Point2D b{0, 0};
    pf::magnitude(b);
    CHECK(pf::magnitude(b) == doctest::Approx(0.f));
    pf::Point2D c{-2, -5};
    pf::magnitude(c);
    CHECK(pf::magnitude(c) == doctest::Approx(5.38516f));
  }

  SUBCASE("Testing normalization() function")
  {
    pf::Point2D a{2, 3};
    pf::normalization(a);
    CHECK(pf::normalization(a).x == doctest::Approx(0.55470f));
    CHECK(pf::normalization(a).y == doctest::Approx(0.83205f));
    CHECK(pf::magnitude(normalization(a)) == doctest::Approx(0.99999f));
    pf::Point2D b{-3, -1};
    pf::normalization(b);
    CHECK(pf::normalization(b).x == doctest::Approx(-0.94868f));
    CHECK(pf::normalization(b).y == doctest::Approx(-0.31623f));
    CHECK(pf::magnitude(normalization(b)) == doctest::Approx(0.99999f));
    pf::Point2D c{0, 0};
    CHECK(pf::normalization(c).x == doctest::Approx(0.f));
    CHECK(pf::normalization(c).y == doctest::Approx(0.f));
    CHECK(pf::magnitude(normalization(c)) == doctest::Approx(0.f));
  }

  SUBCASE("Testing distance() function")
  {
    pf::Point2D a{2, 5};
    pf::Point2D b{0.3f, 6.8f};
    pf::Point2D c{-15, 100};
    CHECK(pf::distance(a, b) == doctest::Approx(2.47589f));
    CHECK(pf::distance(b, c) == doctest::Approx(94.4475f));
    CHECK(pf::distance(a, c) == doctest::Approx(96.5091f));
  }
}

TEST_CASE("Testing methods and operators of the class Boid")
{
  SUBCASE("Testing get_() methods")
  {
    pf::Boid a{{3.2f, 9.4f}, {2, 4.8f}};
    CHECK(a.get_pos().x == 3.2f);
    CHECK(a.get_pos().y == 9.4f);
    CHECK(a.get_vel().x == 2.0f);
    CHECK(a.get_vel().y == 4.8f);
  }

  SUBCASE("Testing set_() methods")
  {
    pf::Boid a{{3.2f, 9.4f}, {2, 4.8f}};
    pf::Point2D p{2.3f, 4.5f};
    a.set_pos(p);
    CHECK(a.get_pos().x == 2.3f);
    CHECK(a.get_pos().y == 4.5f);
    CHECK(a.get_vel().x == 2.0f);
    CHECK(a.get_vel().y == 4.8f);
    pf::Point2D v{3.1f, 7.5f};
    a.set_vel(v);
    CHECK(a.get_pos().x == 2.3f);
    CHECK(a.get_pos().y == 4.5f);
    CHECK(a.get_vel().x == 3.1f);
    CHECK(a.get_vel().y == 7.5f);
  }

  SUBCASE("Testing operator ==")
  {
    pf::Boid a{{3.2f, 9.4f}, {2, 4.8f}};
    pf::Boid b{{3.2f, 9.4f}, {2, 4.8f}};
    pf::Boid c{{6.1f, 134}, {5.4f, 0.4f}};
    pf::Boid d{{3.1f, 9.4f}, {2, 4.8f}};
    CHECK(a == b);
    CHECK(!(a == c));
    CHECK(!(b == d));
  }
}

TEST_CASE("Testing generation of boids")
{
  SUBCASE("Calling generate_flock() with 0 or less boids")
  {
    CHECK_THROWS(pf::generate_flock(0));
    CHECK_THROWS(pf::generate_flock(-2));
    CHECK_THROWS(pf::generate_flock(-46));
    CHECK_THROWS(pf::generate_flock(-57));
    CHECK_THROWS(pf::generate_flock(-1234));
  }

  SUBCASE("Calling generate_flock() with a non integer number of boids")
  {
    CHECK_THROWS(pf::generate_flock(0.5));
    CHECK_THROWS(pf::generate_flock(23.45));
    CHECK_THROWS(pf::generate_flock(-1.4));
    CHECK_THROWS(pf::generate_flock(1234.56));
  }

  SUBCASE("Calling generate_flock() with 5 boids")
  {
    std::vector<pf::Boid> flock_trial = pf::generate_flock(5);
    CHECK(flock_trial.size() == 5);
    CHECK(!(flock_trial[0] == flock_trial[1] && flock_trial[0] == flock_trial[2]
            && flock_trial[0] == flock_trial[3]
            && flock_trial[0] == flock_trial[4]));
    CHECK(!(flock_trial[0].get_pos().x == flock_trial[0].get_pos().y
            && flock_trial[0].get_pos().x == flock_trial[0].get_vel().x
            && flock_trial[0].get_pos().x == flock_trial[0].get_vel().y));
  }

  SUBCASE("Calling generate_flock() with 50 boids")
  {
    std::vector<pf::Boid> flock_trial = pf::generate_flock(50);
    CHECK(flock_trial.size() == 50);
  }
}

TEST_CASE("Testing rules of flight")
{
  SUBCASE("Calling is_in_field_of_view()")
  {
    pf::Boid a1{{0, 0}, {1, 1}};
    pf::Boid b1{{1, 1}, {0, 0}};
    CHECK(is_in_field_of_view(a1, b1, 120.f));
    CHECK(is_in_field_of_view(a1, b1, 60.f));
    pf::Boid a2{{0, 0}, {1, 1}};
    pf::Boid b2{{0, 0}, {2, -1}};
    CHECK(is_in_field_of_view(a2, b2, 120.f) == false);
    CHECK(is_in_field_of_view(a2, b2, 60.f) == false);
    pf::Boid a3{{1, 1}, {1, 1}};
    pf::Boid b3{{-1, 2}, {1, 3}};
    CHECK(is_in_field_of_view(a3, b3, 120.f) == false);
    CHECK(is_in_field_of_view(a3, b3, 60.f) == false);
    CHECK(is_in_field_of_view(a3, b3, 360.f));
    CHECK(is_in_field_of_view(a1, b3, 360.f));
    CHECK(!is_in_field_of_view(a1, b1, 0.f));
    a3 = pf::Boid{{1, 0}, {1, 0}};
    b3 = pf::Boid{{1, 1}, {1, 3}};
    CHECK(is_in_field_of_view(a3, b3, 180.f));
    a3 = pf::Boid{{-1, 0}, {-2, 0}};
    b3 = pf::Boid{{-6, -7}, {2, 3}};
    CHECK(is_in_field_of_view(a3, b3, 180.f));
    a3 = pf::Boid{{0, 0}, {0, 0}};
    b3 = pf::Boid{{1, 1}, {1, 3}};
    CHECK(is_in_field_of_view(a3, b3, 0.f));
    a3 = pf::Boid{{0, 0}, {-1, -1}};
    CHECK(is_in_field_of_view(a3, b3, 360.f));
    CHECK(!is_in_field_of_view(a3, a3, 25.f));
    CHECK(!is_in_field_of_view(a3, a3, 0.f));
    CHECK(!is_in_field_of_view(a3, a3, 360.f));
  }

  std::vector<pf::Boid> flock_trial;
  REQUIRE(flock_trial.size() == 0);

  SUBCASE("Calling separation() with 2 near boids")
  {
    pf::Point2D p1{2, 3};
    pf::Point2D v1{0, 0};
    pf::Point2D p2{4.5f, 7.8f};
    pf::Point2D v2{0, 0};
    pf::Boid b1{p1, v1};
    pf::Boid b2{p2, v2};
    flock_trial.push_back(b1);
    flock_trial.push_back(b2);
    pf::Point2D v3 = separation(flock_trial, flock_trial[0], 0.5f, 10, 360);
    CHECK(v3.x == doctest::Approx(-1.25f));
    CHECK(v3.y == doctest::Approx(-2.4f));
  }

  SUBCASE("Calling separation() with 0 boids")
  {
    pf::Boid b{{2.f, 3.f}, {0.4f, 0.9f}};
    CHECK_THROWS(separation(flock_trial, b, 0.5f, 1, 360));
  }

  SUBCASE("Calling separation() with 1 boid")
  {
    pf::Point2D p1{4.5f, 7.8f};
    pf::Point2D v1{0, 0};
    pf::Boid b1{p1, v1};
    flock_trial.push_back(b1);
    pf::Point2D v_sep = pf::separation(flock_trial, b1, 0.02f, 0.005f, 230);
    CHECK(v_sep.x == doctest::Approx(0.f));
    CHECK(v_sep.y == doctest::Approx(0.f));
  }

  SUBCASE("Calling separation() with 2 near boids, and 2 far boids")
  {
    pf::Point2D p{2, 3};
    pf::Point2D v{0, 0};
    pf::Boid b{p, v};
    flock_trial.push_back(b);
    p = {4.5f, 7.8f};
    b = pf::Boid{p, v};
    flock_trial.push_back(b);
    p = {100, 7.8f};
    b = pf::Boid{p, v};
    flock_trial.push_back(b);
    p = {12, 11.5f};
    b = pf::Boid{p, v};
    flock_trial.push_back(b);
    pf::Point2D v3 = separation(flock_trial, flock_trial[0], 0.5, 10, 360);
    CHECK(v3.x == doctest::Approx(-1.25f));
    CHECK(v3.y == doctest::Approx(-2.4f));
  }

  SUBCASE("Calling separation() with 0 near boids")
  {
    pf::Point2D p{25, 31.2f};
    pf::Point2D v{0, 0};
    pf::Boid b{p, v};
    flock_trial.push_back(b);
    p = {4.5f, 7.8f};
    b = pf::Boid{p, v};
    flock_trial.push_back(b);
    p = {1, 7.8f};
    b = pf::Boid{p, v};
    flock_trial.push_back(b);
    p = {12, 11.5f};
    b = pf::Boid{p, v};
    flock_trial.push_back(b);
    pf::Point2D v3 = separation(flock_trial, flock_trial[0], 0.5f, 10, 360);
    CHECK(v3.x == doctest::Approx(0.f));
    CHECK(v3.y == doctest::Approx(0.f));
  }

  SUBCASE("Calling alignment() with 3 near boids")
  {
    pf::Point2D v1{2, 3};
    pf::Point2D p1{0, 0};
    pf::Point2D v2{0.5f, 6.2f};
    pf::Point2D p2{0, 0};
    pf::Point2D v3{4.5f, 7.8f};
    pf::Point2D p3{0, 0};
    pf::Boid b1{p1, v1};
    pf::Boid b2{p2, v2};
    pf::Boid b3{p3, v3};
    flock_trial.push_back(b1);
    flock_trial.push_back(b2);
    flock_trial.push_back(b3);
    pf::Point2D v4 = alignment(flock_trial, flock_trial[1], 3, 10, 360);
    CHECK(v4.x == doctest::Approx(8.25f));
    CHECK(v4.y == doctest::Approx(-2.4f));
  }

  SUBCASE("Calling alignment() with 0 boids")
  {
    pf::Point2D v1{2, 3};
    pf::Point2D p1{0, 0};
    pf::Boid b{p1, v1};
    CHECK_THROWS(alignment(flock_trial, b, 2, 10, 360));
  }

  SUBCASE("Calling alignment() with 1 boid")
  {
    pf::Point2D p1{4.5f, 7.8f};
    pf::Point2D v1{0, 0};
    pf::Boid b1{p1, v1};
    flock_trial.push_back(b1);
    pf::Point2D v_sep = pf::alignment(flock_trial, b1, 0.02f, 0.005f, 230);
    CHECK(v_sep.x == doctest::Approx(0.f));
    CHECK(v_sep.y == doctest::Approx(0.f));
  }

  SUBCASE("Calling alignment() with 3 near boids and 2 far boids")
  {
    pf::Point2D v{2, 3};
    pf::Point2D p{0, 0};
    flock_trial.push_back(pf::Boid{p, v});
    v = {0.5f, 6.2f};
    flock_trial.push_back(pf::Boid{p, v});
    p = {23, 18};
    v = {23, 18};
    flock_trial.push_back(pf::Boid{p, v});
    p = {0, 1};
    v = {4.5f, 7.8f};
    flock_trial.push_back(pf::Boid{p, v});
    p = {15, 8};
    v = {1.2f, 0.8f};
    flock_trial.push_back(pf::Boid{p, v});
    pf::Point2D v4 = alignment(flock_trial, flock_trial[1], 3, 17, 360);
    CHECK(v4.x == doctest::Approx(8.25f));
    CHECK(v4.y == doctest::Approx(-2.4f));
  }

  SUBCASE("Calling alignment() with 0 near boids")
  {
    pf::Point2D v{2, 3};
    pf::Point2D p{0, 0};
    flock_trial.push_back(pf::Boid{p, v});
    p = {50, 50};
    v = {0.5f, 6.2f};
    flock_trial.push_back(pf::Boid{p, v});
    p = {2, 1};
    v = {23, 18};
    flock_trial.push_back(pf::Boid{p, v});
    v = {4.5f, 7.8f};
    flock_trial.push_back(pf::Boid{p, v});
    v = {1.2f, 0.8f};
    flock_trial.push_back(pf::Boid{p, v});
    pf::Point2D v4 = alignment(flock_trial, flock_trial[1], 3, 17, 360);
    CHECK(v4.x == doctest::Approx(0.f));
    CHECK(v4.y == doctest::Approx(0.f));
  }

  SUBCASE("Calling cohesion() with 3 near boids")
  {
    pf::Point2D p1{2, 3};
    pf::Point2D v1{0, 0};
    pf::Point2D p2{0.5f, 6.2f};
    pf::Point2D v2{0, 0};
    pf::Point2D p3{4.5f, 7.8f};
    pf::Point2D v3{0, 0};
    pf::Boid b1{p1, v1};
    pf::Boid b2{p2, v2};
    pf::Boid b3{p3, v3};
    flock_trial.push_back(b1);
    flock_trial.push_back(b2);
    flock_trial.push_back(b3);
    pf::Point2D v4 = cohesion(flock_trial, flock_trial[0], 0.6f, 11, 360);
    CHECK(v4.x == doctest::Approx(0.3f));
    CHECK(v4.y == doctest::Approx(2.4f));
  }

  SUBCASE("Calling cohesion() with 0 boids")
  {
    pf::Boid b{{2.f, 3.f}, {0.4f, 0.9f}};
    CHECK_THROWS(cohesion(flock_trial, b, 0.2f, 2, 360));
  }

  SUBCASE("Calling cohesion() with 1 boid")
  {
    pf::Point2D p1{4.5f, 7.8f};
    pf::Point2D v1{0, 0};
    pf::Boid b1{p1, v1};
    flock_trial.push_back(b1);
    pf::Point2D v_sep = pf::cohesion(flock_trial, b1, 0.02f, 0.005f, 230);
    CHECK(v_sep.x == doctest::Approx(0.f));
    CHECK(v_sep.y == doctest::Approx(0.f));
  }

  SUBCASE("Calling cohesion() with 3 near boids, and 1 far boid")
  {
    pf::Point2D p{2, 3};
    pf::Point2D v{0, 0};
    flock_trial.push_back(pf::Boid{p, v});
    p = {0.5f, 6.2f};
    flock_trial.push_back(pf::Boid{p, v});
    p = {12, 11.5f};
    flock_trial.push_back(pf::Boid{p, v});
    p = {4.5f, 7.8f};
    flock_trial.push_back(pf::Boid{p, v});
    pf::Point2D v4 = cohesion(flock_trial, flock_trial[0], 0.6f, 9, 360);
    CHECK(v4.x == doctest::Approx(0.3f));
    CHECK(v4.y == doctest::Approx(2.4f));
  }

  SUBCASE("Calling cohesion() with 0 near boids")
  {
    pf::Point2D p{2, 3};
    pf::Point2D v{0, 0};
    flock_trial.push_back(pf::Boid{p, v});
    p = {0.5f, 6.2f};
    flock_trial.push_back(pf::Boid{p, v});
    p = {12, 11.5f};
    flock_trial.push_back(pf::Boid{p, v});
    p = {25, 7.8f};
    flock_trial.push_back(pf::Boid{p, v});
    pf::Point2D v4 = cohesion(flock_trial, flock_trial[3], 0.6f, 8.5f, 360);
    CHECK(v4.x == doctest::Approx(0.f));
    CHECK(v4.y == doctest::Approx(0.f));
  }
}

TEST_CASE("Testing application of the rules of flight")
{
  SUBCASE("Calling movement() with 3 boids")
  {
    pf::Boid b1{{1, 2}, {3, 4}};
    pf::Boid b2{{0.4f, 2}, {0, -0.8f}};
    pf::Boid b3{{5.7f, 3}, {-1, 4}};
    std::vector<pf::Boid> flock_trial{b1, b2, b3};
    pf::movement(flock_trial, 0.5f);
    CHECK(flock_trial[0].get_pos().x == doctest::Approx(2.5f));
    CHECK(flock_trial[0].get_pos().y == doctest::Approx(4.f));
    CHECK(flock_trial[0].get_vel().x == doctest::Approx(3.f));
    CHECK(flock_trial[0].get_vel().y == doctest::Approx(4.f));
    CHECK(flock_trial[1].get_pos().x == doctest::Approx(0.4f));
    CHECK(flock_trial[1].get_pos().y == doctest::Approx(1.6f));
    CHECK(flock_trial[1].get_vel().x == doctest::Approx(0.f));
    CHECK(flock_trial[1].get_vel().y == doctest::Approx(-0.8f));
    CHECK(flock_trial[2].get_pos().x == doctest::Approx(5.2f));
    CHECK(flock_trial[2].get_pos().y == doctest::Approx(5.f));
    CHECK(flock_trial[2].get_vel().x == doctest::Approx(-1.f));
    CHECK(flock_trial[2].get_vel().y == doctest::Approx(4.f));
  }

  SUBCASE("Calling boundary_behavior() with 5 boids")
  {
    pf::Boid b1{{0.2f, 0.5f}, {1, 2}};
    pf::Boid b2{{0.3f, 12}, {1, 2}};
    pf::Boid b3{{2, 0.5f}, {1, 2}};
    pf::Boid b4{{100, 23}, {1, 2}};
    pf::Boid b5{{-2, -3}, {1, 2}};
    std::vector<pf::Boid> flock_trial{b1, b2, b3, b4, b5};
    pf::boundary_behavior(flock_trial);
    CHECK(flock_trial.size() == 5);
    CHECK(flock_trial[0].get_pos().x == 0.2f);
    CHECK(flock_trial[0].get_pos().y == 0.5f);
    CHECK(flock_trial[0].get_vel().x == 1.f);
    CHECK(flock_trial[0].get_vel().y == 2.f);
    CHECK(flock_trial[1].get_pos().x == 0.3f);
    CHECK(flock_trial[1].get_pos().y == 0.f);
    CHECK(flock_trial[1].get_vel().x == 1.f);
    CHECK(flock_trial[1].get_vel().y == 2.f);
    CHECK(flock_trial[2].get_pos().x == 0.f);
    CHECK(flock_trial[2].get_pos().y == 0.5f);
    CHECK(flock_trial[2].get_vel().x == 1.f);
    CHECK(flock_trial[2].get_vel().y == 2.f);
    CHECK(flock_trial[3].get_pos().x == 0.f);
    CHECK(flock_trial[3].get_pos().y == 0.f);
    CHECK(flock_trial[3].get_vel().x == 1.f);
    CHECK(flock_trial[3].get_vel().y == 2.f);
    CHECK(flock_trial[4].get_pos().x == 1.f);
    CHECK(flock_trial[4].get_pos().y == 1.f);
    CHECK(flock_trial[4].get_vel().x == 1.f);
    CHECK(flock_trial[4].get_vel().y == 2.f);
  }

  SUBCASE("Calling flock_trialing_behavior()")
  {
    float d{2};
    float ds{1};
    pf::Boid b1{{1, 2}, {3, 4}};
    pf::Boid b2{{0.4f, 2}, {-7, -0.8f}};
    pf::Boid b3{{5.7f, 3}, {1, 4}};
    pf::Boid b4{{1.3f, 2.7f}, {2.2f, -1}};
    std::vector<pf::Boid> flock_trial{b1, b2, b3, b4};
    float s{0.5f};
    float a{1.2f};
    float c{0.75f};
    pf::flocking_behavior(flock_trial, d, ds, s, a, c, 360);
    CHECK(flock_trial[0].get_pos().x == doctest::Approx(1.f));
    CHECK(flock_trial[0].get_pos().y == doctest::Approx(2.f));
    CHECK(flock_trial[0].get_vel().x == doctest::Approx(-3.4425f));
    CHECK(flock_trial[0].get_vel().y == doctest::Approx(-1.9675f));
    CHECK(flock_trial[1].get_pos().x == doctest::Approx(0.4f));
    CHECK(flock_trial[1].get_pos().y == doctest::Approx(2.f));
    CHECK(flock_trial[1].get_vel().x == doctest::Approx(4.7825f));
    CHECK(flock_trial[1].get_vel().y == doctest::Approx(2.2225f));
    CHECK(flock_trial[2].get_pos().x == doctest::Approx(5.7f));
    CHECK(flock_trial[2].get_pos().y == doctest::Approx(3.f));
    CHECK(flock_trial[2].get_vel().x == doctest::Approx(1.f));
    CHECK(flock_trial[2].get_vel().y == doctest::Approx(4.f));
    CHECK(flock_trial[3].get_pos().x == doctest::Approx(1.3f));
    CHECK(flock_trial[3].get_pos().y == doctest::Approx(2.7f));
    CHECK(flock_trial[3].get_vel().x == doctest::Approx(-3.14f));
    CHECK(flock_trial[3].get_vel().y == doctest::Approx(1.945f));
  }

  SUBCASE("Calling random_boost()")
  {
    pf::Boid b1{{0, 1}, {1, 1}};
    pf::Boid b2{{2, 2}, {-2, 1}};
    pf::Boid b3{{1, 2}, {-2, -2}};
    pf::Boid b4{{2, 3}, {3, -1}};
    pf::Boid b5{{2, 9}, {0, 0}};
    std::vector<pf::Boid> flock_trial{b1, b2, b3, b4, b5};
    float current_angle_b1 = std::atan2(b1.get_vel().y, b1.get_vel().x);
    float current_angle_b2 = std::atan2(b2.get_vel().y, b2.get_vel().x);
    float current_angle_b3 = std::atan2(b3.get_vel().y, b3.get_vel().x);
    float current_angle_b4 = std::atan2(b4.get_vel().y, b4.get_vel().x);
    float current_angle_b5 = std::atan2(b5.get_vel().y, b5.get_vel().x);
    pf::random_boost(flock_trial, 0.1f, 0.01f);
    CHECK(magnitude(flock_trial[0].get_vel()) == doctest::Approx(1.51421f));
    CHECK(current_angle_b1 - (std::atan2(b1.get_vel().y, b1.get_vel().x))
          < (pf::pi_f / 8));
    CHECK(current_angle_b1 - (std::atan2(b1.get_vel().y, b1.get_vel().x))
          > (-pf::pi_f / 8));
    CHECK(magnitude(flock_trial[1].get_vel()) == doctest::Approx(2.33607f));
    CHECK(current_angle_b2 - (std::atan2(b2.get_vel().y, b2.get_vel().x))
          < (pf::pi_f / 8));
    CHECK(current_angle_b2 - (std::atan2(b2.get_vel().y, b2.get_vel().x))
          > (-pf::pi_f / 8));
    CHECK(magnitude(flock_trial[2].get_vel()) == doctest::Approx(2.92843f));
    CHECK(current_angle_b3 - (std::atan2(b3.get_vel().y, b3.get_vel().x))
          < (pf::pi_f / 8));
    CHECK(current_angle_b3 - (std::atan2(b3.get_vel().y, b3.get_vel().x))
          > (-pf::pi_f / 8));
    CHECK(magnitude(flock_trial[3].get_vel()) == doctest::Approx(3.26228f));
    CHECK(current_angle_b4 - (std::atan2(b4.get_vel().y, b4.get_vel().x))
          < (pf::pi_f / 8));
    CHECK(current_angle_b4 - (std::atan2(b4.get_vel().y, b4.get_vel().x))
          > (-pf::pi_f / 8));
    CHECK(magnitude(flock_trial[4].get_vel()) == doctest::Approx(0.1f));
    CHECK(current_angle_b5 - (std::atan2(b5.get_vel().y, b5.get_vel().x))
          < (pf::pi_f / 8));
    CHECK(current_angle_b5 - (std::atan2(b5.get_vel().y, b5.get_vel().x))
          > (-pf::pi_f / 8));
  }

  SUBCASE("Calling speed_control() with 5 boids")
  {
    std::vector<pf::Boid> flock_trial;
    pf::Point2D p{0, 0};
    pf::Point2D v{2, 3};
    flock_trial.push_back(pf::Boid{p, v});
    p = {1, 1};
    v = {0.5f, 1.2f};
    flock_trial.push_back(pf::Boid{p, v});
    v = {2.3f, 1};
    flock_trial.push_back(pf::Boid{p, v});
    p = {2, 1};
    v = {1.5f, 2.8f};
    flock_trial.push_back(pf::Boid{p, v});
    v = {1.2f, 0.8f};
    flock_trial.push_back(pf::Boid{p, v});
    pf::speed_control(flock_trial, 2);
    CHECK(flock_trial.size() == 5);
    CHECK(flock_trial[0].get_pos().x == 0.f);
    CHECK(flock_trial[0].get_pos().y == 0.f);
    CHECK(flock_trial[0].get_vel().x == 2.f);
    CHECK(flock_trial[0].get_vel().y == 2.f);
    CHECK(flock_trial[1].get_pos().x == 1.f);
    CHECK(flock_trial[1].get_pos().y == 1.f);
    CHECK(flock_trial[1].get_vel().x == 0.5f);
    CHECK(flock_trial[1].get_vel().y == 1.2f);
    CHECK(flock_trial[2].get_pos().x == 1.f);
    CHECK(flock_trial[2].get_pos().y == 1.f);
    CHECK(flock_trial[2].get_vel().x == 2.f);
    CHECK(flock_trial[2].get_vel().y == 1.f);
    CHECK(flock_trial[3].get_pos().x == 2.f);
    CHECK(flock_trial[3].get_pos().y == 1.f);
    CHECK(flock_trial[3].get_vel().x == 1.5f);
    CHECK(flock_trial[3].get_vel().y == 2.f);
    CHECK(flock_trial[4].get_pos().x == 2.f);
    CHECK(flock_trial[4].get_pos().y == 1.f);
    CHECK(flock_trial[4].get_vel().x == 1.2f);
    CHECK(flock_trial[4].get_vel().y == 0.8f);
  }

  SUBCASE("Calling flock_trialing_behavior_two_flock_trials()")
  {
    float d{2};
    float ds{1};
    pf::Boid b1{{1, 2}, {3, 4}};
    pf::Boid b2{{0.4f, 2}, {-7, -0.8f}};
    pf::Boid b3{{5.7f, 3}, {1, 4}};
    pf::Boid b4{{1.3f, 2.7f}, {2.2f, -1}};
    std::vector<pf::Boid> flock_trial{b1, b2, b3, b4};
    b1 = pf::Boid{{12, 23}, {1, 2}};
    b2 = pf::Boid{{5.4f, 3.1f}, {0.2f, 1.3f}};
    std::vector<pf::Boid> flock_trial2{b1, b2};
    float s{0.5f};
    float a{1.2f};
    float c{0.75f};
    pf::flocking_behavior_two_flocks(flock_trial, flock_trial2, d, ds, s, a, c,
                                     ds, s, 360);
    CHECK(flock_trial[0].get_pos().x == doctest::Approx(1.f));
    CHECK(flock_trial[0].get_pos().y == doctest::Approx(2.f));
    CHECK(flock_trial[0].get_vel().x == doctest::Approx(-3.4425f));
    CHECK(flock_trial[0].get_vel().y == doctest::Approx(-1.9675f));
    CHECK(flock_trial[1].get_pos().x == doctest::Approx(0.4f));
    CHECK(flock_trial[1].get_pos().y == doctest::Approx(2.f));
    CHECK(flock_trial[1].get_vel().x == doctest::Approx(4.7825f));
    CHECK(flock_trial[1].get_vel().y == doctest::Approx(2.2225f));
    CHECK(flock_trial[2].get_pos().x == doctest::Approx(5.7f));
    CHECK(flock_trial[2].get_pos().y == doctest::Approx(3.f));
    CHECK(flock_trial[2].get_vel().x == doctest::Approx(1.15f));
    CHECK(flock_trial[2].get_vel().y == doctest::Approx(3.95f));
    CHECK(flock_trial[3].get_pos().x == doctest::Approx(1.3f));
    CHECK(flock_trial[3].get_pos().y == doctest::Approx(2.7f));
    CHECK(flock_trial[3].get_vel().x == doctest::Approx(-3.14f));
    CHECK(flock_trial[3].get_vel().y == doctest::Approx(1.945f));
  }
}

TEST_CASE("Testing boids mean parameters")
{
  SUBCASE("Calling mean_position() with 4 boids")
  {
    pf::Boid b1{{0.5f, 0.1f}, {1, 2}};
    pf::Boid b2{{0.9f, 1.4f}, {1, 2}};
    pf::Boid b3{{3, 0.2f}, {1, 2}};
    pf::Boid b4{{2.3f, 1.1f}, {1, 2}};
    std::vector<pf::Boid> flock_trial{b1, b2, b3, b4};
    float mp = pf::mean_position(flock_trial);
    CHECK(mp == doctest::Approx(1.9326f));
  }

  SUBCASE("Calling standdev_position() with 4 boids")
  {
    pf::Boid b1{{0.5f, 0.1f}, {1, 2}};
    pf::Boid b2{{0.9f, 1.4f}, {1, 2}};
    pf::Boid b3{{3, 0.2f}, {1, 2}};
    pf::Boid b4{{2.3f, 1.1f}, {1, 2}};
    std::vector<pf::Boid> flock_trial{b1, b2, b3, b4};
    float sp = pf::standdev_position(flock_trial);
    CHECK(sp == doctest::Approx(1.10003f));
  }

  SUBCASE(
      "Calling mean_position() and standdev_position() with 0, 1 and 2 boids")
  {
    std::vector<pf::Boid> flock_trial;
    REQUIRE(flock_trial.size() == 0);
    CHECK_THROWS(pf::mean_position(flock_trial));
    CHECK_THROWS(pf::standdev_position(flock_trial));
    pf::Boid b1{{1, 2}, {0.3f, 0.8f}};
    flock_trial.push_back(b1);
    CHECK_THROWS(pf::mean_position(flock_trial));
    CHECK_THROWS(pf::standdev_position(flock_trial));
    b1 = pf::Boid{{4.0f, 2.3f}, {0.4f, 0.3f}};
    flock_trial.push_back(b1);
    CHECK_THROWS(pf::mean_position(flock_trial));
    CHECK_THROWS(pf::standdev_position(flock_trial));
  }

  SUBCASE("Calling mean_velocity() with 5 boids")
  {
    pf::Boid b1{{1, 2}, {0.3f, 0.8f}};
    pf::Boid b2{{1, 2}, {2, 4.1f}};
    pf::Boid b3{{1, 2}, {0.2f, 1.1f}};
    pf::Boid b4{{1, 2}, {4, 0.2f}};
    pf::Boid b5{{1, 2}, {0.1f, 0.5f}};
    std::vector<pf::Boid> flock_trial{b1, b2, b3, b4, b5};
    float mv = pf::mean_velocity(flock_trial);
    CHECK(mv == doctest::Approx(2.2098262f));
  }

  SUBCASE("Calling standdev_velocity() with 5 boids")
  {
    pf::Boid b1{{1, 2}, {0.3f, 0.8f}};
    pf::Boid b2{{1, 2}, {2, 4.1f}};
    pf::Boid b3{{1, 2}, {0.2f, 1.1f}};
    pf::Boid b4{{1, 2}, {4, 0.2f}};
    pf::Boid b5{{1, 2}, {0.1f, 0.5f}};
    std::vector<pf::Boid> flock_trial{b1, b2, b3, b4, b5};
    float sv = pf::standdev_velocity(flock_trial);
    CHECK(sv == doctest::Approx(1.91529f));
  }

  SUBCASE(
      "Calling mean_velocity() and standdev_velocity() with 0, 1 and 2 boids")
  {
    std::vector<pf::Boid> flock_trial;
    REQUIRE(flock_trial.size() == 0);
    CHECK_THROWS(pf::mean_velocity(flock_trial));
    CHECK_THROWS(pf::standdev_velocity(flock_trial));
    pf::Boid b1{{1, 2}, {0.3f, 0.8f}};
    flock_trial.push_back(b1);
    CHECK_THROWS(pf::mean_velocity(flock_trial));
    CHECK_THROWS(pf::standdev_velocity(flock_trial));
    b1 = pf::Boid{{4.0f, 2.3f}, {0.4f, 0.3f}};
    flock_trial.push_back(b1);
    CHECK_THROWS(pf::mean_velocity(flock_trial));
    CHECK_THROWS(pf::standdev_velocity(flock_trial));
  }

  SUBCASE("Calling mean_distance() with 4 boids")
  {
    pf::Boid b1{{0.5f, 0.1f}, {1, 2}};
    pf::Boid b2{{0.9f, 1.4f}, {1, 2}};
    pf::Boid b3{{3, 0.2f}, {1, 2}};
    pf::Boid b4{{2.3f, 1.1f}, {1, 2}};
    std::vector<pf::Boid> flock_trial{b1, b2, b3, b4};
    float md = pf::mean_distance(flock_trial);
    CHECK(md == doctest::Approx(1.81865f));
  }

  SUBCASE("Calling standdev_distance() with 4 boids")
  {
    pf::Boid b1{{0.5f, 0.1f}, {1, 2}};
    pf::Boid b2{{0.9f, 1.4f}, {1, 2}};
    pf::Boid b3{{3, 0.2f}, {1, 2}};
    pf::Boid b4{{2.3f, 1.1f}, {1, 2}};
    std::vector<pf::Boid> flock_trial{b1, b2, b3, b4};
    float sd = pf::standdev_distance(flock_trial);
    CHECK(sd == doctest::Approx(0.58396f));
  }

  SUBCASE(
      "Calling mean_distance() and standdev_distance() with 0, 1 and 2 boids")
  {
    std::vector<pf::Boid> flock_trial;
    REQUIRE(flock_trial.size() == 0);
    CHECK_THROWS(pf::mean_distance(flock_trial));
    CHECK_THROWS(pf::standdev_distance(flock_trial));
    pf::Boid b1{{1, 2}, {0.3f, 0.8f}};
    flock_trial.push_back(b1);
    CHECK_THROWS(pf::mean_distance(flock_trial));
    CHECK_THROWS(pf::standdev_distance(flock_trial));
    b1 = pf::Boid{{4.0f, 2.3f}, {0.4f, 0.3f}};
    flock_trial.push_back(b1);
    CHECK_THROWS(pf::mean_distance(flock_trial));
    CHECK_THROWS(pf::standdev_distance(flock_trial));
  }
}

TEST_CASE("Testing functions useful to make the graphic part")
{
  std::vector<pf::Boid> flock_trial;
  REQUIRE(flock_trial.size() == 0);

  SUBCASE("Calling real_to_pixel()")
  {
    sf::Vector2f vect = pf::real_to_pixel(0.345f, 0.827f, 451.f, 765.43f);
    CHECK(vect.x == doctest::Approx(155.595f));
    CHECK(vect.y == doctest::Approx(633.01061f));
  }

  SUBCASE("Calling calculate_rotation_angle()")
  {
    float ang = pf::calculate_rotation_angle(0.2f, 0.56f);
    CHECK(ang == doctest::Approx(70.34618));
  }

  SUBCASE("Calling set_graph_point()")
  {
    sf::Vector2f point = pf::set_graph_point(2, 0.4f, 5, 300.f, 200.f, 1.2f);
    CHECK(point.x == doctest::Approx(120.f));
    CHECK(point.y == doctest::Approx(133.3333333f));
  }
}