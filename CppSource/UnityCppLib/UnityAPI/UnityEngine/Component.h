#pragma once

namespace UnityEngine {
    class Transform;
    class GameObject;

    class Component {
    private:
        GameObject *_gameObject;

    protected:
        Component();
        void setGameObject(GameObject *gameObject);

    public:
        [[nodiscard]] Transform *transform() const;
        [[nodiscard]] GameObject *gameObject() const;
    };
}