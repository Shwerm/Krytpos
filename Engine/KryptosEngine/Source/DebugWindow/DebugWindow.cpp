/*
Debug Window source - Kryptos - Sam Camilleri, Mural Studios
All Rights Reserved 2025.
Dependencies: Graphics.hpp, iostream, Text.hpp, Font.hpp, DebugWindow.h, stdexcept
*/
#include "../Include/DebugWindow/DebugWindow.h"
#include "../Include/PlayerClass/Player.h"
#include <SFML/Window/Event.hpp>
#include <SFML/System/String.hpp>

#include <stdexcept>
#include <iostream>

// Constructor
DebugWindow::DebugWindow()
    : debugWindow(),
    isVisible(false),
    toggleKey(sf::Keyboard::Key::F1) { // Default toggle key: `F1`
    debugWindow.setFramerateLimit(60);

    if (!defaultFont.openFromFile("EngineAssets/Fonts/DebugWindowFont/AtkinsonHyperlegible-Regular.ttf")) {
        throw std::runtime_error("Failed to load default font for DebugWindow");
    }
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

void DebugWindow::draw() {
    if (!isVisible || !debugWindow.isOpen())
        return;

    bool mouseClicked = false;
    sf::Vector2<float> mousePosF;

    // Process events for the debug window
    while (const std::optional<sf::Event> event = debugWindow.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            close();
            return; // Close the debug window
        }

        if (event->is<sf::Event::MouseButtonPressed>() &&
            event->getIf<sf::Event::MouseButtonPressed>()->button == sf::Mouse::Button::Left) {
            mouseClicked = true;
            sf::Vector2i mousePos = sf::Mouse::getPosition(debugWindow);
            mousePosF = sf::Vector2<float>(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
        }
    }

    debugWindow.clear(sf::Color::Black);

    float yOffset = 10.f;

    for (const auto& object : GameObjectManager::getInstance().getGameObjects()) {
        if (!object->isActive()) continue;

        // Create the name text
        sf::String displayName = sf::String("Name: ") + object->getName();
        sf::Text nameText(defaultFont, displayName, 14); // Correct parameter order
        nameText.setFillColor(sf::Color::White);
        nameText.setPosition(sf::Vector2f(10.f, yOffset));
        debugWindow.draw(nameText);

        // Check for mouse click on this text
        if (mouseClicked && nameText.getGlobalBounds().contains(mousePosF)) {
            expandedState[object] = !expandedState[object];
        }

        yOffset += 20.f;

        // Draw expanded details if the object is expanded
        if (expandedState[object]) {
            sf::Text positionText(defaultFont,
                sf::String("Position: (" +
                    std::to_string(object->getPosition().x) + ", " +
                    std::to_string(object->getPosition().y) + ")"),
                14);
            positionText.setFillColor(sf::Color::White);
            positionText.setPosition(sf::Vector2f(20.f, yOffset));
            debugWindow.draw(positionText);

            yOffset += 20.f;

            if (auto player = dynamic_cast<Player*>(object)) {
                std::vector<std::pair<std::string, float>> attributes = {
                    {"Health", player->getHealth()},
                    {"Attack Speed", player->getAttackSpeed()},
                    {"Movement Speed", player->getMovementSpeed()},
                    {"Attack Multiplier", player->getAttackMultiplier()},
                    {"Jump Multiplier", player->getJumpMultiplier()} };

                for (const auto& [label, value] : attributes) {
                    sf::Text attributeText(defaultFont,
                        sf::String(label + ": " + std::to_string(value)),
                        14);
                    attributeText.setFillColor(sf::Color::White);
                    attributeText.setPosition(sf::Vector2f(20.f, yOffset));
                    debugWindow.draw(attributeText);
                    yOffset += 20.f;
                }
            }
        }

        yOffset += 10.f; // Add spacing between objects
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

