#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include "PlayerClass/Player.h"
#include "DebugWindow/DebugWindow.h"

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Player, Game Object & Sprite Renderer Test");

    // Path to the player texture
    std::string playerTexturePath = "D:\\Personal Projects\\Working Title - Kryptos\\Art\\KryptosPlayerSprite\\KrillConcept03.png";

    // Declare Player
    Player player("Kryptos", sf::Vector2(100.f, 300.f), playerTexturePath);

    // Add Player to tracked game objects
    std::vector<GameObject*> trackedObjects = { &player };

    // Create the Debug Window
    DebugWindow debugWindow(trackedObjects);

    sf::Clock clock;

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        while (const std::optional event = window.pollEvent())
        {
            // Close window: exit
            if (event->is<sf::Event::Closed>())
                window.close();

            // Toggle debug window visibility with F1 key
            if (event->is<sf::Event::KeyPressed>() && event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::F1) {
                debugWindow.toggleVisibility();
            }
        }

        // Calculate delta time
        float deltaTime = clock.restart().asSeconds();

        // Update Player
        player.update(deltaTime);

        // Clear screen
        window.clear();

        // Render Player
        player.draw(window);

        // Render Debug Window
        debugWindow.draw();

        // Update the window
        window.display();
    }

    return 0;
}
