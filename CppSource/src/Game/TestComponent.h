#pragma once

#include "../Components/RequiredComponentDefines.h"
#include "../Components/CustomComponent.h"
#include "ComponentsRegistration.h"

REQUIRED_COMPONENT_HEADER

using namespace CppSource::Components;

namespace CppSource::Game {
    class TestComponent : private CustomComponent {
    private:
        REQUIRED_COMPONENT_BODY(TestComponent)

    protected:
        TestComponent();

    public:
        void Awake() override;
        void Start() override;
    };
}