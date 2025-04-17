// StaminaSystem.hpp
#pragma once

/**
 * @brief Handles stamina consumption and regeneration for a game character.
 * Designed to be used by player or AI characters in gameplay.
 */
class StaminaSystem
{
public:
    /**
     * @brief Constructs a StaminaSystem with specified max stamina and regen rate.
     * @param maxStamina The maximum stamina value.
     * @param regenRatePerSecond The regeneration rate in stamina units per second.
     */
    StaminaSystem(float maxStamina, float regenRatePerSecond);

    /**
     * @brief Updates the stamina system. Regenerates stamina based on delta time.
     * @param deltaTime Time passed since last frame (in seconds).
     */
    void Update(float deltaTime);

    /**
     * @brief Attempts to consume a specified amount of stamina.
     * @param amount Amount of stamina to use.
     * @return True if successful, false if not enough stamina.
     */
    bool UseStamina(float amount);

    /**
     * @brief Resets the stamina to the maximum value.
     */
    void Reset();

    /**
     * @brief Gets the current stamina value.
     * @return Current stamina.
     */
    float GetStamina() const;

    /**
     * @brief Gets the maximum stamina value.
     * @return Maximum stamina.
     */
    float GetMaxStamina() const;

    /**
     * @brief Gets a 0.0 to 1.0 ratio of current to max stamina.
     * Useful for UI representation.
     * @return Ratio of current stamina.
     */
    float GetStaminaRatio() const;

private:
    float m_currentStamina;
    float m_maxStamina;
    float m_regenRate;
};
