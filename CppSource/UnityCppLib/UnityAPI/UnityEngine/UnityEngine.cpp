#include "UnityEngine.h"

#include "UnityAPI/NetFramework/System.h"

namespace UnityEngine {
    void InitializeManagedBridge() {
        System::InitializeManagedBridge();

        UnityEngine::Object::InitializeManagedBridge();
        UnityEngine::Component::InitializeManagedBridge();

        UnityEngine::Behaviour::InitializeManagedBridge();
        UnityEngine::MonoBehaviour::InitializeManagedBridge();

        UnityEngine::Transform::InitializeManagedBridge();
        UnityEngine::GameObject::InitializeManagedBridge();
    }
}