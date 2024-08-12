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
  SUBCASE("Testing distance function")
  {
    pf::Point2D a{2, 5};
    pf::Point2D b{0.3, 6.8};
    pf::Point2D c{-15, 100};
    CHECK(pf::distanza(a, b) == doctest::Approx(2.47589));
    CHECK(pf::distanza(b, c) == doctest::Approx(94.4475));
    CHECK(pf::distanza(a, c) == doctest::Approx(96.5091));
  }
}

TEST_CASE("Testing the operators of the class Boid")
{
  SUBCASE("Testing operator ==")
  {
    pf::Boid a{{3.2, 9.4}, {2, 4.8}};
    pf::Boid b{{3.2, 9.4}, {2, 4.8}};
    pf::Boid c{{6.1, 134}, {5.4, 0.4}};
    pf::Boid d{{3.1, 9.4}, {2, 4.8}};
    CHECK(a == b);
    CHECK(!(a == c));
    CHECK(!(b == d));
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
    pf::Point2D v3 = separazione(prova, 0, 0.5, 10);
    CHECK(v3.x == doctest::Approx(-1.25));
    CHECK(v3.y == doctest::Approx(-2.4));
  }

  SUBCASE("Calling separazione() with 0 boids")
  {
    CHECK_THROWS(separazione(prova, 0, 0.5, 1));
  }

  SUBCASE("Calling separazione() with 1 boid")
  {
    pf::Point2D p1{4.5, 7.8};
    pf::Point2D v1{0, 0};
    pf::Boid b1{p1, v1};
    prova.push_back(b1);
    CHECK_THROWS(separazione(prova, 0, 0.5, 12));
  }

  SUBCASE("Calling separazione() with 2 near boids, and 2 far boids")
  {
    pf::Point2D p{2, 3};
    pf::Point2D v{0, 0};
    pf::Boid b{p, v};
    prova.push_back(b);
    p = {4.5, 7.8};
    b = {p, v};
    prova.push_back(b);
    p = {100, 7.8};
    b = {p, v};
    prova.push_back(b);
    p = {12, 11.5};
    b = {p, v};
    prova.push_back(b);
    pf::Point2D v3 = separazione(prova, 0, 0.5, 10);
    CHECK(v3.x == doctest::Approx(-1.25));
    CHECK(v3.y == doctest::Approx(-2.4));
  }

  SUBCASE("Calling separazione() with 0 near boids")
  {
    pf::Point2D p{25, 31.2};
    pf::Point2D v{0, 0};
    pf::Boid b{p, v};
    prova.push_back(b);
    p = {4.5, 7.8};
    b = {p, v};
    prova.push_back(b);
    p = {1, 7.8};
    b = {p, v};
    prova.push_back(b);
    p = {12, 11.5};
    b = {p, v};
    prova.push_back(b);
    pf::Point2D v3 = separazione(prova, 0, 0.5, 10);
    CHECK(v3.x == doctest::Approx(0));
    CHECK(v3.y == doctest::Approx(0));
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
    pf::Point2D v4 = allineamento(prova, 1, 3, 10);
    CHECK(v4.x == doctest::Approx(8.25));
    CHECK(v4.y == doctest::Approx(-2.4));
  }

  SUBCASE("Calling allineamento() with 0 boids")
  {
    CHECK_THROWS(allineamento(prova, 0, 2, 10));
  }

  SUBCASE("Calling allineamento() with 1 boid")
  {
    pf::Point2D v1{4.5, 7.8};
    pf::Point2D p1{0, 0};
    pf::Boid b1{p1, v1};
    prova.push_back(b1);
    CHECK_THROWS(allineamento(prova, 0, 2, 20));
  }

  SUBCASE("Calling allineamento() with 3 near boids and 2 far boids")
  {
    pf::Point2D v{2, 3};
    pf::Point2D p{0, 0};
    prova.push_back({p, v});
    v = {0.5, 6.2};
    prova.push_back({p, v});
    p = {23, 18};
    v = {23, 18};
    prova.push_back({p, v});
    p = {0, 1};
    v = {4.5, 7.8};
    prova.push_back({p, v});
    p = {15, 8};
    v = {1.2, 0.8};
    prova.push_back({p, v});
    pf::Point2D v4 = allineamento(prova, 1, 3, 17);
    CHECK(v4.x == doctest::Approx(8.25));
    CHECK(v4.y == doctest::Approx(-2.4));
  }

  SUBCASE("Calling allineamento() with 0 near boids")
  {
    pf::Point2D v{2, 3};
    pf::Point2D p{0, 0};
    prova.push_back({p, v});
    p = {50, 50};
    v = {0.5, 6.2};
    prova.push_back({p, v});
    p = {2, 1};
    v = {23, 18};
    prova.push_back({p, v});
    v = {4.5, 7.8};
    prova.push_back({p, v});
    v = {1.2, 0.8};
    prova.push_back({p, v});
    pf::Point2D v4 = allineamento(prova, 1, 3, 17);
    CHECK(v4.x == doctest::Approx(0));
    CHECK(v4.y == doctest::Approx(0));
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
    pf::Point2D v4 = coesione(prova, 0, 0.6, 11);
    CHECK(v4.x == doctest::Approx(0.3));
    CHECK(v4.y == doctest::Approx(2.4));
  }

  SUBCASE("Calling coesione() with 0 boids")
  {
    CHECK_THROWS(coesione(prova, 0, 0.2, 2));
  }

  SUBCASE("Calling coesione() with 1 boid")
  {
    pf::Point2D p1{4.5, 7};
    pf::Point2D v1{0, 0};
    pf::Boid b1{p1, v1};
    prova.push_back(b1);
    CHECK_THROWS(coesione(prova, 0, 2, 10));
  }

  SUBCASE("Calling coesione() with 3 near boids, and 1 far boid")
  {
    pf::Point2D p{2, 3};
    pf::Point2D v{0, 0};
    prova.push_back({p, v});
    p = {0.5, 6.2};
    prova.push_back({p, v});
    p = {12, 11.5};
    prova.push_back({p, v});
    p = {4.5, 7.8};
    prova.push_back({p, v});
    pf::Point2D v4 = coesione(prova, 0, 0.6, 9);
    CHECK(v4.x == doctest::Approx(0.3));
    CHECK(v4.y == doctest::Approx(2.4));
  }

  SUBCASE("Calling coesione() with 0 near boids")
  {
    pf::Point2D p{2, 3};
    pf::Point2D v{0, 0};
    prova.push_back({p, v});
    p = {0.5, 6.2};
    prova.push_back({p, v});
    p = {12, 11.5};
    prova.push_back({p, v});
    p = {25, 7.8};
    prova.push_back({p, v});
    pf::Point2D v4 = coesione(prova, 3, 0.6, 8.5);
    CHECK(v4.x == doctest::Approx(0));
    CHECK(v4.y == doctest::Approx(0));
  }
}

