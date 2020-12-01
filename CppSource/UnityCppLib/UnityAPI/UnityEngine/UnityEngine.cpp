#include "UnityEngine.h"

namespace UnityEngine {
    void InitializeManagedBridge() {
        UnityEngine::Object::InitializeManagedBridge();
        UnityEngine::Component::InitializeManagedBridge();
        UnityEngine::Transform::InitializeManagedBridge();
        UnityEngine::GameObject::InitializeManagedBridge();
    }
}