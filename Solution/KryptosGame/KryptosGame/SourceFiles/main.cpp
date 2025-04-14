#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <KryptosEngine.hpp>

#include <iostream>
#include <memory>
#include <filesystem>

int main() {
    try {
        KryptosEngine::EngineInit::Initialise();
        KryptosEngine::Logger::GetLogger()->info("Game started successfully");
    }
    catch (const std::exception& e) {
        std::cerr << "Engine init error: " << e.what() << std::endl;
        return -1;
    }

    try {
        std::cout << "Working directory: " << std::filesystem::current_path() << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Get working dir error: " << e.what() << "\n";
    }

    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Player, Game Object & Sprite Renderer Test");

    // Set up camera controller
    CameraController camera(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y));

    std::string playerTexturePath = "D:\\Personal Projects\\Working Title - Kryptos\\Art\\KryptosPlayerSprite\\KrillConcept03.png";

    // Create player first
    sf::Vector2f playerStart(100.f, 300.f);
    Player player("Kryptos", playerStart, playerTexturePath);

    // Set up environment generation settings
    TerrainGenerationSettings genSettings;
    genSettings.totalPlatforms = 15;
    genSettings.minPlatformWidth = 1.5f;
    genSettings.maxPlatformWidth = 3.5f;
    genSettings.heightVariance = 1.0f;
    genSettings.sameXOffsetYRange = 1.25f;
    genSettings.minY = 150.0f;
    genSettings.maxY = 450.0f;
    genSettings.verticalStackChance = 0.3f;
    genSettings.texturePaths = {
        "GameAssets/Environment/Platforms/platform1.png"
    };
    genSettings.finishPointTexturePath = "GameAssets/Environment/Platforms/banner.png";

    // Generate the environment using the player's actual X/Y base
    float playerBaseY = player.getPosition().y + 48.f; // Collider height
    sf::Vector2f platformStart(player.getPosition().x, playerBaseY);

    EnvironmentGenerator generator(genSettings, platformStart);
    generator.generate();

    KryptosEngine::DebugWindow::DebugWindow debugWindow;
    debugWindow.initialise();

    sf::Clock clock;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
                debugWindow.close();
            }
        }

        float deltaTime = clock.restart().asSeconds();

        for (GameObject* obj : GameObjectManager::getInstance().getGameObjects()) {
            obj->update(deltaTime);
        }

        // Update camera based on player's current position
        camera.Update(player.getPosition());

        debugWindow.handleInput();

        // Apply camera view to window
        camera.ApplyView(window);

        window.clear();

        for (auto* obj : GameObjectManager::getInstance().getGameObjects()) {
            if (auto* platform = dynamic_cast<Platform*>(obj)) {
                platform->draw(window);
            }
        }

        player.draw(window);

        if (debugWindow.isOpen()) {
            debugWindow.draw();
        }

        window.display();
    }

    return 0;
}
