#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include "../../Include/DebugWindow/DebugWindow.h" // Adjust to the correct path
#include <stdexcept>

// Constructor
DebugWindow::DebugWindow(const std::vector<GameObject*>& trackedObjects)
    : debugWindow(sf::VideoMode({ 400, 600 }), "Debug Window", sf::Style::Titlebar | sf::Style::Close),
    isVisible(false),
    objects(trackedObjects) {
    debugWindow.setFramerateLimit(30);
}

// Toggle visibility
void DebugWindow::toggleVisibility() {
    isVisible = !isVisible;
}

// Draw the debug window
void DebugWindow::draw() {
    if (!isVisible || !debugWindow.isOpen())
        return;

    debugWindow.clear(sf::Color::Black);

    sf::Font font;
    if (!font.openFromFile("D:/Personal Projects/Working Title - Kryptos/Krytpos/Engine/KryptosEngine/Assets/Fonts/DebugWindowFont/AtkinsonHyperlegible-Regular.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }
    else {
		std::cout << "Font loaded successfully!" << std::endl;
    }

    sf::Text text(font, "Debug Info", 14); // Pass string, font, and size
    text.setFillColor(sf::Color::White);

    float yOffset = 10.f;

    for (const auto& object : objects) {
        if (!object->isActive()) continue;

        text.setString(
            "Name: " + object->getName() + "\n" +
            "Position: (" + std::to_string(object->getPosition().x) + ", " + std::to_string(object->getPosition().y) + ")"
        );
        text.setPosition(sf::Vector2f(10.f, yOffset));
        yOffset += 50.f;

        debugWindow.draw(text);
    }

    debugWindow.display();
}

// Check if debug window is open
bool DebugWindow::isOpen() const {
    return debugWindow.isOpen();
}
