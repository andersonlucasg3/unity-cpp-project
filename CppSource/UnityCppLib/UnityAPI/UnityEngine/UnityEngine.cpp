#include "UnityEngine.h"

#include "UnityAPI/NetFramework/System.h"

namespace UnityEngine {
    void InitializeManagedBridge() {
        System::InitializeManagedBridge();

        UnityEngine::Object::InitializeManagedBridge();
        UnityEngine::Component::InitializeManagedBridge();
        UnityEngine::Transform::InitializeManagedBridge();
        UnityEngine::GameObject::InitializeManagedBridge();
    }
}