#pragma once

#include "UnityAPI/ManagedBridge/ManagedInstance.h"

#include <cstdint>

using namespace ManagedBridge;

namespace ManagedBridge::Members {
    class ManagedMember : public Managed {
    private:
        MemberType _type;

    protected:
        ManagedMember(ManagedPointer ptr, MemberType type);

    public:
        template<typename TValue>
        [[maybe_unused,nodiscard]] TValue get(ManagedInstance instance) const;
        template<typename TValue>
        [[maybe_unused]] void set(ManagedInstance instance, TValue value) const;
    };
}