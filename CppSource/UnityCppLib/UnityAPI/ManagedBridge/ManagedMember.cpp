#include <malloc.h>
#include "ManagedMember.h"
#include "Managed.h"
#include "UnityAPI/UnityAPIExtern.h"

using namespace UnityEngine::valuePointer;

typedef void (UNITY_METHOD *GetValueFunc)(intptr_t *instancePtr, intptr_t *memberPtr, MemberType type, void **value);
typedef void (UNITY_METHOD *SetValueFunc)(intptr_t *instancePtr, intptr_t *memberPtr, MemberType type, void *value);

struct GetSetValue {
public:
    GetValueFunc getValue;
    SetValueFunc setValue;

    GetSetValue(GetValueFunc getValue, SetValueFunc setValue) {
        this->getValue = getValue;
        this->setValue = setValue;
    }
};

GetSetValue *getSetString = nullptr;
GetSetValue *getSetInt = nullptr;
GetSetValue *getSetLong = nullptr;
GetSetValue *getSetFloat = nullptr;
GetSetValue *getSetDouble = nullptr;
GetSetValue *getSetObject = nullptr;

namespace UnityEngine::valuePointer {
    ManagedMember::ManagedMember(intptr_t *memberPtr, intptr_t *managedPtr, MemberType type) {
        _memberPtr = memberPtr;
        _managedPtr = managedPtr;
        _type = type;
    }

    ManagedMember::~ManagedMember() = default;

    template<typename TValue> void ManagedMember::callGet(void *func, TValue *valuePointer) const {
        auto getValue = (GetValueFunc)func;
        getValue(_managedPtr, _memberPtr, _type, (void **)&valuePointer);
    }

    template<typename TValue> void ManagedMember::callSet(void *func, TValue *value) const {
        auto setValue = (SetValueFunc)func;
        setValue(_managedPtr, _memberPtr, _type, (void *)value);
    }

    const char * ManagedMember::getString() const {
        const char *value;
        callGet<const char *>((void *) getSetString->getValue, &value);
        return value;
    }

    void ManagedMember::setString(const char *value) const {
        callSet<const char>((void *)getSetString->setValue, value);
    }

    int ManagedMember::getInt() const {
        int value;
        callGet<int>((void *)getSetInt->getValue, &value);
        return value;
    }

    void ManagedMember::setInt(int value) const {
        callSet((void *)getSetInt->setValue, &value);
    }

    long ManagedMember::getLong() const {
        long value;
        callGet<long>((void *)getSetLong->getValue, &value);
        return value;
    }

    void ManagedMember::setLong(long value) const {
        callSet((void *)getSetLong->setValue, &value);
    }

    float ManagedMember::getFloat() const {
        float value;
        callGet<float>((void*)getSetFloat->getValue, &value);
        return value;
    }

    void ManagedMember::setFloat(float value) const {
        callSet((void *)getSetFloat->setValue, &value);
    }

    double ManagedMember::getDouble() const {
        double value;
        callGet<double>((void *)getSetDouble->getValue, &value);
        return value;
    }

    void ManagedMember::setDouble(double value) const {
        callSet((void *)getSetDouble->setValue, &value);
    }

    intptr_t *ManagedMember::getObject() const {
        intptr_t *ptr = nullptr;
        callGet<intptr_t *>((void *)getSetObject->getValue, &ptr);
        return (intptr_t *)ptr;
    }

    void ManagedMember::setObject(intptr_t *value) const {
        callSet((void *)getSetObject->setValue, (void *)value);
    }
}

extern "C" {
    [[maybe_unused]] UNITY_EXPORT
    void SetManagedGetSetStringMethod(GetValueFunc getFunc, SetValueFunc setFunc) {
        getSetString = new GetSetValue(getFunc, setFunc);
    }

    [[maybe_unused]] UNITY_EXPORT
    void SetManagedGetSetIntMethod(GetValueFunc getFunc, SetValueFunc setFunc) {
        getSetInt = new GetSetValue(getFunc, setFunc);
    }

    [[maybe_unused]] UNITY_EXPORT
    void SetManagedGetSetLongMethod(GetValueFunc getFunc, SetValueFunc setFunc) {
        getSetLong = new GetSetValue(getFunc, setFunc);
    }

    [[maybe_unused]] UNITY_EXPORT
    void SetManagedGetSetFloatMethod(GetValueFunc getFunc, SetValueFunc setFunc) {
        getSetFloat = new GetSetValue(getFunc, setFunc);
    }

    [[maybe_unused]] UNITY_EXPORT
    void SetManagedGetSetDoubleMethod(GetValueFunc getFunc, SetValueFunc setFunc) {
        getSetDouble = new GetSetValue(getFunc, setFunc);
    }

    [[maybe_unused]] UNITY_EXPORT
    void SetManagedGetSetObjectMethod(GetValueFunc getFunc, SetValueFunc setFunc) {
        getSetObject = new GetSetValue(getFunc, setFunc);
    }
}