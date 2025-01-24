/*
Debug Window header - Kryptos - Sam Camilleri, Mural Studios
All Rights Reserved 2025.
Dependencies: Graphics.hpp, vector, string, GameObject.h
*/
#pragma once
#include <SFML/Graphics.hpp>  // For sf::Text, sf::Font, sf::RenderWindow, sf::String
#include <SFML/Window/Keyboard.hpp>  // For sf::Keyboard
#include <unordered_map>  // For std::unordered_map
#include <memory>  // For std::unique_ptr
#include "../GameObjectSystem/GameObject.h"  // For GameObject class
#include "../GameObjectSystem/GameObjectManager.h"  // For GameObjectManager

class DebugWindow {
private:
    sf::RenderWindow debugWindow;          // Separate window for debugging
    bool isVisible;                        // Toggle visibility
	sf::Keyboard::Key toggleKey;		   // Key to toggle visibility
    std::unordered_map<GameObject*, std::unique_ptr<sf::Text>> nameTexts; // Map of game objects to their text
    std::unordered_map<GameObject*, bool> expandedState; // Dropdown state for each object
    sf::Font defaultFont; // Font for all texts


public:
    DebugWindow();

	void handleInput();
    void toggleVisibility();
    void draw();
	void close();
    bool isOpen() const;
};


