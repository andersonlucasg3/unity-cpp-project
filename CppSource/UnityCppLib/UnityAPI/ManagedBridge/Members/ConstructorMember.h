#pragma once

#include "ManagedMember.h"

namespace UnityEngine::ManagedBridge {
    class ManagedType;
}

namespace UnityEngine::ManagedBridge::Members {
    class ConstructorMember : public ManagedMember {
        friend class ManagedBridge::ManagedType;

    private:
        ConstructorMember();

    protected:
        explicit ConstructorMember(ManagedPointer ptr);

    public:
        static const ConstructorMember null;

        ManagedInstance constructor(ManagedType type, void *parameters[], int paramCount) const;
    };
}