#include "Transform.h"
#include "GameObject.h"
#include "UnityAPI/ManagedBridge/ManagedAssemblyInfo.h"
#include "UnityAPI/UnityAPIExtern.h"

namespace UnityEngine {
    const ManagedAssemblyInfo _transformAssemblyInfo("UnityEngine.Transform", "UnityEngine.dll");

    ManagedType _transformType = ManagedType::null;

    PropertyMember _childCountProperty = PropertyMember::null;
    PropertyMember _parentProperty = PropertyMember::null;

    Transform::Transform(ManagedInstance instance, const GameObject *gameObject) : Component(instance, gameObject) {
        // nothing yet
    }

    Transform::~Transform() = default;

    int Transform::childCount() const {
        return _childCountProperty.get<int>(_instance);
    }

    Transform * Transform::parent() {
        if (_parent != nullptr) {
            ManagedPointer pointer = _parentProperty.get<ManagedPointer>(_instance);
            ManagedPointer currentPointer = _parent->_instance;
            if (currentPointer != pointer) {
                delete _parent;
                if (pointer != nullptr) {
                    _parent = new Transform(ManagedInstance(pointer));
                } else {
                    _parent = nullptr;
                }
            } else {
                Managed::destroy(pointer);
            }
        }
        return _parent;
    }

    void Transform::setParent(Transform *parent) {
        _parentProperty.set(_instance, (ManagedPointer)parent->_instance);
        _parent = parent;
    }

    const ManagedType Transform::type() {
        return _transformType;
    }

    void Transform::InitializeManagedBridge() {
        _transformType = ManagedType(_transformAssemblyInfo);

        _childCountProperty = _transformType.getProperty("childCount");
        _parentProperty = _transformType.getProperty("parent");
    }
}