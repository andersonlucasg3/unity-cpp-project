#include "NativeComponent.h"
#include "Factory/ComponentFactory.h"
#include "UnityAPI/UnityAPIExtern.h"
#include "UnityAPI/UnityEngine/GameObject.h"

using namespace std;
using namespace CppSource::Components;
using namespace CppSource::Components::Factory;
using namespace UnityEngine;

namespace  CppSource::Components {
    NativeComponent::NativeComponent() {
        _gameObject = new GameObject();
    }

    GameObject *NativeComponent::gameObject() {
        return _gameObject;
    }
}

extern "C" {
    UNITY_EXPORT NativeComponent *CreateNativeInstance(const char *className) {
        return ComponentFactory::Instance()->InstantiateHandle(className);
    }

    UNITY_EXPORT void InvokeNativeAwake(NativeComponent *handle) {
        handle->awake();
    }

    UNITY_EXPORT void InvokeNativeStart(NativeComponent *handle) {
        handle->start();
    }

    UNITY_EXPORT void InvokeNativeUpdate(NativeComponent *handle) {
        handle->update();
    }

    UNITY_EXPORT void InvokeNativeLateUpdate(NativeComponent *handle) {
        handle->lateUpdate();
    }
}