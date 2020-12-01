#pragma once

#include "UnityAPI/ManagedBridge/ManagedInstance.h"

#include <cstdint>

using namespace UnityEngine::ManagedBridge;

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

    template<>
    ManagedPointer ManagedMember::pull<ManagedPointer>(ManagedInstance instance) const {
        return pull<void *>(instance);
    }

    template<>
    void ManagedMember::push(ManagedInstance instance, ManagedPointer value) const {
        push<const void *>(instance, value);
    }
}