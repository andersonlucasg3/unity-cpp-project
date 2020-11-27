#include "TestComponent.h"
#include <iostream>
#include REQUIRED_COMPONENT_REGISTER_HEADER
#include "../UnityAPI/UnityAPIExtern.h"

REQUIRED_COMPONENT_REGISTER_NAMESPACE

namespace CppSource::Game {
    TestComponent::TestComponent() = default;

    void TestComponent::Awake() {
        const string& message = "Native TestComponent::Awake";
        cout << message;
        UnitySendMessage(_gameObjectName.c_str(), "DoLog", message.c_str());
    }

    void TestComponent::Start() {
        const string& message = "Native TestComponent::Awake";
        cout << message;
        UnitySendMessage(_gameObjectName.c_str(), "DoLog", message.c_str());
    }

    void TestComponent::Update() {

    }

    void TestComponent::LateUpdate() {

    }

    REQUIRED_COMPONENT_REGISTER(TestComponent)
}