#include "Transform.h"
#include "GameObject.h"
#include "UnityAPI/ManagedBridge/Managed.h"
#include "UnityAPI/ManagedBridge/ManagedMember.h"

namespace UnityEngine {
    Transform::Transform(const GameObject *gameObject, intptr_t *instance) : Component(gameObject, instance) {
        _childCountProperty = nullptr;
        InitializeMembers();
    }

    Transform::~Transform() {
        Managed::destroy(_childCountProperty);
    }

    void Transform::InitializeMembers() {
        _childCountProperty = _managed->getMember("childCount", property);
    }

    int Transform::childCount() const {
        return _childCountProperty->getInt();
    }
}