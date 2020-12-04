#pragma once

#include "UnityAPI/ManagedBridge/ManagedInstance.h"
#include "UnityAPI/ManagedBridge/UnmanagedValue.h"

#include <cstdint>

using namespace ManagedBridge;

namespace ManagedBridge::Members {
    class ManagedMember : public Managed {
    private:
        MemberType _type;

    protected:
        ManagedMember(ManagedPointer ptr, MemberType type);

    public:
        void get(ManagedInstance instance, UnmanagedValue *value) const;
        void setValue(ManagedInstance instance, UnmanagedValue *value) const;
    };
}