#include "UnityAPIExtern.h"

#include "Game/TestComponent.h"
#include "Components/Factory/ComponentFactory.h"
#include "UnityAPI/UnityEngine/GameObject.h"


using namespace CppSource::Game;
using namespace CppSource::Components;
using namespace CppSource::Components::Factory;
using namespace UnityEngine;

extern "C" {
    REGISTER_DECLARE_ALL_COMPONENTS

    UNITY_EXPORT void InitializeNative() {
        REGISTER_ALL_COMPONENTS_CALL

        new GameObject("Meu GO Test");
    }
}