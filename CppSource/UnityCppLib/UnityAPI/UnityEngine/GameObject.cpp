#include "GameObject.h"
#include "Transform.h"
#include "UnityAPI/UnityAPIExtern.h"
#include "UnityAPI/ManagedBridge/ManagedAssemblyInfo.h"
#include "Debug.h"

#include <type_traits>

using namespace std;

namespace UnityEngine {
    const ManagedAssemblyInfo _gameObjectAssembly("UnityEngine.GameObject", "UnityEngine.dll");

    const ManagedType _gameObjectType(_gameObjectAssembly);

    const ConstructorMember _defaultConstructor(_gameObjectType.getConstructor(0));
    const ConstructorMember _secondConstructor(_gameObjectType.getConstructor(1));
    const ConstructorMember _thirdConstructor(_gameObjectType.getConstructor(2));

    const PropertyMember _activeInHierarchyProperty = _gameObjectType.getProperty("activeInHierarchy");
    const PropertyMember _activeSelfProperty = _gameObjectType.getProperty("activeSelf");
    const PropertyMember _isStaticProperty = _gameObjectType.getProperty("isStatic");
    const PropertyMember _layerProperty = _gameObjectType.getProperty("layer");
    const PropertyMember _tagProperty = _gameObjectType.getProperty("tag");
    const PropertyMember _transformProperty = _gameObjectType.getProperty("transform");

    ManagedInstance createTransform(ManagedInstance instance) {
        ManagedPointer pointer = _transformProperty.get<ManagedPointer>(instance);
        return ManagedInstance(pointer);
    }

    GameObject::GameObject() : Object(_gameObjectType) {
        _instance = _defaultConstructor.constructor(_gameObjectType, nullptr, 0);
        _transform = new Transform(createTransform(_instance), this);
    }

    GameObject::GameObject(const char *name) : Object(_gameObjectType) {
        void **parameters = new void *[] { (void *)name };
        _instance = _secondConstructor.constructor(_gameObjectType, parameters, 1);
        delete[] parameters;
        _transform = new Transform(createTransform(_instance), this);
    }

    GameObject::GameObject(const char *name, ManagedType components[], int componentCount) : Object(_gameObjectType) {
        void **componentsPtr = new void *[componentCount];
        ManagedPointer ptr = ManagedPointer::null;
        for (int index = 0; index < componentCount; ++index) {
            ptr = components[index];
            componentsPtr[index] = (void *)(const void *)ptr;
        }
        void **parametersPtr = new void *[] { (void *)name, (void *)components };
        _instance = _thirdConstructor.constructor(_gameObjectType, parametersPtr, 2);
        delete[] componentsPtr;
        delete[] parametersPtr;

        _transform = new Transform(createTransform(_instance), this);
    }

    GameObject::GameObject(ManagedInstance instance) : Object(instance) {
        _instance = instance;

        _transform = new Transform(createTransform(_instance), this);
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
}