#ifndef INPUTLIBRARY_BASESETTINGS_H
#define INPUTLIBRARY_BASESETTINGS_H

#include "../ReadVectorMethod/ReadVectorMethod.h"
#include <unordered_set>
#include <utility>

class BaseSettings
{
	friend class BaseSettingsBuilder;

public:
	BaseSettings() = default;

	BaseSettings & operator=(BaseSettings const & right) noexcept;
	BaseSettings & operator=(BaseSettings && right) noexcept;
	std::unordered_set<wchar_t> const & GetSkipCharacters() const;
	std::unordered_set<wchar_t> const & GetStopCharacters() const;
	ReadVectorMethod GetReadMethod() const;
	size_t GetReadLimit() const;
	bool GetReadEndOfLine() const;

private:
	std::unordered_set<wchar_t> m_skipCharacters;
	std::unordered_set<wchar_t> m_stopCharacters;
	ReadVectorMethod m_readMethod = ReadVectorMethod::PUSH_BACK;
	size_t m_readLimit = SIZE_MAX;
	bool m_readEndOfLine = true;
};

class BaseSettingsBuilder
{
public:
	BaseSettingsBuilder() = default;

	BaseSettingsBuilder & SetSkipCharacters(std::unordered_set<wchar_t> skipCharacters);
	BaseSettingsBuilder & SetStopCharacters(std::unordered_set<wchar_t> stopCharacters);
	BaseSettingsBuilder & SetReadMethod(ReadVectorMethod readMethod);
	BaseSettingsBuilder & SetReadLimit(size_t readLimit);
	BaseSettingsBuilder & SetReadEndOfLine(bool readEndOfLine);
	BaseSettings const & Build() const;

private:
	BaseSettings m_baseSettings;
};

#endif
