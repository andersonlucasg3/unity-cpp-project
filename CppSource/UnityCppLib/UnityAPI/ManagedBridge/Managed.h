#pragma once

#include "ManagedPointer.h"
#include "UnityAPI/ManagedBridge/Members/MemberType.h"
#include "UnityAPI/NetFramework/System.h"

#include <cstdint>

using namespace System;

namespace ManagedBridge {
    typedef void (*UnitySendMessageMethod)(string_c gameObjectName, string_c methodName, string_c message);

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
        bool operator==(pointer_m ptr);
        bool operator!=(pointer_m ptr);
    };
}