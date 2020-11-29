#include "Transform.h"
#include "GameObject.h"
#include "UnityAPI/ManagedBridge/Managed.h"
#include "UnityAPI/ManagedBridge/ManagedMember.h"

namespace UnityEngine {
    Transform::Transform(intptr_t *instance) : Component(instance) {
        InitializeMembers();
    }

    Transform::Transform(const GameObject *gameObject, intptr_t *instance) : Component(gameObject, instance) {
        InitializeMembers();
    }

    Transform::~Transform() {
        Managed::destroy(_childCountProperty);
        Managed::destroy(_parentProperty);
    }

    void Transform::InitializeMembers() {
        Component::InitializeMembers();
        _childCountProperty = _managed->getMember("childCount", property);
        _parentProperty = _managed->getMember("parent", property);

        intptr_t *parentPtr = _parentProperty->getObject();
        if (parentPtr) {
            _parent = new Transform(parentPtr);
        }
    }

    int Transform::childCount() const {
        return _childCountProperty->getInt();
    }

    Transform * Transform::parent() {
        if (_parent != nullptr) {
            delete _parent;
            _parent = nullptr;
        }
        intptr_t *parentPtr = _parentProperty->getObject();
        if (parentPtr) {
            _parent = new Transform(parentPtr);
        }
        return _parent;
    }

    void Transform::setParent(Transform *parent) {
        _parentProperty->setObject(parent->_managed);
        _parent = parent;
    }
}