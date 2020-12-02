#include "Component.h"
#include "GameObject.h"
#include "UnityAPI/ManagedBridge/ManagedAssemblyInfo.h"

using namespace ManagedBridge;

namespace UnityEngine {
    const ManagedAssemblyInfo _componentAssemblyInfo("UnityEngine.Component", "UnityEngine.dll");

    ManagedType _componentType = ManagedType::null;

    PropertyMember _gameObjectProperty = PropertyMember::null;
    PropertyMember _gameObjectTransformProperty = PropertyMember::null;

    Component::Component(ManagedType type) : Object(type) {
        _gameObject = new GameObject(_gameObjectProperty.get<ManagedPointer>(_instance));
    }

    Component::Component(ManagedInstance instance) : Object(instance) {
        _gameObject = new GameObject(_gameObjectProperty.get<ManagedPointer>(_instance));
    }

    Component::Component(ManagedInstance instance, const GameObject *gameObject) : Object(instance) {
        _gameObject = gameObject;
    }

    Component::~Component() = default;

    const Transform *Component::transform() const {
        return _gameObject->transform();
    }

    const GameObject *Component::gameObject() const {
        return _gameObject;
    }

    const ManagedType Component::type() {
        return _componentType;
    }

    void Component::InitializeManagedBridge() {
        _componentType = ManagedType(_componentAssemblyInfo);

        _gameObjectProperty = _componentType.getProperty("gameObject");
        _gameObjectTransformProperty = _componentType.getProperty("transform");
    }
}