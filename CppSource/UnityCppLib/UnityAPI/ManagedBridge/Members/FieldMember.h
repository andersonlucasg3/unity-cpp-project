#pragma once

#include "ManagedMember.h"

namespace UnityEngine::ManagedBridge {
    class ManagedType;
}

namespace UnityEngine::ManagedBridge::Members {
    class FieldMember : public ManagedMember {
        friend class ManagedBridge::ManagedType;

    protected:
        FieldMember(ManagedPointer ptr);

    public:
        template<typename TValue>
        [[maybe_unused,nodiscard]] TValue get(ManagedInstance instance) const;
        template<typename TValue>
        [[maybe_unused]] void set(ManagedInstance instance, TValue value) const;
    };
}