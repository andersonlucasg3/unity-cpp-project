#pragma once

#include "Object.h"

namespace UnityEngine {
    class Transform;
    class GameObject;

    class Component : public Object {
    private:
        static ManagedType _componentType;
        static PropertyMember _transformProperty;
        static PropertyMember _gameObjectProperty;
        static PropertyMember _tagProperty;

        const GameObject *_gameObject = nullptr;
        const Transform *_transform = nullptr;

    protected:
        explicit Component(ManagedInstance instance, const GameObject *gameObject);
        ~Component();

    public:
        [[nodiscard,maybe_unused]] const Transform *transform() const;
        [[nodiscard,maybe_unused]] const GameObject *gameObject() const;
        [[nodiscard,maybe_unused]] const char *tag() const;
        [[maybe_unused]] void setTag(const char *tag) const;

        static const ManagedType type();
        static void InitializeManagedBridge();
    };
}