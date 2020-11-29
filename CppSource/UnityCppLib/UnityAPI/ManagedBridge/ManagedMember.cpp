#include "ManagedMember.h"
#include "Managed.h"
#include "UnityAPI/UnityAPIExtern.h"

using namespace UnityEngine::ManagedBridge;

typedef void *(UNITY_METHOD *__ManagedGetValueFunc)(intptr_t *instancePtr, intptr_t *memberPtr, MemberType type);
typedef void (UNITY_METHOD *__ManagedSetValueFunc)(intptr_t *instancePtr, intptr_t *memberPtr, MemberType type, void *value);

struct GetSetValue {
public:
    __ManagedGetValueFunc getValue;
    __ManagedSetValueFunc setValue;

    GetSetValue(__ManagedGetValueFunc getValue, __ManagedSetValueFunc setValue) {
        this->getValue = getValue;
        this->setValue = setValue;
    }
};

GetSetValue *getSetString = nullptr;
GetSetValue *getSetInt = nullptr;
GetSetValue *getSetLong = nullptr;
GetSetValue *getSetFloat = nullptr;
GetSetValue *getSetDouble = nullptr;

namespace UnityEngine::ManagedBridge {
    ManagedMember::ManagedMember(intptr_t *memberPtr, intptr_t *managedPtr, MemberType type) {
        _memberPtr = memberPtr;
        _managedPtr = managedPtr;
        _type = type;
    }

    ManagedMember::~ManagedMember() = default;

    template<typename TValue> TValue *ManagedMember::callGet(void *func) const {
        auto getValue = (__ManagedGetValueFunc)func;
        return static_cast<TValue *>(getValue(_managedPtr, _memberPtr, _type));
    }

    template<typename TValue> void ManagedMember::callSet(void *func, TValue *value) const {
        auto setValue = (__ManagedSetValueFunc)func;
        setValue(_managedPtr, _memberPtr, _type, (void *)value);
    }

    [[maybe_unused]] const char * ManagedMember::getValueString() const {
        auto value = callGet<const char *>((void *) getSetString->getValue);
        return reinterpret_cast<const char *>(value);
    }

    [[maybe_unused]] void ManagedMember::setValueString(const char *value) const {
        callSet((void *)getSetString->setValue, value);
    }

    [[maybe_unused]] int ManagedMember::getValueInt() const {
        auto value = callGet<int>((void *)getSetInt->getValue);
        return *value;
    }

    [[maybe_unused]] void ManagedMember::setValueInt(int value) const {
        callSet((void *)getSetInt->setValue, &value);
    }

    [[maybe_unused]] long ManagedMember::getValueLong() const {
        auto value = callGet<long>((void *)getSetLong->getValue);
        return *value;
    }

    [[maybe_unused]] void ManagedMember::setValueLong(long value) const {
        callSet((void *)getSetLong->setValue, &value);
    }

    [[maybe_unused]] float ManagedMember::getValueFloat() const {
        auto value = callGet<float>((void*)getSetFloat->getValue);
        return *value;
    }

    [[maybe_unused]] void ManagedMember::setValueFloat(float value) const {
        callSet((void *)getSetFloat->setValue, &value);
    }

    [[maybe_unused]] double ManagedMember::getValueDouble() const {
        auto value = callGet<double>((void *)getSetDouble->getValue);
        return *value;
    }

    [[maybe_unused]] void ManagedMember::setValueDouble(double value) const {
        callSet((void *)getSetDouble->setValue, &value);
    }
}

extern "C" {
    [[maybe_unused]] UNITY_EXPORT void SetManagedGetSetStringMethod(__ManagedGetValueFunc getFunc, __ManagedSetValueFunc setFunc) {
        getSetString = new GetSetValue(getFunc, setFunc);
    }

    [[maybe_unused]] UNITY_EXPORT void SetManagedGetSetIntMethod(__ManagedGetValueFunc getFunc, __ManagedSetValueFunc setFunc) {
        getSetInt = new GetSetValue(getFunc, setFunc);
    }

    [[maybe_unused]] UNITY_EXPORT void SetManagedGetSetLongMethod(__ManagedGetValueFunc getFunc, __ManagedSetValueFunc setFunc) {
        getSetLong = new GetSetValue(getFunc, setFunc);
    }

    [[maybe_unused]] UNITY_EXPORT void SetManagedGetSetFloatMethod(__ManagedGetValueFunc getFunc, __ManagedSetValueFunc setFunc) {
        getSetFloat = new GetSetValue(getFunc, setFunc);
    }

    [[maybe_unused]] UNITY_EXPORT void SetManagedGetSetDoubleMethod(__ManagedGetValueFunc getFunc, __ManagedSetValueFunc setFunc) {
        getSetDouble = new GetSetValue(getFunc, setFunc);
    }
}