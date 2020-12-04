#include "ConstructorMember.h"
#include "UnityAPI/ManagedBridge/ManagedType.h"
#include "UnityAPI/ManagedBridge/ManagedInstance.h"
#include "UnityAPI/ManagedBridge/UnmanagedValue.h"
#include "UnityAPI/UnityAPIExtern.h"

namespace ManagedBridge::Members {
    typedef void *(UNITY_METHOD *__UnityManagedConstructorFunc)(pointer_c constructorPtr, UnmanagedValue parameters[], int paramCount);

    __UnityManagedConstructorFunc _constructor = nullptr;

#pragma region ConstructorMember implementation
    const ConstructorMember ConstructorMember::null = ConstructorMember();

    ConstructorMember::ConstructorMember() : ManagedMember(ManagedPointer::null, MemberType::constructor) {
        // nothing yet
    }

    ConstructorMember::ConstructorMember(ManagedPointer ptr) : ManagedMember(ptr, MemberType::constructor) {
        // nothing yet
    }

    ManagedInstance ConstructorMember::constructor(UnmanagedValue parameters[], int paramCount) const {
        ManagedPointer instancePtr(_constructor(toPointer().toManaged(), parameters, paramCount));
        ManagedInstance instance(instancePtr);
        return instance;
    }

#pragma endregion
}

using namespace ManagedBridge::Members;

extern "C" {
    [[maybe_unused]] UNITY_EXPORT void SetManagedConstructorMethod(__UnityManagedConstructorFunc func) { _constructor = func; }
}