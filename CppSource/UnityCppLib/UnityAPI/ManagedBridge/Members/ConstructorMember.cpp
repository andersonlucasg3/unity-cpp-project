#include "ConstructorMember.h"
#include "UnityAPI/ManagedBridge/ManagedType.h"
#include "UnityAPI/ManagedBridge/ManagedInstance.h"
#include "UnityAPI/UnityAPIExtern.h"

namespace UnityEngine::ManagedBridge::Members {
    typedef void *(UNITY_METHOD *__UnityManagedConstructorFunc)(const void *typePtr, const void *constructorPtr, void **parameters, int paramCount);

    __UnityManagedConstructorFunc _constructor = nullptr;

#pragma region ConstructorMember implementation
    const ConstructorMember ConstructorMember::null = ConstructorMember();

    ConstructorMember::ConstructorMember() : ManagedMember(ManagedPointer::null, MemberType::constructor) {
        // nothing yet
    }

    ConstructorMember::ConstructorMember(ManagedPointer ptr) : ManagedMember(ptr, MemberType::constructor) {
        // nothing yet
    }

    ManagedInstance ConstructorMember::constructor(ManagedType type, void **parameters, int paramCount) const {
        ManagedPointer const typePtr = type;
        return ManagedInstance(type, _constructor(typePtr, this, parameters, paramCount));
    }

#pragma endregion
}

using namespace UnityEngine::ManagedBridge::Members;

extern "C" {
    UNITY_EXPORT void SetManagedConstructorMethod(__UnityManagedConstructorFunc func) { _constructor = func; }
}