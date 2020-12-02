#pragma once

#include "Object.h"

namespace UnityEngine {
    class Transform;
    class GameObject;

    class Component : public Object {
    private:
        const GameObject *_gameObject = nullptr;

    protected:
        explicit Component(ManagedType type);
        explicit Component(ManagedInstance instance);
        explicit Component(ManagedInstance instance, const GameObject *gameObject = nullptr);
        ~Component();

    public:
        [[nodiscard,maybe_unused]] const Transform *transform() const;
        [[nodiscard,maybe_unused]] const GameObject *gameObject() const;

        static const ManagedType type();
        static void InitializeManagedBridge();
    };
}