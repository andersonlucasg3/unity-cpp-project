#pragma once

#include "ManagedMember.h"

namespace ManagedBridge {
    class ManagedType;
}

namespace ManagedBridge::Members {
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