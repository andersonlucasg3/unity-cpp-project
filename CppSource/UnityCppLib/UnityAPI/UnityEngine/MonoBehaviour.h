#pragma once

#include "Behaviour.h"

namespace UnityEngine {
    class MonoBehaviour : public Behaviour {
    private:
        static ManagedType _monoBehaviourBridgeType;
        static ManagedType _monoBehaviourType;

    protected:
        explicit MonoBehaviour(ManagedInstance instance, const GameObject *gameObject);
        ~MonoBehaviour() override;

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

#define MONO_BEHAVIOUR_HEADER_CLASS(CLASS_NAME) \
    protected:                \
        CLASS_NAME(ManagedInstance instance, const GameObject *gameObject); \
    public: \
        static MonoBehaviour *Create(ManagedInstance instance, const GameObject *gameObject); \
        static void Register();

#define MONO_BEHAVIOUR_SOURCE_CLASS(CLASS_NAME) \
    CLASS_NAME::CLASS_NAME(ManagedInstance instance, const GameObject *gameObject) : MonoBehaviour(instance, gameObject) { } \
    \
    MonoBehaviour * CLASS_NAME::Create(ManagedInstance instance, const GameObject *gameObject) { \
        return new CLASS_NAME(instance, gameObject); \
    } \
    \
    void CLASS_NAME::Register() { \
        Registry::reg(#CLASS_NAME, &Create); \
    }