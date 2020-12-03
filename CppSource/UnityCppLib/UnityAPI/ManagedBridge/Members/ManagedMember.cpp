#include "ManagedMember.h"
#include "UnityAPI/UnityAPIExtern.h"

#include <typeindex>
#include <map>

using namespace std;

namespace ManagedBridge {
    typedef void (UNITY_METHOD *GetValueFunc)(pointer_c instancePtr, pointer_c memberPtr, MemberType type, pointer_m *value);
    typedef void (UNITY_METHOD *SetValueFunc)(pointer_c instancePtr, pointer_c memberPtr, MemberType type, pointer_m value);

    struct GetSetValue {
    public:
        GetValueFunc getValue{};
        SetValueFunc setValue{};

        GetSetValue() = default;

        GetSetValue(GetValueFunc getValue, SetValueFunc setValue) {
            this->getValue = getValue;
            this->setValue = setValue;
        }
    };

    GetSetValue _stringFunc;
    GetSetValue _boolFunc;
    GetSetValue _intFunc;
    GetSetValue _uintFunc;
    GetSetValue _longFunc;
    GetSetValue _ulongFunc;
    GetSetValue _floatFunc;
    GetSetValue _doubleFunc;
    GetSetValue _pointerFunc;

#pragma region ManagedMember implementation

    ManagedMember::ManagedMember(ManagedPointer ptr, MemberType type) : Managed(ptr) {
        _type = type;
    }

    template string_m ManagedMember::get(ManagedInstance instance) const;
    template void ManagedMember::setValue(ManagedInstance instance, string_m value) const;

    template string_c ManagedMember::get(ManagedInstance instance) const;
    template void ManagedMember::setValue(ManagedInstance instance, string_c value) const;

    template bool ManagedMember::get(ManagedInstance instance) const;
    template void ManagedMember::setValue(ManagedInstance instance, bool value) const;

    template int ManagedMember::get(ManagedInstance instance) const;
    template void ManagedMember::setValue(ManagedInstance instance, int value) const;

    template uint ManagedMember::get(ManagedInstance instance) const;
    template void ManagedMember::setValue(ManagedInstance instance, uint value) const;

    template long ManagedMember::get(ManagedInstance instance) const;
    template void ManagedMember::setValue(ManagedInstance instance, long value) const;

    template ulong ManagedMember::get(ManagedInstance instance) const;
    template void ManagedMember::setValue(ManagedInstance instance, ulong value) const;

    template float ManagedMember::get(ManagedInstance instance) const;
    template void ManagedMember::setValue(ManagedInstance instance, float value) const;

    template double ManagedMember::get(ManagedInstance instance) const;
    template void ManagedMember::setValue(ManagedInstance instance, double value) const;

    template pointer_m ManagedMember::get(ManagedInstance instance) const;
    template void ManagedMember::setPointer(ManagedInstance instance, pointer_m value) const;

    template pointer_c ManagedMember::get(ManagedInstance instance) const;
    template void ManagedMember::setPointer(ManagedInstance instance, pointer_c value) const;

    template<typename TType>
    GetSetValue getTypedFunc() {
        type_index index = typeid(TType);
        if (index == typeid(string_c)) return _stringFunc;
        if (index == typeid(string_m)) return _stringFunc;
        if (index == typeid(bool)) return _boolFunc;
        if (index == typeid(int)) return _intFunc;
        if (index == typeid(uint)) return _uintFunc;
        if (index == typeid(long)) return _longFunc;
        if (index == typeid(ulong)) return _ulongFunc;
        if (index == typeid(float)) return _floatFunc;
        if (index == typeid(double)) return _doubleFunc;
        if (index == typeid(pointer_m)) return _pointerFunc;
        if (index == typeid(pointer_c)) return _pointerFunc;
        if (index == typeid(ManagedPointer)) return _pointerFunc;
        return GetSetValue();
    }

    template<typename TValue>
    [[maybe_unused]] TValue ManagedMember::get(ManagedInstance instance) const {
        GetValueFunc func = getTypedFunc<TValue>().getValue;
        pointer_c instancePtr = instance.toPointer().toManaged();
        pointer_c memberPtr = toPointer().toManaged();
        TValue value;
        func(instancePtr, memberPtr, _type, (pointer_m *)&value);
        return value;
    }

    template<typename TValue>
    [[maybe_unused]] void ManagedMember::setValue(ManagedInstance instance, TValue value) const {
        setPointer(instance, &value);
    }

    template<typename TValue>
    [[maybe_unused]] void ManagedMember::setPointer(ManagedInstance instance, TValue *value) const {
        SetValueFunc func = getTypedFunc<TValue *>().setValue;
        const void *instancePtr = instance.toPointer().toManaged();
        const void *memberPtr = this->toPointer().toManaged();
        func(instancePtr, memberPtr, _type, (pointer_m)value);
    }

#pragma endregion
}

extern "C" {
    [[maybe_unused]] UNITY_EXPORT
    void SetManagedGetSetStringMethod(GetValueFunc getFunc, SetValueFunc setFunc) {
        _stringFunc = GetSetValue(getFunc, setFunc);
    }

    [[maybe_unused]] UNITY_EXPORT
    void SetManagedGetSetBoolMethod(GetValueFunc getFunc, SetValueFunc setFunc) {
        _boolFunc = GetSetValue(getFunc, setFunc);
    }

    [[maybe_unused]] UNITY_EXPORT
    void SetManagedGetSetIntMethod(GetValueFunc getFunc, SetValueFunc setFunc) {
        _intFunc = GetSetValue(getFunc, setFunc);
    }

    [[maybe_unused]] UNITY_EXPORT
    void SetManagedGetSetUIntMethod(GetValueFunc getFunc, SetValueFunc setFunc) {
        _uintFunc = GetSetValue(getFunc, setFunc);
    }

    [[maybe_unused]] UNITY_EXPORT
    void SetManagedGetSetLongMethod(GetValueFunc getFunc, SetValueFunc setFunc) {
        _longFunc = GetSetValue(getFunc, setFunc);
    }

    [[maybe_unused]] UNITY_EXPORT
    void SetManagedGetSetULongMethod(GetValueFunc getFunc, SetValueFunc setFunc) {
        _ulongFunc = GetSetValue(getFunc, setFunc);
    }

    [[maybe_unused]] UNITY_EXPORT
    void SetManagedGetSetFloatMethod(GetValueFunc getFunc, SetValueFunc setFunc) {
        _floatFunc = GetSetValue(getFunc, setFunc);
    }

    [[maybe_unused]] UNITY_EXPORT
    void SetManagedGetSetDoubleMethod(GetValueFunc getFunc, SetValueFunc setFunc) {
        _doubleFunc = GetSetValue(getFunc, setFunc);
    }

    [[maybe_unused]] UNITY_EXPORT
    void SetManagedGetSetObjectMethod(GetValueFunc getFunc, SetValueFunc setFunc) {
        _pointerFunc = GetSetValue(getFunc, setFunc);
    }
}

