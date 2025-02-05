/*
 * EngineInit.h - Kryptos Engine Initialization
 * --------------------------------------------
 * Provides a centralized interface for initializing core engine systems,
 * including logging and debugging features.
 *
 * Author: Sam Camilleri, Mural Studios
 * All Rights Reserved, 2025.
 *
 * Dependencies:
 *   - Logger.h: Core logging system initialization.
 *   - DebugWindowLogger.h: Debug window logging system initialization.
 */

#pragma once
#include "../Include/LoggingSystem/Logger.h"
#include "../Include/LoggingSystem/DebugWindow/DebugWindowLogger.h"
#include "../Include/DebugWindow/DebugWindow.h"

namespace KryptosEngine {

    /**
     * @class EngineInit
     * @brief Manages the initialization of the Kryptos engine's core systems.
     *
     * The EngineInit class provides a static method to initialize all essential
     * systems required for the engine's functionality, such as logging and debugging.
     */
    class EngineInit {
    public:
        /**
         * @brief Initializes all engine systems.
         *
         * Sets up logging, debugging, and other core systems to prepare the engine for use.
         */
        static void Init();
    };

} // namespace KryptosEngine
