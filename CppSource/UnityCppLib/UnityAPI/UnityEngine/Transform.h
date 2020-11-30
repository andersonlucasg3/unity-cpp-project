#pragma once

#include "Component.h"

namespace UnityEngine {
    class GameObject;

    using namespace ManagedBridge::Members;

    class Transform : public Component {
        friend class GameObject;

    private:
        PropertyMember _childCountProperty = PropertyMember::null;
        PropertyMember _parentProperty = PropertyMember::null;

        Transform *_parent = nullptr;

    protected:
        explicit Transform(const GameObject *gameObject, ManagedInstance instance);
        ~Transform();

    public:
        [[maybe_unused,nodiscard]] int childCount() const;
        [[maybe_unused,nodiscard]] Transform * parent();
        [[maybe_unused]] void setParent(Transform *parent);
    };
}