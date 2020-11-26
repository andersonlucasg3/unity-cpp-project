#pragma once

namespace CppSource::Components {
    class CustomComponent
    {
    protected:
        CustomComponent();

    public:
        virtual void Awake() = 0;
        virtual void Start() = 0;
        virtual void Update() = 0;
        virtual void LateUpdate() = 0;
    };
}