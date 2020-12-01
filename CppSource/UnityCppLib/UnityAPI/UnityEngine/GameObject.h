#pragma once

#include "Object.h"
#include "UnityAPI/ManagedBridge/Members/PropertyMember.h"
#include "UnityAPI/ManagedBridge/Members/ConstructorMember.h"

namespace UnityEngine {
    class Transform;
    class Component;

    class GameObject : public Object {
        friend class Component;

    private:
        Transform *_transform = nullptr;

        GameObject(ManagedInstance instance);

    public:
        explicit GameObject();
        explicit GameObject(const char *name);
        explicit GameObject(const char *name, ManagedType components[], int componentCount);
        ~GameObject();

        [[nodiscard,maybe_unused]] Transform *transform() const;
        template<class TComponent> [[nodiscard,maybe_unused]] TComponent *addComponent() const;
        template<class TComponent> [[nodiscard,maybe_unused]] TComponent *getComponent() const;
        template<class TComponent> [[nodiscard,maybe_unused]] bool tryGetComponent(const TComponent &component);

        static const ManagedType type();
    };
}