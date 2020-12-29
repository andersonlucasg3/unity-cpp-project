#include "Object.h"
#include "MonoBehaviour.h"

using namespace std;
using namespace ManagedBridge;

namespace UnityEngine {
    const ManagedAssemblyInfo _objectBridgeAssemblyInfo("UnityCpp.NativeBridge.UnityBridges.ObjectBridge");
    const ManagedAssemblyInfo _objectAssemblyInfo("UnityEngine.Object", "UnityEngine.dll");

    ManagedType Object::_objectBridgeType = ManagedType::null;
    ManagedType Object::_objectType = ManagedType::null;

    PropertyMember Object::_nameProperty = PropertyMember::null;
    PropertyMember Object::_hideFlagsProperty = PropertyMember::null;

    MethodMember Object::_destroyMethod = MethodMember::null;
    MethodMember Object::_destroyImmediateMethod = MethodMember::null;
    MethodMember Object::_dontDestroyOnLoadMethod = MethodMember::null;

    Object::Object() = default;

    Object::Object(ManagedInstance instance) {
        _instance = instance;
    }

    Object::~Object() {
        Managed::destroy(_instance.toPointer());
    }

    HideFlags Object::hideFlags() const {
        UnmanagedValue value(UnmanagedType::intType);
        _hideFlagsProperty.get(_instance, &value);
        return (HideFlags)(int)value;
    }

    void Object::setHideFlags(HideFlags flags) const {
        UnmanagedValue value(flags);
        _hideFlagsProperty.setValue(_instance, &value);
    }

    string_c Object::name() const {
        UnmanagedValue value(UnmanagedType::stringType);
        _nameProperty.get(_instance, &value);
        return value;
    }

    void Object::setName(string_c name) const {
        UnmanagedValue value(name);
        _nameProperty.setValue(_instance, &value);
    }

    void Object::destroy(Object *obj, float t) {
        ManagedPointer pointer = obj->_instance.toPointer();
        UnmanagedValue parameters[] = { UnmanagedValue(pointer.toManaged()), UnmanagedValue(t) };
        _destroyMethod.callMethod(ManagedInstance::null, parameters, 2);
        if (typeid(MonoBehaviour).before(typeid(obj))) {
            Object::objectDelete(obj);
        }
    }

    void Object::destroyImmediate(Object *obj, bool allowDestroyingAssets) {
        ManagedPointer pointer = obj->_instance.toPointer();
        UnmanagedValue parameters[] = { UnmanagedValue(pointer.toManaged()), UnmanagedValue(allowDestroyingAssets) };
        _destroyImmediateMethod.callMethod(ManagedInstance::null, parameters, 2);
        if (typeid(MonoBehaviour).before(typeid(obj))) {
            Object::objectDelete(obj);
        }
    }

    void Object::dontDestroyOnLoad(Object *target) {
        ManagedPointer pointer = target->_instance.toPointer();
        UnmanagedValue parameters[] = { UnmanagedValue(pointer.toManaged()) };
        _dontDestroyOnLoadMethod.callMethod(ManagedInstance::null, parameters, 1);
    }

    void Object::objectDelete(Object *obj) {
        delete obj;
    }

    ManagedType Object::type() {
        return _objectBridgeType;
    }

    ManagedType Object::unityType() {
        return _objectType;
    }

    void Object::InitializeManagedBridge() {
        _objectBridgeType = ManagedType(_objectBridgeAssemblyInfo);
        _objectType = ManagedType(_objectAssemblyInfo);

        _nameProperty = _objectBridgeType.getProperty("name");
        _hideFlagsProperty = _objectBridgeType.getProperty("hideFlags");

        _destroyMethod = _objectBridgeType.getMethod("Destroy");
        _destroyImmediateMethod = _objectBridgeType.getMethod("DestroyImmediate");
        _dontDestroyOnLoadMethod = _objectBridgeType.getMethod("DontDestroyOnLoad");
    }
}