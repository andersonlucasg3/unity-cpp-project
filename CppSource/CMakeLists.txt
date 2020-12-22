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
        UnityCppLib/UnityAPI/UnityAPIExtern.h
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
        UnityCppLib/UnityAPI/ManagedBridge/Members/PropertyMember.h
        UnityCppLib/UnityAPI/UnityEngine/UnityEngine.h
        UnityCppLib/UnityAPI/UnityEngine/UnityEngine.cpp
        UnityCppLib/UnityAPI/NetFramework/System.h
        UnityCppLib/UnityAPI/NetFramework/System.cpp
        UnityCppLib/UnityAPI/Helpers/Helpers.cpp
        UnityCppLib/UnityAPI/Helpers/Helpers.h
        UnityCppLib/UnityAPI/UnityEngine/Vector3.cpp
        UnityCppLib/UnityAPI/UnityEngine/Vector3.h
        UnityCppLib/UnityAPI/UnityEngine/Quaternion.cpp
        UnityCppLib/UnityAPI/UnityEngine/Quaternion.h
        UnityCppLib/UnityAPI/ManagedBridge/UnmanagedValue.cpp
        UnityCppLib/UnityAPI/ManagedBridge/UnmanagedValue.h
        UnityCppLib/UnityAPI/ManagedBridge/Members/MethodMember.cpp
        UnityCppLib/UnityAPI/ManagedBridge/Members/MethodMember.h
        UnityCppLib/UnityAPI/UnityEngine/Behaviour.cpp
        UnityCppLib/UnityAPI/UnityEngine/Behaviour.h
        UnityCppLib/UnityAPI/UnityEngine/MonoBehaviour.cpp
        UnityCppLib/UnityAPI/UnityEngine/MonoBehaviour.h
        UnityCppLib/UnityAPI/CppEngine/Registry.h
        UnityCppLib/UnityAPI/CppEngine/Registry.cpp
        UnityCppLib/Game/ComponentsEntryPoint.h
        UnityCppLib/Game/ComponentsEntryPoint.cpp
        UnityCppLib/UnityAPI/CppEngine/Trash.cpp
        UnityCppLib/UnityAPI/CppEngine/Trash.h
        UnityCppLib/UnityAPI/CppEngine/semaphores/multiplat_semaphore.cpp
        UnityCppLib/UnityAPI/CppEngine/semaphores/multiplat_semaphore.h
#COMPONENTS_GO_HERE
)

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

if (APPLE)
    set(CMAKE_CXX_FLAGS "-fdeclspec")
endif ()
set(CMAKE_C_FLAGS "-wignored-attributes")

set(LIBRARY_OUTPUT_PATH ../../Assets/Plugins/UnityCpp)