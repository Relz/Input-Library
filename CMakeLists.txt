CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
PROJECT(InputLibrary)

SET(CMAKE_CXX_STANDARD 17)

SET(SOURCE_FILES
	BaseSettings/BaseSettings.cpp
	BaseSettings/BaseSettings.h
	InputLibraryConstant/InputLibraryConstant.cpp
	InputLibraryConstant/InputLibraryConstant.h
	MatrixSettings/MatrixSettings.cpp
	MatrixSettings/MatrixSettings.h
	ReadVectorMethod/ReadVectorMethod.cpp
	ReadVectorMethod/ReadVectorMethod.h
	Input.cpp
	Input.h
	VectorSettings/VectorSettings.cpp
	VectorSettings/VectorSettings.h)

ADD_LIBRARY(InputLibrary SHARED ${SOURCE_FILES})

ADD_SUBDIRECTORY(StreamStringLibrary)

TARGET_LINK_LIBRARIES(InputLibrary StreamStringLibrary)
