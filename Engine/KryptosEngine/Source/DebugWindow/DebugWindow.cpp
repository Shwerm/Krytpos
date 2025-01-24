/*
Debug Window source - Kryptos - Sam Camilleri, Mural Studios
All Rights Reserved 2025.
Dependencies: Graphics.hpp, iostream, Text.hpp, Font.hpp, DebugWindow.h, stdexcept
*/
#include "../Include/DebugWindow/DebugWindow.h"
#include "../Include/PlayerClass/Player.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Rect.hpp>


#include <stdexcept>
#include <iostream>
// Constructor
DebugWindow::DebugWindow()
    : debugWindow(),
    isVisible(false),
    toggleKey(sf::Keyboard::Key::F1) { // Default toggle key: `F1`
    debugWindow.setFramerateLimit(60);
}

// Handle input for toggling debug window
void DebugWindow::handleInput() {
    if (sf::Keyboard::isKeyPressed(toggleKey) && !debugWindow.isOpen()) {
        toggleVisibility();
    }
}

// Toggle visibility
void DebugWindow::toggleVisibility() {
    isVisible = !isVisible;

    if (isVisible) {
        if (!debugWindow.isOpen()) {
            debugWindow.create(sf::VideoMode({ 400, 600 }), "Debug Window", sf::Style::Titlebar | sf::Style::Close);
        }
    }
    else {
        close();
    }
}

// Draw the debug window
void DebugWindow::draw() {
    if (!isVisible || !debugWindow.isOpen())
        return;

    // Process events for the debug window
    while (const std::optional<sf::Event> event = debugWindow.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            close(); // Close the debug window when the "X" button is clicked
            return;
        }

        // Check for a single left mouse button press
        if (event->is<sf::Event::MouseButtonPressed>() &&
            event->getIf<sf::Event::MouseButtonPressed>()->button == sf::Mouse::Button::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(debugWindow);

            float yOffset = 10.f; // Reset yOffset to match the rendering loop
            for (const auto& object : GameObjectManager::getInstance().getGameObjects()) {
                if (!object->isActive()) continue;

                // Check if the mouse clicked on the object's name
                sf::FloatRect nameBounds(sf::Vector2<float>(10.f, yOffset), sf::Vector2<float>(200.f, 20.f)); // Position and size as vectors

                // Convert mouse position to float vector
                sf::Vector2<float> mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

                if (nameBounds.contains(mousePosF)) {
                    expandedState[object] = !expandedState[object]; // Toggle dropdown
                }



                // Increment yOffset to match positioning in the rendering loop
                yOffset += 20.f;
                if (expandedState[object]) {
                    yOffset += 100.f; // Space for dropdown details
                }
            }
        }
    }

    debugWindow.clear(sf::Color::Black);

    sf::Font font;
    if (!font.openFromFile("EngineAssets/Fonts/DebugWindowFont/AtkinsonHyperlegible-Regular.ttf")) {
        std::cout << "Failed to load font!" << std::endl;
        return;
    }

    sf::Text text(font, " ", 14);
    text.setFillColor(sf::Color::White);

    float yOffset = 10.f;

    // Iterate through all game objects and render their details
    for (const auto& object : GameObjectManager::getInstance().getGameObjects()) {
        if (!object->isActive()) continue;

        // Show the object's name
        text.setString("Name: " + object->getName() + "->");
        text.setPosition(sf::Vector2f(10.f, yOffset));
        debugWindow.draw(text);
        yOffset += 20.f;

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


// Close the debug window
void DebugWindow::close() {
    if (debugWindow.isOpen()) {
        debugWindow.close();
    }
	isVisible = false;
}

// Check if debug window is open
bool DebugWindow::isOpen() const {
    return debugWindow.isOpen();
}

