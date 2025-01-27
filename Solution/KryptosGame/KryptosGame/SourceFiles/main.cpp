#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include "LoggingSystem/Logger.h"
#include "PlayerClass/Player.h"
#include "DebugWindow/DebugWindow.h"
#include <iostream>

int main() {
    // Initialize the engine logger
    KryptosEngine::Logger::Init();
    //spdlog::info("Game started");

    // Create the main window
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Player, Game Object & Sprite Renderer Test");

    // Path to the player texture
    std::string playerTexturePath = "D:\\Personal Projects\\Working Title - Kryptos\\Art\\KryptosPlayerSprite\\KrillConcept03.png";

    // Declare Player
    Player player("Kryptos", sf::Vector2(100.f, 300.f), playerTexturePath);
    Player anotherPlayer("Athena", sf::Vector2(200.f, 400.f), playerTexturePath); // Example additional player

    // Create the Debug Window
    DebugWindow debugWindow;

    sf::Clock clock;

    // Start the game loop
    while (window.isOpen()) {
        // Process events
        while (const std::optional event = window.pollEvent()) {
            // Close window: exit
            if (event->is<sf::Event::Closed>()) {
                window.close();
                debugWindow.close(); // Close the debug window as well
            }
        }

        // Calculate delta time
        float deltaTime = clock.restart().asSeconds();

        // Update Players
        player.update(deltaTime);
        anotherPlayer.update(deltaTime);

        // Clear screen
        window.clear();

        // Render Players
        player.draw(window);
        anotherPlayer.draw(window);

        debugWindow.handleInput();

        // Render Debug Window
        if (debugWindow.isOpen()) {
            debugWindow.draw();
        }

        // Update the main window
        window.display();
    }

    return 0;
}
