#pragma once

#include <string>

using namespace std;

namespace CppSource::Components {
    class NativeComponent
    {
    protected:
        const char *_gameObjectName;

        NativeComponent();
        ~NativeComponent();

    public:
        char *GetGameObjectName();
        void SetGameObjectName(const char *gameObjectName);

        virtual void Awake() = 0;
        virtual void Start() = 0;
        virtual void Update() = 0;
        virtual void LateUpdate() = 0;
    };
}