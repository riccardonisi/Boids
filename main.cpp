#include "boids.hpp"
#include "boids2.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

// Funzione per convertire un valore reale in pixel
sf::Vector2f realeToPixel(float x, float y, float scaleFactorX,
                          float scaleFactorY)
{
  return sf::Vector2f(x * scaleFactorX, y * scaleFactorY);
}

int main()
{
  sf::RenderWindow window(
      sf::VideoMode(1000, 600),
      "Simulazione del comportamento di uno stormo, di Nisi, Rosini, Seren");

  // Esempio di vettore di posizioni reali
  std::vector<pf::Boid> stormo = pf::genera_stormo(20);

  // Fattori di scala per la conversione
  float scaleFactorX = 1000.0f / 1.0f; // Scala l'intervallo
  float scaleFactorY = 600.0f / 1.0f;  // Scala l'intervallo

  // Eseguire il loop della finestra finché è aperta
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear(sf::Color::Cyan);

    // Disegnare i punti convertiti in pixel
    for (unsigned long int i{0}; i != stormo.size(); ++i) {
      sf::Vector2f pixelPos = realeToPixel(stormo[i].pos().x, stormo[i].pos().y,
                                           scaleFactorX, scaleFactorY);
      sf::CircleShape shape(5);
      shape.setPointCount(3);
      shape.setPosition(pixelPos);
      shape.setFillColor(sf::Color::Black);
      window.draw(shape);
    }

    pf::movimento(stormo, 0.001);
    pf::comportamento_bordi(stormo);
    pf::applicazione_regole(stormo, 0.02, 0.001, 1.5, 0.15, 0.10);
    pf::controllo_velocità(stormo, 2);

    window.display();
  }

  return 0;
}


