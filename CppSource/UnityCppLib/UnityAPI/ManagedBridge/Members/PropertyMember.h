#pragma once

#include "ManagedMember.h"

namespace UnityEngine::ManagedBridge {
    class ManagedType;
}

namespace UnityEngine::ManagedBridge::Members {
    class PropertyMember : public ManagedMember {
        friend class ManagedBridge::ManagedType;

    private:
        PropertyMember();

    protected:
        explicit PropertyMember(ManagedPointer ptr);

    public:
        static const PropertyMember null;
    };
}