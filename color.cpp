#include <SFML/Graphics.hpp>
#include <boost/format.hpp>
#include <iostream>
#include <chrono> 
using namespace std;

int main() {
  int r = 14;
  int g = 210;
  int b = 221;
  sf::Color color(r, g, b);
  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;
  sf::RenderWindow window(sf::VideoMode(400, 600), "Color", sf::Style::Default,
                          settings);
  window.setFramerateLimit(60);
  sf::RectangleShape rectangle(sf::Vector2f(120, 50));

  sf::Font font;

  if (!font.loadFromFile("Helvetica.ttf")) {
    cout << "Error loading font\n";
  }
  sf::Text text;
  text.setFont(font);
  text.setCharacterSize(24);
  text.setColor(sf::Color::Black);
  text.setPosition(20, 20);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
      if (event.type != sf::Event::LostFocus) {
        
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
          // mt19937 mt_rand(time(0)); <-- do not seed like this.
          auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
          mt19937 mt_rand(seed);

          r = mt_rand() % 255;
          g = mt_rand() % 255;
          b = mt_rand() % 255;

          text.setString((boost::format("rgb(%1%,%2%,%3%)") % r % g % b).str());

          window.clear(sf::Color(r, g, b));
          window.draw(text);
          window.display();
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
          const char *rgb =
              (boost::format("rgb(%1%,%2%,%3%)") % r % g % b).str().c_str();
          const char *fmt =
              (boost::format("echo %1%|xclip -sel clip") % rgb).str().c_str();
          system(fmt);
          cout << "Copied to clipboard" << endl;
        }
      }
    }
  }

  return 0;
}