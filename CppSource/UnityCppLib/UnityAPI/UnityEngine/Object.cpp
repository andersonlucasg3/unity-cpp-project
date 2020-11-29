#include "Object.h"
#include "UnityAPI/ManagedBridge/Managed.h"
#include "UnityAPI/ManagedBridge/ManagedMember.h"

using namespace std;
using namespace UnityEngine::ManagedBridge;

namespace UnityEngine {
    Object::Object() {
        _managed = new Managed();
    }

    Object::Object(intptr_t *instance) {
        _managed = new Managed(instance);
    }

    Object::~Object() {
        Managed::destroy(_nameProperty);
        Managed::destroy(_hideFlagsProperty);
        delete _managed;
    }

    void Object::createManagedInstance(const char *className) {
        _managed->construct(className);
        InitializeMembers();
    }

    void Object::InitializeMembers() {
        _nameProperty = _managed->getMember("name", property);
        _hideFlagsProperty = _managed->getMember("hideFlags", property);
    }

    HideFlags Object::hideFlags() const {
        return (HideFlags) _hideFlagsProperty->getInt();
    }

    const char * Object::name() const {
        return _nameProperty->getString();
    }

    void Object::setName(const char *name) const {
        _nameProperty->setString(name);
    }
}