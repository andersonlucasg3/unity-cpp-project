#pragma once

#include "Object.h"

namespace UnityEngine {
    class Transform;
    class Component;

    class GameObject : private Object {
    public:
        GameObject();
        explicit GameObject(const char *name);
        ~GameObject();

        [[nodiscard]] Transform *transform() const;
        template<class TComponent> TComponent *addComponent() const;
        template<class TComponent> TComponent *getComponent() const;
        template<class TComponent> bool tryGetComponent(const TComponent &component);
    };
}