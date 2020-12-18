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
        virtual void Awake() = 0;
        virtual void OnDestroy() = 0;
        virtual void Start() = 0;
        virtual void Stop() = 0;
        virtual void OnEnable() = 0;
        virtual void OnDisable() = 0;
        virtual void FixedUpdate() = 0;
        virtual void Update() = 0;
        virtual void LateUpdate() = 0;

        static ManagedType type();
        static ManagedType unityType();
        static void InitializeManagedBridge();
    };
}