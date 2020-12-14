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
        class MethodMember;
    }

    using namespace Members;

    class ManagedType : public Managed {
    public:
        static const ManagedType null;

        ManagedType();
        explicit ManagedType(ManagedPointer ptr);
        explicit ManagedType(const ManagedAssemblyInfo& assembly);

        ConstructorMember getConstructor(ManagedType parameterTypes[], int paramCount) const;
        FieldMember getField(string_c fieldName) const;
        PropertyMember getProperty(string_c propertyName) const;
        MethodMember getMethod(string_c methodName) const;
    };
}