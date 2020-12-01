#pragma once

#include "ManagedMember.h"

namespace UnityEngine::ManagedBridge {
    class ManagedType;
}

namespace UnityEngine::ManagedBridge::Members {
    class FieldMember : public ManagedMember {
        friend class ManagedBridge::ManagedType;

    private:
        FieldMember();

    protected:
        FieldMember(ManagedPointer ptr);

    public:
        static const FieldMember null;
    };
}