/**
 * @file EngineInit.h
 * @brief Entry point for initializing all core systems in the Kryptos Engine.
 *
 * @ingroup EngineCoreSystem
 *
 * @author
 * Sam Camilleri, Mural Studios
 * @version 1.0
 * @date 2025
 */

#pragma once

#include "../../Include/LoggingSystem/Logger.h"
#include "../../Include/LoggingSystem/DebugWindow/DebugWindowLogger.h"
#include "../../Include/LoggingSystem/SpriteRenderer/SpriteRendererLogger.h"

namespace KryptosEngine
{
    /**
     * @class EngineInit
     * @brief Static utility for initializing core engine systems such as logging and debugging.
     *
     * Meant to be called during the engine's bootstrapping sequence.
     */
    class EngineInit
    {
    public:
        // -----------------------------------------------------
        // Public Static Methods
        // -----------------------------------------------------

        /**
         * @brief Initialises all critical engine services.
         *
         * Registers the logging system, sprite renderer logging, and debug window logging.
         */
        static void Initialise();
    };
}
