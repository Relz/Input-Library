SET(SOURCE_FILES
	StreamString.cpp
	StreamString.h)

ADD_LIBRARY(StreamString ${SOURCE_FILES})

ADD_SUBDIRECTORY(StreamPosition)

TARGET_LINK_LIBRARIES(StreamString StreamPosition)
