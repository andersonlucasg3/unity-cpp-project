#include "Object.h"
#include "UnityAPI/ManagedBridge/ManagedAssemblyInfo.h"
#include "UnityAPI/ManagedBridge/Members/PropertyMember.h"

using namespace std;
using namespace UnityEngine::ManagedBridge;

namespace UnityEngine {
    const ManagedAssemblyInfo _objectAssemblyInfo("UnityEngine.Object", "UnityEngine.dll");
    const ManagedType _objectType(_objectAssemblyInfo);

    const PropertyMember _nameProperty = _objectType.getProperty("name");
    const PropertyMember _hideFlagsProperty = _objectType.getProperty("hasFlags");

    Object::Object(ManagedType type) {
        _type = type;
    }

    Object::Object(ManagedInstance instance) {
        _type = instance.type();
        _instance = instance;
    }

    Object::~Object() {
        Managed::destroy(_instance);
        Managed::destroy(_nameProperty);
        Managed::destroy(_hideFlagsProperty);
    }

    HideFlags Object::hideFlags() const {
        return (HideFlags) _hideFlagsProperty.get<int>(_instance);
    }

    const char * Object::name() const {
        return _nameProperty.get<const char *>(_instance);
    }

    void Object::setName(const char *name) const {
        _nameProperty.set(_instance, name);
    }

    const ManagedType Object::type() {
        return _objectType;
    }
}