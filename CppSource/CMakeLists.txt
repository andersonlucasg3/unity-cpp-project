cmake_minimum_required(VERSION 3.17)
project(CppSource)

set(CMAKE_CXX_STANDARD 20)

add_library(
        UnityCppAssemblyHelper
        SHARED
        UnityCppAssemblyHelper/AssemblyHelper.cpp
)

target_sources(
        UnityCppAssemblyHelper
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/UnityCppAssemblyHelper
)

target_include_directories(
        UnityCppAssemblyHelper
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/UnityCppAssemblyHelper
)

add_library(
        UnityCppLib
        SHARED
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
        UnityCppLib/UnityAPI/UnityEngine/GameObject.cpp
        UnityCppLib/UnityAPI/UnityEngine/GameObject.h
        UnityCppLib/UnityAPI/UnityEngine/Debug.cpp
        UnityCppLib/UnityAPI/UnityEngine/Debug.h
        UnityCppLib/UnityAPI/UnityEngine/Transform.cpp
        UnityCppLib/UnityAPI/UnityEngine/Transform.h
        UnityCppLib/UnityAPI/UnityEngine/Component.cpp
        UnityCppLib/UnityAPI/UnityEngine/Component.h
        UnityCppLib/UnityAPI/ManagedBridge/Managed.cpp 
        UnityCppLib/UnityAPI/ManagedBridge/Managed.h 
        UnityCppLib/UnityAPI/UnityEngine/Object.cpp 
        UnityCppLib/UnityAPI/UnityEngine/Object.h
        UnityCppLib/UnityAPI/ManagedBridge/Members/ManagedMember.cpp
        UnityCppLib/UnityAPI/ManagedBridge/Members/ManagedMember.h
        UnityCppLib/UnityAPI/UnityEngine/HideFlags.h
        UnityCppLib/UnityAPI/ManagedBridge/Members/MemberType.h
        UnityCppLib/UnityAPI/ManagedBridge/ManagedType.cpp
        UnityCppLib/UnityAPI/ManagedBridge/ManagedType.h
        UnityCppLib/UnityAPI/ManagedBridge/ManagedPointer.h
        UnityCppLib/UnityAPI/ManagedBridge/ManagedPointer.cpp
        UnityCppLib/UnityAPI/ManagedBridge/ManagedInstance.cpp
        UnityCppLib/UnityAPI/ManagedBridge/ManagedInstance.h
        UnityCppLib/UnityAPI/ManagedBridge/ManagedAssemblyInfo.cpp
        UnityCppLib/UnityAPI/ManagedBridge/ManagedAssemblyInfo.h
        UnityCppLib/UnityAPI/ManagedBridge/Members/ConstructorMember.cpp
        UnityCppLib/UnityAPI/ManagedBridge/Members/ConstructorMember.h
        UnityCppLib/UnityAPI/ManagedBridge/Members/FieldMember.cpp
        UnityCppLib/UnityAPI/ManagedBridge/Members/FieldMember.h
        UnityCppLib/UnityAPI/ManagedBridge/Members/PropertyMember.cpp
        UnityCppLib/UnityAPI/ManagedBridge/Members/PropertyMember.h UnityCppLib/UnityAPI/UnityEngine/UnityEngine.h UnityCppLib/UnityAPI/UnityEngine/UnityEngine.cpp UnityCppLib/UnityAPI/NetFramework/System.h UnityCppLib/UnityAPI/NetFramework/System.cpp)

target_sources(
        UnityCppLib
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/UnityCppLib
)

target_include_directories(
        UnityCppLib
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/UnityCppLib
)

set(CMAKE_CXX_FLAGS "-fdeclspec")

set(LIBRARY_OUTPUT_PATH ../../Assets/Plugins/NativeComponents)