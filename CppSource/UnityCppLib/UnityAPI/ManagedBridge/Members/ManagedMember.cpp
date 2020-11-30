#include "ManagedMember.h"
#include "UnityAPI/ManagedBridge/ManagedInstance.h"
#include "UnityAPI/UnityAPIExtern.h"

#include <typeindex>
#include <map>

using namespace std;
using namespace UnityEngine::ManagedBridge;

namespace UnityEngine::ManagedBridge {
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

    map<type_index, GetSetValue> _getSetMap;

#pragma region ManagedMember implementation

    ManagedMember::ManagedMember(ManagedPointer ptr, MemberType type) : Managed(ptr) {
        _type = type;
    }

    template<typename TValue>
    [[maybe_unused]] TValue ManagedMember::pull(ManagedInstance instance) const {
        TValue value;
        GetValueFunc func = _getSetMap[typeid(TValue)].getValue;
        ManagedPointer instancePtr = instance;
        func(instancePtr, this, _type, (void **)&value);
        return value;
    }

    template<typename TValue>
    [[maybe_unused]] void ManagedMember::push(ManagedInstance instance, TValue value) const {
        SetValueFunc func = _getSetMap[typeid(TValue)].setValue;
        ManagedPointer instancePtr = instance;
        func(instancePtr, this, _type, &value);
    }

    template const char *ManagedMember::pull(ManagedInstance instance) const;
    template void ManagedMember::push(ManagedInstance instance, const char *)const ;
    template int ManagedMember::pull(ManagedInstance instance) const;
    template void ManagedMember::push(ManagedInstance instance, int value) const;
    template long ManagedMember::pull(ManagedInstance instance) const;
    template void ManagedMember::push(ManagedInstance instance, long value) const;
    template float ManagedMember::pull(ManagedInstance instance) const;
    template void ManagedMember::push(ManagedInstance instance, float value) const;
    template double ManagedMember::pull(ManagedInstance instance) const;
    template void ManagedMember::push(ManagedInstance instance, double value) const;
    template void *ManagedMember::pull(ManagedInstance instance) const;
    template void ManagedMember::push(ManagedInstance instance, void *value) const;

#pragma endregion
}

template<typename TValue>
void setGetSetMethod(GetValueFunc getFunc, SetValueFunc setFunc) {
    _getSetMap[typeid(TValue)] = GetSetValue(getFunc, setFunc);
}

extern "C" {
    [[maybe_unused]] UNITY_EXPORT
    void SetManagedGetSetStringMethod(GetValueFunc getFunc, SetValueFunc setFunc) {
        setGetSetMethod<const char *>(getFunc, setFunc);
    }

    [[maybe_unused]] UNITY_EXPORT
    void SetManagedGetSetIntMethod(GetValueFunc getFunc, SetValueFunc setFunc) {
        setGetSetMethod<int>(getFunc, setFunc);
    }

    [[maybe_unused]] UNITY_EXPORT
    void SetManagedGetSetLongMethod(GetValueFunc getFunc, SetValueFunc setFunc) {
        setGetSetMethod<long>(getFunc, setFunc);
    }

    [[maybe_unused]] UNITY_EXPORT
    void SetManagedGetSetFloatMethod(GetValueFunc getFunc, SetValueFunc setFunc) {
        setGetSetMethod<float>(getFunc, setFunc);
    }

    [[maybe_unused]] UNITY_EXPORT
    void SetManagedGetSetDoubleMethod(GetValueFunc getFunc, SetValueFunc setFunc) {
        setGetSetMethod<double>(getFunc, setFunc);
    }

    [[maybe_unused]] UNITY_EXPORT
    void SetManagedGetSetObjectMethod(GetValueFunc getFunc, SetValueFunc setFunc) {
        setGetSetMethod<void *>(getFunc, setFunc);
    }
}

