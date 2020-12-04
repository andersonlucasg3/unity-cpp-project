#include "Object.h"
#include "UnityAPI/Helpers/Helpers.h"
#include "UnityAPI/ManagedBridge/ManagedAssemblyInfo.h"

using namespace std;
using namespace Helpers;
using namespace ManagedBridge;

namespace UnityEngine {
    const ManagedAssemblyInfo _objectAssemblyInfo("UnityCpp.NativeBridge.UnityBridges.ObjectBridge");

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
        UnmanagedValue value;
        _hideFlagsProperty.get(_instance, &value);
        return (HideFlags)(int)value;
    }

    void Object::setHideFlags(HideFlags flags) const {
        _hideFlagsProperty.setValue(_instance, flags);
    }

    string_c Object::name() const {
        UnmanagedValue value;
        _nameProperty.get(_instance, &value);
        return value;
    }

    void Object::setName(string_c name) const {
        _nameProperty.setValue(_instance, name);
    }

    ManagedType Object::type() {
        return _objectType;
    }

    void Object::InitializeManagedBridge() {
        _objectType = ManagedType(_objectAssemblyInfo);

        _nameProperty = _objectType.getProperty("name");
        _hideFlagsProperty = _objectType.getProperty("hideFlags");
    }
}