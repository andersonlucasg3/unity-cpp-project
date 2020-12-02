#pragma once

#include "Managed.h"
#include "ManagedType.h"

namespace ManagedBridge {
    class ManagedType;
    struct ManagedPointer;

    namespace Members {
        class ConstructorMember;
    }

    class ManagedInstance : public Managed {
        friend class Members::ConstructorMember;

    private:
        ManagedInstance();

    public:
        static const ManagedInstance null;

        ManagedInstance(ManagedPointer ptr);
    };
}