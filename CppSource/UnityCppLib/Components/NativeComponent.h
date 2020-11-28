#pragma once

#include <string>

namespace UnityEngine {
    class GameObject;
}

using namespace std;
using namespace UnityEngine;

namespace CppSource::Components {
    class NativeComponent
    {
    protected:
        GameObject *_gameObject;

        NativeComponent();

    public:
        GameObject *gameObject();

        virtual void awake() {}
        virtual void start() {}
        virtual void update() {}
        virtual void lateUpdate() {}
    };
}