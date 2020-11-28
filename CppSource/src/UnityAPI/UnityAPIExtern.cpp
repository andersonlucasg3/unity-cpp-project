#include "UnityAPIExtern.h"

__UnitySendMessageFunc UnitySendMessage = nullptr;
__UnityDebugLogFunc UnityDebugLog = nullptr;

extern "C" {
    UNITY_EXPORT void SetUnitySendMessageMethod(__UnitySendMessageFunc func) {
        UnitySendMessage = func;
    }

    UNITY_EXPORT void SetUnityDebugLogMethod(__UnityDebugLogFunc func) {
        UnityDebugLog = func;

        UnityEngine::Debug::Log("Unity Debug.Log function configured!");
    }
}

namespace UnityEngine {
    void Debug::Log(const char *message) {
        UnityDebugLog(message);
    }
}