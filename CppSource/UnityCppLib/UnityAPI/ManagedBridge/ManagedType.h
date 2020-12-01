#pragma once

#include "Managed.h"

#include <cstdint>

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

        ConstructorMember getConstructor(ManagedType parameterTypes[], int paramCount) const;
        FieldMember getField(const char *fieldName) const;
        PropertyMember getProperty(const char *propertyName) const;
    };
}