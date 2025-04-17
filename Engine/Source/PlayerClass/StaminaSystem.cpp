// StaminaSystem.cpp
#include "../../Include/PlayerClass/StaminaSystem.h"

StaminaSystem::StaminaSystem(float maxStamina, float regenRatePerSecond)
    : m_currentStamina(maxStamina),
    m_maxStamina(maxStamina),
    m_regenRate(regenRatePerSecond)
{
}

void StaminaSystem::Update(float deltaTime)
{
    m_currentStamina += m_regenRate * deltaTime;
    if (m_currentStamina > m_maxStamina)
        m_currentStamina = m_maxStamina;
}

bool StaminaSystem::UseStamina(float amount)
{
    if (m_currentStamina < amount)
        return false;

    m_currentStamina -= amount;
    return true;
}

void StaminaSystem::Reset()
{
    m_currentStamina = m_maxStamina;
}

float StaminaSystem::GetStamina() const
{
    return m_currentStamina;
}

float StaminaSystem::GetMaxStamina() const
{
    return m_maxStamina;
}

float StaminaSystem::GetStaminaRatio() const
{
    return (m_maxStamina == 0.f) ? 0.f : m_currentStamina / m_maxStamina;
}
