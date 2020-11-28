#pragma once

#include <list>

using namespace std;

namespace UnityEngine {
    class Transform;
    class Component;

    class GameObject {
    private:
        list<Component> *_components;
        Transform *_transform;

    public:
        GameObject();

        [[nodiscard]] Transform *transform() const;
        template<class TComponent> TComponent *addComponent() const;
        template<class TComponent> TComponent *getComponent() const;
        template<class TComponent> bool tryGetComponent(const TComponent &component);
    };
}