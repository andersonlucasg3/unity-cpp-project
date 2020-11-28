#pragma once

#include "../../UnityCppTestApp/UnityInitialization.h"
#include "../Game/ComponentsRegistration.h"
#include "../Components/Factory/ComponentFactory.h"
#include "UnityAPIExtern.h"
#include "UnityAPI/UnityEngine/GameObject.h"

#ifndef UNITY_EXPORT
#define UNITY_EXPORT __declspec(dllexport)
#endif

#ifndef UNITY_IMPORT
#define UNITY_IMPORT __declspec(dllimport)
#endif

typedef void (__cdecl *__UnitySendMessageFunc)(const char *gameObjectName, const char *methodName, const char *message);

extern "C" {
    UNITY_EXPORT void SetUnitySendMessageMethod(__UnitySendMessageFunc func);
}