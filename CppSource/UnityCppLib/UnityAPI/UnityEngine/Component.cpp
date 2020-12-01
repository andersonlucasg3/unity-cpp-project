#include "Component.h"
#include "GameObject.h"
#include "UnityAPI/ManagedBridge/ManagedAssemblyInfo.h"

using namespace UnityEngine::ManagedBridge;

namespace UnityEngine {
    const ManagedAssemblyInfo _componentAssemblyInfo("UnityEngine.Component", "UnityEngine.dll");
    const ManagedType _componentType(_componentAssemblyInfo);

    const PropertyMember _gameObjectProperty = _componentType.getProperty("gameObject");
    const PropertyMember _tagProperty = _componentType.getProperty("tagProperty");

    Component::Component(ManagedType type) : Object(type) {
        _gameObject = new GameObject(_gameObjectProperty.get<ManagedPointer>(_instance));
    }

    Component::Component(ManagedInstance instance) : Object(instance) {
        _gameObject = new GameObject(_gameObjectProperty.get<ManagedPointer>(_instance));
    }

    Component::Component(ManagedInstance instance, const GameObject *gameObject) : Object(instance) {
        _gameObject = gameObject;
    }

    Component::~Component() {
        Managed::destroy(_tagProperty);
        Managed::destroy(_gameObjectProperty);
    }

    const Transform *Component::transform() const {
        return _gameObject->transform();
    }

    const GameObject *Component::gameObject() const {
        return _gameObject;
    }

    const ManagedType Component::type() {
        return _componentType;
    }
}