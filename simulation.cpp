#include "simulation.hpp"
#include <memory>
#include <string>

namespace pf {

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

  // Vettore di boids, ossia lo stormo
  std::vector<Boid> stormo = genera_stormo(n);

  // Fattori di scala per la conversione
  float scaleFactorX = static_cast<float>(pixelx) / 1.0f;
  float scaleFactorY = static_cast<float>(pixely) / 1.0f;

  // Crea una texture (e poi una sprite) con lo sfondo
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
    for (Boid const& boid : stormo) {
      sf::Vector2f pixelPos = realeToPixel(boid.get_pos().x, boid.get_pos().y,
                                           scaleFactorX, scaleFactorY);
      sf::ConvexShape triangle;
      triangle.setPointCount(3);
      triangle.setPoint(0, sf::Vector2f(0, -3.3f)); // Vertice superiore (punta)
      triangle.setPoint(
          1, sf::Vector2f(-2.0f, 3.3f)); // Punto a sinistra della base
      triangle.setPoint(2,
                        sf::Vector2f(2.0f, 3.3f)); // Punto a destra della base
      triangle.setPosition(pixelPos);
      triangle.setFillColor(sf::Color::Black);
      triangle.setOrigin(0, -3.3f);

      float targetAngle = calculateRotationAngle(
          normalizzazione(boid.get_vel()).x, normalizzazione(boid.get_vel()).y);
      triangle.setRotation(targetAngle + 90);

      window.draw(triangle);
    }

    movimento(stormo, 0.001f);
    comportamento_bordi(stormo);
    applicazione_regole(stormo, d, ds, s, a, c, angolo);
    random_boost(stormo, 0.01f, 0.01f);
    controllo_velocità(stormo, 2);

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

  std::vector<Boid> stormo1 = genera_stormo(n1);
  std::vector<Boid> stormo2 = genera_stormo(n2);

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

    for (Boid const& boid : stormo1) {
      sf::Vector2f pixelPos = realeToPixel(boid.get_pos().x, boid.get_pos().y,
                                           scaleFactorX, scaleFactorY);
      sf::ConvexShape triangle;
      triangle.setPointCount(3);
      triangle.setPoint(0, sf::Vector2f(0, -3.3f));
      triangle.setPoint(1, sf::Vector2f(-2.0f, 3.3f));
      triangle.setPoint(2, sf::Vector2f(2.0f, 3.3f));
      triangle.setPosition(pixelPos);
      triangle.setFillColor(sf::Color::Black);
      triangle.setOrigin(0, -3.3f);
      float targetAngle = calculateRotationAngle(
          normalizzazione(boid.get_vel()).x, normalizzazione(boid.get_vel()).y);
      triangle.setRotation(targetAngle + 90);
      window.draw(triangle);
    }
    movimento(stormo1, 0.001f);
    comportamento_bordi(stormo1);
    applicazione_regole_due_stormi(stormo1, stormo2, d, ds, s, a, c, ds2, s2,
                                   angolo);
    random_boost(stormo1, 0.01f, 0.01f);
    controllo_velocità(stormo1, 2.0);

    for (Boid const& boid : stormo2) {
      sf::Vector2f pixelPos = realeToPixel(boid.get_pos().x, boid.get_pos().y,
                                           scaleFactorX, scaleFactorY);
      sf::ConvexShape triangle;
      triangle.setPointCount(3);
      triangle.setPoint(0, sf::Vector2f(0, -3.3f));
      triangle.setPoint(1, sf::Vector2f(-2.0f, 3.3f));
      triangle.setPoint(2, sf::Vector2f(2.0f, 3.3f));
      triangle.setPosition(pixelPos);
      triangle.setFillColor(sf::Color::Red);
      triangle.setOrigin(0, -3.3f);
      float targetAngle = calculateRotationAngle(
          normalizzazione(boid.get_vel()).x, normalizzazione(boid.get_vel()).y);
      triangle.setRotation(targetAngle + 90);
      window.draw(triangle);
    }
    movimento(stormo2, 0.001f);
    comportamento_bordi(stormo2);
    applicazione_regole_due_stormi(stormo2, stormo1, d, ds, s, a, c, ds2, s2,
                                   angolo);
    random_boost(stormo2, 0.01f, 0.01f);
    controllo_velocità(stormo2, 2.0f);

