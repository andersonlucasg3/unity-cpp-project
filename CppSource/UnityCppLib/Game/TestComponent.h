#pragma once

#include "../Components/NativeComponent.h"

using namespace CppSource::Components;

namespace CppSource::Game {
    class TestComponent : public NativeComponent {
    public:
        TestComponent();

        void awake() override;
        void start() override;
        void update() override;
        void lateUpdate() override;
    };
}