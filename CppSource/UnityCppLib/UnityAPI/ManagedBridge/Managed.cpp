#include "Managed.h"
#include "UnityAPI/UnityAPIExtern.h"

namespace ManagedBridge {
    typedef void (UNITY_METHOD *__UnitySendMessageFunc)(string_c gameObjectName, string_c methodName, string_c message);
    typedef void (UNITY_METHOD *__UnityManagedDestructorFunc)(pointer_c instancePtr);

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

    bool Managed::operator==(pointer_m ptr) {
        return _ptr == ptr;
    }

    bool Managed::operator!=(pointer_m ptr) {
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

using namespace ManagedBridge;

extern "C" {
[[maybe_unused]] UNITY_EXPORT void SetUnitySendMessageMethod(__UnitySendMessageFunc func) { Managed::UnitySendMessage = func; }
[[maybe_unused]] UNITY_EXPORT void SetManagedDestructorMethod(__UnityManagedDestructorFunc func) { UnityManagedDestructor = func; }
}