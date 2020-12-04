#include "Transform.h"
#include "GameObject.h"
#include "UnityAPI/ManagedBridge/ManagedAssemblyInfo.h"

namespace UnityEngine {
    const ManagedAssemblyInfo _transformAssemblyInfo("UnityCpp.NativeBridge.UnityBridges.TransformBridge");

    ManagedType Transform::_transformType = ManagedType::null;
    PropertyMember Transform::_childCountProperty = PropertyMember::null;
    PropertyMember Transform::_parentProperty = PropertyMember::null;

    Transform::Transform(ManagedInstance instance, const GameObject *gameObject) : Component(instance, gameObject) {
        // nothing yet
    }

    Transform::~Transform() = default;

    int Transform::childCount() const {
        UnmanagedValue value(UnmanagedType::intType);
        _childCountProperty.get(_instance, &value);
        return value;
    }

    Transform * Transform::parent() {
        UnmanagedValue value(UnmanagedType::pointerType);
        _parentProperty.get(_instance, &value);
        ManagedPointer pointer(value);
        ManagedPointer currentPointer = _parent->_instance.toPointer();
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
        return _parent;
    }

    void Transform::setParent(Transform *parent) {
        ManagedPointer parentPointer = parent->_instance.toPointer();
        _parentProperty.setValue(_instance, parentPointer.toManaged());
        _parent = parent;
    }

    ManagedType Transform::type() {
        return _transformType;
    }

    void Transform::InitializeManagedBridge() {
        _transformType = ManagedType(_transformAssemblyInfo);

        _childCountProperty = _transformType.getProperty("childCount");
        _parentProperty = _transformType.getProperty("parent");
    }
}