/**
 * @file StaminaSystem.cpp
 * @brief Implements the stamina system for managing stamina use, regeneration, and UI ratio.
 *
 * @ingroup CombatSystem
 *
 * Used by the Player or other characters to control attack/sprint resources and cooldown logic.
 * Supports regeneration over time, usage checks, and stamina reset.
 *
 * Author:
 * Sam Camilleri, Mural Studios
 * @version 1.0
 * @date 2025
 */

#include "../../Include/PlayerClass/StaminaSystem.h"

 // -----------------------------------------------------
 // Constructor
 // -----------------------------------------------------

 /**
  * @brief Constructs a stamina system with a maximum capacity and regeneration rate.
  * @param maxStamina The full capacity of the stamina meter.
  * @param regenRatePerSecond Regeneration rate per second.
  */
StaminaSystem::StaminaSystem(float maxStamina, float regenRatePerSecond)
    : m_currentStamina(maxStamina),
    m_maxStamina(maxStamina),
    m_regenRate(regenRatePerSecond)
{
}

// -----------------------------------------------------
// Public Methods
// -----------------------------------------------------

/**
 * @brief Regenerates stamina over time based on the frame delta.
 * @param deltaTime Time since last frame (in seconds).
 */
void StaminaSystem::Update(float deltaTime)
{
    m_currentStamina += m_regenRate * deltaTime;

    if (m_currentStamina > m_maxStamina)
        m_currentStamina = m_maxStamina;
}

/**
 * @brief Attempts to consume a specific amount of stamina.
 * @param amount Amount to subtract from current stamina.
 * @return True if the stamina was available and deducted, false otherwise.
 */
bool StaminaSystem::UseStamina(float amount)
{
    if (m_currentStamina < amount)
        return false;

    m_currentStamina -= amount;
    return true;
}

/**
 * @brief Resets stamina to its maximum capacity.
 */
void StaminaSystem::Reset()
{
    m_currentStamina = m_maxStamina;
}

/**
 * @brief Returns the current stamina value.
 * @return A float representing the stamina available.
 */
float StaminaSystem::GetStamina() const
{
    return m_currentStamina;
}

/**
 * @brief Returns the maximum stamina capacity.
 * @return A float representing the stamina cap.
 */
float StaminaSystem::GetMaxStamina() const
{
    return m_maxStamina;
}

/**
 * @brief Returns the ratio of current stamina to max, useful for UI fill bars.
 * @return Float value between 0.0 and 1.0 representing stamina percentage.
 */
float StaminaSystem::GetStaminaRatio() const
{
    return (m_maxStamina == 0.f) ? 0.f : m_currentStamina / m_maxStamina;
}
