/**
 * @file EngineInit.cpp
 * @brief Initialises all core systems of the Kryptos Engine.
 *
 * @ingroup CoreSystem
 *
 * Central bootstrapper responsible for setting up the logging, debugging, and rendering logs.
 * Called at the beginning of engine execution to prepare runtime subsystems.
 *
 * Author:
 * Sam Camilleri, Mural Studios
 * @version 1.0
 * @date 2025
 */

#include "../../Include/Initialisers/EngineInit.h"

namespace KryptosEngine
{
    // -----------------------------------------------------
    // Static Initialisation Method
    // -----------------------------------------------------

    /**
     * @brief Performs full startup sequence for all engine systems.
     *
     * - Logging
     * - Debug Window logging
     * - Sprite Renderer logging
     *
     * Future systems can be added to this entry point.
     */
    void EngineInit::Initialise()
    {
        // -----------------------------------------------------
        // General Logger
        // -----------------------------------------------------
        Logger::Init();
        Logger::GetLogger()->info("General logging system initialised");

        // -----------------------------------------------------
        // Debug Window Logger
        // -----------------------------------------------------
        DebugWindowLogger::Init();
        DebugWindowLogger::GetLogger()->info("Debug Window logging initialised");

        // -----------------------------------------------------
        // Sprite Renderer Logger
        // -----------------------------------------------------
        SpriteRendererLogger::Init();
        SpriteRendererLogger::GetLogger()->info("Sprite Rendering logging initialised");

        // -----------------------------------------------------
        // Engine Ready
        // -----------------------------------------------------
        Logger::GetLogger()->info("Engine initialisation completed");
    }

} // namespace KryptosEngine
