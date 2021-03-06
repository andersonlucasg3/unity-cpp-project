#include "MethodMember.h"

namespace ManagedBridge::Members {
    typedef void (UNITY_METHOD *CallMethodFunc)(pointer_c instancePtr, pointer_c memberPtr, UnmanagedValue parameters[], int paramCount, UnmanagedValue *output);
    typedef bool (UNITY_METHOD *CallMethodOutFunc)(pointer_c instancePtr, pointer_c memberPtr, UnmanagedValue parameters[], int paramCount, UnmanagedValue *output);

    CallMethodFunc _callMethodFunc;
    CallMethodOutFunc _callMethodOutFunc;

    const MethodMember MethodMember::null = MethodMember();

    MethodMember::MethodMember() : ManagedMember(ManagedPointer::null, MemberType::method) {
        // nothing yet
    }

    MethodMember::MethodMember(ManagedPointer ptr) : ManagedMember(ptr, MemberType::method) {
        // nothing yet
    }

    void MethodMember::callMethod(ManagedInstance instance, UnmanagedValue parameters[], int paramCount, UnmanagedValue *output) {
        ManagedPointer instancePtr = instance.toPointer();
        ManagedPointer methodPtr = this->toPointer();
        _callMethodFunc(instancePtr.toManaged(), methodPtr.toManaged(), parameters, paramCount, output);
    }

    bool MethodMember::callMethodOut(ManagedInstance instance, UnmanagedValue parameters[], int paramCount, UnmanagedValue *output) {
        ManagedPointer instancePtr = instance.toPointer();
        ManagedPointer methodPtr = this->toPointer();
        return _callMethodOutFunc(instancePtr.toManaged(), methodPtr.toManaged(), parameters, paramCount, output);
    }
}

extern "C" {
    [[maybe_unused]] UNITY_EXPORT
    void SetManagedCallMethodMethod(CallMethodFunc func) { _callMethodFunc = func; }
    [[maybe_unused]] UNITY_EXPORT
    void SetManagedCallMethodOutMethod(CallMethodOutFunc func) { _callMethodOutFunc = func; }
}