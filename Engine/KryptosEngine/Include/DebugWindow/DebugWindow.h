/*
Debug Window header - Kryptos - Sam Camilleri, Mural Studios
All Rights Reserved 2025.
Dependencies: Graphics.hpp, vector, string, GameObject.h
*/
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "../GameObjectSystem/GameObject.h"
#include <unordered_map>
#include "../GameObjectSystem/GameObjectManager.h"

class DebugWindow {
private:
    sf::RenderWindow debugWindow;          // Separate window for debugging
    bool isVisible;                        // Toggle visibility
    std::unordered_map<GameObject*, bool> expandedState; // Dropdown state for each object

public:
    DebugWindow();

    void toggleVisibility();
    void draw();
    bool isOpen() const;
};


