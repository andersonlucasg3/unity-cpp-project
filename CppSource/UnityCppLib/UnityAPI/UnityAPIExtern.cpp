#include "UnityAPIExtern.h"

//#include "Game/TestComponent.h"
#include "Components/Factory/ComponentFactory.h"
#include "UnityAPI/UnityEngine/GameObject.h"


//using namespace CppSource::Game;
using namespace CppSource::Components;
using namespace CppSource::Components::Factory;
using namespace UnityEngine;

GameObject *_shared = nullptr;

extern "C" {
    REGISTER_DECLARE_ALL_COMPONENTS

    UNITY_EXPORT void InitializeNative() {
        REGISTER_ALL_COMPONENTS_CALL
    }

    UNITY_EXPORT void NativeInitialized() {
        _shared = new GameObject();
        _shared->setName("Meu game object");
    }
}