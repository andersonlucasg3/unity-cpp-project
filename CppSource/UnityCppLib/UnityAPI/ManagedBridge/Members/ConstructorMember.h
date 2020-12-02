#pragma once

#include "ManagedMember.h"

namespace ManagedBridge {
    class ManagedType;
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

        ManagedInstance constructor(void *parameters[], int paramCount) const;
    };
}