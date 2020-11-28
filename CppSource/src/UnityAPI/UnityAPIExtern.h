#pragma once

#ifndef UNITY_EXPORT
#define UNITY_EXPORT __declspec(dllexport)
#endif

#ifndef UNITY_IMPORT
#define UNITY_IMPORT __declspec(dllimport)
#endif

typedef void (__cdecl *__UnitySendMessageFunc)(const char *gameObjectName, const char *methodName, const char *message);
typedef void (__cdecl *__UnityDebugLogFunc)(const char *message);

extern "C" {
    UNITY_EXPORT void SetUnitySendMessageMethod(__UnitySendMessageFunc func);
    UNITY_EXPORT void SetUnityDebugLogMethod(__UnityDebugLogFunc func);
}

namespace UnityEngine {
    class Debug {
    public:
        static void Log(const char *message);
    };
}