#ifndef INPUTLIBRARY_INPUT_H
#define INPUTLIBRARY_INPUT_H

#include "StreamStringLibrary/StreamString.h"
#include <fstream>
#include <functional>
#include <iostream>
#include <limits>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <sstream>

class Input
{
public:
	template<typename TVectorElement, typename TReadElement = TVectorElement>
	static bool EmplaceBackElement(std::vector<TVectorElement> & vector, TReadElement & element)
	{
		vector.emplace_back(element);
		return true;
	}

	template<typename TVectorElement, typename TReadElement = TVectorElement>
	static bool EmplaceBackVectorIfNotEmpty(std::vector<std::vector<TVectorElement>> & matrix, std::vector<TReadElement> & vector)
	{
		if (vector.empty())
		{
			return false;
		}
		return EmplaceBackElement(matrix, vector);
	}

	explicit Input(std::istream & is)
		: m_is(is)
	{
		if (IsEndOfStream())
		{
			throw std::invalid_argument("Stream is empty");
		}
		Init();
	}

	explicit Input(std::string fileName)
		: m_fileName(std::move(fileName))
	{
		m_inputFile.open(m_fileName);
		if (!m_inputFile.good())
		{
			throw std::invalid_argument("File \"" + m_fileName + "\" doesn't exists");
		}
		if (IsEndOfStream())
		{
			throw std::invalid_argument("File \"" + m_fileName + "\" is empty");
		}
		Init();
	}

	std::string const & GetFileName() const
	{
		return m_fileName;
	}

	StreamPosition const & GetPosition() const
	{
		return m_position;
	}

	bool GetNextCharacter(char & nextCharacter) const
	{
		if (IsEndOfStream())
		{
			return false;
		}
		nextCharacter = std::char_traits<char>::to_char_type(m_is.peek());
		return true;
	}

	bool IsEndOfStream() const
	{
		return m_is.peek() == std::ifstream::traits_type::eof();
	}

	bool IsEndOfLine() const
	{
		int nextCharacterCode = m_is.peek();
		return nextCharacterCode == ENDL_SYMBOL_CODE_CR || nextCharacterCode == ENDL_SYMBOL_CODE_LF;
	}

	bool SkipLine()
	{
		while (ReadChar(false))
		{
		}
		return ReadEndOfLine();
	}

	bool SkipLines(size_t skipCount)
	{
		while (skipCount != 0)
		{
			if (!SkipLine())
			{
				return false;
			}
			--skipCount;
		}
		return true;
	}

	template<typename T>
	bool SkipArgument(bool skipEndOfLine = true)
	{
		T tempArgument;
		return ReadArguments(skipEndOfLine, tempArgument);
	}

	template<typename T>
	bool SkipArguments(size_t skipCount, bool skipEndOfLine = true)
	{
		while (skipCount != 0)
		{
			if (!SkipArgument<T>(skipEndOfLine))
			{
				return false;
			}
			--skipCount;
		}
		return true;
	}

	bool SkipCharacters(std::unordered_set<char> const & characters)
	{
		bool result = false;
		while (FindDelimiter(characters))
		{
			ReadChar(true);
			result = true;
		}
		return result;
	}

	bool SkipUntilCharacters(std::unordered_set<char> const & characters)
	{
		while (!FindDelimiter(characters) && ReadChar(true))
		{
		}
		return !IsEndOfStream();
	}

	bool SkipUntilStrings(std::vector<std::string> const & strings)
	{
		while (!FindDelimiter(strings) && ReadChar(true))
		{
		}
		return !IsEndOfStream();
	}

	bool ReadLine(std::string & line, bool doAppend = false)
	{
		if (!doAppend)
		{
			line.clear();
		}
		while (ReadCharToString(line, false))
		{
		}
		return ReadEndOfLine();
	}

	template<typename... Targs>
	bool ReadArguments(bool readEndOfLine, Targs &... args)
	{
		return ReadArgumentsFromStream(readEndOfLine, args...);
	}

	bool ReadUntilCharacters(
		std::unordered_set<char> const & characters, std::string & readString, bool doAppend = false)
	{
		if (!doAppend)
		{
			readString.clear();
		}
		while (!FindDelimiter(characters) && ReadCharToString(readString, true))
		{
		}
		return !IsEndOfStream();
	}

	bool ReadUntilStrings(std::vector<std::string> const & strings, std::string & readString, bool doAppend = false)
	{
		if (!doAppend)
		{
			readString.clear();
		}
		while (!FindDelimiter(strings) && ReadCharToString(readString, true))
		{
		}
		return !IsEndOfStream();
	}

