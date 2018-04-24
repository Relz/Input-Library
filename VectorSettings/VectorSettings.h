#ifndef INPUTLIBRARY_VECTORSETTINGS_H
#define INPUTLIBRARY_VECTORSETTINGS_H

#include "../BaseSettings/BaseSettings.h"
#include <unordered_map>

template<typename TVectorElement, typename TReadElement>
class VectorSettingsBuilder;

template<typename TVectorElement, typename TReadElement = TVectorElement>
class VectorSettings
{
	friend class VectorSettingsBuilder<TVectorElement, TReadElement>;

public:
	VectorSettings() = default;

	BaseSettings const & GetBaseSettings() const
	{
		return m_baseSettings;
	}

	std::unordered_map<TReadElement, TVectorElement> GetRules() const
	{
		return m_rules;
	}

	bool DoesStopIfNoRule() const
	{
		return m_stopIfNoRule;
	}

	TVectorElement const & GetDefaultElement() const
	{
		return m_defaultElement;
	}

private:
	BaseSettings m_baseSettings;
	std::unordered_map<TReadElement, TVectorElement> m_rules;
	bool m_stopIfNoRule;
	TVectorElement m_defaultElement;
};

template<typename TVectorElement, typename TReadElement = TVectorElement>
class VectorSettingsBuilder
{
public:
	VectorSettingsBuilder() = default;

	VectorSettingsBuilder & SetRules(std::unordered_map<TReadElement, TVectorElement> rules, bool stopIfNoRule = true, TVectorElement const & defaultElement = TVectorElement())
	{
		m_vectorSettings.m_rules = std::move(rules);
		m_vectorSettings.m_stopIfNoRule = stopIfNoRule;
		m_vectorSettings.m_defaultElement = defaultElement;
		return *this;
	}

	VectorSettings<TVectorElement, TReadElement> const & Build(BaseSettings const & baseSettings = BaseSettings())
	{
		m_vectorSettings.m_baseSettings = baseSettings;
		return m_vectorSettings;
	}

private:
	VectorSettings<TVectorElement, TReadElement> m_vectorSettings;
};

#endif //PROJECT_VECTORSETTINGS_H
