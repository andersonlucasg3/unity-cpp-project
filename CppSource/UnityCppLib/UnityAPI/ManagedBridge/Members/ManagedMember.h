#pragma once

#include "UnityAPI/ManagedBridge/Managed.h"

#include <cstdint>

namespace UnityEngine::ManagedBridge {
    class ManagedInstance;
}

namespace UnityEngine::ManagedBridge::Members {
    class ManagedMember : public Managed {
    private:
        MemberType _type;

    protected:
        ManagedMember(ManagedPointer ptr, MemberType type);

        template<typename TValue>
        [[maybe_unused,nodiscard]] TValue pull(ManagedInstance instance) const;
        template<typename TValue>
        [[maybe_unused]] void push(ManagedInstance instance, TValue value) const;
    };
}