/**
 * @file main.cpp
 * @brief Entry point for launching the Kryptos Engine demo project.
 *
 * @ingroup CoreSystem
 *
 * Handles:
 * - Engine initialisation
 * - Window creation
 * - Player/environment setup
 * - Game loop with fixed physics updates
 *
 * Author:
 * Sam Camilleri, Mural Studios
 * @version 1.0
 * @date 2025
 */

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <KryptosEngine.hpp>

#include <iostream>
#include <memory>
#include <filesystem>

int main()
{
    // -----------------------------------------------------
    // Initialise Engine Systems
    // -----------------------------------------------------
    try {
        KryptosEngine::EngineInit::Initialise();
        KryptosEngine::Logger::GetLogger()->info("Game started successfully");
    }
    catch (const std::exception& e) {
        std::cerr << "Engine init error: " << e.what() << std::endl;
        return -1;
    }

    // -----------------------------------------------------
    // Debug Info: Print working directory
    // -----------------------------------------------------
    try {
        std::cout << "Working directory: " << std::filesystem::current_path() << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Get working dir error: " << e.what() << "\n";
    }

    // -----------------------------------------------------
    // Create Main Window
    // -----------------------------------------------------
    sf::RenderWindow window(sf::VideoMode({ 1088, 640 }), "Player, Game Object & Sprite Renderer Test");

    // -----------------------------------------------------
    // Create Parallax Background
    // -----------------------------------------------------
    ParallaxBackground parallaxBackground(static_cast<float>(window.getSize().x));

    // -----------------------------------------------------
    // Camera Setup
    // -----------------------------------------------------
    CameraController camera(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y));

    // -----------------------------------------------------
    // Create Player
    // -----------------------------------------------------
    std::string playerTexturePath = "Assets/GameAssets/Textures/Player/KrillConcept03.png";
    sf::Vector2f playerStart(100.f, 300.f);
    Player player("Kryptos", playerStart, playerTexturePath);

    // -----------------------------------------------------
    // Register UI (Health & Stamina Bars)
    // -----------------------------------------------------
    auto* healthBar = new HealthBarObject(&player, sf::Vector2f(window.getSize()));
    GameObjectManager::getInstance().registerObject(healthBar);

    auto* staminaBar = new StaminaBarObject(&player, sf::Vector2f(window.getSize()));
    GameObjectManager::getInstance().registerObject(staminaBar);

    // -----------------------------------------------------
    // Environment Generation
    // -----------------------------------------------------
    TerrainGenerationSettings genSettings;
    genSettings.totalPlatforms = 15;
    genSettings.minPlatformWidth = 1.5f;
    genSettings.maxPlatformWidth = 3.5f;
    genSettings.heightVariance = 10.0f;
    genSettings.sameXOffsetYRange = 1.25f;
    genSettings.minY = 150.0f;
    genSettings.maxY = 450.0f;
    genSettings.verticalStackChance = 1.0f;
    genSettings.texturePaths = {
        "Assets/GameAssets/Textures/Environment/Platforms/platform1.png"
    };
    genSettings.finishPointTexturePath = "Assets/GameAssets/Textures/Environment/Platforms/banner.png";

    float playerBaseY = player.getPosition().y + 48.f;
    sf::Vector2f platformStart(player.getPosition().x, playerBaseY);

    EnvironmentGenerator generator(genSettings, platformStart);
    generator.generate(&player);

    // -----------------------------------------------------
    // Debug Window
    // -----------------------------------------------------
    KryptosEngine::DebugWindow::DebugWindow debugWindow;
    debugWindow.initialise();

    // -----------------------------------------------------
    // Fixed Timestep Setup
    // -----------------------------------------------------
    const float fixedDeltaTime = 1.f / 60.f;
    float accumulator = 0.f;
    sf::Clock clock;

    // -----------------------------------------------------
    // Main Game Loop
    // -----------------------------------------------------
    while (window.isOpen())
    {
        // ------------------------------------------
        // Handle Events
        // ------------------------------------------
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
                debugWindow.close();
            }
        }

        float frameTime = clock.restart().asSeconds();
        accumulator += std::min(frameTime, 0.1f); // Cap delta to prevent frame spikes

        // ------------------------------------------
        // Physics Step (Fixed Timestep)
        // ------------------------------------------
        while (accumulator >= fixedDeltaTime)
        {
            GameObjectManager::getInstance().fixedUpdateAll(fixedDeltaTime);
            accumulator -= fixedDeltaTime;
        }

        // ------------------------------------------
        // Logic Update
        // ------------------------------------------
        for (GameObject* obj : GameObjectManager::getInstance().getGameObjects())
        {
            obj->update(frameTime);
        }

        camera.Update(player.getPosition());

        window.clear();

        // ------------------------------------------
        // Apply Camera View
        // ------------------------------------------
        camera.ApplyView(window);

        // ------------------------------------------
        // Background
        // ------------------------------------------
        parallaxBackground.update(player.getPosition().x, camera.GetView());
        parallaxBackground.draw(window);

        // ------------------------------------------
        // World Space Rendering
        // ------------------------------------------
        for (auto* obj : GameObjectManager::getInstance().getGameObjects())
        {
            if (obj->getName() != "HealthBar" && obj->getName() != "StaminaBar")
            {
                obj->draw(window);
            }
        }

        player.draw(window);

        // ------------------------------------------
        // UI Space Rendering (No Camera)
        // ------------------------------------------
        window.setView(window.getDefaultView());

        for (auto* obj : GameObjectManager::getInstance().getGameObjects())
        {
            if (obj->getName() == "HealthBar" || obj->getName() == "StaminaBar")
            {
                obj->draw(window);
            }
        }

        // ------------------------------------------
        // Draw Debug Overlay (if open)
        // ------------------------------------------
        if (debugWindow.isOpen())
        {
            debugWindow.draw();
        }

        window.display();
    }

    return 0;
}
