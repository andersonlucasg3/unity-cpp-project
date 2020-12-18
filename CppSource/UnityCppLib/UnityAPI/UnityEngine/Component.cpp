#include "Component.h"
#include "GameObject.h"
#include "UnityAPI/ManagedBridge/ManagedAssemblyInfo.h"
#include "UnityAPI/Helpers/Helpers.h"

using namespace ManagedBridge;
using namespace Helpers;

namespace UnityEngine {
    const ManagedAssemblyInfo _componentBridgeAssemblyInfo("UnityCpp.NativeBridge.UnityBridges.ComponentBridge");
    const ManagedAssemblyInfo _componentAssemblyInfo("UnityEngine.Component", "UnityEngine.dll");

    ManagedType Component::_componentBridgeType = ManagedType::null;
    ManagedType Component::_componentType = ManagedType::null;

    PropertyMember Component::_transformProperty = PropertyMember::null;
    PropertyMember Component::_gameObjectProperty = PropertyMember::null;
    PropertyMember Component::_tagProperty = PropertyMember::null;

    Component::Component(ManagedInstance instance, const GameObject *gameObject) : Object(instance) {
        if (gameObject == nullptr) {
            UnmanagedValue value(::pointerType);
            _gameObjectProperty.get(instance, &value);
            _gameObject = new GameObject(ManagedInstance(ManagedPointer(value)));
        } else {
            _gameObject = gameObject;
        }
        _transform = _gameObject->transform();
    }

    Component::~Component() = default;

    const Transform *Component::transform() const {
        return _transform;
    }

    const GameObject *Component::gameObject() const {
        return _gameObject;
    }

    string_c Component::tag() const {
        UnmanagedValue value(UnmanagedType::stringType);
        _tagProperty.get(_instance, &value);
        return value;
    }

    void Component::setTag(string_c tag) const {
        UnmanagedValue value(tag);
        _tagProperty.setValue(_instance, &value);
    }

    ManagedType Component::type() {
        return _componentBridgeType;
    }

    ManagedType Component::unityType() {
        return _componentType;
    }

    void Component::InitializeManagedBridge() {
        _componentBridgeType = ManagedType(_componentBridgeAssemblyInfo);
        _componentType = ManagedType(_componentAssemblyInfo);

        _transformProperty = _componentBridgeType.getProperty("transform");
        _gameObjectProperty = _componentBridgeType.getProperty("gameObject");
        _tagProperty = _componentBridgeType.getProperty("tag");
    }
}