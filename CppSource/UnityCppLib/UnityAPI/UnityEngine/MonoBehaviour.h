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
        virtual void Awake();
        virtual void OnDestroy();
        virtual void Start();
        virtual void Stop();
        virtual void OnEnable();
        virtual void OnDisable();
        virtual void FixedUpdate();
        virtual void Update();
        virtual void LateUpdate();

        static ManagedType type();
        static ManagedType unityType();
        static void InitializeManagedBridge();
    };
}