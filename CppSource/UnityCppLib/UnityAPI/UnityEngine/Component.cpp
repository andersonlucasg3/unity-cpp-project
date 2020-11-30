#include "Component.h"
#include "GameObject.h"
#include "UnityAPI/ManagedBridge/Managed.h"

using namespace UnityEngine::ManagedBridge;

namespace UnityEngine {
    Component::Component(const GameObject *gameObject, ManagedInstance instance) : Object(instance) {
        _tagProperty = instance.type().getProperty("tag");
        _gameObjectProperty = instance.type().getProperty("gameObject");
        _gameObject = gameObject;
    }

    Component::~Component() {
        Managed::destroy(_tagProperty);
        Managed::destroy(_gameObjectProperty);
    }

    Transform * Component::transform() const {
        return _gameObject->transform();
    }

    const GameObject *Component::gameObject() {
        if (_gameObject) return _gameObject;

        ManagedPointer pointer = _gameObjectProperty.get<ManagedPointer>(_instance);
        if (pointer != ManagedPointer::null) {
            _gameObject = new GameObject(pointer);
        }
        return _gameObject;
    }
}