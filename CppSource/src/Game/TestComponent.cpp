#include "TestComponent.h"
#include "../UnityAPI/UnityAPIExtern.h"

using namespace UnityEngine;

namespace CppSource::Game {
    TestComponent::TestComponent() = default;

    void TestComponent::Awake() {
        Debug::Log("Native TestComponent::Awake");
    }

    void TestComponent::Start() {
        Debug::Log("Native TestComponent::Awake");
    }

    void TestComponent::Update() {
        Debug::Log("Native TestComponent::Update");
    }

    void TestComponent::LateUpdate() {
        Debug::Log("Native TestComponent::LateUpdate");
    }
}