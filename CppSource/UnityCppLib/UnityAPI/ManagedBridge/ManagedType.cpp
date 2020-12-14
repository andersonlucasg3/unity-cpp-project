#include "ManagedType.h"
#include "ManagedAssemblyInfo.h"
#include "UnityAPI/UnityAPIExtern.h"
#include "UnityAPI/ManagedBridge/Members/ConstructorMember.h"
#include "UnityAPI/ManagedBridge/Members/FieldMember.h"
#include "UnityAPI/ManagedBridge/Members/PropertyMember.h"
#include "UnityAPI/ManagedBridge/Members/MethodMember.h"

using namespace std;

namespace ManagedBridge {
    typedef void *(UNITY_METHOD *__UnityManagedGetTypePtrFunc)(string_c typeName);
    typedef void *(UNITY_METHOD *__UnityManagedGetConstructorPtrFunc)(pointer_c typePtr, pointer_c parameterTypes[], int paramCount);
    typedef void *(UNITY_METHOD *__UnityManagedGetMemberPtrFunc)(pointer_c typePtr, string_c memberName, MemberType type);

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

    ManagedPointer getTypePtr(const ManagedAssemblyInfo& info) {
        string_c name = info.name();
        void *ptr = _getTypePtr(name);
        return ManagedPointer(ptr);
    }

    ManagedType::ManagedType(const ManagedAssemblyInfo& assembly) : Managed(getTypePtr(assembly)) {
        // nothing yet
    }

    ConstructorMember ManagedType::getConstructor(ManagedType parameterTypes[], int paramCount) const {
        ManagedPointer ptr = this->toPointer();
        pointer_c *paramTypesPtr = new pointer_c [paramCount];
        for (int index = 0; index < paramCount; ++index) {
            paramTypesPtr[index] = parameterTypes[index].toPointer().toManaged();
        }
        ManagedPointer constructorPtr(_getConstructorPtr(ptr.toManaged(), paramTypesPtr, paramCount));
        delete[] paramTypesPtr;
        return ConstructorMember(constructorPtr);
    }

    FieldMember ManagedType::getField(string_c fieldName) const {
        ManagedPointer ptr = this->toPointer();
        ManagedPointer fieldPtr(_getMemberPtr(ptr.toManaged(), fieldName, MemberType::field));
        return FieldMember(fieldPtr);
    }

    PropertyMember ManagedType::getProperty(string_c memberName) const {
        ManagedPointer ptr = this->toPointer();
        ManagedPointer propertyPtr(_getMemberPtr(ptr.toManaged(), memberName, MemberType::property));
        return PropertyMember(propertyPtr);
    }

    MethodMember ManagedType::getMethod(string_c methodName) const {
        ManagedPointer ptr = this->toPointer();
        ManagedPointer methodPtr(_getMemberPtr(ptr.toManaged(), methodName, MemberType::method));
        return MethodMember(methodPtr);
    }

#pragma endregion
}

using namespace ManagedBridge;

extern "C" {
[[maybe_unused]] UNITY_EXPORT void SetManagedGetTypePtrMethod(__UnityManagedGetTypePtrFunc func) { _getTypePtr = func; }
[[maybe_unused]] UNITY_EXPORT void SetManagedGetConstructorPtrMethod(__UnityManagedGetConstructorPtrFunc func) { _getConstructorPtr = func; }
[[maybe_unused]] UNITY_EXPORT void SetManagedGetMemberPtrMethod(__UnityManagedGetMemberPtrFunc func) { _getMemberPtr = func; }
}