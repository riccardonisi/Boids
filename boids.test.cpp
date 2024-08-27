#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "statistics.hpp"

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

  SUBCASE("Testing distanza() function")
  {
    pf::Point2D a{2, 5};
    pf::Point2D b{0.3f, 6.8f};
    pf::Point2D c{-15, 100};
    CHECK(pf::distanza(a, b) == doctest::Approx(2.47589f));
    CHECK(pf::distanza(b, c) == doctest::Approx(94.4475f));
    CHECK(pf::distanza(a, c) == doctest::Approx(96.5091f));
  }

  SUBCASE("Testing lunghezza() function")
  {
    pf::Point2D a{1, 2};
    pf::lunghezza(a);
    CHECK(pf::lunghezza(a) == doctest::Approx(2.23607f));
    pf::Point2D b{0, 0};
    pf::lunghezza(b);
    CHECK(pf::lunghezza(b) == doctest::Approx(0.f));
    pf::Point2D c{-2, -5};
    pf::lunghezza(c);
    CHECK(pf::lunghezza(c) == doctest::Approx(5.38516f));
  }

  SUBCASE("Testing normalizzazione() function")
  {
    pf::Point2D a{2, 3};
    pf::normalizzazione(a);
    CHECK(pf::normalizzazione(a).x == doctest::Approx(0.55470f));
    CHECK(pf::normalizzazione(a).y == doctest::Approx(0.83205f));
    CHECK(pf::lunghezza(normalizzazione(a)) == doctest::Approx(0.99999f));
    pf::Point2D b{-3, -1};
    pf::normalizzazione(b);
    CHECK(pf::normalizzazione(b).x == doctest::Approx(-0.94868f));
    CHECK(pf::normalizzazione(b).y == doctest::Approx(-0.31623f));
    CHECK(pf::lunghezza(normalizzazione(b)) == doctest::Approx(0.99999f));
    pf::Point2D c{0, 0};
    CHECK(pf::normalizzazione(c).x == doctest::Approx(0.f));
    CHECK(pf::normalizzazione(c).y == doctest::Approx(0.f));
    CHECK(pf::lunghezza(normalizzazione(c)) == doctest::Approx(0.f));
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
    a.set_pos(pf::Point2D{2.3f, 4.5f});
    CHECK(a.get_pos().x == 2.3f);
    CHECK(a.get_pos().y == 4.5f);
    CHECK(a.get_vel().x == 2.0f);
    CHECK(a.get_vel().y == 4.8f);
    a.set_vel(pf::Point2D{3.1f, 7.5f});
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

TEST_CASE("Testing rules of flight")
{
  std::vector<pf::Boid> prova;
  REQUIRE(prova.size() == 0);

  SUBCASE("Calling separazione() with 2 near boids")
  {
    pf::Point2D p1{2, 3};
    pf::Point2D v1{0, 0};
    pf::Point2D p2{4.5f, 7.8f};
    pf::Point2D v2{0, 0};
    pf::Boid b1{p1, v1};
    pf::Boid b2{p2, v2};
    prova.push_back(b1);
    prova.push_back(b2);
    pf::Point2D v3 = separazione(prova, 0, 0.5f, 10, 360);
    CHECK(v3.x == doctest::Approx(-1.25f));
    CHECK(v3.y == doctest::Approx(-2.4f));
  }

  SUBCASE("Calling separazione() with 0 boids")
  {
    CHECK_THROWS(separazione(prova, 0, 0.5f, 1, 360));
  }

  SUBCASE("Calling separazione() with 1 boid")
  {
    pf::Point2D p1{4.5f, 7.8f};
    pf::Point2D v1{0, 0};
    pf::Boid b1{p1, v1};
    prova.push_back(b1);
    CHECK_THROWS(separazione(prova, 0, 0.5f, 12, 360));
  }

  SUBCASE("Calling separazione() with 2 near boids, and 2 far boids")
  {
    pf::Point2D p{2, 3};
    pf::Point2D v{0, 0};
    pf::Boid b{p, v};
    prova.push_back(b);
    p = {4.5f, 7.8f};
    b = pf::Boid{p, v};
    prova.push_back(b);
    p = {100, 7.8f};
    b = pf::Boid{p, v};
    prova.push_back(b);
    p = {12, 11.5f};
    b = pf::Boid{p, v};
    prova.push_back(b);
    pf::Point2D v3 = separazione(prova, 0, 0.5, 10, 360);
    CHECK(v3.x == doctest::Approx(-1.25f));
    CHECK(v3.y == doctest::Approx(-2.4f));
  }

  SUBCASE("Calling separazione() with 0 near boids")
  {
    pf::Point2D p{25, 31.2f};
    pf::Point2D v{0, 0};
    pf::Boid b{p, v};
    prova.push_back(b);
    p = {4.5f, 7.8f};
    b = pf::Boid{p, v};
    prova.push_back(b);
    p = {1, 7.8f};
    b = pf::Boid{p, v};
    prova.push_back(b);
    p = {12, 11.5f};
    b = pf::Boid{p, v};
    prova.push_back(b);
    pf::Point2D v3 = separazione(prova, 0, 0.5f, 10, 360);
    CHECK(v3.x == doctest::Approx(0.f));
    CHECK(v3.y == doctest::Approx(0.f));
  }

  SUBCASE("Calling allineamento() with 3 near boids")
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
    prova.push_back(b1);
    prova.push_back(b2);
    prova.push_back(b3);
    pf::Point2D v4 = allineamento(prova, 1, 3, 10, 360);
    CHECK(v4.x == doctest::Approx(8.25f));
    CHECK(v4.y == doctest::Approx(-2.4f));
  }

  SUBCASE("Calling allineamento() with 0 boids")
  {
    CHECK_THROWS(allineamento(prova, 0, 2, 10, 360));
  }

  SUBCASE("Calling allineamento() with 1 boid")
  {
    pf::Point2D v1{4.5f, 7.8f};
    pf::Point2D p1{0, 0};
    pf::Boid b1{p1, v1};
    prova.push_back(b1);
    CHECK_THROWS(allineamento(prova, 0, 2, 20, 360));
  }

  SUBCASE("Calling allineamento() with 3 near boids and 2 far boids")
  {
    pf::Point2D v{2, 3};
    pf::Point2D p{0, 0};
    prova.push_back(pf::Boid{p, v});
    v = {0.5f, 6.2f};
    prova.push_back(pf::Boid{p, v});
    p = {23, 18};
    v = {23, 18};
    prova.push_back(pf::Boid{p, v});
    p = {0, 1};
    v = {4.5f, 7.8f};
    prova.push_back(pf::Boid{p, v});
    p = {15, 8};
    v = {1.2f, 0.8f};
    prova.push_back(pf::Boid{p, v});
    pf::Point2D v4 = allineamento(prova, 1, 3, 17, 360);
    CHECK(v4.x == doctest::Approx(8.25f));
    CHECK(v4.y == doctest::Approx(-2.4f));
  }

  SUBCASE("Calling allineamento() with 0 near boids")
  {
    pf::Point2D v{2, 3};
    pf::Point2D p{0, 0};
    prova.push_back(pf::Boid{p, v});
    p = {50, 50};
    v = {0.5f, 6.2f};
    prova.push_back(pf::Boid{p, v});
    p = {2, 1};
    v = {23, 18};
    prova.push_back(pf::Boid{p, v});
    v = {4.5f, 7.8f};
    prova.push_back(pf::Boid{p, v});
    v = {1.2f, 0.8f};
    prova.push_back(pf::Boid{p, v});
    pf::Point2D v4 = allineamento(prova, 1, 3, 17, 360);
    CHECK(v4.x == doctest::Approx(0.f));
    CHECK(v4.y == doctest::Approx(0.f));
  }

  SUBCASE("Calling coesione() with 3 near boids")
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
    prova.push_back(b1);
    prova.push_back(b2);
    prova.push_back(b3);
    pf::Point2D v4 = coesione(prova, 0, 0.6f, 11, 360);
    CHECK(v4.x == doctest::Approx(0.3f));
    CHECK(v4.y == doctest::Approx(2.4f));
  }

  SUBCASE("Calling coesione() with 0 boids")
  {
    CHECK_THROWS(coesione(prova, 0, 0.2f, 2, 360));
  }

  SUBCASE("Calling coesione() with 1 boid")
  {
    pf::Point2D p1{4.5f, 7};
    pf::Point2D v1{0, 0};
    pf::Boid b1{p1, v1};
    prova.push_back(b1);
    CHECK_THROWS(coesione(prova, 0, 2, 10, 360));
  }

  SUBCASE("Calling coesione() with 3 near boids, and 1 far boid")
  {
    pf::Point2D p{2, 3};
    pf::Point2D v{0, 0};
    prova.push_back(pf::Boid{p, v});
    p = {0.5f, 6.2f};
    prova.push_back(pf::Boid{p, v});
    p = {12, 11.5f};
    prova.push_back(pf::Boid{p, v});
    p = {4.5f, 7.8f};
    prova.push_back(pf::Boid{p, v});
    pf::Point2D v4 = coesione(prova, 0, 0.6f, 9, 360);
    CHECK(v4.x == doctest::Approx(0.3f));
    CHECK(v4.y == doctest::Approx(2.4f));
  }

  SUBCASE("Calling coesione() with 0 near boids")
  {
    pf::Point2D p{2, 3};
    pf::Point2D v{0, 0};
    prova.push_back(pf::Boid{p, v});
    p = {0.5f, 6.2f};
    prova.push_back(pf::Boid{p, v});
    p = {12, 11.5f};
    prova.push_back(pf::Boid{p, v});
    p = {25, 7.8f};
    prova.push_back(pf::Boid{p, v});
    pf::Point2D v4 = coesione(prova, 3, 0.6f, 8.5f, 360);
    CHECK(v4.x == doctest::Approx(0.f));
    CHECK(v4.y == doctest::Approx(0.f));
  }
}

