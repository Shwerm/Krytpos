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

 /**
  * @file DebugWindow.h
  * @brief Header file for the DebugWindow class used in the Kryptos Debugging System.
  * @ingroup DebugSystem
  * @author
  * Sam Camilleri, Mural Studios
  * @date 2025
  */

#pragma once

  /**
   * @defgroup DebugSystem Debugging System
   * @brief Contains classes and functionality related to runtime debugging.
   */

#include "../GameObjectSystem/GameObjectManager.h"
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <memory>
#include "../../Include/DebugWindow/DebugWindow.h"
#include "../../Include/PlayerClass/Player.h"
#include "../../Include/LoggingSystem/DebugWindow/DebugWindowLogger.h"
#include <SFML/Window/Event.hpp>
#include <stdexcept>
#include <iostream>

namespace KryptosEngine {
    namespace DebugWindow {

        /**
         * @ingroup DebugSystem
         * @class DebugWindow
         * @brief Provides a graphical interface for debugging game objects in the engine.
         * @details The DebugWindow displays real-time information such as transform and physics values,
         * along with developer-defined variables. This tool is essential for debugging during development.
         */
        class DebugWindow {
        private:
            sf::RenderWindow debugWindow; /**< SFML window used to render the debug overlay. */
            bool isVisible;               /**< Boolean flag to track window visibility status. */
            sf::Keyboard::Key toggleKey;  /**< Keybind for toggling the debug window visibility. */

            /**
             * @brief Stores game object name labels.
             * Maps each GameObject pointer to a unique pointer managing its sf::Text object.
             */
            std::unordered_map<GameObject*, std::unique_ptr<sf::Text>> nameTexts;

            /**
             * @brief Tracks whether each game object in the debug window is expanded or collapsed.
             * This determines whether additional debug details are drawn.
             */
            std::unordered_map<GameObject*, bool> expandedState;

            sf::Font defaultFont; /**< Font used for rendering debug UI text. */

        public:
            /**
             * @brief Default constructor.
             * Initializes the internal state but does not load resources.
             */
            DebugWindow();

            /**
             * @brief Initializes the debug window.
             * Loads required assets like fonts and sets up the window state.
             * @throw std::runtime_error if fonts or other resources fail to load.
             */
            void initialise();

            /**
             * @brief Checks for keyboard input to toggle visibility.
             * Should be called once per frame in the engine's main loop.
             */
            void handleInput();

            /**
             * @brief Toggles debug window visibility.
             * Opens or closes the debug overlay depending on its current state.
             */
            void toggleVisibility();

            /**
             * @brief Closes the debug window.
             * Cleans up any open resources and resets the visibility flag.
             */
            void close();

            /**
             * @brief Checks if the debug window is currently open.
             * @return True if open, false if closed.
             */
            bool isOpen() const;

            /**
             * @brief Renders the debug interface.
             * Iterates through active game objects and displays relevant data.
             * Also handles interaction with expandable details via mouse click.
             */
            void draw();
        };
    } // namespace DebugWindow
} // namespace KryptosEngine
