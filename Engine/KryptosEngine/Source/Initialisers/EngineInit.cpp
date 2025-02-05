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
    void EngineInit::Initialise() {
        // Initialize general logging system
        Logger::Init();
        Logger::GetLogger()->info("General logging system initialized");

        // Initialize Debug Window logging
        DebugWindowLogger::Init();
        DebugWindowLogger::GetLogger()->info("Debug Window logging initialized");

        // Future systems can be initialized here
        Logger::GetLogger()->info("Engine initialization completed");
    }

} // namespace KryptosEngine
