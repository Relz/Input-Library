#ifndef INPUTLIBRARY_MATRIXSETTINGS_H
#define INPUTLIBRARY_MATRIXSETTINGS_H

#include "../BaseSettings/BaseSettings.h"
#include "../ReadVectorMethod/ReadVectorMethod.h"

class MatrixSettings
{
	friend class MatrixSettingsBuilder;

public:
	MatrixSettings() = default;
	BaseSettings const & GetBaseSettings() const;

private:
	BaseSettings m_baseSettings;
};

class MatrixSettingsBuilder
{
public:
	MatrixSettingsBuilder() = default;
	MatrixSettings const & Build(BaseSettings const & baseSettings = BaseSettings());

private:
	MatrixSettings m_matrixSettings;
};

#endif
