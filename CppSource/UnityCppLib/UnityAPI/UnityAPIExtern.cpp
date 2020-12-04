#include <UnityAPI/UnityEngine/Debug.h>
#include "UnityAPIExtern.h"

#include "UnityAPI/UnityEngine/UnityEngine.h"
#include "Components/Factory/ComponentFactory.h"

using namespace CppSource::Components;
using namespace CppSource::Components::Factory;\
using namespace UnityEngine;

extern "C" {
    REGISTER_DECLARE_ALL_COMPONENTS

    UNITY_EXPORT void InitializeNative() {
        REGISTER_ALL_COMPONENTS_CALL

        UnityEngine::InitializeManagedBridge();

        GameObject *gameObject = new GameObject("Transform test");

        GameObject *otherGameObject = new GameObject();
        gameObject->setName("Transform test child");

        otherGameObject->transform()->setParent(gameObject->transform());

        int count = gameObject->transform()->childCount();
        string str("Número de filhos do transform: ");
        str = str.append(to_string(count));
        Debug::Log(str);
    }
}