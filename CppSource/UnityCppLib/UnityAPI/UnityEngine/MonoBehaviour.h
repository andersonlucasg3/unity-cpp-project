#pragma once

#include "Behaviour.h"

namespace UnityEngine {
    class MonoBehaviour : public Behaviour {
    private:
        static ManagedType _monoBehaviourBridgeType;
        static ManagedType _monoBehaviourType;

    protected:
        explicit MonoBehaviour(ManagedInstance instance, const GameObject *gameObject);
        ~MonoBehaviour();

    public:
        static ManagedType type();
        static ManagedType unityType();
        static void InitializeManagedBridge();
    };
}