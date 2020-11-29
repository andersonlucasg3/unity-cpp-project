#include "Component.h"
#include "GameObject.h"
#include "UnityAPI/ManagedBridge/Managed.h"
#include "UnityAPI/ManagedBridge/ManagedMember.h"

using namespace UnityEngine::valuePointer;

namespace UnityEngine {
    Component::Component(const GameObject *gameObject, intptr_t *instance) : Object(instance) {
        _gameObject = gameObject;
        _tagProperty = nullptr;
    }

    Component::~Component() {
        Managed::destroy(_tagProperty);
    }

    void Component::InitializeMembers() {
        _tagProperty = _managed->getMember("tag", property);
    }

    Transform * Component::transform() const {
        return _gameObject->transform();
    }

    const GameObject *Component::gameObject() const {
        return _gameObject;
    }
}