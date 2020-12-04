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
        [[nodiscard,maybe_unused]] string_c tag() const;
        [[maybe_unused]] void setTag(string_c tag) const;

        static ManagedType type();
        static void InitializeManagedBridge();
    };
}