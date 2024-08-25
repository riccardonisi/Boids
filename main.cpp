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

#include "statistics.hpp"
#include <SFML/Graphics.hpp>
#include <cassert>
#include <iostream>
#include <memory>
#include <numbers>

// Funzione per convertire un valore reale in pixel
sf::Vector2f realeToPixel(float x, float y, float scaleFactorX,
                          float scaleFactorY)
{
  return sf::Vector2f(x * scaleFactorX, y * scaleFactorY);
}

constexpr float pi_f = 3.14159265358979323846f;

float calculateRotationAngle(float dx, float dy)
{
  return std::atan2f(dy, dx) * 180.0f / pi_f; // In gradi
}

void simulazione_piano(int n, float d, float ds, float s, float a, float c,
                       float angolo)
{
  constexpr int pixelx = 1000;
  constexpr int pixely = 600;
  sf::RenderWindow window(
      sf::VideoMode(pixelx, pixely),
      "Simulazione del comportamento di uno stormo, di Nisi, Rosini, Seren");
  window.setPosition(sf::Vector2i(50, 70));
  constexpr int frame_rate{60};
  window.setFramerateLimit(frame_rate);

  // Esempio di vettore di posizioni reali
  std::vector<pf::Boid> stormo = pf::genera_stormo(n);

  // Fattori di scala per la conversione
  float scaleFactorX = static_cast<float>(pixelx) / 1.0f;
  float scaleFactorY = static_cast<float>(pixely) / 1.0f;

  // crea una texture (e poi una sprite) con lo sfondo
  sf::Texture texture;
  if (!texture.loadFromFile("sfondo.png")) {
    throw std::runtime_error{"Impossibile caricare l'immagine di sfondo"};
  }
  sf::Sprite sprite;
  sprite.setTexture(texture);

  // Eseguire il loop della finestra finché è aperta
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    window.clear(sf::Color(0, 160, 200, 200));
    window.draw(sprite);

    // Disegnare i punti convertiti in pixel
    for (pf::Boid const& boid : stormo) {
      sf::Vector2f pixelPos = realeToPixel(boid.get_pos().x, boid.get_pos().y,
                                           scaleFactorX, scaleFactorY);
      sf::ConvexShape triangle;
      triangle.setPointCount(3);
      triangle.setPoint(0, sf::Vector2f(0, -5.0)); // Vertice superiore (punta)
      triangle.setPoint(1,
                        sf::Vector2f(-3.0, 5.0)); // Punto a sinistra della base
      triangle.setPoint(2, sf::Vector2f(3.0, 5.0)); // Punto a destra della base
      triangle.setPosition(pixelPos);
      triangle.setFillColor(sf::Color::Black);
      triangle.setOrigin(0, -5.0);

      float targetAngle = calculateRotationAngle(
          normalizzazione(boid.get_vel()).x, normalizzazione(boid.get_vel()).y);
      triangle.setRotation(targetAngle + 90);

      window.draw(triangle);
    }

    pf::movimento(stormo, 0.001f);
    pf::comportamento_bordi(stormo);
    pf::applicazione_regole(stormo, d, ds, s, a, c, angolo);
    pf::controllo_velocità(stormo, 2);

    window.display();
  }
}

void simulazione_piano_due_stormi(int n1, int n2, float d, float ds, float s,
                                  float a, float c, float ds2, float s2,
                                  float angolo)
{
  constexpr int pixelx = 1000;
  constexpr int pixely = 600;
  sf::RenderWindow window(
      sf::VideoMode(pixelx, pixely),
      "Simulazione del comportamento di uno stormo, di Nisi, Rosini, Seren");
  window.setPosition(sf::Vector2i(50, 70));
  constexpr int frame_rate{60};
  window.setFramerateLimit(frame_rate);

  std::vector<pf::Boid> stormo1 = pf::genera_stormo(n1);
  std::vector<pf::Boid> stormo2 = pf::genera_stormo(n2);

  float scaleFactorX = static_cast<float>(pixelx) / 1.0f;
  float scaleFactorY = static_cast<float>(pixely) / 1.0f;

  sf::Texture texture;
  if (!texture.loadFromFile("sfondo.png")) {
    throw std::runtime_error{"Impossibile caricare l'immagine di sfondo"};
  }
  sf::Sprite sprite;
  sprite.setTexture(texture);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    window.clear(sf::Color(0, 160, 200, 200));
    window.draw(sprite);

    for (pf::Boid const& boid : stormo1) {
      sf::Vector2f pixelPos = realeToPixel(boid.get_pos().x, boid.get_pos().y,
                                           scaleFactorX, scaleFactorY);
      sf::ConvexShape triangle;
      triangle.setPointCount(3);
      triangle.setPoint(0, sf::Vector2f(0, -5.0));
      triangle.setPoint(1, sf::Vector2f(-3.0, 5.0));
      triangle.setPoint(2, sf::Vector2f(3.0, 5.0));
      triangle.setPosition(pixelPos);
      triangle.setFillColor(sf::Color::Black);
      triangle.setOrigin(0, -5.0);
      float targetAngle = calculateRotationAngle(
          normalizzazione(boid.get_vel()).x, normalizzazione(boid.get_vel()).y);
      triangle.setRotation(targetAngle + 90);
      window.draw(triangle);
    }
    pf::movimento(stormo1, 0.001f);
    pf::comportamento_bordi(stormo1);
    pf::applicazione_regole_due_stormi(stormo1, stormo2, d, ds, s, a, c, ds2,
                                       s2, angolo);
    pf::controllo_velocità(stormo1, 2.0);

    for (pf::Boid const& boid : stormo2) {
      sf::Vector2f pixelPos = realeToPixel(boid.get_pos().x, boid.get_pos().y,
                                           scaleFactorX, scaleFactorY);
      sf::ConvexShape triangle;
      triangle.setPointCount(3);
      triangle.setPoint(0, sf::Vector2f(0, -5.0));
      triangle.setPoint(1, sf::Vector2f(-3.0, 5.0));
      triangle.setPoint(2, sf::Vector2f(3.0, 5.0));
      triangle.setPosition(pixelPos);
      triangle.setFillColor(sf::Color::Red);
      triangle.setOrigin(0, -5.0);
      float targetAngle = calculateRotationAngle(
          normalizzazione(boid.get_vel()).x, normalizzazione(boid.get_vel()).y);
      triangle.setRotation(targetAngle + 90);
      window.draw(triangle);
    }
    pf::movimento(stormo2, 0.001f);
    pf::comportamento_bordi(stormo2);
    pf::applicazione_regole_due_stormi(stormo2, stormo1, d, ds, s, a, c, ds2,
                                       s2, angolo);
    pf::controllo_velocità(stormo2, 2.0);

    window.display();
  }
}

