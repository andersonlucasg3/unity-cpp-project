#pragma once

#include "Component.h"

namespace UnityEngine {
    class GameObject;

    using namespace ManagedBridge::Members;

    class Transform : public Component {
        friend class GameObject;

    private:
        Transform *_parent = nullptr;

    protected:
        explicit Transform(ManagedInstance instance, const GameObject *gameObject = nullptr);
        ~Transform();

    public:
        [[maybe_unused,nodiscard]] int childCount() const;
        [[maybe_unused,nodiscard]] Transform * parent();
        [[maybe_unused]] void setParent(Transform *parent);

        static const ManagedType type();
    };
}