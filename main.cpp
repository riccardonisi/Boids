#include "simulation.hpp"
#include <cassert>
#include <chrono>
#include <iostream>

int main()
{
  std::cout << "\n    ---------------------------------------------\n";
  std::cout << "    |SIMULAZIONE DEL COMPORTAMENTO DI UNO STORMO|\n";
  std::cout << "    ---------------------------------------------\n";
  std::cout << "      di Riccardo Nisi, Emanuele Rosini, Federico Seren\n\n";
  std::cout << "Opzioni:\n"
            << "a. Visualizzare sul terminale l'andamento nel tempo di "
               "distanza dall'origine, velocità dello stormo e distanza tra "
               "gli uccelli medie\n";
  std::cout << "b. Visualizzare sul piano il comportamento di uno stormo\n";
  std::cout << "c. Visualizzare sul piano il comportamento di uno stormo "
               "usando i parametri consigliati\n";
  std::cout << "d. Visualizzare l'andamento nel tempo di distanza "
               "dall'origine, velocità dello stormo e distanza tra gli uccelli "
               "medie con dei grafici\n";
  std::cout << "e. Visualizzare l'andamento nel tempo di distanza "
               "dall'origine, velocità dello stormo e distanza tra gli uccelli "
               "medie con dei grafici, usando i parametri consigliati\n";
  std::cout << "f. Visualizzare sul piano il comportamento di due stormi (di "
               "specie diverse)\n";
  std::cout << "g. Visualizzare sul piano il comportamento di due stormi "
               "usando i parametri consigliati\n";
  char op;
  std::cin >> op;
  if (op == 'a') {
    std::cout << "Inserire il numero di uccelli: ";
    int n;
    std::cin >> n;
    assert(n > 1);
    std::cout << "Inserire d, ds, s, a, c: ";
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
    std::cout << "Inserire l'angolo di visuale (in gradi): ";
    float angolo;
    std::cin >> angolo;
    assert(angolo >= 0.0f && angolo <= 360.f);

    std::vector<pf::Boid> stormo = pf::genera_stormo(n);
    std::cout << "Inserire il numero di secondi che si vuole far durare la "
                 "simulazione: ";
    int time_tot;
    std::cin >> time_tot;
    ++time_tot;
    std::cout << "Inserire ogni quanti secondi si desiderano leggere i "
                 "parametri medi: ";
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
        std::cout << "\nTempo = " << elapsed_seconds.count() << "s\n";
        std::cout << "Distanza dall'origine media = "
                  << pf::mean_position(stormo) << " +/- "
                  << pf::standdev_position(stormo) << '\n';
        std::cout << "Velocità media = " << pf::mean_velocity(stormo) << " +/- "
                  << pf::standdev_velocity(stormo) << '\n';
        std::cout << "Distanza tra gli uccelli media = "
                  << pf::mean_distance(stormo) << " +/- "
                  << pf::standdev_distance(stormo) << '\n';
        condition = false;
      }
      pf::movimento(stormo, 0.001f);
      pf::comportamento_bordi(stormo);
      pf::applicazione_regole(stormo, d, ds, s, a, c, angolo);
      pf::random_boost(stormo, 0.01f, 0.01f);
      pf::controllo_velocità(stormo, 2);
      elapsed_seconds  = std::chrono::steady_clock::now() - start;
      elapsed_seconds2 = std::chrono::steady_clock::now() - start2;
      if (elapsed_seconds2.count() > time_lapse) {
        condition = true;
      }
    }
  } else if (op == 'b') {
    std::cout << "Inserire il numero di uccelli: ";
    int n;
    std::cin >> n;
    assert(n > 1);
    std::cout << "Inserire d, ds, s, a, c: ";
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
    std::cout << "Inserire l'angolo di visuale (in gradi): ";
    float angolo;
    std::cin >> angolo;
    assert(angolo >= 0.f && angolo <= 360.f);
    pf::simulazione_piano(n, d, ds, s, a, c, angolo);
  } else if (op == 'c') {
    pf::simulazione_piano(200, 0.02f, 0.005f, 0.05f, 0.15f, 0.05f, 150.0f);
  } else if (op == 'd') {
    std::cout << "Inserire il numero di uccelli: ";
    int n;
    std::cin >> n;
    assert(n > 1);
    std::cout << "Inserire d, ds, s, a, c: ";
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
    std::cout << "Inserire l'angolo di visuale (in gradi): ";
    float angolo;
    std::cin >> angolo;
    assert(angolo >= 0.f && angolo <= 360.f);
    pf::grafici(n, d, ds, s, a, c, angolo);
  } else if (op == 'e') {
    pf::grafici(20, 0.02f, 0.005f, 1.0f, 0.15f, 0.005f, 360.0f);
  } else if (op == 'f') {
    std::cout
        << "Inserire il numero di uccelli che compongono il primo stormo: ";
    int n;
    std::cin >> n;
    assert(n > 1);
    std::cout
        << "Inserire il numero di uccelli che compongono il secondo stormo: ";
    int n2;
    std::cin >> n2;
    assert(n2 > 1);
    std::cout << "Inserire d, ds, s, a, c, che si applicano tra gli uccelli di "
                 "una stessa specie: ";
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
    std::cout << "Inserire ds2 , s2, che si applicano tra specie diverse: ";
    float ds2;
    float s2;
    std::cin >> ds2 >> s2;
    assert(s2 > 0.f);
    assert(ds2 >= 0.f && ds2 <= std::sqrt(2.f));
    std::cout << "Inserire l'angolo di visuale (in gradi): ";
    float angolo;
    std::cin >> angolo;
    assert(angolo >= 0.f && angolo <= 360.f);
    pf::simulazione_piano_due_stormi(n, n2, d, ds, s, a, c, ds2, s2, angolo);
  } else if (op == 'g') {
    pf::simulazione_piano_due_stormi(100, 100, 0.03f, 0.0025f, 0.75f, 0.5f,
                                     0.5f, 0.02f, 0.95f, 360.0f);
  } else {
    std::cout << "Carattere non valido";
  }
  std::cout << '\n' << '\n';
}