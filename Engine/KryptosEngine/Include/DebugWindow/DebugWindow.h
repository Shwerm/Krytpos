#pragma once
#ifndef DEBUGWINDOW_H
#define DEBUGWINDOW_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "../GameObjectSystem/GameObject.h"

class DebugWindow {
private:
    sf::RenderWindow debugWindow;             // Separate window for debugging
    bool isVisible;                           // Toggle visibility
    const std::vector<GameObject*>& objects;  // Reference to tracked game objects

public:
    // Constructor
    DebugWindow(const std::vector<GameObject*>& trackedObjects);

    // Toggle visibility
    void toggleVisibility();

    // Draw the debug window
    void draw();

    // Check if debug window is open
    bool isOpen() const;
};

#endif // DEBUGWINDOW_H

