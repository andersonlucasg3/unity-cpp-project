#pragma once

#include "ManagedMember.h"

namespace ManagedBridge {
    class ManagedType;
    struct UnmanagedValue;
}

namespace ManagedBridge::Members {
    class ConstructorMember : public ManagedMember {
        friend class ManagedBridge::ManagedType;

    private:
        ConstructorMember();

    protected:
        explicit ConstructorMember(ManagedPointer ptr);

    public:
        static const ConstructorMember null;

        ManagedInstance constructor(UnmanagedValue parameters[], int paramCount) const;
    };
}