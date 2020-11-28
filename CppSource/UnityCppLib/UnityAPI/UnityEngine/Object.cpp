#include "Object.h"
#include "Managed.h"

#include <typeinfo>

namespace UnityEngine {
    Object::Object() {
        _managed = new Managed;
        _managed->newInstance(typeid(this).name());
    }

    Object::~Object() {
        delete _managed;
    }

    void Object::setValue(const char *propertyName, void *value) {
        _managed->setValue(propertyName, value);
    }
}