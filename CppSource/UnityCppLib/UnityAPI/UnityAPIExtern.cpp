#include "UnityAPIExtern.h"

using namespace CppSource::Game;
using namespace CppSource::Components;
using namespace CppSource::Components::Factory;
using namespace UnityEngine;

__UnitySendMessageFunc UnitySendMessage = nullptr;

extern "C" {
    UNITY_EXPORT void SetUnitySendMessageMethod(__UnitySendMessageFunc func) {
        UnitySendMessage = func;
    }

    REGISTER_DECLARE_ALL_COMPONENTS

    UNITY_EXPORT void InitializeNative() {
        REGISTER_ALL_COMPONENTS_CALL
    }
}