TEST_CASE("Testing generation of boids")
{
  SUBCASE("Calling genera_stormo() with 0 or less boids")
  {
    CHECK_THROWS(pf::genera_stormo(0));
    CHECK_THROWS(pf::genera_stormo(-2));
    CHECK_THROWS(pf::genera_stormo(-46));
    CHECK_THROWS(pf::genera_stormo(-57));
    CHECK_THROWS(pf::genera_stormo(-1234));
  }

  /*SUBCASE("Calling genera_stormo() with a non integer number of boids")
  {
    CHECK_THROWS(pf::genera_stormo(0.5f));
    CHECK_THROWS(pf::genera_stormo(23.45f));
    CHECK_THROWS(pf::genera_stormo(-1.4f));
    CHECK_THROWS(pf::genera_stormo(1234.56f));
  }*/

  SUBCASE("Calling genera_stormo() with 5 boids")
  {
    std::vector<pf::Boid> prova = pf::genera_stormo(5);
    CHECK(prova.size() == 5);
    CHECK(!(prova[0] == prova[1] && prova[0] == prova[2] && prova[0] == prova[3]
            && prova[0] == prova[4]));
    CHECK(!(prova[0].get_pos().x == prova[0].get_pos().y
            && prova[0].get_pos().x == prova[0].get_vel().x
            && prova[0].get_pos().x == prova[0].get_vel().y));
  }

  SUBCASE("Calling genera_stormo() with 50 boids")
  {
    std::vector<pf::Boid> prova = pf::genera_stormo(50);
    CHECK(prova.size() == 50);
  }

  /*SUBCASE("Calling boid_vicini() with 10 boids")
  {
    float dist{2};
    pf::Boid a{{1, 2}, {3, 4}};
    pf::Boid b{{0.4, 2}, {7, 10}};
    pf::Boid c{{5.7, 3}, {3, 4}};
    pf::Boid d{{0.15, 23}, {3, 4}};
    pf::Boid e{{3, 2}, {3, 4}};
    pf::Boid f{{5.3, 1.1}, {3, 4}};
    pf::Boid g{{1.3, 2.7}, {3, 4}};
    pf::Boid h{{1.8, 3.1}, {3, 4}};
    pf::Boid i{{1.4, 2.56}, {3, 4}};
    pf::Boid l{{1, 2}, {3, 4}};
    std::vector<pf::Boid> stormo{a, b, c, d, e, f, g, h, i, l};
    std::vector<pf::Boid> stormo_vicino = boid_vicini(stormo, 0, dist);
    CHECK(stormo_vicino.size() == 5);
    CHECK(stormo_vicino[0] == b);
    CHECK(stormo_vicino[1] == g);
    CHECK(stormo_vicino[2] == h);
    CHECK(stormo_vicino[3] == i);
    CHECK(stormo_vicino[4] == l);
  }*/
}

