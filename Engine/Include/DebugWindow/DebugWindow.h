/**
 * @file DebugWindow.h
 * @brief Debug overlay window for visualising GameObject data at runtime.
 *
 * @ingroup DebugSystem
 * @author
 * Sam Camilleri, Mural Studios
 * @version 1.0
 * @date 2025
 */

#pragma once

#include "../GameObjectSystem/GameObjectManager.h"
#include "../../Include/PlayerClass/Player.h"
#include "../../Include/LoggingSystem/DebugWindow/DebugWindowLogger.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <unordered_map>
#include <memory>
#include <stdexcept>
#include <iostream>

namespace KryptosEngine::DebugWindow
{
    /**
     * @class DebugWindow
     * @brief Provides a graphical interface for debugging active GameObjects.
     *
     * Displays live transform and physics data in a toggleable UI overlay. Each object has an expandable entry.
     */
    class DebugWindow
    {
    public:
        // -----------------------------------------------------
        // Constructors / Destructor
        // -----------------------------------------------------

        /**
         * @brief Constructs the debug window controller. Window is not open or initialised on construction.
         */
        DebugWindow();

        // -----------------------------------------------------
        // Public Methods
        // -----------------------------------------------------

        /**
         * @brief Loads necessary font assets and configures the debug window.
         * @throws std::runtime_error if fonts or system resources fail to load.
         */
        void initialise();

        /**
         * @brief Handles key input for toggling window visibility.
         * Should be called every frame.
         */
        void handleInput();

        /**
         * @brief Toggles the debug window's visibility.
         */
        void toggleVisibility();

        /**
         * @brief Forces the debug window to close and resets visibility state.
         */
        void close();

        /**
         * @brief Returns whether the debug window is currently visible.
         * @return True if the window is open and drawing.
         */
        bool isOpen() const;

        /**
         * @brief Draws the debug UI for all active GameObjects.
         * Should be called once per frame if visible.
         */
        void draw();

    private:
        // -----------------------------------------------------
        // Private Members
        // -----------------------------------------------------

        sf::RenderWindow debugWindow; ///< SFML render window for debug drawing.
        bool isVisible;               ///< Whether the debug window is currently visible.
        sf::Keyboard::Key toggleKey;  ///< Key used to toggle the window on/off.

        sf::Font defaultFont; ///< Default font for rendering debug text.

        std::unordered_map<GameObject*, std::unique_ptr<sf::Text>> nameTexts; ///< Map of GameObject names to renderable text.
        std::unordered_map<GameObject*, bool> expandedState; ///< Tracks whether a GameObject entry is expanded in the debug UI.
    };
}
