#include "ManagedMember.h"
#include "UnityAPI/UnityAPIExtern.h"

using namespace std;

namespace ManagedBridge {
    typedef void (UNITY_METHOD *GetValueFunc)(pointer_c instancePtr, pointer_c memberPtr, MemberType type, UnmanagedValue *value);
    typedef void (UNITY_METHOD *SetValueFunc)(pointer_c instancePtr, pointer_c memberPtr, MemberType type, UnmanagedValue *value);

    struct GetSetValue {
    public:
        GetValueFunc getValue;
        SetValueFunc setValue;

        GetSetValue() = default;
        GetSetValue(GetValueFunc getValue, SetValueFunc setValue) : getValue(getValue), setValue(setValue) { }
    } STRUCT_ALIGN;

    GetSetValue _getSetValueFunc;

#pragma region ManagedMember implementation

    ManagedMember::ManagedMember(ManagedPointer ptr, MemberType type) : Managed(ptr), _type(type) { }

    [[maybe_unused]] void ManagedMember::get(ManagedInstance instance, UnmanagedValue *value) const {
        GetValueFunc func = _getSetValueFunc.getValue;
        pointer_c instancePtr = instance.toPointer().toManaged();
        pointer_c memberPtr = toPointer().toManaged();
        func(instancePtr, memberPtr, _type, value);
    }

    [[maybe_unused]] void ManagedMember::setValue(ManagedInstance instance, UnmanagedValue *value) const {
        SetValueFunc func = _getSetValueFunc.setValue;
        pointer_c instancePtr = instance.toPointer().toManaged();
        pointer_c memberPtr = toPointer().toManaged();
        func(instancePtr, memberPtr, _type, value);
    }

#pragma endregion
}

extern "C" {
    [[maybe_unused]] UNITY_EXPORT
    void SetManagedGetSetValueMethod(GetValueFunc getFunc, SetValueFunc setFunc) {
        _getSetValueFunc = GetSetValue(getFunc, setFunc);
    }
}

