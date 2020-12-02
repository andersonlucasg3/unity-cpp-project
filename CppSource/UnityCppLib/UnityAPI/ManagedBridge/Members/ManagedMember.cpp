#include "ManagedMember.h"
#include "UnityAPI/UnityAPIExtern.h"

#include <typeindex>
#include <map>

using namespace std;

namespace ManagedBridge {
    typedef void (UNITY_METHOD *GetValueFunc)(const void *instancePtr, const void *memberPtr, MemberType type, void **value);
    typedef void (UNITY_METHOD *SetValueFunc)(const void *instancePtr, const void *memberPtr, MemberType type, void *value);

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
    GetSetValue _intFunc;
    GetSetValue _longFunc;
    GetSetValue _floatFunc;
    GetSetValue _doubleFunc;
    GetSetValue _pointerFunc;

#pragma region ManagedMember implementation

    ManagedMember::ManagedMember(ManagedPointer ptr, MemberType type) : Managed(ptr) {
        _type = type;
    }

    template char *ManagedMember::get(ManagedInstance instance) const;
    template void ManagedMember::setPointer(ManagedInstance instance, char *value)const ;
    template int ManagedMember::get(ManagedInstance instance) const;
    template void ManagedMember::setValue(ManagedInstance instance, int value) const;
    template long ManagedMember::get(ManagedInstance instance) const;
    template void ManagedMember::setValue(ManagedInstance instance, long value) const;
    template float ManagedMember::get(ManagedInstance instance) const;
    template void ManagedMember::setValue(ManagedInstance instance, float value) const;
    template double ManagedMember::get(ManagedInstance instance) const;
    template void ManagedMember::setValue(ManagedInstance instance, double value) const;
    template void *ManagedMember::get(ManagedInstance instance) const;
    template void ManagedMember::setPointer(ManagedInstance instance, void *value) const;

    template<typename TType>
    GetSetValue getTypedFunc() {
        type_index index = typeid(TType);
        if (index == typeid(char *)) return _stringFunc;
        if (index == typeid(int)) return _intFunc;
        if (index == typeid(long)) return _longFunc;
        if (index == typeid(float)) return _floatFunc;
        if (index == typeid(double)) return _doubleFunc;
        if (index == typeid(void *)) return _pointerFunc;
        if (index == typeid(ManagedPointer)) return _pointerFunc;
        return GetSetValue();
    }

    template<typename TValue>
    [[maybe_unused]] TValue ManagedMember::get(ManagedInstance instance) const {
        GetValueFunc func = getTypedFunc<TValue>().getValue;
        const void *instancePtr = instance.toPointer().toManaged();
        const void *memberPtr = this->toPointer().toManaged();
        TValue value;
        func(instancePtr, memberPtr, _type, (void **)&value);
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
        func(instancePtr, memberPtr, _type, value);
    }

#pragma endregion
}

extern "C" {
    [[maybe_unused]] UNITY_EXPORT
    void SetManagedGetSetStringMethod(GetValueFunc getFunc, SetValueFunc setFunc) {
        _stringFunc = GetSetValue(getFunc, setFunc);
    }

    [[maybe_unused]] UNITY_EXPORT
    void SetManagedGetSetIntMethod(GetValueFunc getFunc, SetValueFunc setFunc) {
        _intFunc = GetSetValue(getFunc, setFunc);
    }

    [[maybe_unused]] UNITY_EXPORT
    void SetManagedGetSetLongMethod(GetValueFunc getFunc, SetValueFunc setFunc) {
        _longFunc = GetSetValue(getFunc, setFunc);
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

