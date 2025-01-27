#include "../Include/Initialisers/EngineInit.h"

namespace KryptosEngine {

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
