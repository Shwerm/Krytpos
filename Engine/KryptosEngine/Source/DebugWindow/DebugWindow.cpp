/**
 * @file DebugWindow.cpp
 * @brief Implementation of the DebugWindow class for runtime graphical debugging.
 * @ingroup DebugSystem
 */

#include "../Include/DebugWindow/DebugWindow.h"

namespace KryptosEngine {
    namespace DebugWindow {

        /**
         * @brief Default constructor for DebugWindow.
         * Initializes internal state variables but does not create a window.
         */
        DebugWindow::DebugWindow()
            : debugWindow(),
            isVisible(false),
            toggleKey(sf::Keyboard::Key::F1) // F1 used to toggle visibility
        {
        }

        /**
         * @brief Initializes the debug window and loads the required font.
         * Sets the frame rate and logs success or failure.
         * @throw std::runtime_error if the font cannot be loaded.
         */
        void DebugWindow::initialise() {
            debugWindow.setFramerateLimit(60);

            // Attempt to load the default font from disk
            if (!defaultFont.openFromFile("EngineAssets/Fonts/DebugWindowFont/AtkinsonHyperlegible-Regular.ttf")) {
                KryptosEngine::DebugWindowLogger::GetLogger()->error("Failed to load DebugWindow font");
            }
            else {
                KryptosEngine::DebugWindowLogger::GetLogger()->info("DebugWindow font loaded successfully");
            }

            KryptosEngine::DebugWindowLogger::GetLogger()->info("DebugWindow initialised successfully");
        }

        /**
         * @brief Listens for input to toggle the debug window.
         * If the toggle key is pressed and the window is not open, it switches the visibility.
         */
        void DebugWindow::handleInput() {
            if (sf::Keyboard::isKeyPressed(toggleKey) && !debugWindow.isOpen()) {
                toggleVisibility();
            }
        }

        /**
         * @brief Toggles the debug window on or off.
         * Creates the SFML window if toggled on and not already open.
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
         * @brief Draws all debug information to the debug window.
         * Displays game object names, details, and any tracked variables.
         */
        void DebugWindow::draw() {
            if (!isVisible || !debugWindow.isOpen()) return;

            bool mouseClicked = false;
            sf::Vector2<float> mousePosF;

            // Event polling and interaction handling
            while (const std::optional<sf::Event> event = debugWindow.pollEvent()) {
                if (event->is<sf::Event::Closed>()) {
                    close();
                    return;
                }

                // Mouse click detection for expand/collapse
                if (event->is<sf::Event::MouseButtonPressed>() &&
                    event->getIf<sf::Event::MouseButtonPressed>()->button == sf::Mouse::Button::Left) {
                    mouseClicked = true;
                    sf::Vector2i mousePos = sf::Mouse::getPosition(debugWindow);
                    mousePosF = sf::Vector2<float>(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
                }
            }

            debugWindow.clear(sf::Color::Black);
            float yOffset = 10.f;

            // Iterate over all game objects in the engine
            for (const auto& object : GameObjectManager::getInstance().getGameObjects()) {
                if (!object->isActive()) continue;

                // Draw the object name
                sf::String displayName = sf::String("Name: ") + object->getName();
                sf::Text nameText(defaultFont, displayName, 14);
                nameText.setFillColor(sf::Color::White);
                nameText.setPosition(sf::Vector2f(10.f, yOffset));
                debugWindow.draw(nameText);

                // Expand or collapse object info
                if (mouseClicked && nameText.getGlobalBounds().contains(mousePosF)) {
                    expandedState[object] = !expandedState[object];
                }

                yOffset += 20.f;

                if (expandedState[object]) {
                    // Position data
                    sf::Text positionText(defaultFont,
                        sf::String("Position: (" +
                            std::to_string(object->getPosition().x) + ", " +
                            std::to_string(object->getPosition().y) + ")"),
                        14);
                    positionText.setFillColor(sf::Color::White);
                    positionText.setPosition(sf::Vector2f(20.f, yOffset));
                    debugWindow.draw(positionText);
                    yOffset += 20.f;

                    // Rotation data
                    sf::Text rotationText(defaultFont,
                        sf::String("Rotation: " + std::to_string(object->getRotation().asDegrees()) + " degrees"),
                        14);
                    rotationText.setFillColor(sf::Color::White);
                    rotationText.setPosition(sf::Vector2f(20.f, yOffset));
                    debugWindow.draw(rotationText);
                    yOffset += 20.f;

                    // Mass data
                    sf::Text massText(defaultFont,
                        sf::String("Mass: " + std::to_string(object->getMass())),
                        14);
                    massText.setFillColor(sf::Color::White);
                    massText.setPosition(sf::Vector2f(20.f, yOffset));
                    debugWindow.draw(massText);
                    yOffset += 20.f;

                    // Gravity usage
                    sf::Text gravityText(defaultFont,
                        sf::String("Use Gravity: " + std::string(object->getUseGravity() ? "true" : "false")),
                        14);
                    gravityText.setFillColor(sf::Color::White);
                    gravityText.setPosition(sf::Vector2f(20.f, yOffset));
                    debugWindow.draw(gravityText);
                    yOffset += 20.f;

                    // Tracked developer-defined variables
                    const auto& trackedVars = object->getDebugTrackedValues();
                    for (const auto& [name, getter] : trackedVars) {
                        sf::Text trackedVarText(defaultFont, name + ": " + getter(), 14);
                        trackedVarText.setFillColor(sf::Color::White);
                        trackedVarText.setPosition(sf::Vector2f(20.f, yOffset));
                        debugWindow.draw(trackedVarText);
                        yOffset += 20.f;
                    }
                }

                yOffset += 10.f; // Vertical spacing between entries
            }

            debugWindow.display();
        }

        /**
         * @brief Closes the debug window if open.
         * Resets the visibility state and logs the closure.
         */
        void DebugWindow::close() {
            if (debugWindow.isOpen()) {
                debugWindow.close();
            }
            isVisible = false;
            KryptosEngine::DebugWindowLogger::GetLogger()->info("DebugWindow closed successfully");
        }

        /**
         * @brief Returns the state of the debug window.
         * @return True if the window is currently open, false otherwise.
         */
        bool DebugWindow::isOpen() const {
            return debugWindow.isOpen();
        }

    } // namespace DebugWindow
} // namespace KryptosEngine
