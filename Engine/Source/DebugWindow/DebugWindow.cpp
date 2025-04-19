/**
 * @file DebugWindow.cpp
 * @brief Implementation of the DebugWindow class for runtime graphical debugging.
 * 
 * @ingroup DebugSystem
 * 
 * Displays an overlay window with real-time GameObject information, including position,
 * physics, and registered debug variables. Controlled via toggle key input.
 * 
 * @author
 * Sam Camilleri, Mural Studios
 * @version 1.0
 * @date 2025
 */

#include "../../Include/DebugWindow/DebugWindow.h"

namespace KryptosEngine::DebugWindow
{
    // -----------------------------------------------------
    // Constructor
    // -----------------------------------------------------

    /**
     * @brief Constructs the DebugWindow instance and sets default toggle key to F1.
     */
    DebugWindow::DebugWindow()
        : debugWindow(),
          isVisible(false),
          toggleKey(sf::Keyboard::Key::F1)
    {
    }

    // -----------------------------------------------------
    // Initialisation
    // -----------------------------------------------------

    /**
     * @brief Loads font, sets framerate, and prepares the debug UI window.
     */
    void DebugWindow::initialise()
    {
        debugWindow.setFramerateLimit(60);

        if (!defaultFont.openFromFile("Assets/EngineAssets/Fonts/DebugWindowFont/AtkinsonHyperlegible-Regular.ttf"))
        {
            DebugWindowLogger::GetLogger()->error("Failed to load DebugWindow font");
        }
        else
        {
            DebugWindowLogger::GetLogger()->info("DebugWindow font loaded successfully");
        }

        DebugWindowLogger::GetLogger()->info("DebugWindow initialised successfully");
    }

    // -----------------------------------------------------
    // Input Handling
    // -----------------------------------------------------

    /**
     * @brief Checks for the toggle key and opens or closes the window accordingly.
     */
    void DebugWindow::handleInput()
    {
        if (sf::Keyboard::isKeyPressed(toggleKey) && !debugWindow.isOpen())
        {
            toggleVisibility();
        }
    }

    // -----------------------------------------------------
    // Visibility Management
    // -----------------------------------------------------

    /**
     * @brief Toggles the visibility of the debug window.
     */
    void DebugWindow::toggleVisibility()
    {
        isVisible = !isVisible;

        if (isVisible && !debugWindow.isOpen())
        {
            debugWindow.create(
                sf::VideoMode({ 400, 600 }),
                "Debug Window",
                sf::Style::Titlebar | sf::Style::Close
            );

            DebugWindowLogger::GetLogger()->info("DebugWindow opened successfully");
        }
        else if (!isVisible)
        {
            close();
        }
    }

    /**
     * @brief Closes the debug window and resets visibility state.
     */
    void DebugWindow::close()
    {
        if (debugWindow.isOpen())
        {
            debugWindow.close();
        }

        isVisible = false;
        DebugWindowLogger::GetLogger()->info("DebugWindow closed successfully");
    }

    /**
     * @brief Returns whether the debug window is currently open.
     * @return True if open and visible.
     */
    bool DebugWindow::isOpen() const
    {
        return debugWindow.isOpen();
    }

    // -----------------------------------------------------
    // Drawing and Rendering
    // -----------------------------------------------------

    /**
     * @brief Draws debug info for all active GameObjects to the debug window.
     */
    void DebugWindow::draw()
    {
        if (!isVisible || !debugWindow.isOpen()) return;

        bool mouseClicked = false;
        sf::Vector2f mousePosF;

        // Event polling
        while (const std::optional<sf::Event> event = debugWindow.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                close();
                return;
            }

            if (event->is<sf::Event::MouseButtonPressed>() &&
                event->getIf<sf::Event::MouseButtonPressed>()->button == sf::Mouse::Button::Left)
            {
                mouseClicked = true;
                sf::Vector2i mousePos = sf::Mouse::getPosition(debugWindow);
                mousePosF = sf::Vector2f(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
            }
        }

        debugWindow.clear(sf::Color::Black);
        float yOffset = 10.f;

        // Iterate through all active GameObjects
        for (const auto& object : GameObjectManager::getInstance().getGameObjects())
        {
            if (!object->isActive()) continue;

            // Display name
            sf::Text nameText(defaultFont, "Name: " + object->getName(), 14);
            nameText.setFillColor(sf::Color::White);
            nameText.setPosition({ 10.f, yOffset });
            debugWindow.draw(nameText);

            // Toggle expanded view on click
            if (mouseClicked && nameText.getGlobalBounds().contains(mousePosF))
            {
                expandedState[object] = !expandedState[object];
            }

            yOffset += 20.f;

            if (expandedState[object])
            {
                // Position
                sf::Text positionText(defaultFont,
                    "Position: (" + std::to_string(object->getPosition().x) + ", " +
                    std::to_string(object->getPosition().y) + ")", 14);
                positionText.setFillColor(sf::Color::White);
                positionText.setPosition({ 20.f, yOffset });
                debugWindow.draw(positionText);
                yOffset += 20.f;

                // Rotation
                sf::Text rotationText(defaultFont,
                    "Rotation: " + std::to_string(object->getRotation().asDegrees()) + " degrees", 14);
                rotationText.setFillColor(sf::Color::White);
                rotationText.setPosition({ 20.f, yOffset });
                debugWindow.draw(rotationText);
                yOffset += 20.f;

                // Mass
                sf::Text massText(defaultFont,
                    "Mass: " + std::to_string(object->getMass()), 14);
                massText.setFillColor(sf::Color::White);
                massText.setPosition({ 20.f, yOffset });
                debugWindow.draw(massText);
                yOffset += 20.f;

                // Gravity
                sf::Text gravityText(defaultFont,
                    "Use Gravity: " + std::string(object->getUseGravity() ? "true" : "false"), 14);
                gravityText.setFillColor(sf::Color::White);
                gravityText.setPosition({ 20.f, yOffset });
                debugWindow.draw(gravityText);
                yOffset += 20.f;

                // Tracked debug variables
                const auto& trackedVars = object->getDebugTrackedValues();
                for (const auto& [varName, getter] : trackedVars)
                {
                    sf::Text varText(defaultFont, varName + ": " + getter(), 14);
                    varText.setFillColor(sf::Color::White);
                    varText.setPosition({ 20.f, yOffset });
                    debugWindow.draw(varText);
                    yOffset += 20.f;
                }
            }

            yOffset += 10.f; // Spacing between objects
        }

        debugWindow.display();
    }

} // namespace KryptosEngine::DebugWindow
