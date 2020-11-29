#pragma once

#include "Object.h"

namespace UnityEngine {
    class Transform;
    class Component;

    class GameObject : public Object {
        friend class Component;

    private:
        ManagedMember *_activeInHierarchyProperty{};
        ManagedMember *_activeSelfProperty{};
        ManagedMember *_isStaticProperty{};
        ManagedMember *_layerProperty{};
        ManagedMember *_tagProperty{};
        ManagedMember *_transformProperty{};

        Transform *_transform{};

        explicit GameObject(intptr_t *instance);
        void InitializeMembers() override;

    public:
        GameObject();
        ~GameObject();

        [[nodiscard,maybe_unused]] Transform *transform() const;
        template<class TComponent> [[nodiscard,maybe_unused]] TComponent *addComponent() const;
        template<class TComponent> [[nodiscard,maybe_unused]] TComponent *getComponent() const;
        template<class TComponent> [[nodiscard,maybe_unused]] bool tryGetComponent(const TComponent &component);
    };
}