TEST_CASE("Testing application of the rules of flight")
{
  SUBCASE("Calling applicazione_regole()")
  {
    float d{2};
    float ds{1};
    pf::Boid b1{{1, 2}, {3, 4}};
    pf::Boid b2{{0.4f, 2}, {-7, -0.8f}};
    pf::Boid b3{{5.7f, 3}, {1, 4}};
    pf::Boid b4{{1.3f, 2.7f}, {2.2f, -1}};
    std::vector<pf::Boid> stormo{b1, b2, b3, b4};
    float s{0.5f};
    float a{1.2f};
    float c{0.75f};
    pf::applicazione_regole(stormo, d, ds, s, a, c, 360);
    CHECK(stormo[0].get_pos().x == doctest::Approx(1.f));
    CHECK(stormo[0].get_pos().y == doctest::Approx(2.f));
    CHECK(stormo[0].get_vel().x == doctest::Approx(-3.4425f));
    CHECK(stormo[0].get_vel().y == doctest::Approx(-1.9675f));
    CHECK(stormo[1].get_pos().x == doctest::Approx(0.4f));
    CHECK(stormo[1].get_pos().y == doctest::Approx(2.f));
    CHECK(stormo[1].get_vel().x == doctest::Approx(4.7825f));
    CHECK(stormo[1].get_vel().y == doctest::Approx(2.2225f));
    CHECK(stormo[2].get_pos().x == doctest::Approx(5.7f));
    CHECK(stormo[2].get_pos().y == doctest::Approx(3.f));
    CHECK(stormo[2].get_vel().x == doctest::Approx(1.f));
    CHECK(stormo[2].get_vel().y == doctest::Approx(4.f));
    CHECK(stormo[3].get_pos().x == doctest::Approx(1.3f));
    CHECK(stormo[3].get_pos().y == doctest::Approx(2.7f));
    CHECK(stormo[3].get_vel().x == doctest::Approx(-3.14f));
    CHECK(stormo[3].get_vel().y == doctest::Approx(1.945f));
  }

  SUBCASE("Calling movimento() with 3 boids")
  {
    pf::Boid b1{{1, 2}, {3, 4}};
    pf::Boid b2{{0.4f, 2}, {0, -0.8f}};
    pf::Boid b3{{5.7f, 3}, {-1, 4}};
    std::vector<pf::Boid> stormo{b1, b2, b3};
    pf::movimento(stormo, 0.5f);
    CHECK(stormo[0].get_pos().x == doctest::Approx(2.5f));
    CHECK(stormo[0].get_pos().y == doctest::Approx(4.f));
    CHECK(stormo[0].get_vel().x == doctest::Approx(3.f));
    CHECK(stormo[0].get_vel().y == doctest::Approx(4.f));
    CHECK(stormo[1].get_pos().x == doctest::Approx(0.4f));
    CHECK(stormo[1].get_pos().y == doctest::Approx(1.6f));
    CHECK(stormo[1].get_vel().x == doctest::Approx(0.f));
    CHECK(stormo[1].get_vel().y == doctest::Approx(-0.8f));
    CHECK(stormo[2].get_pos().x == doctest::Approx(5.2f));
    CHECK(stormo[2].get_pos().y == doctest::Approx(5.f));
    CHECK(stormo[2].get_vel().x == doctest::Approx(-1.f));
    CHECK(stormo[2].get_vel().y == doctest::Approx(4.f));
  }

  SUBCASE("Calling comportamento_bordi() with 5 boids")
  {
    pf::Boid b1{{0.2f, 0.5f}, {1, 2}};
    pf::Boid b2{{0.3f, 12}, {1, 2}};
    pf::Boid b3{{2, 0.5f}, {1, 2}};
    pf::Boid b4{{100, 23}, {1, 2}};
    pf::Boid b5{{-2, -3}, {1, 2}};
    std::vector<pf::Boid> stormo{b1, b2, b3, b4, b5};
    pf::comportamento_bordi(stormo);
    CHECK(stormo.size() == 5);
    CHECK(stormo[0].get_pos().x == 0.2f);
    CHECK(stormo[0].get_pos().y == 0.5f);
    CHECK(stormo[0].get_vel().x == 1.f);
    CHECK(stormo[0].get_vel().y == 2.f);
    CHECK(stormo[1].get_pos().x == 0.3f);
    CHECK(stormo[1].get_pos().y == 0.f);
    CHECK(stormo[1].get_vel().x == 1.f);
    CHECK(stormo[1].get_vel().y == 2.f);
    CHECK(stormo[2].get_pos().x == 0.f);
    CHECK(stormo[2].get_pos().y == 0.5f);
    CHECK(stormo[2].get_vel().x == 1.f);
    CHECK(stormo[2].get_vel().y == 2.f);
    CHECK(stormo[3].get_pos().x == 0.f);
    CHECK(stormo[3].get_pos().y == 0.f);
    CHECK(stormo[3].get_vel().x == 1.f);
    CHECK(stormo[3].get_vel().y == 2.f);
    CHECK(stormo[4].get_pos().x == 1.f);
    CHECK(stormo[4].get_pos().y == 1.f);
    CHECK(stormo[4].get_vel().x == 1.f);
    CHECK(stormo[4].get_vel().y == 2.f);
  }

  SUBCASE("Calling controllo_velocità() with 5 boids")
  {
    std::vector<pf::Boid> stormo;
    pf::Point2D p{0, 0};
    pf::Point2D v{2, 3};
    stormo.push_back(pf::Boid{p, v});
    p = {1, 1};
    v = {0.5f, 1.2f};
    stormo.push_back(pf::Boid{p, v});
    v = {2.3f, 1};
    stormo.push_back(pf::Boid{p, v});
    p = {2, 1};
    v = {1.5f, 2.8f};
    stormo.push_back(pf::Boid{p, v});
    v = {1.2f, 0.8f};
    stormo.push_back(pf::Boid{p, v});
    pf::controllo_velocità(stormo, 2);
    CHECK(stormo.size() == 5);
    CHECK(stormo[0].get_pos().x == 0.f);
    CHECK(stormo[0].get_pos().y == 0.f);
    CHECK(stormo[0].get_vel().x == 2.f);
    CHECK(stormo[0].get_vel().y == 2.f);
    CHECK(stormo[1].get_pos().x == 1.f);
    CHECK(stormo[1].get_pos().y == 1.f);
    CHECK(stormo[1].get_vel().x == 0.5f);
    CHECK(stormo[1].get_vel().y == 1.2f);
    CHECK(stormo[2].get_pos().x == 1.f);
    CHECK(stormo[2].get_pos().y == 1.f);
    CHECK(stormo[2].get_vel().x == 2.f);
    CHECK(stormo[2].get_vel().y == 1.f);
    CHECK(stormo[3].get_pos().x == 2.f);
    CHECK(stormo[3].get_pos().y == 1.f);
    CHECK(stormo[3].get_vel().x == 1.5f);
    CHECK(stormo[3].get_vel().y == 2.f);
    CHECK(stormo[4].get_pos().x == 2.f);
    CHECK(stormo[4].get_pos().y == 1.f);
    CHECK(stormo[4].get_vel().x == 1.2f);
    CHECK(stormo[4].get_vel().y == 0.8f);
  }

  SUBCASE("Calling campo_visivo()")
  {
    pf::Boid a1{{0, 0}, {1, 1}};
    pf::Boid b1{{1, 1}, {0, 0}};
    float angolo1 = 120.0f;
    float angolo2 = 60.0f;
    CHECK(campo_visivo(a1, b1, angolo1));
    CHECK(campo_visivo(a1, b1, angolo2));
    pf::Boid a2{{0, 0}, {1, 1}};
    pf::Boid b2{{0, 0}, {2, -1}};
    CHECK(campo_visivo(a2, b2, angolo1) == false);
    CHECK(campo_visivo(a2, b2, angolo2) == false);
    pf::Boid a3{{1, 1}, {1, 1}};
    pf::Boid b3{{-1, 2}, {1, 3}};
    CHECK(campo_visivo(a3, b3, angolo1) == false);
    CHECK(campo_visivo(a3, b3, angolo2) == false);
    float angolo3{360.0f};
    CHECK(campo_visivo(a3, b3, angolo3));
    CHECK(campo_visivo(a1, b3, angolo3));
    // float angolo4{0};
    //  CHECK(campo_visivo(a1, b1, angolo4));
    a3      = pf::Boid{{1, 0}, {1, 0}};
    b3      = pf::Boid{{1, 1}, {1, 3}};
    angolo3 = 180.0;
    CHECK(campo_visivo(a3, b3, angolo3));
    a3 = pf::Boid{{-1, 0}, {-2, 0}};
    b3 = pf::Boid{{-6, -7}, {2, 3}};
    CHECK(campo_visivo(a3, b3, angolo3));
    a3 = pf::Boid{{0, 0}, {0, 0}};
    b3 = pf::Boid{{1, 1}, {1, 3}};
    // CHECK(campo_visivo(a3, b3, angolo4));
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
    std::vector<pf::Boid> prova{b1, b2, b3, b4};
    float mp = pf::mean_position(prova);
    CHECK(mp == doctest::Approx(1.9326f));
  }

  SUBCASE("Calling standdev_position() with 4 boids")
  {
    pf::Boid b1{{0.5f, 0.1f}, {1, 2}};
    pf::Boid b2{{0.9f, 1.4f}, {1, 2}};
    pf::Boid b3{{3, 0.2f}, {1, 2}};
    pf::Boid b4{{2.3f, 1.1f}, {1, 2}};
    std::vector<pf::Boid> prova{b1, b2, b3, b4};
    float sp = pf::standdev_position(prova);
    CHECK(sp == doctest::Approx(1.10003f));
  }

  SUBCASE(
      "Calling mean_position() and standdev_position() with 0, 1 and 2 boids")
  {
    pf::Boid b1{{1, 2}, {0.3f, 0.8f}};
    std::vector<pf::Boid> prova{b1};
    CHECK_THROWS(pf::mean_position(prova));
    CHECK_THROWS(pf::standdev_position(prova));
    b1 = pf::Boid{{4.0, 2.3}, {0.4f, 0.3f}};
    prova.push_back(b1);
    CHECK_THROWS(pf::mean_position(prova));
    CHECK_THROWS(pf::standdev_position(prova));
    b1 = pf::Boid{{2.1, 3.3}, {0.3f, 2.f}};
    prova.push_back(b1);
    CHECK_THROWS(pf::mean_position(prova));
    CHECK_THROWS(pf::standdev_position(prova));
  }

  SUBCASE("Calling mean_velocity() with 5 boids")
  {
    pf::Boid b1{{1, 2}, {0.3f, 0.8f}};
    pf::Boid b2{{1, 2}, {2, 4.1f}};
    pf::Boid b3{{1, 2}, {0.2f, 1.1f}};
    pf::Boid b4{{1, 2}, {4, 0.2f}};
    pf::Boid b5{{1, 2}, {0.1f, 0.5f}};
    std::vector<pf::Boid> prova{b1, b2, b3, b4, b5};
    float mv = pf::mean_velocity(prova);
    CHECK(mv == doctest::Approx(2.2098262f));
  }

  SUBCASE("Calling standdev_velocity() with 5 boids")
  {
    pf::Boid b1{{1, 2}, {0.3f, 0.8f}};
    pf::Boid b2{{1, 2}, {2, 4.1f}};
    pf::Boid b3{{1, 2}, {0.2f, 1.1f}};
    pf::Boid b4{{1, 2}, {4, 0.2f}};
    pf::Boid b5{{1, 2}, {0.1f, 0.5f}};
    std::vector<pf::Boid> prova{b1, b2, b3, b4, b5};
    float sv = pf::standdev_velocity(prova);
    CHECK(sv == doctest::Approx(1.91529f));
  }

  SUBCASE(
      "Calling mean_velocity() and standdev_velocity() with 0, 1 and 2 boids")
  {
    pf::Boid b1{{1, 2}, {0.3f, 0.8f}};
    std::vector<pf::Boid> prova{b1};
    CHECK_THROWS(pf::mean_velocity(prova));
    CHECK_THROWS(pf::standdev_velocity(prova));
    b1 = pf::Boid{{4.0, 2.3}, {0.4f, 0.3f}};
    prova.push_back(b1);
    CHECK_THROWS(pf::mean_velocity(prova));
    CHECK_THROWS(pf::standdev_velocity(prova));
    b1 = pf::Boid{{4.3, 2}, {1.2, 5}};
    prova.push_back(b1);
    CHECK_THROWS(pf::mean_velocity(prova));
    CHECK_THROWS(pf::standdev_velocity(prova));
  }

  SUBCASE("Calling mean_distance() with 4 boids")
  {
    pf::Boid b1{{0.5f, 0.1f}, {1, 2}};
    pf::Boid b2{{0.9f, 1.4f}, {1, 2}};
    pf::Boid b3{{3, 0.2f}, {1, 2}};
    pf::Boid b4{{2.3f, 1.1f}, {1, 2}};
    std::vector<pf::Boid> prova{b1, b2, b3, b4};
    float md = pf::mean_distance(prova);
    CHECK(md == doctest::Approx(1.81865f));
  }

  SUBCASE("Calling standdev_distance() with 4 boids")
  {
    pf::Boid b1{{0.5f, 0.1f}, {1, 2}};
    pf::Boid b2{{0.9f, 1.4f}, {1, 2}};
    pf::Boid b3{{3, 0.2f}, {1, 2}};
    pf::Boid b4{{2.3f, 1.1f}, {1, 2}};
    std::vector<pf::Boid> prova{b1, b2, b3, b4};
    float sd = pf::standdev_distance(prova);
    CHECK(sd == doctest::Approx(0.58396f));
  }

  SUBCASE("Calling standdev_distance() with 2 boids")
  {
    pf::Boid b1{{0.5f, 0.1f}, {1, 2}};
    pf::Boid b2{{0.9f, 1.4f}, {1, 2}};
    std::vector<pf::Boid> prova{b1, b2};
    float sd = pf::standdev_distance(prova);
    CHECK(sd == doctest::Approx(0.58396f));
  }

  SUBCASE(
      "Calling mean_distance() and standdev_distance() with 0, 1 and 2 boids")
  {
    pf::Boid b1{{1, 2}, {0.3f, 0.8f}};
    std::vector<pf::Boid> prova{b1};
    CHECK_THROWS(pf::mean_distance(prova));
    CHECK_THROWS(pf::standdev_distance(prova));
    b1 = pf::Boid{{4.0, 2.3}, {0.4f, 0.3f}};
    prova.push_back(b1);
    CHECK_THROWS(pf::mean_distance(prova));
    CHECK_THROWS(pf::standdev_distance(prova));
    b1 = pf::Boid{{1.0, 6.3}, {0.45f, 0.6f}};
    prova.push_back(b1);
    CHECK_THROWS(pf::mean_distance(prova));
    CHECK_THROWS(pf::standdev_distance(prova));
  }
}