/*#include "boids.hpp"
#include "boids2.hpp"
#include <SFML/Graphics.hpp>
#include <cassert>
#include <iostream>
#include <memory>

// Funzione per convertire un valore reale in pixel
sf::Vector2f realeToPixel(float x, float y, float scaleFactorX,
                          float scaleFactorY)
{
  return sf::Vector2f(x * scaleFactorX, y * scaleFactorY);
}

void simulazione_piano(int n, double d, double ds, double s, double a, double c)
{
  sf::RenderWindow window(
      sf::VideoMode(1000, 600),
      "Simulazione del comportamento di uno stormo, di Nisi, Rosini, Seren");

  // Esempio di vettore di posizioni reali
  std::vector<pf::Boid> stormo = pf::genera_stormo(n);

  // Fattori di scala per la conversione
  float scaleFactorX = 1000.0f / 1.0f; // Scala l'intervallo
  float scaleFactorY = 600.0f / 1.0f;  // Scala l'intervallo

  // Eseguire il loop della finestra finché è aperta
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear(sf::Color::Cyan);

    // Disegnare i punti convertiti in pixel
    for (unsigned long int i{0}; i != stormo.size(); ++i) {
      sf::Vector2f pixelPos = realeToPixel(stormo[i].pos().x, stormo[i].pos().y,
                                           scaleFactorX, scaleFactorY);
      sf::CircleShape shape(3);
      shape.setPointCount(3);
      shape.setPosition(pixelPos);
      shape.setFillColor(sf::Color::Black);
      window.draw(shape);
    }

    pf::movimento(stormo, 0.001);
    pf::comportamento_bordi(stormo);
    pf::applicazione_regole(stormo, d, ds, s, a, c);
    pf::controllo_velocità(stormo, 2);

    window.display();
  }

  // std::cout << '\n';
  // for (pf::Boid& b : stormo) {
  //   std::cout << b.pos().x << ' ' << b.pos().y << '\n';
  // }
  // std::cout << '\n';
}

void simulazione_piano_due_stormi(int n1, int n2, double d, double ds, double s,
                                  double a, double c, double ds2, double s2)
{
  sf::RenderWindow window(
      sf::VideoMode(1000, 600),
      "Simulazione del comportamento di uno stormo, di Nisi, Rosini, Seren");

  std::vector<pf::Boid> stormo1 = pf::genera_stormo(n1);
  std::vector<pf::Boid> stormo2 = pf::genera_stormo(n2);

  float scaleFactorX = 1000.0f / 1.0f;
  float scaleFactorY = 600.0f / 1.0f;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear(sf::Color::Cyan);

    for (unsigned long int i{0}; i != stormo1.size(); ++i) {
      sf::Vector2f pixelPos = realeToPixel(
          stormo1[i].pos().x, stormo1[i].pos().y, scaleFactorX, scaleFactorY);
      sf::CircleShape shape(3);
      shape.setPointCount(3);
      shape.setPosition(pixelPos);
      shape.setFillColor(sf::Color::Black);
      window.draw(shape);
    }
    pf::movimento(stormo1, 0.001);
    pf::comportamento_bordi(stormo1);
    pf::applicazione_regole_due_stormi(stormo1, stormo2, d, ds, s, a, c, ds2,
                                       s2);
    pf::controllo_velocità(stormo1, 2);

    for (unsigned long int i{0}; i != stormo2.size(); ++i) {
      sf::Vector2f pixelPos = realeToPixel(
          stormo2[i].pos().x, stormo2[i].pos().y, scaleFactorX, scaleFactorY);
      sf::CircleShape shape(3);
      shape.setPointCount(3);
      shape.setPosition(pixelPos);
      shape.setFillColor(sf::Color::Red);
      window.draw(shape);
    }
    pf::movimento(stormo2, 0.001);
    pf::comportamento_bordi(stormo2);
    pf::applicazione_regole_due_stormi(stormo2, stormo1, d, ds, s, a, c, ds2,
                                       s2);
    pf::controllo_velocità(stormo2, 2);

    window.display();
  }
}

void grafici(int n, double d, double ds, double s, double a, double c)
{}

int main()
{
  std::cout << "\n    ---------------------------------------------\n";
  std::cout << "    |SIMULAZIONE DEL COMPORTAMENTO DI UNO STORMO|\n";
  std::cout << "    ---------------------------------------------\n";
  std::cout << "      di Riccardo Nisi, Emanuele Rosini, Federico Seren\n\n";
  std::cout << "Opzioni:\n"
            << "a. Visualizzare sul piano il comportamento di uno stormo\n";
  std::cout << "b. Visualizzare l'andamento di velocità, posizione e distanza "
               "medie in funzione del tempo con dei graifici\n";
  std::cout << "c. Visualizzare sul piano il comportamento di due stormi (di "
               "specie diverse)\n";
  std::cout << "d. Visualizzare sul piano il comportamento di due stormi "
               "usando i parametri consigiati\n";
  char op;
  std::cin >> op;
  switch (op) {
  case 'a':
    std::cout << "Inserire il numero di uccelli: ";
    int n;
    std::cin >> n;
    assert(n > 1);
    std::cout << "Inserire d, ds, s, a, c: ";
    double d;
    double ds;
    double s;
    double a;
    double c;
    std::cin >> d >> ds >> s >> a >> c;
    assert(d >= 0 && d <= 1);
    assert(ds >= 0 && ds <= 1);
    assert(s > 0);
    assert(a > 0);
    assert(c > 0);
    simulazione_piano(n, d, ds, s, a, c);
    break;
  case 'b':
    std::cout << "Inserire il numero di uccelli: ";
    std::cin >> n;
    assert(n > 1);
    std::cout << "Inserire d, ds, s, a, c: ";
    std::cin >> d >> ds >> s >> a >> c;
    assert(d >= 0 && d <= 1);
    assert(ds >= 0 && ds <= 1);
    assert(s > 0);
    assert(a > 0);
    assert(c > 0);
    grafici(n, d, ds, s, a, c);
    break;
  case 'c':
    std::cout
        << "Inserire il numero di uccelli che compongono il primo stormo: ";
    std::cin >> n;
    assert(n > 1);
    std::cout
        << "Inserire il numero di uccelli che compongono il secondo stormo: ";
    int n2;
    std::cin >> n2;
    assert(n2 > 1);
    std::cout << "Inserire d, ds, s, a, c, che si applicano tra gli uccelli di "
                 "una stessa specie: ";
    std::cin >> d >> ds >> s >> a >> c;
    assert(d >= 0 && d <= 1);
    assert(ds >= 0 && ds <= 1);
    assert(s > 0);
    assert(a > 0);
    assert(c > 0);
    std::cout << "Inserire ds2 , s2, che si applicano tra specie diverse: ";
    int ds2;
    int s2;
    std::cin >> ds2 >> s2;
    assert(s2 > 0);
    assert(ds2 >= 0 && ds2 <= 1);
    simulazione_piano_due_stormi(n, n2, d, ds, s, a, c, ds2, s2);
    break;
  case 'd':
    simulazione_piano_due_stormi(100, 100, 0.03, 0.0025, 0.75, 0.5, 0.5, 0.02,
                                 0.95);
    break;
  default:
    std::cout << "Carattere non valido";
    break;
  }
  std::cout << '\n' << '\n';
}*/