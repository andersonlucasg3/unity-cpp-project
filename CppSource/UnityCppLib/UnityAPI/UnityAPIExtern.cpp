#include "UnityAPIExtern.h"

#include "Components/Factory/ComponentFactory.h"

using namespace CppSource::Components;
using namespace CppSource::Components::Factory;

extern "C" {
    REGISTER_DECLARE_ALL_COMPONENTS

    UNITY_EXPORT void InitializeNative() {
        REGISTER_ALL_COMPONENTS_CALL
    }

    UNITY_EXPORT void NativeInitialized() {
        // TODO: if anything should be started
        // TODO: now would be the moment
    }
}