	template<
		typename TVectorElement,
		typename TReadElement = TVectorElement,
		typename ForEachElementFunctor = std::function<bool(std::vector<TVectorElement> &, TReadElement &)>
	>
	bool ReadVector(
		std::vector<TVectorElement> & vector,
		bool readEndOfLine = false,
		ForEachElementFunctor forEachReadElement = &EmplaceBackElement<TVectorElement, TReadElement>
	)
	{
		if (IsEndOfStream())
		{
			return false;
		}

		bool result = false;
		while (ReadArgumentToVector(vector, readEndOfLine, forEachReadElement))
		{
			result = true;
		}

		return result;
	}

	template<
		typename TVectorElement,
		typename TReadElement = TVectorElement,
		typename ForEachElementFunctor = std::function<bool(std::vector<TVectorElement> &, TReadElement &)>,
		typename ForEachVectorFunctor = std::function<bool(std::vector<std::vector<TVectorElement>> &, std::vector<TReadElement> &)>
	>
	bool ReadMatrix(
		std::vector<std::vector<TVectorElement>> & matrix,
		bool readEndOfLine = false,
		ForEachElementFunctor forEachReadElement = &EmplaceBackElement<TVectorElement, TReadElement>,
		ForEachVectorFunctor forEachReadVector = &EmplaceBackVectorIfNotEmpty<TVectorElement, TReadElement>
	)
	{
		if (IsEndOfStream())
		{
			return false;
		}

		bool result = false;
		while (true)
		{
			std::vector<TVectorElement> vector;
			while (ReadArgumentToVector(vector, readEndOfLine, forEachReadElement))
			{
			}
			if (forEachReadVector(matrix, vector))
			{
				result = true;
				ReadEndOfLine();
			}
			else
			{
				break;
			}
		}

		return result;
	}

	bool Scan(
		std::vector<std::string> const & delimiters,
		StreamString & scannedStreamString,
		StreamString & delimiterStreamString
	)
	{
		StreamString possibleScannedStreamString("", m_position);
		StreamString possibleDelimiterStreamString;
		while (!IsEndOfStream())
		{
			if (FindDelimiter(delimiters, possibleDelimiterStreamString.string))
			{
				possibleDelimiterStreamString.position = m_position;
				SkipArguments<char>(possibleDelimiterStreamString.string.length());
				break;
			}
			else
			{
				ReadCharToString(possibleScannedStreamString.string, true);
			}
		}
		if (!possibleScannedStreamString.string.empty() || !possibleDelimiterStreamString.string.empty())
		{
			scannedStreamString = possibleScannedStreamString;
			delimiterStreamString = possibleDelimiterStreamString;
			return true;
		}
		return false;
	}

private:
	static int const ENDL_SYMBOL_CODE_LF = 10;
	static int const ENDL_SYMBOL_CODE_CR = 13;

	std::string m_fileName;
	std::ifstream m_inputFile;
	std::istream & m_is = m_inputFile;

	StreamPosition m_position;

	void Init()
	{
		std::locale::global(std::locale("en_US.UTF-8"));
		m_inputFile.imbue(std::locale("en_US.UTF-8"));
	}

	template<typename T>
	bool ReadArgumentFromStream(bool readEndOfLine, T & arg)
	{
		if (readEndOfLine)
		{
			do
			{
				SkipWhitespaces();
			}
			while (IsEndOfLine() && ReadEndOfLine());
		}
		SkipWhitespaces();
		if ((!readEndOfLine && IsEndOfLine()) || IsEndOfStream())
		{
			return false;
		}

		bool result = true;
		long beforeReadingPosition = m_is.tellg();
		if (!(m_is >> arg))
		{
			result = false;
		}
		if (IsEndOfStream())
		{
			m_is.clear();
			m_is.seekg(0, std::istream::end);
		}
		long afterReadingPosition = m_is.tellg();
		long readLength = afterReadingPosition - beforeReadingPosition;
		if (result)
		{
			m_position.IncreaseColumn(readLength);
		}
		else
		{
			m_is.seekg(beforeReadingPosition);
		}
		return result;
	}

	bool ReadArgumentFromStream(bool readEndOfLine, char & arg)
	{
		return ReadChar(arg, readEndOfLine);
	}

	bool ReadArgumentsFromStream(bool readEndOfLine)
	{
		return true;
	}

	template<typename T, typename... Targs>
	bool ReadArgumentsFromStream(bool readEndOfLine, T & arg, Targs &... args)
	{
		return ReadArgumentFromStream(readEndOfLine, arg) && ReadArgumentsFromStream(readEndOfLine, args...);
	}

	bool FindDelimiter(std::unordered_set<char> const & delimiters)
	{
		char delimiter;
		return FindDelimiter(delimiters, delimiter);
	}

