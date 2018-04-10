#include "MatrixSettings.h"

BaseSettings const & MatrixSettings::GetBaseSettings() const
{
	return m_baseSettings;
}

MatrixSettings const & MatrixSettingsBuilder::Build(BaseSettings const & baseSettings)
{
	m_matrixSettings.m_baseSettings = baseSettings;
	return m_matrixSettings;
}
