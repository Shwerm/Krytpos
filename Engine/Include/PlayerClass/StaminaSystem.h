/**
 * @file StaminaSystem.h
 * @brief Manages stamina consumption and regeneration for characters.
 *
 * @ingroup CombatSystem
 *
 * @author
 * Sam Camilleri, Mural Studios
 * @version 1.0
 * @date 2025
 */

#pragma once

 /**
  * @class StaminaSystem
  * @brief Handles stamina usage, regeneration, and querying for gameplay mechanics.
  *
  * Used by Player and AI characters to limit actions like attacking or sprinting.
  */
class StaminaSystem
{
public:
    // -----------------------------------------------------
    // Constructors
    // -----------------------------------------------------

    /**
     * @brief Constructs a stamina system with a given maximum and regeneration rate.
     * @param maxStamina Maximum stamina.
     * @param regenRatePerSecond Stamina regenerated per second.
     */
    StaminaSystem(float maxStamina, float regenRatePerSecond);

    // -----------------------------------------------------
    // Public Methods
    // -----------------------------------------------------

    /**
     * @brief Updates stamina over time.
     * @param deltaTime Elapsed time in seconds.
     */
    void Update(float deltaTime);

    /**
     * @brief Attempts to consume a set amount of stamina.
     * @param amount Amount to consume.
     * @return True if successful, false if not enough stamina.
     */
    bool UseStamina(float amount);

    /**
     * @brief Fully restores stamina to max.
     */
    void Reset();

    // -----------------------------------------------------
    // Getters
    // -----------------------------------------------------

    float GetStamina() const;
    float GetMaxStamina() const;
    float GetStaminaRatio() const;

private:
    // -----------------------------------------------------
    // Private Members
    // -----------------------------------------------------

    float m_currentStamina; ///< Current stamina value.
    float m_maxStamina;     ///< Maximum stamina value.
    float m_regenRate;      ///< Regeneration rate per second.
};
