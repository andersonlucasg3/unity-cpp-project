#include "Component.h"
#include "GameObject.h"
#include "UnityAPI/ManagedBridge/ManagedAssemblyInfo.h"

using namespace ManagedBridge;

namespace UnityEngine {
    const ManagedAssemblyInfo _componentAssemblyInfo("UnityCpp.NativeBridge.UnityBridges.ComponentBridge");

    ManagedType Component::_componentType = ManagedType::null;
    
    Component::Component(ManagedType type, const GameObject *gameObject) : Object(type) {
        _gameObject = gameObject;
        _transform = gameObject->transform();
    }

    Component::Component(ManagedInstance instance, const GameObject *gameObject) : Object(instance) {
        _gameObject = gameObject;
        _transform = gameObject->transform();
    }

    Component::~Component() = default;

    const Transform *Component::transform() const {
        return _transform;
    }

    const GameObject *Component::gameObject() const {
        return _gameObject;
    }

    const ManagedType Component::type() {
        return _componentType;
    }

    void Component::InitializeManagedBridge() {
        _componentType = ManagedType(_componentAssemblyInfo);
    }
}