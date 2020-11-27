#include "CustomComponent.h"

namespace  CppSource::Components {
    CustomComponent::CustomComponent() = default;

    void CustomComponent::SetGameObjectName(const string &gameObjectName) {
        _gameObjectName = gameObjectName;
    }
}