	bool FindDelimiter(std::unordered_set<char> const & delimiters, char & foundDelimiter)
	{
		if (delimiters.empty())
		{
			return false;
		}
		char nextCharacter;
		if (!GetNextCharacter(nextCharacter) || delimiters.find(nextCharacter) == delimiters.end())
		{
			return false;
		}
		foundDelimiter = nextCharacter;
		return true;
	}

	bool FindDelimiter(std::vector<std::string> const & delimiters)
	{
		std::string delimiter;
		return FindDelimiter(delimiters, delimiter);
	}

	bool FindDelimiter(std::vector<std::string> const & delimiters, std::string & resultDelimiter)
	{
		bool result = false;
		StreamPosition savedPosition = m_position;
		for (std::string const & delimiter : delimiters)
		{
			std::string possibleDelimiter;
			if (ReadString(delimiter.length(), possibleDelimiter) && possibleDelimiter == delimiter)
			{
				if (IsEndOfStream())
				{
					m_is.clear();
				}
				long currentPosition = m_is.tellg();
				m_is.seekg(currentPosition - possibleDelimiter.length());
				resultDelimiter = std::move(possibleDelimiter);
				result = true;
				break;
			}
			if (!possibleDelimiter.empty())
			{
				if (IsEndOfStream())
				{
					m_is.clear();
				}
				long currentPosition = m_is.tellg();
				m_is.seekg(currentPosition - possibleDelimiter.length());
			}
		}
		m_position = savedPosition;
		return result;
	}

	bool ReadCharToString(std::string & str, bool readEndOfLine = true)
	{
		char ch;
		if (ReadChar(ch, readEndOfLine))
		{
			str.push_back(ch);
			return true;
		}
		return false;
	}

	bool ReadChar(bool readEndOfLine = true)
	{
		char ch;
		return ReadChar(ch, readEndOfLine);
	}

	bool ReadChar(char & ch, bool readEndOfLine = true)
	{
		if (readEndOfLine && ReadEndOfLine(ch))
		{
			return true;
		}
		if (!IsEndOfLine() && !IsEndOfStream() && m_is.get(ch))
		{
			m_position.IncreaseColumn();
			return true;
		}
		return false;
	}

	bool ReadString(size_t const length, std::string & result)
	{
		std::string possibleResult;
		while (possibleResult.length() < length && ReadCharToString(possibleResult, true))
		{
		}
		if (possibleResult.length() == length)
		{
			result = std::move(possibleResult);
			return true;
		}
		if (IsEndOfStream())
		{
			m_is.clear();
		}
		long currentPosition = m_is.tellg();
		m_is.seekg(currentPosition - possibleResult.length());
		return false;
	}

	bool ReadEndOfLine()
	{
		char ch;
		return ReadEndOfLine(ch);
	}

	bool ReadEndOfLine(char & endOfLine)
	{
		bool endOfLineFound = false;
		int nextCharacterCode = m_is.peek();
		if (nextCharacterCode == ENDL_SYMBOL_CODE_CR)
		{
			m_is.get(endOfLine);
			if (m_is.peek() == ENDL_SYMBOL_CODE_LF)
			{
				m_is.get(endOfLine);
			}
			endOfLineFound = true;
		}
		else if (nextCharacterCode == ENDL_SYMBOL_CODE_LF)
		{
			m_is.get(endOfLine);
			endOfLineFound = true;
		}
		if (endOfLineFound)
		{
			m_position.IncreaseLine();
			m_position.ResetColumn();
		}
		return endOfLineFound;
	}

	template<
		typename TVectorElement,
		typename TReadElement = TVectorElement,
		typename ForEachElementFunctor = std::function<bool(std::vector<TVectorElement> &, TReadElement &)>
	>
	bool ReadArgumentToVector(
		std::vector<TVectorElement> & vector,
		bool readEndOfLine,
		ForEachElementFunctor forEachReadElement = &EmplaceBackElement<TVectorElement, TReadElement>
	)
	{
		TReadElement elem;
		bool isReadingSucceeded = ReadArgumentFromStream(readEndOfLine, elem);
		bool continueReading = isReadingSucceeded && forEachReadElement(vector, elem);
		return isReadingSucceeded && continueReading;
	}

	bool SkipWhitespaces(bool add = false)
	{
		long skippedCount = 0;
		return SkipWhitespaces(skippedCount, add);
	}

	bool SkipWhitespaces(long & skippedCount, bool add = false)
	{
		bool result = false;
		if (!add)
		{
			skippedCount = 0;
		}

		char nextCharacter;
		while (GetNextCharacter(nextCharacter) && nextCharacter == ' ' && ReadChar())
		{
			result = true;
			++skippedCount;
		}
		return result;
	}
};

#endif
