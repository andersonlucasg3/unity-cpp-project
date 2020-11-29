#include <UnityAPI/UnityAPIExtern.h>
#include "Debug.h"

typedef void (__cdecl *__UnityDebugLogFunc)(const char *message);

__UnityDebugLogFunc UnityDebugLog = nullptr;

extern "C" {
    UNITY_EXPORT void SetUnityDebugLogMethod(__UnityDebugLogFunc func) {
        UnityDebugLog = func;
    }
}

namespace UnityEngine {
    void Debug::Log(const char *message) {
        UnityDebugLog(message);
    }

    void Debug::Log(const string& message) {
        UnityDebugLog(message.c_str());
    }
}