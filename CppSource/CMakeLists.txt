cmake_minimum_required(VERSION 3.17)
project(CppSource)

set(CMAKE_CXX_STANDARD 20)

add_library(CppSource SHARED
        src/Components/Factory/ComponentFactory.cpp
        src/Components/NativeComponent.cpp
        src/Components/Factory/ComponentFactory.h
        src/Components/NativeComponent.h
        src/Game/TestComponent.cpp
        src/Game/TestComponent.h
        src/UnityAPI/UnityAPIExtern.h
        src/Game/ComponentsRegistration.h
        src/Components/RequiredComponentDefines.h src/UnityAPI/UnityAPIExtern.cpp src/UnityAPI/UnityInitialization.cpp)

set(CMAKE_CXX_FLAGS "-fdeclspec")

set(LIBRARY_OUTPUT_PATH ../../Assets/Plugins/NativeComponents)