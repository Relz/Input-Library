#include "StreamString.h"

StreamString::StreamString(std::string str, StreamPosition position)
	: string(std::move(str))
	, position(position)
{}
