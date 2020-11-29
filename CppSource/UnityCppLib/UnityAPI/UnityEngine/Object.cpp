#include "Object.h"
#include "UnityAPI/ManagedBridge/Managed.h"
#include "UnityAPI/ManagedBridge/ManagedMember.h"

using namespace std;
using namespace UnityEngine::ManagedBridge;

namespace UnityEngine {
    Object::Object() {
        _managed = new Managed();
        _nameProperty = nullptr;
    }

    Object::~Object() {
        delete _managed;
    }

    void Object::createManagedInstance(const char *className) {
        _managed->newInstance(className);
        _nameProperty = _managed->getMember("name", MemberType::property);
    }

    const char * Object::name() const {
        return _nameProperty->getValueString();
    }

    void Object::setName(const char *name) const {
        _nameProperty->setValueString(name);
    }
}