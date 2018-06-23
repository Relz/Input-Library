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

	ReadVectorMethod GetReadMethod() const;
	size_t GetReadLimit() const;

private:
	ReadVectorMethod m_readMethod = ReadVectorMethod::PUSH_BACK;
	size_t m_readLimit = SIZE_MAX;
};

class BaseSettingsBuilder
{
public:
	BaseSettingsBuilder() = default;

	BaseSettingsBuilder & SetReadMethod(ReadVectorMethod readMethod);
	BaseSettingsBuilder & SetReadLimit(size_t readLimit);
	BaseSettings Build() const;

private:
	BaseSettings m_baseSettings;
};

#endif
