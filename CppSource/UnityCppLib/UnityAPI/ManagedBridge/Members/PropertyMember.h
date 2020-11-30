#pragma once

#include "ManagedMember.h"

namespace UnityEngine::ManagedBridge {
    class ManagedType;
}

namespace UnityEngine::ManagedBridge::Members {
    class PropertyMember : public ManagedMember {
        friend class ManagedBridge::ManagedType;

    private:
        PropertyMember();

    protected:
        explicit PropertyMember(ManagedPointer ptr);

    public:
        static const PropertyMember null;

        template<typename TValue>
        TValue get(ManagedInstance instance) const;
        template<typename TValue>
        void set(ManagedInstance instance, TValue value) const;
    };
}