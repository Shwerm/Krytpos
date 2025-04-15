/**
 * @file DebugWindow.h
 * @brief Header file for the DebugWindow class used in the Kryptos Debugging System.
 * @ingroup DebugSystem
 * @author
 * Sam Camilleri, Mural Studios
 * @date 2025
 */

#pragma once

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
         * @class DebugWindow
         * @ingroup DebugSystem
         * @brief Provides a graphical interface for debugging game objects in the engine.
         *
         * Displays transform data, physics values, and developer-defined debug variables in a scrollable overlay.
         * Can be toggled on/off via a designated key. Each GameObject entry can be expanded for additional details.
         */
        class DebugWindow {
        private:
            sf::RenderWindow debugWindow; ///< SFML window used for rendering the debug interface.
            bool isVisible;               ///< Whether the debug window is currently visible.
            sf::Keyboard::Key toggleKey;  ///< Keyboard key used to toggle the debug window.

            std::unordered_map<GameObject*, std::unique_ptr<sf::Text>> nameTexts; ///< Text objects for GameObject names.
            std::unordered_map<GameObject*, bool> expandedState; ///< Whether each object is expanded in the UI.
            sf::Font defaultFont; ///< Font used to render all debug text.

        public:
            /**
             * @brief Constructs a DebugWindow. Does not open or initialise the window yet.
             */
            DebugWindow();

            /**
             * @brief Loads the debug font and sets window parameters like framerate.
             * @throws std::runtime_error if required resources fail to load.
             */
            void initialise();

            /**
             * @brief Checks for toggle key press to show/hide the debug window.
             * Should be called every frame.
             */
            void handleInput();

            /**
             * @brief Opens or closes the debug window based on its current state.
             */
            void toggleVisibility();

            /**
             * @brief Closes the debug window if open and resets visibility state.
             */
            void close();

            /**
             * @brief Returns whether the debug window is currently open.
             * @return True if open, false if not.
             */
            bool isOpen() const;

            /**
             * @brief Renders all GameObjects and tracked variables in the debug window.
             * Should be called once per frame when the window is open.
             */
            void draw();
        };

    } // namespace DebugWindow
} // namespace KryptosEngine
