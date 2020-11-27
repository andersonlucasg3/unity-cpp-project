#pragma once

#include <string>

using namespace std;

namespace CppSource::Components {
    class CustomComponent
    {
    protected:
        string _gameObjectName;

        CustomComponent();

    public:
        void SetGameObjectName(const string& gameObjectName);

        virtual void Awake() = 0;
        virtual void Start() = 0;
        virtual void Update() = 0;
        virtual void LateUpdate() = 0;
    };
}