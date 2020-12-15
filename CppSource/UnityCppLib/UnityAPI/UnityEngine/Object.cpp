#include "Object.h"

using namespace std;
using namespace ManagedBridge;

namespace UnityEngine {
    const ManagedAssemblyInfo _objectBridgeAssemblyInfo("UnityCpp.NativeBridge.UnityBridges.ObjectBridge");
    const ManagedAssemblyInfo _objectAssemblyInfo("UnityEngine.Object", "UnityEngine.dll");

    ManagedType Object::_objectBridgeType = ManagedType::null;
    ManagedType Object::_objectType = ManagedType::null;

    PropertyMember Object::_nameProperty = PropertyMember::null;
    PropertyMember Object::_hideFlagsProperty = PropertyMember::null;

    Object::Object() = default;

    Object::Object(ManagedInstance instance) {
        _instance = instance;
    }

    Object::~Object() {
        Managed::destroy(_instance);
    }

    HideFlags Object::hideFlags() const {
        UnmanagedValue value(UnmanagedType::intType);
        _hideFlagsProperty.get(_instance, &value);
        return (HideFlags)(int)value;
    }

    void Object::setHideFlags(HideFlags flags) const {
        UnmanagedValue value(flags);
        _hideFlagsProperty.setValue(_instance, &value);
    }

    string_c Object::name() const {
        UnmanagedValue value(UnmanagedType::stringType);
        _nameProperty.get(_instance, &value);
        return value;
    }

    void Object::setName(string_c name) const {
        UnmanagedValue value(name);
        _nameProperty.setValue(_instance, &value);
    }

    ManagedType Object::type() {
        return _objectBridgeType;
    }

    ManagedType Object::unityType() {
        return _objectType;
    }

    void Object::InitializeManagedBridge() {
        _objectBridgeType = ManagedType(_objectBridgeAssemblyInfo);
        _objectType = ManagedType(_objectAssemblyInfo);

        _nameProperty = _objectBridgeType.getProperty("name");
        _hideFlagsProperty = _objectBridgeType.getProperty("hideFlags");
    }
}