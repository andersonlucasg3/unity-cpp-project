#include "GameObject.h"
#include "Transform.h"
#include "UnityAPI/ManagedBridge/ManagedAssemblyInfo.h"
#include "Debug.h"

#include <type_traits>

using namespace std;

namespace UnityEngine {
    const ManagedAssemblyInfo _gameObjectAssembly("UnityEngine.GameObject", "UnityEngine.dll");

    ManagedType GameObject::_gameObjectType = ManagedType::null;
    ConstructorMember GameObject::_defaultConstructor = ConstructorMember::null;
    ConstructorMember GameObject::_secondConstructor = ConstructorMember::null;
    ConstructorMember GameObject::_thirdConstructor = ConstructorMember::null;
    PropertyMember GameObject::_activeInHierarchyProperty = PropertyMember::null;
    PropertyMember GameObject::_activeSelfProperty = PropertyMember::null;
    PropertyMember GameObject::_isStaticProperty = PropertyMember::null;
    PropertyMember GameObject::_layerProperty = PropertyMember::null;
    PropertyMember GameObject::_tagProperty = PropertyMember::null;
    PropertyMember GameObject::_transformProperty = PropertyMember::null;

    ManagedInstance createTransform(ManagedInstance instance, PropertyMember transform) {
        ManagedPointer pointer = transform.get<ManagedPointer>(instance);
        return ManagedInstance(pointer);
    }

    GameObject::GameObject() : Object(_gameObjectType) {
        _instance = _defaultConstructor.constructor(nullptr, 0);
        _transform = new Transform(createTransform(_instance, _transformProperty), this);
    }

    GameObject::GameObject(const char *name) : Object(_gameObjectType) {
        void **parameters = new void *[] { (void *)name };
        _instance = _secondConstructor.constructor(parameters, 1);
        delete[] parameters;
        _transform = new Transform(createTransform(_instance, _transformProperty), this);
    }

    GameObject::GameObject(const char *name, ManagedType components[], int componentCount) : Object(_gameObjectType) {
        void **componentsPtr = new void *[componentCount];
        ManagedPointer ptr = ManagedPointer::null;
        for (int index = 0; index < componentCount; ++index) {
            ptr = components[index];
            componentsPtr[index] = (void *)(const void *)ptr;
        }
        void **parametersPtr = new void *[] { (void *)name, (void *)components };
        _instance = _thirdConstructor.constructor(parametersPtr, 2);
        delete[] componentsPtr;
        delete[] parametersPtr;

        _transform = new Transform(createTransform(_instance, _transformProperty), this);
    }

    GameObject::GameObject(ManagedInstance instance) : Object(instance) {
        _instance = instance;

        _transform = new Transform(createTransform(_instance, _transformProperty), this);
    }

    GameObject::~GameObject() {
        delete _transform;
    }

    Transform *GameObject::transform() const {
        return _transform;
    }

    template<class TComponent> TComponent *GameObject::addComponent() const {
        static_assert(is_base_of<Component, TComponent>(), "TComponent must inherit from Component");
        return nullptr; // TODO: make this happen
    }

    template<class TComponent> TComponent *GameObject::getComponent() const {
        static_assert(is_base_of<Component, TComponent>(), "TComponent must inherit from Component");
        return nullptr; // TODO: make this happen
    }

    template<class TComponent> bool GameObject::tryGetComponent(const TComponent &component) {
        static_assert(is_base_of<Component, TComponent>(), "TComponent must inherit from Component");
        component = getComponent<TComponent>();
        return component;
    }

    const ManagedType GameObject::type() {
        return _gameObjectType;
    }

    void GameObject::InitializeManagedBridge() {
        _gameObjectType = ManagedType(_gameObjectAssembly);
        _defaultConstructor = _gameObjectType.getConstructor(0);
        _secondConstructor = _gameObjectType.getConstructor(1);
        _thirdConstructor = _gameObjectType.getConstructor(2);

        _activeInHierarchyProperty = _gameObjectType.getProperty("activeInHierarchy");
        _activeSelfProperty = _gameObjectType.getProperty("activeSelf");
        _isStaticProperty = _gameObjectType.getProperty("isStatic");
        _layerProperty = _gameObjectType.getProperty("layer");
        _tagProperty = _gameObjectType.getProperty("tag");
        _transformProperty = _gameObjectType.getProperty("transform");
    }
}