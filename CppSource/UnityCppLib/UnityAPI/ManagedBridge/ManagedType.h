#pragma once

#include "Managed.h"

#include <cstdint>

namespace UnityEngine::ManagedBridge {
    struct ManagedPointer;
    struct ManagedAssembly;

    namespace Members {
        class ConstructorMember;
        class FieldMember;
        class PropertyMember;
    }

    using namespace Members;

    class ManagedType : public Managed {
        friend class ManagedInstance;

    private:
        ManagedType();
        explicit ManagedType(ManagedPointer ptr);
        explicit ManagedType(ManagedAssembly assembly);

    public:
        static const ManagedType null;

        ConstructorMember getConstructor(char **parameters, int paramCount) const;
        FieldMember getField(const char *fieldName) const;
        PropertyMember getProperty(const char *propertyName) const;
    };
}