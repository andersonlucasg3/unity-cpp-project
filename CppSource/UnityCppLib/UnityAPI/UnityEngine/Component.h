#pragma once

#include "Object.h"

namespace UnityEngine {
    class Transform;
    class GameObject;

    class Component : public Object {
    private:
        static ManagedType _componentType;

        const GameObject *_gameObject = nullptr;
        const Transform *_transform = nullptr;

    protected:
        explicit Component(ManagedType type, const GameObject *gameObject);
        explicit Component(ManagedInstance instance, const GameObject *gameObject);
        ~Component();

    public:
        [[nodiscard,maybe_unused]] const Transform *transform() const;
        [[nodiscard,maybe_unused]] const GameObject *gameObject() const;

        static const ManagedType type();
        static void InitializeManagedBridge();
    };
}