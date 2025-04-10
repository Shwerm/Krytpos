#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <KryptosEngine.hpp>

#include <iostream>
#include <memory>

int main() {
    try {
        // Initialize the engine
        KryptosEngine::EngineInit::Initialise();

        // Log a message indicating the game has started
        KryptosEngine::Logger::GetLogger()->info("Game started successfully");
    }
    catch (const std::exception& e) {
        std::cerr << "An exception occurred during engine initialization: " << e.what() << std::endl;
        return -1;
    }

#include <filesystem>
    try {
        std::cout << "Working directory: " << std::filesystem::current_path() << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Failed to get working directory: " << e.what() << "\n";
    }

    // Create the main window
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Player, Game Object & Sprite Renderer Test");

    // Path to the player texture
    std::string playerTexturePath = "D:\\Personal Projects\\Working Title - Kryptos\\Art\\KryptosPlayerSprite\\KrillConcept03.png";

    // Declare Players
    Player player("Kryptos", sf::Vector2(100.f, 300.f), playerTexturePath);

    // Create the Debug Window
    KryptosEngine::DebugWindow::DebugWindow debugWindow;
    debugWindow.initialise();

    // Define environment generation settings
    TerrainGenerationSettings genSettings;
    genSettings.totalPlatforms = 15;
    genSettings.minPlatformWidth = 1.5f;
    genSettings.maxPlatformWidth = 3.5f;
    genSettings.heightVariance = 1.0f;
    genSettings.sameXOffsetYRange = 1.25f;
    genSettings.minY = 150.0f;
    genSettings.maxY = 450.0f;
    genSettings.verticalStackChance = 0.3f;

    // Add texture paths (make sure these paths are valid for your project)
    genSettings.texturePaths = {
        "GameAssets/Environment/Platforms/platform1.png"
    };

	genSettings.finishPointTexturePath = "GameAssets/Environment/Platforms/banner.png";

    // Create and generate environment
    sf::Vector2f startPosition(50.0f, 300.0f);
    EnvironmentGenerator generator(genSettings, startPosition);
    generator.generate();

    sf::Clock clock;

    // Start the game loop
    while (window.isOpen()) {
        // Process events
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
                debugWindow.close();
            }
        }

        // Calculate delta time
        float deltaTime = clock.restart().asSeconds();

        // Update players
        player.update(deltaTime);

        // Handle debug window input
        debugWindow.handleInput();

        // Clear screen
        window.clear();

        // Draw platforms
        for (auto* obj : GameObjectManager::getInstance().getGameObjects()) {
            if (auto* platform = dynamic_cast<Platform*>(obj)) {
                platform->draw(window);
            }
        }

        // Draw player
        player.draw(window);

        // Draw debug window
        if (debugWindow.isOpen()) {
            debugWindow.draw();
        }

        // Display rendered frame
        window.display();
    }

    return 0;
}
