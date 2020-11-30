#include "Object.h"
#include "UnityAPI/ManagedBridge/Members/PropertyMember.h"

using namespace std;
using namespace UnityEngine::ManagedBridge;

namespace UnityEngine {
    Object::Object(ManagedInstance instance) {
        _instance = instance;

        _nameProperty = instance.type().getProperty("name");
        _hideFlagsProperty = instance.type().getProperty("hideFlags");
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
}