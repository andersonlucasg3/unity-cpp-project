#include "Object.h"
#include "UnityAPI/Helpers/StringsHelper.h"
#include "UnityAPI/ManagedBridge/ManagedAssemblyInfo.h"

#include <cstring>

using namespace std;
using namespace Helpers;
using namespace ManagedBridge;

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

    void Object::setHideFlags(HideFlags flags) const {
        _hideFlagsProperty.setValue<int>(_instance, flags);
    }

    const char * Object::name() const {
        return _nameProperty.get<char *>(_instance);
    }

    void Object::setName(const char *name) const {
        _nameProperty.setPointer(_instance, stringInstance(name));
    }

    const ManagedType Object::type() {
        return _objectType;
    }

    void Object::InitializeManagedBridge() {
        _objectType = ManagedType(_objectAssemblyInfo);

        _nameProperty = _objectType.getProperty("name");
        _hideFlagsProperty = _objectType.getProperty("hideFlags");
    }
}