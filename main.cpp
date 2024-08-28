#include "simulation.hpp"
#include <cassert>
#include <chrono>
#include <iostream>

int main()
{
  std::cout << "\n    ---------------------------------------------\n";
  std::cout << "   |     BOIDS, FLOCKING BEHAVIOR SIMULATION     |\n";
  std::cout << "    ---------------------------------------------\n";
  std::cout << "      by Riccardo Nisi, Emanuele Rosini, Federico Seren\n\n";
  std::cout << "Options:\n"
            << "a. Print on terminal time evolution of "
               "mean distance from origin, mean speed and mean distance "
               "between boids\n";
  std::cout << "b. Visualize animated flocking behavior with your parameters\n";
  std::cout << "c. Visualize animated flocking behavior with "
               "suggested parameters\n";
  std::cout << "d. Visualize with graphs the time evolution of "
               "mean distance from origin, mean speed and mean distance "
               "between boids (your parameters)\n";
  std::cout << "e. Visualize with graphs the time evolution of"
               "mean distance from origin, mean speed and mean distance "
               "between boids (suggested parameters)\n";
  std::cout << "f. Visualize animated flocking behavior of two flocks of "
               "different species, with your parameters\n";
  std::cout << "g. Visualize animated flocking behavior of two flocks of "
               "different species, with suggested parameters\n";
  char op;
  std::cin >> op;
  if (op == 'a') {
    std::cout << "Select the number of boids: ";
    int n;
    std::cin >> n;
    assert(n > 1);
    std::cout << "Set d, ds, s, a, c: ";
    float d;
    float ds;
    float s;
    float a;
    float c;
    std::cin >> d >> ds >> s >> a >> c;
    assert(d >= 0.f && d <= std::sqrt(2.f));
    assert(ds >= 0.f && ds <= std::sqrt(2.f));
    assert(s > 0.f);
    assert(a > 0.f);
    assert(c > 0.f);
    std::cout << "Set the field of view (in degrees): ";
    float field_of_view;
    std::cin >> field_of_view;
    assert(field_of_view >= 0.0f && field_of_view <= 360.f);

    std::vector<pf::Boid> flock = pf::generate_flock(n);
    std::cout << "Set the duration of the simulation"
                 "in seconds: ";
    int time_tot;
    std::cin >> time_tot;
    ++time_tot;
    std::cout << "Set update time of "
                 "mean parameters ";
    int time_lapse;
    std::cin >> time_lapse;
    const auto start{std::chrono::steady_clock::now()};
    auto start2{std::chrono::steady_clock::now()};
    std::chrono::duration<double> elapsed_seconds{0};
    std::chrono::duration<double> elapsed_seconds2{0};
    bool condition{true};
    while (elapsed_seconds.count() < time_tot) {
      if (condition == true) {
        start2 = std::chrono::steady_clock::now();
        std::cout << "\ntime = " << elapsed_seconds.count() << "s\n";
        std::cout << "Mean distance from the origin = "
                  << pf::mean_position(flock) << " +/- "
                  << pf::standdev_position(flock) << '\n';
        std::cout << "Mean speed = " << pf::mean_velocity(flock) << " +/- "
                  << pf::standdev_velocity(flock) << '\n';
        std::cout << "Mean distance between boids = "
                  << pf::mean_distance(flock) << " +/- "
                  << pf::standdev_distance(flock) << '\n';
        condition = false;
      }
      pf::movement(flock, 0.001f);
      pf::boundary_behavior(flock);
      pf::flocking_behavior(flock, d, ds, s, a, c, field_of_view);
      pf::random_boost(flock, 0.01f, 0.01f);
      pf::speed_control(flock, 2);
      elapsed_seconds  = std::chrono::steady_clock::now() - start;
      elapsed_seconds2 = std::chrono::steady_clock::now() - start2;
      if (elapsed_seconds2.count() > time_lapse) {
        condition = true;
      }
    }
  } else if (op == 'b') {
    std::cout << "Select the number of boids: ";
    int n;
    std::cin >> n;
    assert(n > 1);
    std::cout << "Set d, ds, s, a, c: ";
    float d;
    float ds;
    float s;
    float a;
    float c;
    std::cin >> d >> ds >> s >> a >> c;
    assert(d >= 0.f && d <= std::sqrt(2.f));
    assert(ds >= 0.f && ds <= std::sqrt(2.f));
    assert(s > 0.f);
    assert(a > 0.f);
    assert(c > 0.f);
    std::cout << "Set the field of view (in degrees): ";
    float field_of_view;
    std::cin >> field_of_view;
    assert(field_of_view >= 0.f && field_of_view <= 360.f);
    pf::simulation_one_flock(n, d, ds, s, a, c, field_of_view);
  } else if (op == 'c') {
    pf::simulation_one_flock(200, 0.02f, 0.005f, 0.05f, 0.15f, 0.05f, 150.0f);
  } else if (op == 'd') {
    std::cout << "Select the number of boids: ";
    int n;
    std::cin >> n;
    assert(n > 1);
    std::cout << "Set d, ds, s, a, c: ";
    float d;
    float ds;
    float s;
    float a;
    float c;
    std::cin >> d >> ds >> s >> a >> c;
    assert(d >= 0.f && d <= std::sqrt(2.f));
    assert(ds >= 0.f && ds <= std::sqrt(2.f));
    assert(s > 0.f);
    assert(a > 0.f);
    assert(c > 0.f);
    std::cout << "Set the field of view (in degrees): ";
    float field_of_view;
    std::cin >> field_of_view;
    assert(field_of_view >= 0.f && field_of_view <= 360.f);
    pf::graphs(n, d, ds, s, a, c, field_of_view);
  } else if (op == 'e') {
    pf::graphs(20, 0.02f, 0.005f, 1.0f, 0.15f, 0.005f, 360.0f);
  } else if (op == 'f') {
    std::cout
        << "Select the number of boids for the first flock: ";
    int n;
    std::cin >> n;
    assert(n > 1);
    std::cout
        << "Select the number of boids for the second flock: ";
    int n2;
    std::cin >> n2;
    assert(n2 > 1);
    std::cout << "Set d, ds, s, a, c, for boids of their "
                 "own species: ";
    float d;
    float ds;
    float s;
    float a;
    float c;
    std::cin >> d >> ds >> s >> a >> c;
    assert(d >= 0.f && d <= std::sqrt(2.f));
    assert(ds >= 0.f && ds <= std::sqrt(2.f));
    assert(s > 0.f);
    assert(a > 0.f);
    assert(c > 0.f);
    std::cout << "Set ds2 , s2, applied between the two flocks: ";
    float ds2;
    float s2;
    std::cin >> ds2 >> s2;
    assert(s2 > 0.f);
    assert(ds2 >= 0.f && ds2 <= std::sqrt(2.f));
    std::cout << "Set the field of view (in degrees): ";
    float field_of_view;
    std::cin >> field_of_view;
    assert(field_of_view >= 0.f && field_of_view <= 360.f);
    pf::simulation_two_flocks(n, n2, d, ds, s, a, c, ds2, s2, field_of_view);
  } else if (op == 'g') {
    pf::simulation_two_flocks(100, 100, 0.03f, 0.0025f, 0.75f, 0.5f,
                                     0.5f, 0.02f, 0.95f, 360.0f);
  } else {
    std::cout << "Unvalid character";
  }
  std::cout << '\n' << '\n';
}