#pragma once

#include "../Components/RequiredComponentDefines.h"
#include "../Components/CustomComponent.h"
#include "ComponentsRegistration.h"

REQUIRED_COMPONENT_HEADER

using namespace CppSource::Components;

namespace CppSource::Game {
    class TestComponent : public CustomComponent {
    private:
        REQUIRED_COMPONENT_BODY(TestComponent)

    public:
        TestComponent();

        void Awake() override;
        void Start() override;
        void Update() override;
        void LateUpdate() override;
    };
}