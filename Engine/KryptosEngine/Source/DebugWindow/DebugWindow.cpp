/*
Debug Window source - Kryptos - Sam Camilleri, Mural Studios
All Rights Reserved 2025.
Dependencies: Graphics.hpp, iostream, Text.hpp, Font.hpp, DebugWindow.h, stdexcept
*/
#include "../Include/DebugWindow/DebugWindow.h"
#include "../Include/PlayerClass/Player.h"

#include <stdexcept>
#include <iostream>
// Constructor
DebugWindow::DebugWindow()
    : debugWindow(sf::VideoMode({ 400, 600 }), "Debug Window", sf::Style::Titlebar | sf::Style::Close),
    isVisible(false) {
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
    if (!font.openFromFile("EngineAssets/Fonts/DebugWindowFont/AtkinsonHyperlegible-Regular.ttf")) {
        std::cout << "Failed to load font!" << std::endl;
        return;
    }

    sf::Text text(font, " ", 14);
    text.setFillColor(sf::Color::White);

    float yOffset = 10.f;

    // Iterate through all game objects
    for (const auto& object : GameObjectManager::getInstance().getGameObjects()) {
        if (!object->isActive()) continue;

        // Show the object's name
        text.setString("Name: " + object->getName());
        text.setPosition(sf::Vector2f(10.f, yOffset));
        debugWindow.draw(text);
        yOffset += 20.f;

        // Toggle dropdown state
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(debugWindow);
            if (mousePos.y >= yOffset - 20.f && mousePos.y < yOffset) {
                expandedState[object] = !expandedState[object];
            }
        }

        if (expandedState[object]) {
            // Show the object's position
            text.setString("Position: (" +
                std::to_string(object->getPosition().x) + ", " +
                std::to_string(object->getPosition().y) + ")");
            text.setPosition(sf::Vector2f(20.f, yOffset));
            debugWindow.draw(text);
            yOffset += 20.f;

            // If the object is a Player, show additional attributes
            if (auto player = dynamic_cast<Player*>(object)) {
                text.setString("Health: " + std::to_string(player->getHealth()));
                text.setPosition(sf::Vector2f(20.f, yOffset));
                debugWindow.draw(text);
                yOffset += 20.f;

                text.setString("Attack Speed: " + std::to_string(player->getAttackSpeed()));
                text.setPosition(sf::Vector2f(20.f, yOffset));
                debugWindow.draw(text);
                yOffset += 20.f;

                text.setString("Movement Speed: " + std::to_string(player->getMovementSpeed()));
                text.setPosition(sf::Vector2f(20.f, yOffset));
                debugWindow.draw(text);
                yOffset += 20.f;

                text.setString("Attack Multiplier: " + std::to_string(player->getAttackMultiplier()));
                text.setPosition(sf::Vector2f(20.f, yOffset));
                debugWindow.draw(text);
                yOffset += 20.f;

                text.setString("Jump Multiplier: " + std::to_string(player->getJumpMultiplier()));
                text.setPosition(sf::Vector2f(20.f, yOffset));
                debugWindow.draw(text);
                yOffset += 20.f;
            }
        }

        yOffset += 10.f;
    }

    debugWindow.display();
}


// Check if debug window is open
bool DebugWindow::isOpen() const {
    return debugWindow.isOpen();
}

