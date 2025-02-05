/*
 * EngineInit.cpp - Kryptos Engine Initialization Implementation
 * -------------------------------------------------------------
 * Implements the EngineInit class for initializing the Kryptos engine's core systems.
 *
 * Author: Sam Camilleri, Mural Studios
 * All Rights Reserved, 2025.
 *
 * Dependencies:
 *   - EngineInit.h: Header for the EngineInit class.
 */

#include "../Include/Initialisers/EngineInit.h"

namespace KryptosEngine {

    /**
     * @brief Initializes all engine systems.
     *
     * Sets up the general logging system and the debug window logging system.
     * Additional systems can be initialized in this method as required.
     */
    void EngineInit::Init() {
        // Initialise general logging system
        Logger::Init();
        Logger::GetLogger()->info("General logging system initialised");

        // Initialise Debug Window logging
        DebugWindowLogger::Init();
        DebugWindowLogger::GetLogger()->info("Debug Window logging initialised");

        // Initialise Debug Window
		DebugWindow::DebugWindow debugWindow;
        debugWindow.init();

        // Future systems can be initialised here
        Logger::GetLogger()->info("Engine initialisation completed");
    }

} // namespace KryptosEngine
