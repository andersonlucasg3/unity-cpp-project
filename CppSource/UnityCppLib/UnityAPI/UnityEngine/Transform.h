#pragma once

#include "Component.h"

namespace UnityEngine {
    class GameObject;

    class Transform : public Component {
        friend class GameObject;

    private:
        ManagedMember *_childCountProperty;

    protected:
        Transform(const GameObject *gameObject, intptr_t *instance);
        ~Transform();
        void InitializeMembers() override;

    public:
        [[maybe_unused,nodiscard]] int childCount() const;
    };
}