#include "MonoBehaviour.h"
#include "UnityAPI/CppEngine/Registry.h"
#include "UnityAPI/CppEngine/Trash.h"

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
    pointer_c CreateNativeMonoBehaviourInstance(string_c className, pointer_c managedInstance) {
        ManagedPointer ptr = ManagedPointer(managedInstance);
        ManagedInstance instance = ManagedInstance(ptr);
        MonoBehaviour *monoBehaviour = Registry::create(className, instance, nullptr);
        return static_cast<pointer_c>(monoBehaviour);
    }

    void DestroyNativeMonoBehaviourInstance(pointer_c nativePointer) {
        Object::destroyImmediate((MonoBehaviour *)nativePointer);
    }

    MonoBehaviour *Convert(pointer_c instancePtr) {
        return (MonoBehaviour *)instancePtr;
    }

    void CallMonoBehaviourAwake(pointer_c instancePtr) {
        Convert(instancePtr)->Awake();
    }

    void CallMonoBehaviourOnDestroy(pointer_c instancePtr) {
        MonoBehaviour *monoBehaviour = Convert(instancePtr);
        monoBehaviour->OnDestroy();
        Trash::add(monoBehaviour);
    }

    void CallMonoBehaviourStart(pointer_c instancePtr) {
        Convert(instancePtr)->Start();
    }

    void CallMonoBehaviourStop(pointer_c instancePtr) {
        Convert(instancePtr)->Stop();
    }

    void CallMonoBehaviourOnEnable(pointer_c instancePtr) {
        Convert(instancePtr)->OnEnable();
    }

    void CallMonoBehaviourOnDisable(pointer_c instancePtr) {
        Convert(instancePtr)->OnDisable();
    }

    void CallMonoBehaviourFixedUpdate(pointer_c instancePtr) {
        Convert(instancePtr)->FixedUpdate();
    }

    void CallMonoBehaviourUpdate(pointer_c instancePtr) {
        Convert(instancePtr)->Update();
    }

    void CallMonoBehaviourLateUpdate(pointer_c instancePtr) {
        Convert(instancePtr)->LateUpdate();
    }
}