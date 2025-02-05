/*
 * DebugWindow.h - Kryptos Debugging Interface
 * -------------------------------------------
 * Provides a graphical debugging overlay to visualize game objects and their state.
 * Designed for use within the Kryptos game and engine.
 *
 * Author: Sam Camilleri, Mural Studios
 * All Rights Reserved, 2025.
 *
 * Dependencies:
 *   - GameObjectManager.h: Manages game objects in the engine.
 */

#pragma once

#include "../GameObjectSystem/GameObjectManager.h"
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <memory>
#include "../Include/DebugWindow/DebugWindow.h"
#include "../Include/PlayerClass/Player.h"
#include "../Include/LoggingSystem/DebugWindow/DebugWindowLogger.h"
#include <SFML/Window/Event.hpp>
#include <stdexcept>
#include <iostream>

namespace KryptosEngine {
    namespace DebugWindow {
        /**
         * @class DebugWindow
         * @brief Provides a graphical interface for debugging game objects in the engine.
         *
         * This class allows visualization and interaction with game object data during runtime.
         * It supports toggling visibility, displaying object names, and expanding details per object.
         */
        class DebugWindow {
        private:
            sf::RenderWindow debugWindow; ///< Window for rendering debug information.
            bool isVisible;               ///< Tracks whether the debug window is currently visible.
            sf::Keyboard::Key toggleKey;  ///< Key used to toggle the visibility of the debug window.

            /**
             * Map of game objects to their corresponding name text elements.
             * Ownership of `sf::Text` is managed via unique pointers.
             */
            std::unordered_map<GameObject*, std::unique_ptr<sf::Text>> nameTexts;

            /**
             * Stores the expanded/collapsed state for each game object in the debug window.
             */
            std::unordered_map<GameObject*, bool> expandedState;

            sf::Font defaultFont; ///< Default font used for rendering text in the debug window.

        public:
            /**
             * @brief Constructs a DebugWindow object.
             * Does not initialize resources.
             */
            DebugWindow();

            /**
             * @brief Initializes the debug window.
             * Loads resources like the default font and sets up initial configurations.
             * @throw std::runtime_error if resources fail to load.
             */
            void init();

            /**
             * @brief Handles input for toggling the debug window.
             * Listens for the toggle key and switches visibility accordingly.
             */
            void handleInput();

            /**
             * @brief Toggles the visibility of the debug window.
             * If visible, the window is rendered; otherwise, it is hidden.
             */
            void toggleVisibility();

            /**
             * @brief Closes the debug window.
             * Releases any resources associated with the window.
             */
            void close();

            /**
             * @brief Checks if the debug window is open.
             * @return True if the debug window is open, false otherwise.
             */
            bool isOpen() const;

            /**
             * @brief Draws the debug window and its elements.
             * Renders game object information, expanded details, and UI elements.
             */
            void draw();
        };
    } // namespace DebugWindow
} // namespace KryptosEngine



