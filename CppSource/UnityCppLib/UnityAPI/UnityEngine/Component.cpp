#include "Component.h"
#include "GameObject.h"
#include "UnityAPI/ManagedBridge/Managed.h"
#include "UnityAPI/ManagedBridge/ManagedMember.h"

using namespace UnityEngine::ManagedBridge;

namespace UnityEngine {
    Component::Component(intptr_t *instance) : Object(instance) { }

    Component::Component(const GameObject *gameObject, intptr_t *instance) : Object(instance) {
        _gameObject = gameObject;
    }

    Component::~Component() {
        Managed::destroy(_tagProperty);
    }

    void Component::InitializeMembers() {
        Object::InitializeMembers();
        _tagProperty = _managed->getMember("tag", property);
        _gameObjectProperty = _managed->getMember("gameObject", property);

        if (!_gameObject) {
            intptr_t *gameObjectPtr = _gameObjectProperty->getObject();
            _gameObject = new GameObject(gameObjectPtr);
        }
    }

    Transform * Component::transform() const {
        return _gameObject->transform();
    }

    const GameObject *Component::gameObject() const {
        return _gameObject;
    }
}