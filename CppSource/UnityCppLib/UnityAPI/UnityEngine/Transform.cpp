#include "Transform.h"
#include "GameObject.h"

using namespace CppEngine;

namespace UnityEngine {
    const ManagedAssemblyInfo _transformBridgeAssemblyInfo("UnityCpp.NativeBridge.UnityBridges.TransformBridge");
    const ManagedAssemblyInfo _transformAssemblyInfo("UnityEngine.Transform", "UnityEngine.dll");

    ManagedType Transform::_transformBridgeType = ManagedType::null;
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
        UnmanagedValue value(parentPointer.toManaged());
        _parentProperty.setValue(_instance, &value);
        _parent = parent;
    }

    ManagedType Transform::type() {
        return _transformBridgeType;
    }

    ManagedType Transform::unityType() {
        return _transformType;
    }

    void Transform::InitializeManagedBridge() {
        _transformBridgeType = ManagedType(_transformBridgeAssemblyInfo);
        _transformType = ManagedType(_transformAssemblyInfo);

        _childCountProperty = _transformBridgeType.getProperty("childCount");
        _parentProperty = _transformBridgeType.getProperty("parent");
    }
}