#include "Object.h"
#include "UnityAPI/ManagedBridge/ManagedAssemblyInfo.h"
#include "UnityAPI/ManagedBridge/Members/PropertyMember.h"
#include "UnityAPI/ManagedBridge/ManagedType.h"

using namespace std;
using namespace UnityEngine::ManagedBridge;

namespace UnityEngine {
    const ManagedAssemblyInfo _objectAssemblyInfo("UnityEngine.Object", "UnityEngine.dll");

    ManagedType _objectType = ManagedType::null;

    PropertyMember _nameProperty = PropertyMember::null;
    PropertyMember _hideFlagsProperty = PropertyMember::null;

    Object::Object(ManagedType type) {
        _type = type;
    }

    Object::Object(ManagedInstance instance) {
        _instance = instance;
    }

    Object::~Object() {
        Managed::destroy(_instance);
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

    void Object::InitializeManagedBridge() {
        _objectType = ManagedType(_objectAssemblyInfo);

        _nameProperty = _objectType.getProperty("name");
        _hideFlagsProperty = _objectType.getProperty("hasFlags");
    }
}