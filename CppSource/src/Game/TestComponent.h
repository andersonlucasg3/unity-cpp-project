#pragma once

#include "../Components/NativeComponent.h"

using namespace CppSource::Components;

namespace CppSource::Game {
    class TestComponent : public NativeComponent {
    public:
        TestComponent();

        void Awake() override;
        void Start() override;
        void Update() override;
        void LateUpdate() override;
    };
}