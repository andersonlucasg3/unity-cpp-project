#pragma once

#include "Component.h"

namespace UnityEngine {
    class GameObject;

    class Transform : public Component {
        friend class GameObject;

    private:
        ManagedMember *_childCountProperty{};
        ManagedMember *_parentProperty{};

        Transform *_parent{};

    protected:
        explicit Transform(intptr_t *instance);
        Transform(const GameObject *gameObject, intptr_t *instance);
        ~Transform();
        void InitializeMembers() override;

    public:
        [[maybe_unused,nodiscard]] int childCount() const;
        [[maybe_unused,nodiscard]] Transform * parent();
        [[maybe_unused]] void setParent(Transform *parent);
    };
}