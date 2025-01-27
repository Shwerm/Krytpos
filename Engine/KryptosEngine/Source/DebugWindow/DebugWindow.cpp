/*
 * DebugWindow.cpp - Kryptos Debugging Interface
 * ---------------------------------------------
 * Implements the DebugWindow class for providing a graphical debugging interface.
 * Allows visualization and interaction with game object states during runtime.
 *
 * Author: Sam Camilleri, Mural Studios
 * All Rights Reserved, 2025.
 *
 * Dependencies:
 *   - Graphics.hpp: Provides SFML graphics components.
 *   - iostream: Standard I/O for debugging.
 *   - Text.hpp, Font.hpp: SFML text and font handling.
 *   - DebugWindow.h: Header for DebugWindow class.
 *   - stdexcept: For exception handling.
 */

#include "../Include/DebugWindow/DebugWindow.h"
#include "../Include/PlayerClass/Player.h"
#include <SFML/Window/Event.hpp>
#include <stdexcept>
#include <iostream>

namespace KryptosEngine {
    namespace DebugWindow {
        /**
         * @brief Constructs a DebugWindow object.
         * Does not initialize resources. Use `initialize()` to complete setup.
         */
        DebugWindow::DebugWindow()
            : debugWindow(),
            isVisible(false),
            toggleKey(sf::Keyboard::Key::F1) { // Default toggle key: `F1`
        }

        /**
         * @brief Initializes the debug window.
         * Loads the default font and sets up the window's initial state.
         * @throw std::runtime_error if the font fails to load.
         */
        void DebugWindow::initialise() {
            debugWindow.setFramerateLimit(60);

            if (!defaultFont.openFromFile("EngineAssets/Fonts/DebugWindowFont/AtkinsonHyperlegible-Regular.ttf")) {
                throw std::runtime_error("Failed to load default font for DebugWindow");
            }
        }

        /**
         * @brief Handles keyboard input for toggling the debug window.
         * Monitors the assigned toggle key and switches the window's visibility when pressed.
         */
        void DebugWindow::handleInput() {
            if (sf::Keyboard::isKeyPressed(toggleKey) && !debugWindow.isOpen()) {
                toggleVisibility();
            }
        }

        /**
         * @brief Toggles the visibility of the debug window.
         * Opens the debug window if currently closed, or closes it if open.
         */
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

        /**
         * @brief Renders the debug window.
         * Displays game object names, properties, and debug-tracked values.
         * Handles user interaction with the window's elements.
         */
        void DebugWindow::draw() {
            if (!isVisible || !debugWindow.isOpen()) {
                return;
            }

            bool mouseClicked = false;
            sf::Vector2<float> mousePosF;

            // Process events in the debug window
            while (const std::optional<sf::Event> event = debugWindow.pollEvent()) {
                if (event->is<sf::Event::Closed>()) {
                    close();
                    return; // Exit if the window is closed
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

                // Render game object name
                sf::String displayName = sf::String("Name: ") + object->getName();
                sf::Text nameText(defaultFont, displayName, 14);
                nameText.setFillColor(sf::Color::White);
                nameText.setPosition(sf::Vector2f(10.f, yOffset));
                debugWindow.draw(nameText);

                // Handle mouse clicks on object names
                if (mouseClicked && nameText.getGlobalBounds().contains(mousePosF)) {
                    expandedState[object] = !expandedState[object];
                }

                yOffset += 20.f;

                // Render additional details if expanded
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

                    sf::Text rotationText(defaultFont,
                        sf::String("Rotation: " + std::to_string(object->getRotation().asDegrees()) + " degrees"),
                        14);
                    rotationText.setFillColor(sf::Color::White);
                    rotationText.setPosition(sf::Vector2f(20.f, yOffset));
                    debugWindow.draw(rotationText);
                    yOffset += 20.f;

                    sf::Text massText(defaultFont,
                        sf::String("Mass: " + std::to_string(object->getMass())),
                        14);
                    massText.setFillColor(sf::Color::White);
                    massText.setPosition(sf::Vector2f(20.f, yOffset));
                    debugWindow.draw(massText);
                    yOffset += 20.f;

                    sf::Text gravityText(defaultFont,
                        sf::String("Use Gravity: " + std::string(object->getUseGravity() ? "true" : "false")),
                        14);
                    gravityText.setFillColor(sf::Color::White);
                    gravityText.setPosition(sf::Vector2f(20.f, yOffset));
                    debugWindow.draw(gravityText);
                    yOffset += 20.f;

                    const auto& trackedVars = object->getDebugTrackedValues();
                    for (const auto& [name, getter] : trackedVars) {
                        sf::Text trackedVarText(defaultFont, name + ": " + getter(), 14);
                        trackedVarText.setFillColor(sf::Color::White);
                        trackedVarText.setPosition(sf::Vector2f(20.f, yOffset));
                        debugWindow.draw(trackedVarText);
                        yOffset += 20.f;
                    }
                }

                yOffset += 10.f; // Add spacing between objects
            }

            debugWindow.display();
        }

        /**
         * @brief Closes the debug window.
         * Releases resources associated with the window and resets visibility.
         */
        void DebugWindow::close() {
            if (debugWindow.isOpen()) {
                debugWindow.close();
            }
            isVisible = false;
        }

        /**
         * @brief Checks if the debug window is open.
         * @return True if the debug window is open, false otherwise.
         */
        bool DebugWindow::isOpen() const {
            return debugWindow.isOpen();
        }
    } // namespace DebugWindow
} // namespace KryptosEngine



