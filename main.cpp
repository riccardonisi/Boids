#include "simulation.hpp"
#include <cassert>
#include <chrono>
#include <iostream>

int main()
{
  try {
    std::cout << "\n    ---------------------------------------------\n";
    std::cout << "   |     BOIDS, FLOCKING BEHAVIOR SIMULATION     |\n";
    std::cout << "    ---------------------------------------------\n";
    std::cout << "      by Riccardo Nisi, Emanuele Rosini, Federico Seren\n\n";
    std::cout << "Options:\n"
              << "a. Print on terminal time evolution of "
                 "mean distance from origin, mean speed and mean distance "
                 "between boids\n";
    std::cout
        << "b. Visualize animated flocking behavior with your parameters\n";
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
    char op{};
    while (true) {
      std::cin >> op;
      if (op == 'a') {
        std::cout << "Select the number of boids: ";
        double n;
        std::cin >> n;
        if (n < 3) {
          throw std::runtime_error{"Not enough boids to estimate parameters"};
        }
        if (std::floor(n) != n) {
          throw std::runtime_error{
              "The number of boids must be a natural number"};
        }
        std::cout << "Set d, ds, s, a, c: ";
        float d;
        float ds;
        float s;
        float a;
        float c;
        std::cin >> d >> ds >> s >> a >> c;
        if (d < 0.f || d > std::sqrt(2.f)) {
          throw std::runtime_error{
              "d must be defined in the range [0, sqrt(2)]"};
        }
        if (ds < 0.f || ds > d) {
          throw std::runtime_error{"ds must be defined in the range [0, d]"};
        }
        if (s < 0.f) {
          throw std::runtime_error{"s must be non-negative"};
        }
        if (a < 0.f) {
          throw std::runtime_error{"a must be non-negative"};
        }
        if (c < 0.f) {
          throw std::runtime_error{"c must be non-negative"};
        }
        std::cout << "Set the field of view (in degrees): ";
        float field_of_view;
        std::cin >> field_of_view;
        assert(field_of_view >= 0.0f && field_of_view <= 360.f);
        if (field_of_view < 0.0f && field_of_view > 360.f) {
          throw std::runtime_error{"The field of view must be an angle defined "
                                   "in the range [0°, 360°]"};
        }
        std::vector<pf::Boid> flock = pf::generate_flock(n);
        std::cout << "Set the duration of the simulation in seconds: ";
        double time_tot;
        std::cin >> time_tot;
        if (time_tot < 0.0f) {
          throw std::runtime_error{
              "The simulation can't last less that 0 seconds"};
        }
        std::cout << "Set update time of mean parameters ";
        double time_lapse;
        std::cin >> time_lapse;
        if (time_lapse < 0.0f) {
          throw std::runtime_error{"The update time can't be negative"};
        }
        if (time_lapse > time_tot) {
          throw std::runtime_error{"The update time can't be bigger that the "
                                   "duration of the simulation"};
        }
        const auto start{std::chrono::steady_clock::now()};
        auto start2{std::chrono::steady_clock::now()};
        std::chrono::duration<double> elapsed_seconds{0};
        std::chrono::duration<double> elapsed_seconds2{0};
        bool condition{true};
        while (elapsed_seconds.count() < time_tot) {
          if (condition) {
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
        std::cout << '\n' << '\n';
        return EXIT_SUCCESS;
      } else if (op == 'b') {
        std::cout << "Select the number of boids: ";
        double n;
        std::cin >> n;
        if (std::floor(n) != n || !(std::cin.good())) {
          throw std::runtime_error{
              "The number of boids must be a natural number"};
        }
        if (n < 1) {
          throw std::runtime_error{"Not enough boids to generate a flock"};
        }
        
        std::cout << "Set d, ds, s, a, c: ";
        float d;
        float ds;
        float s;
        float a;
        float c;
        std::cin >> d;
        if (d < 0.f || d > std::sqrt(2.f) || !(std::cin.good())) {
          throw std::runtime_error{
              "d must be a number defined in the range [0, sqrt(2)]"};
        }
        std::cin >> ds;
        if (ds < 0.f || ds > d || !(std::cin.good())) {
          throw std::runtime_error{
              "ds must be a nummber defined in the range [0, d]"};
        }
        std::cin >> s;
        if (s < 0.f || !(std::cin.good())) {
          throw std::runtime_error{"s must be non-negative number"};
        }
        std::cin >> a;
        if (a < 0.f || !(std::cin.good())) {
          throw std::runtime_error{"a must be non-negative number"};
        }
        std::cin >> c;
        if (c < 0.f || !(std::cin.good())) {
          throw std::runtime_error{"c must be non-negative number"};
        }
        std::cout << "Set the field of view (in degrees): ";
        float field_of_view;
        std::cin >> field_of_view;
        if (field_of_view < 0.0f || field_of_view > 360.f
            || !(std::cin.good())) {
          throw std::runtime_error{"The field of view must be an angle defined "
                                   "in the range [0°, 360°]"};
        }
        pf::simulation_one_flock(n, d, ds, s, a, c, field_of_view);
        std::cout << '\n' << '\n';
        return EXIT_SUCCESS;
      } else if (op == 'c') {
        pf::simulation_one_flock(2000, 0.02f, 0.005f, 1.0f, 0.15f, 0.005f,
                                 230.0f);
        std::cout << '\n' << '\n';
        return EXIT_SUCCESS;
      } else if (op == 'd') {
        std::cout << "Select the number of boids: ";
        double n;
        std::cin >> n;
        if (n < 3) {
          throw std::runtime_error{"Not enought boids to estimate parameters"};
        }
        if (std::floor(n) != n) {
          throw std::runtime_error{
              "The number of boids must be a natural number"};
        }
        std::cout << "Set d, ds, s, a, c: ";
        float d;
        float ds;
        float s;
        float a;
        float c;
        std::cin >> d >> ds >> s >> a >> c;
        if (d < 0.f || d > std::sqrt(2.f)) {
          throw std::runtime_error{
              "d must be defined in the range [0, sqrt(2)]"};
        }
        if (ds < 0.f || ds > d) {
          throw std::runtime_error{"ds must be defined in the range [0, d]"};
        }
        if (s < 0.f) {
          throw std::runtime_error{"s must be non-negative"};
        }
        if (a < 0.f) {
          throw std::runtime_error{"a must be non-negative"};
        }
        if (c < 0.f) {
          throw std::runtime_error{"c must be non-negative"};
        }
        std::cout << "Set the field of view (in degrees): ";
        float field_of_view;
        std::cin >> field_of_view;
        if (field_of_view < 0.0f && field_of_view > 360.f) {
          throw std::runtime_error{"The field of view must be an angle defined "
                                   "in the range [0°, 360°]"};
        }
        pf::graphs(n, d, ds, s, a, c, field_of_view);
        std::cout << '\n' << '\n';
        return EXIT_SUCCESS;
      } else if (op == 'e') {
        pf::graphs(1000, 0.05f, 0.005f, 0.7f, 0.3f, 0.005f, 230.0f);
        std::cout << '\n' << '\n';
        return EXIT_SUCCESS;
      } else if (op == 'f') {
        std::cout << "Select the number of boids for the first flock: ";
        double n1;
        std::cin >> n1;
        if (n1 < 1) {
          throw std::runtime_error{"Not enough boids to generate a flock"};
        }
        if (std::floor(n1) != n1) {
          throw std::runtime_error{
              "The number of boids must be a natural number"};
        }
        std::cout << "Select the number of boids for the second flock: ";
        double n2;
        std::cin >> n2;
        if (n2 < 1) {
          throw std::runtime_error{"Not enough boids to generate a flock"};
        }
        if (std::floor(n2) != n2) {
          throw std::runtime_error{
              "The number of boids must be a natural number"};
        }
        std::cout << "Set d, ds, s, a, c, for boids of their "
                     "own species: ";
        float d;
        float ds;
        float s;
        float a;
        float c;
        std::cin >> d >> ds >> s >> a >> c;
        if (d < 0.f || d > std::sqrt(2.f)) {
          throw std::runtime_error{
              "d must be defined in the range [0, sqrt(2)]"};
        }
        if (ds < 0.f || ds > d) {
          throw std::runtime_error{"ds must be defined in the range [0, d]"};
        }
        if (s < 0.f) {
          throw std::runtime_error{"s must be non-negative"};
        }
        if (a < 0.f) {
          throw std::runtime_error{"a must be non-negative"};
        }
        if (c < 0.f) {
          throw std::runtime_error{"c must be non-negative"};
        }
        std::cout << "Set ds2 , s2, applied between the two flocks: ";
        float ds2;
        float s2;
        std::cin >> ds2 >> s2;
        if (ds < 0.f || ds > d) {
          throw std::runtime_error{
              "ds2 must be defined in the range [0, sqrt(2)]"};
        }
        if (s2 < 0.f) {
          throw std::runtime_error{"s2 must be non-negative"};
        }
        std::cout << "Set the field of view (in degrees): ";
        float field_of_view;
        std::cin >> field_of_view;
        if (field_of_view < 0.0f && field_of_view > 360.f) {
          throw std::runtime_error{"The field of view must be an angle defined "
                                   "in the range [0°, 360°]"};
        }
        pf::simulation_two_flocks(n1, n2, d, ds, s, a, c, ds2, s2,
                                  field_of_view);
        std::cout << '\n' << '\n';
        return EXIT_SUCCESS;
      } else if (op == 'g') {
        pf::simulation_two_flocks(100, 100, 0.03f, 0.0025f, 0.75f, 0.5f, 0.5f,
                                  0.02f, 0.95f, 360.0f);
        std::cout << '\n' << '\n';
        return EXIT_SUCCESS;
      } else {
        std::cout << "Unvalid character.\nReinsert: ";
        op = {};
      }
    }
  } catch (std::runtime_error const& e) {
    std::cerr << '\n' << e.what() << "\n\n";
    return EXIT_FAILURE;
  } catch (...) {
    std::cerr << "\nCaught unknown exception\n";
    return EXIT_FAILURE;
  }
}