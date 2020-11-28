#include "NativeComponent.h"
#include "Factory/ComponentFactory.h"
#include "../UnityAPI/UnityAPIExtern.h"

using namespace std;
using namespace CppSource::Components;
using namespace CppSource::Components::Factory;
using namespace UnityEngine;

namespace  CppSource::Components {
    NativeComponent::NativeComponent() = default;

    NativeComponent::~NativeComponent() {
        delete[] _gameObjectName;
    }

    void NativeComponent::SetGameObjectName(const char *gameObjectName) {
        _gameObjectName = gameObjectName;
    }
}

extern "C" {
    UNITY_EXPORT NativeComponent *CreateNativeInstance(const char *className, const char *gameObjectName) {
        Debug::Log("Creating the component!");
        NativeComponent *component = ComponentFactory::Instance().InstantiateHandle(className);
        Debug::Log("Component created");
        component->SetGameObjectName(gameObjectName);
        Debug::Log("Set game object name");
        return component;
    }

    UNITY_EXPORT void InvokeNativeAwake(NativeComponent *handle) {
        handle->Awake();
    }

    UNITY_EXPORT void InvokeNativeStart(NativeComponent *handle) {
        handle->Start();
    }

    UNITY_EXPORT void InvokeNativeUpdate(NativeComponent *handle) {
        handle->Update();
    }

    UNITY_EXPORT void InvokeNativeLateUpdate(NativeComponent *handle) {
        handle->LateUpdate();
    }
}