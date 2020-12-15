#include "GameObject.h"
#include "Transform.h"

namespace UnityEngine {
    template bool GameObject::tryGetComponent(Transform **component);
}