#pragma once

#include "UnityAPI/ManagedBridge/Members/MemberType.h"
#include "ManagedPointer.h"

#include <cstdint>

namespace UnityEngine::ManagedBridge {
    typedef void (*UnitySendMessageMethod)(const char *gameObjectName, const char *methodName, const char *message);

    struct ManagedPointer;

    namespace Members {
        class ManagedMember;
    }

    class Managed {
    private:
        ManagedPointer _ptr = ManagedPointer::null;

    protected:
        Managed(ManagedPointer ptr);

    public:
        static UnitySendMessageMethod UnitySendMessage;

        ManagedPointer toPointer() const;

        static void destroy(Managed *managed);
        static void destroy(const Managed &managed);
        static void destroy(ManagedPointer pointer);

        bool operator==(Managed other);
        bool operator!=(Managed other);
        bool operator==(void *ptr);
        bool operator!=(void *ptr);
    };
}