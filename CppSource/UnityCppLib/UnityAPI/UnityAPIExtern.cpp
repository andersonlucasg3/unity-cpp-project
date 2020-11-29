#include <UnityAPI/UnityEngine/Debug.h>
#include "UnityAPIExtern.h"

#include "Components/Factory/ComponentFactory.h"
#include "UnityAPI/UnityEngine/GameObject.h"
#include "UnityAPI/UnityEngine/Transform.h"

using namespace CppSource::Components;
using namespace CppSource::Components::Factory;
using namespace UnityEngine;

extern "C" {
    REGISTER_DECLARE_ALL_COMPONENTS

    UNITY_EXPORT void InitializeNative() {
        REGISTER_ALL_COMPONENTS_CALL
    }

    UNITY_EXPORT void NativeInitialized() {
        GameObject *gameObject = new GameObject();
        gameObject->setName("Teste com transform");

        int count = gameObject->transform()->childCount();
        string str("Número de filhos do transform: ");
        str = str.append(to_string(count));
        Debug::Log(str);
    }
}