namespace pf {
sf::Vector2f set_graph_point(int i, float valore, int size, float scaleFactorX,
                             float scaleFactorY, float max_y)
{
  float y = valore / max_y;
  float x = static_cast<float>(i) / static_cast<float>(size);
  return sf::Vector2f(realeToPixel(x, 1.f - y, scaleFactorX, scaleFactorY));
}
} // namespace pf

void grafici(int n, float d, float ds, float s, float a, float c, float angolo)
{
  constexpr int pixelx = 1200;
  constexpr int pixely = 650;
  sf::RenderWindow window(
      sf::VideoMode(pixelx, pixely),
      "Simulazione del comportamento di uno stormo, di Nisi, Rosini, Seren");
  window.setPosition(sf::Vector2i(10, 40));
  constexpr int frame_rate{120};
  window.setFramerateLimit(frame_rate);

  std::vector<pf::Boid> stormo = pf::genera_stormo(n);

  float scaleFactorX = 300.0f / 1.0f;
  float scaleFactorY = 250.0f / 1.0f;

  std::vector<float> meanpos;
  meanpos.push_back(pf::mean_position(stormo));
  std::vector<float> meanvel;
  meanvel.push_back(pf::mean_velocity(stormo));
  std::vector<float> meandist;
  meandist.push_back(pf::mean_distance(stormo));
  std::vector<float> devpos;
  devpos.push_back(pf::standdev_position(stormo));
  std::vector<float> devvel;
  devvel.push_back(pf::standdev_velocity(stormo));
  std::vector<float> devdist;
  devdist.push_back(pf::standdev_distance(stormo));

  sf::Texture sfondo_texture;
  if (!sfondo_texture.loadFromFile("sfondo_grafici.png")) {
    throw std::runtime_error{"Impossibile caricare l'immagine di sfondo"};
  }
  sf::Sprite sfondo_sprite;
  sfondo_sprite.setTexture(sfondo_texture);

  sf::RenderTexture renderTexture;
  if (!renderTexture.create(300, 250)) {
    throw std::runtime_error{
        "Impossibile creare la texture su cui disegnare i grafici"};
  }

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
    window.clear(sf::Color::White);
    window.draw(sfondo_sprite);

    renderTexture.clear(sf::Color(230, 190, 80));
    float max_y = 1.0F;
    for (int i{0}, size = static_cast<int>(meanpos.size()); i != size; ++i) {
      sf::Vector2f pixelPos =
          pf::set_graph_point(i, meanpos[static_cast<long unsigned int>(i)],
                              size, scaleFactorX, scaleFactorY, max_y);
      sf::CircleShape shape(2);
      shape.setPosition(pixelPos);
      shape.setFillColor(sf::Color::Black);
      renderTexture.draw(shape);
    }
    renderTexture.display();
    const sf::Texture& texture1 = renderTexture.getTexture();
    sf::Sprite sprite1(texture1);
    sprite1.setPosition(51.f, 40.f);
    window.draw(sprite1);

    renderTexture.clear(sf::Color(230, 190, 80));
    max_y = 1.0F;
    for (int i{0}, size = static_cast<int>(meanvel.size()); i != size; ++i) {
      sf::Vector2f pixelPos =
          pf::set_graph_point(i, meanvel[static_cast<long unsigned int>(i)],
                              size, scaleFactorX, scaleFactorY, max_y);
      sf::CircleShape shape(2);
      shape.setPosition(pixelPos);
      shape.setFillColor(sf::Color::Black);
      renderTexture.draw(shape);
    }
    renderTexture.display();
    const sf::Texture& texture2 = renderTexture.getTexture();
    sf::Sprite sprite2(texture2);
    sprite2.setPosition(451.f, 40.f);
    window.draw(sprite2);

    renderTexture.clear(sf::Color(230, 190, 80));
    max_y = 0.85F;
    for (int i{0}, size = static_cast<int>(meandist.size()); i != size; ++i) {
      sf::Vector2f pixelPos =
          pf::set_graph_point(i, meandist[static_cast<long unsigned int>(i)],
                              size, scaleFactorX, scaleFactorY, max_y);
      sf::CircleShape shape(2);
      shape.setPosition(pixelPos);
      shape.setFillColor(sf::Color::Black);
      renderTexture.draw(shape);
    }
    renderTexture.display();
    const sf::Texture& texture3 = renderTexture.getTexture();
    sf::Sprite sprite3(texture3);
    sprite3.setPosition(851.f, 40.f);
    window.draw(sprite3);

    renderTexture.clear(sf::Color(230, 190, 80));
    max_y = 0.4F;
    for (int i{0}, size = static_cast<int>(devpos.size()); i != size; ++i) {
      sf::Vector2f pixelPos =
          pf::set_graph_point(i, devpos[static_cast<long unsigned int>(i)],
                              size, scaleFactorX, scaleFactorY, max_y);
      sf::CircleShape shape(2);
      shape.setPosition(pixelPos);
      shape.setFillColor(sf::Color::Black);
      renderTexture.draw(shape);
    }
    renderTexture.display();
    const sf::Texture& texture4 = renderTexture.getTexture();
    sf::Sprite sprite4(texture4);
    sprite4.setPosition(51.f, 365.f);
    window.draw(sprite4);

    renderTexture.clear(sf::Color(230, 190, 80));
    max_y = 0.4F;
    for (int i{0}, size = static_cast<int>(devvel.size()); i != size; ++i) {
      sf::Vector2f pixelPos =
          pf::set_graph_point(i, devvel[static_cast<long unsigned int>(i)],
                              size, scaleFactorX, scaleFactorY, max_y);
      sf::CircleShape shape(2);
      shape.setPosition(pixelPos);
      shape.setFillColor(sf::Color::Black);
      renderTexture.draw(shape);
    }
    renderTexture.display();
    const sf::Texture& texture5 = renderTexture.getTexture();
    sf::Sprite sprite5(texture5);
    sprite5.setPosition(451.f, 365.f);
    window.draw(sprite5);

    renderTexture.clear(sf::Color(230, 190, 80));
    max_y = 0.4F;
    for (int i{0}, size = static_cast<int>(devdist.size()); i != size; ++i) {
      sf::Vector2f pixelPos =
          pf::set_graph_point(i, devdist[static_cast<long unsigned int>(i)],
                              size, scaleFactorX, scaleFactorY, max_y);
      sf::CircleShape shape(2);
      shape.setPosition(pixelPos);
      shape.setFillColor(sf::Color::Black);
      renderTexture.draw(shape);
    }
    renderTexture.display();
    const sf::Texture& texture6 = renderTexture.getTexture();
    sf::Sprite sprite6(texture6);
    sprite6.setPosition(851.f, 365.f);
    window.draw(sprite6);

    pf::movimento(stormo, 0.001f);
    pf::comportamento_bordi(stormo);
    pf::applicazione_regole(stormo, d, ds, s, a, c, angolo);
    pf::controllo_velocità(stormo, 2.0f);

    meanpos.push_back(pf::mean_position(stormo));
    meanvel.push_back(pf::mean_velocity(stormo));
    meandist.push_back(pf::mean_distance(stormo));
    devpos.push_back(pf::standdev_position(stormo));
    devvel.push_back(pf::standdev_velocity(stormo));
    devdist.push_back(pf::standdev_distance(stormo));

    window.display();
  }
}

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
    simulazione_piano(n, d, ds, s, a, c, angolo);
    break;
  case 'b':
    simulazione_piano(200, 0.02f, 0.005f, 0.05f, 0.15f, 0.05f, 150.0f);
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
    grafici(n, d, ds, s, a, c, angolo);
    break;
  case 'd':
    grafici(20, 0.02f, 0.005f, 1.0f, 0.15f, 0.005f, 360.0f);
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
    simulazione_piano_due_stormi(n, n2, d, ds, s, a, c, ds2, s2, angolo);
    break;
  case 'f':
    simulazione_piano_due_stormi(100, 100, 0.03f, 0.0025f, 0.75f, 0.5f, 0.5f,
                                 0.02f, 0.95f, 360.0f);
    break;
  default:
    std::cout << "Carattere non valido";
    break;
  }
  std::cout << '\n' << '\n';
}