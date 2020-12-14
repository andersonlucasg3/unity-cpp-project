#include "GameObject.h"
#include "Transform.h"
#include "Debug.h"
#include "UnityAPI/ManagedBridge/ManagedAssemblyInfo.h"
#include "UnityAPI/ManagedBridge/UnmanagedValue.h"
#include "UnityAPI/NetFramework/System.h"
#include "UnityAPI/Helpers/Helpers.h"

#include <type_traits>

using namespace std;
using namespace Helpers;
using namespace ManagedBridge;

namespace UnityEngine {
    const ManagedAssemblyInfo _gameObjectAssembly("UnityCpp.NativeBridge.UnityBridges.GameObjectBridge");

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
        return TComponent(ManagedPointer(output));
    }

    template<class TComponent> TComponent *GameObject::getComponent() const {
        static_assert(is_base_of<Component, TComponent>(), "TComponent must inherit from Component");
        UnmanagedValue output(::pointerType);
        UnmanagedValue parameters[] = { TComponent::type() };
        _getComponentMethod.callMethod(_instance, parameters, 1, &output);
        return TComponent(ManagedPointer(output));
    }

    template<class TComponent> bool GameObject::tryGetComponent(TComponent **component) {
        static_assert(is_base_of<Component, TComponent>(), "TComponent must inherit from Component");
        UnmanagedValue output(::pointerType);
        UnmanagedValue parameters[] = { TComponent::type(), &output };
        _tryGetComponentMethod.callMethod(_instance, parameters, nullptr);
        (*component) = new TComponent(ManagedPointer(output));
    }

    const ManagedType GameObject::type() {
        return _gameObjectType;
    }

    void GameObject::InitializeManagedBridge() {
        _gameObjectType = ManagedType(_gameObjectAssembly);

        _defaultConstructor = _gameObjectType.getConstructor(nullptr, 0);

        ManagedType secondConstructorParams[] = { System::managedStringType };
        _secondConstructor = _gameObjectType.getConstructor(secondConstructorParams, 1);

        ManagedType thirdConstructorParams[] = { System::managedStringType, System::managedArrayType };
        _thirdConstructor = _gameObjectType.getConstructor(thirdConstructorParams, 2);

        _activeInHierarchyProperty = _gameObjectType.getProperty("activeInHierarchy");
        _sceneCullingMaskProperty = _gameObjectType.getProperty("sceneCullingMask");
        _activeSelfProperty = _gameObjectType.getProperty("activeSelf");
        _isStaticProperty = _gameObjectType.getProperty("isStatic");
        _layerProperty = _gameObjectType.getProperty("layer");
        _tagProperty = _gameObjectType.getProperty("tag");
        _transformProperty = _gameObjectType.getProperty("transform");

        _addComponentMethod = _gameObjectType.getMethod("AddComponent");
        _getComponentMethod = _gameObjectType.getMethod("GetComponent");
        _tryGetComponentMethod = _gameObjectType.getMethod("TryGetComponent");
    }
}