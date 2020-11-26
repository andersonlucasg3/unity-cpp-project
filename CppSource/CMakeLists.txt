cmake_minimum_required(VERSION 3.17)
project(CppSource)

set(CMAKE_CXX_STANDARD 20)

add_library(CppSource SHARED
        src/Components/Factory/ComponentFactoryExtern.cpp
        src/Components/Factory/ComponentFactory.cpp
        src/Components/CustomComponent.cpp
        src/Components/Factory/ComponentFactoryExtern.h
        src/Components/Factory/ComponentFactory.h
        src/Components/CustomComponent.h
        src/Game/TestComponent.cpp
        src/Game/TestComponent.h
        src/UnityAPI/UnityAPIExtern.h src/Game/ComponentsRegistration.h src/Components/RequiredComponentDefines.h)

set(LIBRARY_OUTPUT_PATH ../../Assets/Plugins/NativeComponents)