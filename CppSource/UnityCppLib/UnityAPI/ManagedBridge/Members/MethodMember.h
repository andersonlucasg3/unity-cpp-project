#pragma once

#include "ManagedMember.h"

namespace ManagedBridge {
    class ManagedType;
}

namespace ManagedBridge::Members {
    class MethodMember : public ManagedMember {
        friend class ManagedBridge::ManagedType;

    private:
        MethodMember();

    protected:
        explicit MethodMember(ManagedPointer ptr);

    public:
        static const MethodMember null;

        void callMethod(ManagedInstance instance, UnmanagedValue parameters[], int paramCount, UnmanagedValue *output);
        bool callMethodOut(ManagedInstance instance, UnmanagedValue parameters[], int paramCount, UnmanagedValue *output);
    };
}