/**
 * @file KryptosEngine.hpp
 * @brief Primary include header for all core modules in the Kryptos Engine.
 *
 * @ingroup CoreSystem
 *
 * @details
 * This header is intended to be the single point of inclusion for applications or games
 * using the Kryptos Engine. It aggregates all core systems, subsystems, and utilities.
 *
 * @author
 * Sam Camilleri, Mural Studios
 * @version 1.0
 * @date 2025
 */

#pragma once

 // Core Engine Subsystems
#include "DebugWindow/debugWindow.hpp"
#include "EnvironmentGenerator/enviro.hpp"
#include "GameObjectSystem/gameObject.hpp"
#include "Initialisers/init.hpp"
#include "LoggingSystem/logger.hpp"
#include "PlayerClass/player.hpp"
#include "SpriteRenderingSystem/spriteRenderer.hpp"
#include "CameraSystem/PlayerCamera.hpp"

// UI
#include "UI/HealthBar.h"
#include "UI/StaminaBar.h"
