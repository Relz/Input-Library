#ifndef PROJECT_STREAMSTRING_H
#define PROJECT_STREAMSTRING_H

#include "StreamPosition/StreamPosition.h"
#include <string>

class StreamString
{
public:
	explicit StreamString(std::string str = "", StreamPosition position = StreamPosition());

	std::string string;
	StreamPosition position;
};

#endif //PROJECT_STREAMSTRING_H
