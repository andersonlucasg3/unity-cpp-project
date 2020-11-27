#include "TestComponent.h"
#include REQUIRED_COMPONENT_REGISTER_HEADER

REQUIRED_COMPONENT_REGISTER_NAMESPACE

namespace CppSource::Game {
    TestComponent::TestComponent() = default;

    void TestComponent::Awake() {

    }

    void TestComponent::Start() {

    }

    void TestComponent::Update() {

    }

    void TestComponent::LateUpdate() {

    }

    REQUIRED_COMPONENT_REGISTER(TestComponent)
}