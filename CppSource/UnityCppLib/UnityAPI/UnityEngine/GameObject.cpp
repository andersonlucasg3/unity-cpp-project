#include "GameObject.h"
#include "Transform.h"
#include "Debug.h"
#include "UnityAPI/ManagedBridge/ManagedAssemblyInfo.h"
#include "UnityAPI/NetFramework/System.h"
#include "UnityAPI/Helpers/StringsHelper.h"

#include <type_traits>

using namespace std;
using namespace Helpers;

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

    ManagedInstance createTransform(ManagedInstance instance, PropertyMember transform) {
        ManagedPointer pointer = transform.get<ManagedPointer>(instance);
        return ManagedInstance(pointer);
    }

    GameObject::GameObject() : Object() {
        _instance = _defaultConstructor.constructor(nullptr, 0);
        _transform = new Transform(createTransform(_instance, _transformProperty), this);
    }

    GameObject::GameObject(string_c name) : Object() {
        void **parameters = new void *[] { (void *)name };
        _instance = _secondConstructor.constructor(parameters, 1);
        delete[] parameters;
        _transform = new Transform(createTransform(_instance, _transformProperty), this);
    }

    GameObject::GameObject(string_c name, ManagedType components[], int componentCount) : Object() {
        void ** componentsPtr = new void *[componentCount];
        ManagedPointer ptr = ManagedPointer::null;
        for (int index = 0; index < componentCount; ++index) {
            ptr = components[index].toPointer();
            componentsPtr[index] = (void *)ptr.toManaged();
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

    bool GameObject::activeSelf() const {
        return _activeSelfProperty.get<bool>(_instance);
    }

    bool GameObject::activeInHierarchy() const {
        return _activeInHierarchyProperty.get<bool>(_instance);
    }

    ulong GameObject::sceneCullingMask() const {
        return _sceneCullingMaskProperty.get<ulong>(_instance);
    }

    bool GameObject::isStatic() const {
        return _isStaticProperty.get<bool>(_instance);
    }

    void GameObject::setIsStatic(bool isStatic) const {
        _isStaticProperty.setValue(_instance, isStatic);
    }

    int GameObject::layer() const {
        return _layerProperty.get<int>(_instance);
    }

    void GameObject::setLayer(int layer) const {
        _layerProperty.setValue(_instance, layer);
    }

    string_c  GameObject::tag() const {
        return _tagProperty.get<string_c>(_instance);
    }

    void GameObject::setTag(string_c tag) const {
        string_m str = stringInstance(tag);
        _tagProperty.setValue(_instance, str);
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

        _defaultConstructor = _gameObjectType.getConstructor(nullptr, 0);

        ManagedType secondConstructorParams[] = { System::stringType };
        _secondConstructor = _gameObjectType.getConstructor(secondConstructorParams, 1);

//        _thirdConstructor = _gameObjectType.getConstructor(2);

        _activeInHierarchyProperty = _gameObjectType.getProperty("activeInHierarchy");
        _sceneCullingMaskProperty = _gameObjectType.getProperty("sceneCullingMask");
        _activeSelfProperty = _gameObjectType.getProperty("activeSelf");
        _isStaticProperty = _gameObjectType.getProperty("isStatic");
        _layerProperty = _gameObjectType.getProperty("layer");
        _tagProperty = _gameObjectType.getProperty("tag");
        _transformProperty = _gameObjectType.getProperty("transform");
    }
}