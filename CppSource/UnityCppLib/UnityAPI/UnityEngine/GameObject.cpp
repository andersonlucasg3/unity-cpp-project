#include "GameObject.h"
#include "Transform.h"
#include "Debug.h"

#include <type_traits>

using namespace std;
using namespace ManagedBridge;

namespace UnityEngine {
    const ManagedAssemblyInfo _gameObjectBridgeAssembly("UnityCpp.NativeBridge.UnityBridges.GameObjectBridge");
    const ManagedAssemblyInfo _gameObjectAssembly("UnityEngine.GameObject", "UnityEngine.dll");

    ManagedType GameObject::_gameObjectBridgeType = ManagedType::null;
    ManagedType GameObject::_gameObjectType = ManagedType::null;

    ConstructorMember GameObject::_defaultConstructor = ConstructorMember::null;
    ConstructorMember GameObject::_secondConstructor = ConstructorMember::null;
    ConstructorMember GameObject::_thirdConstructor = ConstructorMember::null;

    PropertyMember GameObject::_activeInHierarchyProperty = PropertyMember::null;
    PropertyMember GameObject::_sceneCullingMaskProperty = PropertyMember::null;
    PropertyMember GameObject::_activeSelfProperty = PropertyMember::null;
    PropertyMember GameObject::_isStaticProperty = PropertyMember::null;
    PropertyMember GameObject::_layerProperty = PropertyMember::null;
    PropertyMember GameObject::_tagProperty = PropertyMember::null;
    PropertyMember GameObject::_transformProperty = PropertyMember::null;

    MethodMember GameObject::_addComponentMethod = MethodMember::null;
    MethodMember GameObject::_getComponentMethod = MethodMember::null;
    MethodMember GameObject::_tryGetComponentMethod = MethodMember::null;

    ManagedInstance createTransform(ManagedInstance instance, PropertyMember transform) {
        UnmanagedValue value(UnmanagedType::pointerType);
        transform.get(instance, &value);
        return ManagedInstance(ManagedPointer(value));
    }

    GameObject::GameObject() : Object() {
        _instance = _defaultConstructor.constructor(nullptr, 0);
        _transform = new Transform(createTransform(_instance, _transformProperty), this);
    }

    GameObject::GameObject(string_c name) : Object() {
        UnmanagedValue parameters[] = { UnmanagedValue(name) };
        _instance = _secondConstructor.constructor(parameters, 1);
        _transform = new Transform(createTransform(_instance, _transformProperty), this);
    }

    GameObject::GameObject(string_c name, ManagedType components[], int componentCount) : Object() {
        UnmanagedValue *componentsParameter = (UnmanagedValue *)malloc(sizeof(UnmanagedValue) * componentCount);
        for (int index = 0; index < componentCount; ++index) {
            componentsParameter[index] = UnmanagedValue(components[index].toPointer().toManaged());
        }
        UnmanagedValue parameters[] = { UnmanagedValue(name), UnmanagedValue(componentsParameter) };
        _instance = _thirdConstructor.constructor(parameters, 2);
        free(componentsParameter);

        _transform = new Transform(createTransform(_instance, _transformProperty), this);
    }

    GameObject::GameObject(ManagedInstance instance) : Object(instance) {
        _instance = instance;

        _transform = new Transform(createTransform(_instance, _transformProperty), this);
    }

    GameObject::~GameObject() {
        delete _transform;
    }

    bool GameObject::activeSelf() const {
        UnmanagedValue value(UnmanagedType::boolType);
        _activeSelfProperty.get(_instance, &value);
        return value;
    }

    bool GameObject::activeInHierarchy() const {
        UnmanagedValue value(UnmanagedType::boolType);
        _activeInHierarchyProperty.get(_instance, &value);
        return value;
    }

    ulong GameObject::sceneCullingMask() const {
        UnmanagedValue value(UnmanagedType::ulongType);
        _sceneCullingMaskProperty.get(_instance, &value);
        return value;
    }

    bool GameObject::isStatic() const {
        UnmanagedValue value(UnmanagedType::boolType);
        _isStaticProperty.get(_instance, &value);
        return value;
    }

