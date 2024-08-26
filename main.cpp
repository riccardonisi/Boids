/*
#include "statistics.hpp"
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
  constexpr int frame_rate{60};
  window.setFramerateLimit(frame_rate);

  // Esempio di vettore di posizioni reali
  std::vector<pf::Boid> stormo = pf::genera_stormo(100);

  // Fattori di scala per la conversione
  float scaleFactorX = 1000.0f / 1.0f;
  float scaleFactorY = 600.0f / 1.0f;

  // Eseguire il loop della finestra finché è aperta
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    window.clear(sf::Color::Cyan);

    // Disegnare i punti convertiti in pixel
    for (pf::Boid const& boid : stormo) {
      sf::Vector2f pixelPos =
          realeToPixel(boid.pos().x, boid.pos().y, scaleFactorX, scaleFactorY);
      sf::CircleShape shape(2.5);
      shape.setPointCount(3);
      shape.setPosition(pixelPos);
      shape.setFillColor(sf::Color::Black);
      window.draw(shape);
    }

    pf::movimento(stormo, 0.001);
    pf::comportamento_bordi(stormo);
    pf::applicazione_regole(stormo, 0.02, 0.005, 0.05, 0.15, 0.05);
    pf::controllo_velocità(stormo, 2);

    window.display();
  }

  return 0;
}
*/

#include "simulation.hpp"
#include <cassert>
#include <iostream>

int main()
{
  std::cout << "\n    ---------------------------------------------\n";
  std::cout << "    |SIMULAZIONE DEL COMPORTAMENTO DI UNO STORMO|\n";
  std::cout << "    ---------------------------------------------\n";
  std::cout << "      di Riccardo Nisi, Emanuele Rosini, Federico Seren\n\n";
  std::cout << "Opzioni:\n"
            << "a. Visualizzare sul piano il comportamento di uno stormo\n";
  std::cout << "b. Visualizzare sul piano il comportamento di uno stormo "
               "usando i parametri consigliati\n";
  std::cout << "c. Visualizzare l'andamento nel tempo di distanza "
               "dall'origine, velocità dello stormo e distanza tra gli uccelli "
               "medie con dei grafici\n";
  std::cout << "d. Visualizzare l'andamento nel tempo di distanza "
               "dall'origine, velocità dello stormo e distanza tra gli uccelli "
               "medie con dei grafici, usando i parametri consigliati\n";
  std::cout << "e. Visualizzare sul piano il comportamento di due stormi (di "
               "specie diverse)\n";
  std::cout << "f. Visualizzare sul piano il comportamento di due stormi "
               "usando i parametri consigliati\n";
  char op;
  std::cin >> op;
  switch (op) {
  case 'a':
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
    assert(d >= 0 && d <= std::sqrt(2));
    assert(ds >= 0 && ds <= std::sqrt(2));
    assert(s > 0);
    assert(a > 0);
    assert(c > 0);
    std::cout << "Inserire l'angolo di visuale (in gradi): ";
    float angolo;
    std::cin >> angolo;
    assert(angolo >= 0 && d <= 360);
    pf::simulazione_piano(n, d, ds, s, a, c, angolo);
    break;
  case 'b':
    pf::simulazione_piano(200, 0.02f, 0.005f, 0.05f, 0.15f, 0.05f, 150.0f);
    break;
  case 'c':
    std::cout << "Inserire il numero di uccelli: ";
    std::cin >> n;
    assert(n > 1);
    std::cout << "Inserire d, ds, s, a, c: ";
    std::cin >> d >> ds >> s >> a >> c;
    assert(d >= 0 && d <= std::sqrt(2));
    assert(ds >= 0 && ds <= std::sqrt(2));
    assert(s > 0);
    assert(a > 0);
    assert(c > 0);
    std::cout << "Inserire l'angolo di visuale (in gradi): ";
    std::cin >> angolo;
    pf::grafici(n, d, ds, s, a, c, angolo);
    break;
  case 'd':
    pf::grafici(20, 0.02f, 0.005f, 1.0f, 0.15f, 0.005f, 360.0f);
    break;
  case 'e':
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
    assert(d >= 0 && d <= std::sqrt(2));
    assert(ds >= 0 && ds <= std::sqrt(2));
    assert(s > 0);
    assert(a > 0);
    assert(c > 0);
    std::cout << "Inserire ds2 , s2, che si applicano tra specie diverse: ";
    float ds2;
    float s2;
    std::cin >> ds2 >> s2;
    assert(s2 > 0);
    assert(ds2 >= 0 && ds2 <= std::sqrt(2));
    std::cout << "Inserire l'angolo di visuale (in gradi): ";
    std::cin >> angolo;
    assert(angolo >= 0 && d <= 360);
    pf::simulazione_piano_due_stormi(n, n2, d, ds, s, a, c, ds2, s2, angolo);
    break;
  case 'f':
    pf::simulazione_piano_due_stormi(100, 100, 0.03f, 0.0025f, 0.75f, 0.5f,
                                     0.5f, 0.02f, 0.95f, 360.0f);
    break;
  default:
    std::cout << "Carattere non valido";
    break;
  }
  std::cout << '\n' << '\n';
}