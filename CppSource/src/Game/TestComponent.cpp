#include "TestComponent.h"
#include REQUIRED_COMPONENT_REGISTER_HEADER

REQUIRED_COMPONENT_REGISTER_NAMESPACE

namespace CppSource::Game {
    TestComponent::TestComponent() = default;

    void TestComponent::Awake() {

    }

    void TestComponent::Start() {

    }

    REQUIRED_COMPONENT_REGISTER(TestComponent)
}