    void GameObject::setIsStatic(bool isStatic) const {
        UnmanagedValue value(isStatic);
        _isStaticProperty.setValue(_instance, &value);
    }

    int GameObject::layer() const {
        UnmanagedValue value(UnmanagedType::intType);
        _layerProperty.get(_instance, &value);
        return value;
    }

    void GameObject::setLayer(int layer) const {
        UnmanagedValue value(layer);
        _layerProperty.setValue(_instance, &value);
    }

    string_c  GameObject::tag() const {
        UnmanagedValue value(UnmanagedType::stringType);
        _tagProperty.get(_instance, &value);
        return value;
    }

    void GameObject::setTag(string_c tag) const {
        UnmanagedValue value(tag);
        _tagProperty.setValue(_instance, &value);
    }

    Transform *GameObject::transform() const {
        return _transform;
    }

    template<class TComponent> TComponent *GameObject::addComponent() const {
        static_assert(is_base_of<Component, TComponent>(), "TComponent must inherit from Component");
        UnmanagedValue output(::pointerType);
        UnmanagedValue parameters[] = { TComponent::type() };
        _addComponentMethod.callMethod(_instance, parameters, 1, &output);
        return TComponent(ManagedPointer(output), this);
    }

    template<class TComponent> TComponent *GameObject::getComponent() const {
        static_assert(is_base_of<Component, TComponent>(), "TComponent must inherit from Component");
        UnmanagedValue output(::pointerType);
        UnmanagedValue parameters[] = { TComponent::type() };
        _getComponentMethod.callMethod(_instance, parameters, 1, &output);
        return TComponent(ManagedPointer(output), this);
    }

    template<class TComponent> bool GameObject::tryGetComponent(TComponent **component) {
        static_assert(is_base_of<Component, TComponent>(), "TComponent must inherit from Component");
        UnmanagedValue output(::pointerType);
        UnmanagedValue parameters[] = { UnmanagedValue(TComponent::unityType().toPointer().toManaged()) };
        bool ret = _tryGetComponentMethod.callMethodOut(_instance, parameters, 2, &output);
        if (ret) {
            (*component) = new TComponent(ManagedPointer(output), this);
        }
        return ret;
    }

    const ManagedType GameObject::type() {
        return _gameObjectBridgeType;
    }

    void GameObject::InitializeManagedBridge() {
        _gameObjectBridgeType = ManagedType(_gameObjectBridgeAssembly);
        _gameObjectType = ManagedType(_gameObjectAssembly);

        ManagedType firstConstructorParams[] = { System::managedIntPtrType };
        _defaultConstructor = _gameObjectBridgeType.getConstructor(firstConstructorParams, 1);

        ManagedType secondConstructorParams[] = { System::managedIntPtrType, System::managedStringType };
        _secondConstructor = _gameObjectBridgeType.getConstructor(secondConstructorParams, 2);

        ManagedType thirdConstructorParams[] = { System::managedIntPtrType, System::managedStringType, System::managedArrayType };
        _thirdConstructor = _gameObjectBridgeType.getConstructor(thirdConstructorParams, 3);

        _activeInHierarchyProperty = _gameObjectBridgeType.getProperty("activeInHierarchy");
        _sceneCullingMaskProperty = _gameObjectBridgeType.getProperty("sceneCullingMask");
        _activeSelfProperty = _gameObjectBridgeType.getProperty("activeSelf");
        _isStaticProperty = _gameObjectBridgeType.getProperty("isStatic");
        _layerProperty = _gameObjectBridgeType.getProperty("layer");
        _tagProperty = _gameObjectBridgeType.getProperty("tag");
        _transformProperty = _gameObjectBridgeType.getProperty("transform");

        _addComponentMethod = _gameObjectBridgeType.getMethod("AddComponent");
        _getComponentMethod = _gameObjectBridgeType.getMethod("GetComponent");
        _tryGetComponentMethod = _gameObjectBridgeType.getMethod("TryGetComponent");
    }

    template bool GameObject::tryGetComponent(Transform **component);
}