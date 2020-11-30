#pragma once

#include "Managed.h"
#include "ManagedType.h"

namespace UnityEngine::ManagedBridge {
    class ManagedType;
    struct ManagedPointer;

    namespace Members {
        class ConstructorMember;
    }

    class ManagedInstance : public Managed {
        friend class Members::ConstructorMember;

    private:
        ManagedType _type = ManagedType(ManagedPointer::null);

        ManagedInstance();

    public:
        static const ManagedInstance null;

        ManagedInstance(ManagedType type, ManagedPointer ptr);

        [[nodiscard]] const ManagedType type() const;
    };
}