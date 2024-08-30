#include "simulation.hpp"
#include <chrono>
#include <iostream>

int main()
{
  try {
    std::cout << "\n    ---------------------------------------------\n";
    std::cout << "   |     BOIDS, FLOCKING BEHAVIOR SIMULATION     |\n";
    std::cout << "    ---------------------------------------------\n";
    std::cout << "      by Riccardo Nisi, Emanuele Rosini, Federico Seren\n\n";

    std::cout << "The program simulates coordinated animal motion such as the "
                 "behavior of bird flocks.\n";
    std::cout << "It is based on the computer model developed by Craig "
                 "Reynolds in 1986.\n\n";
    std::cout << "Options:\n"
              << "a. Print on terminal time evolution of "
                 "mean distance from origin, mean speed and mean distance "
                 "between boids\n";
    std::cout
        << "b. Visualize animated flocking behavior, with your parameters\n";
    std::cout << "c. Visualize animated flocking behavior, with "
                 "suggested parameters\n";
    std::cout << "d. Visualize with graphs the time evolution of "
                 "mean distance from origin, mean speed and mean distance "
                 "between boids, with your parameters\n";
    std::cout << "e. Visualize with graphs the time evolution of "
                 "mean distance from origin, mean speed and mean distance "
                 "between boids, with suggested parameters\n";
    std::cout << "f. Visualize animated flocking behavior of two flocks of "
                 "different species, with your parameters\n";
    std::cout << "g. Visualize animated flocking behavior of two flocks of "
                 "different species, with suggested parameters\n";
    std::string op{};
    while (true) {
      std::cin >> op;
      if (op == std::string{"a"}) {
        std::cout << "\nParameters to choose:\n";
        std::cout << "- number of boids, a natural number >2 (to calculate "
                     "statistics)\n";
        std::cout
            << "- d = the distance within which the rules of flight are "
               "activated, floating point number in the range [0, sqrt(2)]\n";
        std::cout << "- ds = the distance within which separation is "
                     "activated, floating point number in the range [0, d]\n";
        std::cout << "- s = non-negativa factor that increases separation\n";
        std::cout << "- a = non-negative factor that increases alignemnt\n";
        std::cout << "- c = non-negative factor that increases cohesion\n";
        std::cout
            << "- the field of view of the boids, in the range [0°, 360°]\n\n";
        std::cout << "Provide the number of boids: ";
        double n;
        std::cin >> n;
        if (std::floor(n) != n || !(std::cin.good())) {
          throw std::runtime_error{
              "The number of boids must be a positive natural number"};
        }
        if (n < 3) {
          throw std::runtime_error{"Not enough boids to estimate parameters"};
        }
        std::cout << "Set d, ds, s, a, c: ";
        float d;
        std::cin >> d;
        if (d < 0.f || d > std::sqrt(2.f) || !(std::cin.good())) {
          throw std::runtime_error{
              "d must be a number defined in the range [0, sqrt(2)]"};
        }
        float ds;
        std::cin >> ds;
        if (ds < 0.f || ds > d || !(std::cin.good())) {
          throw std::runtime_error{
              "ds must be a number defined in the range [0, d]"};
        }
        float s;
        std::cin >> s;
        if (s < 0.f || !(std::cin.good())) {
          throw std::runtime_error{"s must be non-negative number"};
        }
        float a;
        std::cin >> a;
        if (a < 0.f || !(std::cin.good())) {
          throw std::runtime_error{"a must be non-negative number"};
        }
        float c;
        std::cin >> c;
        if (c < 0.f || !(std::cin.good())) {
          throw std::runtime_error{"c must be non-negative number"};
        }
        std::cout << "Set the field of view: ";
        float field_of_view;
        std::cin >> field_of_view;
        if (field_of_view < 0.0f || field_of_view > 360.f
            || !(std::cin.good())) {
          throw std::runtime_error{"The field of view must be an angle defined "
                                   "in the range [0°, 360°]"};
        }
        std::vector<pf::Boid> flock = pf::generate_flock(n);
        std::cout << "Set the duration of the simulation in seconds: ";
        double time_tot;
        std::cin >> time_tot;
        if (!(std::cin.good())) {
          throw std::runtime_error{"The duration must be a number"};
        }
        if (time_tot < 0.0f) {
          throw std::runtime_error{
              "The simulation can't last less than 0 seconds"};
        }
        std::cout << "Set update time of mean parameters: ";
        double time_lapse;
        std::cin >> time_lapse;
        if (!(std::cin.good())) {
          throw std::runtime_error{"The duration must be a number"};
        }
        if (time_lapse < 0.0f) {
          throw std::runtime_error{"The update time can't be negative"};
        }
        if (time_lapse > time_tot) {
          throw std::runtime_error{"The update time can't be greater than the "
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
      } else if (op == std::string{"b"}) {
        std::cout << "\nParameters to choose:\n";
        std::cout << "- number of boids, a positive natural number\n";
        std::cout
            << "- d = the distance within which the rules of flight are "
               "activated, floating point number in the range [0, sqrt(2)]\n";
        std::cout << "- ds = the distance within which separation is "
                     "activated, floating point number in the range [0, d]\n";
        std::cout << "- s = non-negativa factor that increases separation\n";
        std::cout << "- a = non-negative factor that increases alignemnt\n";
        std::cout << "- c = non-negative factor that increases cohesion\n";
        std::cout
            << "- the field of view of the boids, in the range [0°, 360°]\n\n";
        std::cout << "Provide the number of boids: ";
        double n;
        std::cin >> n;
        if (n < 1 || std::floor(n) != n || !(std::cin.good())) {
          throw std::runtime_error{
              "The number of boids must be a positive natural number"};
        }
        std::cout << "Set d, ds, s, a, c: ";
        float d;
        std::cin >> d;
        if (d < 0.f || d > std::sqrt(2.f) || !(std::cin.good())) {
          throw std::runtime_error{
              "d must be a number defined in the range [0, sqrt(2)]"};
        }
        float ds;
        std::cin >> ds;
        if (ds < 0.f || ds > d || !(std::cin.good())) {
          throw std::runtime_error{
              "ds must be a number defined in the range [0, d]"};
        }
        float s;
        std::cin >> s;
        if (s < 0.f || !(std::cin.good())) {
          throw std::runtime_error{"s must be non-negative number"};
        }
        float a;
        std::cin >> a;
        if (a < 0.f || !(std::cin.good())) {
          throw std::runtime_error{"a must be non-negative number"};
        }
        float c;
        std::cin >> c;
        if (c < 0.f || !(std::cin.good())) {
          throw std::runtime_error{"c must be non-negative number"};
        }
        std::cout << "Set the field of view: ";
        float field_of_view;
        std::cin >> field_of_view;
        if (field_of_view < 0.0f || field_of_view > 360.f
            || !(std::cin.good())) {
          throw std::runtime_error{"The field of view must be an angle defined "
                                   "in the range [0°, 360°]"};
        }
        pf::simulation_one_flock(n, d, ds, s, a, c, field_of_view, false);
        std::cout << '\n' << '\n';
        return EXIT_SUCCESS;
      } else if (op == std::string{"c"}) {
        pf::simulation_one_flock(2000, 0.03f, 0.005f, 1.0f, 0.2f, 0.01f, 270.0f,
                                 false);
        std::cout << '\n' << '\n';
        return EXIT_SUCCESS;
      } else if (op == std::string{"d"}) {
        std::cout << "\nParameters to choose:\n";
        std::cout << "- number of boids, a natural number >2 (to calculate "
                     "statistics)\n";
        std::cout
            << "- d = the distance within which the rules of flight are "
               "activated, floating point number in the range [0, sqrt(2)]\n";
        std::cout << "- ds = the distance within which separation is "
                     "activated, floating point number in the range [0, d]\n";
        std::cout << "- s = non-negativa factor that increases separation\n";
        std::cout << "- a = non-negative factor that increases alignemnt\n";
        std::cout << "- c = non-negative factor that increases cohesion\n";
        std::cout
            << "- the field of view of the boids, in the range [0°, 360°]\n\n";
        std::cout << "Provide the number of boids: ";
        double n;
        std::cin >> n;
        if (std::floor(n) != n || !(std::cin.good()) || n < 3) {
          throw std::runtime_error{
              "The number of boids must be a positive natural number >2"};
        }
        std::cout << "Set d, ds, s, a, c: ";
        float d;
        std::cin >> d;
        if (d < 0.f || d > std::sqrt(2.f) || !(std::cin.good())) {
          throw std::runtime_error{
              "d must be a number defined in the range [0, sqrt(2)]"};
        }
        float ds;
        std::cin >> ds;
        if (ds < 0.f || ds > d || !(std::cin.good())) {
          throw std::runtime_error{
              "ds must be a number defined in the range [0, d]"};
        }
        float s;
        std::cin >> s;
        if (s < 0.f || !(std::cin.good())) {
          throw std::runtime_error{"s must be non-negative number"};
        }
        float a;
        std::cin >> a;
        if (a < 0.f || !(std::cin.good())) {
          throw std::runtime_error{"a must be non-negative number"};
        }
        float c;
        std::cin >> c;
        if (c < 0.f || !(std::cin.good())) {
          throw std::runtime_error{"c must be non-negative number"};
        }
        std::cout << "Set the field of view: ";
        float field_of_view;
        std::cin >> field_of_view;
        if (field_of_view < 0.0f || field_of_view > 360.f
            || !(std::cin.good())) {
          throw std::runtime_error{"The field of view must be an angle defined "
                                   "in the range [0°, 360°]"};
        }
        pf::graphs(n, d, ds, s, a, c, field_of_view);
        std::cout << '\n' << '\n';
        return EXIT_SUCCESS;
      } else if (op == std::string{"e"}) {
        pf::graphs(2000, 0.03f, 0.005f, 1.0f, 0.2f, 0.005f, 230.0f);
        std::cout << '\n' << '\n';
        return EXIT_SUCCESS;
      } else if (op == std::string{"f"}) {
        std::cout << "\nParameters to choose:\n";
        std::cout << "- number of boids of each flock, positive natural "
                     "numbers\n";
        std::cout
            << "inside a flock:\n"
            << "     - d = the distance within which the rules of flight are "
               "activated, floating point number in the range [0, sqrt(2)]\n";
        std::cout << "     - ds = the distance within which separation is "
                     "activated, floating point number in the range [0, d]\n";
        std::cout
            << "     - s = non-negative factor that increases separation\n";
        std::cout
            << "     - a = non-negative factor that increases alignemnt\n";
        std::cout << "     - c = non-negative factor that increases cohesion\n";
        std::cout << "between flocks:\n "
                  << "    - ds2 = the distance within which separation is "
                     "activated, floating point number in the range [0, d]\n";
        std::cout
            << "     - s2 = non-negative factor that increases separation\n";
        std::cout
            << "- the field of view of the boids, in the range [0°, 360°]\n\n";
        std::cout << "Provide the number of boids in the first flock: ";
        double n1;
        std::cin >> n1;
        if (n1 < 1 || std::floor(n1) != n1 || !(std::cin.good())) {
          throw std::runtime_error{"The number of boids in a flock must be a "
                                   "positive natural number"};
        }
        std::cout << "Provide the number of boids in the second flock: ";
        double n2;
        std::cin >> n2;
        if (n2 < 1 || std::floor(n2) != n2 || !(std::cin.good())) {
          throw std::runtime_error{"The number of boids in a flock must be a "
                                   "positive natural number"};
        }
        std::cout << "Set d, ds, s, a, c, for boids of their own species: ";
        float d;
        std::cin >> d;
        if (d < 0.f || d > std::sqrt(2.f) || !(std::cin.good())) {
          throw std::runtime_error{
              "d must be a number defined in the range [0, sqrt(2)]"};
        }
        float ds;
        std::cin >> ds;
        if (ds < 0.f || ds > d || !(std::cin.good())) {
          throw std::runtime_error{
              "ds must be a number defined in the range [0, d]"};
        }
        float s;
        std::cin >> s;
        if (s < 0.f || !(std::cin.good())) {
          throw std::runtime_error{"s must be non-negative number"};
        }
        float a;
        std::cin >> a;
        if (a < 0.f || !(std::cin.good())) {
          throw std::runtime_error{"a must be non-negative number"};
        }
        float c;
        std::cin >> c;
        if (c < 0.f || !(std::cin.good())) {
          throw std::runtime_error{"c must be non-negative number"};
        }
        std::cout << "Set ds2 , s2, applied between the two flocks: ";
        float ds2;
        std::cin >> ds2;
        if (ds2 < 0.f || ds2 > sqrt(2.f) || !(std::cin.good())) {
          throw std::runtime_error{
              "ds2 must be a number defined in the range [0, sqrt(2)]"};
        }
        float s2;
        std::cin >> s2;
        if (s2 < 0.f || !(std::cin.good())) {
          throw std::runtime_error{"s2 must be a non-negative number"};
        }
        std::cout << "Set the field of view: ";
        float field_of_view;
        std::cin >> field_of_view;
        if (field_of_view < 0.0f || field_of_view > 360.f
            || !(std::cin.good())) {
          throw std::runtime_error{"The field of view must be an angle defined "
                                   "in the range [0°, 360°]"};
        }
        pf::simulation_two_flocks(n1, n2, d, ds, s, a, c, ds2, s2,
                                  field_of_view);
        std::cout << '\n' << '\n';
        return EXIT_SUCCESS;
      } else if (op == std::string{"g"}) {
        pf::simulation_two_flocks(300, 300, 0.03f, 0.005f, 1.0f, 0.15f, 0.01f,
                                  0.05f, 1.0f, 270.0f);
        std::cout << '\n' << '\n';
        return EXIT_SUCCESS;
      } else if (op == std::string{"h"}) {
        std::cout << "\nEaster egg found. Now solve the puzzle:\n\n"
                     "One thousand birds in measured flight,\n"
                     "Across the pale, unfolding light.\n"
                     "1.4 hearts, syncopated, beat,\n"
                     "Amidst the whispers of the street.\n"
                     "0.1 dreams in silent drift,\n"
                     "Through morning's veil, they lightly sift.\n"
                     "Zero sound in their ascent,\n"
                     "Zero weight, no earthbound bent.\n"
                     "360 degrees of view,\n"
                     "Encircle all, the old, the new.\n\n"
                     "In the void where light recedes,\n"
                     "A dark embrace begins to feed."
                  << '\n'
                  << '\n';
        std::cout << "Provide the number of boids: ";
        double n;
        std::cin >> n;
        if (n < 1 || std::floor(n) != n || !(std::cin.good())) {
          throw std::runtime_error{
              "The number of boids must be a positive natural number"};
        }
        std::cout << "Set d, ds, s, a, c: ";
        float d;
        std::cin >> d;
        if (d < 0.f || d > std::sqrt(2.f) || !(std::cin.good())) {
          throw std::runtime_error{
              "d must be a number defined in the range [0, sqrt(2)]"};
        }
        float ds;
        std::cin >> ds;
        if (ds < 0.f || ds > d || !(std::cin.good())) {
          throw std::runtime_error{
              "ds must be a number defined in the range [0, d]"};
        }
        float s;
        std::cin >> s;
        if (s < 0.f || !(std::cin.good())) {
          throw std::runtime_error{"s must be non-negative number"};
        }
        float a;
        std::cin >> a;
        if (a < 0.f || !(std::cin.good())) {
          throw std::runtime_error{"a must be non-negative number"};
        }
        float c;
        std::cin >> c;
        if (c < 0.f || !(std::cin.good())) {
          throw std::runtime_error{"c must be non-negative number"};
        }
        std::cout << "Set the field of view: ";
        float field_of_view;
        std::cin >> field_of_view;
        if (field_of_view < 0.0f || field_of_view > 360.f
            || !(std::cin.good())) {
          throw std::runtime_error{"The field of view must be an angle defined "
                                   "in the range [0°, 360°]"};
        }
        pf::simulation_one_flock(n, d, ds, s, a, c, field_of_view, true);
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