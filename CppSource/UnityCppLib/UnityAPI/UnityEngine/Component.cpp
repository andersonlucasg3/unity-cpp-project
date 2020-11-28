#include "Component.h"
#include "GameObject.h"

namespace UnityEngine {
    Component::Component() = default;

    void Component::setGameObject(GameObject *gameObject) {
        _gameObject = gameObject;
    }

    Transform * Component::transform() const {
        return _gameObject->transform();
    }

    GameObject * Component::gameObject() const {
        return _gameObject;
    }
}