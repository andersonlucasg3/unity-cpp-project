#include "Managed.h"
#include "UnityAPI/UnityAPIExtern.h"

typedef void (UNITY_METHOD *__UnitySendMessageFunc)(const char *gameObjectName, const char *methodName, const char *message);
typedef intptr_t *(UNITY_METHOD *__UnityManagedNewCallFunc)(const char *typeName);
typedef void (UNITY_METHOD *__UnityManagedDestroyCallFunc)(intptr_t *instance);
typedef void (UNITY_METHOD *__UnityManagedSetValueFunc)(intptr_t *managedPointer, const char *propertyName, void *value);

__UnityManagedNewCallFunc UnityManagedNewCall = nullptr;
__UnityManagedDestroyCallFunc UnityManagedDestroyCall = nullptr;
__UnityManagedSetValueFunc UnityManagedSetValue = nullptr;

namespace UnityEngine {
    UnitySendMessageMethod Managed::UnitySendMessage = nullptr;

    Managed::~Managed() {
        UnityManagedDestroyCall(_instance);
    }

    void Managed::newInstance(const char *typeName) {
        _instance = UnityManagedNewCall(typeName);
    }

    void Managed::setValue(const char *propertyName, void *value) {
        UnityManagedSetValue(_instance, propertyName, value);
    }
}

extern "C" {
UNITY_EXPORT void SetUnitySendMessageMethod(__UnitySendMessageFunc func) {UnityEngine::Managed::UnitySendMessage = func;}
UNITY_EXPORT void SetManagedNewCallMethod(__UnityManagedNewCallFunc func) {UnityManagedNewCall = func;}
UNITY_EXPORT void SetManagedDestroyCallMethod(__UnityManagedDestroyCallFunc func) {UnityManagedDestroyCall = func;}
UNITY_EXPORT void SetManagedSetValueMethod(__UnityManagedSetValueFunc func) {UnityManagedSetValue = func;}
}