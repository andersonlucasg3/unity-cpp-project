#pragma once

#include "Component.h"

namespace ManagedBridge {
    class ManagedType;

    namespace Members {
        class PropertyMember;
    }
}

using namespace ManagedBridge;
using namespace ManagedBridge::Members;


namespace UnityEngine {
    class Behaviour : public Component {
    private:
        static ManagedType _behaviourBridgeType;
        static ManagedType _behaviourType;

        static PropertyMember _enabledProperty;
        static PropertyMember _isActiveAndEnabledProperty;

    protected:
        explicit Behaviour(ManagedInstance instance, const GameObject *gameObject);
        ~Behaviour();

    public:
        bool enabled() const;
        bool isActiveAndEnabled() const;

        static ManagedType type();
        static ManagedType unityType();
        static void InitializeManagedBridge();
    };
}