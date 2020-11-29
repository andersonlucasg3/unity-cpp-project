#include "Managed.h"
#include "ManagedMember.h"
#include "UnityAPI/UnityAPIExtern.h"

#include <typeinfo>

namespace UnityEngine::ManagedBridge {
    typedef void (UNITY_METHOD *__UnitySendMessageFunc)(const char *gameObjectName, const char *methodName, const char *message);

    typedef intptr_t *(UNITY_METHOD *__UnityManagedConstructorFunc)(const char *typeName);
    typedef void (UNITY_METHOD *__UnityManagedDestructorFunc)(intptr_t *instance);

    typedef intptr_t *(UNITY_METHOD *__UnityManagedGetMemberPtrFunc)(intptr_t *instance, const char *memberName, MemberType type);

    __UnityManagedConstructorFunc UnityManagedConstructor = nullptr;
    __UnityManagedDestructorFunc UnityManagedDestructor = nullptr;
    __UnityManagedGetMemberPtrFunc UnityManagedGetMemberPtr = nullptr;

#pragma region Managed implementation

    UnitySendMessageMethod Managed::UnitySendMessage = nullptr;

    Managed::Managed() {
        _instance = nullptr;
    }

    Managed::~Managed() {
        UnityManagedDestructor(_instance);
    }

    void Managed::newInstance(const char *typeName) {
        _instance = UnityManagedConstructor(typeName);
    }

    ManagedMember *Managed::getMember(const char *memberName, MemberType type) {
        intptr_t *memberPtr = UnityManagedGetMemberPtr(_instance, memberName, type);;
        return new ManagedMember(memberPtr, this, type);
    }

#pragma endregion
}

using namespace UnityEngine::ManagedBridge;

extern "C" {
UNITY_EXPORT void SetUnitySendMessageMethod(__UnitySendMessageFunc func) { Managed::UnitySendMessage = func; }
UNITY_EXPORT void SetManagedConstructorMethod(__UnityManagedConstructorFunc func) { UnityManagedConstructor = func; }
UNITY_EXPORT void SetManagedDestructorMethod(__UnityManagedDestructorFunc func) { UnityManagedDestructor = func; }
UNITY_EXPORT void SetManagedGetMemberPtrMethod(__UnityManagedGetMemberPtrFunc func) { UnityManagedGetMemberPtr = func; }
}