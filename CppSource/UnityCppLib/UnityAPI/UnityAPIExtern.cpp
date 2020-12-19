#include "UnityAPIExtern.h"
#include "UnityAPI/UnityEngine/UnityEngine.h"

#include "Game/ComponentsEntryPoint.h"

using namespace UnityEngine;

extern "C" {
    UNITY_EXPORT void InitializeNative() {
        UnityEngine::InitializeEngine();

        RegisterComponents();
    }

    UNITY_EXPORT void DeInitializeNative() {
        UnityEngine::DeInitializeEngine();
    }
}