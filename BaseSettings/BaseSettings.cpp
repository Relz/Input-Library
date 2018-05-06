#include "BaseSettings.h"

BaseSettings & BaseSettings::operator=(BaseSettings const & right) noexcept
{
	if (this == &right)
	{
		return *this;
	}
	m_skipCharacters = right.m_skipCharacters;
	m_stopCharacters = right.m_stopCharacters;
	m_readMethod = right.m_readMethod;
	m_readLimit = right.m_readLimit;
	m_readEndOfLine = right.m_readEndOfLine;
	return *this;
}

BaseSettings & BaseSettings::operator=(BaseSettings && right) noexcept
{
	if (this == &right)
	{
		return *this;
	}
	m_skipCharacters = std::move(right.m_skipCharacters);
	m_stopCharacters = std::move(right.m_stopCharacters);
	m_readMethod = right.m_readMethod;
	m_readLimit = right.m_readLimit;
	m_readEndOfLine = right.m_readEndOfLine;
	return *this;
}

std::unordered_set<wchar_t> const & BaseSettings::GetSkipCharacters() const
{
	return m_skipCharacters;
}

std::unordered_set<wchar_t> const & BaseSettings::GetStopCharacters() const
{
	return m_stopCharacters;
}

ReadVectorMethod BaseSettings::GetReadMethod() const
{
	return m_readMethod;
}

size_t BaseSettings::GetReadLimit() const
{
	return m_readLimit;
}

bool BaseSettings::GetReadEndOfLine() const
{
	return m_readEndOfLine;
}

BaseSettingsBuilder & BaseSettingsBuilder::SetSkipCharacters(std::unordered_set<wchar_t> skipCharacters)
{
	m_baseSettings.m_skipCharacters = std::move(skipCharacters);
	return *this;
}

BaseSettingsBuilder & BaseSettingsBuilder::SetStopCharacters(std::unordered_set<wchar_t> stopCharacters)
{
	m_baseSettings.m_stopCharacters = std::move(stopCharacters);
	return *this;
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

BaseSettingsBuilder & BaseSettingsBuilder::SetReadEndOfLine(bool readEndOfLine)
{
	m_baseSettings.m_readEndOfLine = readEndOfLine;
	return *this;
}

BaseSettings const & BaseSettingsBuilder::Build() const
{
	return m_baseSettings;
}
