#include "Managed.h"
#include "UnityAPI/UnityAPIExtern.h"

namespace UnityEngine::ManagedBridge {
    typedef void (UNITY_METHOD *__UnitySendMessageFunc)(const char *gameObjectName, const char *methodName, const char *message);
    typedef void (UNITY_METHOD *__UnityManagedDestructorFunc)(const void *instancePtr);

    __UnityManagedDestructorFunc UnityManagedDestructor = nullptr;

#pragma region Managed implementation

    [[maybe_unused]] UnitySendMessageMethod Managed::UnitySendMessage = nullptr;

    Managed::Managed(ManagedPointer ptr) {
        _ptr = ptr;
    }

    Managed::operator ManagedPointer const () const {
        return _ptr;
    }

    void Managed::destroy(Managed *managed) {
        destroy(*managed);
        delete managed;
    }

    void Managed::destroy(const Managed &managed) {
        destroy((ManagedPointer)managed);
    }

    void Managed::destroy(ManagedPointer pointer) {
        UnityManagedDestructor(pointer);
    }

#pragma endregion
}

using namespace UnityEngine::ManagedBridge;

extern "C" {
[[maybe_unused]] UNITY_EXPORT void SetUnitySendMessageMethod(__UnitySendMessageFunc func) { Managed::UnitySendMessage = func; }
[[maybe_unused]] UNITY_EXPORT void SetManagedDestructorMethod(__UnityManagedDestructorFunc func) { UnityManagedDestructor = func; }
}