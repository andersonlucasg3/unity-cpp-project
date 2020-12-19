#include "UnityEngine.h"

#include "UnityAPI/NetFramework/System.h"
#include "UnityAPI/CppEngine/Trash.h"

using namespace CppEngine;

namespace UnityEngine {
    void InitializeEngine() {
        System::InitializeManagedBridge();

        UnityEngine::Object::InitializeManagedBridge();
        UnityEngine::Component::InitializeManagedBridge();

        UnityEngine::Behaviour::InitializeManagedBridge();
        UnityEngine::MonoBehaviour::InitializeManagedBridge();

        UnityEngine::Transform::InitializeManagedBridge();
        UnityEngine::GameObject::InitializeManagedBridge();

        Trash::setup();
    }

    void DeInitializeEngine() {
        Trash::empty();
    }
}