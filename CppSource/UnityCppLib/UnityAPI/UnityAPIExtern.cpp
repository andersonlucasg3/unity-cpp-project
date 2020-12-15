#include <UnityAPI/UnityEngine/Debug.h>
#include "UnityAPIExtern.h"

#include "UnityAPI/UnityEngine/UnityEngine.h"
#include "Components/Factory/ComponentFactory.h"

using namespace CppSource::Components;
using namespace CppSource::Components::Factory;
using namespace UnityEngine;

extern "C" {
    REGISTER_DECLARE_ALL_COMPONENTS

    UNITY_EXPORT void InitializeNative() {
        REGISTER_ALL_COMPONENTS_CALL

        UnityEngine::InitializeManagedBridge();

        GameObject *obj = new GameObject();
        Transform *t;
        if (obj->tryGetComponent(&t)) {
            t->setName("Transform got");
        }
    }
}