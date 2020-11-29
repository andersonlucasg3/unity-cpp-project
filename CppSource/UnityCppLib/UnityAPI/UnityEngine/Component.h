#pragma once

#include "Object.h"

namespace UnityEngine {
    class Transform;
    class GameObject;

    class Component : public Object {
    private:
        ManagedMember *_gameObjectProperty{};
        ManagedMember *_tagProperty{};

        const GameObject *_gameObject{};

    protected:
        Component(intptr_t *instance);
        Component(const GameObject *gameObject, intptr_t *instance);
        ~Component();
        void InitializeMembers() override;

    public:
        [[nodiscard,maybe_unused]] Transform *transform() const;
        [[nodiscard,maybe_unused]] const GameObject *gameObject() const;
    };
}