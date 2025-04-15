/**
 * @file DebugWindow.cpp
 * @brief Implementation of the DebugWindow class for runtime graphical debugging.
 * @ingroup DebugSystem
 */

#include "../../Include/DebugWindow/DebugWindow.h"

namespace KryptosEngine {
    namespace DebugWindow {

        /**
         * @brief Constructs a DebugWindow and sets the default toggle key to F1.
         */
        DebugWindow::DebugWindow()
            : debugWindow(),
            isVisible(false),
            toggleKey(sf::Keyboard::Key::F1) {}

        /**
         * @brief Sets up the debug window, loads fonts, and sets framerate.
         * Logs the result using the DebugWindowLogger.
         *
         * @throws std::runtime_error if the debug font fails to load.
         */
        void DebugWindow::initialise() {
            debugWindow.setFramerateLimit(60);

            if (!defaultFont.openFromFile("Assets/EngineAssets/Fonts/DebugWindowFont/AtkinsonHyperlegible-Regular.ttf")) {
                KryptosEngine::DebugWindowLogger::GetLogger()->error("Failed to load DebugWindow font");
            }
            else {
                KryptosEngine::DebugWindowLogger::GetLogger()->info("DebugWindow font loaded successfully");
            }

            KryptosEngine::DebugWindowLogger::GetLogger()->info("DebugWindow initialised successfully");
        }

        /**
         * @brief Checks if the toggle key is pressed and toggles the debug window if necessary.
         * Should be called once per frame.
         */
        void DebugWindow::handleInput() {
            if (sf::Keyboard::isKeyPressed(toggleKey) && !debugWindow.isOpen()) {
                toggleVisibility();
            }
        }

        /**
         * @brief Toggles the debug window's visibility.
         * If toggled on, creates the window. If off, closes it.
         */
        void DebugWindow::toggleVisibility() {
            isVisible = !isVisible;

            if (isVisible) {
                if (!debugWindow.isOpen()) {
                    debugWindow.create(
                        sf::VideoMode({ 400, 600 }),
                        "Debug Window",
                        sf::Style::Titlebar | sf::Style::Close
                    );
                    KryptosEngine::DebugWindowLogger::GetLogger()->info("DebugWindow opened successfully");
                }
            }
            else {
                close();
            }
        }

        /**
         * @brief Closes the debug window and logs the action.
         */
        void DebugWindow::close() {
            if (debugWindow.isOpen()) {
                debugWindow.close();
            }

            isVisible = false;
            KryptosEngine::DebugWindowLogger::GetLogger()->info("DebugWindow closed successfully");
        }

        /**
         * @brief Returns whether the debug window is currently open.
         *
         * @return True if the debug window is open; false otherwise.
         */
        bool DebugWindow::isOpen() const {
            return debugWindow.isOpen();
        }

        /**
         * @brief Renders the contents of the debug window.
         * Displays name, transform, physics state, and tracked debug variables for all active GameObjects.
         */
        void DebugWindow::draw() {
            if (!isVisible || !debugWindow.isOpen()) return;

            bool mouseClicked = false;
            sf::Vector2<float> mousePosF;

            // Poll SFML events
            while (const std::optional<sf::Event> event = debugWindow.pollEvent()) {
                if (event->is<sf::Event::Closed>()) {
                    close();
                    return;
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

            // Loop through all active GameObjects
            for (const auto& object : GameObjectManager::getInstance().getGameObjects()) {
                if (!object->isActive()) continue;

                // Draw object name
                sf::String displayName = sf::String("Name: ") + object->getName();
                sf::Text nameText(defaultFont, displayName, 14);
                nameText.setFillColor(sf::Color::White);
                nameText.setPosition(sf::Vector2f(10.f, yOffset));
                debugWindow.draw(nameText);

                // Toggle expanded view on click
                if (mouseClicked && nameText.getGlobalBounds().contains(mousePosF)) {
                    expandedState[object] = !expandedState[object];
                }

                yOffset += 20.f;

                if (expandedState[object]) {
                    // Show Position
                    sf::Text positionText(defaultFont,
                        "Position: (" + std::to_string(object->getPosition().x) + ", " +
                        std::to_string(object->getPosition().y) + ")", 14);
                    positionText.setFillColor(sf::Color::White);
                    positionText.setPosition(sf::Vector2f(20.f, yOffset));
                    debugWindow.draw(positionText);
                    yOffset += 20.f;

                    // Show Rotation
                    sf::Text rotationText(defaultFont,
                        "Rotation: " + std::to_string(object->getRotation().asDegrees()) + " degrees", 14);
                    rotationText.setFillColor(sf::Color::White);
                    rotationText.setPosition(sf::Vector2f(20.f, yOffset));
                    debugWindow.draw(rotationText);
                    yOffset += 20.f;

                    // Show Mass
                    sf::Text massText(defaultFont,
                        "Mass: " + std::to_string(object->getMass()), 14);
                    massText.setFillColor(sf::Color::White);
                    massText.setPosition(sf::Vector2f(20.f, yOffset));
                    debugWindow.draw(massText);
                    yOffset += 20.f;

                    // Show Gravity toggle
                    sf::Text gravityText(defaultFont,
                        "Use Gravity: " + std::string(object->getUseGravity() ? "true" : "false"), 14);
                    gravityText.setFillColor(sf::Color::White);
                    gravityText.setPosition(sf::Vector2f(20.f, yOffset));
                    debugWindow.draw(gravityText);
                    yOffset += 20.f;

                    // Show tracked debug values
                    const auto& trackedVars = object->getDebugTrackedValues();
                    for (const auto& [name, getter] : trackedVars) {
                        sf::Text trackedVarText(defaultFont, name + ": " + getter(), 14);
                        trackedVarText.setFillColor(sf::Color::White);
                        trackedVarText.setPosition(sf::Vector2f(20.f, yOffset));
                        debugWindow.draw(trackedVarText);
                        yOffset += 20.f;
                    }
                }

                yOffset += 10.f; // space between objects
            }

            debugWindow.display();
        }

    } // namespace DebugWindow
} // namespace KryptosEngine
