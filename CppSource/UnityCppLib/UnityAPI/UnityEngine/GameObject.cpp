#include "GameObject.h"
#include "Transform.h"
#include "UnityAPI/UnityAPIExtern.h"
#include "Debug.h"

#include <type_traits>
#include <typeinfo>

using namespace std;

namespace UnityEngine {
    GameObject::GameObject() : Object() {

    }

    GameObject::GameObject(const char *name) : GameObject() {
        Object::setValue("name", (void *)name);
    }

    GameObject::~GameObject() = default;

    Transform *GameObject::transform() const {
        return nullptr; // TODO: make this happen
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