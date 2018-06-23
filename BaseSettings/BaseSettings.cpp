#include "BaseSettings.h"

ReadVectorMethod BaseSettings::GetReadMethod() const
{
	return m_readMethod;
}

size_t BaseSettings::GetReadLimit() const
{
	return m_readLimit;
}

BaseSettingsBuilder & BaseSettingsBuilder::SetReadMethod(ReadVectorMethod readMethod)
{
	m_baseSettings.m_readMethod = readMethod;
	return *this;
}

BaseSettingsBuilder & BaseSettingsBuilder::SetReadLimit(size_t readLimit)
{
	m_baseSettings.m_readLimit = readLimit;
	return *this;
}

BaseSettings BaseSettingsBuilder::Build() const
{
	return m_baseSettings;
}