TEST_CASE("Testing generation of boids")
{
  SUBCASE("Calling genera_stormo() with 0 ore less boids")
  {
    CHECK_THROWS(pf::genera_stormo(0));
    CHECK_THROWS(pf::genera_stormo(-2));
    CHECK_THROWS(pf::genera_stormo(-46));
    CHECK_THROWS(pf::genera_stormo(-57));
    CHECK_THROWS(pf::genera_stormo(-1234));
  }

  SUBCASE("Calling genera_stormo() with a non integer number of boids")
  {
    CHECK_THROWS(pf::genera_stormo(0.5));
    CHECK_THROWS(pf::genera_stormo(23.45));
    CHECK_THROWS(pf::genera_stormo(-1.4));
    CHECK_THROWS(pf::genera_stormo(1234.56));
  }

  SUBCASE("Calling genera_stormo() with 5 boids")
  {
    std::vector<pf::Boid> prova = pf::genera_stormo(5);
    CHECK(prova.size() == 5);
    CHECK(!(prova[0] == prova[1] && prova[0] == prova[2] && prova[0] == prova[3]
            && prova[0] == prova[4]));
    CHECK(!(prova[0].pos().x == prova[0].pos().y
            && prova[0].pos().x == prova[0].vel().x
            && prova[0].pos().x == prova[0].vel().y));
  }

  SUBCASE("Calling genera_stormo() with 50 boids")
  {
    std::vector<pf::Boid> prova = pf::genera_stormo(50);
    CHECK(prova.size() == 50);
  }

  /*SUBCASE("Calling boid_vicini() with 10 boids")
  {
    double dist{2};
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
    double d{2};
    double ds{1};
    pf::Boid b1{{1, 2}, {3, 4}};
    pf::Boid b2{{0.4, 2}, {-7, -0.8}};
    pf::Boid b3{{5.7, 3}, {1, 4}};
    pf::Boid b4{{1.3, 2.7}, {2.2, -1}};
    std::vector<pf::Boid> stormo{b1, b2, b3, b4};
    double s{0.5};
    double a{1.2};
    double c{0.75};
    pf::applicazione_regole(stormo, d, ds, s, a, c);
    CHECK(stormo[0].pos().x == doctest::Approx(1));
    CHECK(stormo[0].pos().y == doctest::Approx(2));
    CHECK(stormo[0].vel().x == doctest::Approx(-3.4425));
    CHECK(stormo[0].vel().y == doctest::Approx(-1.9675));
    CHECK(stormo[1].pos().x == doctest::Approx(0.4));
    CHECK(stormo[1].pos().y == doctest::Approx(2));
    CHECK(stormo[1].vel().x == doctest::Approx(4.7825));
    CHECK(stormo[1].vel().y == doctest::Approx(2.2225));
    CHECK(stormo[2].pos().x == doctest::Approx(5.7));
    CHECK(stormo[2].pos().y == doctest::Approx(3));
    CHECK(stormo[2].vel().x == doctest::Approx(1));
    CHECK(stormo[2].vel().y == doctest::Approx(4));
    CHECK(stormo[3].pos().x == doctest::Approx(1.3));
    CHECK(stormo[3].pos().y == doctest::Approx(2.7));
    CHECK(stormo[3].vel().x == doctest::Approx(-3.14));
    CHECK(stormo[3].vel().y == doctest::Approx(1.945));
  }

  SUBCASE("Calling movimento() with 3 boids")
  {
    pf::Boid b1{{1, 2}, {3, 4}};
    pf::Boid b2{{0.4, 2}, {0, -0.8}};
    pf::Boid b3{{5.7, 3}, {-1, 4}};
    std::vector<pf::Boid> stormo{b1, b2, b3};
    pf::movimento(stormo, 0.5);
    CHECK(stormo[0].pos().x == doctest::Approx(2.5));
    CHECK(stormo[0].pos().y == doctest::Approx(4));
    CHECK(stormo[0].vel().x == doctest::Approx(3));
    CHECK(stormo[0].vel().y == doctest::Approx(4));
    CHECK(stormo[1].pos().x == doctest::Approx(0.4));
    CHECK(stormo[1].pos().y == doctest::Approx(1.6));
    CHECK(stormo[1].vel().x == doctest::Approx(0));
    CHECK(stormo[1].vel().y == doctest::Approx(-0.8));
    CHECK(stormo[2].pos().x == doctest::Approx(5.2));
    CHECK(stormo[2].pos().y == doctest::Approx(5));
    CHECK(stormo[2].vel().x == doctest::Approx(-1));
    CHECK(stormo[2].vel().y == doctest::Approx(4));
  }
  
  SUBCASE("Calling comportamento_bordi() with 5 boids")
  {
    pf::Boid b1{{0.2, 0.5}, {1, 2}};
    pf::Boid b2{{0.3, 12}, {1, 2}};
    pf::Boid b3{{2, 0.5}, {1, 2}};
    pf::Boid b4{{100, 23}, {1, 2}};
    pf::Boid b5{{-2, -3}, {1, 2}};
    std::vector<pf::Boid> stormo{b1, b2, b3, b4, b5};
    pf::comportamento_bordi(stormo);
    CHECK(stormo.size() == 5);
    CHECK(stormo[0].pos().x == 0.2);
    CHECK(stormo[0].pos().y == 0.5);
    CHECK(stormo[0].vel().x == 1);
    CHECK(stormo[0].vel().y == 2);
    CHECK(stormo[1].pos2().x == 0.3);
    CHECK(stormo[1].pos().y == 0);
    CHECK(stormo[1].vel().x == 1);
    CHECK(stormo[1].vel().y == 2);
    CHECK(stormo[2].pos().x == 0);
    CHECK(stormo[2].pos().y == 0.5);
    CHECK(stormo[2].vel().x == 1);
    CHECK(stormo[2].vel().y == 2);
    CHECK(stormo[3].pos().x == 0);
    CHECK(stormo[3].pos().y == 0);
    CHECK(stormo[3].vel().x == 1);
    CHECK(stormo[3].vel().y == 2);
    CHECK(stormo[4].pos().x == 1);
    CHECK(stormo[4].pos().y == 1);
    CHECK(stormo[4].vel().x == 1);
    CHECK(stormo[4].vel().y == 2);
  }
}
