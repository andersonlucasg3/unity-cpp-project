#include "Behaviour.h"
#include "Component.h"

namespace UnityEngine {
    const ManagedAssemblyInfo _behaviourBridgeAssembly("UnityCpp.NativeBridge.UnityBridges.BehaviourBridge");
    const ManagedAssemblyInfo _behaviourAssembly("UnityEngine.Behaviour", "UnityEngine.dll");

    ManagedType Behaviour::_behaviourBridgeType = ManagedType::null;
    ManagedType Behaviour::_behaviourType = ManagedType::null;

    PropertyMember Behaviour::_enabledProperty = PropertyMember::null;
    PropertyMember Behaviour::_isActiveAndEnabledProperty = PropertyMember::null;

    Behaviour::Behaviour(ManagedInstance instance, const GameObject *gameObject) : Component(instance, gameObject) {
        //
    }

    Behaviour::~Behaviour() = default;

    bool Behaviour::enabled() const {
        UnmanagedValue value(UnmanagedType::boolType);
        _enabledProperty.get(_instance, &value);
        return value;
    }

    bool Behaviour::isActiveAndEnabled() const {
        UnmanagedValue value(UnmanagedType::boolType);
        _isActiveAndEnabledProperty.get(_instance, &value);
        return value;
    }

    ManagedType Behaviour::type() {
        return _behaviourBridgeType;
    }

    ManagedType Behaviour::unityType() {
        return _behaviourType;
    }

    void Behaviour::InitializeManagedBridge() {
        _behaviourBridgeType = ManagedType(_behaviourBridgeAssembly);
        _behaviourType = ManagedType(_behaviourAssembly);

        _enabledProperty = _behaviourBridgeType.getProperty("enabled");
        _isActiveAndEnabledProperty = _behaviourBridgeType.getProperty("isActiveAndEnabled");
    }
}