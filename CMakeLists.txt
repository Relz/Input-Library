CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
PROJECT(InputLibrary)

SET(CMAKE_CXX_STANDARD 17)

ADD_LIBRARY(InputLibrary SHARED Input.cpp Input.h)

ADD_SUBDIRECTORY(BaseSettings)
ADD_SUBDIRECTORY(InputLibraryConstant)
ADD_SUBDIRECTORY(MatrixSettings)
ADD_SUBDIRECTORY(ReadVectorMethod)
ADD_SUBDIRECTORY(StreamString)
ADD_SUBDIRECTORY(VectorSettings)

TARGET_LINK_LIBRARIES(InputLibrary
	BaseSettings
	InputLibraryConstant
	MatrixSettings
	ReadVectorMethod
	StreamString
	VectorSettings)
