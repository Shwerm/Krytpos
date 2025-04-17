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

    sf::RenderWindow window(sf::VideoMode({ 1088, 640 }), "Player, Game Object & Sprite Renderer Test");

    // Create parallax background
    ParallaxBackground parallaxBackground(static_cast<float>(window.getSize().x));

    // Set up camera controller
    CameraController camera(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y));

    std::string playerTexturePath = "Assets/GameAssets/Textures/Player/KrillConcept03.png";

    // Create player first
    sf::Vector2f playerStart(100.f, 300.f);
    Player player("Kryptos", playerStart, playerTexturePath);

    // Create and register health bar UI
    auto* healthBar = new HealthBarObject(&player, sf::Vector2f(window.getSize()));
    GameObjectManager::getInstance().registerObject(healthBar);

    // Create and register stamina bar UI
    auto* staminaBar = new StaminaBarObject(&player, sf::Vector2f(window.getSize()));
    GameObjectManager::getInstance().registerObject(staminaBar);

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
        "Assets/GameAssets/Textures/Environment/Platforms/platform1.png"
    };
    genSettings.finishPointTexturePath = "Assets/GameAssets/Textures/Environment/Platforms/banner.png";

    // Generate the environment using the player's actual X/Y base
    float playerBaseY = player.getPosition().y + 48.f; // Collider height
    sf::Vector2f platformStart(player.getPosition().x, playerBaseY);

    EnvironmentGenerator generator(genSettings, platformStart);
    generator.generate(&player);

    KryptosEngine::DebugWindow::DebugWindow debugWindow;
    debugWindow.initialise();

    const float fixedDeltaTime = 1.f / 60.f; // 60 Hz physics
    float accumulator = 0.f;

    sf::Clock clock;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
                debugWindow.close();
            }
        }

        float frameTime = clock.restart().asSeconds();
        accumulator += std::min(frameTime, 0.1f); // prevent massive spikes on window focus

        // Fixed timestep physics
        while (accumulator >= fixedDeltaTime) {
            GameObjectManager::getInstance().fixedUpdateAll(fixedDeltaTime);
            accumulator -= fixedDeltaTime;
        }

        // Visual/input updates
        for (GameObject* obj : GameObjectManager::getInstance().getGameObjects()) {
            obj->update(frameTime);
        }

        camera.Update(player.getPosition());

        window.clear();

        // ---------- Apply camera ----------
        camera.ApplyView(window);

        // ---------- Update and Draw Parallax Background ----------
        parallaxBackground.update(player.getPosition().x, camera.GetView());
        parallaxBackground.draw(window);

        // ---------- Draw World Space Objects ----------
        for (auto* obj : GameObjectManager::getInstance().getGameObjects()) {
            if (obj->getName() != "HealthBar" && obj->getName() != "StaminaBar") {
                obj->draw(window);
            }
        }

        player.draw(window);

        // ---------- Draw UI (screen-space) ----------
        window.setView(window.getDefaultView());

        for (auto* obj : GameObjectManager::getInstance().getGameObjects()) {
            if (obj->getName() == "HealthBar" || obj->getName() == "StaminaBar") {
                obj->draw(window);
            }
        }

        if (debugWindow.isOpen()) {
            debugWindow.draw();
        }

        window.display();
    }

    return 0;
}
