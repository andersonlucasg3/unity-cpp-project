#include "GameObject.h"
#include "Transform.h"

#include <type_traits>

using namespace std;

namespace UnityEngine {
    GameObject::GameObject() {
        _components = new list<Component>;
        _transform = addComponent<Transform>();
    }

    Transform *GameObject::transform() const {
        return _transform;
    }

    template<class TComponent> TComponent *GameObject::addComponent() const {
        static_assert(is_base_of<Component, TComponent>(), "TComponent must inherit from Component");
        auto *instance = new TComponent;
        _components->push_back(*instance);
        return instance;
    }

    bool ComponentCompare(Component *component, const type_info& componentType) {
        return typeid(*component) == componentType;
    }

    template<class TComponent> TComponent *GameObject::getComponent() const {
        static_assert(is_base_of<Component, TComponent>(), "TComponent must inherit from Component");
        auto iterator = _components->begin();
        for (int index = 0; index < _components->size(); ++index) {
            advance(iterator, 1);
            Component *current = iterator.operator->();
            if (ComponentCompare(current, typeid(TComponent))) {
                return current;
            }
        }
        return nullptr;
    }

    template<class TComponent> bool GameObject::tryGetComponent(const TComponent &component) {
        static_assert(is_base_of<Component, TComponent>(), "TComponent must inherit from Component");
        component = getComponent<TComponent>();
        return component;
    }
}