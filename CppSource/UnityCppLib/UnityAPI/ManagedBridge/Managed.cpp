#include <cstdlib>
#include "Managed.h"
#include "ManagedMember.h"
#include "UnityAPI/UnityAPIExtern.h"

namespace UnityEngine::valuePointer {
    typedef void (UNITY_METHOD *__UnitySendMessageFunc)(const char *gameObjectName, const char *methodName, const char *message);

    typedef intptr_t *(UNITY_METHOD *__UnityManagedConstructorFunc)(const char *typeName);
    typedef void (UNITY_METHOD *__UnityManagedDestructorFunc)(intptr_t *instance);

    typedef intptr_t *(UNITY_METHOD *__UnityManagedGetMemberPtrFunc)(intptr_t *instance, const char *memberName, MemberType type);

    __UnityManagedConstructorFunc UnityManagedConstructor = nullptr;
    __UnityManagedDestructorFunc UnityManagedDestructor = nullptr;
    __UnityManagedGetMemberPtrFunc UnityManagedGetMemberPtr = nullptr;

#pragma region Managed implementation

    [[maybe_unused]] UnitySendMessageMethod Managed::UnitySendMessage = nullptr;

    Managed::Managed() {
        _instance = nullptr;
    }

    Managed::Managed(intptr_t *instance) {
        _instance = instance;
    }

    Managed::~Managed() {
        UnityManagedDestructor(_instance);
    }

    void Managed::construct(const char *typeName) {
        _instance = UnityManagedConstructor(typeName);
    }

    ManagedMember *Managed::getMember(const char *memberName, MemberType type) {
        intptr_t *memberPtr = UnityManagedGetMemberPtr(_instance, memberName, type);;
        return new ManagedMember(memberPtr, _instance, type);
    }

    void Managed::destroy(ManagedMember *member) {
        UnityManagedDestructor(member->_memberPtr);
        delete member;
    }

    void Managed::destroy(ManagedMember *member, bool freeMemberPtr) {
        UnityManagedDestructor(member->_memberPtr);
        free(member->_memberPtr);
        delete member;
    }

#pragma endregion
}

using namespace UnityEngine::valuePointer;

extern "C" {
[[maybe_unused]] UNITY_EXPORT void SetUnitySendMessageMethod(__UnitySendMessageFunc func) { Managed::UnitySendMessage = func; }
[[maybe_unused]] UNITY_EXPORT void SetManagedConstructorMethod(__UnityManagedConstructorFunc func) { UnityManagedConstructor = func; }
[[maybe_unused]] UNITY_EXPORT void SetManagedDestructorMethod(__UnityManagedDestructorFunc func) { UnityManagedDestructor = func; }
[[maybe_unused]] UNITY_EXPORT void SetManagedGetMemberPtrMethod(__UnityManagedGetMemberPtrFunc func) { UnityManagedGetMemberPtr = func; }
}