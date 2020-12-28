#include "MonoBehaviour.h"
#include "UnityAPI/CppEngine/Registry.h"

using namespace CppEngine;

namespace UnityEngine {
    const ManagedAssemblyInfo _monoBehaviourBridgeAssembly("UnityCpp.NativeBridge.UnityBridges.MonoBehaviourBridge");
    const ManagedAssemblyInfo _monoBehaviourAssembly("UnityEngine.MonoBehaviour", "UnityEngine.dll");

    ManagedType MonoBehaviour::_monoBehaviourBridgeType = ManagedType::null;
    ManagedType MonoBehaviour::_monoBehaviourType = ManagedType::null;

    MonoBehaviour::MonoBehaviour(ManagedInstance instance, const GameObject *gameObject) : Behaviour(instance, gameObject) {
        //
    }

    MonoBehaviour::~MonoBehaviour() = default;

    void MonoBehaviour::Awake() { }
    void MonoBehaviour::OnDestroy() { }
    void MonoBehaviour::Start() { }
    void MonoBehaviour::Stop() { }
    void MonoBehaviour::OnEnable() { }
    void MonoBehaviour::OnDisable() { }
    void MonoBehaviour::FixedUpdate() { }
    void MonoBehaviour::Update() { }
    void MonoBehaviour::LateUpdate() { }

    ManagedType MonoBehaviour::type() {
        return _monoBehaviourBridgeType;
    }

    ManagedType MonoBehaviour::unityType() {
        return _monoBehaviourType;
    }

    void MonoBehaviour::InitializeManagedBridge() {
        _monoBehaviourBridgeType = ManagedType(_monoBehaviourBridgeAssembly);
        _monoBehaviourType = ManagedType(_monoBehaviourAssembly);
    }
}

using namespace UnityEngine;

extern "C" {
    UNITY_EXPORT pointer_c CreateNativeMonoBehaviourInstance(string_c className, pointer_c managedInstance) {
        ManagedPointer ptr = ManagedPointer(managedInstance);
        ManagedInstance instance = ManagedInstance(ptr);
        MonoBehaviour *monoBehaviour = Registry::create(className, instance, nullptr);
        return static_cast<pointer_c>(monoBehaviour);
    }

    UNITY_EXPORT void DestroyNativeMonoBehaviourInstance(pointer_c nativePointer) {
        Object::destroyImmediate((MonoBehaviour *) nativePointer);
    }

    UNITY_EXPORT MonoBehaviour *Convert(pointer_c instancePtr) {
        return (MonoBehaviour *) instancePtr;
    }

    UNITY_EXPORT void CallMonoBehaviourAwake(pointer_c instancePtr) {
        Convert(instancePtr)->Awake();
    }

    UNITY_EXPORT void CallMonoBehaviourOnDestroy(pointer_c instancePtr) {
        Convert(instancePtr)->OnDestroy();
    }

    UNITY_EXPORT void CallMonoBehaviourStart(pointer_c instancePtr) {
        Convert(instancePtr)->Start();
    }

    UNITY_EXPORT void CallMonoBehaviourStop(pointer_c instancePtr) {
        Convert(instancePtr)->Stop();
    }

    UNITY_EXPORT void CallMonoBehaviourOnEnable(pointer_c instancePtr) {
        Convert(instancePtr)->OnEnable();
    }

    UNITY_EXPORT void CallMonoBehaviourOnDisable(pointer_c instancePtr) {
        Convert(instancePtr)->OnDisable();
    }

    UNITY_EXPORT void CallMonoBehaviourFixedUpdate(pointer_c instancePtr) {
        Convert(instancePtr)->FixedUpdate();
    }

    UNITY_EXPORT void CallMonoBehaviourUpdate(pointer_c instancePtr) {
        Convert(instancePtr)->Update();
    }

    UNITY_EXPORT void CallMonoBehaviourLateUpdate(pointer_c instancePtr) {
        Convert(instancePtr)->LateUpdate();
    }
}