#include "ConstructorMember.h"
#include "UnityAPI/ManagedBridge/ManagedType.h"
#include "UnityAPI/ManagedBridge/ManagedInstance.h"
#include "UnityAPI/UnityAPIExtern.h"

namespace UnityEngine::ManagedBridge::Members {
    typedef void *(UNITY_METHOD *__UnityManagedConstructorFunc)(const void *constructorPtr, void **parameters, int paramCount);

    __UnityManagedConstructorFunc _constructor = nullptr;

#pragma region ConstructorMember implementation
    const ConstructorMember ConstructorMember::null = ConstructorMember();

    ConstructorMember::ConstructorMember() : ManagedMember(ManagedPointer::null, MemberType::constructor) {
        // nothing yet
    }

    ConstructorMember::ConstructorMember(ManagedPointer ptr) : ManagedMember(ptr, MemberType::constructor) {
        // nothing yet
    }

    ManagedInstance ConstructorMember::constructor(void *parameters[], int paramCount) const {
        void **paramPtr = new void *[paramCount];
        for (int index = 0; index < paramCount; ++index) {
            paramPtr[index] = (void *)(const void *)parameters[index];
        }
        ManagedPointer instancePtr(_constructor(this->toPointer().toManaged(), paramPtr, paramCount));
        ManagedInstance instance(instancePtr);
        delete[] paramPtr;
        return instance;
    }

#pragma endregion
}

using namespace UnityEngine::ManagedBridge::Members;

extern "C" {
    [[maybe_unused]] UNITY_EXPORT void SetManagedConstructorMethod(__UnityManagedConstructorFunc func) { _constructor = func; }
}