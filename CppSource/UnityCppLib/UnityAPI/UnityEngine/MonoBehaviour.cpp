#include "MonoBehaviour.h"

namespace UnityEngine {
    const ManagedAssemblyInfo _monoBehaviourBridgeAssembly("UnityCpp.NativeBridge.UnityBridges.MonoBehaviourBridge");
    const ManagedAssemblyInfo _monoBehaviourAssembly("UnityEngine.MonoBehaviour", "UnityEngine.dll");

    ManagedType MonoBehaviour::_monoBehaviourBridgeType = ManagedType::null;
    ManagedType MonoBehaviour::_monoBehaviourType = ManagedType::null;

    MonoBehaviour::MonoBehaviour(ManagedInstance instance, const GameObject *gameObject) : Behaviour(instance, gameObject) {
        //
    }

    MonoBehaviour::~MonoBehaviour() = default;

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