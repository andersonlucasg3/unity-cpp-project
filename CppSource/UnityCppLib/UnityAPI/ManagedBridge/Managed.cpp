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

    void Managed::destroy(Managed *managed) {
        destroy(*managed);
        delete managed;
    }

    void Managed::destroy(const Managed &managed) {
        destroy(managed.toPointer());
    }

    void Managed::destroy(ManagedPointer pointer) {
        UnityManagedDestructor(pointer.toManaged());
    }

    ManagedPointer Managed::toPointer() const {
        return _ptr;
    }

    bool Managed::operator==(void *ptr) {
        return _ptr == ptr;
    }

    bool Managed::operator!=(void *ptr) {
        return _ptr != ptr;
    }

    bool Managed::operator==(Managed other) {
        return _ptr == other._ptr;
    }

    bool Managed::operator!=(Managed other) {
        return _ptr != other._ptr;
    }

#pragma endregion
}

using namespace UnityEngine::ManagedBridge;

extern "C" {
[[maybe_unused]] UNITY_EXPORT void SetUnitySendMessageMethod(__UnitySendMessageFunc func) { Managed::UnitySendMessage = func; }
[[maybe_unused]] UNITY_EXPORT void SetManagedDestructorMethod(__UnityManagedDestructorFunc func) { UnityManagedDestructor = func; }
}