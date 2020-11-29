#include "GameObject.h"
#include "Transform.h"
#include "UnityAPI/UnityAPIExtern.h"
#include "UnityAPI/ManagedBridge/Managed.h"
#include "UnityAPI/ManagedBridge/ManagedMember.h"
#include "Debug.h"

#include <type_traits>
#include <iostream>

using namespace std;

namespace UnityEngine {
    const char * const _gameObjectClassName = "UnityEngine.GameObject, UnityEngine.dll";

    GameObject::GameObject() : Object() {
        createManagedInstance(_gameObjectClassName);
    }

    GameObject::~GameObject() {
        Managed::destroy(_activeInHierarchyProperty);
        Managed::destroy(_activeSelfProperty);
        Managed::destroy(_isStaticProperty);
        Managed::destroy(_layerProperty);
        Managed::destroy(_tagProperty);
        Managed::destroy(_transformProperty);

        delete _transform;
    }

    void GameObject::InitializeMembers() {
        Object::InitializeMembers();
        _activeInHierarchyProperty = _managed->getMember("activeInHierarchy", property);
        _activeSelfProperty = _managed->getMember("activeSelf", property);
        _isStaticProperty = _managed->getMember("isStatic", property);
        _layerProperty = _managed->getMember("layer", property);
        _tagProperty = _managed->getMember("tag", property);
        _transformProperty = _managed->getMember("transform", property);

        intptr_t *transformPtr = _transformProperty->getObject();
        _transform = new Transform(this, transformPtr);
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
}