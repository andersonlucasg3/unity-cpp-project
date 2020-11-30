#pragma once

#include "Object.h"

namespace UnityEngine {
    class Transform;
    class GameObject;

    class Component : public Object {
    private:
        PropertyMember _gameObjectProperty = PropertyMember::null;
        PropertyMember _tagProperty = PropertyMember::null;

        const GameObject *_gameObject = nullptr;

    protected:
        explicit Component(const GameObject *gameObject, ManagedInstance instance);
        ~Component();

    public:
        [[nodiscard,maybe_unused]] Transform *transform() const;
        [[nodiscard,maybe_unused]] const GameObject *gameObject();
    };
}