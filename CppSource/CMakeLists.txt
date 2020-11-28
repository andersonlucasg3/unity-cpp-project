cmake_minimum_required(VERSION 3.17)
project(CppSource)

set(CMAKE_CXX_STANDARD 20)

add_library(UnityCppLib SHARED
        UnityCppLib/Components/Factory/ComponentFactory.cpp
        UnityCppLib/Components/NativeComponent.cpp
        UnityCppLib/Components/Factory/ComponentFactory.h
        UnityCppLib/Components/NativeComponent.h
        UnityCppLib/Game/TestComponent.cpp
        UnityCppLib/Game/TestComponent.h
        UnityCppLib/UnityAPI/UnityAPIExtern.h
        UnityCppLib/Game/ComponentsRegistration.h
        UnityCppLib/Components/RequiredComponentDefines.h
        UnityCppLib/UnityAPI/UnityAPIExtern.cpp
        UnityCppLib/UnityAPI/UnityEngine/GameObject.cpp UnityCppLib/UnityAPI/UnityEngine/GameObject.h UnityCppLib/UnityAPI/UnityEngine/Debug.cpp UnityCppLib/UnityAPI/UnityEngine/Debug.h UnityCppLib/UnityAPI/UnityEngine/Transform.cpp UnityCppLib/UnityAPI/UnityEngine/Transform.h UnityCppLib/UnityAPI/UnityEngine/Component.cpp UnityCppLib/UnityAPI/UnityEngine/Component.h)
target_include_directories(UnityCppLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/UnityCppLib)

add_executable(UnityCppTestApp
        UnityCppTestApp/main.cpp
        UnityCppTestApp/UnityInitialization.h
        )

target_include_directories(UnityCppTestApp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/UnityCppLib)
target_link_libraries(UnityCppTestApp LINK_PUBLIC UnityCppLib)

set(CMAKE_CXX_FLAGS "-fdeclspec")

set(LIBRARY_OUTPUT_PATH ../../Assets/Plugins/NativeComponents)