    window.display();
  }
}

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

  std::vector<Boid> stormo = genera_stormo(n);

  float scaleFactorX = 300.0f / 1.0f;
  float scaleFactorY = 250.0f / 1.0f;

  std::vector<float> meanpos;
  meanpos.push_back(mean_position(stormo));
  std::vector<float> meanvel;
  meanvel.push_back(mean_velocity(stormo));
  std::vector<float> meandist;
  meandist.push_back(mean_distance(stormo));
  std::vector<float> devpos;
  devpos.push_back(standdev_position(stormo));
  std::vector<float> devvel;
  devvel.push_back(standdev_velocity(stormo));
  std::vector<float> devdist;
  devdist.push_back(standdev_distance(stormo));

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
  sf::RenderTexture renderTextureTime;
  if (!renderTextureTime.create(355, 15)) {
    throw std::runtime_error{
        "Impossibile creare la texture su cui scrivere il tempo"};
  }

  sf::Clock clock;
  sf::Font font;
  if (!font.loadFromFile("cambria.ttc")) {
    throw std::runtime_error{"Impossibile caricare il font"};
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
          set_graph_point(i, meanpos[static_cast<long unsigned int>(i)], size,
                          scaleFactorX, scaleFactorY, max_y);
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
          set_graph_point(i, meanvel[static_cast<long unsigned int>(i)], size,
                          scaleFactorX, scaleFactorY, max_y);
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
          set_graph_point(i, meandist[static_cast<long unsigned int>(i)], size,
                          scaleFactorX, scaleFactorY, max_y);
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
          set_graph_point(i, devpos[static_cast<long unsigned int>(i)], size,
                          scaleFactorX, scaleFactorY, max_y);
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
          set_graph_point(i, devvel[static_cast<long unsigned int>(i)], size,
                          scaleFactorX, scaleFactorY, max_y);
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
          set_graph_point(i, devdist[static_cast<long unsigned int>(i)], size,
                          scaleFactorX, scaleFactorY, max_y);
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

    renderTextureTime.clear(sf::Color::White);
    sf::Time time = clock.getElapsedTime();
    float sec     = time.asSeconds();
    std::string tempo{std::to_string(sec)};
    std::string tempo_approssimato{tempo.substr(0, 3)};
    sf::Text text;
    text.setFont(font);
    text.setString(tempo_approssimato);
    text.setCharacterSize(10);
    text.setFillColor(sf::Color::Black);
    text.setPosition(288.F, 2.F);
    renderTextureTime.draw(text);
    tempo              = std::to_string(sec / 2.f);
    tempo_approssimato = tempo.substr(0, 3);
    text.setString(tempo_approssimato);
    text.setPosition(138.F, 2.F);
    renderTextureTime.draw(text);
    tempo              = std::to_string(sec / 4.f);
    tempo_approssimato = tempo.substr(0, 3);
    text.setString(tempo_approssimato);
    text.setPosition(63.F, 2.F);
    renderTextureTime.draw(text);
    tempo              = std::to_string(sec * 3.F / 4.f);
    tempo_approssimato = tempo.substr(0, 3);
    text.setString(tempo_approssimato);
    text.setPosition(213.F, 2.F);
    renderTextureTime.draw(text);
    renderTextureTime.display();
    text.setString("tempo (s)");
    text.setPosition(307.F, 2.F);
    renderTextureTime.draw(text);
    renderTextureTime.display();
    const sf::Texture& texture_time = renderTextureTime.getTexture();
    sf::Sprite sprite_time(texture_time);
    sprite_time.setPosition(50.f, 296.f);
    window.draw(sprite_time);
    sprite_time.setPosition(450.f, 296.f);
    window.draw(sprite_time);
    sprite_time.setPosition(850.f, 296.f);
    window.draw(sprite_time);
    sprite_time.setPosition(50.f, 621.f);
    window.draw(sprite_time);
    sprite_time.setPosition(450.f, 621.f);
    window.draw(sprite_time);
    sprite_time.setPosition(850.f, 621.f);
    window.draw(sprite_time);

    movimento(stormo, 0.001f);
    comportamento_bordi(stormo);
    applicazione_regole(stormo, d, ds, s, a, c, angolo);
    controllo_velocità(stormo, 2.0f);

    meanpos.push_back(mean_position(stormo));
    meanvel.push_back(mean_velocity(stormo));
    meandist.push_back(mean_distance(stormo));
    devpos.push_back(standdev_position(stormo));
    devvel.push_back(standdev_velocity(stormo));
    devdist.push_back(standdev_distance(stormo));

    window.display();
  }
}
} // namespace pf