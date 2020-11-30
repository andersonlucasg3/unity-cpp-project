#include "ManagedType.h"
#include "ManagedPointer.h"
#include "ManagedAssembly.h"
#include "ManagedInstance.h"
#include "UnityAPI/UnityAPIExtern.h"
#include "UnityAPI/ManagedBridge/Members/MemberType.h"
#include "UnityAPI/ManagedBridge/Members/ConstructorMember.h"
#include "UnityAPI/ManagedBridge/Members/FieldMember.h"
#include "UnityAPI/ManagedBridge/Members/PropertyMember.h"

using namespace std;

namespace UnityEngine::ManagedBridge {
    typedef void *(UNITY_METHOD *__UnityManagedGetTypePtrFunc)(const char *typeName);
    typedef void *(UNITY_METHOD *__UnityManagedGetConstructorPtrFunc)(char **parameters, int paramCount);
    typedef void *(UNITY_METHOD *__UnityManagedGetMemberPtrFunc)(const void *typePtr, const char *memberName, MemberType type);

    __UnityManagedGetTypePtrFunc _getTypePtr = nullptr;
    __UnityManagedGetConstructorPtrFunc _getConstructorPtr = nullptr;
    __UnityManagedGetMemberPtrFunc _getMemberPtr = nullptr;

#pragma region MemberType implementation

    const ManagedType ManagedType::null = ManagedType();

    ManagedType::ManagedType() : Managed(ManagedPointer::null) {
        // nothing yet
    }

    ManagedType::ManagedType(ManagedPointer ptr) : Managed(ptr) {
        // nothing yet
    }

    ManagedType::ManagedType(ManagedAssembly assembly) : Managed(_getTypePtr(assembly.name())) {
        // nothing yet
    }

    ConstructorMember ManagedType::getConstructor(char **parameters, int paramCount) const {
        return ConstructorMember(_getConstructorPtr(parameters, paramCount));
    }

    FieldMember ManagedType::getField(const char *fieldName) const {
        ManagedPointer fieldPtr = _getMemberPtr(this, fieldName, MemberType::field);
        return FieldMember(fieldPtr);
    }

    PropertyMember ManagedType::getProperty(const char *memberName) const {
        ManagedPointer propertyPtr = _getMemberPtr(this, memberName, MemberType::property);
        return PropertyMember(propertyPtr);
    }

#pragma endregion
}

using namespace UnityEngine::ManagedBridge;

extern "C" {
[[maybe_unused]] UNITY_EXPORT void SetManagedGetTypePtrMethod(__UnityManagedGetTypePtrFunc func) { _getTypePtr = func; }
[[maybe_unused]] UNITY_EXPORT void SetManagedGetConstructorPtrMethod(__UnityManagedGetConstructorPtrFunc func) { _getConstructorPtr = func; }
[[maybe_unused]] UNITY_EXPORT void SetManagedGetMemberPtrMethod(__UnityManagedGetMemberPtrFunc func) { _getMemberPtr = func; }
}