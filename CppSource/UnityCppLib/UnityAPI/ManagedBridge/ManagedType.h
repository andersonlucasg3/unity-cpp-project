#pragma once

#include "Managed.h"
#include "UnityAPI/NetFramework/System.h"

#include <cstdint>

using namespace System;

namespace ManagedBridge {
    struct ManagedPointer;
    struct ManagedAssemblyInfo;

    namespace Members {
        class ConstructorMember;
        class FieldMember;
        class PropertyMember;
    }

    using namespace Members;

    class ManagedType : public Managed {
    public:
        static const ManagedType null;

        ManagedType();
        explicit ManagedType(ManagedPointer ptr);
        explicit ManagedType(const ManagedAssemblyInfo& assembly);

        [[maybe_unused]] ConstructorMember getConstructor(ManagedType parameterTypes[], int paramCount) const;
        [[maybe_unused]] FieldMember getField(string_c fieldName) const;
        [[maybe_unused]] PropertyMember getProperty(string_c propertyName) const;
    };
}