TEST_CASE("Testing rules of flight with 2 storms")
{
  std::vector<pf::Boid> prova;
  REQUIRE(prova.size() == 0);

  SUBCASE("Calling separazione_altro_stormo() with 1 near boid and 1 far boid")
  {
    pf::Point2D p1{2, 3};
    pf::Point2D v1{0, 0};
    pf::Boid b1{p1, v1};
    pf::Point2D p2{4.5f, 7.8f};
    pf::Point2D v2{0, 0};
    pf::Boid b2{p2, v2};
    prova.push_back(b2);
    p2 = {11, 7.8f};
    v2 = {0, 0};
    b2 = pf::Boid{p2, v2};
    prova.push_back(b2);
    pf::Point2D v3 = pf::separazione_altro_stormo(prova, b1, 0.5f, 10, 360);
    CHECK(v3.x == doctest::Approx(-1.25f));
    CHECK(v3.y == doctest::Approx(-2.4f));
  }

  SUBCASE("Calling separazione_altro_stormo() with 0 boids")
  {
    pf::Point2D p1{2, 3};
    pf::Point2D v1{0, 0};
    pf::Boid b1{p1, v1};
    CHECK_THROWS(separazione_altro_stormo(prova, b1, 0.5f, 1, 360));
  }

  SUBCASE("Calling separazione_altro_stormo() with 1 boid")
  {
    pf::Point2D p1{4.5f, 7.8f};
    pf::Point2D v1{0, 0};
    pf::Boid b1{p1, v1};
    prova.push_back(b1);
    pf::Point2D p2{2, 3};
    pf::Point2D v2{0, 0};
    pf::Boid b2{p2, v2};
    CHECK_THROWS(separazione_altro_stormo(prova, b2, 0.5f, 12, 360));
  }

  SUBCASE("Calling separazione_altro_stormo() with 1 near boid and 2 far boids")
  {
    pf::Point2D p{4.5f, 7.8f};
    pf::Point2D v{0, 0};
    pf::Boid b{p, v};
    prova.push_back(b);
    p = {100, 7.8f};
    b = pf::Boid{p, v};
    prova.push_back(b);
    p = {12, 11.5f};
    b = pf::Boid{p, v};
    prova.push_back(b);
    p              = {2, 3};
    b              = pf::Boid{p, v};
    pf::Point2D v3 = separazione_altro_stormo(prova, b, 0.5f, 10, 360);
    CHECK(v3.x == doctest::Approx(-1.25f));
    CHECK(v3.y == doctest::Approx(-2.4f));
  }

  SUBCASE("Calling separazione_altro_stormo() with 0 near boids")
  {
    pf::Point2D p{4.5f, 7.8f};
    pf::Point2D v{0, 0};
    pf::Boid b{p, v};
    prova.push_back(b);
    p = {1, 7.8f};
    b = pf::Boid{p, v};
    prova.push_back(b);
    p = {12, 11.5f};
    b = pf::Boid{p, v};
    prova.push_back(b);
    p              = {20, 18.3f};
    b              = pf::Boid{p, v};
    pf::Point2D v3 = separazione_altro_stormo(prova, b, 0.5f, 10, 360);
    CHECK(v3.x == doctest::Approx(0.f));
    CHECK(v3.y == doctest::Approx(0.f));
  }

  SUBCASE("Calling applicazione_regole_due_stormi()")
  {
    float d{2};
    float ds{1};
    pf::Boid b1{{1, 2}, {3, 4}};
    pf::Boid b2{{0.4f, 2}, {-7, -0.8f}};
    pf::Boid b3{{5.7f, 3}, {1, 4}};
    pf::Boid b4{{1.3f, 2.7f}, {2.2f, -1}};
    std::vector<pf::Boid> stormo{b1, b2, b3, b4};
    b1 = pf::Boid{{12, 23}, {1, 2}};
    b2 = pf::Boid{{5.4f, 3.1f}, {0.2f, 1.3f}};
    std::vector<pf::Boid> stormo2{b1, b2};
    float s{0.5f};
    float a{1.2f};
    float c{0.75f};
    pf::applicazione_regole_due_stormi(stormo, stormo2, d, ds, s, a, c, ds, s,
                                       360);
    CHECK(stormo[0].get_pos().x == doctest::Approx(1.f));
    CHECK(stormo[0].get_pos().y == doctest::Approx(2.f));
    CHECK(stormo[0].get_vel().x == doctest::Approx(-3.4425f));
    CHECK(stormo[0].get_vel().y == doctest::Approx(-1.9675f));
    CHECK(stormo[1].get_pos().x == doctest::Approx(0.4f));
    CHECK(stormo[1].get_pos().y == doctest::Approx(2.f));
    CHECK(stormo[1].get_vel().x == doctest::Approx(4.7825f));
    CHECK(stormo[1].get_vel().y == doctest::Approx(2.2225f));
    CHECK(stormo[2].get_pos().x == doctest::Approx(5.7f));
    CHECK(stormo[2].get_pos().y == doctest::Approx(3.f));
    CHECK(stormo[2].get_vel().x == doctest::Approx(1.15f));
    CHECK(stormo[2].get_vel().y == doctest::Approx(3.95f));
    CHECK(stormo[3].get_pos().x == doctest::Approx(1.3f));
    CHECK(stormo[3].get_pos().y == doctest::Approx(2.7f));
    CHECK(stormo[3].get_vel().x == doctest::Approx(-3.14f));
    CHECK(stormo[3].get_vel().y == doctest::Approx(1.945f));
  }
}

TEST_CASE("Testing functions useful to make the graphic part")
{
  std::vector<pf::Boid> prova;
  REQUIRE(prova.size() == 0);

  SUBCASE("Calling realeToPixel()")
  {}

  SUBCASE("Calling calculateRotationAngle()")
  {}

  SUBCASE("Calling set_graph_point()")
  {}
}