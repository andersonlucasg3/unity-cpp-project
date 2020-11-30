#include "Transform.h"
#include "GameObject.h"
#include "UnityAPI/ManagedBridge/Managed.h"
#include "UnityAPI/ManagedBridge/ManagedInstance.h"
#include "UnityAPI/ManagedBridge/Members/ManagedMember.h"

namespace UnityEngine {
    Transform::Transform(const GameObject *gameObject, ManagedInstance instance) : Component(gameObject, instance) {
        _childCountProperty = instance.type().getProperty("childCount");
        _parentProperty = instance.type().getProperty("parent");

        ManagedPointer parentPtr = _parentProperty.get<ManagedPointer>(instance);
        if (parentPtr) {
            _parent = new Transform(nullptr, ManagedInstance(instance.type(), parentPtr));
        }
    }

    Transform::~Transform() {
        Managed::destroy(_childCountProperty);
        Managed::destroy(_parentProperty);
    }

    int Transform::childCount() const {
        return _childCountProperty.get<int>(_instance);
    }

    Transform * Transform::parent() {
        ManagedPointer pointer = _parentProperty.get<ManagedPointer>(_instance);
        if (_parent != nullptr) {
            ManagedPointer currentPointer = _parent->_instance;
            if (currentPointer != pointer) {
                delete _parent;
                _parent = new Transform(nullptr, ManagedInstance(_instance.type(), pointer));
            } else {
                Managed::destroy(pointer);
            }
        }
        return _parent;
    }

    void Transform::setParent(Transform *parent) {
        _parentProperty.set(_instance, (ManagedPointer)parent->_instance);
        _parent = parent;
    }
}